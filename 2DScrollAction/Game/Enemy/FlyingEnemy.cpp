#include <iostream>
#include "Game/Enemy/FlyingEnemy.h"
#include "System/LogConsole/LogConsole.h"
#include "Game/GameInfo/GameInfo.h"
#include "System/Input/InputManager.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// リセット時間を変数limit_timeに格納する
  /// </summary>
  float limit_time = 0.0f;

  /// <summary>
  /// 初期のリセット時間を定数kFirstLimitTimeに格納する
  /// </summary>
  static const float kFirstLimitTime = 0.8f;

  /// <summary>
  /// ジャンプのリセット時間を定数kJumpLimitTimeに格納する
  /// </summary>
  static const float kJumpLimitTime = 0.15f;

  /// <summary>
  /// X座標の開始位置を定数kStartFlyingEnemyXに格納する
  /// </summary>
  static const int kStartFlyingEnemyX = 3000;

  /// <summary>
  /// Y座標の開始位置を定数kStartFlyingEnemyYに格納する
  /// </summary>
  static const int kStartFlyingEnemyY = 380;

  /// <summary>
  /// 敵が歩き始めてから折り返すまでの距離を定数kWalkDistanceに格納する
  /// </summary>
  static const int kWalkDistance = 300;

  /// <summary>
  /// 5の整数を定数kLevelFiveに格納する
  /// </summary>
  static const int kLevelFive = 5;

  /// <summary>
  /// 7の整数を定数kLevelSevenに格納する
  /// </summary>
  static const int kLevelSeven = 7;

  /// <summary>
  /// 9の整数を定数kLevelNineに格納する
  /// </summary>
  static const int kLevelNine = 9;

  /// <summary>
  /// 座標の位置調整に使用する整数2を定数kTwoに格納する
  /// </summary>
  static const int kTwo = 2;

  /// <summary>
  /// 座標の位置調整に使用する整数3を定数kThreeに格納する
  /// </summary>
  static const int kThree = 3;

  /// <summary>
  /// 画像を透過させるαブレンドの値を定数kAlphaBlendに格納する
  /// </summary>
  static const int kAlphaBlend = 122;

  /// <summary>
  /// 効果音の最大音量を定数kVolumeに格納する
  /// </summary>
  static const int kMaxSoundEffectVolume = 255;

  /// <summary>
  /// 100％の分母を定数kHundredに格納する
  /// </summary>
  static const int kHundred = 100;

  /// <summary>
  /// 配列の次の要素に切り替える時間を定数の配列kChangeTimeに格納する
  /// </summary>
  static const float kChangeTime[] = { 0.05f, 0.1f, 0.15f, 0.2f ,0.25f ,0.3f ,0.35f ,0.4f ,0.45f};

  /// <summary>
  /// 画像の横向きの分割数を配列kPartitionNumbersに格納する
  /// </summary>
  static const int kPartitionNumbers[] = { kFlyingEnemyFlyingX, kFlyingEnemyFlyingX, kFlyingEnemyHitX, 1, 1 };

  /// <summary>
  /// ジャンプの初速度を定数kInitialRateに格納する
  /// </summary>
  static const float kInitialRate = 16.0f;

  /// <summary>
  /// ジャンプの高さの計算で使用する1.0fを定数kFloatOneに格納する
  /// </summary>
  static const float kFloatOne = 1.0f;

  /// <summary>
  /// 重力によって変化するY位置の変化量を定数kGravityに格納する
  /// </summary>
  static const int kGravity = 5;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
FlyingEnemy::FlyingEnemy(Task task_id, TaskManager * task_manager)
  : Task(task_id)
  , now_phase_(kPreraration)
  , task_manager_(task_manager)
  , walking_gr_handle_{}
  , hit_gr_handle_{}
  , accumulation_time_(0.0f)
  , wait_accumulation_time_(0.0f)
  , flying_enemys_drop_accumulation_time_(0.0f)
  , fall_accumulation_count_(0.0f)
  , x_coordinate_(kStartFlyingEnemyX)
  , y_coordinate_(kStartFlyingEnemyY)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , now_direction_(kNone)
  , display_x_coordinate_(0.0f)
  , display_y_coordinate_(0.0f)
  , piece_bottom_(0)
  , piece_top_(0)
  , piece_left_(0)
  , piece_right_(0)
  , is_hit_bottom_(false)
  , is_hit_right_(false)
  , is_hit_left_(false)
  , is_hit_(false)
  , move_sound_handle_(0)
  , move_handle_(0)
  , sound_volume_(0)
  , jump_gr_handle_(0)
  , fall_gr_handle_(0)
  , status_type_(kWalkRight)
  , index_(0)
  , difference_x_pos_(0)
  , jump_speed_(0.0f)
{
  DEBUG_PRINT(FlyingEnemyのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
FlyingEnemy::~FlyingEnemy() {
  DEBUG_PRINT(FlyingEnemyのデストラクタ);
  //wait_accumulation_time_ = 0.0f;
  //drop_accumulation_time_ = 0.0f;
  //fall_accumulation_count_ = 0.0f;
}

/// <summary>
/// 毎フレーム更新処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>なし</returns>
void FlyingEnemy::UpdateFrame(float time) {
  if (now_phase_ != kStop && now_phase_ != kFinish && now_phase_ != kPreraration) {

    //累積時間
    accumulation_time_ = accumulation_time_ + time;

    //右に飛ぶ状態の場合
    if (status_type_ == kWalkRight) {
      x_coordinate_ = x_coordinate_ + kTwo;
      if ((x_coordinate_ - kStartFlyingEnemyX) == kWalkDistance) {
        status_type_ = kIdolRight;
      }
    }
    //右に飛んだ後、待機している状態の場合
    else if (status_type_ == kIdolRight) {
      wait_accumulation_time_ = wait_accumulation_time_ + time;
      if (wait_accumulation_time_ >= kFirstLimitTime) {
        status_type_ = kWalkLeft;
        wait_accumulation_time_ = 0.0f;
      }
    }
    //左に飛ぶ状態の場合
    else if (status_type_ == kWalkLeft) {
      x_coordinate_ = x_coordinate_ - kTwo;
      if ((x_coordinate_) == kStartFlyingEnemyX) {
        status_type_ = kIdolLeft;
      }
    }
    //左に飛んだ後、待機している状態の場合
    else if (status_type_ == kIdolLeft) {
      wait_accumulation_time_ = wait_accumulation_time_ + time;
      if (wait_accumulation_time_ >= kFirstLimitTime) {
        status_type_ = kWalkRight;
        wait_accumulation_time_ = 0.0f;
      }
    }
    //倒された場合
    else if (status_type_ == kDrop) {

      //累積時間によって飛び上がる高さを計算する
      float jump_speed_ = CalculateJumpSpeed(time);

      y_coordinate_ = y_coordinate_ - static_cast<int>(jump_speed_) * kTwo;
      if (flying_enemys_drop_accumulation_time_ == kJumpLimitTime) {
        FallEnemy(time, kJumpLimitTime);
      }
    }

    //累積時間に応じて、グラフィックハンドルで使用する要素番号を増やす
    for (int i = 0; i < (kFlyingEnemyFlyingX); i++) {
      if (accumulation_time_ >= kChangeTime[i]) {
        index_ = i + 1;
      }
    }
    for (int i = 0; i < ((static_cast<int>(kEnemyMax) / kTwo)); i++) {
      if ((static_cast<int>(status_type_) / kTwo) == i) {
        if (accumulation_time_ > kChangeTime[kPartitionNumbers[i] - 1]) {
          accumulation_time_ = 0.0f;
          index_ = 0;
        }
      }
    }

  }
}

/// 毎フレーム描画処理
/// </remarks>
/// <param>なし</param>
/// <returns>なし</returns>
void FlyingEnemy::RenderFrame() {
  //DEBUG_PRINT(FlyingEnemyの毎フレーム描画処理);
  if (now_phase_ != kFinish && now_phase_ != kPreraration) {
    //X位置を取得する
    int x_coordinate = GetXPosition();
    //DEBUG_PRINT_VAR(x_coordinate);
    //Y位置を取得する
    int y_coordinate = GetYPosition();
    //DEBUG_PRINT_VAR(y_coordinate);

    //幅を取得する
    int width = GetWidth();

    //高さを取得する
    int height = GetHeight();

    //半分の幅を取得する
    float half_width = GetHalfWidth();

    //半分の高さを取得する
    float half_height = GetHalfHeight();

    //ゲーム情報のインスタンスを取得する
    GameInfo* game_info = GameInfo::GetInstance();

    //ゲーム情報からマップの左上の座標を取得する
    int map_left_x = game_info->GetMapLeftX();
    int map_left_y = game_info->GetMapLeftY();

    //グラフィックハンドルを配列に格納する
    int graphic_handles[] = { walking_gr_handle_[(index_) % kFlyingEnemyFlyingX], walking_gr_handle_[(index_) % kFlyingEnemyFlyingX], hit_gr_handle_[(index_) % kFlyingEnemyHitX], jump_gr_handle_, fall_gr_handle_ };

    //敵の状態に応じて描画する
    for (int i = 0; i < ((static_cast<int>(kEnemyMax) / kTwo)); i++) {
      if ((static_cast<int>(status_type_) / kTwo) == i) {
        //status_type_が奇数の場合は左方向に進むので、画像を左右反転させる
        if ((static_cast<int>(status_type_) % kTwo) == 1) {
          DrawGraph((x_coordinate_ - difference_x_pos_), (y_coordinate_), graphic_handles[i], TRUE);
        }
        //status_type_が偶数の場合
        else {
          DrawRotaGraph((x_coordinate_ + static_cast<int>(half_width_) - difference_x_pos_), (y_coordinate_ + static_cast<int>(half_height_)), 1.0f, 0.0, graphic_handles[i], TRUE, TRUE);
        }
      }
    }
    if (status_type_ == kDrop) {
      DrawGraph((x_coordinate - difference_x_pos_), (y_coordinate), hit_gr_handle_[kFlyingEnemyHitX - 1], TRUE);
    }
  }
}

/// <summary>
/// SetWalkingGrHandle関数の定義
/// </summary>
/// <param = "walking_gr_handle">歩行時のグラフィックハンドル</param>
/// <returns>なし</returns>
void FlyingEnemy::SetWalkingGrHandle(std::array<int, kFlyingEnemyFlyingX> walking_gr_handle) {
  walking_gr_handle_ = walking_gr_handle;
}

/// <summary>
/// GetWalkingGrHandle関数の定義
/// </summary>
/// <param = "element_num">要素番号</param>
/// <returns>歩行時のグラフィックハンドル</returns>
int FlyingEnemy::GetWalkingGrHandle(int element_num) {
  return walking_gr_handle_[element_num];
}

/// <summary>
/// SetHitGrHandle関数の定義
/// </summary>
/// <param = "hit_gr_handle">ヒット時のグラフィックハンドル</param>
/// <returns>なし</returns>
void FlyingEnemy::SetHitGrHandle(std::array<int, kFlyingEnemyHitX> hit_gr_handle) {
  hit_gr_handle_ = hit_gr_handle;
}

/// <summary>
/// GetHitGrHandle関数の定義
/// </summary>
/// <param = "element_num">要素番号</param>
/// <returns>ヒット時のグラフィックハンドル</returns>
int FlyingEnemy::GetHitGrHandle(int element_num) {
  return hit_gr_handle_[element_num];
}

/// <summary>
/// SetXPosition関数の定義
/// </summary>
/// <param = "x_coordinate">X座標</param>
/// <returns>なし</returns>
void FlyingEnemy::SetXPosition(int x_coordinate) {
  x_coordinate_ = x_coordinate;
}

/// <summary>
/// GetXPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>X座標</returns>
int FlyingEnemy::GetXPosition() {
  return x_coordinate_;
}

/// <summary>
/// SetYPosition関数の定義
/// </summary>
/// <param = "y_coordinate">Y座標</param>
/// <returns>なし</returns>
void FlyingEnemy::SetYPosition(int y_coordinate) {
  y_coordinate_ = y_coordinate;
}

/// <summary>
/// GetYPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Y座標</returns>
int FlyingEnemy::GetYPosition() {
  return y_coordinate_;
}

/// <summary>
/// SetWidth関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void FlyingEnemy::SetWidth(int size_x) {
  width_ = size_x;
}

/// <summary>
/// GetWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int FlyingEnemy::GetWidth() {
  return width_;
}

/// <summary>
/// SetHeight関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void FlyingEnemy::SetHeight(int size_y) {
  height_ = size_y;
}

/// <summary>
/// GetHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さ</returns>
int FlyingEnemy::GetHeight() {
  return height_;
}

/// <summary>
/// SetHalfWidth関数の定義
/// </summary>
/// <param>画像の幅の半分</param>
/// <returns>なし</returns>
void FlyingEnemy::SetHalfWidth(float size_half_x) {
  half_width_ = size_half_x;
}

/// <summary>
/// GetHalfWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅の半分</returns>
float FlyingEnemy::GetHalfWidth() {
  return half_width_;
}

/// <summary>
/// SetHalfHeight関数の定義
/// </summary>
/// <param>画像の高さの半分</param>
/// <returns>なし</returns>
void FlyingEnemy::SetHalfHeight(float size_half_y) {
  half_height_ = size_half_y;
}

/// <summary>
/// GetHalfHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さの半分</returns>
float FlyingEnemy::GetHalfHeight() {
  return half_height_;
}

/// <summary>
/// SetDirectionType関数の定義
/// </summary>
/// <param = "direction">方向の種類</param>
/// <returns>なし</returns>
void FlyingEnemy::SetDirectionType(DirectionType direction) {
  now_direction_ = direction;
}

/// <summary>
/// GetDirectionType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
FlyingEnemy::DirectionType FlyingEnemy::GetDirectionType() {
  return now_direction_;
}

/// <summary>
/// SetPhaseType関数の定義
/// </summary>
/// <param = "type">方向の種類</param>
/// <returns>なし</returns>
void FlyingEnemy::SetPhaseType(PhaseType type) {
  now_phase_ = type;
}

/// <summary>
/// GetPhaseType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
FlyingEnemy::PhaseType FlyingEnemy::GetPhaseType() {
  return now_phase_;
}

/// <summary>
/// SetDisplayXPosition関数の定義
/// </summary>
/// <param = "display_x_coordinate">表示用のX座標</param>
/// <returns>なし</returns>
void FlyingEnemy::SetDisplayXPosition(float display_x_coordinate) {
  display_x_coordinate_ = display_x_coordinate;
}

/// <summary>
/// GetDisplayXPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>表示用のX座標</returns>
float FlyingEnemy::GetDisplayXPosition() {
  return display_x_coordinate_;
}

/// <summary>
/// SetDisplayYPosition関数の定義
/// </summary>
/// <param = "display_y_coordinate">表示用のY座標</param>
/// <returns>なし</returns>
void FlyingEnemy::SetDisplayYPosition(float display_y_coordinate) {
  display_y_coordinate_ = display_y_coordinate;
}

/// <summary>
/// GetDisplayYPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>表示用のY座標</returns>
float FlyingEnemy::GetDisplayYPosition() {
  return display_y_coordinate_;
}

/// <summary>
/// GetPieceTop関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>最上部の位置</returns>
int FlyingEnemy::GetPieceTop() {
  //int x, y;

  return 0;
}

/// <summary>
/// GetPieceBottom関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>最下部の位置</returns>
int FlyingEnemy::GetPieceBottom() {
  //int x, y;

  return 0;
}

/// <summary>
/// GetPieceLeft関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>最左部の位置</returns>
int FlyingEnemy::GetPieceLeft() {
  //int x, y;

  return 0;
}

/// <summary>
/// GetPieceRight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>最右部の位置</returns>
int FlyingEnemy::GetPieceRight() {
  //int x, y;

  return 0;
}

/// <summary>
/// SetHitBottom関数の宣言
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void FlyingEnemy::SetHitBottom(bool is_hit_bottom) {
  is_hit_bottom_ = is_hit_bottom;
}

/// <summary>
/// SetHitRight関数の宣言
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void FlyingEnemy::SetHitRight() {
  is_hit_right_ = true;
}

/// <summary>
/// SetHitLeft関数の宣言
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void FlyingEnemy::SetHitLeft() {
  is_hit_left_ = true;
}

/// <summary>
/// SetHit関数の宣言
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void FlyingEnemy::SetHit(bool is_hit) {
  is_hit_ = is_hit;
}

/// <summary>
/// IsHit関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>他と重なったかの有無</returns>
bool FlyingEnemy::IsHit() {
  return is_hit_;
}

/// <summary>
/// 下に移動する時に衝突したかを確認する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
int FlyingEnemy::CheckIsHitEnemyBasesBottom() {

  int harddrop_num = 0;
  int x_coordinate = x_coordinate_;
  int y_coordinate = y_coordinate_;

  return harddrop_num;
}

/// <summary>
/// SetMoveSoundHandle関数の定義
/// </summary>
/// <param = "move_sound_handle">サウンドハンドル</param>
/// <returns>なし</returns>
void FlyingEnemy::SetMoveSoundHandle(int move_sound_handle) {
  move_sound_handle_ = move_sound_handle;
}

/// <summary>
/// GetMoveSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>サウンドハンドル</returns>
int FlyingEnemy::GetMoveSoundHandle() {
  return move_sound_handle_;
}

/// <summary>
/// SetXMoveSoundHandle関数の定義
/// </summary>
/// <param = "move_handle">左右移動時のサウンドハンドル</param>
/// <returns>なし</returns>
void FlyingEnemy::SetXMoveSoundHandle(int move_handle) {
  move_handle_ = move_handle;
}

/// <summary>
/// GetXMoveSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>左右移動時のサウンドハンドル</returns>
int FlyingEnemy::GetXMoveSoundHandle() {
  return move_handle_;
}

/// <summary>
/// SetSoundVolume関数の定義
/// </summary>
/// <param = "sound_volume">音量</param>
/// <returns>なし</returns>
void FlyingEnemy::SetSoundVolume(int sound_volume) {
  sound_volume_ = sound_volume;
}

/// <summary>
/// SetJumpGrHandle関数の定義
/// </summary>
/// <param = "jump_gr_handle">ジャンプ時のグラフィックハンドル</param>
/// <returns>なし</returns>
void FlyingEnemy::SetJumpGrHandle(int jump_gr_handle) {
  jump_gr_handle_ = jump_gr_handle;
}

/// <summary>
/// GetJumpGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ジャンプ時のグラフィックハンドル</returns>
int FlyingEnemy::GetJumpGrHandle() {
  return jump_gr_handle_;
}

/// <summary>
/// SetFallGrHandle関数の定義
/// </summary>
/// <param = "fall_gr_handle">着地時のグラフィックハンドル</param>
/// <returns>なし</returns>
void FlyingEnemy::SetFallGrHandle(int fall_gr_handle) {
  fall_gr_handle_ = fall_gr_handle;
}

/// <summary>
/// GetFallGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>着地時のグラフィックハンドル</returns>
int FlyingEnemy::GetFallGrHandle() {
  return fall_gr_handle_;
}

/// <summary>
/// SetDifferenceXpos関数の定義
/// </summary>
/// <param>フィールドの描画X位置を調整するための整数</param>
/// <returns>なし</returns>
void FlyingEnemy::SetDifferenceXpos(int difference_x_pos) {
  difference_x_pos_ = difference_x_pos;
}

/// <summary>
/// SetStatusType関数の定義
/// </summary>
/// <param = "status_type">敵の状態</param>
/// <returns>なし</returns>
void FlyingEnemy::SetStatusType(StatusType status_type) {
  status_type_ = status_type;
}

/// <summary>
/// GetStatusType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>敵の状態</returns>
FlyingEnemy::StatusType FlyingEnemy::GetStatusType() {
  return status_type_;
}

/// <summary>
/// CalculateJumpSpeed関数の宣言
/// </summary>
/// <param ="time">毎フレーム更新時間</param>
/// <returns>なし</returns>
float FlyingEnemy::CalculateJumpSpeed(float time) {

  flying_enemys_drop_accumulation_time_ = flying_enemys_drop_accumulation_time_ + time;
  //累積時間が一定時間を超えない様にする
  if (flying_enemys_drop_accumulation_time_ > kJumpLimitTime) {
    flying_enemys_drop_accumulation_time_ = kJumpLimitTime;
  }

  //累積時間によって飛び上がる高さを計算する
  float jump_speed = kInitialRate * (kFloatOne - flying_enemys_drop_accumulation_time_ / kJumpLimitTime);

  return jump_speed;
}

/// <summary>
/// FallEnemy関数の宣言
/// </summary>
/// <param ="time">毎フレーム更新時間</param>
/// <returns>なし</returns>
void FlyingEnemy::FallEnemy(float time, float limit_time) {

  fall_accumulation_count_ = fall_accumulation_count_ + time;
  //累積時間によって変化する降りる速さを計算する
  float fall_speed = kInitialRate * (fall_accumulation_count_ / limit_time);
  y_coordinate_ = static_cast<int>(y_coordinate_ + fall_speed);
}