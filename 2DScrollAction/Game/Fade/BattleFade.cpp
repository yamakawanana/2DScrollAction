#include <iostream>
#include "Game/Fade/BattleFade.h"
#include "System/LogConsole/LogConsole.h"
#include "Game/Field/Field.h"
#include "Game/Fade/FadeManager.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// 計算に使用する整数2を定数kTwoに格納する
  /// </summary>
  static const int kTwo = 2;

  /// <summary>
  /// 計算に使用する整数3を定数kThreeに格納する
  /// </summary>
  static const int kThree = 3;

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
  /// フェードイン時間
  /// </summary>
  const float kFadeInTime = 0.1f;

  /// <summary>
  //黒色の値を取得
  /// <summary>
  unsigned int Cr = GetColor(0, 0, 0);
}

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
BattleFade::BattleFade()
  : fade_(0)
  , is_fade_(false)
  , display_accumulation_time_(0.0f)
  , is_fade_end_(false)
{
  DEBUG_PRINT(BattleFadeのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
BattleFade::BattleFade(TaskId task_id)
  : Task(task_id)
  , fade_(0)
  , is_fade_(false)
  , display_accumulation_time_(0.0f)
  , is_fade_end_(false)
{
  DEBUG_PRINT(BattleFadeのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
BattleFade::~BattleFade() {
  DEBUG_PRINT(BattleFadeのデストラクタ);
  //display_accumulation_time_ = 0.0f;
}

/// <summary>
/// 毎フレーム更新処理　UpdateFrame関数の定義
/// </summary>
/// <param name="time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
/// <returns>なし</returns>
void BattleFade::UpdateFrame(float time) {
  //DEBUG_PRINT(BattleFadeクラスの毎フレーム更新処理);

  if (is_fade_) {
    display_accumulation_time_ = display_accumulation_time_ + time;
    if (display_accumulation_time_ >= kFadeInTime) {
      fade_++;
      display_accumulation_time_ = 0;
    }
  }

}

/// <summary>
/// RenderFrame関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleFade::RenderFrame() {
  if (is_fade_) {
    //フェードマネージャーのインスタンスを取得
    FadeManager* fade_manager = FadeManager::GetInstance();
    if (fade_ <= (kFadeValue / kPlusAlpha)) {
      fade_manager->FadeIn(0, 0, kScreenSizeX, kScreenSizeY, fade_, kPlusAlpha);
    }
    else {
      is_fade_end_ = true;
      DrawBox(0, 0, kScreenSizeX, kScreenSizeY, Cr, TRUE);
    }
  }
}

/// <summary>
/// SetFade関数の定義
/// </summary>
/// <param = "is_fade">フェードの有無</param>
/// <returns>なし</returns>
void BattleFade::SetFade(bool is_fade) {
  is_fade_ = is_fade;
}

/// <summary>
/// GetFadeEnd関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>フェードが終わったかの有無</returns>
bool BattleFade::GetFadeEnd() {
  return is_fade_end_;
}