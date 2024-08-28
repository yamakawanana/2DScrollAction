#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "System/Task/Task.h"
#include "DxLib.h"

/// <summary>
/// TaskManagerクラス
/// </summary>
class TaskManager {
public:

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  TaskManager();

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~TaskManager();

  /// <summary>
  /// AddTask関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>成功したらtrue、失敗したらfalse</returns>
  bool AddTask(Task* task);

  /// <summary>
  /// UnloadTask関数の宣言
  /// </summary>
  /// <param name = "id">TaskId型のid</param>
  /// <returns>なし</returns>
  Task* UnloadTask(Task::TaskId id);

  /// <summary>
  /// UpdateTask関数の宣言
  /// </summary>
  /// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
  /// <returns>なし</returns>
  void UpdateTask(float time);

  /// <summary>
  /// Render関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void RenderTask();

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// <summary>
  /// タスクリスト
  /// </summary>
  std::map<Task::TaskId, Task*> task_list_;

  /// <summary>
  /// 追加するタスクのタスクリスト
  /// </summary>
  std::map<Task::TaskId, Task*> add_task_list_;

  /// <summary>
  /// 降ろすタスクのタスクIDリスト
  /// </summary>
  std::vector<Task::TaskId> unload_task_list_;

  /// <summary>
  /// 毎フレーム更新処理中かの有無
  /// </summary>
  bool is_updating_;
};