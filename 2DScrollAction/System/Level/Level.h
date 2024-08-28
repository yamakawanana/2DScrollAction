#pragma once
#include <iostream>
#include "System/Task/TaskManager.h"

/// <summary>
/// Levelクラス
/// </summary>
class Level : public Task {
public:
  /// <summary>
  //フェーズの種類の列挙型PhaseType型を定義する
  /// <summary>
  enum PhaseType {
    /// <summary>
    /// 何もしない
    /// </summary>
    kNone,

    /// <summary>
    /// 初期化フェーズ
    /// </summary>
    kInitializing,

    /// <summary>
    /// 初期化済みフェーズ
    /// </summary>
    kInitialized,

    /// <summary>
    /// 処理フェーズ
    /// </summary>
    kProcessing,

    /// <summary>
    /// 終了リクエストフェーズ
    /// </summary>
    kEndRequest,

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
  /// デフォルトコンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Level();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Level(TaskId task_id, TaskManager* task_manager);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~Level();

  /// <summary>
  /// SetTaskManager関数の宣言
  /// </summary>
  /// <param = "task_manager">TaskManagerのポインタのtask_manager</param>
  /// <returns>なし</returns>
  void SetTaskManager(TaskManager* task_manager);

  /// <summary>
  /// SetEndButton関数の宣言
  /// </summary>
  /// <returns>なし</returns>
  /// <returns>なし</returns>
  void SetEndButton();

  /// <summary>
  /// GetEndButton関数の宣言
  /// </summary>
  /// <returns>なし</returns>
  /// <returns>終了ボタンが押されていたらtrue、押されていなければfalse</returns>
  bool GetEndButton();

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
  /// 終了リクエストフェーズかの有無を取得する関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>終了リクエストフェーズであればtrue、そうでなければfalse</returns>
  bool IsEndRequest();

  /// <summary>
  /// StartInitializing関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void StartInitializing();

  /// <summary>
  /// CheckIsInitialized関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>初期化済みフェーズならtrue、そうでないならfalse</returns>
  bool CheckIsInitialized();

  /// <summary>
  /// StartEnding関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void StartEnding();

  /// <summary>
  /// CheckIsEnded関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>終了済みフェーズならtrue、そうでないならfalse</returns>
  bool CheckIsEnded();

  /// <summary>
  /// CheckIsPreEnding関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>前回フレームが終了フェーズならtrue、そうでないならfalse</returns>
  bool CheckIsPreEnding();

  /// <summary>
  /// StartProcessing関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void StartProcessing();

  /// <summary>
  /// RequestChangeLevel関数の宣言
  /// </summary>
  /// <param name = "id">次に遷移するレベルのタスクID</param>
  /// <returns>hp_</returns>
  bool RequestChangeLevel(TaskId id);

  /// <summary>
  /// GetTaskId関数の定義
  /// </summary>
  /// <param name>なし</param>
  /// <returns>task_id_</returns>
  TaskId GetTaskId();

  /// <summary>
  /// RequestEndLevel関数の宣言
  /// </summary>
  /// <param name></param>
  /// <returns></returns>
  void RequestEndLevel();

  /// <summary>
  /// ChangeError関数の定義
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void ChangeError();

  /// <summary>
  /// IsError関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>エラー：true、エラーではない：false</returns>
  bool IsError();

  /// <summary>
  /// IsSetting関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>設定に遷移するかの有無</returns>
  bool IsSetting();

  /// <summary>
  /// SetSetting関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void SetSetting();

  /// <summary>
  /// SetBackTitle関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void SetBackTitle();

  /// <summary>
  /// IsBackTitle関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>タイトル画面に戻るかの有無</returns>
  bool IsBackTitle();

  /// <summary>
  /// IsPlayerAlive関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>プレイヤーが残っているかの有無</returns>
  bool IsPlayerAlive();

  /// <summary>
  /// SetPlayerAlive関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void SetPlayerAlive(bool is_player_alive);

  /// <summary>
  /// IsGameClear関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>ゲームクリアの有無</returns>
  bool IsGameClear();

  /// <summary>
  /// SetGameClear関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void SetGameClear(bool is_game_clear);

  /// <summary>
  /// IsGuide関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>操作説明に遷移するかの有無</returns>
  bool IsGuide();

  /// <summary>
  /// SetGuide関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void SetGuide();

protected:

  /// <summary>
  /// 初期化処理フェーズの毎フレーム更新処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  virtual bool InitializeUpdate(float time) = 0;

  /// <summary>
  /// 処理中処理フェーズの毎フレーム更新処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  virtual bool ProcessingUpdate(float time) = 0;

  /// <summary>
  /// 処理中処理フェーズの毎フレーム描画処理
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual void ProcessingRender() = 0;

  /// <summary>
  /// 終了処理フェーズの毎フレーム更新処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  virtual bool PhaseFinalize(float time) = 0;

protected:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// </summary>
  //タスクマネージャーのポインタ
  /// </summary>
  TaskManager* task_manager_;

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// </summary>
  //フェーズの種類
  /// </summary>
  PhaseType phase_type_;

  /// </summary>
  //前回フレームのフェーズの種類
  /// </summary>
  PhaseType pre_phase_type_;

  /// </summary>
  //次に遷移するレベルのタスクID
  /// </summary>
  TaskId task_id_;

  /// <summary>
  /// エラー発生の有無
  /// </summary>
  bool error_;

  /// <summary>
  /// 終了ボタンが押されたかの有無
  /// </summary>
  bool end_;

  /// <summary>
  /// 設定に遷移するかの有無
  /// </summary>
  bool is_setting_;

  /// <summary>
  /// タイトル画面に戻るかの有無
  /// </summary>
  bool back_title_;

  /// <summary>
  /// プレイヤーが残っているかの有無
  /// </summary>
  bool is_player_alive_;

  /// <summary>
  /// ゲームクリアの有無
  /// </summary>
  bool is_clear_;

  /// <summary>
  /// 操作説明に遷移するかの有無
  /// </summary>
  bool is_guide_;
};
