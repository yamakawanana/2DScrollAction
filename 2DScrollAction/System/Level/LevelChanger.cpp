#include <iostream>
#include "System/Level/LevelChanger.h"
#include "System/Level/Level.h"
#include "System/LogConsole/LogConsole.h"
#include "System/Task/TaskManager.h"
#include "System/Task/Task.h"
#include "Game/Level/BootLevel.h"
#include "Game/Level/TitleLevel.h"
#include "Game/Level/BattleLevel.h"
#include "Game/Level/ResultLevel.h"
#include "Game/Level/SettingLevel.h"
#include "Game/Level/GuideLevel.h"
#include "Game/Level/StageSelectLevel.h"
#include "System/FileManager/FileManager.h"
#include "Game/GameInfo/GameInfo.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// 選択可能なステージを保存するファイル名を定数kSelectableStageCSVに格納する
  /// </summary>
  static const char* kSelectableStageCSV = "Assets/CsvFiles/selectable_stages.csv";
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
LevelChanger::LevelChanger()
//メンバ変数を初期化する
  : task_manager_(nullptr)
  , phase_type_(kInitialized)
  , level_transition_(kNone)
  , level_(nullptr)
  , task_id_(Task::kNone)
  , end_(false)
{
  DEBUG_PRINT(LevelChangerのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
LevelChanger::~LevelChanger() {
  DEBUG_PRINT(LevelChangerのデストラクタ);
}

/// <summary>
/// SetTaskManager関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void LevelChanger::SetTaskManager(TaskManager* task_manager){
  task_manager_ = task_manager;
}

/// <summary>
/// UpdateFrame関数の定義
/// </summary>
/// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
/// <returns>なし</returns>
void LevelChanger::UpdateFrame(float time) {
  //DEBUG_PRINT(LevelChangerクラスの毎フレーム更新処理);

  bool result = false;
  bool end_result = false;

  switch (phase_type_) {
  //レベルチェンジャーのフェーズが初期化フェーズの場合
  case kInitialized: {
    Initialize(time);
    phase_type_ = kProcessing;
    DEBUG_PRINT(処理フェーズに遷移);
    break;
  }
  //レベルチェンジャーのフェーズが処理フェーズの場合
  case PhaseType::kProcessing: {
    result = PhaseUpdate(time);
    if (result) {
      phase_type_ = kEnding;
      DEBUG_PRINT(レベルチェンジャーの終了フェーズに遷移);
    }
    break;
  }
 //レベルチェンジャーのフェーズが終了フェーズの場合
  case PhaseType::kEnding: {
    result = Finalize(time);
    //終了ボタンが押されている場合は、何もしないフェーズに遷移する
    if (end_) {
      phase_type_ = kNothing;
    }
    //終了ボタンが押されていない場合は、終了済みフェーズに遷移する
    else {
      phase_type_ = kEnded;
      DEBUG_PRINT(レベルチェンジャーの終了済みフェーズに遷移);
    }
    break;
  }
  //レベルチェンジャーのフェーズが終了済みフェーズの場合
  case PhaseType::kEnded: {
    //終了ボタンが押されていないなら、次の画面に遷移するため、初期化フェーズに戻す
    phase_type_ = kInitialized;
    DEBUG_PRINT(初期化フェーズに戻した);
    break;
  }
  //終了ボタンが押されている場合は、メインループを抜ける
  case PhaseType::kNothing: {
    DEBUG_PRINT(終了ボタンが押されているので終了する);
    PostQuitMessage(0);
    break;
  }
  }
}

/// <summary>
/// RenderFrame関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void LevelChanger::RenderFrame() {
  //DEBUG_PRINT(LevelChangerクラスの毎フレーム描画処理);
}

/// <summary>
/// EndLevelChanger関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void LevelChanger::EndLevelChanger() {
  phase_type_ = kEnding;
}

/// <summary>
/// CheckLevelChangerEnded関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
bool LevelChanger::CheckLevelChangerEnded() {
  if (phase_type_ == kEnded) {
    return true;
  }
  return false;
}

/// <summary>
/// CreateLevelProcessing関数の定義
/// </summary>
/// <param>生成するレベルのタスクID</param>
/// <returns>レベル処理のポインタ</returns>
Level* LevelChanger::CreateLevelProcessing(TaskId task_id, Level* generate_level) {

  //タスクIDに対応したレベル処理を生成する
  switch (task_id) {
  case TaskId::kBootLevelTask:
    generate_level = new BootLevel(task_id, task_manager_);
    DEBUG_PRINT(ブートレベルを生成した);
    break;

  case TaskId::kTitleLevelTask:
    generate_level = new TitleLevel(task_id, task_manager_);
    DEBUG_PRINT(タイトルレベルを生成した);
    break;

  case TaskId::kSettingLevelTask:
    generate_level = new SettingLevel(task_id, task_manager_);
    DEBUG_PRINT(設定レベルを生成した);
    break;

  case TaskId::kGuideLevelTask:
    generate_level = new GuideLevel(task_id, task_manager_);
    DEBUG_PRINT(操作説明レベルを生成した);
    break;

  case TaskId::kStageSelectLevelTask:
    generate_level = new StageSelectLevel(task_id, task_manager_);
    DEBUG_PRINT(ステージ選択レベルを生成した);
    break;

  case TaskId::kBattleLevelTask:
    generate_level = new BattleLevel(task_id, task_manager_);
    DEBUG_PRINT(バトルレベルを生成した);
    break;

  case TaskId::kResultLevelTask:
    generate_level = new ResultLevel(task_id, task_manager_);
    DEBUG_PRINT(リザルトレベルを生成した);
    break;

  }
  return generate_level;
}

/// <summary>
/// 初期化処理のフェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool LevelChanger::Initialize(float time) {
  DEBUG_PRINT(初期化処理のフェーズ処理);
  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool LevelChanger::PhaseUpdate(float time) {
	//DEBUG_PRINT(レベルチェンジャーの毎フレーム更新処理のフェーズ処理);

  //レベルのフェーズが終了済みフェーズの場合、レベルチェンジャーの終了フェーズに遷移する
  if (level_ != nullptr && level_->CheckIsEnded() && level_->CheckIsPreEnding()) {
    phase_type_ = kEnding;
    DEBUG_PRINT(切り替え終了したので、レベルチェンジャーを終了させる);
    return true;
  }

  //全くレベルが存在しない場合
  if (level_ == nullptr && level_transition_== kNone) {

    //タスクIDの最初のレベルのタスクIDを設定する
    task_id_ = kBootLevelTask;

    //レベル遷移フェーズに【次のレベルの生成】を設定する
    level_transition_ = kCreateNextLevel;
    DEBUG_PRINT(レベルが存在しないので生成する);
  }

  else if (level_->GetTaskId() != task_id_) {
    //レベル切り替えの場合、設定されているTaskIDを使って次のレベルの生成を設定する
    if (task_id_ == kBootLevelTask && level_transition_ == kEnd) {
      level_transition_ = kCreateNextLevel;
      DEBUG_PRINT(kBootLevelTask 次のレベルの生成);
    }
    else if (task_id_ == kTitleLevelTask && level_transition_ == kEnd) {
      level_transition_ = kCreateNextLevel;
      DEBUG_PRINT(kTitleLevelTask 次のレベルの生成);
    }
    else if (task_id_ == kSettingLevelTask && level_transition_ == kEnd) {
      level_transition_ = kCreateNextLevel;
      DEBUG_PRINT(kSettingLevelTask 次のレベルの生成);
    }
    else if (task_id_ == kGuideLevelTask && level_transition_ == kEnd) {
      level_transition_ = kCreateNextLevel;
      DEBUG_PRINT(kGuideLevelTask 次のレベルの生成);
    }
    else if (task_id_ == kStageSelectLevelTask && level_transition_ == kEnd) {
      level_transition_ = kCreateNextLevel;
      DEBUG_PRINT(kStageSelectLevelTask 次のレベルの生成);
    }
    else if (task_id_ == kBattleLevelTask && level_transition_ == kEnd) {
      level_transition_ = kCreateNextLevel;
      DEBUG_PRINT(kBattleLevelTask 次のレベルの生成);
    }
    else if (task_id_ == kResultLevelTask && level_transition_ == kEnd) {
      level_transition_ = kCreateNextLevel;
      DEBUG_PRINT(kResultLevelTask 次のレベルの生成);
    }
  }

  //レベルが終了リクエストを出している場合、またはレベルが終了済みフェーズである場合
  else if (level_->IsEndRequest()|| level_->CheckIsEnded()) {
    //レベル遷移フェーズに【現在のレベルの終了処理】を設定する
    level_transition_ = kEndProcessing;
    DEBUG_PRINT(レベルが終了リクエストを出しているのでレベルの終了処理に遷移する);
  }

  switch (level_transition_) {

    DEBUG_PRINT_VAR(level_transition_);

  //レベル遷移フェーズが【現在のレベルの終了処理】の場合
  case LevelTransitionType::kEndProcessing: {
    //現在のレベルの終了処理を開始する
    Finalize(time);
    //レベル遷移フェーズに【終了処理の終了】を設定する
    level_transition_ = kEndEnding;


    DEBUG_PRINT(終了処理の終了に遷移する);
    break;
  }

  //レベル遷移フェーズが【終了処理の終了】の場合
  case LevelTransitionType::kEndEnding: {

    //現在のレベルが終了済みなら
    if (level_->CheckIsEnded()) {
      DEBUG_PRINT(現在のレベルが終了済みなら);
      //動作中のレベルのタスクIDを取得する
      TaskId now_id = level_->GetTaskId();
      DEBUG_PRINT_VAR(now_id);
      //取得したタスクIDを利用してレベルタスクを降ろす
      task_manager_->UnloadTask(now_id);
      DEBUG_PRINT(レベルタスクを降ろした);
    }

    //次のレベルのタスクIDが設定されているなら、【次のレベルの生成】フェーズに遷移する
    if (task_id_ != kNone) {
    level_transition_ = kCreateNextLevel;
    DEBUG_PRINT(次のレベルを生成する);
    }
    else {
      //次に遷移するレベルが設定されていない場合、レベル遷移フェーズは【何もしない】を設定
      level_transition_ = kNone;
      //遷移フェーズは終了フェーズにする
      phase_type_ = kEnding;
      DEBUG_PRINT(レベルチェンジャーを終了させる);

      return true;
    }

    break;
  }
                                                
  //レベル遷移フェーズが【次のレベルの生成】の場合
  case LevelTransitionType::kCreateNextLevel: {
    Level* generate_level = nullptr;

    //次のレベルを生成する
    level_ = CreateLevelProcessing(task_id_, generate_level);

    if (generate_level != nullptr) {
      delete generate_level;
      generate_level = nullptr;
    }

    //レベル遷移フェーズに【次のレベルの開始処理】を設定する
    level_transition_ = kStartNextProcessing;
    DEBUG_PRINT(次のレベルの開始処理に遷移する);
    break;
  }

  //レベル遷移フェーズが【次のレベルの開始処理】の場合
  case LevelTransitionType::kStartNextProcessing: {

    //生成したレベルからタスクを取得し、タスクマネージャーに積む
    task_manager_->AddTask(level_);

    //レベルの初期化処理を開始する
    level_->StartInitializing();

    //レベル遷移のフェーズを【次のレベルの開始処理の終了】フェーズにする
    level_transition_ = kEndingStartNextProcessing;
    DEBUG_PRINT(次のレベルの開始処理の終了に遷移する);
    break;
  }

  //レベル遷移フェーズが【次のレベルの開始処理の終了】の場合
  case LevelTransitionType::kEndingStartNextProcessing: {

    //初期化処理が終了していれば
    if (level_->CheckIsInitialized()) {
      //次のレベル処理を開始する
      level_->StartProcessing();

      //レベル遷移のフェーズを【切り替え終了】フェーズにする
      level_transition_ = kEndTransition;
      DEBUG_PRINT(レベル切り替え終了);

    }
    break;
  }

  }
  return false;
}

/// <summary>
/// 終了処理のフェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool LevelChanger::Finalize(float time) {
  DEBUG_PRINT(Finalize);

  if (level_->GetEndButton()) {
    end_ = true;
    DEBUG_PRINT(終了ボタンが押されているので終了する);
  }

  //タスクマネージャーに積んでいたレベルを解放するためにrelease_taskに格納する
  Task* release_task = task_manager_->UnloadTask(task_id_);

  //「タイトルへ」が押されたかのフラグ
  bool back_title = level_->IsBackTitle();

  //ファイルマネージャーのインスタンスを取得
  FileManager* file_manager = FileManager::GetInstance();

  //選択可能なステージのデータを読み込む
  std::vector<int> selectable_stages = file_manager->ReadDataFromFile(kSelectableStageCSV);

  //次のレベルの生成に備え、タスクIDを更新する
  if (task_id_ == kNone) {
    task_id_ = kBootLevelTask;
    DEBUG_PRINT(kBootLevelTaskタスクIDを更新した);
  }
  else if (task_id_ == kBootLevelTask) {
    task_id_ = kTitleLevelTask;
    DEBUG_PRINT(kTitleLevelTaskタスクIDを更新した);
  }
  else if (task_id_ == kTitleLevelTask) {
    bool is_setting = level_->IsSetting();
    bool is_guide = level_->IsGuide();
    DEBUG_PRINT_VAR(is_setting);
    if (is_setting) {
      task_id_ = kSettingLevelTask;
      DEBUG_PRINT(kSettingLevelTaskタスクIDを更新した);
    }
    else if (is_guide) {
      task_id_ = kGuideLevelTask;
      DEBUG_PRINT(kGuideLevelTaskタスクIDを更新した);
    }
    else if(selectable_stages.at(0) == 0){
      task_id_ = kBattleLevelTask;
      DEBUG_PRINT(kBattleLevelTaskタスクIDを更新した);
    }
    else {
      task_id_ = kStageSelectLevelTask;
      DEBUG_PRINT(kStageSelectLevelTaskタスクIDを更新した);
    }
  }
  else if (task_id_ == kSettingLevelTask) {
    if (back_title == true) {
      task_id_ = kTitleLevelTask;
      DEBUG_PRINT(kTitleLevelTaskタスクIDを更新した);
    }
    else if (selectable_stages.at(0) == 0) {
      task_id_ = kBattleLevelTask;
      DEBUG_PRINT(kBattleLevelTaskタスクIDを更新した);
    }
    else {
      task_id_ = kStageSelectLevelTask;
      DEBUG_PRINT(kStageSelectLevelTaskタスクIDを更新した);
    }
  }
  else if (task_id_ == kGuideLevelTask) {
    if (back_title == true) {
      task_id_ = kTitleLevelTask;
      DEBUG_PRINT(kTitleLevelTaskタスクIDを更新した);
    }
    else if (selectable_stages.at(0) == 0) {
      task_id_ = kBattleLevelTask;
      DEBUG_PRINT(kBattleLevelTaskタスクIDを更新した);
    }
    else {
      task_id_ = kStageSelectLevelTask;
      DEBUG_PRINT(kStageSelectLevelTaskタスクIDを更新した);
    }
  }
  else if (task_id_ == kStageSelectLevelTask) {
    if (back_title == true) {
      task_id_ = kTitleLevelTask;
      DEBUG_PRINT(kTitleLevelTaskタスクIDを更新した);
    }
    else{
      task_id_ = kBattleLevelTask;
      DEBUG_PRINT(kBattleLevelTaskタスクIDを更新した);
    }
  }
  else if (task_id_ == kBattleLevelTask) {
    bool is_player_alive = level_->IsPlayerAlive();
    bool is_clear = level_->IsGameClear();
    if (is_player_alive && (!is_clear)) {
      task_id_ = kBattleLevelTask;
      DEBUG_PRINT(kBattleLevelTaskタスクIDを更新した);
    }
    else {
      task_id_ = kResultLevelTask;
      DEBUG_PRINT(kResultLevelTaskタスクIDを更新した);
    }
  }
  else if (task_id_ == kResultLevelTask) {
    //ゲーム情報を取得する
    GameInfo* game_info = GameInfo::GetInstance();
    bool game_clear = game_info->IsGameClear();
    if (back_title == true) {
      task_id_ = kTitleLevelTask;
      DEBUG_PRINT(kTitleLevelTaskタスクIDを更新した);
    }
    else if(game_clear){
      task_id_ = kStageSelectLevelTask;
      DEBUG_PRINT(kStageSelectLevelTaskタスクIDを更新した);
    }
    else {
      task_id_ = kBattleLevelTask;
      DEBUG_PRINT(kBattleLevelTaskタスクIDを更新した);
    }
    DEBUG_PRINT(タスクIDを更新した);
  }

  //release_taskのメモリを解放する
  delete release_task;

  //レベル遷移のフェーズを【処理終了】フェーズにする
  level_transition_ = kEnd;

  DEBUG_PRINT(終了処理のフェーズ処理をした);

  return true;
}