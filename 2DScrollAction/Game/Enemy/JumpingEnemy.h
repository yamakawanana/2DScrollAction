#pragma once
#include "System/Task/Task.h"
#include "System/Task/TaskManager.h"
#include "Game/Field/Field.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// 敵がヒットした時の画像の横向きの分割数を定数kJumpingEnemyHitXに格納する
  /// </summary>
  static const int kJumpingEnemyHitX = 5;

  // <summary>
  //敵がジャンプしている時の画像の横向きの分割数を定数kJumpingEnemyJumpingXに格納する
  /// <summary>
  static const int kJumpingEnemyJumpingX = 4;

}

/// <summary>
/// JumpingEnemyクラス
/// </summary>
class JumpingEnemy : public Task {
public:

  /// <summary>
  /// フェーズの種類
  /// </summary>
  enum PhaseType {
    /// <summary>
    /// 準備中
    /// </summary>
    kPreraration,

    /// <summary>
    /// プレイ中
    /// </summary>
    kPlaying,

    /// <summary>
    /// プレイ中断
    /// </summary>
    kStop,

    /// <summary>
    /// 終了フェーズ
    /// </summary>
    kFinish,

    /// <summary>
    /// フェーズの種類の最大数
    /// </summary>
    kMax,
  };

  /// <summary>
  //方向の種類の列挙型DirectionType型を定義する
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
    /// 何もない
    /// </summary>
    kNone,
  };

  /// <summary>
  //状態の種類の列挙型StatusType型を定義する
  /// <summary>
  enum StatusType {
    /// <summary>
    /// ジャンプ
    /// </summary>
    kJump,

    /// <summary>
    /// 上で待機
    /// </summary>
    kIdolUp,

    /// <summary>
    /// 着地
    /// </summary>
    kFall,

    /// <summary>
    /// 下で待機
    /// </summary>
    kIdolDown,

    /// <summary>
    /// ヒット
    /// </summary>
    kHit,

    /// <summary>
    /// 落下
    /// </summary>
    kDrop,

    /// <summary>
    /// 最大値
    /// </summary>
    kEnemyMax,
  };

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  JumpingEnemy(Task task_id, TaskManager * task_manager);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~JumpingEnemy();

  /// <summary>
  /// 毎フレーム更新処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>なし</returns>
  void UpdateFrame(float time) override;

  /// 毎フレーム描画処理
  /// </remarks>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void RenderFrame() override;

  /// <summary>
  /// SetXPosition関数の宣言
  /// </summary>
  /// <param = "x_coordinate">X座標</param>
  /// <returns>なし</returns>
  void SetXPosition(int x_coordinate);

  /// <summary>
  /// GetXPosition関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>X座標</returns>
  int GetXPosition();

  /// <summary>
  /// SetYPosition関数の宣言
  /// </summary>
  /// <param = "y_coordinate">Y座標</param>
  /// <returns>なし</returns>
  void SetYPosition(int y_coordinate);

  /// <summary>
  /// GetYPosition関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>Y座標</returns>
  int GetYPosition();

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
  /// SetDirectionType関数の宣言
  /// </summary>
  /// <param = "direction">方向の種類</param>
  /// <returns>なし</returns>
  void SetDirectionType(DirectionType direction);

  /// <summary>
  /// GetDirectionType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>方向の種類</returns>
  DirectionType GetDirectionType();

  /// <summary>
  /// SetPhaseType関数の宣言
  /// </summary>
  /// <param = "type">フェーズの種類</param>
  /// <returns>なし</returns>
  void SetPhaseType(PhaseType type);

  /// <summary>
  /// GetPhaseType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>フェーズの種類</returns>
  PhaseType GetPhaseType();

  /// <summary>
  /// SetDisplayXPosition関数の宣言
  /// </summary>
  /// <param = "display_x_coordinate">表示用のX座標</param>
  /// <returns>なし</returns>
  void SetDisplayXPosition(float display_x_coordinate);

  /// <summary>
  /// GetDisplayXPosition関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>表示用のX座標</returns>
  float GetDisplayXPosition();

  /// <summary>
  /// SetDisplayYPosition関数の宣言
  /// </summary>
  /// <param = "display_y_coordinate">表示用のY座標</param>
  /// <returns>なし</returns>
  void SetDisplayYPosition(float display_y_coordinate);

  /// <summary>
  /// GetDisplayYPosition関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>表示用のY座標</returns>
  float GetDisplayYPosition();

  /// <summary>
  /// GetPieceTop関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>最上部の位置</returns>
  int GetPieceTop();

  /// <summary>
  /// GetPieceBottom関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>最下部の位置</returns>
  int GetPieceBottom();

  /// <summary>
  /// GetPieceLeft関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>最左部の位置</returns>
  int GetPieceLeft();

  /// <summary>
  /// GetPieceRight関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>最右部の位置</returns>
  int GetPieceRight();

  /// <summary>
  /// SetHitBottom関数の宣言
  /// </summary>
  /// <param = ""></param>
  /// <returns>なし</returns>
  void SetHitBottom(bool is_hit_bottom);

  /// <summary>
  /// SetHitRight関数の宣言
  /// </summary>
  /// <param = ""></param>
  /// <returns>なし</returns>
  void SetHitRight();

  /// <summary>
  /// SetHitLeft関数の宣言
  /// </summary>
  /// <param = ""></param>
  /// <returns>なし</returns>
  void SetHitLeft();

  /// <summary>
  /// SetHit関数の宣言
  /// </summary>
  /// <param = "is_hit"></param>
  /// <returns>なし</returns>
  void SetHit(bool is_hit);

  /// <summary>
  /// IsHit関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>他と衝突したかの有無</returns>
  bool IsHit();

  /// <summary>
  /// 下に移動する時に衝突するかを確認する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  int CheckIsHitEnemyBasesBottom();

  /// <summary>
  /// SetMoveSoundHandle関数の宣言
  /// </summary>
  /// <param = "move_sound_handle">サウンドハンドル</param>
  /// <returns>なし</returns>
  void SetMoveSoundHandle(int move_sound_handle);

  /// <summary>
  /// GetMoveSoundHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>サウンドハンドル</returns>
  int GetMoveSoundHandle();

  /// <summary>
  /// SetXMoveSoundHandle関数の宣言
  /// </summary>
  /// <param = "move_handle">サウンドハンドル</param>
  /// <returns>なし</returns>
  void SetXMoveSoundHandle(int move_handle);

  /// <summary>
  /// GetXMoveSoundHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>サウンドハンドル</returns>
  int GetXMoveSoundHandle();

  /// <summary>
  /// SetSoundVolume関数の宣言
  /// </summary>
  /// <param = "sound_volume">音量</param>
  /// <returns>なし</returns>
  void SetSoundVolume(int sound_volume);

  /// <summary>
  /// SetJumpingGrHandle関数の宣言
  /// </summary>
  /// <param = "walking_gr_handle">ジャンプ時のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetJumpingGrHandle(std::array<int, kJumpingEnemyJumpingX> walking_gr_handle);

  /// <summary>
  /// GetJumpingGrHandle関数の宣言
  /// </summary>
  /// <param = "element_num">要素番号</param>
  /// <returns>ジャンプ時のグラフィックハンドル</returns>
  int GetJumpingGrHandle(int element_num);

  /// <summary>
  /// SetDifferenceXpos関数の宣言
  /// </summary>
  /// <param = "difference_x_pos">フィールドの描画X位置を調整するための整数</param>
  /// <returns>なし</returns>
  void SetDifferenceXpos(int difference_x_pos);

  /// <summary>
  /// SetStatusType宣言
  /// </summary>
  /// <param = "status_type">敵の状態</param>
  /// <returns>なし</returns>
  void SetStatusType(StatusType status_type);

  /// <summary>
  /// GetStatusType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>敵の状態</returns>
  StatusType GetStatusType();

  /// <summary>
  /// CalculateJumpSpeed関数の宣言
  /// </summary>
  /// <param ="time">毎フレーム更新時間</param>
  /// <returns>なし</returns>
  float CalculateJumpSpeed(float time);

  /// <summary>
  /// SetPlayerWithTube宣言
  /// </summary>
  /// <param = "is_player_tube">プレイヤーが土管の周りに立っているかの有無</param>
  /// <returns>なし</returns>
  void SetPlayerWithTube(bool is_player_tube);

protected:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// </summary>
  //現在のフェーズ
  /// </summary>
  PhaseType now_phase_;

  /// </summary>
  //タスクマネージャーのポインタ
  /// </summary>
  TaskManager* task_manager_;

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// <summary>
  /// ジャンプ時の敵のグラフィックハンドル
  /// </summary>
  std::array<int, kJumpingEnemyJumpingX> jump_gr_handle_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float accumulation_time_;

  /// <summary>
  /// 待機の累積時間（秒）
  /// </summary>
  float wait_accumulation_time_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float drop_accumulation_time_;

  /// <summary>
  /// 落下時のフレーム累積回数
  /// </summary>
  float fall_accumulation_count_;

  /// <summary>
  /// X座標
  /// </summary>
  int x_coordinate_;

  /// <summary>
  /// Y座標
  /// </summary>
  int y_coordinate_;

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

  /// </summary>
  //現在の向き
  /// </summary>
  DirectionType now_direction_;

  /// <summary>
  /// 表示用のX座標
  /// </summary>
  float display_x_coordinate_;

  /// <summary>
  /// 表示用のY座標
  /// </summary>
  float display_y_coordinate_;

  /// <summary>
  /// 最下部の位置
  /// </summary>
  int piece_bottom_;

  /// <summary>
  /// 最上部の位置
  /// </summary>
  int piece_top_;

  /// <summary>
  /// 最左部の位置
  /// </summary>
  int piece_left_;

  /// <summary>
  /// 最右部の位置
  /// </summary>
  int piece_right_;

  /// <summary>
  /// 下に移動する時に他とぶつかっているかの有無
  /// </summary>
  bool is_hit_bottom_;

  /// <summary>
  /// 右に移動する時に他とぶつかっているかの有無
  /// </summary>
  bool is_hit_right_;

  /// <summary>
  /// 左に移動する時に他とぶつかっているかの有無
  /// </summary>
  bool is_hit_left_;

  /// <summary>
  /// 他とぶつかっているかの有無
  /// </summary>
  bool is_hit_;

  /// <summary>
  /// サウンドハンドル
  /// </summary>
  int move_sound_handle_;

  /// <summary>
  /// 移動のサウンドハンドル
  /// </summary>
  int move_handle_;

  /// <summary>
  /// 音量
  /// </summary>
  int sound_volume_;

  /// </summary>
  //現在の向き
  /// </summary>
  StatusType status_type_;

  /// <summary>
  /// インデックス
  /// </summary>
  int index_;

  /// <summary>
  /// フィールドの描画X位置を調整するための整数
  /// </summary>
  int difference_x_pos_;

  /// <summary>
  /// プレイヤーが土管の周りに立っているかの有無
  /// </summary>
  bool is_player_tube_;
};