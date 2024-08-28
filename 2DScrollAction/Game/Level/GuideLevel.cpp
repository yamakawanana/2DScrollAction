#include <iostream>
#include <chrono>
#include <thread>
#include "Game/Level/GuideLevel.h"
#include "Game/GameInfo/GameInfo.h"
#include "System/FileManager/FileManager.h"
#include "System/Input/InputManager.h"
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
  /// 累積時間のリセット時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 1.0f;

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
  /// 操作説明画面の背景画像のファイル名を定数kGuidePngに格納する
  /// </summary>
  static const char* kGuidePng = "Assets/Images/Guide/guide.png";

  /// <summary>
  /// 星の画像のファイル名を定数kStarPngに格納する
  /// </summary>
  static const char* kStarPng = "Assets/Images/Button/orange_star.png";

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
  /// 「ゲーム開始」を指定する文字列を定数kGameStartStringに格納する
  /// </summary>
  static const char* kGameStartString = "ゲーム開始";

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
  static const int kFontSize = 28;

  /// <summary>
  //左側の文字の表示X位置を定数kXcoordinateに格納する
  /// <summary>
  static const int kXcoordinate = 200;

  /// <summary>
  //左側の文字の表示Y位置を定数kYcoordinateに格納する
  /// <summary>
  static const int kYcoordinate = 440;

  /// <summary>
  //右側の文字の表示X位置を定数kSecondXcoordinateに格納する
  /// <summary>
  static const int kSecondXcoordinate = 450;

  /// <summary>
  //右側の文字の表示Y位置を定数kSecondYcoordinateに格納する
  /// <summary>
  static const int kSecondYcoordinate = 440;

  /// <summary>
  //回る物体の描画X座標を定数kStarXcoordinatesに格納する
  /// <summary>
  static const int kStarXcoordinates[] = { 180, 430};

  /// <summary>
  //回る物体の描画Y座標を定数kStarYcoordinatesに格納する
  /// <summary>
  static const int kStarYcoordinates[] = { 455, 455 };
}

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
GuideLevel::GuideLevel()
  : is_finish_(false)
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , end_type_(kUnloadTask)
  , guide_handle_(0)
  , triangle_handle_(0)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , bgm_handle_(0)
  , cursor_handle_(0)
  , next_level_handle_(0)
  , menu_type_(kGoBattle)
  , fade_(0)
  , is_enter_(false)
  , star_gr_handle_(0)
  , angle_type_(kAngle0)
  , select_index_(0)
{
  DEBUG_PRINT(GuideLevelのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
GuideLevel::GuideLevel(TaskId task_id, TaskManager* task_manager)
  : Level(task_id, task_manager)
  , is_finish_(false)
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , end_type_(kUnloadTask)
  , guide_handle_(0)
  , triangle_handle_(0)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , bgm_handle_(0)
  , cursor_handle_(0)
  , next_level_handle_(0)
  , menu_type_(kGoBattle)
  , fade_(0)
  , is_enter_(false)
  , star_gr_handle_(0)
  , angle_type_(kAngle0)
  , select_index_(0)
{
  DEBUG_PRINT(GuideLevelのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
GuideLevel::~GuideLevel() {
  DEBUG_PRINT(GuideLevelのデストラクタ);
}

/// <summary>
/// 決定ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void GuideLevel::OnPushDecide() {
  DEBUG_PRINT(決定ボタンが押された時のイベント);

  is_finish_ = true;

}

/// <summary>
/// 終了ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void GuideLevel::OnPushFinish() {
  DEBUG_PRINT(Escキーが押された時のイベント);
  
}

/// <summary>
/// ポーズボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void GuideLevel::OnPushPause() {
  DEBUG_PRINT(ポーズボタンが押された時のイベント);
}

/// <summary>
/// SetRuleGrHandle関数の定義
/// </summary>
/// <param = "guide_handle">操作説明のグラフィックハンドル</param>
/// <returns>なし</returns>
void GuideLevel::SetRuleGrHandle(int guide_handle) {
  guide_handle_ = guide_handle;
}

/// <summary>
/// GetRuleGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>操作説明のグラフィックハンドル</returns>
int GuideLevel::GetRuleGrHandle() {
  return guide_handle_;
}

/// <summary>
/// SetWidth関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void GuideLevel::SetWidth(int size_x) {
  width_ = size_x;
}

/// <summary>
/// GetWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int GuideLevel::GetWidth() {
  return width_;
}

/// <summary>
/// SetHeight関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void GuideLevel::SetHeight(int size_y) {
  height_ = size_y;
}

/// <summary>
/// GetHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さ</returns>
int GuideLevel::GetHeight() {
  return height_;
}

/// <summary>
/// SetHalfWidth関数の定義
/// </summary>
/// <param>画像の幅の半分</param>
/// <returns>なし</returns>
void GuideLevel::SetHalfWidth(float size_half_x) {
  half_width_ = size_half_x;
}

/// <summary>
/// GetHalfWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅の半分</returns>
float GuideLevel::GetHalfWidth() {
  return half_width_;
}

/// <summary>
/// SetHalfHeight関数の定義
/// </summary>
/// <param>画像の高さの半分</param>
/// <returns>なし</returns>
void GuideLevel::SetHalfHeight(float size_half_y) {
  half_height_ = size_half_y;
}

/// <summary>
/// GetHalfHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さの半分</returns>
float GuideLevel::GetHalfHeight() {
  return half_height_;
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool GuideLevel::InitializeUpdate(float time) {
  DEBUG_PRINT(GuideLevelの初期化処理);

  //画像データをロードする
  int guide_handle = LoadGraph(kGuidePng);
  int star_handle = LoadGraph(kStarPng);

  //オーディオマネージャーを生成する
  audio_manager_ = new AudioManager();

  //効果音をロードする
  audio_manager_->LoadSe(AudioManager::SeKind::kCursorMp3);
  audio_manager_->LoadSe(AudioManager::SeKind::kEnterMp3);
  //BGMをロードする
  audio_manager_->LoadBgm(AudioManager::BgmKind::kGuideBgmMp3);

  //グラフィックハンドルを設定する
  SetRuleGrHandle(guide_handle);
  //星のグラフィックハンドルを設定する
  SetStarGrHandle(star_handle);

  //BGMを再生する
  audio_manager_->PlayBgm(AudioManager::BgmKind::kGuideBgmMp3);

  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool GuideLevel::ProcessingUpdate(float time) {
  //DEBUG_PRINT(GuideLevelの毎フレーム更新処理のフェーズ処理);

  //入力管理を取得
  InputManager* input_manager = InputManager::GetInstance();

  accumulation_time_ = accumulation_time_ + time;
  if (accumulation_time_ >= kLimitTime) {
    accumulation_time_ = 0.0f;
    //is_finish_ = true;
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
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kRight) && is_enter_ == false) {
    if (select_index_ == static_cast<int>(MenuOption::kGoBattle)) {
      audio_manager_->PlaySe(AudioManager::SeKind::kCursorMp3);
      select_index_ = static_cast<int>(MenuOption::kBackTitle);
    }
  }
  else if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kLeft) && is_enter_ == false) {
    if (select_index_ == static_cast<int>(MenuOption::kBackTitle)) {
      audio_manager_->PlaySe(AudioManager::SeKind::kCursorMp3);
      select_index_ = static_cast<int>(MenuOption::kGoBattle);
    }
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
void GuideLevel::ProcessingRender() {
  //ルール説明画像を描画する
  DrawGraph(0, 0, guide_handle_, TRUE);

  for (int i = 0; i < static_cast<int>((MenuOption::kBackTitle)+1); ++i) {
    if (i == select_index_) {
      for (int j = 0; j < kAnglesElement; j++) {
        if (angle_type_ == static_cast<AngleType>(j)) {
          //選択中の項目の横に回転する物体を描画
          DrawRotaGraph(kStarXcoordinates[i], kStarYcoordinates[i], 1.0, kAngles[j], star_gr_handle_, TRUE);
        }
      }
    }
  }

  //「ゲーム開始」と「タイトルへ」の文字を描画する
  DrawString(kXcoordinate, kYcoordinate, kGameStartString, Cr);
  DrawString(kSecondXcoordinate, kSecondYcoordinate, kGoTitleString, Cr);

  if (is_enter_ == true) {
    //フェードマネージャーのインスタンスを取得
    FadeManager* fade_manager = FadeManager::GetInstance();
    if (fade_ <= (kFadeValue / kPlusAlpha)) {
      //画面遷移時の黒いフェードイン
      fade_manager->FadeIn(0, 0, kScreenSizeX, kScreenSizeY, fade_, kPlusAlpha);
    }
  }

}

/// <summary>
/// 終了処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool GuideLevel::PhaseFinalize(float time) {
  DEBUG_PRINT(GuideLevelの終了処理);
  //描画をクリアする
  ClearDrawScreen();

  //取得したグラフィックハンドルを使い、リソースを破棄する
  DeleteGraph(GetRuleGrHandle());
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
void GuideLevel::SetStarGrHandle(int star_gr_handle) {
  star_gr_handle_ = star_gr_handle;
}

/// <summary>
/// GetStarGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>星のグラフィックハンドル</returns>
int GuideLevel::GetStarGrHandle() {
  return star_gr_handle_;
}