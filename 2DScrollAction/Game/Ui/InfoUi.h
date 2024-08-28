#pragma once
#include "System/Task/Task.h"
#include "System/Task/TaskManager.h"
#include <array>

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// カウントダウンのグラフィックハンドルの配列の要素数を定数kElementNumberに格納する
  /// </summary>
  static const int kElementNumber = 10;

  /// <summary>
  /// タイムアップのグラフィックハンドルの配列の要素数を定数kTimeUpElementNumberに格納する
  /// </summary>
  static const int kTimeUpElementNumber = 4;

  /// <summary>
  /// 星が流れるエフェクトの画像の横向きの分割数を定数kStarFlowEffectXに格納する
  /// </summary>
  static const int kStarFlowEffectX = 6;

  /// <summary>
  /// 星が流れるエフェクトの画像の縦向きの分割数を定数kStarFlowEffectYに格納する
  /// </summary>
  static const int kStarFlowEffectY = 2;

  /// <summary>
  /// ステージとプレイヤー数を表示するの画像の横向きの分割数を定数kPlayerNumXに格納する
  /// </summary>
  static const int kPlayerNumX = 9;
}

/// <summary>
/// InfoUiクラス
/// </summary>
class InfoUi : public Task {
public:

  /// <summary>
  /// フェーズの種類
  /// </summary>
  enum PhaseType {
    /// <summary>
    /// 準備中
    /// </summary>
    kPreraration,

    /// <summary>
    /// プレイヤーの数表示
    /// </summary>
    kDisplayPlayerNum,

    /// <summary>
    /// フェード
    /// </summary>
    kFade,

    /// <summary>
    /// プレイ中
    /// </summary>
    kPlaying,

    /// <summary>
    /// プレイ中断
    /// </summary>
    kStop,

    /// <summary>
    /// ステージクリア
    /// </summary>
    kStageClear,

    /// <summary>
    /// 終了フェーズ
    /// </summary>
    kFinish,

    /// <summary>
    /// フェーズの種類の最大数
    /// </summary>
    kMax,
  };

  /// <summary>
  /// 星のエフェクト表示の種類
  /// </summary>
  enum StarEffectType {
    /// <summary>
    /// なし
    /// </summary>
    kEffectNone,

    /// <summary>
    /// HPが2になった
    /// </summary>
    kHpTwo,

    /// <summary>
    /// HPが3になった
    /// </summary>
    kHpThree,

    /// <summary>
    /// HPが4になった
    /// </summary>
    kHpFour,

    /// <summary>
    /// 最大数
    /// </summary>
    kEffectMax,
  };

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  InfoUi(TaskId task_id, std::array<int, kElementNumber> countdown_handle, std::array<int, kElementNumber> ten_countdown_handle, std::array<int, kTimeUpElementNumber> timeup_handle, std::array<int, kStarFlowEffectX* kStarFlowEffectY> star_effect_gr_handle, std::array<int, kStarFlowEffectX* kStarFlowEffectY> big_star_effect_gr_handle, std::array<int, kPlayerNumX> player_num_gr_handle, int stage_num, std::array<int, kElementNumber> game_clear_handle);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~InfoUi();

  /// <summary>
  /// 毎フレーム更新処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>なし</returns>
  void UpdateFrame(float time) override;

  /// 毎フレーム描画処理
  /// </remarks>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void RenderFrame() override;

  /// <summary>
  /// GetGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>グラフィックハンドル</returns>
  int GetGrHandle(int element_num);

  /// <summary>
  /// SetGrHandle関数の宣言
  /// </summary>
  /// <param = "gr_handle">グラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetGrHandle(int gr_handle);

  /// <summary>
  /// GetTenGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>10秒前カウントのグラフィックハンドル</returns>
  int GetTenGrHandle(int element_num);

  /// <summary>
  /// SetTenGrHandle関数の宣言
  /// </summary>
  /// <param = "ten_gr_handle">10秒前カウントのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetTenGrHandle(int ten_gr_handle);

  /// <summary>
  /// GetTimeUpGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>タイムアップ画像のグラフィックハンドル</returns>
  int GetTimeUpGrHandle(int element_num);

  /// <summary>
  /// SetTimeUpGrHandle関数の宣言
  /// </summary>
  /// <param = "gr_handle">タイムアップ画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetTimeUpGrHandle(int gr_handle);

  /// <summary>
  /// GetWatchGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>時計のグラフィックハンドル</returns>
  int GetWatchGrHandle();

  /// <summary>
  /// SetWatchGrHandle関数の宣言
  /// </summary>
  /// <param = "watch_gr_handle">時計のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetWatchGrHandle(int watch_gr_handle);

  /// <summary>
  /// GetHpOneGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>HP1の時の表示のグラフィックハンドル</returns>
  int GetHpOneGrHandle();

  /// <summary>
  /// SetHpOneGrHandle関数の宣言
  /// </summary>
  /// <param = "hp_one_handle">HP1の時の表示のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetHpOneGrHandle(int hp_one_handle);

  /// <summary>
  /// GetHpTwoGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>HP2の時の表示のグラフィックハンドル</returns>
  int GetHpTwoGrHandle();

  /// <summary>
  /// SetHpTwoGrHandle関数の宣言
  /// </summary>
  /// <param = "hp_two_handle">HP2の時の表示のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetHpTwoGrHandle(int hp_two_handle);

  /// <summary>
  /// GetHpThreeGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>HP3の時の表示のグラフィックハンドル</returns>
  int GetHpThreeGrHandle();

  /// <summary>
  /// SetHpThreeGrHandle関数の宣言
  /// </summary>
  /// <param = "hp_three_handle">HP3の時の表示のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetHpThreeGrHandle(int hp_three_handle);

  /// <summary>
  /// GetHpFourGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>HP4の時の表示のグラフィックハンドル</returns>
  int GetHpFourGrHandle();

  /// <summary>
  /// SetHpFourGrHandle関数の宣言
  /// </summary>
  /// <param = "hp_four_handle">HP4の時の表示のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetHpFourGrHandle(int hp_four_handle);

  /// <summary>
  /// SetCountdown関数の宣言
  /// </summary>
  /// <param = "countdown">カウントダウンの値</param>
  /// <returns>なし</returns>
  void SetCountdown(int countdown);

  /// <summary>
  /// SetWidth関数の宣言
  /// </summary>
  /// <param>画像の幅</param>
  /// <returns>なし</returns>
  void SetWidth(int size_x);

  /// <summary>
  /// GetWidth関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の幅</returns>
  int GetWidth();

  /// <summary>
  /// SetHeight関数の宣言
  /// </summary>
  /// <param>画像の高さ</param>
  /// <returns>なし</returns>
  void SetHeight(int size_y);

  /// <summary>
  /// GetHeight関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の高さ</returns>
  int GetHeight();

  /// <summary>
  /// SetHalfWidth関数の宣言
  /// </summary>
  /// <param>画像の幅</param>
  /// <returns>なし</returns>
  void SetHalfWidth(float size_half_x);

  /// <summary>
  /// GetHalfWidth関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の幅の半分</returns>
  float GetHalfWidth();

  /// <summary>
  /// SetHalfHeight関数の宣言
  /// </summary>
  /// <param>画像の高さ</param>
  /// <returns>なし</returns>
  void SetHalfHeight(float size_half_y);

  /// <summary>
  /// GetHalfHeight関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の高さの半分</returns>
  float GetHalfHeight();

  /// タイムアップを描画する
  /// </remarks>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void RenderTimeUp(float time);

  /// <summary>
  /// GetTimeUpRenderEnd関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>タイムアップのアニメーションが終わったかの有無</returns>
  bool GetTimeUpRenderEnd();

  /// <summary>
  /// フェードイン表示する関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "handle">グラフィックハンドル</param>
  /// <param = "is_transparent">透過の有無</param>
  /// <returns>なし</returns>
  void FadeIn(int x, int y, int handle, bool is_transparent, int fade_value);

  /// <summary>
  /// SetPlayerHp関数の宣言
  /// </summary>
  /// <param = "player_hp">プレイヤーのHP</param>
  /// <returns>なし</returns>
  void SetPlayerHp(int player_hp);

  /// <summary>
  /// GetPlayerHp関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>プレイヤーのHP</returns>
  int GetPlayerHp();

  /// <summary>
  /// SetPhaseType関数の宣言
  /// </summary>
  /// <param = "now_phase">現在のフェーズ</param>
  /// <returns>なし</returns>
  void SetPhaseType(PhaseType now_phase);

  /// <summary>
  /// GetPhaseType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>フェーズの種類</returns>
  PhaseType GetPhaseType();

  /// <summary>
  /// GetStarFlowGrHandle関数の宣言
  /// </summary>
  /// <param = "element_num">要素番号</param>
  /// <returns>星が流れるエフェクトのグラフィックハンドル</returns>
  int GetStarFlowGrHandle(int element_num);

  /// <summary>
  /// GetBigStarFlowGrHandle関数の宣言
  /// </summary>
  /// <param = "element_num">要素番号</param>
  /// <returns>大きい星が流れるエフェクトのグラフィックハンドル</returns>
  int GetBigStarFlowGrHandle(int element_num);

  /// <summary>
  /// GetStageClearGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ステージクリア画像のグラフィックハンドル</returns>
  int GetStageClearGrHandle();

  /// <summary>
  /// SetStageClearGrHandle関数の宣言
  /// </summary>
  /// <param = "stage_clear_handle">ステージクリア画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetStageClearGrHandle(int stage_clear_handle);

  /// <summary>
  /// GetPlayerNumGrHandle関数の宣言
  /// </summary>
  /// <param = "element_num">要素番号</param>
  /// <returns>ステージとプレイヤー数を表示する画像のグラフィックハンドル</returns>
  int GetPlayerNumGrHandle(int element_num);

  /// <summary>
  /// GetGameClearGrHandle関数の宣言
  /// </summary>
  /// <param = "element_num">要素番号</param>
  /// <returns>ゲームクリアのグラフィックハンドル</returns>
  int GetGameClearGrHandle(int element_num);

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// </summary>
  //現在のフェーズ
  /// </summary>
  PhaseType now_phase_;

  /// <summary>
  /// カウントダウンのグラフィックハンドル
  /// </summary>
  std::array<int, kElementNumber> countdown_gr_handle_;

  /// <summary>
  /// 10秒前カウントダウンのグラフィックハンドル
  /// </summary>
  std::array<int, kElementNumber> ten_countdown_gr_handle_;

  /// <summary>
  /// TimeUpのグラフィックハンドル
  /// </summary>
  std::array<int, kTimeUpElementNumber> timeup_gr_handle_;

  /// <summary>
  /// 星が流れるエフェクトのグラフィックハンドル
  /// </summary>
  std::array<int, kStarFlowEffectX* kStarFlowEffectY> star_effect_gr_handle_;

  /// <summary>
  /// 大きい星が流れるエフェクトのグラフィックハンドル
  /// </summary>
  std::array<int, kStarFlowEffectX* kStarFlowEffectY> big_star_effect_gr_handle_;

  /// <summary>
  /// ステージとプレイヤー数の表示のグラフィックハンドル
  /// </summary>
  std::array<int, kPlayerNumX> player_num_gr_handle_;

  /// <summary>
  /// 時計のグラフィックハンドル
  /// </summary>
  int watch_gr_handle_;

  /// <summary>
  /// HPが1の時のグラフィックハンドル
  /// </summary>
  int hp_one_handle_;

  /// <summary>
  /// HPが2の時のグラフィックハンドル
  /// </summary>
  int hp_two_handle_;

  /// <summary>
  /// HPが3の時のグラフィックハンドル
  /// </summary>
  int hp_three_handle_;

  /// <summary>
  /// HPが4の時のグラフィックハンドル
  /// </summary>
  int hp_four_handle_;

  /// <summary>
  /// ステージクリアのグラフィックハンドル
  /// </summary>
  int stage_clear_handle_;

  /// <summary>
  /// ゲームクリアのグラフィックハンドル
  /// </summary>
  std::array<int, kElementNumber> game_clear_handle_;

  /// <summary>
  /// カウントダウンのカウント
  /// </summary>
  int countdown_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float accumulation_time_;

  /// <summary>
  /// 画像の幅
  /// </summary>
  int width_;

  /// <summary>
  /// 画像の高さ
  /// </summary>
  int height_;

  /// <summary>
  /// 画像の幅の半分
  /// </summary>
  float half_width_;

  /// <summary>
  /// 画像の高さの半分
  /// </summary>
  float half_height_;

  /// <summary>
  /// タイムアップのアニメーションが終わったかの有無
  /// </summary>
  bool timeup_end_;

  /// <summary>
  /// プレイヤーのHP
  /// </summary>
  int player_hp_;

  /// <summary>
  /// 前回フレームでのプレイヤーHP
  /// </summary>
  int pre_player_hp_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float timeup_accumulation_time_;

  /// <summary>
  /// 星表示の累積時間（秒）
  /// </summary>
  float star_accumulation_time_;

  /// <summary>
  /// ゲームクリア表示の累積時間（秒）
  /// </summary>
  float game_clear_accumulation_time_;

  /// <summary>
  /// インデックス
  /// </summary>
  int index_;

  /// <summary>
  /// ゲームクリア表示で使うインデックス
  /// </summary>
  int clear_index_;

  /// <summary>
  /// エフェクト表示の種類
  /// </summary>
  StarEffectType star_effect_type;

  /// <summary>
  /// プレイヤーの残数
  /// </summary>
  int player_num_;

  /// <summary>
  /// 現在のステージ
  /// </summary>
  int stage_num_;
};
