#include <iostream>
#include "Game/Ui/StartUi.h"
#include "Game/GameInfo/GameInfo.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// is_can_display_の配列の要素数を定数kElementNumに格納する
  /// </summary>
  static const int kElementNum = 6;

  /// <summary>
  /// スタートUIを表示終了するまでの時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 3.5f;

  /// <summary>
  /// スタートUIを表示開始するまでの待ち時間を定数kWaitTimeに格納する
  /// </summary>
  static const float kWaitTimes[kElementNum] = { 1.0f, 1.2f, 1.4f, 1.6f, 1.8f, 2.0f };

  /// <summary>
  /// スタートUIを表示するY位置を定数kYCoordinateに格納する
  /// </summary>
  static const int kYCoordinate = 270;

  /// <summary>
  /// スタートUIの1番目のキューブを表示するX位置を定数kXCoordinateOneに格納する
  /// </summary>
  static const int kXCoordinateOne = 280;

  /// <summary>
  /// スタートUIの2番目のキューブを表示するX位置を定数kXCoordinateTwoに格納する
  /// </summary>
  static const int kXCoordinateTwo = 320;

  /// <summary>
  /// スタートUIの3番目のキューブを表示するX位置を定数kXCoordinateThreeに格納する
  /// </summary>
  static const int kXCoordinateThree = 360;

  /// <summary>
  /// スタートUIの4番目のキューブを表示するX位置を定数kXCoordinateFourに格納する
  /// </summary>
  static const int kXCoordinateFour = 400;

  /// <summary>
  /// スタートUIの5番目のキューブを表示するX位置を定数kXCoordinateFiveに格納する
  /// </summary>
  static const int kXCoordinateFive = 440;

  /// <summary>
  /// スタートUIの6番目のキューブを表示するX位置を定数kXCoordinateSixに格納する
  /// </summary>
  static const int kXCoordinateSix = 480;

  /// <summary>
  /// 「R」を指定する文字を定数kRcharに格納する
  /// </summary>
  static const char* kRchar = "R";

  /// <summary>
  /// 「E」を指定する文字を定数kEcharに格納する
  /// </summary>
  static const char* kEchar = "E";

  /// <summary>
  /// 「A」を指定する文字を定数kAcharに格納する
  /// </summary>
  static const char* kAchar = "A";

  /// <summary>
  /// 「D」を指定する文字を定数kDcharに格納する
  /// </summary>
  static const char* kDchar = "D";

  /// <summary>
  /// 「Y」を指定する文字を定数kYcharに格納する
  /// </summary>
  static const char* kYchar = "Y";

  /// <summary>
  /// 「?」を指定する文字を定数kQuestionCharに格納するexclamation
  /// </summary>
  static const char* kQuestionChar = "?";

  /// <summary>
  /// 「S」を指定する文字を定数kScharに格納する
  /// </summary>
  static const char* kSchar = "S";

  /// <summary>
  /// 「T」を指定する文字を定数kTcharに格納する
  /// </summary>
  static const char* kTchar = "T";

  /// <summary>
  //色の値を取得
  /// </summary>
  unsigned int Cr = GetColor(41, 58, 255);

  /// <summary>
  /// 「!」を指定する文字を定数kExclamationCharに格納する
  /// </summary>
  static const char* kExclamationChar = "!";

  /// <summary>
  /// 文字を表示するY位置の微調整で使う値を定数kStringYCoordinateに格納する
  /// </summary>
  static const int kStringYCoordinate = 12;

  /// <summary>
  /// 文字を表示するX位置の微調整で使う値を定数kStringXCoordinateに格納する
  /// </summary>
  static const int kStringXCoordinate = 13;

  /// <summary>
  /// 「!」を表示するX位置の微調整で使う値を定数kExclamationStringXCoordinateに格納する
  /// </summary>
  static const int kExclamationStringXCoordinate = 4;

  /// <summary>
  /// フォントサイズの定数kFontSize
  /// </summary>
  static const int kFontSize = 21;

  /// <summary>
  /// フォントを指定する文字列を定数kFontに格納する
  /// </summary>
  static const char* kFont = "Arial";
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
StartUi::StartUi(TaskId task_id)
  : Task(task_id)
  , gr_handle_(0)
  , accumulation_time_(0.0f)
  , now_phase_(kDisplay)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , is_can_display_{ false }
{
  //DEBUG_PRINT(StartUiのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
StartUi::~StartUi() {
  //DEBUG_PRINT(StartUiのデストラクタ);
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void StartUi::InitStartUi(int gr_handle) {
  //DEBUG_PRINT(StartUiクラスの初期化処理);

}

/// <summary>
/// 毎フレーム更新処理　UpdateFrame関数の定義
/// </summary>
/// <param name="time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
/// <returns>なし</returns>
void StartUi::UpdateFrame(float time) {
  //DEBUG_PRINT(StartUiクラスの毎フレーム更新処理);

  if (now_phase_ != kStop) {
    //accumulation_time_ = accumulation_time_ + time;

    for (int i = 0; i < kElementNum; i++) {
      if (accumulation_time_ >= kWaitTimes[i]) {
        is_can_display_[i] = true;
      }
    }

    //秒経過したら、UI終了待機フェーズにし、accumulation_time_をリセットする
    if (accumulation_time_ >= kLimitTime) {
      now_phase_ = kFinish;
      accumulation_time_ = 0.0f;
    }
  }
}

/// 毎フレーム描画処理
/// </remarks>
/// <param>なし</param>
/// <returns>なし</returns>
void StartUi::RenderFrame() {
  //スタートUIのキューブを時間差で表示する
  if (now_phase_ == kDisplay) {
    int x_coordinates[kElementNum] = { kXCoordinateOne, kXCoordinateTwo, kXCoordinateThree, kXCoordinateFour, kXCoordinateFive, kXCoordinateSix };
    const char* chars[kElementNum] = { kSchar, kTchar, kAchar, kRchar, kTchar, kExclamationChar };
    for (int i = 0; i < kElementNum; i++) {
      if (is_can_display_[i]) {
        SetFontSize(kFontSize);
        ChangeFont(kFont);
        //DrawGraph(x_coordinates[i], kYCoordinate, gr_handle_, TRUE);
        if (i == (kElementNum - 1)){
          //DrawFormatString((x_coordinates[i] + kStringXCoordinate + kExclamationStringXCoordinate), (kYCoordinate + kStringYCoordinate), Cr, chars[i]);
        }
        else {
          //DrawFormatString((x_coordinates[i] + kStringXCoordinate), (kYCoordinate + kStringYCoordinate), Cr, chars[i]);
        }
        
      }
    }
  }
}

/// <summary>
/// GetGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int StartUi::GetGrHandle() {
  return gr_handle_;
}

/// <summary>
/// SetGrHandle関数の定義
/// </summary>
/// <param = "gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void StartUi::SetGrHandle(int gr_handle) {
  gr_handle_ = gr_handle;
}

/// <summary>
/// SetWidth関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void StartUi::SetWidth(int size_x) {
  width_ = size_x;
}

/// <summary>
/// GetWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int StartUi::GetWidth() {
  return width_;
}

/// <summary>
/// SetHeight関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void StartUi::SetHeight(int size_y) {
  height_ = size_y;
}

/// <summary>
/// GetHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さ</returns>
int StartUi::GetHeight() {
  return height_;
}

/// <summary>
/// SetHalfWidth関数の定義
/// </summary>
/// <param>画像の幅の半分</param>
/// <returns>なし</returns>
void StartUi::SetHalfWidth(float size_half_x) {
  half_width_ = size_half_x;
}

/// <summary>
/// GetHalfWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅の半分</returns>
float StartUi::GetHalfWidth() {
  return half_width_;
}

/// <summary>
/// SetHalfHeight関数の定義
/// </summary>
/// <param>画像の高さの半分</param>
/// <returns>なし</returns>
void StartUi::SetHalfHeight(float size_half_y) {
  half_height_ = size_half_y;
}

/// <summary>
/// GetHalfHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さの半分</returns>
float StartUi::GetHalfHeight() {
  return half_height_;
}

/// <summary>
/// SetPhaseType関数の定義
/// </summary>
/// <param = "type">方向の種類</param>
/// <returns>なし</returns>
void StartUi::SetPhaseType(PhaseType type) {
  now_phase_ = type;
}

/// <summary>
/// GetPhaseType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
StartUi::PhaseType StartUi::GetPhaseType() {
  return now_phase_;
}