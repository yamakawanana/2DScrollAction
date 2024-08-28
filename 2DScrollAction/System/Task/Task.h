#pragma once
#include <iostream>
#include "DxLib.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// １種類ごとの敵の数の最大値を定数kMaxEnemyNumに格納する
  /// </summary>
  static const int kMaxEnemyNum = 20;
}

/// <summary>
/// Taskクラス
/// </summary>
class Task {
public:
  /// <summary>
  //列挙型TaskIdを定義する
  /// <summary>
  enum TaskId {
    /// <summary>
    /// 何もない
    /// </summary>
    kNone,

    /// <summary>
    /// ブートレベル
    /// </summary>
    kBootLevelTask,

    /// <summary>
    /// タイトルレベル
    /// </summary>
    kTitleLevelTask,

    /// <summary>
    /// 設定レベル
    /// </summary>
    kSettingLevelTask,

    /// <summary>
    /// 操作説明レベル
    /// </summary>
    kGuideLevelTask,

    /// <summary>
    /// ステージ選択レベル
    /// </summary>
    kStageSelectLevelTask,

    /// <summary>
    /// バトルレベル
    /// </summary>
    kBattleLevelTask,

    /// <summary>
    /// リザルトレベル
    /// </summary>
    kResultLevelTask,

    /// <summary>
    /// フィールドタスク
    /// </summary>
    kField,

    /// <summary>
    /// 下から出てくる敵タスク
    /// </summary>
    kJumpingEnemy,

    /// <summary>
    /// 下から出てくる敵タスクの最大値
    /// </summary>
    kMaxJumpingEnemyNum = kJumpingEnemy + kMaxEnemyNum,

    /// <summary>
    /// 土管
    /// </summary>
    kPipe,

    /// <summary>
    /// ゲームモードタスク
    /// </summary>
    kGameMode,

    /// <summary>
    /// スタートUIタスク
    /// </summary>
    kStartUi,

    /// <summary>
    /// フィニッシュUIタスク
    /// </summary>
    kFinishUi,

    /// <summary>
    /// 1種類目の歩く敵タスク
    /// </summary>
    kFirstWalkingEnemy,

    /// <summary>
    /// 1種類目の歩く敵タスクの最大値
    /// </summary>
    kMaxFirstWalkingEnemyNum = kFirstWalkingEnemy + kMaxEnemyNum,

    /// <summary>
    /// 2種類目の歩く敵タスク
    /// </summary>
    kSecondWalkingEnemy,

    /// <summary>
    /// 2種類目の歩く敵タスクの最大値
    /// </summary>
    kMaxSecondWalkingEnemyNum = kSecondWalkingEnemy + kMaxEnemyNum,

    /// <summary>
    /// 飛ぶ敵タスク
    /// </summary>
    kFlyingEnemy,

    /// <summary>
    /// 飛ぶ敵タスクの最大値
    /// </summary>
    kMaxFlyingEnemyNum = kFlyingEnemy + kMaxEnemyNum,

    /// <summary>
    /// プレイヤータスク
    /// </summary>
    kPlayer,

    /// <summary>
    /// アイテムタスク
    /// </summary>
    kItem,

    /// <summary>
    /// バトル情報UIタスク
    /// </summary>
    kInfoUi,

    /// <summary>
    /// ポーズUIタスク
    /// </summary>
    kPauseUi,

    /// <summary>
    /// カメラタスク
    /// </summary>
    kCamera,

    /// <summary>
    /// 衝突判定タスク
    /// </summary>
    kCollision,

    /// <summary>
    /// BattleFade
    /// </summary>
    kBattleFade,

    /// <summary>
    /// タスク最大値
    /// </summary>
    kTaskMax,
  };

  /// <summary>
  /// デフォルトコンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Task();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Task(TaskId task_id);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~Task();

  /// <summary>
  /// GetId関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>id_</returns>
  TaskId GetId();

  /// <summary>
  /// SetId関数の宣言
  /// </summary>
  /// <param name = "id">TaskId型のid</param>
  /// <returns>なし</returns>
  void SetId(TaskId id);

  /// <summary>
  /// GetTaskUnload関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>task_unload_</returns>
  bool GetTaskUnload();

  /// <summary>
  /// SetTaskUnload関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void SetTaskUnload();

  /// <summary>
  /// ResetTaskUnload関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void ResetTaskUnload();

  /// <summary>
  /// UpdateFrame関数の宣言
  /// </summary>
  /// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
  /// <returns>なし</returns>
  virtual void UpdateFrame(float time);

  /// <summary>
  /// RenderFrame関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  virtual void RenderFrame();

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// </summary>
  //タスクID
  /// </summary>
  TaskId id_;

  /// </summary>
  //タスクを下ろしたかの有無
  /// </summary>
  bool task_unload_;
};