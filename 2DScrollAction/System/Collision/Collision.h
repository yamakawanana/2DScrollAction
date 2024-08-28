#pragma once
#include <map>
#include <array>
#include <queue>
#include "System/Task/Task.h"
#include "System/Task/TaskManager.h"
#include "Game/Field/Field.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
}

/// <summary>
/// Collisionクラス
/// </summary>
class Collision{
public:

  /// <summary>
  //フェーズの種類の列挙型CollisionPhaseType型を定義する
  /// <summary>
  enum CollisionPhaseType {
    /// <summary>
    /// フィールド初期化フェーズ
    /// </summary>
    kCollisionInitialized,

    /// <summary>
    /// プレイヤーの初期化フェーズ
    /// </summary>
    kPlayerInitialized,

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

    /// <summary>
    /// 中断フェーズ
    /// </summary>
    kStop,
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
  //マップの種類の列挙型MapType型を定義する
  /// <summary>
  enum MapType {
    /// <summary>
    /// 何もない
    /// </summary>
    kNone,

    /// <summary>
    /// 地面
    /// </summary>
    kGround,

    /// <summary>
    /// 箱
    /// </summary>
    kBox,

    /// <summary>
    /// 土管の縁部分の右側
    /// </summary>
    kTubeRimRight,

    /// <summary>
    /// 土管の縁部分の真ん中
    /// </summary>
    kTubeRimMiddle,

    /// <summary>
    /// 土管の縁部分の左側
    /// </summary>
    kTubeRimLeft,

    /// <summary>
    /// 土管の縁以外の右側
    /// </summary>
    kTubeRight,

    /// <summary>
    /// 土管の縁以外の真ん中
    /// </summary>
    kTubeMiddle,

    /// <summary>
    /// 土管の縁以外の左側
    /// </summary>
    kTubeLeft,

    /// <summary>
    /// ゴール
    /// </summary>
    kGoal,

    /// <summary>
    /// マップの種類の最大値
    /// </summary>
    kMapMax,
  };

  /// <summary>
  //調べる方向の種類の列挙型DirectionType型を定義する
  /// <summary>
  enum DirectionType {

    /// <summary>
    /// 上
    /// </summary>
    kUp,

    /// <summary>
    /// 下
    /// </summary>
    kDown,

    /// <summary>
    /// 右
    /// </summary>
    kRight,

    /// <summary>
    /// 左
    /// </summary>
    kLeft,

    /// <summary>
    /// 最大値
    /// </summary>
    kMax,
  };

  /// <summary>
  //プレイヤーと敵の衝突判定の種類の列挙型PlayerEnemyCollisionType型を定義する
  /// <summary>
  enum PlayerEnemyCollisionType {

    /// <summary>
    /// 敵を倒した
    /// </summary>
    kAttackEnemy,

    /// <summary>
    /// ダメージを受けた
    /// </summary>
    kDamage,

    /// <summary>
    /// ダメージを受けてからの待ち時間
    /// </summary>
    kDamageWait,

    /// <summary>
    /// 衝突していない
    /// </summary>
    kCollisionNone,
  };

  /// <summary>
  //敵の種類の列挙型EnemyType型を定義する
  /// <summary>
  enum EnemyType {

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
  };

private:

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Collision(int stage_num);

public:

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~Collision();

  /// <summary>
  /// インスタンスを生成する
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  static void CreateInstance(int stage_num);

  /// <summary>
  /// インスタンスを取得する
  /// </summary>
  /// <param>なし</param>
  /// <returns>インスタンス</returns>
  static Collision* GetInstance();

  /// <summary>
  /// インスタンスを解放する
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  static void ReleaseInstance();

  /// <summary>
  /// 初期化処理
  /// </summary>
  /// <param name></param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool PhaseInitialize();

  /// <summary>
  /// mapdata_の指定位置の要素を変更する関数
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "maptype">マップの種類</param>
  /// <returns>なし</returns>
  void SetMapType(int x, int y, MapType maptype);

  /// <summary>
  /// mapdata_の指定位置の要素を返す関数
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <returns>マップの種類</returns>
  MapType GetMapType(int x, int y);

  /// <summary>
  /// SetPlayerXPos関数の宣言
  /// </summary>
  /// <param = "player_x_pos">プレイヤーのX位置</param>
  /// <returns>なし</returns>
  void SetPlayerXPos(int player_x_pos);

  /// <summary>
  /// IsFootGround関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "character_size">キャラクター画像の幅と高さ</param>
  /// <returns>プレイヤーの足元に地面かブロックがあるかの有無</returns>
  bool IsFootGround(int& x, int& y, int character_height);

  /// <summary>
  /// IsHitRight関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "character_size">キャラクター画像の幅と高さ</param>
  /// <returns>プレイヤーの右側に地面かブロックがあるかの有無</returns>
  bool IsHitRight(int& x, int y, int character_size);

  /// <summary>
  /// IsHitLeft関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "character_size">キャラクター画像の幅と高さ</param>
  /// <returns>プレイヤーの左側に地面かブロックがあるかの有無</returns>
  bool IsHitLeft(int& x, int y, int character_size);

  /// <summary>
  /// IsHitHead関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "character_size">キャラクター画像の幅と高さ</param>
  /// <returns>プレイヤーの頭側に地面かブロックがあるかの有無</returns>
  bool IsHitHead(int x, int y, int character_size);

  /// <summary>
  /// InitializeMapData関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns></returns>
  void InitializeMapData();

  /// <summary>
  /// IsPileBottom関数の宣言
  /// </summary>
  /// <returns>プレイヤーの足元が地面かブロックと重なっているかの有無</returns>
  bool IsPileBottom();

  /// <summary>
  /// IsPileRight関数の宣言
  /// </summary>
  /// <returns>プレイヤーの右が地面かブロックと重なっているかの有無</returns>
  bool IsPileRight();

  /// <summary>
  /// IsPileLeft関数の宣言
  /// </summary>
  /// <returns>プレイヤーの左が地面かブロックと重なっているかの有無</returns>
  bool IsPileLeft();

  /// <summary>
  /// IsHitPlayerEnemy関数の宣言
  /// </summary>
  /// <param = "player_x">プレイヤーX位置</param>
  /// <param = "player_y">プレイヤーY位置</param>
  /// <param = "player_size">プレイヤー画像の幅と高さ</param>
  /// <param = "enemy_x">敵X位置</param>
  /// <param = "enemy_y">敵Y位置</param>
  /// <param = "enemy_width">敵の画像の幅</param>
  /// <param = "enemy_height">敵の画像の高さ</param>
  /// <returns>プレイヤーが敵とぶつかっているかの有無</returns>
  bool IsHitPlayerEnemy(int player_x, int player_y, int player_size, int enemy_x, int enemy_y, int enemy_width, int enemy_height, Task::TaskId enemy_id);

  /// <summary>
  /// SetPlayerEnemyCollisionType関数の宣言
  /// </summary>
  /// <param = "type">プレイヤーと敵の衝突判定の種類</param>
  /// <returns>なし</returns>
  void SetPlayerEnemyCollisionType(PlayerEnemyCollisionType type);

  /// <summary>
  /// GetPlayerEnemyCollisionType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>プレイヤーと敵の衝突判定の種類</returns>
  PlayerEnemyCollisionType GetPlayerEnemyCollisionType();

  /// <summary>
  /// IsHitPlayerItem関数の宣言
  /// </summary>
  /// <param = "player_x">プレイヤーX位置</param>
  /// <param = "player_y">プレイヤーY位置</param>
  /// <param = "player_size">プレイヤー画像の幅と高さ</param>
  /// <param = "items_x">アイテムX位置</param>
  /// <param = "items_y">アイテムY位置</param>
  /// <param = "items_width">アイテムの画像の幅</param>
  /// <param = "items_height">アイテムの画像の高さ</param>
  /// <returns>プレイヤーがアイテムとぶつかっているかの有無</returns>
  bool IsHitPlayerItem(int player_x, int player_y, int player_size, int items_x, int items_y, int items_width, int items_height, Task::TaskId items_id);

  /// <summary>
  /// IsPlayerWithTube関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "character_size">キャラクター画像の幅と高さ</param>
  /// <returns>プレイヤーが土管の周りに立っているかの有無</returns>
  bool IsPlayerWithTube(int x, int y, int character_size);

  /// <summary>
  /// IsPlayerGoal関数の宣言
  /// </summary>
  /// <param = "x">プレイヤーX位置</param>
  /// <param = "y">プレイヤーY位置</param>
  /// <param = "character_size">プレイヤー画像の幅と高さ</param>
  /// <returns>プレイヤーがゴールしたかの有無</returns>
  bool IsPlayerGoal(int x, int y, int character_size);

  /// <summary>
  /// SetStageNum関数
  /// </summary>
  /// <param = "stage_num">現在のステージ</param>
  /// <returns>なし</returns>
  void SetStageNum(int stage_num);

  /// <summary>
  /// IsHitRightFoot関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "character_size">キャラクター画像の幅と高さ</param>
  /// <returns>プレイヤーの右側足元に地面かブロックがあるかの有無</returns>
  bool IsHitRightFoot(int& x, int y, int character_size);

  /// <summary>
  /// IsHitLeftFoot関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "character_size">キャラクター画像の幅と高さ</param>
  /// <returns>プレイヤーの左側足元に地面かブロックがあるかの有無</returns>
  bool IsHitLeftFoot(int& x, int y, int character_size);

  /// <summary>
  /// IsHitRightHead関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "character_size">キャラクター画像の幅と高さ</param>
  /// <returns>プレイヤーの右側の真上にブロックがあるかの有無</returns>
  bool IsHitRightHead(int& x, int y, int character_size);

  /// <summary>
  /// IsHitLeftHead関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "character_size">キャラクター画像の幅と高さ</param>
  /// <returns>プレイヤーの左側の真上にブロックがあるかの有無</returns>
  bool IsHitLeftHead(int& x, int y, int character_size);

protected:
  /// <summary>
  /// メンバ変数
  /// </summary>

private:

  /// <summary>
  /// 毎フレーム更新処理のフェーズ処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool PhaseUpdate(float time);

  /// <summary>
  /// 終了処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool PhaseFinalize(float time);

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// </summary>
  //インスタンス
  /// </summary>
  static Collision* collision_;

  /// </summary>
  //マップの種類
  /// </summary>
  MapType map_type_;

  /// </summary>
  //フェーズの種類
  /// </summary>
  CollisionPhaseType collision_phase_type_;

  /// </summary>
  //現在のフェーズ
  /// </summary>
  CollisionPhaseType now_phase_;

  /// </summary>
  //プレイヤーと敵の衝突判定の種類
  /// </summary>
  PlayerEnemyCollisionType player_enemy_collisiontype_;

  /// <summary>
  /// フィールド情報
  /// </summary>
  MapType mapdata_[kTotalRow][kTotalColumn];

  /// <summary>
  /// 前回フレームでのレベル
  /// </summary>
  int pre_level_;

  /// <summary>
  /// インデックス
  /// </summary>
  int index_;

  /// <summary>
  /// プレイヤーのX位置
  /// </summary>
  int player_x_pos_;

  /// </summary>
  // プレイヤーの足元に地面かブロックがあるかの有無を受け取る変数
  /// </summary>
  bool is_ground_;

  /// </summary>
  // プレイヤーの足元が物体と重なっているかの有無を受け取る変数
  /// </summary>
  bool is_pile_bottom_;

  /// </summary>
  // プレイヤーの右が物体と重なっているかの有無を受け取る変数
  /// </summary>
  bool is_pile_right_;

  /// </summary>
  // プレイヤーの左が物体と重なっているかの有無を受け取る変数
  /// </summary>
  bool is_pile_left_;

  /// </summary>
  // 敵の種類
  /// </summary>
  EnemyType enemy_type_;

  /// <summary>
  /// プレイヤーが土管の周りに立っているかの有無
  /// </summary>
  bool is_player_tube_;

  /// </summary>
  // ステージの種類
  /// </summary>
  StageType stage_type_;
};