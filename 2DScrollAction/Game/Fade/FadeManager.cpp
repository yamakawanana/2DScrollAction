#include "DxLib.h"
#include "Game/Fade/FadeManager.h"
#include "Game/GameInfo/GameInfo.h"
#include "System/Math/Math.h"

/// <summary>
/// FadeManager.cpp内でのみ使用する定数
/// </summary>
namespace {

  /// <summary>
  /// フェード用黒画像のファイルパス
  /// </summary>
  //const char* kBlackImageFilePath = "Assets/Image/black.png";

  /// <summary>
  /// フェード用画像のスケール値（十分に画面が隠れるサイズ）
  /// </summary>
  const double kFadeImageScale = 40.0;

  /// <summary>
  /// フェード用画像のアルファの最大値
  /// </summary>
  const int kFadeImageMaxAlpha = 255;

  /// <summary>
  //黒色の値を取得
  /// <summary>
  unsigned int Cr = GetColor(0, 0, 0);

}

//FadeManagerのインスタンス初期化
FadeManager* FadeManager::instance_ = nullptr;

/// <summary>
/// コンストラクタ
/// </summary>
FadeManager::FadeManager()
  : fade_state_(FadeState::kNone)
  , black_image_handle_(0)
  , current_fade_time_(0.0f)
  , target_fade_time_(0.0f)
  , current_fade_alpha_(0)
  , fade_image_pos_x_(0)
  , fade_image_pos_y_(0)
  , fade_(0)
  , display_accumulation_time_(0.0f)
{
}

/// <summary>
/// デストラクタ
/// </summary>
FadeManager::~FadeManager() {
}

/// <summary>
/// フェードマネージャーの初期化
/// </summary>
void FadeManager::InitFadeManager() {

  //フェード用黒画像の読み込み
  //black_image_handle_ = LoadGraph(kBlackImageFilePath);

  //ゲーム情報から座標を取得
  GameInfo* game_info = GameInfo::GetInstance();
  fade_image_pos_x_ = game_info->GetCenterX();
  fade_image_pos_y_ = game_info->GetCenterY();
}

/// <summary>
/// フェードマネージャーの後処理
/// </summary>
void FadeManager::FinFadeManager() {

  //フェード用黒画像の破棄
  DeleteGraph(black_image_handle_);

}

/// <summary>
/// フェードマネージャーの更新
/// </summary>
/// <param name="delta_time">前回実行フレームからの経過時間（秒）</param>
void FadeManager::UpdateFadeManager(float delta_time) {

  //フェード処理していないなら終了
  if (fade_state_ == FadeState::kNone) {
    return;
  }

  //フェード時間を計測
  current_fade_time_ += delta_time;

  //経過時間を0～1の割合にする
  float time_rate = current_fade_time_ / target_fade_time_;

  //フェードアウト中
  if (fade_state_ == FadeState::kWaitFadeOut) {

    //フェードアウト時間経過した
    if (current_fade_time_ >= target_fade_time_) {

      //アルファ値を最大に
      current_fade_alpha_ = kFadeImageMaxAlpha;

      //状態を待機に
      fade_state_ = FadeState::kNone;
    }
    //まだ時間経過していない
    else {

      //線形補間でアルファ値を算出
      current_fade_alpha_  = static_cast<int>(Math::Lerp(0, kFadeImageMaxAlpha, time_rate));
      //current_fade_alpha_ = static_cast<int>(kFadeImageMaxAlpha + time_rate * (0 - kFadeImageMaxAlpha));
    }
  }
  //フェードイン中
  else if (fade_state_ == FadeState::kWaitFadeIn) {

    //フェードイン時間経過した
    if (current_fade_time_ >= target_fade_time_) {

      //アルファ値をゼロに
      current_fade_alpha_ = 0;

      //状態を待機に
      fade_state_ = FadeState::kNone;

    }
    //まだ時間経過していない
    else {

      //経過時間から現在のアルファ値を計算
      //current_fade_alpha_ = static_cast<int>(kFadeImageMaxAlpha - kFadeImageMaxAlpha * (target_fade_time_ / current_fade_time_));

      //current_fade_alpha_ = static_cast<int>(kFadeImageMaxAlpha + time_rate * (0 - kFadeImageMaxAlpha));

      //線形補間でアルファ値を算出
      current_fade_alpha_ = static_cast<int>(Math::Lerp(kFadeImageMaxAlpha, 0, time_rate));
      //DEBUG_PRINT_VAR(current_fade_alpha_);
    }
  }
}

/// <summary>
/// フェードマネージャーの描画
/// </summary>
void FadeManager::RenderFadeManager() {
  //DEBUG_PRINT(フェードマネージャーの描画);

  //ブレンドモードを透過に設定
  SetDrawBlendMode(DX_BLENDMODE_ALPHA, current_fade_alpha_);

  //案内画像描画
  //DrawRotaGraph(0, 0, 1, 0.0, black_image_handle_, TRUE);
  DrawGraph(0, 0, black_image_handle_, TRUE);

  //ブレンドモードを通常に戻す
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

/// <summary>
/// フェードアウト開始
/// </summary>
/// <param name="time">フェードアウトにかける時間</param>
void FadeManager::BeginFadeOut(float time) {

  //フェードアウトにかける時間を設定
  target_fade_time_ = time;

  //フェード時間をクリア
  current_fade_time_ = 0.0f;

  //初期アルファ値を設定
  current_fade_alpha_ = 0;

  //状態をフェードアウト待ちに
  fade_state_ = FadeState::kWaitFadeOut;
}

/// <summary>
/// フェードアウトは終了したか
/// </summary>
/// <returns>終了しているならtrue</returns>
bool FadeManager::IsEndFadeOut() {

  return fade_state_ == FadeState::kNone;
}

/// <summary>
/// フェードイン開始
/// </summary>
/// <param name="time">フェードインにかける時間</param>
void FadeManager::BeginFadeIn(float time) {
  DEBUG_PRINT(フェードイン開始);

  //フェードインにかける時間を設定
  target_fade_time_ = time;

  //フェード時間をクリア
  current_fade_time_ = 0.0f;

  //アルファ値を設定
  current_fade_alpha_ = kFadeImageMaxAlpha;

  //状態をフェードイン待ちに
  fade_state_ = FadeState::kWaitFadeIn;
}

/// <summary>
/// フェードインは終了したか
/// </summary>
/// <returns>終了しているならtrue</returns>
bool FadeManager::IsEndFadeIn() {
  DEBUG_PRINT(フェードインは終了したか);

  return fade_state_ == FadeState::kNone;
}

/// <summary>
/// フェードイン表示する関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void FadeManager::FadeIn(int x, int y, int size_x, int size_y, int fade, int plus_alpha) {

  //DEBUG_PRINT(フェードイン開始);

  int alpha = plus_alpha * fade;
  //DEBUG_PRINT_VAR(alpha);

  SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
  DrawBox(x, y, size_x, size_y, Cr, TRUE);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

/// <summary>
/// 指定の画像をフェード表示する関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "gr_handle">グラフィックハンドル</param>
/// <param = "fade">アルファ値の増減に使用する定数</param>
/// <param = "plus_alpha">アルファ値の増減に使用する定数</param>
/// <returns>なし</returns>
void FadeManager::FadeImage(int x, int y, int gr_handle, int fade, int plus_alpha) {

  int alpha = plus_alpha * fade;
  //DEBUG_PRINT_VAR(alpha);

  SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
  DrawGraph(x, y, gr_handle, TRUE);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

/// <summary>
/// 指定の画像を角度を変えてフェード表示する関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "ext_rate">拡大率</param>
/// <param = "angle">描画角度</param>
/// <param = "gr_handle">グラフィックハンドル</param>
/// <param = "fade">アルファ値の増減に使用する定数</param>
/// <param = "plus_alpha">アルファ値の増減に使用する定数</param>
/// <returns>なし</returns>
void FadeManager::FadeRotaGraph(int x, int y, double ext_rate, double angle, int gr_handle, int fade, int plus_alpha) {

  int alpha = plus_alpha * fade;
  //DEBUG_PRINT_VAR(alpha);

  SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
  DrawRotaGraph(x, y, ext_rate, angle, gr_handle, TRUE, TRUE);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}