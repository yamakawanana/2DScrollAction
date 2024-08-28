#include <iostream>
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
  //TaskのコンストラクタのDrawString関数のY座標を定数kYTaskConstructorに格納する
  /// <summary>
  static const int kYTaskConstructor = 140;

  /// <summary>
  //TaskのデストラクタのDrawString関数のY座標を定数kYTaskDestructorに格納する
  /// <summary>
  static const int kYTaskDestructor = 270;

  /// <summary>
  //Taskクラスの毎フレーム更新処理のDrawString関数のY座標を定数kYTaskUpdateに格納する
  /// <summary>
  static const int kYTaskUpdate = 200;

  /// <summary>
  //Taskクラスの毎フレーム描画処理のDrawString関数のY座標を定数kYTaskRenderに格納する
  /// <summary>
  static const int kYTaskRender = 240;

  // <summary>
  //taskクラスに設定するIDの定数kFirstIdを用意する
  /// <summary>
  static const int kFirstId = 1;
}

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Task::Task()
//メンバ変数を初期化する
  : id_(kNone)
  , task_unload_(false)
{
  //DrawString(kXcoordinate, kYTaskConstructor, "Taskのコンストラクタ", Cr);

  DEBUG_PRINT(Taskのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Task::Task(TaskId task_id)
//メンバ変数を初期化する
  : id_(task_id)
  , task_unload_(false)
{
  //DrawString(kXcoordinate, kYTaskConstructor, "Taskのコンストラクタ", Cr);

  DEBUG_PRINT(Taskのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Task::~Task()
{
  //DrawString(kXcoordinate, kYTaskDestructor, "Taskのデストラクタ", Cr);
  DEBUG_PRINT(Taskのデストラクタ);
}

/// <summary>
/// GetId関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>id_</returns>
Task::TaskId Task::GetId() {
  return id_;
}

/// <summary>
/// SetId関数の定義
/// </summary>
/// <param name = "id">TaskId型のid</param>
/// <returns>なし</returns>
void Task::SetId(TaskId id) {
  id_ = id;
}

/// <summary>
/// GetTaskUnload関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>task_unload_</returns>
bool Task::GetTaskUnload() {
  return task_unload_;
}

/// <summary>
/// SetTaskUnload関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void Task::SetTaskUnload() {
  task_unload_ = true;
}

/// <summary>
/// ResetTaskUnload関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void Task::ResetTaskUnload() {
  task_unload_ = false;
}

/// <summary>
/// UpdateFrame関数の定義
/// </summary>
/// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
/// <returns>なし</returns>
void Task::UpdateFrame(float time) {
  //DrawString(kXcoordinate, kYTaskUpdate, "Taskクラスの毎フレーム更新処理", Cr);
  //DEBUG_PRINT(Taskクラスの毎フレーム更新処理);
}

/// <summary>
/// RenderFrame関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void Task::RenderFrame() {
  //DrawString(kXcoordinate, kYTaskRender, "Taskクラスの毎フレーム描画処理", Cr);
  //DEBUG_PRINT(Taskクラスの毎フレーム描画処理);
}