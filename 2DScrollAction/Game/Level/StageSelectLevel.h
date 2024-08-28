#pragma once
#include "DxLib.h"
#include "System/Level/Level.h"
#include "System/LogConsole/LogConsole.h"
#include "Game/Audio/AudioManager.h"

/// <summary>
/// StageSelectLevelクラス
/// </summary>
class StageSelectLevel : public Level {
public:

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
  // メニューの種類の列挙型MenuOption型を定義する
  /// <summary>
  enum MenuOption {
    /// <summary>
    /// ステージ1
    /// </summary>
    kStageOne,

    /// <summary>
    /// ステージ2
    /// </summary>
    kStageTwo,

    /// <summary>
    /// ステージ3
    /// </summary>
    kStageThree,

    /// <summary>
    /// タイトルへ
    /// </summary>
    kGoTitle
  };

  /// <summary>
  // 星の角度の列挙型AngleType型を定義する
  /// <summary>
  enum AngleType {
    /// <summary>
    /// 0度
    /// </summary>
    kAngle0,

    /// <summary>
    /// 45度
    /// </summary>
    kAngle45,

    /// <summary>
    /// 90度
    /// </summary>
    kAngle90,

    /// <summary>
    /// 135度
    /// </summary>
    kAngle135,

    /// <summary>
    /// 180度
    /// </summary>
    kAngle180,

    /// <summary>
    /// 225度
    /// </summary>
    kAngle225,

    /// <summary>
    /// 270度
    /// </summary>
    kAngle270,

    /// <summary>
    /// 315度
    /// </summary>
    kAngle315,
  };

  /// <summary>
  /// デフォルトコンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  StageSelectLevel();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  StageSelectLevel(TaskId task_id, TaskManager* task_manager);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~StageSelectLevel();

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
  /// SetStageGrHandle関数の宣言
  /// </summary>
  /// <param = "stage_handle">ステージ選択背景のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetStageGrHandle(int stage_handle);

  /// <summary>
  /// GetStageGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ステージ選択背景のグラフィックハンドル</returns>
  int GetStageGrHandle();

  /// <summary>
  /// SetWidth関数の宣言
  /// </summary>
  /// <param>画像の幅</param>
  /// <returns>なし</returns>
  void SetWidth(int size_x);

  /// <summary>
  /// GetWidth関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の幅</returns>
  int GetWidth();

  /// <summary>
  /// SetHeight関数の宣言
  /// </summary>
  /// <param>画像の高さ</param>
  /// <returns>なし</returns>
  void SetHeight(int size_y);

  /// <summary>
  /// GetHeight関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の高さ</returns>
  int GetHeight();

  /// <summary>
  /// SetHalfWidth関数の宣言
  /// </summary>
  /// <param>画像の幅</param>
  /// <returns>なし</returns>
  void SetHalfWidth(float size_half_x);

  /// <summary>
  /// GetHalfWidth関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の幅の半分</returns>
  float GetHalfWidth();

  /// <summary>
  /// SetHalfHeight関数の宣言
  /// </summary>
  /// <param>画像の高さ</param>
  /// <returns>なし</returns>
  void SetHalfHeight(float size_half_y);

  /// <summary>
  /// GetHalfHeight関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の高さの半分</returns>
  float GetHalfHeight();

  /// <summary>
  /// SetStarGrHandle関数の宣言
  /// </summary>
  /// <param = "star_gr_handle">星のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetStarGrHandle(int star_gr_handle);

  /// <summary>
  /// GetStarGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>星のグラフィックハンドル</returns>
  int GetStarGrHandle();

  /// <summary>
  /// SetStageOneGrHandle関数の宣言
  /// </summary>
  /// <param = "stage_one_handle">ステージ1の画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetStageOneGrHandle(int stage_one_handle);

  /// <summary>
  /// GetStageOneGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ステージ1の画像のグラフィックハンドル</returns>
  int GetStageOneGrHandle();

  /// <summary>
  /// SetStageTwoGrHandle関数の宣言
  /// </summary>
  /// <param = "stage_two_handle">ステージ2の画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetStageTwoGrHandle(int stage_two_handle);

  /// <summary>
  /// GetStageTwoGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ステージ2の画像のグラフィックハンドル</returns>
  int GetStageTwoGrHandle();

  /// <summary>
  /// SetStageThreeGrHandle関数の宣言
  /// </summary>
  /// <param = "stage_three_handle">ステージ3の画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetStageThreeGrHandle(int stage_three_handle);

  /// <summary>
  /// GetStageThreeGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ステージ3の画像のグラフィックハンドル</returns>
  int GetStageThreeGrHandle();

  /// <summary>
  /// SetLockGrHandle関数の宣言
  /// </summary>
  /// <param = "lock_handle">鍵の画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetLockGrHandle(int lock_handle);

  /// <summary>
  /// GetLockGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>鍵の画像のグラフィックハンドル</returns>
  int GetLockGrHandle();

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
  /// 終了フェーズの種類
  /// </summary>
  EndPhaseType end_type_;

  /// <summary>
  /// ステージ選択画面のグラフィックハンドル
  /// </summary>
  int stage_handle_;

  /// <summary>
  /// 画像の幅
  /// </summary>
  int width_;

  /// <summary>
  /// 画像の高さ
  /// </summary>
  int height_;

  /// <summary>
  /// 画像の幅の半分
  /// </summary>
  float half_width_;

  /// <summary>
  /// 画像の高さの半分
  /// </summary>
  float half_height_;

  /// <summary>
  /// BGMサウンドハンドル
  /// </summary>
  int bgm_handle_;

  /// <summary>
  /// Enterを押した時のサウンドハンドル
  /// </summary>
  int enter_handle_;

  /// <summary>
  /// カーソル操作時のサウンドハンドル
  /// </summary>
  int cursor_handle_;

  /// <summary>
  /// メニューの種類
  /// </summary>
  MenuOption menu_type_;

  /// <summary>
  /// メニューの選択に使うインデックス
  /// </summary>
  int select_index_;

  /// <summary>
  /// フェードイン・フェードアウトで使用する整数
  /// </summary>
  int fade_;

  /// <summary>
  /// エンターを押されたかの有無
  /// </summary>
  bool is_enter_;

  /// <summary>
  /// 星の画像のグラフィックハンドル
  /// </summary>
  int star_gr_handle_;

  /// <summary>
  /// 角度情報
  /// </summary>
  AngleType angle_type_;

  /// <summary>
  /// ステージ1の画像のグラフィックハンドル
  /// </summary>
  int stage_one_handle_;

  /// <summary>
  /// ステージ2の画像のグラフィックハンドル
  /// </summary>
  int stage_two_handle_;

  /// <summary>
  /// ステージ3の画像のグラフィックハンドル
  /// </summary>
  int stage_three_handle_;

  /// <summary>
  /// 鍵の画像のグラフィックハンドル
  /// </summary>
  int lock_handle_;

  /// <summary>
  /// オーディオマネージャー
  /// </summary>
  AudioManager* audio_manager_;
};
