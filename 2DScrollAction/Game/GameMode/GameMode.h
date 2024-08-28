#pragma once
#include "System/Task/Task.h"

/// <summary>
/// GameModeクラス
/// </summary>
class GameMode : public Task {
public:

  /// <summary>
  /// 制限時間を定数kTimeLimitに格納する
  /// </summary>
  static const int kTimeLimit = 30;

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  GameMode(TaskId task_id);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~GameMode();

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// <summary>
  /// ゲームクリアかの有無
  /// </summary>
  bool game_clear_;
};

