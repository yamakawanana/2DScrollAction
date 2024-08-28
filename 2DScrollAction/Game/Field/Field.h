#pragma once
#include <map>
#include <array>
#include <queue>
#include "System/Task/Task.h"
#include "System/Task/TaskManager.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// フィールドの行数を定数kRowに格納する
  /// </summary>
  static const int kRow = 24;

  /// <summary>
  /// フィールドの列数を定数kColumnに格納する
  /// </summary>
  static const int kColumn = 14;

  /// <summary>
  /// 全体のフィールドの行数を定数kRowに格納する
  /// </summary>
  static const int kTotalRow = 19;

  /// <summary>
  /// 全体のフィールドの列数を定数kTotalColumnに格納する
  /// </summary>
  static const int kTotalColumn = 200;

  /// <summary>
  /// 壁の幅を定数kWallWidthに格納する
  /// </summary>
  static const int kWallWidth = 2;

  /// <summary>
  /// マップチップ一つのドットサイズを定数kMapSizeに格納する
  /// </summary>
  static const int kMapSize = 32;

  /// <summary>
  /// 紙吹雪の画像のグラフィックハンドルの配列の要素数を定数kConfettiElementNumberに格納する
  /// </summary>
  static const int kConfettiElementNumber = 36;

  // <summary>
  //画面の幅を定数kScreenSizeXに格納する
  /// <summary>
  static const int kScreenSizeX = 800;

  // <summary>
  //画面の高さを定数kScreenSizeYに格納する
  /// <summary>
  static const int kScreenSizeY = 600;
}

/// <summary>
/// Fieldクラス
/// </summary>
class Field : public Task {
public:

  /// <summary>
  //フェーズの種類の列挙型FieldPhaseType型を定義する
  /// <summary>
  enum FieldPhaseType {
    /// <summary>
    /// フィールド初期化フェーズ
    /// </summary>
    kFieldInitialized,

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
    /// 箱
    /// </summary>
    kBox,

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
  /// デフォルトコンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Field();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Field(TaskId task_id, TaskManager* task_manager, int stage_num);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~Field();

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
  /// InitializeMapData関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns></returns>
  void InitializeMapData();

  /// <summary>
  /// SetBattleBackGrHandle関数の宣言
  /// </summary>
  /// <param = "battle_back_handle">BattleLevelの背景のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetBattleBackGrHandle(int battle_back_handle);

  /// <summary>
  /// GetBattleBackGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>BattleLevelの背景のグラフィックハンドル</returns>
  int GetBattleBackGrHandle();

  /// <summary>
  /// SetFieldPhaseType関数の宣言
  /// </summary>
  /// <param = "type">フェーズの種類</param>
  /// <returns>なし</returns>
  void SetFieldPhaseType(FieldPhaseType type);

  /// <summary>
  /// GetFieldPhaseType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>フェーズの種類</returns>
  FieldPhaseType GetFieldPhaseType();

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
  /// GetBoxGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>箱のグラフィックハンドル</returns>
  int GetBoxGrHandle();

  /// <summary>
  /// SetBoxGrHandle関数の宣言
  /// </summary>
  /// <param = "box_handle">箱のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetBoxGrHandle(int box_handle);

  /// <summary>
  /// GetGroundGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>地面のグラフィックハンドル</returns>
  int GetGroundGrHandle();

  /// <summary>
  /// SetGroundGrHandle関数の宣言
  /// </summary>
  /// <param = "ground_gr_handle">地面のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetGroundGrHandle(int ground_gr_handle);

  /// <summary>
  /// SetFieldGameOver関数の宣言
  /// </summary>
  /// <param= "is_gameover">ゲームオーバーしたかの有無</param>
  /// <returns></returns>
  void SetFieldGameOver(bool is_gameover);

  /// <summary>
  /// SetConfettiHandle関数の宣言
  /// </summary>
  /// <param = "confetti_handle">紙吹雪のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetConfettiHandle(std::array<int, kConfettiElementNumber> confetti_handle);

  /// <summary>
  /// GetConfettiHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>紙吹雪のグラフィックハンドル</returns>
  int GetConfettiHandle(int element_num);

  /// <summary>
  /// SetPlayerXPos関数の宣言
  /// </summary>
  /// <param = "player_x_pos">プレイヤーのX位置</param>
  /// <returns>なし</returns>
  void SetPlayerXPos(int player_x_pos);

  /// <summary>
  /// SetDifferenceXpos関数の宣言
  /// </summary>
  /// <param = "difference_x_pos">フィールドの描画X位置を調整するための整数</param>
  /// <returns>なし</returns>
  void SetDifferenceXpos(int difference_x_pos);

  /// <summary>
  /// GetDifferenceXpos関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>フィールドの描画X位置を調整するための整数</returns>
  int GetDifferenceXpos();

  /// <summary>
  /// SetStageNum関数
  /// </summary>
  /// <param = "stage_num">現在のステージ</param>
  /// <returns>なし</returns>
  void SetStageNum(int stage_num);

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
  /// 初期化処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool PhaseInitialize(float time);

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
  //マップの種類
  /// </summary>
  MapType map_type_;

  /// </summary>
  //フェーズの種類
  /// </summary>
  FieldPhaseType field_phase_type_;

  /// </summary>
  //現在のフェーズ
  /// </summary>
  FieldPhaseType now_phase_;

  /// <summary>
  /// BattleLevelの背景のグラフィックハンドル
  /// </summary>
  int battle_back_handle_;

  /// <summary>
  /// フィールド情報
  /// </summary>
  MapType mapdata_[kTotalRow][kTotalColumn];

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float accumulation_time_;

  /// <summary>
  /// 箱のグラフィックハンドル
  /// </summary>
  int box_handle_;

  /// <summary>
  /// 地面のグラフィックハンドル
  /// </summary>
  int ground_gr_handle_;

  /// </summary>
  // ゲームオーバーであるかの有無を受け取る変数
  /// </summary>
  bool is_gameover_;

  /// <summary>
  /// インデックス
  /// </summary>
  int index_;

  /// <summary>
  /// 紙吹雪のグラフィックハンドル
  /// </summary>
  std::array<int, kConfettiElementNumber> confetti_handle_;

  /// <summary>
  /// プレイヤーのX位置
  /// </summary>
  int player_x_pos_;

  /// <summary>
  /// フィールドの描画X位置を調整するための整数
  /// </summary>
  int difference_x_pos_;

  /// </summary>
  // プレイヤーの足元に地面かブロックがあるかの有無を受け取る変数
  /// </summary>
  bool is_ground_;

  /// <summary>
  /// フェードイン・フェードアウトで使用する整数
  /// </summary>
  int fade_;

  /// </summary>
  // ステージの種類
  /// </summary>
  StageType stage_type_;
};
