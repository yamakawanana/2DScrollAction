#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "DxLib.h"
#include "System/Collision/Collision.h"
#include "Game/Level/BattleLevel.h"
#include "System/LogConsole/LogConsole.h"
#include "System/Collision/Collision.h"
#include "Game/Fade/FadeManager.h"
#include "System/Math/Math.h"
#include "System/FileManager/FileManager.h"

//インスタンスの初期化
Collision* Collision::collision_ = nullptr;

/// <summary>
/// 無名名前空間
/// </summary>
namespace {

  /// <summary>
  /// リセット時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 1.0f;

  /// <summary>
  /// 二次元配列の要素の整数1を定数kFirstElementValueに格納する
  /// </summary>
  static const int kFirstElementValue = 1;

  /// <summary>
  /// 二次元配列の要素の整数2を定数kSecondElementValueに格納する
  /// </summary>
  static const int kSecondElementValue = 2;

  /// <summary>
  /// 二次元配列の要素の整数3を定数kThirdElementValueに格納する
  /// </summary>
  static const int kThirdElementValue = 3;

  /// <summary>
  /// 二次元配列の要素の整数4を定数kForthElementValueに格納する
  /// </summary>
  static const int kForthElementValue = 4;

  /// <summary>
  /// 二次元配列の要素の整数5を定数kFifthElementValueに格納する
  /// </summary>
  static const int kFifthElementValue = 5;

  /// <summary>
  /// 二次元配列の要素の整数6を定数kSixthElementValueに格納する
  /// </summary>
  static const int kSixthElementValue = 6;

  /// <summary>
  /// 二次元配列の要素の整数7を定数kSeventhElementValueに格納する
  /// </summary>
  static const int kSeventhElementValue = 7;

  /// <summary>
  /// 二次元配列の要素の整数8を定数kEighthElementValueに格納する
  /// </summary>
  static const int kEighthElementValue = 8;

  /// <summary>
  /// 二次元配列の要素の整数9を定数kNineElementValueに格納する
  /// </summary>
  static const int kNineElementValue = 9;

  /// <summary>
  /// マップデータを読み込むファイル名を定数kMapdataCSVsに格納する
  /// </summary>
  static const char* kMapdataCSVs[] = { "Assets/CsvFiles/mapdata.csv" ,"Assets/CsvFiles/mapdata2.csv" ,"Assets/CsvFiles/mapdata3.csv" };

  /// <summary>
  /// ステージ数を保存するファイル名を定数kStageNumCSVに格納する
  /// </summary>
  static const char* kStageNumCSV = "Assets/CsvFiles/stage_num.csv";

  /// <summary>
  /// 文字を格納する変数bufの要素数を定数kBufElementに格納する
  /// </summary>
  static const int kBufElement = 10;

  /// <summary>
  /// 当たり判定の幅を微調整する整数を定数kDifferenceに格納する
  /// </summary>
  static const int kDifference = 10;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Collision::Collision(int stage_num)
  : map_type_(kNone)
  , collision_phase_type_(kCollisionInitialized)
  , now_phase_(kCollisionInitialized)
  , player_enemy_collisiontype_(kCollisionNone)
  , mapdata_{ kNone }
  , pre_level_(1)
  , index_(0)
  , player_x_pos_(0)
  , is_ground_(true)
  , is_pile_bottom_(false)
  , is_pile_right_(false)
  , is_pile_left_(false)
  , enemy_type_(kFirstWalkingEnemy)
  , is_player_tube_(false)
  , stage_type_(static_cast<StageType>(stage_num))
{
  DEBUG_PRINT(Collisionのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Collision::~Collision() {
  DEBUG_PRINT(Collisionのデストラクタ);
}

/// <summary>
/// インスタンスを生成する
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void Collision::CreateInstance(int stage_num) {
  //まだインスタンスが生成されていなければ、インスタンスを生成する
  if (collision_ == nullptr) {
    collision_ = new Collision(stage_num);
  }
}

/// <summary>
/// インスタンスを取得する
/// </summary>
/// <param>なし</param>
/// <returns>インスタンス</returns>
Collision* Collision::GetInstance() {
  return collision_;
}

/// <summary>
/// インスタンスを解放する
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void Collision::ReleaseInstance() {
  if (collision_ != nullptr) {
    delete collision_;
    collision_ = nullptr;
  }
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name></param>
/// <returns>処理終了：true、処理継続：false</returns>
bool Collision::PhaseInitialize() {

  InitializeMapData();

  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool Collision::PhaseUpdate(float time) {

  return false;
}

/// <summary>
/// 終了処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool Collision::PhaseFinalize(float time) {
  //mapdata_を初期化する
  for (int i = 0; i < kTotalRow; i++) {
    for (int j = 0; j < kTotalColumn; j++) {
      mapdata_[i][j] = { kNone };
    }
  }

  return true;
}

/// <summary>
/// mapdata_の指定位置の要素を変更する関数
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "maptype">マップの種類</param>
/// <returns>なし</returns>
void Collision::SetMapType(int x, int y, MapType maptype) {
  mapdata_[y][x] = maptype;
}

/// <summary>
/// mapdata_の指定位置の要素を返す関数
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <returns>マップの種類</returns>
Collision::MapType Collision::GetMapType(int x, int y) {
  return mapdata_[y][x];
}

/// <summary>
/// SetPlayerXPos関数の定義
/// </summary>
/// <param = "player_x_pos">プレイヤーのX位置</param>
/// <returns>なし</returns>
void Collision::SetPlayerXPos(int player_x_pos) {
  player_x_pos_ = player_x_pos;
}

/// <summary>
/// IsFootGround関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "character_size">キャラクター画像の幅と高さ</param>
/// <returns>プレイヤーの足元に地面かブロックがあるかの有無</returns>
bool Collision::IsFootGround(int& x, int& y, int character_height) {

  //プレイヤーの足元のY位置を計算する
  int foot_y = y + character_height;
  //プレイヤーの足元のX位置はマップ上のどのX位置にあたるか計算する
  double map_foot_x = x / kMapSize;
  //DEBUG_PRINT_VAR(map_foot_x);
  //プレイヤーの足元のY位置はマップ上のどのY位置にあたるか計算する
  double map_foot_y = foot_y / kMapSize;
  //DEBUG_PRINT_VAR(map_foot_y);

  //mapdata_内でプレイヤーの足元の位置の下が0ではない場合、マップ上の物体と接している
  if ((map_foot_y >= 0) && (map_foot_y < kTotalRow) && mapdata_[static_cast<int>(map_foot_y)][static_cast<int>(map_foot_x) + 1] != 0 && mapdata_[static_cast<int>(map_foot_y)][static_cast<int>(map_foot_x) + 1] != kNineElementValue) {
    //DEBUG_PRINT(下と接している);
    //プレイヤーの立ち位置が地面に少しめり込む位置にある時、立ち位置を調整する
    if (foot_y > map_foot_y * kMapSize) {
      is_pile_bottom_ = true;
      foot_y = static_cast<int>(map_foot_y * kMapSize);
      y = foot_y - character_height;
    }
    else if (foot_y == map_foot_y * kMapSize) {
      is_pile_bottom_ = false;
    }
    return true;
  }

  return false;
}

/// <summary>
/// IsHitRight関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "character_size">キャラクター画像の幅と高さ</param>
/// <returns>プレイヤーの右側に地面かブロックがあるかの有無</returns>
bool Collision::IsHitRight(int& x, int y, int character_size) {
  //プレイヤーの右端のX位置を計算する
  int right_x = x + character_size;
  //プレイヤーの右端のX位置はマップ上のどのX位置にあたるか計算する
  double map_right_x = right_x / kMapSize;
  //DEBUG_PRINT_VAR(map_right_x);
  //プレイヤーの右端のY位置はマップ上のどのY位置にあたるか計算する
  double map_right_y = y / kMapSize;
  //DEBUG_PRINT_VAR(map_right_y);

  //プレイヤーの足元のY位置を計算する
  int foot_y = y + character_size;
  //プレイヤーの足元のY位置はマップ上のどのY位置にあたるか計算する
  double map_foot_y = foot_y / kMapSize;
  //DEBUG_PRINT_VAR(map_foot_y);

  //mapdata_内でプレイヤーの右端の位置の右が0ではない場合、マップ上の物体と接している
  if ((map_right_y < kTotalRow - 1) && (map_right_y >= 0) && (mapdata_[static_cast<int>(map_right_y + 1)][static_cast<int>(map_right_x)] != 0) && mapdata_[static_cast<int>(map_right_y + 1)][static_cast<int>(map_right_x)] != kNineElementValue) {
    //DEBUG_PRINT(右側にぶつかった);
    //プレイヤーの立ち位置が２つのマップチップに跨っている時、立ち位置を調整する
    if (right_x > map_right_x * kMapSize) {
      //right_x = static_cast<int>(map_right_x * kMapSize + kMapSize / kSecondElementValue);
      //x = right_x - character_size;
      //DEBUG_PRINT(右側重なった);
    }
    return true;
  }

  return false;
}

/// <summary>
/// IsHitLeft関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "character_size">キャラクター画像の幅と高さ</param>
/// <returns>プレイヤーの左側に地面かブロックがあるかの有無</returns>
bool Collision::IsHitLeft(int& x, int y, int character_size) {
  //プレイヤーの左端のX位置を計算する
  int left_x = x;
  //プレイヤーの左端のX位置はマップ上のどのX位置にあたるか計算する
  double map_left_x = left_x / kMapSize;
  //DEBUG_PRINT_VAR(map_left_x);
  //プレイヤーの左端のY位置はマップ上のどのY位置にあたるか計算する
  double map_left_y = y / kMapSize;
  //DEBUG_PRINT_VAR(map_left_y);

  //プレイヤーの足元のY位置を計算する
  int foot_y = y + character_size;
  //プレイヤーの足元のY位置はマップ上のどのY位置にあたるか計算する
  double map_foot_y = foot_y / kMapSize;
  //DEBUG_PRINT_VAR(map_foot_y);

  //mapdata_内でプレイヤーの左端の位置の左が0ではない場合、マップ上の物体と接している
  if ((map_left_y < kTotalRow -1) && (map_left_y >= 0) && (mapdata_[static_cast<int>(map_left_y) + 1][static_cast<int>(map_left_x)] != 0) && mapdata_[static_cast<int>(map_left_y) + 1][static_cast<int>(map_left_x)] != kNineElementValue) {
    //DEBUG_PRINT(左側にぶつかった);
    //プレイヤーの立ち位置が２つのマップチップに跨っている時、立ち位置を調整する
    if (left_x < map_left_x * kMapSize) {
      //left_x = static_cast<int>(map_left_x * kMapSize);
      //x = left_x;
      //DEBUG_PRINT(左側重なった);
    }

    return true;
  }

  return false;
}

/// <summary>
/// IsHitHead関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "character_size">キャラクター画像の幅と高さ</param>
/// <returns>プレイヤーの頭上に地面かブロックがあるかの有無</returns>
bool Collision::IsHitHead(int x, int y, int character_size) {
  //プレイヤーの頭上のY位置を計算する
  int head_y = y;
  //プレイヤーの頭上のX位置はマップ上のどのX位置にあたるか計算する
  double map_head_x = x / kMapSize;
  //DEBUG_PRINT_VAR(map_head_x);
  //プレイヤーの頭上のY位置はマップ上のどのY位置にあたるか計算する
  double map_head_y = head_y / kMapSize;
  //DEBUG_PRINT_VAR(map_head_y);

  //mapdata_内でプレイヤーの頭上の位置の上が0ではない場合、マップ上の物体と接している
  if ((map_head_y < kTotalRow) && (map_head_y >= 0) && mapdata_[static_cast<int>(map_head_y)][static_cast<int>(map_head_x) + 1] != 0 && mapdata_[static_cast<int>(map_head_y)][static_cast<int>(map_head_x) + 1] != kNineElementValue) {
    return true;
  }

  return false;
}

/// <summary>
/// InitializeMapData関数の定義
/// </summary>
/// <param>なし</param>
/// <returns></returns>
void Collision::InitializeMapData() {
  //mapdata_を初期化するための一時的な二次元配列を用意する
  int cell[kTotalRow][kTotalColumn];

  //ファイルのポインタを宣言する
  FILE* fp;

  for (int j = 0; j < static_cast<int>(kThirdStage) + 1; j++) {
    if (stage_type_ == static_cast<StageType>(j)) {
      DEBUG_PRINT_VAR(j);
      //ファイルを開く
      if ((fopen_s(&fp, kMapdataCSVs[j], "r")) != 0) {
        printf("ファイルを開けませんでした");
      }

      //文字を格納する変数
      int cha;
      //行と列の整数を格納する変数
      int row = 0;
      int width = 0;
      //文字列を格納する配列
      char buf[kBufElement];
      //bufを初期化する
      memset(buf, 0, sizeof(buf));
      //テキストファイルの末尾であるかを示す変数
      bool eof_flag = false;

      while (1) {
        while (1) {
          //ファイルを読み込む
          cha = fgetc(fp);
          //テキストファイルの末尾の場合、ループを2回抜けるためにeof_flagをtrueにする
          if (cha == EOF) {
            eof_flag = true;
            break;
          }
          //chaがカンマ区切りか改行でなければ、bufに連結する
          if (cha != ',' && cha != '\n') {
            strcat_s(buf, (const char*)&cha);
          }
          else {
            //bufをint型に変換し、cellの要素として代入する
            int num = atoi(buf);
            cell[row][width] = num;
            //bufを初期値に戻す
            memset(buf, 0, sizeof(buf));
            break;
          }
        }
        //テキストファイルの末尾の場合
        if (eof_flag) {
          break;
        }
        //カンマ区切りの場合
        if (cha == ',') {
          width++;
        }
        //改行の場合
        if (cha == '\n') {
          row++;
          width = 0;
        }
      }

      //cellの要素をmapdata_にコピーし、mapdata_を初期化する
      for (int i = 0; i < kTotalRow; i++) {
        for (int j = 0; j < kTotalColumn; j++) {
          int element_value = cell[i][j];
          switch (element_value) {
          case kFirstElementValue:
            mapdata_[i][j] = MapType::kGround;
            break;
          case kSecondElementValue:
            mapdata_[i][j] = MapType::kBox;
            break;
          case kThirdElementValue:
            mapdata_[i][j] = MapType::kTubeRimLeft;
            break;
          case kForthElementValue:
            mapdata_[i][j] = MapType::kTubeRimMiddle;
            break;
          case kFifthElementValue:
            mapdata_[i][j] = MapType::kTubeRimRight;
            break;
          case kSixthElementValue:
            mapdata_[i][j] = MapType::kTubeLeft;
            break;
          case kSeventhElementValue:
            mapdata_[i][j] = MapType::kTubeMiddle;
            break;
          case kEighthElementValue:
            mapdata_[i][j] = MapType::kTubeRight;
            break;
          case kNineElementValue:
            mapdata_[i][j] = MapType::kGoal;
            break;
          }
        }
      }
      DEBUG_PRINT(Collisionのmapdata_を初期化した);
    }
  }
}

/// <summary>
/// IsPileBottom関数の宣言
/// </summary>
/// <returns>プレイヤーの足元が地面かブロックと重なっているかの有無</returns>
bool Collision::IsPileBottom() {
  return is_pile_bottom_;
}

/// <summary>
/// IsPileRight関数の宣言
/// </summary>
/// <returns>プレイヤーの右が地面かブロックと重なっているかの有無</returns>
bool Collision::IsPileRight() {
  return is_pile_right_;
}

/// <summary>
/// IsPileLeft関数の宣言
/// </summary>
/// <returns>プレイヤーの左が地面かブロックと重なっているかの有無</returns>
bool Collision::IsPileLeft() {
  return is_pile_left_;
}

/// <summary>
/// IsHitPlayerEnemy関数の定義
/// </summary>
/// <param = "player_x">プレイヤーX位置</param>
/// <param = "player_y">プレイヤーY位置</param>
/// <param = "player_size">プレイヤー画像の幅と高さ</param>
/// <param = "enemy_x">敵X位置</param>
/// <param = "enemy_y">敵Y位置</param>
/// <param = "enemy_width">敵の画像の幅</param>
/// <param = "enemy_height">敵の画像の高さ</param>
/// <returns>プレイヤーが敵とぶつかっているかの有無</returns>
bool Collision::IsHitPlayerEnemy(int player_x, int player_y, int player_size, int enemy_x, int enemy_y, int enemy_width, int enemy_height, Task::TaskId enemy_id) {

  //DEBUG_PRINT_VAR(player_enemy_collisiontype_);

  //DEBUG_PRINT_VAR(player_x);
  //DEBUG_PRINT_VAR(player_y);
  //DEBUG_PRINT_VAR(enemy_x);
  //DEBUG_PRINT_VAR(enemy_y);

  //プレイヤーの足元のY位置を計算する
  int foot_y = player_y + player_size - kDifference;
  //プレイヤーの右側のX位置を計算する
  int player_right = player_x + player_size - kDifference;
  //敵の頭上のY位置を計算する
  int head_enemy;
  if (enemy_id > Task::TaskId::kMaxJumpingEnemyNum) {
    head_enemy = enemy_y;
  }
  else {
    head_enemy = enemy_y + kDifference * kThirdElementValue;
  }
  //敵の足元のY位置を計算する
  int foot_enemy = enemy_y + enemy_height - kDifference;
  //敵の右側のX位置を計算する
  int enemy_right = enemy_x + enemy_width - kDifference;

  if ((player_right > enemy_x) && (player_x < enemy_right) && (player_y < foot_enemy) && (foot_y > head_enemy)) {
    //DEBUG_PRINT(敵とぶつかった);
    if (foot_y > enemy_y && foot_y < foot_enemy && enemy_id > Task::TaskId::kMaxJumpingEnemyNum && player_enemy_collisiontype_ != kDamage && player_enemy_collisiontype_ != kDamageWait) {
      //DEBUG_PRINT(敵を倒した);
      player_enemy_collisiontype_ = kAttackEnemy;
    }
    else if(player_enemy_collisiontype_ == kCollisionNone){
      //DEBUG_PRINT(ダメージを受けた);
      player_enemy_collisiontype_ = kDamage;
    }
    return true;
  }

  return false;
}

/// <summary>
/// SetPlayerEnemyCollisionType関数の定義
/// </summary>
/// <param = "type">プレイヤーと敵の衝突判定の種類</param>
/// <returns>なし</returns>
void Collision::SetPlayerEnemyCollisionType(PlayerEnemyCollisionType type) {
  player_enemy_collisiontype_ = type;
}

/// <summary>
/// GetPlayerEnemyCollisionType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>プレイヤーと敵の衝突判定の種類</returns>
Collision::PlayerEnemyCollisionType Collision::GetPlayerEnemyCollisionType() {
  return player_enemy_collisiontype_;
}

/// <summary>
/// IsHitPlayerItem関数の定義
/// </summary>
/// <param = "player_x">プレイヤーX位置</param>
/// <param = "player_y">プレイヤーY位置</param>
/// <param = "player_size">プレイヤー画像の幅と高さ</param>
/// <param = "items_x">アイテムX位置</param>
/// <param = "items_y">アイテムY位置</param>
/// <param = "items_width">アイテムの画像の幅</param>
/// <param = "items_height">アイテムの画像の高さ</param>
/// <returns>プレイヤーがアイテムとぶつかっているかの有無</returns>
bool Collision::IsHitPlayerItem(int player_x, int player_y, int player_size, int items_x, int items_y, int items_width, int items_height, Task::TaskId items_id) {

  //DEBUG_PRINT_VAR(player_enemy_collisiontype_);

  //DEBUG_PRINT_VAR(player_x);
  //DEBUG_PRINT_VAR(player_y);
  //DEBUG_PRINT_VAR(enemy_x);
  //DEBUG_PRINT_VAR(enemy_y);

  //プレイヤーの足元のY位置を計算する
  int foot_y = player_y + player_size - kDifference;
  //プレイヤーの右側のX位置を計算する
  int player_right = player_x + player_size - kDifference;
  //アイテムの頭上のY位置を計算する
  int head_item = items_y;
  //アイテムの足元のY位置を計算する
  int foot_item = items_y + items_height - kDifference;
  //アイテムの右側のX位置を計算する
  int items_right = items_x + items_width - kDifference;

  if ((player_right > items_x) && (player_x < items_right) && (player_y < foot_item) && (foot_y > head_item)) {
    //DEBUG_PRINT(アイテムとぶつかった);

    return true;
  }

  return false;
}

/// <summary>
/// IsPlayerWithTube関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "character_size">キャラクター画像の幅と高さ</param>
/// <returns>プレイヤーが土管の周りに立っているかの有無</returns>
bool Collision::IsPlayerWithTube(int x, int y, int character_size) {
  //プレイヤーの足元のY位置を計算する
  int foot_y = y + character_size;
  //プレイヤーの足元のX位置はマップ上のどのX位置にあたるか計算する
  double map_foot_x = x / kMapSize;
  //プレイヤーの足元のY位置はマップ上のどのY位置にあたるか計算する
  double map_foot_y = foot_y / kMapSize;

  //プレイヤーの右端のX位置を計算する
  int right_x = x + character_size;
  //プレイヤーの右端のX位置はマップ上のどのX位置にあたるか計算する
  double map_right_x = right_x / kMapSize;
  //プレイヤーの右端のY位置はマップ上のどのY位置にあたるか計算する
  double map_right_y = y / kMapSize;

  //プレイヤーの左端のX位置を計算する
  int left_x = x;
  //プレイヤーの左端のX位置はマップ上のどのX位置にあたるか計算する
  double map_left_x = left_x / kMapSize;
  //プレイヤーの左端のY位置はマップ上のどのY位置にあたるか計算する
  double map_left_y = y / kMapSize;

  //mapdata_内でプレイヤーの右端か左端の位置が土管の位置である場合、土管と接している
  for (int i = 0; i < kTotalRow; i++) {
    if ((map_foot_y >= 0) && (map_foot_y < kTotalRow) && (map_left_y < kTotalRow) && (map_left_y >= 0) && (map_right_y < kTotalRow) && (map_right_y >= 0) && ((mapdata_[static_cast<int>(i)][static_cast<int>(map_foot_x) + 1] > kSecondElementValue && mapdata_[static_cast<int>(i)][static_cast<int>(map_foot_x) + 1] <= kEighthElementValue) || (mapdata_[static_cast<int>(i + 1)][static_cast<int>(map_right_x)] > kSecondElementValue && mapdata_[static_cast<int>(i + 1)][static_cast<int>(map_right_x)] <= kEighthElementValue) || (mapdata_[static_cast<int>(i + 1)][static_cast<int>(map_left_x)] > kSecondElementValue && mapdata_[static_cast<int>(i + 1)][static_cast<int>(map_left_x)] <= kEighthElementValue))) {
      //DEBUG_PRINT(土管の周りにいる);
      return true;
    }
  }

  return false;
}

/// <summary>
/// IsPlayerGoal関数の定義
/// </summary>
/// <param = "x">プレイヤーX位置</param>
/// <param = "y">プレイヤーY位置</param>
/// <param = "character_size">プレイヤー画像の幅と高さ</param>
/// <returns>プレイヤーがゴールしたかの有無</returns>
bool Collision::IsPlayerGoal(int x, int y, int character_size) {
  //プレイヤーの足元のY位置を計算する
  int foot_y = y + character_size;
  //プレイヤーの足元のX位置はマップ上のどのX位置にあたるか計算する
  double map_foot_x = x / kMapSize;
  //プレイヤーの足元のY位置はマップ上のどのY位置にあたるか計算する
  double map_foot_y = foot_y / kMapSize;

  //プレイヤーの右端のX位置を計算する
  int right_x = x + character_size;
  //プレイヤーの右端のX位置はマップ上のどのX位置にあたるか計算する
  double map_right_x = right_x / kMapSize;
  //プレイヤーの右端のY位置はマップ上のどのY位置にあたるか計算する
  double map_right_y = y / kMapSize;

  //プレイヤーの左端のX位置を計算する
  int left_x = x;
  //プレイヤーの左端のX位置はマップ上のどのX位置にあたるか計算する
  double map_left_x = left_x / kMapSize;
  //プレイヤーの左端のY位置はマップ上のどのY位置にあたるか計算する
  double map_left_y = y / kMapSize;

  if ((map_foot_y >= 0) && (map_foot_y < kTotalRow) && mapdata_[static_cast<int>(map_foot_y)][static_cast<int>(map_foot_x) + 1] == kNineElementValue
    || mapdata_[static_cast<int>(map_left_y) + 1][static_cast<int>(map_left_x + 1)] == kNineElementValue) {
    //DEBUG_PRINT(ゴール);

    return true;
  }

  return false;
}

/// <summary>
/// SetStageNum関数
/// </summary>
/// <param = "stage_num">現在のステージ</param>
/// <returns>なし</returns>
void Collision::SetStageNum(int stage_num) {
  stage_type_ = static_cast<StageType>(stage_num);
}

/// <summary>
/// IsHitRightFoot関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "character_size">キャラクター画像の幅と高さ</param>
/// <returns>プレイヤーの右側に地面かブロックがあるかの有無</returns>
bool Collision::IsHitRightFoot(int& x, int y, int character_size) {
  //プレイヤーの右端のX位置を計算する
  int right_x = x + character_size;
  //プレイヤーの右端のX位置はマップ上のどのX位置にあたるか計算する
  double map_right_x = right_x / kMapSize;
  //DEBUG_PRINT_VAR(map_right_x);
  //プレイヤーの右端のY位置はマップ上のどのY位置にあたるか計算する
  double map_right_y = y / kMapSize;
  //DEBUG_PRINT_VAR(map_right_y);

  //プレイヤーの足元のY位置を計算する
  int foot_y = y + character_size;
  //プレイヤーの足元のY位置はマップ上のどのY位置にあたるか計算する
  double map_foot_y = foot_y / kMapSize;
  //DEBUG_PRINT_VAR(map_foot_y);

  //mapdata_内でプレイヤーの右端足元の位置の右が0ではない場合、マップ上の物体と接している
  if ((map_foot_y >= 0) && (map_foot_y < kTotalRow) && mapdata_[static_cast<int>(map_foot_y)][static_cast<int>(map_right_x)] != 0) {
    //DEBUG_PRINT(足元右側にぶつかった);
    //プレイヤーの立ち位置が２つのマップチップに跨っている時、立ち位置を調整する
    if ((right_x > map_right_x * kMapSize)) {
      right_x = static_cast<int>(map_right_x * kMapSize + kMapSize / kSecondElementValue);
      x = right_x - character_size;
      //DEBUG_PRINT(足元右側位置調整);
    }
    return true;
  }

  return false;
}

/// <summary>
/// IsHitLeftFoot関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "character_size">キャラクター画像の幅と高さ</param>
/// <returns>プレイヤーの左側に地面かブロックがあるかの有無</returns>
bool Collision::IsHitLeftFoot(int& x, int y, int character_size) {
  //プレイヤーの左端のX位置を計算する
  int left_x = x;
  //プレイヤーの左端のX位置はマップ上のどのX位置にあたるか計算する
  double map_left_x = left_x / kMapSize;
  //DEBUG_PRINT_VAR(map_left_x);
  //プレイヤーの左端のY位置はマップ上のどのY位置にあたるか計算する
  double map_left_y = y / kMapSize;
  //DEBUG_PRINT_VAR(map_left_y);

  //プレイヤーの足元のY位置を計算する
  int foot_y = y + character_size;
  //プレイヤーの足元のY位置はマップ上のどのY位置にあたるか計算する
  double map_foot_y = foot_y / kMapSize;
  //DEBUG_PRINT_VAR(map_foot_y);

  //mapdata_内でプレイヤーの左端の足元の位置の左が0ではない場合、マップ上の物体と接している
  if ((map_foot_y >= 0) && (map_foot_y < kTotalRow) && mapdata_[static_cast<int>(map_foot_y)][static_cast<int>(map_left_x)] != 0) {
    //DEBUG_PRINT(足元左側にぶつかった);
    //プレイヤーの立ち位置が２つのマップチップに跨っている時、立ち位置を調整する
    if ((left_x >= map_left_x * kMapSize)) {
      left_x = static_cast<int>(map_left_x * kMapSize + kDifference * kSecondElementValue);
      x = left_x;
      //DEBUG_PRINT(足元左側位置調整);
    }

    return true;
  }

  return false;
}

/// <summary>
/// IsHitRightHead関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "character_size">キャラクター画像の幅と高さ</param>
/// <returns>プレイヤーの右側の真上にブロックがあるかの有無</returns>
bool Collision::IsHitRightHead(int& x, int y, int character_size) {
  //プレイヤーの右端のX位置を計算する
  int right_x = x + character_size;
  //プレイヤーの右端のX位置はマップ上のどのX位置にあたるか計算する
  double map_right_x = right_x / kMapSize;
  //DEBUG_PRINT_VAR(map_right_x);
  //プレイヤーの右端のY位置はマップ上のどのY位置にあたるか計算する
  double map_right_y = y / kMapSize;
  //DEBUG_PRINT_VAR(map_right_y);

  //mapdata_内でプレイヤーの右端の位置の右が0ではない場合、マップ上の物体と接している
  if ((map_right_y < kTotalRow - 1) && (map_right_y >= 0) && (mapdata_[static_cast<int>(map_right_y)][static_cast<int>(map_right_x)] != 0) && mapdata_[static_cast<int>(map_right_y + 1)][static_cast<int>(map_right_x)] != kNineElementValue) {
    //DEBUG_PRINT(右側にぶつかった);
    //プレイヤーの立ち位置が２つのマップチップに跨っている時、立ち位置を調整する
    if (right_x > map_right_x * kMapSize) {
      //right_x = static_cast<int>(map_right_x * kMapSize + kMapSize / kSecondElementValue);
      //x = right_x - character_size;
      //DEBUG_PRINT(右側重なった);
    }
    return true;
  }

  return false;
}

/// <summary>
/// IsHitLeftHead関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "character_size">キャラクター画像の幅と高さ</param>
/// <returns>プレイヤーの左側の真上にブロックがあるかの有無</returns>
bool Collision::IsHitLeftHead(int& x, int y, int character_size) {
  //プレイヤーの左端のX位置を計算する
  int left_x = x;
  //プレイヤーの左端のX位置はマップ上のどのX位置にあたるか計算する
  double map_left_x = left_x / kMapSize;
  //DEBUG_PRINT_VAR(map_left_x);
  //プレイヤーの左端のY位置はマップ上のどのY位置にあたるか計算する
  double map_left_y = y / kMapSize;
  //DEBUG_PRINT_VAR(map_left_y);

  //mapdata_内でプレイヤーの左端の位置の左が0ではない場合、マップ上の物体と接している
  if ((map_left_y < kTotalRow - 1) && (map_left_y >= 0) && (mapdata_[static_cast<int>(map_left_y)][static_cast<int>(map_left_x)] != 0) && mapdata_[static_cast<int>(map_left_y) + 1][static_cast<int>(map_left_x)] != kNineElementValue) {
    //DEBUG_PRINT(左側にぶつかった);
    //プレイヤーの立ち位置が２つのマップチップに跨っている時、立ち位置を調整する
    if (left_x >= map_left_x * kMapSize) {
      //left_x = static_cast<int>(map_left_x * kMapSize + kDifference * kSecondElementValue);
      //x = left_x;
      //DEBUG_PRINT(左側重なった);
    }

    return true;
  }

  return false;
}
