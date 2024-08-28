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
/// Pipeクラス
/// </summary>
class Pipe : public Task {
public:

  /// <summary>
  //フェーズの種類の列挙型PipePhaseType型を定義する
  /// <summary>
  enum PipePhaseType {
    /// <summary>
    /// フィールド初期化フェーズ
    /// </summary>
    kPipeInitialized,

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
  Pipe();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Pipe(TaskId task_id, TaskManager* task_manager, int stage_num);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~Pipe();

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
  /// SetPipePhaseType関数の宣言
  /// </summary>
  /// <param = "type">フェーズの種類</param>
  /// <returns>なし</returns>
  void SetPipePhaseType(PipePhaseType type);

  /// <summary>
  /// GetPipePhaseType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>フェーズの種類</returns>
  PipePhaseType GetPipePhaseType();

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
  /// GetTubeRimLeftGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>土管の縁部分の左側の画像のグラフィックハンドル</returns>
  int GetTubeRimLeftGrHandle();

  /// <summary>
  /// SetTubeRimLeftGrHandle関数の宣言
  /// </summary>
  /// <param = "tube_rim_left_handle">土管の縁部分の左側の画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetTubeRimLeftGrHandle(int tube_rim_left_handle);

  /// <summary>
  /// GetTubeRimMiddleGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>土管の縁部分の真ん中の画像のグラフィックハンドル</returns>
  int GetTubeRimMiddleGrHandle();

  /// <summary>
  /// SetTubeRimMiddleGrHandle関数の宣言
  /// </summary>
  /// <param = "tube_rim_middle_handle">土管の縁部分の真ん中の画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetTubeRimMiddleGrHandle(int tube_rim_middle_handle);

  /// <summary>
  /// SetTubeRimRightGrHandle関数の宣言
  /// </summary>
  /// <param = "tube_rim_right_handle">土管の縁部分の右側の画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetTubeRimRightGrHandle(int tube_rim_right_handle);

  /// <summary>
  /// GetTubeRimRightGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>土管の縁部分の右側の画像のグラフィックハンドル</returns>
  int GetTubeRimRightGrHandle();

  /// <summary>
  /// GetTubeLeftGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>土管の縁以外の左側の画像のグラフィックハンドル</returns>
  int GetTubeLeftGrHandle();

  /// <summary>
  /// SetTubeLeftGrHandle関数の宣言
  /// </summary>
  /// <param = "tube_left_handle">土管の縁以外の左側の画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetTubeLeftGrHandle(int tube_left_handle);

  /// <summary>
  /// GetTubeMiddleGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>土管の縁以外の真ん中の画像のグラフィックハンドル</returns>
  int GetTubeMiddleGrHandle();

  /// <summary>
  /// SetTubeMiddleGrHandle関数の宣言
  /// </summary>
  /// <param = "tube_middle_handle">土管の縁以外の真ん中の画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetTubeMiddleGrHandle(int tube_middle_handle);

  /// <summary>
  /// SetTubeRightGrHandle関数の宣言
  /// </summary>
  /// <param = "tube_right_handle">土管の縁以外の右側の画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetTubeRightGrHandle(int tube_right_handle);

  /// <summary>
  /// GetTubeRightGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>土管の縁以外の右側の画像のグラフィックハンドル</returns>
  int GetTubeRightGrHandle();

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
  PipePhaseType pipe_phase_type_;

  /// </summary>
  //現在のフェーズ
  /// </summary>
  PipePhaseType now_phase_;

  /// <summary>
  /// フィールド情報
  /// </summary>
  MapType mapdata_[kTotalRow][kTotalColumn];

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float accumulation_time_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float display_accumulation_time_;

  /// <summary>
  /// 土管の縁部分の左側の画像のグラフィックハンドル
  /// </summary>
  int tube_rim_left_handle_;

  /// <summary>
  /// 土管の縁部分の真ん中の画像のグラフィックハンドル
  /// </summary>
  int tube_rim_middle_handle_;

  /// <summary>
  /// 土管の縁部分の右側の画像のグラフィックハンドル
  /// </summary>
  int tube_rim_right_handle_;

  /// <summary>
  /// 土管の縁以外の左側の画像のグラフィックハンドル
  /// </summary>
  int tube_left_handle_;

  /// <summary>
  /// 土管の縁以外の真ん中の画像のグラフィックハンドル
  /// </summary>
  int tube_middle_handle_;

  /// <summary>
  /// 土管の縁以外の右側の画像のグラフィックハンドル
  /// </summary>
  int tube_right_handle_;

  /// <summary>
  /// インデックス
  /// </summary>
  int index_;

  /// <summary>
  /// プレイヤーのX位置
  /// </summary>
  int player_x_pos_;

  /// <summary>
  /// フィールドの描画X位置を調整するための整数
  /// </summary>
  int difference_x_pos_;

  /// </summary>
  // ステージの種類
  /// </summary>
  StageType stage_type_;
};