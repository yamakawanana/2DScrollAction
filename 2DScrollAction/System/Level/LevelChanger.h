#pragma once
#include <array>
#include "System/Task/Task.h"
#include "System/Task/TaskManager.h"
#include "System/Level/Level.h"

/// <summary>
/// LevelChangerクラス
/// </summary>
class LevelChanger : public Task {
public:
  /// <summary>
  //フェーズの種類の列挙型PhaseType型を定義する
  /// <summary>
  enum PhaseType {
    /// <summary>
    /// 何もしない
    /// </summary>
    kNothing,

    /// <summary>
    /// 初期化フェーズ
    /// </summary>
    kInitialized,

    /// <summary>
    /// 処理フェーズ
    /// </summary>
    kProcessing,

    /// <summary>
    /// 終了フェーズ
    /// </summary>
    kEnding,

    /// <summary>
    /// 終了済みフェーズ
    /// </summary>
    kEnded,
  };


  /// <summary>
  //レベル遷移フェーズの種類の列挙型LevelTransitionType型を定義する
  /// <summary>
  enum LevelTransitionType {
    /// <summary>
    /// 何もしない
    /// </summary>
    kNone,

    /// <summary>
    /// 終了処理フェーズ
    /// </summary>
    kEndProcessing,

    /// <summary>
    /// 終了処理の終了フェーズ
    /// </summary>
    kEndEnding,

    /// <summary>
    /// 次のレベルの生成フェーズ
    /// </summary>
    kCreateNextLevel,

    /// <summary>
    /// 開始処理フェーズ
    /// </summary>
    kStartNextProcessing,

    /// <summary>
    /// 開始処理の終了フェーズ
    /// </summary>
    kEndingStartNextProcessing,

    /// <summary>
    /// 切り替え終了フェーズ
    /// </summary>
    kEndTransition,

    /// <summary>
    /// 処理終了
    /// </summary>
    kEnd,
  };


  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  LevelChanger();

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~LevelChanger();

  /// <summary>
  /// SetTaskManager関数の宣言
  /// </summary>
  /// <param = "task_manager">TaskManagerのポインタのtask_manager</param>
  /// <returns>なし</returns>
  void SetTaskManager(TaskManager* task_manager);

  /// <summary>
  /// UpdateFrame関数の宣言
  /// </summary>
  /// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
  /// <returns>なし</returns>
  void UpdateFrame(float time) override;

  /// <summary>
  /// RenderFrame関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void RenderFrame() override;

  /// <summary>
  /// EndLevelChanger関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void EndLevelChanger();

  /// <summary>
  /// CheckLevelChangerEnded関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>終了しているかの有無</returns>
  bool CheckLevelChangerEnded();

private:
  /// <summary>
  /// CreateLevelProcessing関数の宣言
  /// </summary>
  /// <param>生成するレベルのタスクID</param>
  /// <returns>レベル処理のポインタ</returns>
  Level* CreateLevelProcessing(TaskId task_id, Level* generate_level);

  /// <summary>
  /// 初期化処理のフェーズ処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool Initialize(float time);

  /// <summary>
  /// 毎フレーム更新処理のフェーズ処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool PhaseUpdate(float time);

  /// <summary>
  /// 終了処理のフェーズ処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool Finalize(float time);

  /// <summary>
  /// メンバ変数
  /// </summary>

  /// </summary>
  //タスクマネージャーのポインタ
  /// </summary>
  TaskManager* task_manager_;

  /// </summary>
  //フェーズの種類
  /// </summary>
  PhaseType phase_type_;

  /// </summary>
  //レベル遷移フェーズの種類
  /// </summary>
  LevelTransitionType level_transition_;

  /// </summary>
  //処理中のレベルのポインタ
  /// </summary>
  Level* level_;

  /// </summary>
  //次に遷移するレベルのタスクID
  /// </summary>
  TaskId task_id_;

  /// <summary>
  /// 終了ボタンが押されたかの有無
  /// </summary>
  bool end_;
};