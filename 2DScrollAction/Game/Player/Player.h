#pragma once
#include "Game/Player/Player.h"
#include "System/Task/Task.h"
#include "System/Task/TaskManager.h"
#include "Game/Field/Field.h"
#include "System/Collision/Collision.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// プレイヤーがヒットした時の画像の横向きの分割数を定数kPlayerHitXに格納する
  /// </summary>
  static const int kPlayerHitX = 7;

  // <summary>
  //プレイヤーが待機している時の画像の横向きの分割数を定数kPlayerIdlingXに格納する
  /// <summary>
  static const int kPlayerIdlingX = 11;

  // <summary>
  //プレイヤーが歩いている時の画像の横向きの分割数を定数kPlayerWalkingXに格納する
  /// <summary>
  static const int kPlayerWalkingX = 12;

  /// <summary>
  /// ダッシュ時のエフェクトの画像の横向きの分割数を定数kDashEffectXに格納する
  /// </summary>
  static const int kDashEffectX = 8;

  // <summary>
  //ダッシュ時のエフェクトの画像の幅と高さを定数kDashEffectSizeに格納する
  /// <summary>
  static const int kDashEffectSize = 96;

  /// <summary>
  /// ジャンプ時のエフェクトの画像の横向きの分割数を定数kJumpEffectXに格納する
  /// </summary>
  static const int kJumpEffectX = 6;

  // <summary>
  //ダッシュ時のエフェクトの画像の幅と高さを定数kJumpEffectSizeに格納する
  /// <summary>
  static const int kJumpEffectSize = 64;

  /// <summary>
  /// プレイヤー落下時の星が散るエフェクトの画像の横向きの分割数を定数kStarEffectXに格納する
  /// </summary>
  static const int kStarEffectX = 5;

  /// <summary>
  /// プレイヤー落下時の星が散るエフェクトの画像の縦向きの分割数を定数kStarEffectYに格納する
  /// </summary>
  static const int kStarEffectY = 2;

  // <summary>
  //プレイヤーの画像の幅と高さを定数kPlayerSizeに格納する
  /// <summary>
  static const int kPlayerSize = 64;
}

/// <summary>
/// Playerクラス
/// </summary>
class Player : public Task{
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
    /// 待機(右向き)
    /// </summary>
    kIdolRight,

    /// <summary>
    /// 待機(左向き)
    /// </summary>
    kIdolLeft,

    /// <summary>
    /// 歩行(右向き)
    /// </summary>
    kWalkRight,

    /// <summary>
    /// 歩行(左向き)
    /// </summary>
    kWalkLeft,

    /// <summary>
    /// ヒット(右向き)
    /// </summary>
    kHitRight,

    /// <summary>
    /// ヒット(左向き)
    /// </summary>
    kHitLeft,

    /// <summary>
    /// ジャンプ(右向き)
    /// </summary>
    kJumpRight,

    /// <summary>
    /// ジャンプ(左向き)
    /// </summary>
    kJumpLeft,

    /// <summary>
    /// 着地(右向き)
    /// </summary>
    kFallRight,

    /// <summary>
    /// 着地(左向き)
    /// </summary>
    kFallLeft,

    /// <summary>
    /// 最大値
    /// </summary>
    kPlayerMax,

    /// <summary>
    /// 落下
    /// </summary>
    kDrop,

    /// <summary>
    /// 落下時の演出が終わった
    /// </summary>
    kFinishDrop,
  };

  /// <summary>
  // 回転時の角度の列挙型AngleType型を定義する
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
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Player(Task task_id, TaskManager* task_manager);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~Player();

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
  /// <param = "is_hit_right">右に移動する時に他とぶつかっているかの有無</param>
  /// <returns>なし</returns>
  void SetHitRight(bool is_hit_right);

  /// <summary>
  /// SetHitLeft関数の宣言
  /// </summary>
  /// <param = "is_hit_left">左に移動する時に他とぶつかっているかの有無</param>
  /// <returns>なし</returns>
  void SetHitLeft(bool is_hit_left);

  /// <summary>
  /// SetHitHead関数の宣言
  /// </summary>
  /// <param = "is_hit"></param>
  /// <returns>なし</returns>
  void SetHitHead(bool is_hit);

  /// <summary>
  /// IsHitHead関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>他と衝突したかの有無</returns>
  bool IsHitHead();

  /// <summary>
  /// 下に移動する時に衝突するかを確認する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  int CheckIsHitPlayersBottom();

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
  /// SetIdlingGrHandle関数の宣言
  /// </summary>
  /// <param = "idling_gr_handle">待機時のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetIdlingGrHandle(std::array<int, kPlayerIdlingX> idling_gr_handle);

  /// <summary>
  /// GetIdlingGrHandle関数の宣言
  /// </summary>
  /// <param = "element_num">要素番号</param>
  /// <returns>待機時のグラフィックハンドル</returns>
  int GetIdlingGrHandle(int element_num);

  /// <summary>
  /// SetWalkingGrHandle関数の宣言
  /// </summary>
  /// <param = "walking_gr_handle">歩行時のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetWalkingGrHandle(std::array<int, kPlayerWalkingX> walking_gr_handle);

  /// <summary>
  /// GetWalkingGrHandle関数の宣言
  /// </summary>
  /// <param = "element_num">要素番号</param>
  /// <returns>歩行時のグラフィックハンドル</returns>
  int GetWalkingGrHandle(int element_num);

  /// <summary>
  /// SetHitGrHandle関数の宣言
  /// </summary>
  /// <param = "hit_gr_handle">ヒット時のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetHitGrHandle(std::array<int, kPlayerHitX> hit_gr_handle);

  /// <summary>
  /// GetHitGrHandle関数の宣言
  /// </summary>
  /// <param = "element_num">要素番号</param>
  /// <returns>ヒット時のグラフィックハンドル</returns>
  int GetHitGrHandle(int element_num);

  /// <summary>
  /// SetJumpGrHandle関数の宣言
  /// </summary>
  /// <param = "jump_gr_handle">ジャンプ時のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetJumpGrHandle(int jump_gr_handle);

  /// <summary>
  /// GetJumpGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ジャンプ時のグラフィックハンドル</returns>
  int GetJumpGrHandle();

  /// <summary>
  /// SetFallGrHandle関数の宣言
  /// </summary>
  /// <param = "fall_gr_handle">着地時のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetFallGrHandle(int fall_gr_handle);

  /// <summary>
  /// GetFallGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>着地時のグラフィックハンドル</returns>
  int GetFallGrHandle();

  /// <summary>
  /// SetDashEffectGrHandle関数の宣言
  /// </summary>
  /// <param = "dash_effect_gr_handle">ダッシュ時のエフェクトのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetDashEffectGrHandle(std::array<int, kDashEffectX> dash_effect_gr_handle);

  /// <summary>
  /// GetDashEffectGrHandle関数の宣言
  /// </summary>
  /// <param = "element_num">要素番号</param>
  /// <returns>ダッシュ時のエフェクトのグラフィックハンドル</returns>
  int GetDashEffectGrHandle(int element_num);

  /// <summary>
  /// SetJumpEffectGrHandle関数の宣言
  /// </summary>
  /// <param = "jump_effect_gr_handle">ジャンプ時のエフェクトのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetJumpEffectGrHandle(std::array<int, kJumpEffectX> jump_effect_gr_handle);

  /// <summary>
  /// GetJumpEffectGrHandle関数の宣言
  /// </summary>
  /// <param = "element_num">要素番号</param>
  /// <returns>ジャンプ時のエフェクトのグラフィックハンドル</returns>
  int GetJumpEffectGrHandle(int element_num);

  /// <summary>
  /// SetDifferenceXpos関数の宣言
  /// </summary>
  /// <param = "difference_x_pos">フィールドの描画X位置を調整するための整数</param>
  /// <returns>なし</returns>
  void SetDifferenceXpos(int difference_x_pos);

  /// <summary>
  /// SetFootGround関数の宣言
  /// </summary>
  /// <param = "is_ground">プレイヤーの足元に地面やブロックがあるかの有無</param>
  /// <returns>なし</returns>
  void SetFootGround(bool is_ground);

  /// <summary>
  /// GetStatusType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>プレイヤーの状態</returns>
  StatusType GetStatusType();

  /// <summary>
  /// SetStatusType宣言
  /// </summary>
  /// <param = "status_type">プレイヤーの状態</param>
  /// <returns>なし</returns>
  void SetStatusType(StatusType status_type);

  /// <summary>
  /// IsDash関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>プレイヤーの状態</returns>
  bool IsDash();

  /// <summary>
  /// SetStarEffectGrHandle関数の宣言
  /// </summary>
  /// <param = "star_effect_gr_handle">プレイヤー落下時の星のエフェクトのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetStarEffectGrHandle(std::array<int, (kStarEffectX * kStarEffectY)> star_effect_gr_handle);

  /// <summary>
  /// GetStarEffectGrHandle関数の宣言
  /// </summary>
  /// <param = "element_num">要素番号</param>
  /// <returns>プレイヤー落下時の星のエフェクトのグラフィックハンドル</returns>
  int GetStarEffectGrHandle(int element_num);

  /// <summary>
  /// CalculateJumpSpeed関数の宣言
  /// </summary>
  /// <param ="time">毎フレーム更新時間</param>
  /// <returns>なし</returns>
  float CalculateJumpSpeed(float time);

  /// <summary>
  /// SetPileBottom関数の宣言
  /// </summary>
  /// <param = "is_pile_bottom">プレイヤーの足元が地面やブロックと重なっているかの有無</param>
  /// <returns>なし</returns>
  void SetPileBottom(bool is_pile_bottom);

  /// <summary>
  /// SetPileRight関数の宣言
  /// </summary>
  /// <param = "is_pile_right">プレイヤーの右が地面やブロックと重なっているかの有無</param>
  /// <returns>なし</returns>
  void SetPileRight(bool is_pile_right);

  /// <summary>
  /// SetPileLeft関数の宣言
  /// </summary>
  /// <param = "is_pile_left">プレイヤーの左が地面やブロックと重なっているかの有無</param>
  /// <returns>なし</returns>
  void SetPileLeft(bool is_pile_left);

  /// <summary>
  /// SetPlayerHp関数の宣言
  /// </summary>
  /// <param = "player_hp">プレイヤーのHP</param>
  /// <returns>なし</returns>
  void SetPlayerHp(int player_hp);

  /// <summary>
  /// GetPlayerHp関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>プレイヤーのHP</returns>
  int GetPlayerHp();

  /// <summary>
  /// SetHitWait関数の宣言
  /// </summary>
  /// <param = "is_hit_wait"></param>
  /// <returns>なし</returns>
  void SetHitWait(bool is_hit_wait);

  /// <summary>
  /// IsHitWait関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>次のダメージを受けるまでの待ち時間であるかの有無</returns>
  bool IsHitWait();

  /// <summary>
  /// IsPushJumpThisFlame関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ジャンプに対応するボタンがこのフレームで押されたかの有無</returns>
  bool IsPushJumpThisFlame();

  /// <summary>
  /// IsDownJump関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ジャンプに対応するボタンが押されているかの有無</returns>
  bool IsDownJump();

  /// <summary>
  /// CheckPlayerXCollision関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void CheckPlayerXCollision();

  /// <summary>
  /// CheckPlayerXFootCollision関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void CheckPlayerXFootCollision();

  /// <summary>
  /// CheckPlayerXHeadCollision関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void CheckPlayerXHeadCollision();

  /// <summary>
  /// IsNotDropAndFinishDrop関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>落下中でも落下時の演出が終わった状態でもないかの有無</returns>
  bool IsNotDropAndFinishDrop();

  /// <summary>
  /// IsPlayerJumping関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>プレイヤーがジャンプしているかのフラグ</returns>
  bool IsPlayerJumping();

  /// <summary>
  /// SetCanMove関数の宣言
  /// </summary>
  /// <param = "is_finish_opening_display">ステージ開始時のプレイヤー残機数とステージ数の表示が終わったかの有無</param>
  /// <returns>なし</returns>
  void SetCanMove(bool is_finish_opening_display);

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
  /// 累積時間（秒）
  /// </summary>
  float accumulation_time_;

  /// <summary>
  /// キー入力時の累積時間（秒）
  /// </summary>
  float keyinput_accumulation_time_;

  /// <summary>
  /// JumpEffect表示の累積時間（秒）
  /// </summary>
  float jump_accumulation_time_;

  /// <summary>
  /// 回転表示の累積時間（秒）
  /// </summary>
  float rotation_accumulation_time_;

  /// <summary>
  /// 星表示の累積時間（秒）
  /// </summary>
  float star_accumulation_time_;

  /// <summary>
  /// ジャンプの速さ計算で使う累積時間（秒）
  /// </summary>
  float jump_speed_accumulation_time_;

  /// <summary>
  /// ヒット中の累積時間（秒）
  /// </summary>
  float hit_accumulation_time_;

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
  /// 頭上で物とぶつかっているかの有無
  /// </summary>
  bool is_hit_head_;

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

  /// <summary>
  /// 待機時のプレイヤーのグラフィックハンドル
  /// </summary>
  std::array<int, kPlayerIdlingX> idling_gr_handle_;

  /// <summary>
  /// 歩行時のプレイヤーのグラフィックハンドル
  /// </summary>
  std::array<int, kPlayerWalkingX> walking_gr_handle_;

  /// <summary>
  /// ヒット時のプレイヤーのグラフィックハンドル
  /// </summary>
  std::array<int, kPlayerHitX> hit_gr_handle_;

  /// <summary>
  /// ジャンプ時のプレイヤーのグラフィックハンドル
  /// </summary>
  int jump_gr_handle_;

  /// <summary>
  /// 着地時のプレイヤーのグラフィックハンドル
  /// </summary>
  int fall_gr_handle_;

  /// </summary>
  //現在の状態
  /// </summary>
  StatusType status_type_;

  /// <summary>
  /// インデックス
  /// </summary>
  int index_;

  /// <summary>
  /// ダッシュ時のエフェクトのグラフィックハンドル
  /// </summary>
  std::array<int, kDashEffectX> dash_effect_gr_handle_;

  /// <summary>
  /// ジャンプ時のエフェクトのグラフィックハンドル
  /// </summary>
  std::array<int, kJumpEffectX> jump_effect_gr_handle_;

  /// <summary>
  /// プレイヤー落下時の星のエフェクトのグラフィックハンドル
  /// </summary>
  std::array<int, (kStarEffectX * kStarEffectY)> star_effect_gr_handle_;

  /// <summary>
  /// JumpEffect時に使うインデックス
  /// </summary>
  int jump_index_;

  /// <summary>
  /// フィールドの描画X位置を調整するための整数
  /// </summary>
  int difference_x_pos_;

  /// </summary>
  // プレイヤーの足元に地面かブロックがあるかの有無を受け取る変数
  /// </summary>
  bool is_ground_;

  /// </summary>
  // ジャンプのエフェクトを表示するかの有無を受け取る変数
  /// </summary>
  bool is_display_jump_effect_;

  /// </summary>
  // ダッシュのエフェクトを表示するかの有無を受け取る変数
  /// </summary>
  bool is_display_dash_effect_;

  /// </summary>
  // ダッシュボタンのキーが離れてからダッシュエフェクトがフェードアウトし始めるかのフラグ
  /// </summary>
  bool is_fade_dash_effect_;

  /// <summary>
  /// 角度情報
  /// </summary>
  AngleType angle_type_;

  /// <summary>
  /// 星のアニメーション表示用のインデックス
  /// </summary>
  int star_index_;

  /// <summary>
  /// 落下時のフレーム累積回数
  /// </summary>
  float fall_accumulation_count_;

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

  /// <summary>
  /// プレイヤーのHP
  /// </summary>
  int player_hp_;

  /// </summary>
  // ヒット終了後の待ち時間であるかの有無
  /// </summary>
  bool is_hit_wait_;

  /// <summary>
  /// ヒット終了後の待ち時間の累積時間（秒）
  /// </summary>
  float hit_wait_accumulation_time_;

  /// <summary>
  /// 敵を踏んだ時の小さいジャンプの速さ計算で使う累積時間（秒）
  /// </summary>
  float step_jump_accumulation_time_;

  /// </summary>
  // ジャンプに対応するボタンがこのフレームで押されたかの有無
  /// </summary>
  bool is_pushed_jump_this_frame_;

  /// </summary>
  // ジャンプに対応するボタンが押されているかの有無
  /// </summary>
  bool is_down_jump_;

  /// </summary>
  // 右移動に対応するボタンが押されているかの有無
  /// </summary>
  bool is_down_right_;

  /// </summary>
  // 左移動に対応するボタンが押されているかの有無
  /// </summary>
  bool is_down_left_;

  /// <summary>
  /// ジャンプ速度
  /// </summary>
  float jump_speed_;

  /// </summary>
  // ジャンプが終わったかのフラグ
  /// </summary>
  bool is_finish_jump_;

  /// </summary>
  // ジャンプ中であるかのフラグ
  /// </summary>
  bool is_jumping_;

  /// <summary>
  /// フェードイン・フェードアウトで使用する整数
  /// </summary>
  int image_fade_;

  /// </summary>
  // フェードの有無を受け取る変数
  /// </summary>
  bool is_image_fade_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float image_display_accumulation_time_;

  /// </summary>
  // フェードが終わったかの有無を受け取る変数
  /// </summary>
  bool is_image_fade_end_;

  /// </summary>
  // ステージ開始時のプレイヤー残機数とステージ数の表示が終わったかの有無を受け取る変数
  /// </summary>
  bool is_finish_opening_display_;
};