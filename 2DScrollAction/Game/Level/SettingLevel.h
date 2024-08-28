#pragma once
#include <array>
#include "DxLib.h"
#include "System/Level/Level.h"
#include "System/LogConsole/LogConsole.h"
#include "Game/Audio/AudioManager.h"

/// <summary>
/// SettingLevelクラス
/// </summary>
class SettingLevel : public Level{
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
  //選択項目の種類の列挙型MenuOption型を定義する
  /// <summary>
  enum MenuOption {

    /// <summary>
    /// 音量
    /// </summary>
    kSoundVolume,

    /// <summary>
    /// バトル画面に遷移する
    /// </summary>
    kGoBattle,

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
  SettingLevel();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  SettingLevel(TaskId task_id, TaskManager* task_manager);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~SettingLevel();

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
  /// SetSettingGrHandle関数の宣言
  /// </summary>
  /// <param = "setting_handle">設定画面のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetSettingGrHandle(int setting_handle);

  /// <summary>
  /// GetSettingGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>設定画面のグラフィックハンドル</returns>
  int GetSettingGrHandle();

  /// <summary>
  /// SetTriangleGrHandle関数の宣言
  /// </summary>
  /// <param = "triangle_handle">三角形の画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetTriangleGrHandle(int triangle_handle);

  /// <summary>
  /// GetTriangleGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>三角形の画像のグラフィックハンドル</returns>
  int GetTriangleGrHandle();

  /// <summary>
  /// SetBgmHandle関数の宣言
  /// </summary>
  /// <param = "bgm_handle">BGMのサウンドハンドル</param>
  /// <returns>なし</returns>
  void SetBgmHandle(int bgm_handle);

  /// <summary>
  /// GetBgmHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>BGMのサウンドハンドル</returns>
  int GetBgmHandle();

  /// <summary>
  /// SetCursorSoundHandle関数の宣言
  /// </summary>
  /// <param = "cursor_handle">カーソル操作のサウンドハンドル</param>
  /// <returns>なし</returns>
  void SetCursorSoundHandle(int cursor_handle);

  /// <summary>
  /// GetCursorSoundHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>カーソル操作のサウンドハンドル</returns>
  int GetCursorSoundHandle();

  /// <summary>
  /// SetNextLevelSoundHandle関数の宣言
  /// </summary>
  /// <param = "next_level_handle">次のレベルに遷移する時のサウンドハンドル</param>
  /// <returns>なし</returns>
  void SetNextLevelSoundHandle(int next_level_handle);

  /// <summary>
  /// GetNextLevelSoundHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>次のレベルに遷移する時のサウンドハンドル</returns>
  int GetNextLevelSoundHandle();

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
  /// SetButtonOnGrHandle関数の宣言
  /// </summary>
  /// <param = "on_button_handle">押されているボタンのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetButtonOnGrHandle(int on_button_handle);

  /// <summary>
  /// GetButtonOnGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>押されているボタンのグラフィックハンドル</returns>
  int GetButtonOnGrHandle();

  /// <summary>
  /// SetButtonOffGrHandle関数の宣言
  /// </summary>
  /// <param = "off_button_handle">押されていないボタンのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetButtonOffGrHandle(int off_button_handle);

  /// <summary>
  /// GetButtonOffGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>押されていないボタンのグラフィックハンドル</returns>
  int GetButtonOffGrHandle();

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
  /// メニューの種類
  /// </summary>
  MenuOption menu_type_;

  /// <summary>
  /// 設定画面背景のグラフィックハンドル
  /// </summary>
  int setting_handle_;

  /// <summary>
  /// 三角形の画像のグラフィックハンドル
  /// </summary>
  int triangle_handle_;

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
  /// 次のレベルに遷移する時のサウンドハンドル
  /// </summary>
  int next_level_handle_;

  /// <summary>
  /// カーソル操作時のサウンドハンドル
  /// </summary>
  int cursor_handle_;

  /// <summary>
  /// メニューの選択に使うインデックス
  /// </summary>
  int select_index_;

  /// <summary>
  /// 音量
  /// </summary>
  int sound_volume_;

  /// <summary>
  /// 押されているボタンのグラフィックハンドル
  /// </summary>
  int on_button_handle_;

  /// <summary>
  /// 押されていないボタンのグラフィックハンドル
  /// </summary>
  int off_button_handle_;

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
  /// オーディオマネージャー
  /// </summary>
  AudioManager* audio_manager_;
};