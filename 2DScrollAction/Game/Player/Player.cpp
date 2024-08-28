#include <iostream>
#include "Game/Player/Player.h"
#include "System/LogConsole/LogConsole.h"
#include "Game/GameInfo/GameInfo.h"
#include "System/Input/InputManager.h"
#include "Game/Fade/FadeManager.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// リセット時間を変数limit_timeに格納する
  /// </summary>
  float limit_time = 0.0f;

  /// <summary>
  /// 累積時間のリセット時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 0.4f;

  /// <summary>
  /// 初期のリセット時間を定数kFirstLimitTimeに格納する
  /// </summary>
  static const float kFirstLimitTime = 1.2f;

  /// <summary>
  /// ジャンプ速度の計算で使う累積時間を増やす上限を定数kJumpLimitTimeに格納する
  /// </summary>
  static const float kJumpLimitTime = 0.7f;

  /// <summary>
  /// 落下速度の計算で使う定数をkFallLimitTimeに格納する
  /// </summary>
  static const float kFallLimitTime = 1.5f;

  /// <summary>
  /// 星表示累積時間のリセット時間を定数kStarLimitTimeに格納する
  /// </summary>
  static const float kStarLimitTime = 1.2f;

  /// <summary>
  /// ヒット時間の累積時間のリセット時間を定数kHitLimitTimeに格納する
  /// </summary>
  static const float kHitLimitTime = 0.2f;

  /// <summary>
  /// 待ち時間の累積時間のリセット時間を定数kWaitLimitTimeに格納する
  /// </summary>
  static const float kWaitLimitTime = 0.2f;

  /// <summary>
  /// ジャンプ後の落下時にジャンプ速度を減速させる定数kJumpReduceTime
  /// </summary>
  static const float kJumpReduceTime = 0.5f;

  /// <summary>
  /// X座標の開始位置を定数kStartPlayerXに格納する
  /// </summary>
  static const int kStartPlayerX = 0;

  /// <summary>
  /// Y座標の開始位置を定数kStartPlayerYに格納する
  /// </summary>
  static const int kStartPlayerY = 480;

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
  /// 座標の位置調整に使用する整数4を定数kFourに格納する
  /// </summary>
  static const int kFour = 4;

  /// <summary>
  /// 座標の位置調整に使用する整数5を定数kFiveに格納する
  /// </summary>
  static const int kFive = 5;

  /// <summary>
  /// 座標の位置調整に使用する整数6を定数kSixに格納する
  /// </summary>
  static const int kSix = 6;

  /// <summary>
  /// 座標の位置調整に使用する整数6を定数kSevenに格納する
  /// </summary>
  static const int kSeven = 7;

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
  static const float kChangeTime[] = {0.05f, 0.1f, 0.15f, 0.2f ,0.25f ,0.3f ,0.35f ,0.4f ,0.45f ,0.5f ,0.55f, 0.6f};

  /// <summary>
  /// ジャンプ時のエフェクトの配列の次の要素に切り替える時間を定数の配列kJumpEffectChangeTimeに格納する
  /// </summary>
  static const float kJumpEffectChangeTime[] = { 0.075f, 0.15f ,0.25f ,0.3f ,0.375f ,0.4f };

  /// <summary>
  /// 右に走る時の土煙の位置調整に使用する整数を定数kDashEffRightXに格納する
  /// </summary>
  static const int kDashEffRightX = 80;

  /// <summary>
  /// 左に走る時の土煙の位置調整に使用する整数を定数kDashEffLeftXに格納する
  /// </summary>
  static const int kDashEffLeftX = 50;

  /// <summary>
  /// 星のX位置調整に使用する整数を定数kStarEffXに格納する
  /// </summary>
  static const int kStarEffX = -60;

  /// <summary>
  /// 星のY位置調整に使用する整数を定数kStarEffYに格納する
  /// </summary>
  static const int kStarEffY = -70;

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

  /// <summary>
  /// 画像の横向きの分割数を配列kPartitionNumbersに格納する
  /// </summary>
  static const int kPartitionNumbers[] = { kPlayerIdlingX, kPlayerWalkingX, kPlayerHitX, 1, 1 };

  /// <summary>
  //描画角度を定数の配列kPiに格納する
  /// <summary>
  static const double kAngles[] = { 0.0, (3.141592654 / 4),  (3.141592654 / 2), (3 * (3.141592654) / 4), (3.141592654 / 1), (5 * (3.141592654) / 4), (3 * (3.141592654) / 2), (7 * (3.141592654) / 4) };

  /// <summary>
  /// kAnglesの要素数を定数kAnglesElementに格納する
  /// </summary>
  static const int kAnglesElement = 8;

  /// <summary>
  /// 角度を変えるまでの待ち時間を定数kWaitTimeに格納する
  /// </summary>
  static const float kWaitTimes[] = { 0.0f, 0.05f, 0.1f, 0.15f, 0.2f, 0.25f, 0.3f, 0.35f, 0.4f };

  /// <summary>
  /// 星の画像表示の待ち時間を定数kStarWaitTimesに格納する
  /// </summary>
  static const float kStarWaitTimes[] = { 0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f };

  /// <summary>
  /// FPSに近い整数を定数kFpsに格納する
  /// </summary>
  static const int kFps = 60;

  /// <summary>
  /// フェードイン時間
  /// </summary>
  const float kFadeInTime = 0.01f;

  /// <summary>
  /// フェード値を定数kFadeValueに格納する
  /// </summary>
  static const int kFadeValue = 250;

  /// <summary>
  /// アルファ値から引く値を定数kPlusAlphaに格納する
  /// </summary>
  static const int kPlusAlpha = 25;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Player::Player(Task task_id, TaskManager* task_manager)
  : Task(task_id)
  , now_phase_(kPreraration)
  , task_manager_(task_manager)
  , x_coordinate_(kStartPlayerX)
  , y_coordinate_(kStartPlayerY)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , now_direction_(kNone)
  , display_x_coordinate_(0.0f)
  , display_y_coordinate_(0.0f)
  , accumulation_time_(0.0f)
  , keyinput_accumulation_time_(0.0f)
  , jump_accumulation_time_(0.0f)
  , rotation_accumulation_time_(0.0f)
  , star_accumulation_time_(0.0f)
  , jump_speed_accumulation_time_(0.0f)
  , hit_accumulation_time_(0.0f)
  , piece_bottom_(0)
  , piece_top_(0)
  , piece_left_(0)
  , piece_right_(0)
  , is_hit_bottom_(false)
  , is_hit_right_(false)
  , is_hit_left_(false)
  , is_hit_head_(false)
  , move_sound_handle_(0)
  , move_handle_(0)
  , sound_volume_(0)
  , idling_gr_handle_{}
  , walking_gr_handle_{}
  , hit_gr_handle_{}
  , jump_gr_handle_(0)
  , fall_gr_handle_(0)
  , status_type_(kIdolRight)
  , index_(0)
  , dash_effect_gr_handle_{}
  , jump_effect_gr_handle_{}
  , star_effect_gr_handle_{}
  , jump_index_(0)
  , difference_x_pos_(0)
  , is_ground_(true)
  , is_display_jump_effect_(false)
  , is_display_dash_effect_(false)
  , is_fade_dash_effect_(false)
  , angle_type_(kAngle0)
  , star_index_(0)
  , fall_accumulation_count_(0.0f)
  , is_pile_bottom_(false)
  , is_pile_right_(false)
  , is_pile_left_(false)
  , player_hp_(kThree)
  , is_hit_wait_(false)
  , hit_wait_accumulation_time_(0.0f)
  , step_jump_accumulation_time_(0.0f)
  , is_pushed_jump_this_frame_(false)
  , is_down_jump_(false)
  , is_down_right_(false)
  , is_down_left_(false)
  , jump_speed_(0.0f)
  , is_finish_jump_(false)
  , is_jumping_(false)
  , image_fade_(0)
  , is_image_fade_(false)
  , image_display_accumulation_time_(0.0f)
  , is_image_fade_end_(false)
  , is_finish_opening_display_(false)
{
  DEBUG_PRINT(Playerのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Player::~Player() {
  DEBUG_PRINT(Playerのデストラクタ);
}

/// <summary>
/// 毎フレーム更新処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>なし</returns>
void Player::UpdateFrame(float time) {
  if (now_phase_ != kStop && now_phase_ != kFinish && now_phase_ != kPreraration) {

    //入力管理を取得
    InputManager* input_manager = InputManager::GetInstance();

    //衝突判定のインスタンスを取得する
    Collision* collision_ = Collision::GetInstance();

    //落下状態でも落下時の演出が終わった状態でもないか判定する
    bool isnt_drop_and_finish_drop = IsNotDropAndFinishDrop();

    //足元が地面やブロック等と接しているか判定する
    if (status_type_ != kFinishDrop) {
      bool is_ground = collision_->IsFootGround(x_coordinate_, y_coordinate_, kPlayerSize);
      if (is_ground) {
        is_ground_ = true;
        is_finish_jump_ = false;
      }
      else {
        is_ground_ = false;
      }
    }

    //頭がブロック等と接しているか判定する
    bool is_head = collision_->IsHitHead(x_coordinate_, y_coordinate_, kPlayerSize);
    if (is_head) {
      is_hit_head_ = true;
    }
    else {
      is_hit_head_ = false;
    }

    //プレイヤーの右端に地面かブロックがあるかの有無を設定する
    bool is_right = collision_->IsHitRight(x_coordinate_, y_coordinate_, kPlayerSize);
    if (is_right) {
      is_hit_right_ = true;
    }
    else {
      is_hit_right_ = false;
    }
    //プレイヤーの左端に地面かブロックがあるかの有無を設定する
    bool is_left = collision_->IsHitLeft(x_coordinate_, y_coordinate_, kPlayerSize);
    if (is_left) {
      is_hit_left_ = true;
    }
    else {
      is_hit_left_ = false;
    }

    //ステージ開始時の表示が終わっていたらキー操作を有効にする
    if (is_finish_opening_display_) {
      //右ボタンが押されたら、X位置を増やす
      if (input_manager->IsDown(InputManager::GameKeyKind::kRight) && status_type_ != kHitRight && status_type_ != kHitLeft && isnt_drop_and_finish_drop) {
        is_down_right_ = true;
        if (is_ground_) {
          //地面に付いている時だけ、歩く状態に変える
          status_type_ = kWalkRight;
        }
        if ((x_coordinate_ < (kTotalColumn - 1) * kMapSize - (kMapSize * kFour)) && is_hit_right_ == false) {
          x_coordinate_ = x_coordinate_ + kTwo;
        }
        //右ボタンと一緒にXボタンが押されたら、ダッシュする
        if (input_manager->IsDown(InputManager::GameKeyKind::kX)) {
          is_display_dash_effect_ = true;
          if ((x_coordinate_ < (kTotalColumn - 1) * kMapSize - (kMapSize * kFour)) && is_hit_right_ == false) {
            x_coordinate_ = x_coordinate_++;
          }
        }
        else if (input_manager->IsReleasedKeyThisFlame(InputManager::GameKeyKind::kX)) {
          is_display_dash_effect_ = false;
          is_fade_dash_effect_ = true;
        }
      }
      else if (input_manager->IsReleasedKeyThisFlame(InputManager::GameKeyKind::kRight) && isnt_drop_and_finish_drop) {
        is_down_right_ = false;
        status_type_ = kIdolRight;
        if (is_display_dash_effect_) {
          is_fade_dash_effect_ = true;
        }
        is_display_dash_effect_ = false;
      }

      //左ボタンが押されたら、X位置を減らす
      if (input_manager->IsDown(InputManager::GameKeyKind::kLeft) && status_type_ != kHitRight && status_type_ != kHitLeft && isnt_drop_and_finish_drop) {
        is_down_left_ = true;
        if (is_ground_) {
          //地面に付いている時だけ、歩く状態に変える
          status_type_ = kWalkLeft;
        }
        if ((x_coordinate_ >= kTwo) && is_hit_left_ == false) {
          x_coordinate_ = x_coordinate_ - kTwo;
        }
        //左ボタンと一緒にXボタンが押されたら、ダッシュする
        if (input_manager->IsDown(InputManager::GameKeyKind::kX)) {
          is_display_dash_effect_ = true;
          if ((x_coordinate_ >= kTwo) && is_hit_left_ == false) {
            x_coordinate_ = x_coordinate_--;
          }
        }
        else if (input_manager->IsReleasedKeyThisFlame(InputManager::GameKeyKind::kX)) {
          is_display_dash_effect_ = false;
          is_fade_dash_effect_ = true;
        }
      }
      else if (input_manager->IsReleasedKeyThisFlame(InputManager::GameKeyKind::kLeft) && isnt_drop_and_finish_drop) {
        is_down_left_ = false;
        status_type_ = kIdolLeft;
        if (is_display_dash_effect_) {
          is_fade_dash_effect_ = true;
        }
        is_display_dash_effect_ = false;
      }

      //ジャンプに対応するキーがこのフレームで押されたか判定する
      is_pushed_jump_this_frame_ = IsPushJumpThisFlame();
      //ジャンプに対応するキーが押されているか判定する
      is_down_jump_ = IsDownJump();

      //上ボタンまたはZボタンが押されたら、Y位置が上昇する
      if (is_pushed_jump_this_frame_ == true && status_type_ != kHitRight && status_type_ != kHitLeft && isnt_drop_and_finish_drop && status_type_ != kFallRight && status_type_ != kFallLeft && (!is_finish_jump_)) {
        is_jumping_ = true;
        is_display_jump_effect_ = true;
      }
      else if (is_down_jump_ == true && status_type_ != kHitRight && status_type_ != kHitLeft && isnt_drop_and_finish_drop && status_type_ != kFallRight && status_type_ != kFallLeft && (!is_finish_jump_)) {

        //累積時間によって変化するジャンプの速さを計算する
        jump_speed_ = CalculateJumpSpeed(time);

        //DEBUG_PRINT_VAR(jump_speed_);

        //状態をジャンプの状態にする
        if (status_type_ == kIdolRight || status_type_ == kWalkRight) {
          status_type_ = kJumpRight;
        }
        else if (status_type_ == kIdolLeft || status_type_ == kWalkLeft) {
          status_type_ = kJumpLeft;
        }
        if (!is_hit_head_) {
          y_coordinate_ = y_coordinate_ - static_cast<int>(jump_speed_);
          bool is_head = collision_->IsHitHead(x_coordinate_, y_coordinate_, kPlayerSize);
          if (is_head) {
            is_hit_head_ = true;
          }
        }
        //プレイヤーの左右の端に地面かブロック等があるかを確認する
        collision_->IsHitLeft(x_coordinate_, y_coordinate_, kPlayerSize);
        collision_->IsHitRight(x_coordinate_, y_coordinate_, kPlayerSize);
        //プレイヤーの左右の足元が物体と重なるかを判定
        collision_->IsHitLeftFoot(x_coordinate_, y_coordinate_, kPlayerSize);
        collision_->IsHitRightFoot(x_coordinate_, y_coordinate_, kPlayerSize);
        //プレイヤーの左右の真上が物体と重なるかを判定
        collision_->IsHitLeftHead(x_coordinate_, y_coordinate_, kPlayerSize);
        collision_->IsHitRightHead(x_coordinate_, y_coordinate_, kPlayerSize);
      }
      //キーが離れたら、状態を降りる状態にする
      else if (input_manager->IsReleasedKeyThisFlame(InputManager::GameKeyKind::kUp) || input_manager->IsReleasedKeyThisFlame(InputManager::GameKeyKind::kZ) || jump_speed_accumulation_time_ == kJumpLimitTime) {
        is_finish_jump_ = true;
      }

    }

    //足元に地面やブロック等が無い場合、重力で落下する
    if (is_ground_ == false && ((is_down_jump_ == false && is_pushed_jump_this_frame_ == false) || is_finish_jump_ == true || ((!is_jumping_) && (jump_speed_accumulation_time_ == 0.0f)))) {
      //プレイヤーの左右の足元が物体と重なるかを判定
      CheckPlayerXFootCollision();
      //プレイヤーの左右の真上が物体と重なるかを判定
      CheckPlayerXHeadCollision();
      if (jump_speed_ > 0.0f) {
        jump_speed_ = jump_speed_ - kJumpReduceTime;
      }
      else if (jump_speed_ <= 0.0f) {
        if (status_type_ == kJumpRight) {
          status_type_ = kFallRight;
        }
        else if (status_type_ == kJumpLeft) {
          status_type_ = kFallLeft;
        }
        jump_speed_ = 0.0f;
      }
      //累積時間によって変化する降りる速さを計算する
      float fall_speed = kInitialRate * (fall_accumulation_count_ / kFallLimitTime);
      //DEBUG_PRINT_VAR(fall_speed);
      if (is_hit_head_) {
        fall_speed = jump_speed_ + 1;
      }
      y_coordinate_ = static_cast<int>(y_coordinate_ + fall_speed - jump_speed_);
      //DEBUG_PRINT_VAR(jump_speed_);
      //DEBUG_PRINT_VAR(jump_speed_ - fall_speed);
      if (status_type_ != kFinishDrop) {
        bool is_ground = collision_->IsFootGround(x_coordinate_, y_coordinate_, kPlayerSize);
        if (is_ground) {
          //DEBUG_PRINT(is_ground);
          jump_speed_accumulation_time_ = 0.0f;
          is_ground_ = true;
          is_finish_jump_ = false;
          is_jumping_ = false;
          //まだジャンプキーが押されていた場合、ジャンプのエフェクトを表示する
          if (is_down_jump_) {
            is_display_jump_effect_ = true;
          }
        }
      }
      //プレイヤーの左右の端に地面かブロック等があるかの有無を設定する
      CheckPlayerXCollision();
      //DEBUG_PRINT_VAR(fall_speed);
      if (status_type_ == kIdolRight || status_type_ == kWalkRight) {
        status_type_ = kFallRight;
      }
      else if (status_type_ == kIdolLeft || status_type_ == kWalkLeft) {
        status_type_ = kFallLeft;
      }
      //画面の下まで落ちた場合
      if ((y_coordinate_ > kTotalRow * kMapSize) && status_type_ != kFinishDrop) {
        jump_speed_accumulation_time_ = 0.0f;
      }
      fall_accumulation_count_ = fall_accumulation_count_ + time;
    }
    //足元に地面やブロック等があり、着地状態である場合は待機状態に戻す
    else if (is_ground_ == true) {
      fall_accumulation_count_ = 0.0f;
      if (status_type_ == kFallRight) {
        status_type_ = kIdolRight;
      }
      else if (status_type_ == kFallLeft) {
        status_type_ = kIdolLeft;
      }
    }

    accumulation_time_ = accumulation_time_ + time;

    //DEBUG_PRINT_VAR(jump_accumulation_time_);

    if (is_display_jump_effect_) {
      //ジャンプのエフェクトの描画で使用する累積時間にtimeを足す
      jump_accumulation_time_ = jump_accumulation_time_ + time;
    }
      
    //ジャンプの描画で使うjump_index_を累積時間によって更新する
    for (int i = 0; i < (kJumpEffectX - 1); i++) {
      if (jump_accumulation_time_ >= kJumpEffectChangeTime[i]) {
        jump_index_ = i + 1;
      }
    }
    for (int i = 0; i < ((static_cast<int>(kPlayerMax) / kTwo)); i++) {
      if ((static_cast<int>(status_type_) / kTwo) == i) {
        if (jump_accumulation_time_ > kJumpEffectChangeTime[kJumpEffectX - 1]) {
          jump_accumulation_time_ = 0.0f;
          jump_index_ = 0;
          is_display_jump_effect_ = false;
        }
      }
    }

    //累積時間に応じて、グラフィックハンドルで使用する要素番号を増やす
    for (int i = 0; i < (kPlayerWalkingX); i++) {
      if (accumulation_time_ >= kChangeTime[i]) {
        index_ = i + 1;
      }
    }
    for (int i = 0; i < ((static_cast<int>(kPlayerMax) / kTwo)); i++) {
      if ((static_cast<int>(status_type_)/ kTwo) == i) {
        if (accumulation_time_ > kChangeTime[kPartitionNumbers[i]-1]) {
          accumulation_time_ = 0.0f;
          index_ = 0;
        }
      }
    }

    //回転表示用の累積時間を更新する
    rotation_accumulation_time_ = rotation_accumulation_time_ + time;
    if (rotation_accumulation_time_ >= kLimitTime) {
      rotation_accumulation_time_ = 0.0f;
    }

    //累積時間によって角度を変更する
    for (int i = 0; i < (kAnglesElement + 1); i++) {
      if (rotation_accumulation_time_ >= kWaitTimes[i] && rotation_accumulation_time_ < kWaitTimes[i + 1]) {
        angle_type_ = static_cast<AngleType>((i));
        //DEBUG_PRINT_VAR(angle_type_);
      }
    }

    //DEBUG_PRINT_VAR(index_);
  }

  //画面下まで落下の状態の場合
  if (status_type_ == kDrop) {
    //星表示用の累積時間を更新する
    star_accumulation_time_ = star_accumulation_time_ + time;
    if (star_accumulation_time_ >= kStarLimitTime) {
      star_accumulation_time_ = 0.0f;
    }
    //累積時間によって表示する星のアニメーションの要素を変更する
    for (int i = 0; i < ((kStarEffectX * kStarEffectY) + 1); i++) {
      if (star_accumulation_time_ >= kStarWaitTimes[i] && star_accumulation_time_ < kStarWaitTimes[i + 1]) {
        star_index_ = i;
        //DEBUG_PRINT_VAR(star_index_);
      }
    }

    //累積時間によって飛び上がる高さを計算する
    jump_speed_ = CalculateJumpSpeed(time);

    y_coordinate_ = y_coordinate_ - static_cast<int>(jump_speed_) * kTwo;
    if (jump_speed_accumulation_time_ == kJumpLimitTime) {
      status_type_ = kFinishDrop;
    }
  }

  //ダッシュのエフェクトがフェードアウトし始める場合
  if (is_fade_dash_effect_) {
    image_display_accumulation_time_ = image_display_accumulation_time_ + time;
    if (image_display_accumulation_time_ >= kFadeInTime) {
      image_fade_++;
      image_display_accumulation_time_ = 0;
      DEBUG_PRINT_VAR(image_fade_);
    }
    if (image_fade_ > ((kFadeValue / kPlusAlpha))) {
      image_fade_ = 0;
      is_fade_dash_effect_ = false;
    }
  }

  CheckPlayerXCollision();
}

/// 毎フレーム描画処理
/// </remarks>
/// <param>なし</param>
/// <returns>なし</returns>
void Player::RenderFrame() {
  //DEBUG_PRINT(Playerの毎フレーム描画処理);
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

    //フェードマネージャーのインスタンスを取得
    FadeManager* fade_manager = FadeManager::GetInstance();

    //グラフィックハンドルを配列に格納する
    int graphic_handles[] = { idling_gr_handle_[(index_) % kPlayerIdlingX], walking_gr_handle_[(index_) % kPlayerWalkingX], hit_gr_handle_[(index_) % kPlayerHitX], jump_gr_handle_, fall_gr_handle_ };

    //プレイヤーの状態に応じて描画する
    for (int i = 0; i < ((static_cast<int>(kPlayerMax) / kTwo)); i++) {
      if ((static_cast<int>(status_type_) / kTwo) == i) {
        //status_type_が奇数の場合は左方向に進む描画
        if ((static_cast<int>(status_type_) % kTwo) == 1) {
          DrawRotaGraph((x_coordinate_ + static_cast<int>(half_width_) - difference_x_pos_), (y_coordinate_ + static_cast<int>(half_height_)), 1.0f, 0.0, graphic_handles[i], TRUE, TRUE);
          //ダッシュのエフェクトの描画
          if (is_display_dash_effect_ && is_ground_) {
            DrawGraph((x_coordinate_ + kDashEffLeftX - difference_x_pos_), (y_coordinate_ - (kMapSize / kTwo)), dash_effect_gr_handle_[(index_) % kDashEffectX], TRUE);
          }
          //ダッシュのエフェクトがフェードアウトし始める場合
          else if (is_fade_dash_effect_) {
            if (image_fade_ <= (kFadeValue / kPlusAlpha)) {
              fade_manager->FadeImage((x_coordinate_ + kDashEffLeftX - difference_x_pos_), (y_coordinate_ - (kMapSize / kTwo)), dash_effect_gr_handle_[(index_) % kDashEffectX], ((kFadeValue / kPlusAlpha) - image_fade_), kPlusAlpha);
            }
          }
        }
        //status_type_が偶数の場合は右方向に進む描画
        else {
          DrawGraph((x_coordinate_ - difference_x_pos_), (y_coordinate_), graphic_handles[i], TRUE);
          //ダッシュのエフェクトの描画
          if (is_display_dash_effect_ && is_ground_) {
            DrawRotaGraph(((x_coordinate_ - kDashEffRightX - difference_x_pos_) + (kDashEffectSize / kTwo)), (y_coordinate_ + (kDashEffectSize / kTwo) - (kMapSize / kTwo)), 1.0f, 0.0, dash_effect_gr_handle_[(index_) % kDashEffectX], TRUE, TRUE);
          }
          //ダッシュのエフェクトがフェードアウトし始める場合
          else if (is_fade_dash_effect_ && is_ground_) {
            if (image_fade_ <= (kFadeValue / kPlusAlpha)) {
              fade_manager->FadeRotaGraph(((x_coordinate_ - kDashEffRightX - difference_x_pos_) + (kDashEffectSize / kTwo)), (y_coordinate_ + (kDashEffectSize / kTwo) - (kMapSize / kTwo)), 1.0f, 0.0, dash_effect_gr_handle_[(index_) % kDashEffectX], ((kFadeValue / kPlusAlpha) - image_fade_), kPlusAlpha);
            }
          }
        }   
      }
    }

    //ジャンプの状態の場合、ジャンプのエフェクトを描画する
    if ((status_type_ == kJumpRight || status_type_ == kJumpLeft) && keyinput_accumulation_time_ < kFirstLimitTime) {
      DrawGraph((x_coordinate_ - difference_x_pos_), (y_coordinate_ + kDashEffLeftX), jump_effect_gr_handle_[(jump_index_) % kJumpEffectX], TRUE);
    }

    //画面の下に落下した時の描画
    if (status_type_ == kDrop || status_type_ == kFinishDrop) {
      for (int j = 0; j < kAnglesElement; j++) {
        if (angle_type_ == static_cast<AngleType>(j)) {
          DrawGraph((x_coordinate_  + kStarEffX - difference_x_pos_), (y_coordinate_ + kStarEffY), star_effect_gr_handle_[star_index_], TRUE);
          DrawRotaGraph((x_coordinate_ + static_cast<int>(half_width_) - difference_x_pos_), (y_coordinate_ + static_cast<int>(half_height_)), 1.0, kAngles[j], jump_gr_handle_, TRUE);
        }
      }
    }
  }
}

/// <summary>
/// SetXPosition関数の定義
/// </summary>
/// <param = "x_coordinate">X座標</param>
/// <returns>なし</returns>
void Player::SetXPosition(int x_coordinate) {
  x_coordinate_ = x_coordinate;
}

/// <summary>
/// GetXPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>X座標</returns>
int Player::GetXPosition() {
  return x_coordinate_;
}

/// <summary>
/// SetYPosition関数の定義
/// </summary>
/// <param = "y_coordinate">Y座標</param>
/// <returns>なし</returns>
void Player::SetYPosition(int y_coordinate) {
  y_coordinate_ = y_coordinate;
}

/// <summary>
/// GetYPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Y座標</returns>
int Player::GetYPosition() {
  return y_coordinate_;
}

/// <summary>
/// SetWidth関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void Player::SetWidth(int size_x) {
  width_ = size_x;
}

/// <summary>
/// GetWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int Player::GetWidth() {
  return width_;
}

/// <summary>
/// SetHeight関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void Player::SetHeight(int size_y) {
  height_ = size_y;
}

/// <summary>
/// GetHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さ</returns>
int Player::GetHeight() {
  return height_;
}

/// <summary>
/// SetHalfWidth関数の定義
/// </summary>
/// <param>画像の幅の半分</param>
/// <returns>なし</returns>
void Player::SetHalfWidth(float size_half_x) {
  half_width_ = size_half_x;
}

/// <summary>
/// GetHalfWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅の半分</returns>
float Player::GetHalfWidth() {
  return half_width_;
}

/// <summary>
/// SetHalfHeight関数の定義
/// </summary>
/// <param>画像の高さの半分</param>
/// <returns>なし</returns>
void Player::SetHalfHeight(float size_half_y) {
  half_height_ = size_half_y;
}

/// <summary>
/// GetHalfHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さの半分</returns>
float Player::GetHalfHeight() {
  return half_height_;
}

/// <summary>
/// SetDirectionType関数の定義
/// </summary>
/// <param = "direction">方向の種類</param>
/// <returns>なし</returns>
void Player::SetDirectionType(DirectionType direction) {
  now_direction_ = direction;
}

/// <summary>
/// GetDirectionType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
Player::DirectionType Player::GetDirectionType() {
  return now_direction_;
}

/// <summary>
/// SetPhaseType関数の定義
/// </summary>
/// <param = "type">方向の種類</param>
/// <returns>なし</returns>
void Player::SetPhaseType(PhaseType type) {
  now_phase_ = type;
}

/// <summary>
/// GetPhaseType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
Player::PhaseType Player::GetPhaseType() {
  return now_phase_;
}

/// <summary>
/// SetDisplayXPosition関数の定義
/// </summary>
/// <param = "display_x_coordinate">表示用のX座標</param>
/// <returns>なし</returns>
void Player::SetDisplayXPosition(float display_x_coordinate) {
  display_x_coordinate_ = display_x_coordinate;
}

/// <summary>
/// GetDisplayXPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>表示用のX座標</returns>
float Player::GetDisplayXPosition() {
  return display_x_coordinate_;
}

/// <summary>
/// SetDisplayYPosition関数の定義
/// </summary>
/// <param = "display_y_coordinate">表示用のY座標</param>
/// <returns>なし</returns>
void Player::SetDisplayYPosition(float display_y_coordinate) {
  display_y_coordinate_ = display_y_coordinate;
}

/// <summary>
/// GetDisplayYPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>表示用のY座標</returns>
float Player::GetDisplayYPosition() {
  return display_y_coordinate_;
}

/// <summary>
/// GetPieceTop関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>最上部の位置</returns>
int Player::GetPieceTop() {
  //int x, y;

  return 0;
}

/// <summary>
/// GetPieceBottom関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>最下部の位置</returns>
int Player::GetPieceBottom() {
  //int x, y;

  return 0;
}

/// <summary>
/// GetPieceLeft関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>最左部の位置</returns>
int Player::GetPieceLeft() {
  //int x, y;

  return 0;
}

/// <summary>
/// GetPieceRight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>最右部の位置</returns>
int Player::GetPieceRight() {
  //int x, y;

  return 0;
}

/// <summary>
/// SetHitBottom関数の定義
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void Player::SetHitBottom(bool is_hit_bottom) {
  is_hit_bottom_ = is_hit_bottom;
}

/// <summary>
/// SetHitRight関数の定義
/// </summary>
/// <param = "is_hit_right">右に移動する時に他とぶつかっているかの有無</param>
/// <returns>なし</returns>
void Player::SetHitRight(bool is_hit_right) {
  is_hit_right_ = is_hit_right;
}

/// <summary>
/// SetHitLeft関数の定義
/// </summary>
/// <param = "is_hit_left">左に移動する時に他とぶつかっているかの有無</param>
/// <returns>なし</returns>
void Player::SetHitLeft(bool is_hit_left) {
  is_hit_left_ = is_hit_left;
}

/// <summary>
/// SetHitHead関数の宣言
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void Player::SetHitHead(bool is_hit) {
  is_hit_head_ = is_hit;
}

/// <summary>
/// IsHitHead関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>頭上で物とぶつかっているかの有無</returns>
bool Player::IsHitHead() {
  return is_hit_head_;
}

/// <summary>
/// 下に移動する時に衝突したかを確認する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
int Player::CheckIsHitPlayersBottom() {

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
void Player::SetMoveSoundHandle(int move_sound_handle) {
  move_sound_handle_ = move_sound_handle;
}

/// <summary>
/// GetMoveSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>サウンドハンドル</returns>
int Player::GetMoveSoundHandle() {
  return move_sound_handle_;
}

/// <summary>
/// SetXMoveSoundHandle関数の定義
/// </summary>
/// <param = "move_handle">左右移動時のサウンドハンドル</param>
/// <returns>なし</returns>
void Player::SetXMoveSoundHandle(int move_handle) {
  move_handle_ = move_handle;
}

/// <summary>
/// GetXMoveSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>左右移動時のサウンドハンドル</returns>
int Player::GetXMoveSoundHandle() {
  return move_handle_;
}

/// <summary>
/// SetSoundVolume関数の定義
/// </summary>
/// <param = "sound_volume">音量</param>
/// <returns>なし</returns>
void Player::SetSoundVolume(int sound_volume) {
  sound_volume_ = sound_volume;
}

/// <summary>
/// SetIdlingGrHandle関数の定義
/// </summary>
/// <param = "idling_gr_handle">待機時のグラフィックハンドル</param>
/// <returns>なし</returns>
void Player::SetIdlingGrHandle(std::array<int, kPlayerIdlingX> idling_gr_handle) {
  idling_gr_handle_ = idling_gr_handle;
}

/// <summary>
/// GetIdlingGrHandle関数の定義
/// </summary>
/// <param = "element_num">要素番号</param>
/// <returns>待機時のグラフィックハンドル</returns>
int Player::GetIdlingGrHandle(int element_num) {
  return idling_gr_handle_[element_num];
}

/// <summary>
/// SetWalkingGrHandle関数の定義
/// </summary>
/// <param = "walking_gr_handle">歩行時のグラフィックハンドル</param>
/// <returns>なし</returns>
void Player::SetWalkingGrHandle(std::array<int, kPlayerWalkingX> walking_gr_handle) {
  walking_gr_handle_ = walking_gr_handle;
}

/// <summary>
/// GetWalkingGrHandle関数の定義
/// </summary>
/// <param = "element_num">要素番号</param>
/// <returns>歩行時のグラフィックハンドル</returns>
int Player::GetWalkingGrHandle(int element_num) {
  return walking_gr_handle_[element_num];
}

/// <summary>
/// SetHitGrHandle関数の定義
/// </summary>
/// <param = "hit_gr_handle">ヒット時のグラフィックハンドル</param>
/// <returns>なし</returns>
void Player::SetHitGrHandle(std::array<int, kPlayerHitX> hit_gr_handle) {
  hit_gr_handle_ = hit_gr_handle;
}

/// <summary>
/// GetHitGrHandle関数の定義
/// </summary>
/// <param = "element_num">要素番号</param>
/// <returns>ヒット時のグラフィックハンドル</returns>
int Player::GetHitGrHandle(int element_num) {
  return hit_gr_handle_[element_num];
}

/// <summary>
/// SetJumpGrHandle関数の定義
/// </summary>
/// <param = "jump_gr_handle">ジャンプ時のグラフィックハンドル</param>
/// <returns>なし</returns>
void Player::SetJumpGrHandle(int jump_gr_handle) {
  jump_gr_handle_ = jump_gr_handle;
}

/// <summary>
/// GetJumpGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ジャンプ時のグラフィックハンドル</returns>
int Player::GetJumpGrHandle() {
  return jump_gr_handle_;
}

/// <summary>
/// SetFallGrHandle関数の定義
/// </summary>
/// <param = "fall_gr_handle">着地時のグラフィックハンドル</param>
/// <returns>なし</returns>
void Player::SetFallGrHandle(int fall_gr_handle) {
  fall_gr_handle_ = fall_gr_handle;
}

/// <summary>
/// GetFallGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>着地時のグラフィックハンドル</returns>
int Player::GetFallGrHandle() {
  return fall_gr_handle_;
}

/// <summary>
/// SetDashEffectGrHandle関数の定義
/// </summary>
/// <param = "dash_effect_gr_handle">ダッシュ時のエフェクトのグラフィックハンドル</param>
/// <returns>なし</returns>
void Player::SetDashEffectGrHandle(std::array<int, kDashEffectX> dash_effect_gr_handle) {
  dash_effect_gr_handle_ = dash_effect_gr_handle;
}

/// <summary>
/// GetDashEffectGrHandle関数の定義
/// </summary>
/// <param = "element_num">要素番号</param>
/// <returns>ダッシュ時のエフェクトのグラフィックハンドル</returns>
int Player::GetDashEffectGrHandle(int element_num) {
  return dash_effect_gr_handle_[element_num];
}

/// <summary>
/// SetJumpEffectGrHandle関数の定義
/// </summary>
/// <param = "jump_effect_gr_handle">ジャンプ時のエフェクトのグラフィックハンドル</param>
/// <returns>なし</returns>
void Player::SetJumpEffectGrHandle(std::array<int, kJumpEffectX> jump_effect_gr_handle) {
  jump_effect_gr_handle_ = jump_effect_gr_handle;
}

/// <summary>
/// GetJumpEffectGrHandle関数の定義
/// </summary>
/// <param = "element_num">要素番号</param>
/// <returns>ジャンプ時のエフェクトのグラフィックハンドル</returns>
int Player::GetJumpEffectGrHandle(int element_num) {
  return jump_effect_gr_handle_[element_num];
}

/// <summary>
/// SetDifferenceXpos関数の定義
/// </summary>
/// <param>フィールドの描画X位置を調整するための整数</param>
/// <returns>なし</returns>
void Player::SetDifferenceXpos(int difference_x_pos) {
  difference_x_pos_ = difference_x_pos;
}

/// <summary>
/// SetFootGround関数の定義
/// </summary>
/// <param = "is_ground">プレイヤーの足元に地面やブロックがあるかの有無</param>
/// <returns>なし</returns>
void Player::SetFootGround(bool is_ground) {
  is_ground_ = is_ground;
}

/// <summary>
/// GetStatusType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>プレイヤーの状態</returns>
Player::StatusType Player::GetStatusType() {
  return status_type_;
}

/// <summary>
/// SetStatusType関数の定義
/// </summary>
/// <param = "status_type">プレイヤーの状態</param>
/// <returns>なし</returns>
void Player::SetStatusType(StatusType status_type) {
  status_type_ = status_type;
}

/// <summary>
/// IsDash関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>ダッシュしているか</returns>
bool Player::IsDash() {
  return is_display_dash_effect_;
}

/// <summary>
/// SetStarEffectGrHandle関数の定義
/// </summary>
/// <param = "star_effect_gr_handle">プレイヤー落下時の星のエフェクトのグラフィックハンドル</param>
/// <returns>なし</returns>
void Player::SetStarEffectGrHandle(std::array<int, (kStarEffectX* kStarEffectY)> star_effect_gr_handle) {
  star_effect_gr_handle_ = star_effect_gr_handle;
}

/// <summary>
/// GetStarEffectGrHandle関数の定義
/// </summary>
/// <param = "element_num">要素番号</param>
/// <returns>プレイヤー落下時の星のエフェクトのグラフィックハンドル</returns>
int Player::GetStarEffectGrHandle(int element_num) {
  return star_effect_gr_handle_[element_num];
}

/// <summary>
/// CalculateJumpSpeed関数の宣言
/// </summary>
/// <param ="time">毎フレーム更新時間</param>
/// <returns>なし</returns>
float Player::CalculateJumpSpeed(float time) {

  jump_speed_accumulation_time_ = jump_speed_accumulation_time_ + time;
  //累積時間が一定時間を超えない様にする
  if (jump_speed_accumulation_time_ > kJumpLimitTime) {
    jump_speed_accumulation_time_ = kJumpLimitTime;
    is_finish_jump_ = true;
  }

  //累積時間によって飛び上がる高さを計算する
  float jump_speed = kInitialRate * (kFloatOne - jump_speed_accumulation_time_ / kJumpLimitTime);

  return jump_speed;
}

/// <summary>
/// SetPileBottom関数の定義
/// </summary>
/// <param = "is_pile_bottom">プレイヤーの足元が地面やブロックと重なっているかの有無</param>
/// <returns>なし</returns>
void Player::SetPileBottom(bool is_pile_bottom) {
  is_pile_bottom_ = is_pile_bottom;
}

/// <summary>
/// SetPileRight関数の定義
/// </summary>
/// <param = "is_pile_right">プレイヤーの右が地面やブロックと重なっているかの有無</param>
/// <returns>なし</returns>
void Player::SetPileRight(bool is_pile_right) {
  is_pile_right_ = is_pile_right;
}

/// <summary>
/// SetPileLeft関数の定義
/// </summary>
/// <param = "is_pile_left">プレイヤーの左が地面やブロックと重なっているかの有無</param>
/// <returns>なし</returns>
void Player::SetPileLeft(bool is_pile_left) {
  is_pile_left_ = is_pile_left;
}

/// <summary>
/// SetPlayerHp関数の定義
/// </summary>
/// <param = "player_hp">プレイヤーのHP</param>
/// <returns>なし</returns>
void Player::SetPlayerHp(int player_hp) {
  player_hp_ = player_hp;
}

/// <summary>
/// GetPlayerHp関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>プレイヤーのHP</returns>
int Player::GetPlayerHp() {
  return player_hp_;
}

/// <summary>
/// SetHitWait関数の宣言
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void Player::SetHitWait(bool is_hit_wait) {
  is_hit_wait_ = is_hit_wait;
}

/// <summary>
/// IsHitWait関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>次のダメージを受けるまでの待ち時間であるかの有無</returns>
bool Player::IsHitWait() {
  return is_hit_wait_;
}

/// <summary>
/// IsPushJumpThisFlame関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ジャンプに対応するボタンがこのフレームで押されたかの有無</returns>
bool Player::IsPushJumpThisFlame() {
  //入力管理を取得
  InputManager* input_manager = InputManager::GetInstance();
  //上キーまたはZキーがこのフレームで押されたか判定する
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kUp) || input_manager->IsPushThisFlame(InputManager::GameKeyKind::kZ)) {
    return true;
  }
  return false;
}

/// <summary>
/// IsDownJump関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ジャンプに対応するボタンが押されているかの有無</returns>
bool Player::IsDownJump() {
  //入力管理を取得
  InputManager* input_manager = InputManager::GetInstance();
  //上キーまたはZキーが押されているか判定する
  if (input_manager->IsDown(InputManager::GameKeyKind::kUp) || input_manager->IsDown(InputManager::GameKeyKind::kZ)) {
    return true;
  }
  return false;
}

/// <summary>
/// CheckPlayerXCollision関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void Player::CheckPlayerXCollision() {
  //衝突判定のインスタンスを取得する
  Collision* collision_ = Collision::GetInstance();

  //反対方向の横移動のキーが押されていない時だけ、左右の衝突判定をする
  if (!is_down_right_) {
    collision_->IsHitLeft(x_coordinate_, y_coordinate_, kPlayerSize);
  }
  if (!is_down_left_) {
    collision_->IsHitRight(x_coordinate_, y_coordinate_, kPlayerSize);
  }
}

/// <summary>
/// CheckPlayerXFootCollision関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void Player::CheckPlayerXFootCollision() {
  //衝突判定のインスタンスを取得する
  Collision* collision_ = Collision::GetInstance();

  //反対方向の横移動のキーが押されていない時だけ、プレイヤーの左右の足元が物体と重なるかを判定
  if (!is_down_right_) {
    collision_->IsHitLeftFoot(x_coordinate_, y_coordinate_, kPlayerSize);
  }
  if (!is_down_left_) {
    collision_->IsHitRightFoot(x_coordinate_, y_coordinate_, kPlayerSize);
  }
}

/// <summary>
/// CheckPlayerXHeadCollision関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void Player::CheckPlayerXHeadCollision() {
  //衝突判定のインスタンスを取得する
  Collision* collision_ = Collision::GetInstance();

  //反対方向の横移動のキーが押されていない時だけ、左右の真上の衝突判定をする
  if (!is_down_right_) {
    collision_->IsHitLeftHead(x_coordinate_, y_coordinate_, kPlayerSize);
  }
  if (!is_down_left_) {
    collision_->IsHitRightHead(x_coordinate_, y_coordinate_, kPlayerSize);
  }
}

/// <summary>
/// IsNotDropAndFinishDrop関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>落下状態でも落下時の演出が終わった状態でもないかの有無</returns>
bool Player::IsNotDropAndFinishDrop() {
  //落下状態でもなく落下時の演出が終わった状態でもないか判定する
  if (status_type_ != kDrop && status_type_ != kFinishDrop) {
    return true;
  }
  return false;
}

/// <summary>
/// IsPlayerJumping関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>プレイヤーがジャンプしているかのフラグ</returns>
bool Player::IsPlayerJumping() {
  return is_display_jump_effect_;
}

/// <summary>
/// SetCanMove関数の定義
/// </summary>
/// <param = "is_finish_opening_display">ステージ開始時のプレイヤー残機数とステージ数の表示が終わったかの有無</param>
/// <returns>なし</returns>
void Player::SetCanMove(bool is_finish_opening_display) {
  is_finish_opening_display_ = is_finish_opening_display;
}