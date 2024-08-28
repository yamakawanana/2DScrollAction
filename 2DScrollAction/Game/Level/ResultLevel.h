#pragma once
#include "System/Level/Level.h"
#include "System/LogConsole/LogConsole.h"
#include "Game/Audio/AudioManager.h"

/// <summary>
/// ResultLevelクラス
/// </summary>
class ResultLevel : public Level{
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
    /// フェーズ
    /// </summary>
    kDelete,
  };

  /// <summary>
// メニューの種類の列挙型MenuOption型を定義する
/// <summary>
  enum MenuOption {
    /// <summary>
    /// リトライ
    /// </summary>
    kRetry,

    /// <summary>
    /// タイトル画面に戻る
    /// </summary>
    kBackTitle,
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
  ResultLevel();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ResultLevel(TaskId task_id, TaskManager* task_manager);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~ResultLevel();

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
  /// SetResultGrHandle関数の宣言
  /// </summary>
  /// <param = "title_handle">Resultのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetResultGrHandle(int title_handle);

  /// <summary>
  /// GetResultGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>Resultのグラフィックハンドル</returns>
  int GetResultGrHandle();

  /// <summary>
  /// SetSelectedButtonGrHandle関数の宣言
  /// </summary>
  /// <param = "selected_button_handle">選択されたボタンを囲む枠のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetSelectedButtonGrHandle(int selected_button_handle);

  /// <summary>
  /// GetSelectedButtonGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>選択されたボタンを囲む枠のグラフィックハンドル</returns>
  int GetSelectedButtonGrHandle();

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
  /// リザルト画面のグラフィックハンドル
  /// </summary>
  int result_handle_;

  /// <summary>
  /// 選択されている項目を囲む枠のグラフィックハンドル
  /// </summary>
  int selected_button_handle_;

  /// <summary>
  /// Enterを押した時のサウンドハンドル
  /// </summary>
  int enter_handle_;

  /// <summary>
  /// カーソル操作時のサウンドハンドル
  /// </summary>
  int cursor_handle_;

  /// <summary>
  /// 音量
  /// </summary>
  int sound_volume_;

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
  /// ゲームクリアかの有無
  /// </summary>
  bool game_clear_;

  /// <summary>
  /// オーディオマネージャー
  /// </summary>
  AudioManager* audio_manager_;
};