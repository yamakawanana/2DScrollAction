#include <iostream>
#include "Game/Item/Item.h"
#include "System/LogConsole/LogConsole.h"
#include "Game/GameInfo/GameInfo.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// X座標の開始位置を定数kStartPlayerXに格納する
  /// </summary>
  static const int kStartItemX = 3400;

  /// <summary>
  /// Y座標の開始位置を定数kStartPlayerYに格納する
  /// </summary>
  static const int kStartItemY = 300;

  /// <summary>
  /// アイテムの描画の次の要素に切り替える時間を定数の配列kChangeTimeに格納する
  /// </summary>
  static const float kChangeTime[] = { 0.05f, 0.1f, 0.15f, 0.2f ,0.25f ,0.3f ,0.35f ,0.4f ,0.45f ,0.5f ,0.55f, 0.6f ,0.65f ,0.7f ,0.75f ,0.8f, 0.85f };

  /// <summary>
  /// アイテムをゲットしたエフェクトの描画の次の要素に切り替える時間を定数の配列kEffectChangeTimeに格納する
  /// </summary>
  static const float kEffectChangeTime[] = { 0.05f, 0.1f, 0.15f, 0.2f ,0.25f ,0.3f};
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Item::Item(Task task_id)
  : Task(task_id)
  , now_phase_(kPreraration)
  , status_type_(kExist)
  , gr_handle_{}
  , get_effect_gr_handle_{}
  , change_amount_(100)
  , x_coordinate_(kStartItemX)
  , y_coordinate_(kStartItemY)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , accumulation_time_(0.0f)
  , items_get_accumulation_time_(0.0f)
  , index_(0)
  , difference_x_pos_(0)
  , effect_index_(0)
{
  DEBUG_PRINT(Itemのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Item::~Item() {
  DEBUG_PRINT(Itemのデストラクタ);
  //accumulation_time_ = 0.0f;
  //items_get_accumulation_time_ = 0.0f;
}

/// <summary>
/// 毎フレーム更新処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>なし</returns>
void Item::UpdateFrame(float time) {
  //DEBUG_PRINT(Itemの毎フレーム更新処理);

  if (now_phase_ != kStop) {
    accumulation_time_ = accumulation_time_ + time;
  }
  if (status_type_ == kEffect) {
    items_get_accumulation_time_ = items_get_accumulation_time_ + time;
  }

  //累積時間に応じてindex_を更新する
  for (int i = 0; i < (kWatermelonX - 1); i++) {
    if (accumulation_time_ >= kChangeTime[i]) {
      index_ = i + 1;
    }
  }
  for (int i = 0; i < (kItemGetEffectX - 1); i++) {
    if (items_get_accumulation_time_ >= kEffectChangeTime[i]) {
      effect_index_ = i + 1;
    }
  }

  if (accumulation_time_ > kChangeTime[kWatermelonX - 1]) {
    accumulation_time_ = 0.0f;
    index_ = 0;
  }
  if (items_get_accumulation_time_ > kChangeTime[kItemGetEffectX - 1]) {
    items_get_accumulation_time_ = 0.0f;
    effect_index_ = 0;
    status_type_ = kNone;
  }

  //アイテムが獲得されて消えている場合
  if (status_type_ == kNone) {
    x_coordinate_ = 0;
    y_coordinate_ = 0;
  }

}

/// 毎フレーム描画処理
/// </remarks>
/// <param>なし</param>
/// <returns>なし</returns>
void Item::RenderFrame() {
  //DEBUG_PRINT(Itemの毎フレーム描画処理);
  {
    // アイテムが存在する場合
    if (status_type_ != kNone && status_type_ != kEffect) {
      DrawGraph((x_coordinate_ - difference_x_pos_), (y_coordinate_), gr_handle_[(index_) % kWatermelonX], TRUE);
    }
    // アイテムが消える場合
    if (status_type_ == kEffect) {
      DrawGraph((x_coordinate_ - difference_x_pos_), (y_coordinate_), get_effect_gr_handle_[(effect_index_) % kItemGetEffectX], TRUE);
    }
  }
}

/// <summary>
/// GetGrHandle関数の定義
/// </summary>
/// <param>要素番号</param>
/// <returns>グラフィックハンドル</returns>
int Item::GetGrHandle(int element) {
  return gr_handle_[element];
}

/// <summary>
/// SetGrHandle関数の定義
/// </summary>
/// <param = "gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Item::SetGrHandle(std::array<int, kWatermelonX> gr_handle) {
  gr_handle_ = gr_handle;
}

/// <summary>
/// GetEffectGrHandle関数の定義
/// </summary>
/// <param>要素番号</param>
/// <returns>グラフィックハンドル</returns>
int Item::GetEffectGrHandle(int element) {
  return get_effect_gr_handle_[element];
}

/// <summary>
/// SetEffectGrHandle関数の定義
/// </summary>
/// <param = "get_effect_gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Item::SetEffectGrHandle(std::array<int, kItemGetEffectX> get_effect_gr_handle) {
  get_effect_gr_handle_ = get_effect_gr_handle;
}

/// <summary>
/// SetPhaseType関数の定義
/// </summary>
/// <param = "type">フェーズの種類</param>
/// <returns>なし</returns>
void Item::SetPhaseType(PhaseType type) {
  now_phase_ = type;
}

/// <summary>
/// GetPhaseType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>フェーズの種類</returns>
Item::PhaseType Item::GetPhaseType() {
  return now_phase_;
}

/// <summary>
/// SetStatusType関数の定義
/// </summary>
/// <param = "type">方向の種類</param>
/// <returns>なし</returns>
void Item::SetStatusType(StatusType type) {
  status_type_ = type;
}

/// <summary>
/// GetStatusType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
Item::StatusType Item::GetStatusType() {
  return status_type_;
}

/// <summary>
/// SetDifferenceXpos関数の定義
/// </summary>
/// <param>フィールドの描画X位置を調整するための整数</param>
/// <returns>なし</returns>
void Item::SetDifferenceXpos(int difference_x_pos) {
  difference_x_pos_ = difference_x_pos;
}

/// <summary>
/// SetXPosition関数の定義
/// </summary>
/// <param = "x_coordinate">X座標</param>
/// <returns>なし</returns>
void Item::SetXPosition(int x_coordinate) {
  x_coordinate_ = x_coordinate;
}

/// <summary>
/// GetXPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>X座標</returns>
int Item::GetXPosition() {
  return x_coordinate_;
}

/// <summary>
/// SetYPosition関数の定義
/// </summary>
/// <param = "y_coordinate">Y座標</param>
/// <returns>なし</returns>
void Item::SetYPosition(int y_coordinate) {
  y_coordinate_ = y_coordinate;
}

/// <summary>
/// GetYPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Y座標</returns>
int Item::GetYPosition() {
  return y_coordinate_;
}