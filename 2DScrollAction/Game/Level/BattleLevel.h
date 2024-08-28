#pragma once
#include <queue>
#include "System/Level/Level.h"
#include "System/LogConsole/LogConsole.h"
#include "Game/Field/Field.h"
#include "Game/Field/Pipe.h"
#include "Game/Player/Player.h"
#include "Game/GameMode/GameMode.h"
#include "Game/Ui/StartUi.h"
#include "Game/Ui/PauseUi.h"
#include "Game/Enemy/FirstWalkingEnemy.h"
#include "Game/Enemy/SecondWalkingEnemy.h"
#include "Game/Enemy/FlyingEnemy.h"
#include "Game/Enemy/JumpingEnemy.h"
#include "System/Camera/Camera.h"
#include "Game/Enemy/FlyingEnemy.h"
#include "Game/Enemy/JumpingEnemy.h"
#include "System/Collision/Collision.h"
#include "Game/Ui/InfoUi.h"
#include "Game/Item/Item.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Fade/BattleFade.h"
#include "Game/Audio/AudioManager.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// キノコの敵の数を定数kFirstWalkingEnemyNumsに格納する
  /// </summary>
  static const int kFirstWalkingEnemyNums[] = {16,14,3};

  /// <summary>
  /// カタツムリの敵の数を定数kSecondWalkingEnemyNumsに格納する
  /// </summary>
  static const int kSecondWalkingEnemyNums[] = { 1,4,2 };

  /// <summary>
  /// コウモリの敵の数を定数kFlyingEnemyNumsに格納する
  /// </summary>
  static const int kFlyingEnemyNums[] = { 1,0,2 };

  /// <summary>
  /// クワガタの敵の数を定数kJumpingEnemyNumsに格納する
  /// </summary>
  static const int kJumpingEnemyNums[] = { 1,3,0 };

  /// <summary>
  /// アイテムの数を定数kItemNumに格納する
  /// </summary>
  static const int kItemNum = 1;

  /// <summary>
  /// 敵データのCSVファイルの項目数を定数kEnemyDataColumnに格納する
  /// </summary>
  static const int kEnemyDataColumn = 4;
}

/// <summary>
/// BattleLevelクラス
/// </summary>
class BattleLevel : public Level{
public:

  /// <summary>
  //ImageInfo構造体型を定義する
  /// <summary>
  struct ImageInfo {
    /// <summary>
    //画像のグラフィックハンドル
    /// <summary>
    int handle;
    /// <summary>
    //画像の幅
    /// <summary>
    int size_x; 
    /// <summary>
    //画像の高さ
    /// <summary>
    int size_y; 
  };

  /// <summary>
  //終了フェーズの種類の列挙型EndPhaseType型を定義する
  /// <summary>
  enum EndPhaseType {
    /// <summary>
    /// タスクを降ろすフェーズ
    /// </summary>
    kUnloadTask,

    /// <summary>
    /// 破棄フェーズ
    /// </summary>
    kDelete,
  };

  /// <summary>
  //ステージの種類の列挙型StageType型を定義する
  /// <summary>
  enum StageType {
    /// <summary>
    /// ステージ1
    /// </summary>
    kFirstStage,

    /// <summary>
    /// ステージ2
    /// </summary>
    kSecondStage,

    /// <summary>
    /// ステージ3
    /// </summary>
    kThirdStage,
  };

  /// <summary>
  //敵かアイテムの種類の列挙型EnemyItemType型を定義する
  /// <summary>
  enum EnemyItemType {

    /// <summary>
    /// 1種類目の歩く敵
    /// </summary>
    kFirstWalkingEnemy,

    /// <summary>
    /// 2種類目の歩く敵
    /// </summary>
    kSecondWalkingEnemy,

    /// <summary>
    /// 飛ぶ敵
    /// </summary>
    kFlyingEnemy,

    /// <summary>
    /// 下から出て来る敵
    /// </summary>
    kJumpingEnemy,

    /// <summary>
    /// アイテム
    /// </summary>
    kItem,
  };

  /// <summary>
  //フェーズの種類(処理中のフェーズ)
  /// <summary>
  enum ProcessingPhaseType {
    /// <summary>
    /// 準備中
    /// </summary>
    kPreparation,

    /// <summary>
    /// スタートUI表示
    /// </summary>
    kStartUiDisplay,

    /// <summary>
    /// スタートUI終了待機
    /// </summary>
    kStartUiFinishWaiting,

    /// <summary>
    /// プレイヤーの残数が減った
    /// </summary>
    kDecreasedPlayer,

    /// <summary>
    /// ゲームオーバー
    /// </summary>
    kGameOver,

    /// <summary>
    /// フェードイン
    /// </summary>
    kFadeIn,

    /// <summary>
    /// フィニッシュUI表示
    /// </summary>
    kFinishUiDisplay,

    /// <summary>
    /// フィニッシュUI終了待機
    /// </summary>
    kFinishUiFinishWaiting,

    /// <summary>
    /// 処理中
    /// </summary>
    kProcessing,

    /// <summary>
    /// プレイ中断
    /// </summary>
    kStop,

    /// <summary>
    /// ステージクリア
    /// </summary>
    kStageClear,

    /// <summary>
    /// バトル終了
    /// </summary>
    kBattleFinish,

    /// <summary>
    /// レベル遷移
    /// </summary>
    kLevelTransition,

    /// <summary>
    /// 終了済み
    /// </summary>
    kFinished,
  };

  /// <summary>
  /// デフォルトコンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  BattleLevel();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  BattleLevel(TaskId task_id, TaskManager* task_manager);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~BattleLevel();

  /// <summary>
  /// 各方向キーが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void OnPushDirectionKey();

  /// <summary>
  /// 移動範囲をチェックする
  /// </summary>
  /// <param name ></param>
  /// <returns>なし</returns>
  void CheckWalkDistance();

  /// <summary>
  /// 決定ボタンが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void OnPushDecide();

  /// <summary>
  /// 終了ボタンが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void OnPushFinish();

  /// <summary>
  /// スペースボタンが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void OnPushPause();

  /// <summary>
  /// BackSpaceボタンが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void OnPushBackSpace();

  /// <summary>
  /// ゲームオーバーを設定する処理
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void SetGameOver();

  /// <summary>
  /// UI終了のイベント
  /// </summary>
  /// <param name="task_id">終了するUIのタスクID</param>
  /// <returns>なし</returns>
  virtual void EndUi(TaskId task_id);

  /// <summary>
  /// LoadImage関数の宣言
  /// </summary>
  /// <param = "filename">画像のファイル名</param>
  /// <returns>ImageInfo構造体型のinfo</returns>
  ImageInfo LoadImage(const char* filename);

  /// <summary>
  /// SetGameOverGrHandle関数の宣言
  /// </summary>
  /// <param = "gameover_handle">ゲームオーバーの画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetGameOverGrHandle(int gameover_handle);

  /// <summary>
  /// GetGameOverGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ゲームオーバーの画像のグラフィックハンドル</returns>
  int GetGameOverGrHandle();

  /// <summary>
  /// StopAll関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void StopAll();

  /// <summary>
  /// SetPlayingAll関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void SetPlayingAll();

  /// <summary>
  /// StopEnemyAndCountdown関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void StopEnemyAndCountdown();

  /// <summary>
  /// SetEnemyAndCountdown関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void SetEnemyAndCountdown();

  /// <summary>
  /// StopPlayerAndCountdown関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void StopPlayerAndCountdown();

  /// <summary>
  /// SetPlayerAndCountdown関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void SetPlayerAndCountdown();

  /// <summary>
  /// フェードアウト表示する関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "handle">グラフィックハンドル</param>
  /// <param = "is_transparent">透過の有無</param>
  /// <returns>なし</returns>
  void FadeOut();

  /// <summary>
  /// SetWhiteRectangleGrHandle関数の宣言
  /// </summary>
  /// <param = "white_rectangle_handle">文字表示のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetWhiteRectangleGrHandle(int white_rectangle_handle);

  /// <summary>
  /// GetWhiteRectangleGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>文字表示のグラフィックハンドル</returns>
  int GetWhiteRectangleGrHandle();

  /// <summary>
  /// 下に移動する時に衝突したかを確認する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void CheckIsHitPlayersBottom();

  /// <summary>
  /// 右に移動する時に衝突したかを確認する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void CheckIsHitPlayersRight();

  /// <summary>
  /// 左に移動する時に衝突したかを確認する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void CheckIsHitPlayersLeft();

  /// <summary>
  /// InitializeEnemyData関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns></returns>
  void InitializeEnemyData(int enemy_num, const char* filename, EnemyItemType enemy_item_type);

  /// <summary>
  /// IsPlayerDropThisFrame関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>プレイヤーの状態がkDropになった瞬間であるかのフラグ</returns>
  bool IsPlayerDropThisFrame(Player::StatusType player_status);

protected:

  /// <summary>
  /// 初期化処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool InitializeUpdate(float time) override;

  /// <summary>
  /// 毎フレーム更新処理のフェーズ処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool ProcessingUpdate(float time) override;

  /// <summary>
  /// 毎フレームの描画処理
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void ProcessingRender() override;

  /// <summary>
  /// 終了処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool PhaseFinalize(float time) override;

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// <summary>
  /// 終了の有無
  /// </summary>
  bool is_finish_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float accumulation_time_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float display_accumulation_time_;

  /// <summary>
  /// フィールド処理
  /// </summary>
  Field* field_;

  /// <summary>
  /// 土管処理
  /// </summary>
  Pipe* pipe_;

  /// <summary>
  /// プレイヤー
  /// </summary>
  Player* player_;

  /// <summary>
  /// 1種類目の歩く敵(配列の要素番号で何匹目の敵であるか指定)
  /// </summary>
  FirstWalkingEnemy* first_walking_enemys_[kMaxEnemyNum];

  /// <summary>
  /// 2種類目の歩く敵(配列の要素番号で何匹目の敵であるか指定)
  /// </summary>
  SecondWalkingEnemy* second_walking_enemys_[kMaxEnemyNum];

  /// <summary>
  /// 飛ぶ敵(配列の要素番号で何匹目の敵であるか指定)
  /// </summary>
  FlyingEnemy* flying_enemys_[kMaxEnemyNum];

  /// <summary>
  /// 下から出てくる敵(配列の要素番号で何匹目の敵であるか指定)
  /// </summary>
  JumpingEnemy* jumping_enemys_[kMaxEnemyNum];

  /// <summary>
  /// 終了フェーズの種類
  /// </summary>
  EndPhaseType end_type_;

  /// <summary>
  /// ゲームモード
  /// </summary>
  GameMode* game_mode_;

  /// <summary>
  /// フェーズの種類
  /// </summary>
  ProcessingPhaseType phase_type_;

  /// <summary>
  /// スタートUI
  /// </summary>
  StartUi* start_ui_;

  /// <summary>
  /// ポーズ情報UI
  /// </summary>
  PauseUi* pause_ui_;

  /// <summary>
  /// 情報UI
  /// </summary>
  InfoUi* info_ui_;

  /// <summary>
  /// カメラ
  /// </summary>
  Camera* camera_;

  /// <summary>
  /// 衝突判定
  /// </summary>
  Collision* collision_;

  /// <summary>
  /// BattleFade
  /// </summary>
  BattleFade* battle_fade_;

  /// <summary>
  /// アイテム
  /// </summary>
  Item* items_[kItemNum];

  /// <summary>
  /// 終わったかの有無
  /// </summary>
  //bool last_render_;

  /// <summary>
  /// ゲームオーバーの画像のグラフィックハンドル
  /// </summary>
  int gameover_handle_;

  /// <summary>
  /// 文字表示の画像のグラフィックハンドル
  /// </summary>
  int white_rectangle_handle_;

  /// <summary>
  /// ゲームオーバー時の画像のフェードインが終わったかの有無
  /// </summary>
  bool gameover_fade_end_;

  /// <summary>
  /// BGMサウンドハンドル
  /// </summary>
  int bgm_handle_;

  /// <summary>
  /// ゲームオーバー時のサウンドハンドル
  /// </summary>
  int gameover_sound_handle_;

  /// <summary>
  /// サウンドハンドル
  /// </summary>
  int first_enter_sound_handle_;

  /// <summary>
  /// サウンドハンドル
  /// </summary>
  int second_enter_sound_handle_;

  /// <summary>
  /// フェードイン・フェードアウトで使用する整数
  /// </summary>
  int fade_;

  /// <summary>
  /// 前回までのFieldクラスのフェーズ
  /// </summary>
  Field::FieldPhaseType pre_field_phase_;

  /// <summary>
  /// 前回までのPlayerの状態
  /// </summary>
  Player::StatusType pre_player_status_;

  /// <summary>
  /// プレイヤーのHP
  /// </summary>
  int player_hp_;

  /// <summary>
  /// 前回フレームでのプレイヤーHP
  /// </summary>
  int pre_player_hp_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float damage_wait_accumulation_time_;

  /// <summary>
  /// プレイヤーの状態がkDropになるまでの累積時間（秒）
  /// </summary>
  float player_drop_accumulation_time_;

  /// <summary>
  /// 1種類目の敵の状態がkDropになるまでの累積時間（配列の要素番号で何匹目の敵であるか指定）
  /// </summary>
  float first_enemy_drop_accumulation_times_[kMaxEnemyNum];

  /// <summary>
  /// 2種類目の敵の状態がkDropになるまでの累積時間（配列の要素番号で何匹目の敵であるか指定）
  /// </summary>
  float second_enemy_drop_accumulation_times_[kMaxEnemyNum];

  /// <summary>
  /// 飛ぶ敵の状態がkDropになるまでの累積時間（配列の要素番号で何匹目の敵であるか指定）
  /// </summary>
  float flying_enemys_drop_accumulation_times_[kMaxEnemyNum];

  /// <summary>
  /// ステージクリアの演出を表示するまでの累積時間（秒）
  /// </summary>
  float clear_accumulation_time_;

  /// <summary>
  /// プレイヤーの残機を減らす処理をするまでの累積時間（秒）
  /// </summary>
  float player_reduce_time_;

  /// <summary>
  /// プレイヤーが1種類目の敵と衝突したか(配列の要素番号で1種類目の敵の何匹目であるか指定)
  /// </summary>
  bool is_hit_first_enemys_[kMaxEnemyNum];

  /// <summary>
  /// プレイヤーが2種類目の敵と衝突したか(配列の要素番号で2種類目の敵の何匹目であるか指定)
  /// </summary>
  bool is_hit_second_enemys_[kMaxEnemyNum];

  /// <summary>
  /// プレイヤーが飛ぶ敵と衝突したか(配列の要素番号で飛ぶ敵の何匹目であるか指定)
  /// </summary>
  bool is_hit_flying_enemys_[kMaxEnemyNum];

  /// <summary>
  /// プレイヤーが下から出て来る敵と衝突したか(配列の要素番号で下から出て来る敵の何匹目であるか指定)
  /// </summary>
  bool is_hit_jumping_enemys_[kMaxEnemyNum];

  /// <summary>
  /// プレイヤーの残数
  /// </summary>
  int player_num_;

  /// <summary>
  /// プレイヤーと敵の衝突の種類
  /// </summary>
  Collision::PlayerEnemyCollisionType collision_type_;

  /// </summary>
  // フェードが終わったかの有無を受け取る変数
  /// </summary>
  bool is_fade_end_;

  /// </summary>
  // ステージの種類
  /// </summary>
  StageType stage_type_;

  /// </summary>
  // 敵かアイテムの種類
  /// </summary>
  EnemyItemType enemy_item_type_;

  /// <summary>
  /// オーディオマネージャー
  /// </summary>
  AudioManager* audio_manager_;

  /// </summary>
  // プレイヤーが今回フレームでジャンプしたかのフラグ
  /// </summary>
  bool is_player_jump_this_frame_;

  /// </summary>
  // プレイヤーが前回フレームでジャンプしたかのフラグ
  /// </summary>
  bool pre_player_jump_;
};