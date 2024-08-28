#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include "Game/Level/TitleLevel.h"
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
  //選択項目の描画X座標を定数kXcoordinateに格納する
  /// <summary>
  static const int kXcoordinate = 485;

  /// <summary>
  //選択項目の描画Y座標を定数kYcoordinateに格納する
  /// <summary>
  static const int kYcoordinate = 305;

  /// <summary>
  //回る物体の描画X座標を定数kPlayerXcoordinatesに格納する
  /// <summary>
  static const int kPlayerXcoordinates[] = { 495, 496, 527, 484 };

  /// <summary>
  //回る物体の描画Y座標を定数kPlayerYcoordinatesに格納する
  /// <summary>
  static const int kPlayerYcoordinates[] = { 305, 378, 447, 535};

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
  /// タイトル画面の背景画像のファイル名を定数kTitlePngに格納する
  /// </summary>
  static const char* kTitlePng = "Assets/Images/Title/title.png";

  /// <summary>
  /// 星の画像のファイル名を定数kStarPngに格納する
  /// </summary>
  static const char* kStarPng = "Assets/Images/Button/22535725.png";

  /// <summary>
  /// タイトル画面の動画のファイル名を定数kTitleMp4に格納する
  /// </summary>
  static const char* kTitleMp4 = "Assets/Images/title.mp4";

  /// <summary>
  /// フォントを指定する文字列を定数kFontに格納する
  /// </summary>
  static const char* kFont = "メイリオ";

  /// <summary>
  /// 「ゲーム開始」を指定する文字列を定数kGameStartStringに格納する
  /// </summary>
  static const char* kGameStartString = "ゲーム開始";

  /// <summary>
  /// 「操作説明」を指定する文字列を定数kGuideStringに格納する
  /// </summary>
  static const char* kGuideString = "操作説明";

  /// <summary>
  /// 「設定」を指定する文字列を定数kSettingStringに格納する
  /// </summary>
  static const char* kSettingString = "   設定    ";

  /// <summary>
  /// 「ゲーム終了」を指定する文字列を定数kExitStringに格納する
  /// </summary>
  static const char* kExitString = "ゲーム終了";

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
  /// フェードイン時間
  /// </summary>
  const float kFadeInTime = 0.1f;

  /// <summary>
  //描画角度を定数の配列kPiに格納する
  /// <summary>
  static const double kAngles[] = { 0.0, (3.141592654/4),  (3.141592654 / 2), (3*(3.141592654) / 4), (3.141592654 / 1), (5 * (3.141592654) / 4), (3 * (3.141592654) / 2), (7 * (3.141592654) / 4) };

  /// <summary>
  /// kAnglesの要素数を定数kAnglesElementに格納する
  /// </summary>
  static const int kAnglesElement = 8;

  /// <summary>
  /// 角度を変えるまでの待ち時間を定数kWaitTimeに格納する
  /// </summary>
  static const float kWaitTimes[] = { 0.0f, 0.2f, 0.4f, 0.6f, 0.8f, 1.0f, 1.2f, 1.4f, 1.6f };
}

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
TitleLevel::TitleLevel()
: is_finish_(false)
, accumulation_time_(0.0f)
, display_accumulation_time_(0.0f)
, end_type_(kUnloadTask)
, title_handle_(0)
, width_(0)
, height_(0)
, half_width_(0.0f)
, half_height_(0.0f)
, bgm_handle_(0)
, enter_handle_(0)
, cursor_handle_(0)
, menu_type_(kStartGame)
, select_index_(0)
, fade_(0)
, is_enter_(false)
, star_gr_handle_(0)
, angle_type_(kAngle0)
{
  DEBUG_PRINT(TitleLevelのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
TitleLevel::TitleLevel(TaskId task_id, TaskManager* task_manager)
  : Level(task_id, task_manager)
  , is_finish_(false)
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , end_type_(kUnloadTask)
  , title_handle_(0)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , bgm_handle_(0)
  , enter_handle_(0)
  , cursor_handle_(0)
  , menu_type_(kStartGame)
  , select_index_(0)
  , fade_(0)
  , is_enter_(false)
  , star_gr_handle_(0)
  , angle_type_(kAngle0)
{
  DEBUG_PRINT(TitleLevelのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
TitleLevel::~TitleLevel() {
  DEBUG_PRINT(TitleLevelのデストラクタ);
  //accumulation_time_ = 0.0f;
  //display_accumulation_time_ = 0.0f;
}

/// <summary>
/// 決定ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void TitleLevel::OnPushDecide() {
  DEBUG_PRINT(決定ボタンが押された時のイベント);
  is_finish_ = true;
}

/// <summary>
/// 終了ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void TitleLevel::OnPushFinish() {
  //DEBUG_PRINT(終了ボタンが押された時のイベント);
  //SetEndButton();
  //is_finish_ = true;
}

/// <summary>
/// スペースボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void TitleLevel::OnPushPause() {
  DEBUG_PRINT(スペースボタンが押された時のイベント);
}

/// <summary>
/// BackSpaceボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void TitleLevel::OnPushBackSpace() {
  DEBUG_PRINT(BackSpaceボタンが押された時のイベント);
}

/// <summary>
/// SetTitleGrHandle関数の定義
/// </summary>
/// <param = "title_handle">Titleのグラフィックハンドル</param>
/// <returns>なし</returns>
void TitleLevel::SetTitleGrHandle(int title_handle) {
  title_handle_ = title_handle;
}

/// <summary>
/// GetTitleGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Titleのグラフィックハンドル</returns>
int TitleLevel::GetTitleGrHandle() {
  return title_handle_;
}

/// <summary>
/// SetWidth関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void TitleLevel::SetWidth(int size_x) {
  width_ = size_x;
}

/// <summary>
/// GetWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int TitleLevel::GetWidth() {
  return width_;
}

/// <summary>
/// SetHeight関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void TitleLevel::SetHeight(int size_y) {
  height_ = size_y;
}

/// <summary>
/// GetHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さ</returns>
int TitleLevel::GetHeight() {
  return height_;
}

/// <summary>
/// SetHalfWidth関数の定義
/// </summary>
/// <param>画像の幅の半分</param>
/// <returns>なし</returns>
void TitleLevel::SetHalfWidth(float size_half_x) {
  half_width_ = size_half_x;
}

/// <summary>
/// GetHalfWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅の半分</returns>
float TitleLevel::GetHalfWidth() {
  return half_width_;
}

/// <summary>
/// SetHalfHeight関数の定義
/// </summary>
/// <param>画像の高さの半分</param>
/// <returns>なし</returns>
void TitleLevel::SetHalfHeight(float size_half_y) {
  half_height_ = size_half_y;
}

/// <summary>
/// GetHalfHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さの半分</returns>
float TitleLevel::GetHalfHeight() {
  return half_height_;
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool TitleLevel::InitializeUpdate(float time) {
  DEBUG_PRINT(TitleLevelの初期化処理);

  //画像データをロードする
  int title_handle = LoadGraph(kTitlePng);
  int star_handle = LoadGraph(kStarPng);

  //オーディオマネージャーを生成する
  audio_manager_ = new AudioManager();

  //効果音をロードする
  audio_manager_->LoadSe(AudioManager::SeKind::kCursorMp3);
  audio_manager_->LoadSe(AudioManager::SeKind::kEnterMp3);
  //BGMをロードする
  audio_manager_->LoadBgm(AudioManager::BgmKind::kTitleBgmMp3);

  //グラフィックハンドルを設定する
  SetTitleGrHandle(title_handle);
  SetStarGrHandle(star_handle);

  //BGMを再生する
  audio_manager_->PlayBgm(AudioManager::BgmKind::kTitleBgmMp3);

  //ロードした画像の幅を取得して保存するための整数size_xを用意して初期化
  int size_x = 0;
  //ロードした画像の高さを取得して保存するための整数size_yを用意して初期化
  int size_y = 0;

  //ロードしたキャラクターの画像のサイズを取得する
  GetGraphSize(title_handle, &size_x, &size_y);

  DEBUG_PRINT_VAR(size_x);
  DEBUG_PRINT_VAR(size_y);

  //画像の幅を設定する
  SetWidth(size_x);
  //画像の高さを設定する
  SetHeight(size_y);

  //ロードした画像から取得した幅の半分のサイズを計算する
  float half_width = static_cast<float>(size_x) / 2;
  //ロードした画像から取得した高さの半分のサイズを計算する
  float half_height = static_cast<float>(size_y) / 2;

  //画像の幅の半分を設定する
  SetHalfWidth(half_width);
  //画像の高さの半分を設定する
  SetHalfHeight(half_height);

  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool TitleLevel::ProcessingUpdate(float time) {
  //DEBUG_PRINT(TitleLevelの毎フレーム更新処理のフェーズ処理);

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
    // 選択されたメニューに応じて画面遷移する
    if (static_cast<MenuOption>(select_index_) == kStartGame) {
      OnPushDecide();
      //DEBUG_PRINT(ゲーム開始が確定);
    }
    else if (static_cast<MenuOption>(select_index_) == kSetting) {
      //DEBUG_PRINT(設定が確定);
      SetSetting();
      OnPushDecide();
    }
    else if (static_cast<MenuOption>(select_index_) == kGuide) {
      //DEBUG_PRINT(操作説明が確定);
      SetGuide();
      OnPushDecide();
    }
    else if (static_cast<MenuOption>(select_index_) == kExit) {
      SetEndButton();
      OnPushDecide();
      //DEBUG_PRINT(ゲーム終了が確定);
    }
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

  // 矢印キーで選択を変更する
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kUp) && is_enter_ == false) {
    audio_manager_->PlaySe(AudioManager::SeKind::kCursorMp3);
    select_index_ = (select_index_ - 1 + static_cast<int>((MenuOption::kExit)+1)) % static_cast<int>((MenuOption::kExit)+1);
  }
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kDown) && is_enter_ == false) {
    audio_manager_->PlaySe(AudioManager::SeKind::kCursorMp3);
    select_index_ = (select_index_ + 1) % static_cast<int>((MenuOption::kExit)+1);
  }

  // エンターキーが押された場合
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kDecide) && (static_cast<MenuOption>(select_index_) == kStartGame || static_cast<MenuOption>(select_index_) == kGuide || static_cast<MenuOption>(select_index_) == kSetting || static_cast<MenuOption>(select_index_) == kExit)) {
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
void TitleLevel::ProcessingRender() {
  //DEBUG_PRINT(TitleLevelの描画処理);

  //タイトルを表示する
  DrawGraph(0, 0, title_handle_, TRUE);

  ChangeFont(kFont);
  SetFontSize(kFontSize);
  //SetFontThickness(kFontThickness);
  // メニューの描画
  for (int i = 0; i < static_cast<int>((MenuOption::kExit)+1); ++i) {
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
bool TitleLevel::PhaseFinalize(float time) {
  DEBUG_PRINT(TitleLevelの終了処理);
  //描画をクリアする
  ClearDrawScreen();

  //取得したグラフィックハンドルを使い、リソースを破棄する
  DeleteGraph(GetTitleGrHandle());
  DeleteGraph(GetStarGrHandle());

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
void TitleLevel::SetStarGrHandle(int star_gr_handle) {
  star_gr_handle_ = star_gr_handle;
}

/// <summary>
/// GetStarGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>星のグラフィックハンドル</returns>
int TitleLevel::GetStarGrHandle() {
  return star_gr_handle_;
}