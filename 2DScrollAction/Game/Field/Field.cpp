#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "DxLib.h"
#include "Game/Field/Field.h"
#include "Game/Level/BattleLevel.h"
#include "System/LogConsole/LogConsole.h"
#include "Game/GameInfo/GameInfo.h"
#include "Game/Fade/FadeManager.h"
#include "System/Math/Math.h"
#include "System/FileManager/FileManager.h"
#include "Game/Fade/FadeManager.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {

  /// <summary>
  /// キー操作情報の画像のX位置を定数kKeyInfoXに格納する
  /// </summary>
  static const int kKeyInfoX = 0;

  /// <summary>
  /// キー操作情報の画像のY位置を定数kKeyInfoYに格納する
  /// </summary>
  static const int kKeyInfoY = 570;

  // <summary>
  //screen_handleの幅を定数kScreenHandleXに格納する
  /// <summary>
  static const int kScreenHandleX = 640;

  // <summary>
  //screen_handleの高さを定数kScreenHandleYに格納する
  /// <summary>
  static const int kScreenHandleY = 480;

  /// <summary>
  /// リセット時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 1.0f;

  /// <summary>
  /// アニメーション用のリセット時間を定数kAnimationLimitTimeに格納する
  /// </summary>
  static const float kAnimationLimitTime = 1.7f;

  /// <summary>
  /// 表示リセット時間を定数kLineNumLimitTimeに格納する
  /// </summary>
  static const float kLineNumLimitTime = 0.6f;

  /// <summary>
  //白色の値を取得
  /// </summary>
  unsigned int WhiteCr = GetColor(255, 255, 255);

  /// <summary>
  //黒色の値を取得
  /// </summary>
  unsigned int BlackCr = GetColor(0, 0, 0);

  /// <summary>
  /// フォントサイズの定数kFontSize
  /// </summary>
  static const int kFontSize = 21;

  /// <summary>
  /// フォントの太さの定数kFontThickness
  /// </summary>
  static const int kFontThickness = 10;

  /// <summary>
  /// フォントを指定する文字列を定数kFontに格納する
  /// </summary>
  static const char* kFont = "Arial";

  /// <summary>
  /// 「」を指定する文字列を定数kScoreに格納する
  /// </summary>
  static const char* kScore = "SCORE";

  /// <summary>
  /// 「%5d」を指定する文字列を定数kPercentFiveDに格納する
  /// </summary>
  static const char* kPercentFiveD = "%5d";

  /// <summary>
  /// 効果音の最大音量を定数kVolumeに格納する
  /// </summary>
  static const int kMaxSoundEffectVolume = 255;

  /// <summary>
  /// 100％の分母を定数kHundredに格納する
  /// </summary>
  static const int kHundred = 100;

  /// <summary>
  /// マップデータを読み込むファイル名を定数kMapdataCSVsに格納する
  /// </summary>
  static const char* kMapdataCSVs[] = { "Assets/CsvFiles/mapdata.csv" ,"Assets/CsvFiles/mapdata2.csv" ,"Assets/CsvFiles/mapdata3.csv" };

  /// <summary>
  /// ステージ数を保存するファイル名を定数kStageNumCSVに格納する
  /// </summary>
  static const char* kStageNumCSV = "Assets/CsvFiles/stage_num.csv";

  /// <summary>
  /// 配列の次の要素に切り替える時間を定数の配列kChangeTimeに格納する
  /// </summary>
  static const float kChangeTime[] = { 0.4f , 0.8f ,1.2f };

  /// <summary>
  /// 文字を格納する変数bufの要素数を定数kBufElementに格納する
  /// </summary>
  static const int kBufElement = 10;

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
}

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Field::Field()
  : task_manager_(nullptr)
  , map_type_(kNone)
  , field_phase_type_(kFieldInitialized)
  , now_phase_(kFieldInitialized)
  , battle_back_handle_(0)
  , accumulation_time_(0.0f)
  , mapdata_{ kNone }
  , box_handle_(0)
  , ground_gr_handle_(0)
  , is_gameover_(false)
  , index_(0)
  , confetti_handle_{}
  , player_x_pos_(0)
  , difference_x_pos_(0)
  , is_ground_(true)
  , fade_(0)
  , stage_type_(kFirstStage)
{
  DEBUG_PRINT(Fieldのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Field::Field(TaskId task_id, TaskManager* task_manager, int stage_num)
  : Task(task_id)
  , task_manager_(task_manager)
  , map_type_(kNone)
  , field_phase_type_(kFieldInitialized)
  , now_phase_(kFieldInitialized)
  , battle_back_handle_(0)
  , accumulation_time_(0.0f)
  , mapdata_{ kNone }
  , box_handle_(0)
  , ground_gr_handle_(0)
  , is_gameover_(false)
  , index_(0)
  , confetti_handle_{}
  , player_x_pos_(0)
  , difference_x_pos_(0)
  , is_ground_(true)
  , fade_(0)
  , stage_type_(static_cast<StageType>(stage_num))
{
  DEBUG_PRINT(Fieldのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Field::~Field() {
  DEBUG_PRINT(Fieldのデストラクタ);
}

/// <summary>
/// UpdateFrame関数の定義
/// </summary>
/// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
/// <returns>なし</returns>
void Field::UpdateFrame(float time) {

  //ゲームオーバー中ではなく、ポーズ中でなければ、累積時間を更新
  if (is_gameover_ != true && field_phase_type_ != kStop) {
    accumulation_time_ = accumulation_time_ + time;
  }
  if (accumulation_time_ >= kAnimationLimitTime) {
    accumulation_time_ = 0.0f;
    index_ = 0;
  }

  //DEBUG_PRINT(Fieldクラスの毎フレーム更新処理);
  if (now_phase_ != kStop) {

    bool result = false;

    switch (field_phase_type_) {

      //フェーズが初期化フェーズの場合
    case kFieldInitialized: {
      //mapdata_の初期化を行う
      result = PhaseInitialize(time);
      //初期化処理が終わったら、プレイヤー初期化フェーズに遷移する
      if (result) {
        field_phase_type_ = kPlayerInitialized;
        DEBUG_PRINT(プレイヤー初期化フェーズに遷移);
      }
      break;
    }

    //フェーズがプレイヤー初期化フェーズの場合
    case kPlayerInitialized: {
      field_phase_type_ = kProcessing;
      //DEBUG_PRINT(処理フェーズに遷移);
      break;
    }
    //フェーズが処理フェーズの場合
    case FieldPhaseType::kProcessing: {
      //処理フェーズが終わったら、終了フェーズに遷移する
      result = PhaseUpdate(time);
      if (result) {
        field_phase_type_ = kEnding;
        DEBUG_PRINT(Fieldの終了フェーズに遷移);
      }
      break;
    }
    //フェーズが終了フェーズの場合
    case FieldPhaseType::kEnding: {
      //終了フェーズが終わったら、終了済みフェーズに遷移する
      result = PhaseFinalize(time);
      if (result) {
        field_phase_type_ = kEnded;
        DEBUG_PRINT(Fieldの終了済みフェーズに遷移);
      }
      break;
    }
    //フェーズが終了済みの場合
    case FieldPhaseType::kEnded: {
      //DEBUG_PRINT(Fieldのフェーズが終了済み);
      break;
    }
    }
  }
}

/// <summary>
/// RenderFrame関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void Field::RenderFrame() {
  //DEBUG_PRINT(Fieldクラスの毎フレーム描画処理);

  DrawGraph(-difference_x_pos_, 0, battle_back_handle_, TRUE);

  // 処理中かポーズ中の状態であれば、描画する
  if (field_phase_type_ == kProcessing || field_phase_type_ == kStop) {
    for (int i = 0; i < kTotalRow; i++)
    {
      for (int j = 0; j < kTotalColumn; j++)
      {
        if (mapdata_[i][j] == kGround) {
          DrawGraph((j * kMapSize) - (difference_x_pos_), (i * kMapSize), ground_gr_handle_, TRUE);
        }
        else if (mapdata_[i][j] == kBox) {
          DrawGraph((j * kMapSize) - (difference_x_pos_), (i * kMapSize), box_handle_, TRUE);
        }
      }
    }
  }

}

/// <summary>
/// InitializeMapData関数の定義
/// </summary>
/// <param>なし</param>
/// <returns></returns>
void Field::InitializeMapData() {
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
          }
        }
      }
      DEBUG_PRINT(mapdata_を初期化した);
    }
  }
}

/// <summary>
/// SetBattleBackGrHandle関数の定義
/// </summary>
/// <param = "battle_back_handle">BattleLevelの背景のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetBattleBackGrHandle(int battle_back_handle) {
  battle_back_handle_ = battle_back_handle;
}

/// <summary>
/// GetBattleBackGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>BattleLevelの背景のグラフィックハンドル</returns>
int Field::GetBattleBackGrHandle() {
  return battle_back_handle_;
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool Field::PhaseInitialize(float time) {
  //ゲーム情報のインスタンスを取得する
  GameInfo* game_info = GameInfo::GetInstance();
  //マップのサイズを設定する
  game_info->SetMapSize(kTotalColumn * kMapSize, kTotalRow * kMapSize);

  InitializeMapData();

  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool Field::PhaseUpdate(float time) {
  return false;
}

/// <summary>
/// 終了処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool Field::PhaseFinalize(float time) {
  //mapdata_を初期化する
  for (int i = 0; i < kTotalRow; i++) {
    for (int j = 0; j < kTotalColumn; j++) {
      mapdata_[i][j] = { kNone };
    }
  }
  DEBUG_PRINT(mapdata_をクリアした);

  //累積時間をリセットする
  accumulation_time_ = 0.0f;

  return true;
}

/// <summary>
/// SetFieldPhaseType関数の定義
/// </summary>
/// <param = "type">方向の種類</param>
/// <returns>なし</returns>
void Field::SetFieldPhaseType(FieldPhaseType type) {
  field_phase_type_ = type;
}

/// <summary>
/// GetFieldPhaseType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
Field::FieldPhaseType Field::GetFieldPhaseType() {
  return field_phase_type_;
}

/// <summary>
/// mapdata_の指定位置の要素を変更する関数
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "maptype">マップの種類</param>
/// <returns>なし</returns>
void Field::SetMapType(int x, int y, MapType maptype) {
  mapdata_[y][x] = maptype;
}

/// <summary>
/// mapdata_の指定位置の要素を返す関数
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <returns>マップの種類</returns>
Field::MapType Field::GetMapType(int x, int y) {
  return mapdata_[y][x];
}

/// <summary>
/// GetBoxGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>箱のグラフィックハンドル</returns>
int Field::GetBoxGrHandle() {
  return box_handle_;
}

/// <summary>
/// SetBoxGrHandle関数の定義
/// </summary>
/// <param = "box_handle">箱のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetBoxGrHandle(int box_handle) {
  box_handle_ = box_handle;
}

/// <summary>
/// GetGroundGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>地面のグラフィックハンドル</returns>
int Field::GetGroundGrHandle() {
  return ground_gr_handle_;
}

/// <summary>
/// SetGroundGrHandle関数の定義
/// </summary>
/// <param = "ground_gr_handle">地面のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetGroundGrHandle(int ground_gr_handle) {
  ground_gr_handle_ = ground_gr_handle;
}

/// <summary>
/// SetFieldGameOver関数の宣言
/// </summary>
/// <param= "is_gameover">ゲームオーバーしたかの有無</param>
/// <returns></returns>
void Field::SetFieldGameOver(bool is_gameover) {
  is_gameover_ = is_gameover;
}

/// <summary>
/// GetConfettiHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Field::GetConfettiHandle(int element_num) {
  return confetti_handle_[element_num];
}

/// <summary>
/// SetConfettiHandle関数の定義
/// </summary>
/// <param = "confetti_handle">紙吹雪のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetConfettiHandle(std::array<int, kConfettiElementNumber> confetti_handle) {
  confetti_handle_ = confetti_handle;
}

/// <summary>
/// SetPlayerXPos関数の定義
/// </summary>
/// <param = "player_x_pos">プレイヤーのX位置</param>
/// <returns>なし</returns>
void Field::SetPlayerXPos(int player_x_pos) {
  player_x_pos_ = player_x_pos;
}

/// <summary>
/// SetDifferenceXpos関数の定義
/// </summary>
/// <param>フィールドの描画X位置を調整するための整数</param>
/// <returns>なし</returns>
void Field::SetDifferenceXpos(int difference_x_pos) {
  difference_x_pos_ = difference_x_pos;
}

/// <summary>
/// GetDifferenceXpos関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>フィールドの描画X位置を調整するための整数</returns>
int Field::GetDifferenceXpos() {
  return difference_x_pos_;
}

/// <summary>
/// SetStageNum関数
/// </summary>
/// <param = "stage_num">現在のステージ</param>
/// <returns>なし</returns>
void Field::SetStageNum(int stage_num) {
  stage_type_ = static_cast<StageType>(stage_num);
}