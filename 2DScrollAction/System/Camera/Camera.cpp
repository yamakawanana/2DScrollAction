#include <iostream>
#include "System/Camera/Camera.h"
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
  /// 座標の位置調整に使用する整数4を定数kFourに格納する
  /// </summary>
  static const int kFour = 4;

  /// <summary>
  /// 進行方向が右の場合の遅延係数を定数kDelayRightに格納する
  /// </summary>
  static const float kDelayRight = 0.6f;

  /// <summary>
  /// 進行方向が左の場合の遅延係数を定数kDelayLeftに格納する
  /// </summary>
  static const float kDelayLeft = 0.0001f;

  /// <summary>
  /// カメラに映す範囲の微調整に使用する整数を定数kRangeChangeに格納する
  /// </summary>
  static const int kRangeChange = 0;

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
Camera::Camera()
  : difference_x_pos_(0)
  , player_x_pos_(0)
  , target_x_pos_(0)
  , is_turn_(false)
{
  DEBUG_PRINT(Cameraのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Camera::Camera(TaskId task_id)
  : Task(task_id)
  , difference_x_pos_(0)
  , player_x_pos_(0)
  , target_x_pos_(0)
  , is_turn_(false)
{
  DEBUG_PRINT(Cameraのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Camera::~Camera() {
  DEBUG_PRINT(Cameraのデストラクタ);
  //display_accumulation_time_ = 0.0f;
}

/// <summary>
/// 毎フレーム更新処理　UpdateFrame関数の定義
/// </summary>
/// <param name="time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
/// <returns>なし</returns>
void Camera::UpdateFrame(float time) {
  //DEBUG_PRINT(Cameraクラスの毎フレーム更新処理);

  //プレイヤーのX位置から目標X位置を計算する
  //進行方向が左向きの場合
  if (is_turn_) {
    target_x_pos_ = player_x_pos_ - (kScreenSizeX / kTwo) - static_cast<int>(kDelayLeft * (player_x_pos_ - target_x_pos_));
  }
  else {
    //進行方向が右向きの場合
    target_x_pos_ = player_x_pos_ - (kScreenSizeX / kTwo) + static_cast<int>(kDelayRight * (player_x_pos_ - target_x_pos_));
  }

  //target_x_pos_がフィールド端から出る位置にある場合、target_x_pos_をフィールドの範囲内に調整する
  if (target_x_pos_ < 0) {
    target_x_pos_ = 0;
  }
  else if (target_x_pos_ > (kTotalColumn) * kMapSize - kScreenSizeX + kRangeChange) {
    target_x_pos_ = (kTotalColumn) * kMapSize - kScreenSizeX + kRangeChange;
  }

  // フィールドの描画X位置を調整するための整数を目標位置に向かって少しずつずらす
  //進行方向が左向きの場合
  if (is_turn_) {
    if ((difference_x_pos_ > target_x_pos_)) {
      difference_x_pos_ = static_cast<int>(difference_x_pos_ + (target_x_pos_ - difference_x_pos_) * time * kTwo);
    }
  }
  else {
    //進行方向が右向きの場合
    if ((difference_x_pos_ < target_x_pos_)) {
      difference_x_pos_ = static_cast<int>(difference_x_pos_ + (target_x_pos_ - difference_x_pos_) * time * kTwo);
    }
  }

  //DEBUG_PRINT_VAR(player_x_pos_);
  //DEBUG_PRINT_VAR(target_x_pos_);
  //DEBUG_PRINT_VAR(difference_x_pos_);

}

/// <summary>
/// RenderFrame関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void Camera::RenderFrame() {

}

/// <summary>
/// SetPlayerXPos関数の定義
/// </summary>
/// <param = "player_x_pos">プレイヤーのX位置</param>
/// <returns>なし</returns>
void Camera::SetPlayerXPos(int player_x_pos) {
  player_x_pos_ = player_x_pos;
}

/// <summary>
/// SetDifferenceXpos関数の定義
/// </summary>
/// <param>フィールドの描画X位置を調整するための整数</param>
/// <returns>なし</returns>
void Camera::SetDifferenceXpos(int difference_x_pos) {
  difference_x_pos_ = difference_x_pos;
}

/// <summary>
/// GetDifferenceXpos関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>フィールドの描画X位置を調整するための整数</returns>
int Camera::GetDifferenceXpos() {
  return difference_x_pos_;
}

/// <summary>
/// SetPlayerTurned関数の定義
/// </summary>
/// <param = "is_dash">プレイヤーがダッシュしたかの有無</param>
/// <returns>なし</returns>
void Camera::SetPlayerTurned(bool is_dash) {
  is_turn_ = is_dash;
}