#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "DxLib.h"
#include "Game/Field/Pipe.h"
#include "Game/Level/BattleLevel.h"
#include "System/LogConsole/LogConsole.h"
#include "Game/GameInfo/GameInfo.h"
#include "Game/Fade/FadeManager.h"
#include "System/Math/Math.h"
#include "System/FileManager/FileManager.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {

  /// <summary>
  /// リセット時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 1.0f;

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
  //fade_カウントを定数kDeleteCharacterに格納する
  /// <summary>
  static const int kDeleteCharacter = 10;

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
Pipe::Pipe()
  : task_manager_(nullptr)
  , map_type_(kNone)
  , pipe_phase_type_(kPipeInitialized)
  , now_phase_(kPipeInitialized)
  , mapdata_{ kNone }
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , tube_rim_left_handle_(0)
  , tube_rim_middle_handle_(0)
  , tube_rim_right_handle_(0)
  , tube_left_handle_(0)
  , tube_middle_handle_(0)
  , tube_right_handle_(0)
  , index_(0)
  , player_x_pos_(0)
  , difference_x_pos_(0)
  , stage_type_(kFirstStage)
{
  DEBUG_PRINT(Pipeのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Pipe::Pipe(TaskId task_id, TaskManager* task_manager, int stage_num)
  : Task(task_id)
  , task_manager_(task_manager)
  , map_type_(kNone)
  , pipe_phase_type_(kPipeInitialized)
  , now_phase_(kPipeInitialized)
  , mapdata_{ kNone }
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , tube_rim_left_handle_(0)
  , tube_rim_middle_handle_(0)
  , tube_rim_right_handle_(0)
  , tube_left_handle_(0)
  , tube_middle_handle_(0)
  , tube_right_handle_(0)
  , index_(0)
  , player_x_pos_(0)
  , difference_x_pos_(0)
  , stage_type_(static_cast<StageType>(stage_num))
{
  DEBUG_PRINT(Pipeのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Pipe::~Pipe() {
  DEBUG_PRINT(Pipeのデストラクタ);
  //accumulation_time_ = 0.0f;
  //display_accumulation_time_ = 0.0f;
}

/// <summary>
/// UpdateFrame関数の定義
/// </summary>
/// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
/// <returns>なし</returns>
void Pipe::UpdateFrame(float time) {

  //DEBUG_PRINT(Pipeクラスの毎フレーム更新処理);
  if (now_phase_ != kStop) {

    bool result = false;

    switch (pipe_phase_type_) {

    //フェーズが初期化フェーズの場合
    case kPipeInitialized: {
      //mapdata_の初期化を行う
      result = PhaseInitialize(time);
      //初期化処理が終わったら、プレイヤー初期化フェーズに遷移する
      if (result) {
        pipe_phase_type_ = kPlayerInitialized;
        DEBUG_PRINT(プレイヤー初期化フェーズに遷移);
      }
      break;
    }

    //フェーズがプレイヤー初期化フェーズの場合
    case kPlayerInitialized: {
      pipe_phase_type_ = kProcessing;
      //DEBUG_PRINT(処理フェーズに遷移);
      break;
    }
    //フェーズが処理フェーズの場合
    case PipePhaseType::kProcessing: {
      //処理フェーズが終わったら、終了フェーズに遷移する
      result = PhaseUpdate(time);
      if (result) {
        pipe_phase_type_ = kEnding;
        DEBUG_PRINT(Pipeの終了フェーズに遷移);
      }
      break;
    }
    //フェーズが終了フェーズの場合
    case PipePhaseType::kEnding: {
      //終了フェーズが終わったら、終了済みフェーズに遷移する
      result = PhaseFinalize(time);
      if (result) {
        pipe_phase_type_ = kEnded;
        DEBUG_PRINT(Pipeの終了済みフェーズに遷移);
      }
      break;
    }
    //フェーズが終了済みの場合
    case PipePhaseType::kEnded: {
      //DEBUG_PRINT(Pipeのフェーズが終了済み);
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
void Pipe::RenderFrame() {
  //DEBUG_PRINT(Pipeクラスの毎フレーム描画処理);

  //ゲーム情報のインスタンスを取得する
  GameInfo* game_info = GameInfo::GetInstance();

  //ゲーム情報からマップの左上の座標を取得する
  int map_left_x = game_info->GetMapLeftX();
  int map_left_y = game_info->GetMapLeftY();

  // 処理中かポーズ中の状態であれば、描画する
  if (pipe_phase_type_ == kProcessing || pipe_phase_type_ == kStop) {
    for (int i = 0; i < kTotalRow; i++)
    {
      for (int j = 0; j < kTotalColumn; j++)
      {
        int gr_handles[static_cast<int>(kMapMax)] = { 0 , tube_rim_right_handle_, tube_rim_middle_handle_ , tube_rim_left_handle_, tube_right_handle_, tube_middle_handle_ , tube_left_handle_};

        for (int k = 0; k < static_cast<int>(kMapMax); k++) {
          if (mapdata_[i][j] == static_cast<Pipe::MapType>(k)) {
            DrawGraph((j * kMapSize) - (difference_x_pos_), (i * kMapSize), gr_handles[k], TRUE);
            break;
          }
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
void Pipe::InitializeMapData() {
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
          }
        }
      }
      DEBUG_PRINT(mapdata_を初期化した);
    }
  }
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool Pipe::PhaseInitialize(float time) {

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
bool Pipe::PhaseUpdate(float time) {
  return false;
}

/// <summary>
/// 終了処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool Pipe::PhaseFinalize(float time) {

  //mapdata_を初期化する
  for (int i = 0; i < kTotalRow; i++) {
    for (int j = 0; j < kTotalColumn; j++) {
      mapdata_[i][j] = { kNone };
    }
  }
  DEBUG_PRINT(mapdata_をクリアした);

  return true;
}

/// <summary>
/// SetPipePhaseType関数の定義
/// </summary>
/// <param = "type">方向の種類</param>
/// <returns>なし</returns>
void Pipe::SetPipePhaseType(PipePhaseType type) {
  pipe_phase_type_ = type;
}

/// <summary>
/// GetPipePhaseType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
Pipe::PipePhaseType Pipe::GetPipePhaseType() {
  return pipe_phase_type_;
}

/// <summary>
/// mapdata_の指定位置の要素を変更する関数
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "maptype">マップの種類</param>
/// <returns>なし</returns>
void Pipe::SetMapType(int x, int y, MapType maptype) {
  mapdata_[y][x] = maptype;
}

/// <summary>
/// mapdata_の指定位置の要素を返す関数
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <returns>マップの種類</returns>
Pipe::MapType Pipe::GetMapType(int x, int y) {
  return mapdata_[y][x];
}

/// <summary>
/// GetTubeRimLeftGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>土管の縁部分の左側の画像のグラフィックハンドル</returns>
int Pipe::GetTubeRimLeftGrHandle() {
  return tube_rim_left_handle_;
}

/// <summary>
/// SetTubeRimLeftGrHandle関数の定義
/// </summary>
/// <param = "tube_rim_left_handle">土管の縁部分の左側の画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Pipe::SetTubeRimLeftGrHandle(int tube_rim_left_handle) {
  tube_rim_left_handle_ = tube_rim_left_handle;
}

/// <summary>
/// GetTubeRimMiddleGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>土管の縁部分の真ん中の画像のグラフィックハンドル</returns>
int Pipe::GetTubeRimMiddleGrHandle() {
  return tube_rim_middle_handle_;
}

/// <summary>
/// SetTubeRimMiddleGrHandle関数の定義
/// </summary>
/// <param = "tube_rim_middle_handle">土管の縁部分の真ん中の画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Pipe::SetTubeRimMiddleGrHandle(int tube_rim_middle_handle) {
  tube_rim_middle_handle_ = tube_rim_middle_handle;
}

/// <summary>
/// SetTubeRimRightGrHandle関数の定義
/// </summary>
/// <param = "tube_rim_right_handle">土管の縁部分の右側の画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Pipe::SetTubeRimRightGrHandle(int tube_rim_right_handle) {
  tube_rim_right_handle_ = tube_rim_right_handle;
}

/// <summary>
/// GetTubeRimRightGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>土管の縁部分の右側の画像のグラフィックハンドル</returns>
int Pipe::GetTubeRimRightGrHandle() {
  return tube_rim_right_handle_;
}

/// <summary>
/// GetTubeLeftGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>土管の縁以外の左側の画像のグラフィックハンドル</returns>
int Pipe::GetTubeLeftGrHandle() {
  return tube_left_handle_;
}

/// <summary>
/// SetTubeLeftGrHandle関数の定義
/// </summary>
/// <param = "tube_left_handle">土管の縁以外の左側の画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Pipe::SetTubeLeftGrHandle(int tube_left_handle) {
  tube_left_handle_ = tube_left_handle;
}

/// <summary>
/// GetTubeMiddleGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>土管の縁以外の真ん中の画像のグラフィックハンドル</returns>
int Pipe::GetTubeMiddleGrHandle() {
  return tube_middle_handle_;
}

/// <summary>
/// SetTubeMiddleGrHandle関数の定義
/// </summary>
/// <param = "tube_middle_handle">土管の縁以外の真ん中の画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Pipe::SetTubeMiddleGrHandle(int tube_middle_handle) {
  tube_middle_handle_ = tube_middle_handle;
}

/// <summary>
/// SetTubeRightGrHandle関数の定義
/// </summary>
/// <param = "tube_right_handle">土管の縁以外の右側の画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Pipe::SetTubeRightGrHandle(int tube_right_handle) {
  tube_right_handle_ = tube_right_handle;
}

/// <summary>
/// GetTubeRightGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>土管の縁以外の右側の画像のグラフィックハンドル</returns>
int Pipe::GetTubeRightGrHandle() {
  return tube_right_handle_;
}

/// <summary>
/// SetPlayerXPos関数の定義
/// </summary>
/// <param = "player_x_pos">プレイヤーのX位置</param>
/// <returns>なし</returns>
void Pipe::SetPlayerXPos(int player_x_pos) {
  player_x_pos_ = player_x_pos;
}

/// <summary>
/// SetDifferenceXpos関数の定義
/// </summary>
/// <param>フィールドの描画X位置を調整するための整数</param>
/// <returns>なし</returns>
void Pipe::SetDifferenceXpos(int difference_x_pos) {
  difference_x_pos_ = difference_x_pos;
}

/// <summary>
/// GetDifferenceXpos関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>フィールドの描画X位置を調整するための整数</returns>
int Pipe::GetDifferenceXpos() {
  return difference_x_pos_;
}

/// <summary>
/// SetStageNum関数
/// </summary>
/// <param = "stage_num">現在のステージ</param>
/// <returns>なし</returns>
void Pipe::SetStageNum(int stage_num) {
  stage_type_ = static_cast<StageType>(stage_num);
}