#include <iostream>
#include "Game/Enemy/FirstWalkingEnemy.h"
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
  static const float kFirstLimitTime = 1.0f;

  /// <summary>
  /// ジャンプのリセット時間を定数kJumpLimitTimeに格納する
  /// </summary>
  static const float kJumpLimitTime = 0.15f;

  /// <summary>
  /// X座標の開始位置を定数kStartFirstWalkingEnemyXに格納する
  /// </summary>
  static const int kStartFirstWalkingEnemyX = 5500;

  /// <summary>
  /// Y座標の開始位置を定数kStartFirstWalkingEnemyYに格納する
  /// </summary>
  static const int kStartFirstWalkingEnemyY = 480;

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
  static const float kChangeTime[] = { 0.05f, 0.1f, 0.15f, 0.2f ,0.25f ,0.3f ,0.35f ,0.4f ,0.45f ,0.5f ,0.55f, 0.6f ,0.65f ,0.7f ,0.75f, 0.8f };

  /// <summary>
  /// 画像の横向きの分割数を配列kPartitionNumbersに格納する
  /// </summary>
  static const int kPartitionNumbers[] = { kFirstWalkingEnemyIdlingX, kFirstWalkingEnemyWalkingX, kFirstWalkingEnemyHitX, 1, 1 };

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

  // <summary>
  //キノコの画像の幅と高さを定数kFirstWalkingEnemySizeに格納する
  /// <summary>
  static const int kFirstWalkingEnemySize = 64;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
FirstWalkingEnemy::FirstWalkingEnemy(Task task_id, TaskManager * task_manager)
  : Task(task_id)
  , now_phase_(kPreraration)
  , task_manager_(task_manager)
  , idling_gr_handle_{}
  , walking_gr_handle_{}
  , hit_gr_handle_{}
  , accumulation_time_(0.0f)
  , wait_accumulation_time_(0.0f)
  , first_enemy_drop_accumulation_time_(0.0f)
  , fall_accumulation_count_(0.0f)
  , x_coordinate_(kStartFirstWalkingEnemyX)
  , y_coordinate_(kStartFirstWalkingEnemyY)
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
  , status_type_(kWalkLeft)
  , index_(0)
  , difference_x_pos_(0)
  , is_move_(false)
  , is_ground_(true)
  , start_move_x_(0)
  , jump_speed_(0.0f)
{
  DEBUG_PRINT(FirstWalkingEnemyのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
FirstWalkingEnemy::~FirstWalkingEnemy() {
  DEBUG_PRINT(FirstWalkingEnemyのデストラクタ);
  //wait_accumulation_time_ = 0.0f;
  //drop_accumulation_time_ = 0.0f;
  //fall_accumulation_count_ = 0.0f;
}

/// <summary>
/// 毎フレーム更新処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>なし</returns>
void FirstWalkingEnemy::UpdateFrame(float time) {
  if (now_phase_ != kStop && now_phase_ != kFinish && now_phase_ != kPreraration && is_move_) {

    //累積時間
    accumulation_time_ = accumulation_time_ + time;

    //衝突判定のインスタンスを取得する
    Collision* collision_ = Collision::GetInstance();

    //足元が地面と接しているか判定する
    is_ground_ = collision_->IsFootGround(x_coordinate_, y_coordinate_, kFirstWalkingEnemySize);

    //右に歩く状態の場合
    if (status_type_ == kWalkRight) {
      x_coordinate_ = x_coordinate_ + kTwo;
      bool is_right = collision_->IsHitRight(x_coordinate_, y_coordinate_, kFirstWalkingEnemySize);
      if (is_right) {
        status_type_ = kIdolRight;
      }
    }
    //右に歩いた後、待機している状態の場合
    else if (status_type_ == kIdolRight) {
      wait_accumulation_time_ = wait_accumulation_time_ + time;
      if (wait_accumulation_time_ >= kFirstLimitTime) {
        status_type_ = kWalkLeft;
        wait_accumulation_time_ = 0.0f;
      }
    }
    //左に歩く状態の場合
    else if (status_type_ == kWalkLeft) {
      x_coordinate_ = x_coordinate_ - kTwo;
      bool is_left = collision_->IsHitLeft(x_coordinate_, y_coordinate_, kFirstWalkingEnemySize);
      if (is_left) {
        status_type_ = kIdolLeft;
      }
    }
    //右に歩いた後、待機している状態の場合
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
      jump_speed_ = CalculateJumpSpeed(time);

      y_coordinate_ = y_coordinate_ - static_cast<int>(jump_speed_) * kTwo;
      if (first_enemy_drop_accumulation_time_ == kJumpLimitTime) {
        FallEnemy(time, kJumpLimitTime);
      }
    }

    //足元に地面やブロック等が無い場合、重力で落下する
    if (is_ground_ == false) {
      FallEnemy(time, kFirstLimitTime);
      is_ground_ = collision_->IsFootGround(x_coordinate_, y_coordinate_, kFirstWalkingEnemySize);
      if (is_ground_) {
        is_ground_ = true;
      }
      //DEBUG_PRINT_VAR(fall_speed);
      //画面の下まで落ちた場合
      if (y_coordinate_ > kTotalRow * kMapSize) {
        status_type_ = kDrop;
      }
    }

    //累積時間に応じて、グラフィックハンドルで使用する要素番号を増やす
    for (int i = 0; i < (kFirstWalkingEnemyWalkingX); i++) {
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
void FirstWalkingEnemy::RenderFrame() {
  //DEBUG_PRINT(FirstWalkingEnemyの毎フレーム描画処理);
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
    int graphic_handles[] = { idling_gr_handle_[(index_) % kFirstWalkingEnemyIdlingX], walking_gr_handle_[(index_) % kFirstWalkingEnemyWalkingX], hit_gr_handle_[(index_) % kFirstWalkingEnemyHitX], jump_gr_handle_, fall_gr_handle_ };

    //敵の状態に応じて描画する
    for (int i = 0; i < ((static_cast<int>(kEnemyMax) / kTwo)); i++) {
      if ((static_cast<int>(status_type_) / kTwo) == i) {
        //status_type_が奇数の場合は左方向に進むので、画像を左右反転させる
        if ((static_cast<int>(status_type_) % kTwo) == 1) {
          DrawGraph((x_coordinate - difference_x_pos_), (y_coordinate), graphic_handles[i], TRUE);
        }
        //status_type_が偶数の場合
        else {
          DrawRotaGraph((x_coordinate_ + static_cast<int>(half_width_) - difference_x_pos_), (y_coordinate_ + static_cast<int>(half_height_)), 1.0f, 0.0, graphic_handles[i], TRUE, TRUE);
        }
      }
    }
    if (status_type_ == kDrop) {
      DrawGraph((x_coordinate - difference_x_pos_), (y_coordinate), hit_gr_handle_[kFirstWalkingEnemyHitX - 1], TRUE);
    }
  }
}

/// <summary>
/// SetIdlingGrHandle関数の定義
/// </summary>
/// <param = "idling_gr_handle">待機時のグラフィックハンドル</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetIdlingGrHandle(std::array<int, kFirstWalkingEnemyIdlingX> idling_gr_handle) {
  idling_gr_handle_ = idling_gr_handle;
}

/// <summary>
/// GetIdlingGrHandle関数の定義
/// </summary>
/// <param = "element_num">要素番号</param>
/// <returns>待機時のグラフィックハンドル</returns>
int FirstWalkingEnemy::GetIdlingGrHandle(int element_num) {
  return idling_gr_handle_[element_num];
}

/// <summary>
/// SetWalkingGrHandle関数の定義
/// </summary>
/// <param = "walking_gr_handle">歩行時のグラフィックハンドル</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetWalkingGrHandle(std::array<int, kFirstWalkingEnemyWalkingX> walking_gr_handle) {
  walking_gr_handle_ = walking_gr_handle;
}

/// <summary>
/// GetWalkingGrHandle関数の定義
/// </summary>
/// <param = "element_num">要素番号</param>
/// <returns>歩行時のグラフィックハンドル</returns>
int FirstWalkingEnemy::GetWalkingGrHandle(int element_num) {
  return walking_gr_handle_[element_num];
}

/// <summary>
/// SetHitGrHandle関数の定義
/// </summary>
/// <param = "hit_gr_handle">ヒット時のグラフィックハンドル</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetHitGrHandle(std::array<int, kFirstWalkingEnemyHitX> hit_gr_handle) {
  hit_gr_handle_ = hit_gr_handle;
}

/// <summary>
/// GetHitGrHandle関数の定義
/// </summary>
/// <param = "element_num">要素番号</param>
/// <returns>ヒット時のグラフィックハンドル</returns>
int FirstWalkingEnemy::GetHitGrHandle(int element_num) {
  return hit_gr_handle_[element_num];
}

/// <summary>
/// SetXPosition関数の定義
/// </summary>
/// <param = "x_coordinate">X座標</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetXPosition(int x_coordinate) {
  x_coordinate_ = x_coordinate;
}

/// <summary>
/// GetXPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>X座標</returns>
int FirstWalkingEnemy::GetXPosition() {
  return x_coordinate_;
}

/// <summary>
/// SetYPosition関数の定義
/// </summary>
/// <param = "y_coordinate">Y座標</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetYPosition(int y_coordinate) {
  y_coordinate_ = y_coordinate;
}

/// <summary>
/// GetYPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Y座標</returns>
int FirstWalkingEnemy::GetYPosition() {
  return y_coordinate_;
}

/// <summary>
/// SetWidth関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetWidth(int size_x) {
  width_ = size_x;
}

/// <summary>
/// GetWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int FirstWalkingEnemy::GetWidth() {
  return width_;
}

/// <summary>
/// SetHeight関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetHeight(int size_y) {
  height_ = size_y;
}

/// <summary>
/// GetHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さ</returns>
int FirstWalkingEnemy::GetHeight() {
  return height_;
}

/// <summary>
/// SetHalfWidth関数の定義
/// </summary>
/// <param>画像の幅の半分</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetHalfWidth(float size_half_x) {
  half_width_ = size_half_x;
}

/// <summary>
/// GetHalfWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅の半分</returns>
float FirstWalkingEnemy::GetHalfWidth() {
  return half_width_;
}

/// <summary>
/// SetHalfHeight関数の定義
/// </summary>
/// <param>画像の高さの半分</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetHalfHeight(float size_half_y) {
  half_height_ = size_half_y;
}

/// <summary>
/// GetHalfHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さの半分</returns>
float FirstWalkingEnemy::GetHalfHeight() {
  return half_height_;
}

/// <summary>
/// SetDirectionType関数の定義
/// </summary>
/// <param = "direction">方向の種類</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetDirectionType(DirectionType direction) {
  now_direction_ = direction;
}

/// <summary>
/// GetDirectionType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
FirstWalkingEnemy::DirectionType FirstWalkingEnemy::GetDirectionType() {
  return now_direction_;
}

/// <summary>
/// SetPhaseType関数の定義
/// </summary>
/// <param = "type">方向の種類</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetPhaseType(PhaseType type) {
  now_phase_ = type;
}

/// <summary>
/// GetPhaseType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
FirstWalkingEnemy::PhaseType FirstWalkingEnemy::GetPhaseType() {
  return now_phase_;
}

/// <summary>
/// SetDisplayXPosition関数の定義
/// </summary>
/// <param = "display_x_coordinate">表示用のX座標</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetDisplayXPosition(float display_x_coordinate) {
  display_x_coordinate_ = display_x_coordinate;
}

/// <summary>
/// GetDisplayXPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>表示用のX座標</returns>
float FirstWalkingEnemy::GetDisplayXPosition() {
  return display_x_coordinate_;
}

/// <summary>
/// SetDisplayYPosition関数の定義
/// </summary>
/// <param = "display_y_coordinate">表示用のY座標</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetDisplayYPosition(float display_y_coordinate) {
  display_y_coordinate_ = display_y_coordinate;
}

/// <summary>
/// GetDisplayYPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>表示用のY座標</returns>
float FirstWalkingEnemy::GetDisplayYPosition() {
  return display_y_coordinate_;
}

/// <summary>
/// GetPieceTop関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>最上部の位置</returns>
int FirstWalkingEnemy::GetPieceTop() {
  //int x, y;

  return 0;
}

/// <summary>
/// GetPieceBottom関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>最下部の位置</returns>
int FirstWalkingEnemy::GetPieceBottom() {
  //int x, y;

  return 0;
}

/// <summary>
/// GetPieceLeft関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>最左部の位置</returns>
int FirstWalkingEnemy::GetPieceLeft() {
  //int x, y;

  return 0;
}

/// <summary>
/// GetPieceRight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>最右部の位置</returns>
int FirstWalkingEnemy::GetPieceRight() {
  //int x, y;

  return 0;
}

/// <summary>
/// SetHitBottom関数の宣言
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetHitBottom(bool is_hit_bottom) {
  is_hit_bottom_ = is_hit_bottom;
}

/// <summary>
/// SetHitRight関数の宣言
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetHitRight() {
  is_hit_right_ = true;
}

/// <summary>
/// SetHitLeft関数の宣言
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetHitLeft() {
  is_hit_left_ = true;
}

/// <summary>
/// SetHit関数の宣言
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetHit(bool is_hit) {
  is_hit_ = is_hit;
}

/// <summary>
/// IsHit関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>他と重なったかの有無</returns>
bool FirstWalkingEnemy::IsHit() {
  return is_hit_;
}

/// <summary>
/// 下に移動する時に衝突したかを確認する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
int FirstWalkingEnemy::CheckIsHitEnemyBasesBottom() {

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
void FirstWalkingEnemy::SetMoveSoundHandle(int move_sound_handle) {
  move_sound_handle_ = move_sound_handle;
}

/// <summary>
/// GetMoveSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>サウンドハンドル</returns>
int FirstWalkingEnemy::GetMoveSoundHandle() {
  return move_sound_handle_;
}

/// <summary>
/// SetXMoveSoundHandle関数の定義
/// </summary>
/// <param = "move_handle">左右移動時のサウンドハンドル</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetXMoveSoundHandle(int move_handle) {
  move_handle_ = move_handle;
}

/// <summary>
/// GetXMoveSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>左右移動時のサウンドハンドル</returns>
int FirstWalkingEnemy::GetXMoveSoundHandle() {
  return move_handle_;
}

/// <summary>
/// SetSoundVolume関数の定義
/// </summary>
/// <param = "sound_volume">音量</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetSoundVolume(int sound_volume) {
  sound_volume_ = sound_volume;
}

/// <summary>
/// SetJumpGrHandle関数の定義
/// </summary>
/// <param = "jump_gr_handle">ジャンプ時のグラフィックハンドル</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetJumpGrHandle(int jump_gr_handle) {
  jump_gr_handle_ = jump_gr_handle;
}

/// <summary>
/// GetJumpGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ジャンプ時のグラフィックハンドル</returns>
int FirstWalkingEnemy::GetJumpGrHandle() {
  return jump_gr_handle_;
}

/// <summary>
/// SetFallGrHandle関数の定義
/// </summary>
/// <param = "fall_gr_handle">着地時のグラフィックハンドル</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetFallGrHandle(int fall_gr_handle) {
  fall_gr_handle_ = fall_gr_handle;
}

/// <summary>
/// GetFallGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>着地時のグラフィックハンドル</returns>
int FirstWalkingEnemy::GetFallGrHandle() {
  return fall_gr_handle_;
}

/// <summary>
/// SetDifferenceXpos関数の定義
/// </summary>
/// <param>フィールドの描画X位置を調整するための整数</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetDifferenceXpos(int difference_x_pos) {
  difference_x_pos_ = difference_x_pos;
}

/// <summary>
/// SetStatusType関数の定義
/// </summary>
/// <param = "status_type">敵の状態</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetStatusType(StatusType status_type) {
  status_type_ = status_type;
}

/// <summary>
/// GetStatusType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>敵の状態</returns>
FirstWalkingEnemy::StatusType FirstWalkingEnemy::GetStatusType() {
  return status_type_;
}

/// <summary>
/// CalculateJumpSpeed関数の宣言
/// </summary>
/// <param ="time">毎フレーム更新時間</param>
/// <returns>なし</returns>
float FirstWalkingEnemy::CalculateJumpSpeed(float time) {

  first_enemy_drop_accumulation_time_ = first_enemy_drop_accumulation_time_ + time;
  //累積時間が一定時間を超えない様にする
  if (first_enemy_drop_accumulation_time_ > kJumpLimitTime) {
    first_enemy_drop_accumulation_time_ = kJumpLimitTime;
  }

  //累積時間によって飛び上がる高さを計算する
  float jump_speed = kInitialRate * (kFloatOne - first_enemy_drop_accumulation_time_ / kJumpLimitTime);

  return jump_speed;
}

/// <summary>
/// FallEnemy関数の宣言
/// </summary>
/// <param ="time">毎フレーム更新時間</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::FallEnemy(float time, float limit_time) {

  fall_accumulation_count_ = fall_accumulation_count_ + time;
  //累積時間によって変化する降りる速さを計算する
  float fall_speed = kInitialRate * (fall_accumulation_count_ / limit_time);
  y_coordinate_ = static_cast<int>(y_coordinate_ + fall_speed);
}

/// <summary>
/// SetMove関数の宣言
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetMove(bool is_move) {
  is_move_ = is_move;
}

/// <summary>
/// SetStartMoveX関数の定義
/// </summary>
/// <param = "start_move_x">プレイヤーが到達した時に敵が動き出すX位置</param>
/// <returns>なし</returns>
void FirstWalkingEnemy::SetStartMoveX(int start_move_x) {
  start_move_x_ = start_move_x;
}

/// <summary>
/// GetStartMoveX関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>プレイヤーが到達した時に敵が動き出すX位置</returns>
int FirstWalkingEnemy::GetStartMoveX() {

  return start_move_x_;
}