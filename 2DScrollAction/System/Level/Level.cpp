#include <iostream>
#include "System/Level/Level.h"
#include "System/LogConsole/LogConsole.h"

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Level::Level()
//メンバ変数を初期化する
  : task_manager_(nullptr)
  , phase_type_(kNone)
  , pre_phase_type_(kNone)
  , task_id_(Task::kNone)
  , error_(false)
  , end_(false)
  , is_setting_(false)
  , back_title_(false)
  , is_player_alive_(true)
  , is_clear_(false)
  , is_guide_(false)
{
  DEBUG_PRINT(Levelのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Level::Level(TaskId task_id, TaskManager* task_manager)
//メンバ変数を初期化する
  : Task(task_id)
  , task_manager_(task_manager)
  , phase_type_(kNone)
  , pre_phase_type_(kNone)
  , task_id_(Task::kNone)
  , error_(false)
  , end_(false)
  , is_setting_(false)
  , back_title_(false)
  , is_player_alive_(true)
  , is_clear_(false)
  , is_guide_(false)
{
  DEBUG_PRINT(Levelのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Level::~Level() {
  DEBUG_PRINT(Levelのデストラクタ);
}

/// <summary>
/// SetTaskManager関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void Level::SetTaskManager(TaskManager* task_manager) {
  task_manager_ = task_manager;
}

/// <summary>
/// SetEndButton関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void Level::SetEndButton() {
  end_ = true;
  DEBUG_PRINT(終了ボタン);
}

/// <summary>
/// GetEndButton関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>終了ボタンが押されていたらtrue、押されていなければfalse</returns>
bool Level::GetEndButton() {
  if (Level::end_ == true) {
    DEBUG_PRINT(終了ボタンが押されている);
    return true;
  }
  DEBUG_PRINT(終了ボタンは押されていない);
  return false;
}

/// <summary>
/// UpdateFrame関数の定義
/// </summary>
/// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
/// <returns>なし</returns>
void Level::UpdateFrame(float time) {
  //DEBUG_PRINT(Levelクラスの毎フレーム更新処理);

  bool result = false;

  //DEBUG_PRINT_VAR(phase_type_);

  pre_phase_type_ = phase_type_;

  switch (phase_type_) {
  //フェーズが何もしないフェーズの場合
  case PhaseType::kNone: {
    DEBUG_PRINT(何もしないフェーズ);
    break;
  }
    //フェーズが初期化フェーズの場合
  case kInitializing: {
    //初期化処理が終わったら、初期化済みフェーズに遷移する
    result = InitializeUpdate(time);
    if (result) {
      phase_type_ = kInitialized;
      DEBUG_PRINT(初期化済みフェーズに遷移);
    }
    break;
  }
  //フェーズが処理フェーズまたは終了リクエストフェーズの場合
  case PhaseType::kInitialized:
  case PhaseType::kProcessing:
  case PhaseType::kEndRequest: {
    //処理フェーズが終わったら、終了フェーズに遷移する
    result = ProcessingUpdate(time);
    if (result) {
      phase_type_ = kEnding;
      DEBUG_PRINT(レベルの終了フェーズに遷移);
    }
    break;
  }
  //フェーズが終了フェーズの場合
  case PhaseType::kEnding: {
    //終了フェーズが終わったら、終了済みフェーズに遷移する
    result = PhaseFinalize(time);
    if (result) {
      phase_type_ = kEnded;
      DEBUG_PRINT(レベルの終了済みフェーズに遷移);
    }
    break;
  }
    //フェーズが終了済みの場合
  case PhaseType::kEnded:{
    DEBUG_PRINT(フェーズが終了済み);
    break;
  }
  }
}

/// <summary>
/// RenderFrame関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void Level::RenderFrame() {
  //DEBUG_PRINT(Levelクラスの毎フレーム描画処理);
}

/// <summary>
/// 終了リクエストフェーズかの有無を取得する関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>終了リクエストフェーズであればtrue、そうでなければfalse</returns>
bool Level::IsEndRequest() {
  if (phase_type_ == kEndRequest) {
    return true;
  }
  return false;
}

  /// <summary>
  /// StartInitializing関数の定義
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
void Level::StartInitializing() {
  phase_type_ = kInitializing;
  DEBUG_PRINT(レベルの開始処理に遷移した);
}

/// <summary>
/// CheckIsInitialized関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>初期化済みフェーズならtrue、そうでないならfalse</returns>
bool Level::CheckIsInitialized() {
  if (phase_type_ == kInitialized) {
    return true;
  }
  return false;
}

/// <summary>
/// StartEnding関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void Level::StartEnding() {
  phase_type_ = kEnding;
}

/// <summary>
/// CheckIsEnded関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>終了済みフェーズならtrue、そうでないならfalse</returns>
bool Level::CheckIsEnded() {
  if (phase_type_ == kEnded) {
    return true;
  }
  return false;
}

/// <summary>
/// CheckIsPreEnding関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>終了済みフェーズならtrue、そうでないならfalse</returns>
bool Level::CheckIsPreEnding() {
  if (pre_phase_type_ == kEnding) {
    return true;
  }
  return false;
}

/// <summary>
/// StartProcessing関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void Level::StartProcessing() {
  if (phase_type_ == kInitialized) {
    phase_type_ = kProcessing;
    DEBUG_PRINT(レベルの処理を開始した);
  }
}

/// <summary>
/// RequestChangeLevel関数の定義
/// </summary>
/// <param name = "id">次に遷移するレベルのタスクID</param>
/// <returns>切り替え成功できたらtrue</returns>
bool Level::RequestChangeLevel(TaskId id) {
  task_id_ = id;
  phase_type_ = kEndRequest;
  return true;
}

/// <summary>
/// GetTaskIdの定義
/// </summary>
/// <param name>なし</param>
/// <returns>task_id_</returns>
Task::TaskId Level::GetTaskId() {
  return task_id_;
}

/// <summary>
/// RequestEndLevel関数の定義
/// </summary>
/// <param name></param>
/// <returns></returns>
void Level::RequestEndLevel() {
  phase_type_ = kEndRequest;
}

/// <summary>
/// ChangeError関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void Level::ChangeError() {
  error_ = true;
  phase_type_ = kEnding;
}

/// <summary>
/// IsError関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>エラー：true、エラーではない：false</returns>
bool Level::IsError() {
  if (error_) {
    return true;
  }
  return false;
}

/// <summary>
/// IsSetting関数
/// </summary>
/// <param name>なし</param>
/// <returns>設定に遷移するかの有無</returns>
bool Level::IsSetting() {
  return is_setting_;
}

/// <summary>
/// SetSetting関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void Level::SetSetting() {
  is_setting_ = true;
  DEBUG_PRINT(設定に遷移する);
}

/// <summary>
/// SetBackTitle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void Level::SetBackTitle() {
  back_title_ = true;
}

/// <summary>
/// IsBackTitle関数
/// </summary>
/// <param name>なし</param>
/// <returns>設定に遷移するかの有無</returns>
bool Level::IsBackTitle() {
  return back_title_;
}

/// <summary>
/// IsPlayerAlive関数
/// </summary>
/// <param name>なし</param>
/// <returns>設定に遷移するかの有無</returns>
bool Level::IsPlayerAlive() {
  return is_player_alive_;
}

/// <summary>
/// SetPlayerAlive関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void Level::SetPlayerAlive(bool is_player_alive) {
  is_player_alive_ = is_player_alive;
}

/// <summary>
/// IsGameClear関数
/// </summary>
/// <param name>なし</param>
/// <returns>ゲームクリアかの有無</returns>
bool Level::IsGameClear() {
  return is_clear_;
}

/// <summary>
/// SetGameClear関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void Level::SetGameClear(bool is_game_clear) {
  is_clear_ = is_game_clear;
}

/// <summary>
/// IsGuide関数
/// </summary>
/// <param name>なし</param>
/// <returns>操作説明に遷移するかの有無</returns>
bool Level::IsGuide() {
  return is_guide_;
}

/// <summary>
/// SetGuide関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void Level::SetGuide() {
  DEBUG_PRINT(操作説明に遷移する);
  is_guide_ = true;
}