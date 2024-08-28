#include <iostream>
#include "System/Task/TaskManager.h"
#include "System/Task/Task.h"
#include "System/LogConsole/LogConsole.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  //====================================================
  //白色の値を取得
  //====================================================
  unsigned int Cr = GetColor(255, 255, 255);

  /// <summary>
  //DrawString関数のX座標を定数kXcoordinateに格納する
  /// <summary>
  static const int kXcoordinate = 250;

  /// <summary>
  //TaskManagerのコンストラクタのDrawString関数のY座標を定数kYTaskManaConstructorに格納する
  /// <summary>
  static const int kYTaskManaConstructor = 110;

  /// <summary>
  //TaskManagerのデストラクタのDrawString関数のY座標を定数kYTaskManaDestructorに格納する
  /// <summary>
  static const int kYTaskManaDestructor = 300;

  /// <summary>
  //TaskManagerクラスの毎フレーム更新処理のDrawString関数のY座標を定数kYTaskManaUpdateに格納する
  /// <summary>
  static const int kYTaskManaUpdate = 180;

  /// <summary>
  //TaskManagerクラスの毎フレーム描画処理のDrawString関数のY座標を定数kYTaskManaRenderに格納する
  /// <summary>
  static const int kYTaskManaRender = 220;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
TaskManager::TaskManager()
//メンバ変数を初期化する
  : task_list_()
  , add_task_list_()
  , unload_task_list_()
  , is_updating_(false)
{
  //DrawString(kXcoordinate, kYTaskManaConstructor, "TaskManagerのコンストラクタ", Cr);
  DEBUG_PRINT(TaskManagerのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
TaskManager::~TaskManager() {
  //DrawString(kXcoordinate, kYTaskManaDestructor, "TaskManagerのデストラクタ", Cr);
  DEBUG_PRINT(TaskManagerのデストラクタ);
}

/// <summary>
/// AddTask関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>成功したらtrue、失敗したらfalse</returns>
bool TaskManager::AddTask(Task* task) {

  //====================================================
  //タスクの降ろす設定をリセットする
  //====================================================
  task->ResetTaskUnload();

  //====================================================
  //毎フレーム更新処理中の時には
  //追加するタスクリストに
  //タスクを積む（追加する）
  //====================================================
  if (is_updating_) {
    add_task_list_[task->GetId()] = task;
    DEBUG_PRINT(追加するタスクリストにタスクを積んだ);
    DEBUG_PRINT_VAR(task->GetId());
    DEBUG_PRINT_VAR(task);
  }
  //====================================================
  //毎フレーム更新処理実行中でないなら、
  //タスクを積む（追加する）
  //====================================================
  else {
    task_list_[task->GetId()] = task;
    DEBUG_PRINT(タスクリストにタスクを積んだ);
    DEBUG_PRINT_VAR(task->GetId());
    DEBUG_PRINT_VAR(task);
  }
  return true;
}

/// <summary>
/// UnloadTask関数の定義
/// </summary>
/// <param name = "id">std::string型のid</param>
/// <returns>なし</returns>
Task* TaskManager::UnloadTask(Task::TaskId id) {

  if (id >= Task::kTaskMax || id < 0) {
    DEBUG_PRINT_VAR(id);
    DEBUG_PRINT(タスクが不正値);
    return nullptr;
  }

  //タスクが存在しない場合、処理しない
  if (task_list_.find(id) == task_list_.end()) {
    DEBUG_PRINT(タスクが存在しない);
    return nullptr;
  }

  //====================================================
  //タスクを取得する
  //====================================================
  Task* task = task_list_[id];
  DEBUG_PRINT_VAR(id);

  //====================================================
  //タスクに解放を設定する
  //====================================================
  task->SetTaskUnload();

  //====================================================
  //毎フレーム更新処理中の時には
  //降ろすタスクリストに
  //タスクを積む（追加する）
  //====================================================
  if (is_updating_) {
    unload_task_list_.push_back(id);
    //DEBUG_PRINT(毎フレーム更新処理中なので降ろすタスクリストに);
  }
  //====================================================
  //毎フレーム更新処理実行中でないなら、
  //タスクを降ろす
  //====================================================
  else {
    task_list_.erase(id);
    DEBUG_PRINT(タスクを降ろした);
  }
  return task;
}

/// <summary>
/// UpdateTask関数の定義
/// </summary>
/// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
/// <returns>なし</returns>
void TaskManager::UpdateTask(float time) {
  //DrawString(kXcoordinate, kYTaskManaUpdate, "TaskManagerクラスの毎フレーム更新処理", Cr);
  //DEBUG_PRINT(TaskManagerクラスの毎フレーム更新処理);

  //====================================================
  //毎フレーム更新処理中の有無に有りを設定する
  //====================================================
    is_updating_ = true;

    //====================================================
    //積んでいるタスク全部の１フレームの更新処理を実行する
    //====================================================
    for (auto it = task_list_.begin(); it != task_list_.end(); ++it) {
      //DEBUG_PRINT_VAR(it->second);
      //====================================================
      //タスクが解放設定になっていないなら、
      //毎フレーム更新処理を実行する
      //====================================================
      if (!it->second->GetTaskUnload()) {
        it->second->UpdateFrame(time);
      }
    }
    //====================================================
    //更新処理が終わったら、毎フレーム更新処理中の有無に無しを設定する
    //====================================================
    is_updating_ = false;

    //====================================================
    //追加のタスクリストにあるタスクをタスクリストに追加する
    //====================================================
    for (auto it = add_task_list_.begin(); it != add_task_list_.end(); ++it) {
      task_list_[it->second->GetId()] = it->second;
      //DEBUG_PRINT(追加のタスクリストにあるタスクをタスクリストに追加する);
      DEBUG_PRINT_VAR(it->second);
    }
    //追加のタスクリストをクリアする
    add_task_list_.clear();

    //====================================================
    //降ろすタスクリストにあるタスクをタスクリストから解放する
    //====================================================
    for (auto task_id : unload_task_list_) {
      task_list_.erase(task_id);
      //DEBUG_PRINT(降ろすタスクリストにあるタスクをタスクリストから解放する);
      DEBUG_PRINT_VAR(task_id);
    }
    //降ろすタスクリストをクリアする
    unload_task_list_.clear();
}

/// <summary>
/// RenderTask関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void TaskManager::RenderTask() {
  //DrawString(kXcoordinate, kYTaskManaRender, "TaskManagerクラスの毎フレーム描画処理", Cr);
  //DEBUG_PRINT(TaskManagerクラスの毎フレーム描画処理);

  //====================================================
  //積んでいるタスク全部の１フレームの描画処理を実行する
  //====================================================
  for (auto it = task_list_.begin(); it != task_list_.end(); ++it) {
      //====================================================
      //タスクが解放設定になっていないなら、
      //毎フレームの描画処理を実行する
      //====================================================
    if (!it->second->GetTaskUnload()) {
      it->second->RenderFrame();
    }
  }
}