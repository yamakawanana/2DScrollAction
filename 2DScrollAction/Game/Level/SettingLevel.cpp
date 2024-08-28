#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include "Game/Level/SettingLevel.h"
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
  //黒色の値を取得
  /// <summary>
  unsigned int Cr = GetColor(0, 0, 0);

  /// <summary>
  //白色の値を取得
  /// </summary>
  unsigned int WhiteCr = GetColor(255, 255, 255);

  /// <summary>
  /// 累積時間のリセット時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 1.6f;

  /// <summary>
  //左側のボタンの画像のX位置を定数kXcoordinateに格納する
  /// <summary>
  static const int kXcoordinate = 225;

  /// <summary>
  //左側のボタンの画像のY位置を定数kYcoordinateに格納する
  /// <summary>
  static const int kYcoordinate = 395;

  /// <summary>
  //右側のボタンの画像のX位置を定数kSecondXcoordinateに格納する
  /// <summary>
  static const int kSecondXcoordinate = 413;

  /// <summary>
  //右側のボタンの画像のY位置を定数kSecondYcoordinateに格納する
  /// <summary>
  static const int kSecondYcoordinate = 395;

  /// <summary>
  /// 音量の変化量を定数kChangeVolumeに格納する
  /// </summary>
  static const int kChangeVolume = 5;

  /// <summary>
  /// 音量の初期値を定数kDefaultVolumeに格納する
  /// </summary>
  static const int kDefaultVolume = 80;

  /// <summary>
  /// 音量の初期値を定数kVolumeMaxに格納する
  /// </summary>
  static const int kVolumeMax = 100;

  // <summary>
  //画面の幅を定数kScreenSizeXに格納する
  /// <summary>
  static const int kScreenSizeX = 800;

  // <summary>
  //画面の高さを定数kScreenSizeYに格納する
  /// <summary>
  static const int kScreenSizeY = 600;

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

  /// <summary>
  /// 背景画像のファイル名を定数kSettingPngに格納する
  /// </summary>
  static const char* kSettingPng = "Assets/Images/Setting/setting_back.png";

  /// <summary>
  /// 押されている時のボタンのファイル名を定数kButtonOnPngに格納する
  /// </summary>
  static const char* kButtonOnPng = "Assets/Images/Button/button_on.png";

  /// <summary>
  /// 押されていない時のボタンのファイル名を定数kButtonOffPngに格納する
  /// </summary>
  static const char* kButtonOffPng = "Assets/Images/Button/button_off.png";

  /// <summary>
  /// 星の画像のファイル名を定数kStarPngに格納する
  /// </summary>
  static const char* kStarPng = "Assets/Images/Button/orange_star.png";

  /// <summary>
  /// 設定を保存するファイル名を定数kSettingCSVに格納する
  /// </summary>
  static const char* kSettingCSV = "Assets/CsvFiles/setting.csv";

  /// <summary>
  /// 「","」を指定する文字列を定数kCommaに格納する
  /// </summary>
  static const char* kComma = ",";

  /// <summary>
  /// フォントを指定する文字列を定数kFontに格納する
  /// </summary>
  static const char* kFont = "メイリオ";

  /// <summary>
  /// フォントサイズの定数kFontSize
  /// </summary>
  static const int kFontSize = 28;

  /// <summary>
  /// 「%4d」を指定する文字列を定数kPercentFiveDに格納する
  /// </summary>
  static const char* kPercentFiveD = "%4d";

  /// <summary>
  //音量の描画のX位置を定数kSoundVolumeXに格納する
  /// <summary>
  static const int kSoundVolumeX = 363;

  /// <summary>
  //音量の描画のY位置を定数kSoundVolumeYに格納する
  /// <summary>
  static const int kSoundVolumeY = 250;

  /// <summary>
  /// 「ゲーム開始」を指定する文字列を定数kGameStartStringに格納する
  /// </summary>
  static const char* kGameStartString = "ゲーム開始";

  /// <summary>
  /// 「タイトルへ」を指定する文字列を定数kGoTitleStringに格納する
  /// </summary>
  static const char* kGoTitleString = "タイトルへ";

  /// <summary>
  //画像と文字の描画X位置の差を定数kChangeXに格納する
  /// <summary>
  static const int kChangeX = 14;

  /// <summary>
  //画像と文字の描画Y位置の差を定数kChangeYに格納する
  /// <summary>
  static const int kChangeY = 6;

  /// <summary>
  //円周率を定数kPiに格納する
  /// <summary>
  static const double kPi = 3.141592654;

  /// <summary>
  /// 効果音の最大音量を定数kVolumeに格納する
  /// </summary>
  static const int kMaxSoundEffectVolume = 255;

  /// <summary>
  /// 100％の分母を定数kHundredに格納する
  /// </summary>
  static const int kHundred = 100;

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
  /// 音量の最小値の星の描画X位置を定数kMinStarXに格納する
  /// </summary>
  static const int kMinStarX = 280;

  /// <summary>
  /// 音量の最大値の星の描画X位置を定数kMaxStarXに格納する
  /// </summary>
  static const int kMaxStarX = 520;

  /// <summary>
  /// 音量の最大値の星の描画Y位置を定数kStarYに格納する
  /// </summary>
  static const int kStarY = 300;

  /// <summary>
  /// 星の描画X位置の変化量を定数kChangeStarXに格納する
  /// </summary>
  static const int kChangeStarX = 12;

  /// <summary>
  /// BGMのボリュームの倍率
  /// </summary>
  const float kBgmVolume = 0.8f;
}

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
SettingLevel::SettingLevel()
  : is_finish_(false)
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , end_type_(kUnloadTask)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , menu_type_(kSoundVolume)
  , setting_handle_(0)
  , triangle_handle_(0)
  , bgm_handle_(0)
  , next_level_handle_(0)
  , cursor_handle_(0)
  , select_index_(0)
  , sound_volume_(kDefaultVolume)
  , on_button_handle_(0)
  , off_button_handle_(0)
  , fade_(0)
  , is_enter_(false)
  , star_gr_handle_(0)
  , angle_type_(kAngle0)
{
  DEBUG_PRINT(SettingLevelのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
SettingLevel::SettingLevel(TaskId task_id, TaskManager* task_manager)
  : Level(task_id, task_manager)
  , is_finish_(false)
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , end_type_(kUnloadTask)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , menu_type_(kSoundVolume)
  , setting_handle_(0)
  , triangle_handle_(0)
  , bgm_handle_(0)
  , next_level_handle_(0)
  , cursor_handle_(0)
  , select_index_(0)
  , sound_volume_(kDefaultVolume)
  , on_button_handle_(0)
  , off_button_handle_(0)
  , fade_(0)
  , is_enter_(false)
  , star_gr_handle_(0)
  , angle_type_(kAngle0)
{
  DEBUG_PRINT(SettingLevelのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
SettingLevel::~SettingLevel() {
  DEBUG_PRINT(SettingLevelのデストラクタ);
  //accumulation_time_ = 0.0f;
  //display_accumulation_time_ = 0.0f;
}

/// <summary>
/// 決定ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void SettingLevel::OnPushDecide() {
  DEBUG_PRINT(決定ボタンが押された時のイベント);

  is_finish_ = true;

}

/// <summary>
/// 終了ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void SettingLevel::OnPushFinish() {
  DEBUG_PRINT(Escキーが押された時のイベント);
  //phase_type_ = kFadeOut;
}

/// <summary>
/// スペースボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void SettingLevel::OnPushPause() {
  DEBUG_PRINT(スペースボタンが押された時のイベント);
}

/// <summary>
/// BackSpaceボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void SettingLevel::OnPushBackSpace() {
  DEBUG_PRINT(BackSpaceボタンが押された時のイベント);

}

/// <summary>
/// SetSettingGrHandle関数の定義
/// </summary>
/// <param = "setting_handle">設定画面のグラフィックハンドル</param>
/// <returns>なし</returns>
void SettingLevel::SetSettingGrHandle(int setting_handle) {
  setting_handle_ = setting_handle;
}

/// <summary>
/// GetSettingGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>設定画面のグラフィックハンドル</returns>
int SettingLevel::GetSettingGrHandle() {
  return setting_handle_;
}

/// <summary>
/// SetWidth関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void SettingLevel::SetWidth(int size_x) {
  width_ = size_x;
}

/// <summary>
/// GetWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int SettingLevel::GetWidth() {
  return width_;
}

/// <summary>
/// SetHeight関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void SettingLevel::SetHeight(int size_y) {
  height_ = size_y;
}

/// <summary>
/// GetHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さ</returns>
int SettingLevel::GetHeight() {
  return height_;
}

/// <summary>
/// SetHalfWidth関数の定義
/// </summary>
/// <param>画像の幅の半分</param>
/// <returns>なし</returns>
void SettingLevel::SetHalfWidth(float size_half_x) {
  half_width_ = size_half_x;
}

/// <summary>
/// SetTriangleGrHandle関数の定義
/// </summary>
/// <param = "triangle_handle">三角形の画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void SettingLevel::SetTriangleGrHandle(int triangle_handle) {
  triangle_handle_ = triangle_handle;
}

/// <summary>
/// GetTriangleGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>三角形の画像のグラフィックハンドル</returns>
int SettingLevel::GetTriangleGrHandle() {
  return triangle_handle_;
}

/// <summary>
/// SetBgmHandle関数の定義
/// </summary>
/// <param = "bgm_handle">BGMのサウンドハンドル</param>
/// <returns>なし</returns>
void SettingLevel::SetBgmHandle(int bgm_handle) {
  bgm_handle_ = bgm_handle;
}

/// <summary>
/// GetBgmHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>BGMのサウンドハンドル</returns>
int SettingLevel::GetBgmHandle() {
  return bgm_handle_;
}

/// <summary>
/// SetCursorSoundHandle関数の定義
/// </summary>
/// <param = "cursor_sound_handle">カーソル操作のサウンドハンドル</param>
/// <returns>なし</returns>
void SettingLevel::SetCursorSoundHandle(int cursor_handle) {
  cursor_handle_ = cursor_handle;
}

/// <summary>
/// GetCursorSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>カーソル操作のサウンドハンドル</returns>
int SettingLevel::GetCursorSoundHandle() {
  return cursor_handle_;
}

/// <summary>
/// SetNextLevelSoundHandle関数の定義
/// </summary>
/// <param = "next_level_handle">次のレベルに遷移する時のサウンドハンドル</param>
/// <returns>なし</returns>
void SettingLevel::SetNextLevelSoundHandle(int next_level_handle) {
  next_level_handle_ = next_level_handle;
}

/// <summary>
/// GetNextLevelSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>次のレベルに遷移する時のサウンドハンドル</returns>
int SettingLevel::GetNextLevelSoundHandle() {
  return next_level_handle_;
}

/// <summary>
/// GetHalfWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅の半分</returns>
float SettingLevel::GetHalfWidth() {
  return half_width_;
}

/// <summary>
/// SetHalfHeight関数の定義
/// </summary>
/// <param>画像の高さの半分</param>
/// <returns>なし</returns>
void SettingLevel::SetHalfHeight(float size_half_y) {
  half_height_ = size_half_y;
}

/// <summary>
/// GetHalfHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さの半分</returns>
float SettingLevel::GetHalfHeight() {
  return half_height_;
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool SettingLevel::InitializeUpdate(float time) {
  DEBUG_PRINT(SettingLevelの初期化処理);

  //画像データをロードする
  int rule_gr_handle = LoadGraph(kSettingPng);
  int button_on_handle = LoadGraph(kButtonOnPng);
  int button_off_handle = LoadGraph(kButtonOffPng);
  int star_handle = LoadGraph(kStarPng);

  //オーディオマネージャーを生成する
  audio_manager_ = new AudioManager();

  //効果音をロードする
  audio_manager_->LoadSe(AudioManager::SeKind::kCursorMp3);
  audio_manager_->LoadSe(AudioManager::SeKind::kEnterMp3);
  //BGMをロードする
  audio_manager_->LoadBgm(AudioManager::BgmKind::kSettingBgmMp3);

  //グラフィックハンドルを設定する
  SetSettingGrHandle(rule_gr_handle);
  //ボタンのグラフィックハンドルを設定する
  SetButtonOnGrHandle(button_on_handle);
  SetButtonOffGrHandle(button_off_handle);
  //星のグラフィックハンドルを設定する
  SetStarGrHandle(star_handle);

  //ファイルマネージャーのインスタンスを取得
  FileManager* file_manager = FileManager::GetInstance();

  //設定のファイルを読み込む
  std::vector<int> setting = file_manager->ReadDataFromFile(kSettingCSV);

  //音量の設定をセットする
  sound_volume_ = setting.at(0);
  DEBUG_PRINT_VAR(sound_volume_);

  //BGMを再生する
  audio_manager_->PlayBgm(AudioManager::BgmKind::kSettingBgmMp3);

  //フォントとフォントサイズを設定する
  ChangeFont(kFont);
  SetFontSize(kFontSize);

  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool SettingLevel::ProcessingUpdate(float time) {
  //DEBUG_PRINT(SettingLevelの毎フレーム更新処理のフェーズ処理);

  //入力管理を取得
  InputManager* input_manager = InputManager::GetInstance();

  if (select_index_ == static_cast<int>(kSoundVolume)) {
    accumulation_time_ = accumulation_time_ + time;
    if (accumulation_time_ >= kLimitTime) {
      accumulation_time_ = 0.0f;
    }
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
    //ファイルマネージャーのインスタンスを取得
    FileManager* file_manager = FileManager::GetInstance();
    //設定の値を一時的に格納するvector
    std::vector<int> setting;
    setting.push_back(sound_volume_);
    file_manager->WriteDataToFile(kSettingCSV, setting);
    OnPushDecide();
  }

  //×ボタンが押された場合
  if (GetWindowUserCloseFlag()) {
    SetEndButton();
    is_finish_ = true;
  }

  //Enterが押されたら、決定ボタンが押された時のイベントを呼び出す
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kDecide) && (select_index_ == static_cast<int>(MenuOption::kBackTitle) || select_index_ == static_cast<int>(MenuOption::kGoBattle))) {
    is_enter_ = true; 
    audio_manager_->PlaySe(AudioManager::SeKind::kEnterMp3);
  }

  // 矢印キーで変更する
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kUp) && is_enter_ == false) {
    if (select_index_ == static_cast<int>(MenuOption::kGoBattle)|| select_index_ == static_cast<int>(MenuOption::kBackTitle)) {
      audio_manager_->PlaySe(AudioManager::SeKind::kCursorMp3);
      select_index_ = static_cast<int>(MenuOption::kSoundVolume);
    }
  }
  else if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kDown) && is_enter_ == false) {
    if (select_index_ == static_cast<int>(MenuOption::kSoundVolume)) {
      audio_manager_->PlaySe(AudioManager::SeKind::kCursorMp3);
      select_index_ = static_cast<int>(MenuOption::kGoBattle);
    }
  }
  else if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kRight) && is_enter_ == false) {
    if (select_index_ == static_cast<int>(MenuOption::kGoBattle)) {
      audio_manager_->PlaySe(AudioManager::SeKind::kCursorMp3);
      select_index_ = static_cast<int>(MenuOption::kBackTitle);
    }
    else if (select_index_ == static_cast<int>(MenuOption::kSoundVolume) && sound_volume_ < kVolumeMax) {
      audio_manager_->PlaySe(AudioManager::SeKind::kCursorMp3);
      sound_volume_ = sound_volume_ + kChangeVolume;
    }
  }
  else if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kLeft) && is_enter_ == false) {
    if (select_index_ == static_cast<int>(MenuOption::kBackTitle)) {
      audio_manager_->PlaySe(AudioManager::SeKind::kCursorMp3);
      select_index_ = static_cast<int>(MenuOption::kGoBattle);
    }
    else if (select_index_ == static_cast<int>(MenuOption::kSoundVolume) && sound_volume_ > 0) {
      audio_manager_->PlaySe(AudioManager::SeKind::kCursorMp3);
      sound_volume_ = sound_volume_ - kChangeVolume;
    }
  }

  //DEBUG_PRINT_VAR(select_index_);

  //再生中のサウンドの音量を変更する
  audio_manager_->ChangeBgmVolume(AudioManager::BgmKind::kSettingBgmMp3, static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) * kBgmVolume / static_cast<float>(kHundred))));
  audio_manager_->ChangeSeVolume(AudioManager::SeKind::kEnterMp3, static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))));
  audio_manager_->ChangeSeVolume(AudioManager::SeKind::kCursorMp3, static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))));

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
void SettingLevel::ProcessingRender() {
  //設定画面の背景画像を描画する
  DrawGraph(0, 0, setting_handle_, TRUE);

  //押されていない状態のボタンを表示する
  DrawGraph(kXcoordinate, kYcoordinate, off_button_handle_, TRUE);
  DrawGraph(kSecondXcoordinate, kSecondYcoordinate, off_button_handle_, TRUE);

  //押されている状態のボタンを描画する
  if (select_index_ == static_cast<int>(MenuOption::kGoBattle)) {
    DrawGraph(kXcoordinate, kYcoordinate, on_button_handle_, TRUE);
  }
  else if (select_index_ == static_cast<int>(MenuOption::kBackTitle)) {
    DrawGraph(kSecondXcoordinate, kSecondYcoordinate, on_button_handle_, TRUE);
  }

  //「ゲーム開始」と「タイトルへ」の文字を描画する
  DrawString(kXcoordinate + kChangeX, kYcoordinate + kChangeY, kGameStartString, WhiteCr);
  DrawString(kSecondXcoordinate + kChangeX, kSecondYcoordinate + kChangeY, kGoTitleString, WhiteCr);

  //現在の音量を音量の変化量で割った値を計算する
  int sound_volume_x = (sound_volume_ / kChangeVolume);

  for (int j = 0; j < kAnglesElement; j++) {
    if (angle_type_ == static_cast<AngleType>(j)) {
      //音量の位置に合わせて回転する星を描画
      DrawRotaGraph(kMinStarX + (sound_volume_x * kChangeStarX), kStarY, 1.0, kAngles[j], star_gr_handle_, TRUE);
    }
  }
  
  //音量の数字を描画する
  DrawFormatString(kSoundVolumeX, kSoundVolumeY, Cr, kPercentFiveD, sound_volume_);

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
bool SettingLevel::PhaseFinalize(float time) {
  DEBUG_PRINT(SettingLevelの終了処理);
  //描画をクリアする
  ClearDrawScreen();

  //取得したグラフィックハンドルを使い、リソースを破棄する

  DeleteGraph(GetSettingGrHandle());
  DeleteGraph(GetButtonOnGrHandle());
  DeleteGraph(GetButtonOffGrHandle());
  DeleteGraph(GetStarGrHandle());

  //サウンドのリソースを破棄する
  DeleteSoundMem(GetBgmHandle());
  DeleteSoundMem(GetCursorSoundHandle());
  DeleteSoundMem(GetNextLevelSoundHandle());

  //オーディオマネージャーの後処理と破棄
  audio_manager_->FinAudioManager();
  delete audio_manager_;
  audio_manager_ = nullptr;

  return true;
}

/// <summary>
/// SetButtonOnGrHandle関数の定義
/// </summary>
/// <param = "on_button_handle">押されているボタンのグラフィックハンドル</param>
/// <returns>なし</returns>
void SettingLevel::SetButtonOnGrHandle(int on_button_handle) {
  on_button_handle_ = on_button_handle;
}

/// <summary>
/// GetButtonOnGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>押されているボタンのグラフィックハンドル</returns>
int SettingLevel::GetButtonOnGrHandle() {
  return on_button_handle_;
}

/// <summary>
/// SetButtonOffGrHandle関数の定義
/// </summary>
/// <param = "off_button_handle">押されていないボタンのグラフィックハンドル</param>
/// <returns>なし</returns>
void SettingLevel::SetButtonOffGrHandle(int off_button_handle) {
  off_button_handle_ = off_button_handle;
}

/// <summary>
/// GetButtonOffGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>押されていないボタンのグラフィックハンドル</returns>
int SettingLevel::GetButtonOffGrHandle() {
  return off_button_handle_;
}

/// <summary>
/// SetStarGrHandle関数の定義
/// </summary>
/// <param = "star_gr_handle">星のグラフィックハンドル</param>
/// <returns>なし</returns>
void SettingLevel::SetStarGrHandle(int star_gr_handle) {
  star_gr_handle_ = star_gr_handle;
}

/// <summary>
/// GetStarGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>星のグラフィックハンドル</returns>
int SettingLevel::GetStarGrHandle() {
  return star_gr_handle_;
}