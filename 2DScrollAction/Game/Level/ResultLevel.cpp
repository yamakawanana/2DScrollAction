#include <iostream>
#include "Game/Level/ResultLevel.h"
#include "Game/GameInfo/GameInfo.h"
#include "System/Input/InputManager.h"
#include <DxLib.h>
#include <string>
#include "System/FileManager/FileManager.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Audio/AudioManager.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// 累積時間のリセット時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 1.6f;

  //黒色の値を取得
  unsigned int Cr = GetColor(0, 0, 0);

  //白色の値を取得
  unsigned int WhiteCr = GetColor(255, 255, 255);

  /// <summary>
  /// 文字表示の画像を点滅させるタイミングを定数kFlashBubbleに格納する
  /// </summary>
  static const float kFlashBubble = 0.8f;

  /// <summary>
  /// ゲームオーバー時のリザルト画面の背景画像のファイル名を定数kGameOverResultPngに格納する
  /// </summary>
  static const char* kGameOverResultPng = "Assets/Images/Result/gameover_result.png";

  /// <summary>
  /// ゲームクリア時のリザルト画面の背景画像のファイル名を定数kGameClearResultPngに格納する
  /// </summary>
  static const char* kGameClearResultPng = "Assets/Images/Result/gameclear_result.png";

  /// <summary>
  /// 選択項目を囲む枠のファイル名を定数kSelectedButtonPngに格納する
  /// </summary>
  static const char* kSelectedButtonPng = "Assets/Images/Button/selected_button.png";

  /// <summary>
  /// 星の画像のファイル名を定数kStarPngに格納する
  /// </summary>
  static const char* kStarPng = "Assets/Images/Button/_22535725.png";

  /// <summary>
  /// フェード値を定数kFadeValueに格納する
  /// </summary>
  static const int kFadeValue = 250;

  /// <summary>
  /// アルファ値から引く値を定数kPlusAlphaに格納する
  /// </summary>
  static const int kPlusAlpha = 30;

  /// <summary>
  /// フェードインの待ち時間を定数kWaitTimeに格納する
  /// </summary>
  static const int kWaitTime = 30;

  // <summary>
  //画面の幅を定数kScreenSizeXに格納する
  /// <summary>
  static const int kScreenSizeX = 800;

  // <summary>
  //画面の高さを定数kScreenSizeYに格納する
  /// <summary>
  static const int kScreenSizeY = 600;

  /// <summary>
  /// 設定を保存するファイル名を定数kSettingCSVに格納する
  /// </summary>
  static const char* kSettingCSV = "Assets/CsvFiles/setting.csv";

  /// <summary>
  /// 音量の初期値を定数kDefaultVolumeに格納する
  /// </summary>
  static const int kDefaultVolume = 80;

  /// <summary>
  /// 「%5d」を指定する文字列を定数kPercentFiveDに格納する
  /// </summary>
  static const char* kPercentFiveD = "%5d";

  /// <summary>
  //選択されたボタンを囲む枠のX位置を定数kSelectedButtonXcoordinateに格納する
  /// <summary>
  static const int kSelectedButtonXcoordinate = 102;

  /// <summary>
  //選択されたボタンを囲む枠の2つ目のX位置を定数kSecondSelectedButtonXcoordinateに格納する
  /// <summary>
  static const int kSecondSelectedButtonXcoordinate = 374;

  /// <summary>
  //選択されたボタンを囲む枠のY位置を定数kSelectedButtonYcoordinateに格納する
  /// <summary>
  static const int kSelectedButtonYcoordinate = 464;

  /// <summary>
  /// フェードイン時間
  /// </summary>
  const float kFadeInTime = 0.1f;

  /// <summary>
  //描画角度を定数の配列kPiに格納する
  /// <summary>
  static const double kAngles[] = { 0.0, (3.141592654 / 4),  (3.141592654 / 2), (3 * (3.141592654) / 4), (3.141592654 / 1), (5 * (3.141592654) / 4), (3 * (3.141592654) / 2), (7 * (3.141592654) / 4) };

  /// <summary>
  /// kAnglesの要素数を定数kAnglesElementに格納する
  /// </summary>
  static const int kAnglesElement = 8;

  /// <summary>
  /// 角度を変えるまでの待ち時間を定数kWaitTimeに格納する
  /// </summary>
  static const float kWaitTimes[] = { 0.0f, 0.2f, 0.4f, 0.6f, 0.8f, 1.0f, 1.2f, 1.4f, 1.6f };

  /// <summary>
  /// 「リトライ」を指定する文字列を定数kGameStartStringに格納する
  /// </summary>
  static const char* kGameStartString = "リトライ";

  /// <summary>
  /// 「タイトルへ」を指定する文字列を定数kGoTitleStringに格納する
  /// </summary>
  static const char* kGoTitleString = "タイトルへ";

  /// <summary>
  /// フォントを指定する文字列を定数kFontに格納する
  /// </summary>
  static const char* kFont = "メイリオ";

  /// <summary>
  /// フォントサイズの定数kFontSize
  /// </summary>
  static const int kFontSize = 32;

  /// <summary>
  //左側の文字の表示X位置を定数kXcoordinateに格納する
  /// <summary>
  static const int kXcoordinate = 180;

  /// <summary>
  //左側の文字の表示Y位置を定数kYcoordinateに格納する
  /// <summary>
  static const int kYcoordinate = 540;

  /// <summary>
  //右側の文字の表示X位置を定数kSecondXcoordinateに格納する
  /// <summary>
  static const int kSecondXcoordinate = 520;

  /// <summary>
  //右側の文字の表示Y位置を定数kSecondYcoordinateに格納する
  /// <summary>
  static const int kSecondYcoordinate = 540;

  /// <summary>
  //ゲームオーバー時の文字の表示Y位置を定数kGameOverYcoordinateに格納する
  /// <summary>
  static const int kGameOverYcoordinate = 450;

  /// <summary>
  //ゲームオーバー時の星の表示Y位置を定数kGameOverStarYcoordinateに格納する
  /// <summary>
  static const int kGameOverStarYcoordinate = 465;

  /// <summary>
  //回る物体の描画X座標を定数kStarXcoordinatesに格納する
  /// <summary>
  static const int kStarXcoordinates[] = { 136, 482 };

  /// <summary>
  //回る物体の描画Y座標を定数kStarYcoordinatesに格納する
  /// <summary>
  static const int kStarYcoordinates[] = { 555, 555 };
}

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ResultLevel::ResultLevel()
  : is_finish_(false)
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , end_type_(kUnloadTask)
  , result_handle_(0)
  , selected_button_handle_(0)
  , enter_handle_(0)
  , cursor_handle_(0)
  , sound_volume_(kDefaultVolume)
  , menu_type_(kRetry)
  , select_index_(0)
  , fade_(0)
  , is_enter_(false)
  , star_gr_handle_(0)
  , angle_type_(kAngle0)
  , game_clear_(false)
{
  DEBUG_PRINT(ResultLevelのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ResultLevel::ResultLevel(TaskId task_id, TaskManager* task_manager)
  : Level(task_id, task_manager)
  , is_finish_(false)
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , end_type_(kUnloadTask)
  , result_handle_(0)
  , selected_button_handle_(0)
  , enter_handle_(0)
  , cursor_handle_(0)
  , sound_volume_(kDefaultVolume)
  , menu_type_(kRetry)
  , select_index_(0)
  , fade_(0)
  , is_enter_(false)
  , star_gr_handle_(0)
  , angle_type_(kAngle0)
  , game_clear_(false)
{
  DEBUG_PRINT(ResultLevelのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ResultLevel::~ResultLevel() {
  DEBUG_PRINT(ResultLevelのデストラクタ);
  //accumulation_time_ = 0.0f;
  //display_accumulation_time_ = 0.0f;
}

/// <summary>
/// 決定ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void ResultLevel::OnPushDecide() {
  DEBUG_PRINT(決定ボタンが押された時のイベント);
  is_finish_ = true;
}

/// <summary>
/// 終了ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void ResultLevel::OnPushFinish() {
  //DEBUG_PRINT(終了ボタンが押された時のイベント);
  //SetEndButton();
  //is_finish_ = true;
}

/// <summary>
/// スペースボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void ResultLevel::OnPushPause() {
  DEBUG_PRINT(スペースボタンが押された時のイベント);
}

/// <summary>
/// BackSpaceボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void ResultLevel::OnPushBackSpace() {
  DEBUG_PRINT(BackSpaceボタンが押された時のイベント);
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool ResultLevel::InitializeUpdate(float time) {
  DEBUG_PRINT(ResultLevelの初期化処理);

  //ゲーム情報を取得する
  GameInfo* game_info = GameInfo::GetInstance();
  game_clear_ = game_info->IsGameClear();

  //オーディオマネージャーを生成する
  audio_manager_ = new AudioManager();

  //効果音をロードする
  audio_manager_->LoadSe(AudioManager::SeKind::kCursorMp3);
  audio_manager_->LoadSe(AudioManager::SeKind::kEnterMp3);

  //ゲームクリアの場合とゲームオーバーの場合でロードするデータを分ける
  int result_handle;
  if (game_clear_) {
    //リザルト画面の背景をロードする
    result_handle = LoadGraph(kGameClearResultPng);
    //BGMのデータをロードする
    audio_manager_->LoadBgm(AudioManager::BgmKind::kGameClearBgmMp3);
    //BGMを再生する
    audio_manager_->PlayBgm(AudioManager::BgmKind::kGameClearBgmMp3);
  }
  else {
    //リザルト画面の背景をロードする
    result_handle = LoadGraph(kGameOverResultPng);
    //BGMのデータをロードする
    audio_manager_->LoadBgm(AudioManager::BgmKind::kGameOverBgmMp3);
    //BGMを再生する
    audio_manager_->PlayBgm(AudioManager::BgmKind::kGameOverBgmMp3);
  }

  //選択されたボタンを囲む枠の画像データをロードする
  int selected_handle = LoadGraph(kSelectedButtonPng);
  int star_handle = LoadGraph(kStarPng);

  //グラフィックハンドルを設定する
  SetResultGrHandle(result_handle);
  SetSelectedButtonGrHandle(selected_handle);
  SetStarGrHandle(star_handle);

  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool ResultLevel::ProcessingUpdate(float time) {
  //DEBUG_PRINT(ResultLevelの毎フレーム更新処理のフェーズ処理);

  //入力管理を取得
  InputManager* input_manager = InputManager::GetInstance();

  accumulation_time_ = accumulation_time_ + time;
  if (accumulation_time_ >= kLimitTime) {
    accumulation_time_ = 0.0f;
  }

  //累積時間によって角度を変更する
  for (int i = 0; i < (kAnglesElement + 1); i++) {
    if (accumulation_time_ >= kWaitTimes[i] && accumulation_time_ < kWaitTimes[i + 1]) {
      angle_type_ = static_cast<AngleType>((i));
    }
  }

  //Enterが押された後の場合
  if (is_enter_ == true) {
    display_accumulation_time_ = display_accumulation_time_ + time;
    if (display_accumulation_time_ >= kFadeInTime) {
      fade_++;
      display_accumulation_time_ = 0;
    }
  }
  if (fade_ >= (kFadeValue / kPlusAlpha)) {
    if (select_index_ == static_cast<int>(MenuOption::kBackTitle)) {
      SetBackTitle();
    }
    OnPushDecide();
  }

  if (GetWindowUserCloseFlag()) {
    SetEndButton();
    is_finish_ = true;
    DEBUG_PRINT(×ボタン);
  }

  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kRight) && is_enter_ == false) {
    if (select_index_ == static_cast<int>(MenuOption::kRetry)) {
      audio_manager_->PlaySe(AudioManager::SeKind::kCursorMp3);
      select_index_ = static_cast<int>(MenuOption::kBackTitle);
    }
  }
  else if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kLeft) && is_enter_ == false) {
    if (select_index_ == static_cast<int>(MenuOption::kBackTitle)) {
      audio_manager_->PlaySe(AudioManager::SeKind::kCursorMp3);
      select_index_ = static_cast<int>(MenuOption::kRetry);
    }
  }

  //Enterが押されたら、決定ボタンが押された時のイベントを呼び出す
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kDecide)) {
    is_enter_ = true;
    audio_manager_->PlaySe(AudioManager::SeKind::kEnterMp3);
  }

  //スペースボタンが押されたら、スペースボタンが押された時のイベントを呼び出す
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kSpace)) {
    OnPushPause();
  }

  //描画処理を実行する
  ProcessingRender();

  return is_finish_;
}

/// <summary>
/// 毎フレームの描画処理
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ResultLevel::ProcessingRender() {
  //DEBUG_PRINT(ResultLevelの描画処理);

  //リザルト画面を表示する
  DrawGraph(0, 0, result_handle_, TRUE);

  SetFontSize(kFontSize);

  for (int i = 0; i < static_cast<int>((MenuOption::kBackTitle)+1); ++i) {
    if (i == select_index_) {
      for (int j = 0; j < kAnglesElement; j++) {
        if (angle_type_ == static_cast<AngleType>(j)) {
          if (game_clear_) {
            //選択中の項目の横に回転する物体を描画
            DrawRotaGraph(kStarXcoordinates[i], kStarYcoordinates[i], 1.0, kAngles[j], star_gr_handle_, TRUE);
          }
          else {
            //選択中の項目の横に回転する物体を描画
            DrawRotaGraph(kStarXcoordinates[i], kGameOverStarYcoordinate, 1.0, kAngles[j], star_gr_handle_, TRUE);
          }
        }
      }
    }
  }

  //「ゲーム開始」と「タイトルへ」の文字を描画する
  if (game_clear_) {
    DrawString(kXcoordinate, kYcoordinate, kGameStartString, Cr);
    DrawString(kSecondXcoordinate, kSecondYcoordinate, kGoTitleString, Cr);
  }
  else {
    DrawString(kXcoordinate, kGameOverYcoordinate, kGameStartString, WhiteCr);
    DrawString(kSecondXcoordinate, kGameOverYcoordinate, kGoTitleString, WhiteCr);
  }


  //画面遷移時の黒いフェードイン
  if (is_enter_ == true) {
    //フェードマネージャーのインスタンスを取得
    FadeManager* fade_manager = FadeManager::GetInstance();
    if (fade_ <= (kFadeValue / kPlusAlpha)) {
      fade_manager->FadeIn(0, 0, kScreenSizeX, kScreenSizeY, fade_, kPlusAlpha);
    }
  }
}

/// <summary>
/// 終了処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool ResultLevel::PhaseFinalize(float time) {
  DEBUG_PRINT(ResultLevelの終了処理);

  //描画をクリアする
  ClearDrawScreen();

  //取得したグラフィックハンドルを使い、リソースを破棄する
  DeleteGraph(GetResultGrHandle());
  DeleteGraph(GetSelectedButtonGrHandle());
  DeleteGraph(GetStarGrHandle());

  //オーディオマネージャーの後処理と破棄
  audio_manager_->FinAudioManager();
  delete audio_manager_;
  audio_manager_ = nullptr;

  return true;
}

/// <summary>
/// SetResultGrHandle関数の定義
/// </summary>
/// <param = "result_handle">Resultのグラフィックハンドル</param>
/// <returns>なし</returns>
void ResultLevel::SetResultGrHandle(int result_handle) {
  result_handle_ = result_handle;
}

/// <summary>
/// GetResultGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Resultのグラフィックハンドル</returns>
int ResultLevel::GetResultGrHandle() {
  return result_handle_;
}

/// <summary>
/// SetSelectedButtonGrHandle関数の定義
/// </summary>
/// <param = "selected_button_handle">選択されたボタンを囲む枠のグラフィックハンドル</param>
/// <returns>なし</returns>
void ResultLevel::SetSelectedButtonGrHandle(int selected_button_handle) {
  selected_button_handle_ = selected_button_handle;
}

/// <summary>
/// GetSelectedButtonGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>選択されたボタンを囲む枠のグラフィックハンドル</returns>
int ResultLevel::GetSelectedButtonGrHandle() {
  return selected_button_handle_;
}

/// <summary>
/// SetStarGrHandle関数の定義
/// </summary>
/// <param = "star_gr_handle">星のグラフィックハンドル</param>
/// <returns>なし</returns>
void ResultLevel::SetStarGrHandle(int star_gr_handle) {
  star_gr_handle_ = star_gr_handle;
}

/// <summary>
/// GetStarGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>星のグラフィックハンドル</returns>
int ResultLevel::GetStarGrHandle() {
  return star_gr_handle_;
}