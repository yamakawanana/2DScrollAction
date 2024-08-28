#pragma once
#include "System/Task/Task.h"
#include "System/Task/TaskManager.h"
#include "Game/Field/Field.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// スイカの画像の横向きの分割数を定数kWatermelonXに格納する
  /// </summary>
  static const int kWatermelonX = 17;

  /// <summary>
  /// アイテムをゲットした時のエフェクトの画像の横向きの分割数を定数kItemGetEffectXに格納する
  /// </summary>
  static const int kItemGetEffectX = 6;
}

/// <summary>
/// Itemクラス
/// </summary>
class Item : public Task {
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
    /// プレイ中
    /// </summary>
    kPlaying,

    /// <summary>
    /// プレイ中断
    /// </summary>
    kStop,

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
  /// 状態の種類
  /// </summary>
  enum StatusType {
    /// <summary>
    /// 存在する
    /// </summary>
    kExist,

    /// <summary>
    /// アイテムが消えるエフェクトを表示するフェーズ
    /// </summary>
    kEffect,

    /// <summary>
    /// 消えた
    /// </summary>
    kNone,
  };

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Item(Task task_id);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~Item();

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
  /// <param>要素番号</param>
  /// <returns>グラフィックハンドル</returns>
  int GetGrHandle(int element);

  /// <summary>
  /// SetGrHandle関数の宣言
  /// </summary>
  /// <param = "gr_handle">グラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetGrHandle(std::array<int, kWatermelonX> gr_handle);

  /// <summary>
  /// GetEffectGrHandle関数の宣言
  /// </summary>
  /// <param>要素番号</param>
  /// <returns>アイテムをゲットしたエフェクトのグラフィックハンドル</returns>
  int GetEffectGrHandle(int element);

  /// <summary>
  /// SetEffectGrHandle関数の宣言
  /// </summary>
  /// <param = "get_effect_gr_handle">アイテムをゲットしたエフェクトのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetEffectGrHandle(std::array<int, kItemGetEffectX> get_effect_gr_handle);

  /// <summary>
  /// SetPhaseType関数の宣言
  /// </summary>
  /// <param = "type">フェーズの種類</param>
  /// <returns>なし</returns>
  void SetPhaseType(PhaseType type);

  /// <summary>
  /// GetPhaseType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>フェーズの種類</returns>
  PhaseType GetPhaseType();

  /// <summary>
  /// SetStatusType関数の宣言
  /// </summary>
  /// <param = "type">状態の種類</param>
  /// <returns>なし</returns>
  void SetStatusType(StatusType type);

  /// <summary>
  /// GetStatusType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>状態の種類</returns>
  StatusType GetStatusType();

  /// <summary>
  /// SetDifferenceXpos関数の宣言
  /// </summary>
  /// <param = "difference_x_pos">フィールドの描画X位置を調整するための整数</param>
  /// <returns>なし</returns>
  void SetDifferenceXpos(int difference_x_pos);

  /// <summary>
  /// SetXPosition関数の宣言
  /// </summary>
  /// <param = "x_coordinate">X座標</param>
  /// <returns>なし</returns>
  void SetXPosition(int x_coordinate);

  /// <summary>
  /// GetXPosition関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>X座標</returns>
  int GetXPosition();

  /// <summary>
  /// SetYPosition関数の宣言
  /// </summary>
  /// <param = "y_coordinate">Y座標</param>
  /// <returns>なし</returns>
  void SetYPosition(int y_coordinate);

  /// <summary>
  /// GetYPosition関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>Y座標</returns>
  int GetYPosition();

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// </summary>
  //現在のフェーズ
  /// </summary>
  PhaseType now_phase_;

  /// </summary>
  //アイテムの状態
  /// </summary>
  StatusType status_type_;

  /// <summary>
  /// グラフィックハンドル
  /// </summary>
  std::array<int, kWatermelonX> gr_handle_;

  /// <summary>
  /// アイテムをゲットした時のエフェクトのグラフィックハンドル
  /// </summary>
  std::array<int, kItemGetEffectX> get_effect_gr_handle_;

  /// <summary>
  /// 1フレームあたりのアニメーションの変化量
  /// </summary>
  float change_amount_;

  /// <summary>
  /// X座標
  /// </summary>
  int x_coordinate_;

  /// <summary>
  /// Y座標
  /// </summary>
  int y_coordinate_;

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
  /// 累積時間（秒）
  /// </summary>
  float accumulation_time_;

  /// <summary>
  /// アイテムをゲットしたエフェクトで使う累積時間（秒）
  /// </summary>
  float items_get_accumulation_time_;

  /// <summary>
  /// インデックス
  /// </summary>
  int index_;

  /// <summary>
  /// フィールドの描画X位置を調整するための整数
  /// </summary>
  int difference_x_pos_;

  /// <summary>
  /// エフェクト用のインデックス
  /// </summary>
  int effect_index_;
};


