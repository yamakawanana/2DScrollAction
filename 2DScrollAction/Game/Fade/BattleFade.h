#pragma once
#include "System/Task/Task.h"

/// <summary>
/// BattleFadeクラス
/// </summary>
class BattleFade : public Task {
public:

  /// <summary>
  /// デフォルトコンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  BattleFade();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  BattleFade(TaskId task_id);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~BattleFade();

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
  /// SetFade関数の宣言
  /// </summary>
  /// <param = "is_fade">フェードの有無</param>
  /// <returns>なし</returns>
  void SetFade(bool is_fade);

  /// <summary>
  /// GetFadeEnd関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>フェードが終わったかの有無</returns>
  bool GetFadeEnd();

protected:
  /// <summary>
  /// メンバ変数
  /// </summary>


private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// <summary>
  /// フェードイン・フェードアウトで使用する整数
  /// </summary>
  int fade_;

  /// </summary>
  // フェードの有無を受け取る変数
  /// </summary>
  bool is_fade_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float display_accumulation_time_;

  /// </summary>
  // フェードが終わったかの有無を受け取る変数
  /// </summary>
  bool is_fade_end_;

};
