#pragma once
#include "System/Task/Task.h"

/// <summary>
/// Cameraクラス
/// </summary>
class Camera : public Task {
public:

  /// <summary>
  /// デフォルトコンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Camera();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Camera(TaskId task_id);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~Camera();

  /// <summary>
  /// 毎フレーム更新処理
  /// </summary>
  /// <param name="time">最後のフレームを完了するのに要した時間 (秒)</param>
  /// <returns>なし</returns>
  void UpdateFrame(float time) override;

  /// <summary>
  /// RenderFrame関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void RenderFrame() override;

  /// <summary>
  /// SetPlayerXPos関数の宣言
  /// </summary>
  /// <param = "player_x_pos">プレイヤーのX位置</param>
  /// <returns>なし</returns>
  void SetPlayerXPos(int player_x_pos);

  /// <summary>
  /// SetDifferenceXpos関数の宣言
  /// </summary>
  /// <param = "difference_x_pos">フィールドの描画X位置を調整するための整数</param>
  /// <returns>なし</returns>
  void SetDifferenceXpos(int difference_x_pos);

  /// <summary>
  /// GetDifferenceXpos関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>フィールドの描画X位置を調整するための整数</returns>
  int GetDifferenceXpos();

  /// <summary>
  /// SetPlayerTurned関数の宣言
  /// </summary>
  /// <param = "is_turn">プレイヤーが逆行したかの有無</param>
  /// <returns>なし</returns>
  void SetPlayerTurned(bool is_turn);

protected:
  /// <summary>
  /// メンバ変数
  /// </summary>


private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// <summary>
  /// フィールドの描画X位置を調整するための整数
  /// </summary>
  int difference_x_pos_;

  /// <summary>
  /// プレイヤーのX位置
  /// </summary>
  int player_x_pos_;

  /// <summary>
  /// 目標X位置
  /// </summary>
  int target_x_pos_;

  /// <summary>
  /// プレイヤーが逆行したかの有無
  /// </summary>
  bool is_turn_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float display_accumulation_time_;
};

