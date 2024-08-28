#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include "Game/Level/StageSelectLevel.h"
#include "Game/GameInfo/GameInfo.h"
#include "System/Input/InputManager.h"
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

  /// <summary>
  //黒色の値を取得
  /// <summary>
  unsigned int Cr = GetColor(0, 0, 0);

  /// <summary>
  //白色の値を取得
  /// </summary>
  unsigned int WhiteCr = GetColor(255, 255, 255);

  /// <summary>
  //赤色の値を取得
  /// <summary>
  unsigned int RedCr = GetColor(255, 30, 30);

  /// <summary>
  //ステージ名の描画X座標を定数kXcoordinateに格納する
  /// <summary>
  static const int kXcoordinate = 150;

  /// <summary>
  //ステージ1の描画Y座標を定数kYcoordinateOneに格納する
  /// <summary>
  static const int kYcoordinateOne = 210;

  /// <summary>
  //ステージ2の描画Y座標を定数kYcoordinateTwoに格納する
  /// <summary>
  static const int kYcoordinateTwo = 290;

  /// <summary>
  //ステージ3の描画Y座標を定数kYcoordinateThreeに格納する
  /// <summary>
  static const int kYcoordinateThree = 370;

  /// <summary>
  //「タイトルへ」の描画X座標を定数kXcoordinateGoTitleに格納する
  /// <summary>
  static const int kXcoordinateGoTitle = 330;

  /// <summary>
  //「タイトルへ」の描画Y座標を定数kYcoordinateGoTitleに格納する
  /// <summary>
  static const int kYcoordinateGoTitle = 450;

  /// <summary>
  //回る物体の描画X座標を定数kPlayerXcoordinatesに格納する
  /// <summary>
  static const int kPlayerXcoordinates[] = { 120, 120, 120, 300 };

  /// <summary>
  //回る物体の描画Y座標を定数kPlayerYcoordinatesに格納する
  /// <summary>
  static const int kPlayerYcoordinates[] = { 224, 304, 384, 464 };

  /// <summary>
  //選択項目の描画Y座標の間隔を定数kYcoordinateSpaceに格納する
  /// <summary>
  static const int kYcoordinateSpace = 70;

  /// <summary>
  ///画像を点滅させるタイミングを定数kFlashBubbleに格納する
  /// </summary>
  static const float kFlashBubble = 0.8f;

  /// <summary>
  /// フェード値を定数kFadeValueに格納する
  /// </summary>
  static const int kFadeValue = 250;

  /// <summary>
  /// アルファ値から引く値を定数kPlusAlphaに格納する
  /// </summary>
  static const int kPlusAlpha = 25;

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
  /// ステージ選択画面の背景画像のファイル名を定数kStageSelectPngに格納する
  /// </summary>
  static const char* kStageSelectPng = "Assets/Images/StageSelect/stage_select.png";

  /// <summary>
  /// 星の画像のファイル名を定数kStarPngに格納する
  /// </summary>
  static const char* kStarPng = "Assets/Images/Button/orange_star.png";

  /// <summary>
  /// ステージ1の画像のファイル名を定数kStageOnePngに格納する
  /// </summary>
  static const char* kStageOnePng = "Assets/Images/StageSelect/stage1.png";

  /// <summary>
  /// ステージ2の画像のファイル名を定数kStageTwoPngに格納する
  /// </summary>
  static const char* kStageTwoPng = "Assets/Images/StageSelect/stage2.png";

  /// <summary>
  /// ステージ3の画像のファイル名を定数kStageThreePngに格納する
  /// </summary>
  static const char* kStageThreePng = "Assets/Images/StageSelect/stage3.png";

  /// <summary>
  /// 鍵の画像のファイル名を定数kLockPngに格納する
  /// </summary>
  static const char* kLockPng = "Assets/Images/StageSelect/lock.png";

  /// <summary>
  /// フォントを指定する文字列を定数kFontに格納する
  /// </summary>
  static const char* kFont = "メイリオ";

  /// <summary>
  /// 「ステージ選択」を指定する文字列を定数kStageSelectStringに格納する
  /// </summary>
  static const char* kStageSelectString = "ステージ選択";

  /// <summary>
  /// 「ステージ1」を指定する文字列を定数kStageOneStringに格納する
  /// </summary>
  static const char* kStageOneString = "ステージ1";

  /// <summary>
  /// 「ステージ2」を指定する文字列を定数kStageTwoStringに格納する
  /// </summary>
  static const char* kStageTwoString = "ステージ2";

  /// <summary>
  /// 「ステージ3」を指定する文字列を定数kStageThreeStringに格納する
  /// </summary>
  static const char* kStageThreeString = "ステージ3";

  /// <summary>
  /// 「タイトルへ」を指定する文字列を定数kGoTitleStringに格納する
  /// </summary>
  static const char* kGoTitleString = "タイトルへ";

  /// <summary>
  /// 「%s」を指定する文字列を定数kPercentSに格納する
  /// </summary>
  static const char* kPercentS = "%s";

  /// <summary>
  /// フォントサイズの定数kFontSize
  /// </summary>
  static const int kFontSize = 30;

  /// <summary>
  /// フォントの太さの定数kFontThickness
  /// </summary>
  static const int kFontThickness = 10;

  /// <summary>
  /// 設定を保存するファイル名を定数kSettingCSVに格納する
  /// </summary>
  static const char* kSettingCSV = "Assets/CsvFiles/setting.csv";

  /// <summary>
  /// 選択可能なステージを保存するファイル名を定数kSelectableStageCSVに格納する
  /// </summary>
  static const char* kSelectableStageCSV = "Assets/CsvFiles/selectable_stages.csv";

  /// <summary>
  /// ステージ数を保存するファイル名を定数kStageNumCSVに格納する
  /// </summary>
  static const char* kStageNumCSV = "Assets/CsvFiles/stage_num.csv";

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
  /// 整数2を定数kTwoに格納する
  /// </summary>
  static const int kTwo = 2;

  /// <summary>
  //ステージ画像の描画X座標を定数kStageXに格納する
  /// <summary>
  static const int kStageX = 340;

  /// <summary>
  //ステージ画像の描画Y座標を定数kStageYに格納する
  /// <summary>
  static const int kStageY = 180;

  /// <summary>
  //黒い透過したBoxの左上の描画X座標を定数kLeftUpXに格納する
  /// <summary>
  static const int kLeftUpX = 140;

  /// <summary>
  //黒い透過したBoxの左上の描画Y座標を定数kLeftUpYに格納する
  /// <summary>
  static const int kLeftUpY = 360;

  /// <summary>
  //黒い透過したBoxの右下の描画X座標を定数kRightDownXに格納する
  /// <summary>
  static const int kRightDownX = 300;

  /// <summary>
  //黒い透過したBoxの右下の描画Y座標を定数kRightDownYに格納する
  /// <summary>
  static const int kRightDownY = 410;

  /// <summary>
  //鍵の画像の描画X座標を定数kLockXに格納する
  /// <summary>
  static const int kLockX = 195;

  /// <summary>
  //鍵の画像の描画Y座標を定数kLockYに格納する
  /// <summary>
  static const int kLockY = 360;

  /// <summary>
  //白いBoxの左上の描画X座標を定数kWhiteBoxLeftUpXに格納する
  /// <summary>
  static const int kWhiteBoxLeftUpX = 205;

  /// <summary>
  //白いBoxの左上の描画Y座標を定数kWhiteBoxLeftUpYに格納する
  /// <summary>
  static const int kWhiteBoxLeftUpY = 370;

  /// <summary>
  //白いBoxの右下の描画X座標を定数kWhiteBoxRightDownXに格納する
  /// <summary>
  static const int kWhiteBoxRightDownX = 240;

  /// <summary>
  //白いBoxの右下の描画Y座標を定数kWhiteBoxRightDownYに格納する
  /// <summary>
  static const int kWhiteBoxRightDownY = 400;
}

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
StageSelectLevel::StageSelectLevel()
  : is_finish_(false)
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , end_type_(kUnloadTask)
  , stage_handle_(0)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , bgm_handle_(0)
  , enter_handle_(0)
  , cursor_handle_(0)
  , menu_type_(kStageOne)
  , select_index_(0)
  , fade_(0)
  , is_enter_(false)
  , star_gr_handle_(0)
  , angle_type_(kAngle0)
  , stage_one_handle_(0)
  , stage_two_handle_(0)
  , stage_three_handle_(0)
  , lock_handle_(0)
{
  DEBUG_PRINT(StageSelectLevelのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
StageSelectLevel::StageSelectLevel(TaskId task_id, TaskManager* task_manager)
  : Level(task_id, task_manager)
  , is_finish_(false)
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , end_type_(kUnloadTask)
  , stage_handle_(0)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , bgm_handle_(0)
  , enter_handle_(0)
  , cursor_handle_(0)
  , menu_type_(kStageOne)
  , select_index_(0)
  , fade_(0)
  , is_enter_(false)
  , star_gr_handle_(0)
  , angle_type_(kAngle0)
  , stage_one_handle_(0)
  , stage_two_handle_(0)
  , stage_three_handle_(0)
  , lock_handle_(0)
{
  DEBUG_PRINT(StageSelectLevelのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
StageSelectLevel::~StageSelectLevel() {
  DEBUG_PRINT(StageSelectLevelのデストラクタ);
  //accumulation_time_ = 0.0f;
  //display_accumulation_time_ = 0.0f;
}

/// <summary>
/// 決定ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void StageSelectLevel::OnPushDecide() {
  DEBUG_PRINT(決定ボタンが押された時のイベント);
  is_finish_ = true;
}

/// <summary>
/// 終了ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void StageSelectLevel::OnPushFinish() {
  //DEBUG_PRINT(終了ボタンが押された時のイベント);
  //SetEndButton();
  //is_finish_ = true;
}

/// <summary>
/// スペースボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void StageSelectLevel::OnPushPause() {
  DEBUG_PRINT(スペースボタンが押された時のイベント);
}

/// <summary>
/// BackSpaceボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void StageSelectLevel::OnPushBackSpace() {
  DEBUG_PRINT(BackSpaceボタンが押された時のイベント);
}

/// <summary>
/// SetStageGrHandle関数の定義
/// </summary>
/// <param = "stage_handle">ステージ選択背景のグラフィックハンドル</param>
/// <returns>なし</returns>
void StageSelectLevel::SetStageGrHandle(int stage_handle) {
  stage_handle_ = stage_handle;
}

/// <summary>
/// GetStageGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ステージ選択背景のグラフィックハンドル</returns>
int StageSelectLevel::GetStageGrHandle() {
  return stage_handle_;
}

/// <summary>
/// SetWidth関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void StageSelectLevel::SetWidth(int size_x) {
  width_ = size_x;
}

/// <summary>
/// GetWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int StageSelectLevel::GetWidth() {
  return width_;
}

/// <summary>
/// SetHeight関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void StageSelectLevel::SetHeight(int size_y) {
  height_ = size_y;
}

/// <summary>
/// GetHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さ</returns>
int StageSelectLevel::GetHeight() {
  return height_;
}

/// <summary>
/// SetHalfWidth関数の定義
/// </summary>
/// <param>画像の幅の半分</param>
/// <returns>なし</returns>
void StageSelectLevel::SetHalfWidth(float size_half_x) {
  half_width_ = size_half_x;
}

/// <summary>
/// GetHalfWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅の半分</returns>
float StageSelectLevel::GetHalfWidth() {
  return half_width_;
}

/// <summary>
/// SetHalfHeight関数の定義
/// </summary>
/// <param>画像の高さの半分</param>
/// <returns>なし</returns>
void StageSelectLevel::SetHalfHeight(float size_half_y) {
  half_height_ = size_half_y;
}

/// <summary>
/// GetHalfHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さの半分</returns>
float StageSelectLevel::GetHalfHeight() {
  return half_height_;
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool StageSelectLevel::InitializeUpdate(float time) {
  DEBUG_PRINT(StageSelectLevelの初期化処理);

  //画像データをロードする
  int stage_handle = LoadGraph(kStageSelectPng);
  int star_handle = LoadGraph(kStarPng);
  int stage_one_handle = LoadGraph(kStageOnePng);
  int stage_two_handle = LoadGraph(kStageTwoPng);
  int stage_three_handle = LoadGraph(kStageThreePng);
  int lock_handle = LoadGraph(kLockPng);

  //オーディオマネージャーを生成する
  audio_manager_ = new AudioManager();

  //効果音をロードする
  audio_manager_->LoadSe(AudioManager::SeKind::kCursorMp3);
  audio_manager_->LoadSe(AudioManager::SeKind::kEnterMp3);
  //BGMをロードする
  audio_manager_->LoadBgm(AudioManager::BgmKind::kStageSelectBgmMp3);

  //グラフィックハンドルを設定する
  SetStageGrHandle(stage_handle);
  SetStarGrHandle(star_handle);
  SetStageOneGrHandle(stage_one_handle);
  SetStageTwoGrHandle(stage_two_handle);
  SetStageThreeGrHandle(stage_three_handle);
  SetLockGrHandle(lock_handle);

  //BGMを再生する
  audio_manager_->PlayBgm(AudioManager::BgmKind::kStageSelectBgmMp3);

  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool StageSelectLevel::ProcessingUpdate(float time) {
  //DEBUG_PRINT(StageSelectLevelの毎フレーム更新処理のフェーズ処理);

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
      //DEBUG_PRINT_VAR(i);
      //DEBUG_PRINT_VAR(angle_type_);
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

    //ファイルマネージャーのインスタンスを取得
    FileManager* file_manager = FileManager::GetInstance();
    //ステージ数を一時的に格納するvector
    std::vector<int> stage_num;

    // 選択されたメニューに応じて画面遷移する
    if (static_cast<MenuOption>(select_index_) == kStageOne) {
      stage_num.push_back(0);
      OnPushDecide();
    }
    else if (static_cast<MenuOption>(select_index_) == kStageTwo) {
      stage_num.push_back(1);
      OnPushDecide();
    }
    else if (static_cast<MenuOption>(select_index_) == kStageThree) {
      stage_num.push_back(kTwo);
      OnPushDecide();
    }
    else if (static_cast<MenuOption>(select_index_) == kGoTitle) {
      SetBackTitle();
      OnPushDecide();
    }
    file_manager->WriteDataToFile(kStageNumCSV, stage_num);
  }

  //DEBUG_PRINT_VAR(accumulation_time_);

  if (GetWindowUserCloseFlag()) {
    SetEndButton();
    is_finish_ = true;
  }

  //スペースボタンが押されたら、スペースボタンが押された時のイベントを呼び出す
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kSpace)) {
    OnPushPause();
  }

  //ファイルマネージャーのインスタンスを取得
  FileManager* file_manager = FileManager::GetInstance();

  //選択可能なステージのデータを読み込む
  std::vector<int> selectable_stages = file_manager->ReadDataFromFile(kSelectableStageCSV);

  // 矢印キーで選択を変更する
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kUp) && is_enter_ == false) {
    audio_manager_->PlaySe(AudioManager::SeKind::kCursorMp3);
    //ステージ2までしかクリアしていない場合、ステージ3は選択できないので、ステージ3にカーソルを移動させない
    if ((selectable_stages.at(0) == 1) && (static_cast<MenuOption>(select_index_) == kGoTitle)) {
      select_index_ = static_cast<int>(MenuOption::kStageTwo);
    }
    else {
      select_index_ = (select_index_ - 1 + static_cast<int>((MenuOption::kGoTitle)+1)) % static_cast<int>((MenuOption::kGoTitle)+1);
    }
  }
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kDown) && is_enter_ == false) {
    audio_manager_->PlaySe(AudioManager::SeKind::kCursorMp3);
    //ステージ2までしかクリアしていない場合、ステージ3は選択できないので、ステージ3にカーソルを移動させない
    if ((selectable_stages.at(0) == 1) && (static_cast<MenuOption>(select_index_) == kStageTwo)) {
      select_index_ = static_cast<int>(MenuOption::kGoTitle);
    }
    else {
      select_index_ = (select_index_ + 1) % static_cast<int>((MenuOption::kGoTitle)+1);
    }
  }

  // エンターキーが押された場合
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kDecide) && (static_cast<MenuOption>(select_index_) == kStageOne || static_cast<MenuOption>(select_index_) == kStageTwo || static_cast<MenuOption>(select_index_) == kStageThree || static_cast<MenuOption>(select_index_) == kGoTitle)) {
    is_enter_ = true;
    audio_manager_->PlaySe(AudioManager::SeKind::kEnterMp3);
  }

  //描画処理を実行する
  ProcessingRender();

  //各ボタンを押された時のイベントでis_finish_がtrueになった時、処理終了する
  return is_finish_;
}

/// <summary>
/// 毎フレームの描画処理
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void StageSelectLevel::ProcessingRender() {
  //DEBUG_PRINT(StageSelectLevelの描画処理);

  //背景画像を表示する
  DrawGraph(0, 0, stage_handle_, TRUE);

  ChangeFont(kFont);
  SetFontSize(kFontSize);

  DrawString(kXcoordinate, kYcoordinateOne, kStageOneString, Cr);
  DrawString(kXcoordinate, kYcoordinateTwo, kStageTwoString, Cr);
  DrawString(kXcoordinate, kYcoordinateThree, kStageThreeString, Cr);
  DrawString(kXcoordinateGoTitle, kYcoordinateGoTitle, kGoTitleString, Cr);

  //ファイルマネージャーのインスタンスを取得
  FileManager* file_manager = FileManager::GetInstance();

  //選択可能なステージのデータを読み込む
  std::vector<int> selectable_stages = file_manager->ReadDataFromFile(kSelectableStageCSV);

  if (selectable_stages.at(0) == 1) {
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, kFadeValue / kTwo);
    DrawBox(kLeftUpX, kLeftUpY, kRightDownX, kRightDownY, Cr, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawBox(kWhiteBoxLeftUpX, kWhiteBoxLeftUpY, kWhiteBoxRightDownX, kWhiteBoxRightDownY, WhiteCr, true);
    DrawGraph(kLockX, kLockY, lock_handle_, TRUE);
  }

  // 選択されたメニューに応じてステージの画像を描画する
  if (static_cast<MenuOption>(select_index_) == kStageOne) {
    DrawGraph(kStageX, kStageY, stage_one_handle_, TRUE);
  }
  else if (static_cast<MenuOption>(select_index_) == kStageTwo) {
    DrawGraph(kStageX, kStageY, stage_two_handle_, TRUE);
  }
  else if (static_cast<MenuOption>(select_index_) == kStageThree) {
    DrawGraph(kStageX, kStageY, stage_three_handle_, TRUE);
  }

  for (int i = 0; i < static_cast<int>((MenuOption::kGoTitle)+1); ++i) {
    if (i == select_index_) {
      for (int j = 0; j < kAnglesElement; j++) {
        if (angle_type_ == static_cast<AngleType>(j)) {
          //選択中の項目の横に回転する物体を描画
          DrawRotaGraph(kPlayerXcoordinates[i], kPlayerYcoordinates[i], 1.0, kAngles[j], star_gr_handle_, TRUE);
        }
      }
    }
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
bool StageSelectLevel::PhaseFinalize(float time) {
  DEBUG_PRINT(StageSelectLevelの終了処理);
  //描画をクリアする
  ClearDrawScreen();

  //取得したグラフィックハンドルを使い、リソースを破棄する
  DeleteGraph(GetStageGrHandle());
  DeleteGraph(GetStarGrHandle());
  DeleteGraph(GetStageOneGrHandle());
  DeleteGraph(GetStageTwoGrHandle());
  DeleteGraph(GetStageThreeGrHandle());
  DeleteGraph(GetLockGrHandle());

  //オーディオマネージャーの後処理と破棄
  audio_manager_->FinAudioManager();
  delete audio_manager_;
  audio_manager_ = nullptr;

  return true;
}

/// <summary>
/// SetStarGrHandle関数の定義
/// </summary>
/// <param = "star_gr_handle">星のグラフィックハンドル</param>
/// <returns>なし</returns>
void StageSelectLevel::SetStarGrHandle(int star_gr_handle) {
  star_gr_handle_ = star_gr_handle;
}

/// <summary>
/// GetStarGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>星のグラフィックハンドル</returns>
int StageSelectLevel::GetStarGrHandle() {
  return star_gr_handle_;
}

/// <summary>
/// SetStageOneGrHandle関数の定義
/// </summary>
/// <param = "stage_one_handle">ステージ1の画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void StageSelectLevel::SetStageOneGrHandle(int stage_one_handle) {
  stage_one_handle_ = stage_one_handle;
}

/// <summary>
/// GetStageOneGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ステージ1の画像のグラフィックハンドル</returns>
int StageSelectLevel::GetStageOneGrHandle() {
  return stage_one_handle_;
}

/// <summary>
/// SetStageTwoGrHandle関数の定義
/// </summary>
/// <param = "stage_two_handle">ステージ2の画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void StageSelectLevel::SetStageTwoGrHandle(int stage_two_handle) {
  stage_two_handle_ = stage_two_handle;
}

/// <summary>
/// GetStageTwoGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ステージ2の画像のグラフィックハンドル</returns>
int StageSelectLevel::GetStageTwoGrHandle() {
  return stage_two_handle_;
}

/// <summary>
/// SetStageThreeGrHandle関数の定義
/// </summary>
/// <param = "stage_three_handle">ステージ3の画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void StageSelectLevel::SetStageThreeGrHandle(int stage_three_handle) {
  stage_three_handle_ = stage_three_handle;
}

/// <summary>
/// GetStageThreeGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ステージ3の画像のグラフィックハンドル</returns>
int StageSelectLevel::GetStageThreeGrHandle() {
  return stage_three_handle_;
}


/// <summary>
/// SetLockGrHandle関数の定義
/// </summary>
/// <param = "lock_handle">鍵の画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void StageSelectLevel::SetLockGrHandle(int lock_handle) {
  lock_handle_ = lock_handle;
}

/// <summary>
/// GetLockGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>鍵の画像のグラフィックハンドル</returns>
int StageSelectLevel::GetLockGrHandle() {
  return lock_handle_;
}