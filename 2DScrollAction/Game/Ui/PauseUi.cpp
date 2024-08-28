#include <iostream>
#include "Game/Ui/PauseUi.h"
#include "Game/GameInfo/GameInfo.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {

}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
PauseUi::PauseUi(TaskId task_id, int pause_gr_handle)
  : Task(task_id)
  , gr_handle_(pause_gr_handle)
  , accumulation_time_(0.0f)
  , now_phase_(kPreDisplay)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
{
  //DEBUG_PRINT(PauseUiのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
PauseUi::~PauseUi() {
  //DEBUG_PRINT(PauseUiのデストラクタ);
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void PauseUi::InitPauseUi(int gr_handle) {
  //DEBUG_PRINT(PauseUiクラスの初期化処理);
}

/// <summary>
/// 毎フレーム更新処理　UpdateFrame関数の定義
/// </summary>
/// <param name="time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
/// <returns>なし</returns>
void PauseUi::UpdateFrame(float time) {
  //DEBUG_PRINT(PauseUiクラスの毎フレーム更新処理);
  //accumulation_time_ = accumulation_time_ + time;

}

/// 毎フレーム描画処理
/// </remarks>
/// <param>なし</param>
/// <returns>なし</returns>
void PauseUi::RenderFrame() {
  //DEBUG_PRINT(Playerの毎フレーム描画処理);

  if (now_phase_ == kDisplay) {
    //ゲーム情報を取得する
    GameInfo* game_info = GameInfo::GetInstance();

    //画面の中心の位置を取得する
    int left_x = game_info->GetCenterX();
    int left_y = game_info->GetCenterY();

    //画面の中心の座標から画像の大きさの半分の長さを引いた位置にタイトルロゴを表示する
    DrawGraph(static_cast<int>(left_x - half_width_), static_cast<int>(left_y - half_height_), gr_handle_, TRUE);
  }

}

/// <summary>
/// GetGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int PauseUi::GetGrHandle() {
  return gr_handle_;
}

/// <summary>
/// SetGrHandle関数の定義
/// </summary>
/// <param = "gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void PauseUi::SetGrHandle(int gr_handle) {
  gr_handle_ = gr_handle;
}

/// <summary>
/// SetWidth関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void PauseUi::SetWidth(int size_x) {
  width_ = size_x;
}

/// <summary>
/// GetWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int PauseUi::GetWidth() {
  return width_;
}

/// <summary>
/// SetHeight関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void PauseUi::SetHeight(int size_y) {
  height_ = size_y;
}

/// <summary>
/// GetHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さ</returns>
int PauseUi::GetHeight() {
  return height_;
}

/// <summary>
/// SetHalfWidth関数の定義
/// </summary>
/// <param>画像の幅の半分</param>
/// <returns>なし</returns>
void PauseUi::SetHalfWidth(float size_half_x) {
  half_width_ = size_half_x;
}

/// <summary>
/// GetHalfWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅の半分</returns>
float PauseUi::GetHalfWidth() {
  return half_width_;
}

/// <summary>
/// SetHalfHeight関数の定義
/// </summary>
/// <param>画像の高さの半分</param>
/// <returns>なし</returns>
void PauseUi::SetHalfHeight(float size_half_y) {
  half_height_ = size_half_y;
}

/// <summary>
/// GetHalfHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さの半分</returns>
float PauseUi::GetHalfHeight() {
  return half_height_;
}

/// <summary>
/// SetPhaseType関数の定義
/// </summary>
/// <param = "type">方向の種類</param>
/// <returns>なし</returns>
void PauseUi::SetPhaseType(PhaseType type) {
  now_phase_ = type;
}

/// <summary>
/// GetPhaseType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
PauseUi::PhaseType PauseUi::GetPhaseType() {
  return now_phase_;
}