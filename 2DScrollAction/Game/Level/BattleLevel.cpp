#include <iostream>
#include <random>
#include <fstream>
#include "DxLib.h"
#include "Game/Level/BattleLevel.h"
#include "Game/GameInfo/GameInfo.h"
#include "System/Input/InputManager.h"
#include "Game/Fade/FadeManager.h"
#include "System/Math/Math.h"
#include "System/FileManager/FileManager.h"
#include "Game/Ui/InfoUi.h"
#include "Game/Audio/AudioManager.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  //黒色の値を取得
  unsigned int Cr = GetColor(0, 0, 0);

  /// <summary>
  /// 制限時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 0.5f;

  /// <summary>
  /// ヒットの制限時間を定数kHitLimitTimeに格納する
  /// </summary>
  static const float kHitLimitTime = 0.5f;

  /// <summary>
  /// ダメージの制限時間を定数kDamageLimitTimeに格納する
  /// </summary>
  static const float kDamageLimitTime = 1.5f;

  /// <summary>
  /// プレイヤーのHPが0になった時の制限時間を定数kPlayerHpZeroLimitTimeに格納する
  /// </summary>
  static const float kPlayerHpZeroLimitTime = 1.0f;

  /// <summary>
  /// タイムアップの制限時間を定数kTimeUpLimitTimeに格納する
  /// </summary>
  static const float kTimeUpLimitTime = 1.5f;

  /// <summary>
  /// ステージクリアを表示する累積時間を定数kClearLimitTimeに格納する
  /// </summary>
  static const float kClearLimitTime = 3.0f;

  /// <summary>
  /// フェード値を定数kFadeValueに格納する
  /// </summary>
  static const int kFadeValue = 250;

  /// <summary>
  /// 少し透過させた状態でフェードインする時のフェード値を定数kMiddleFadeValueに格納する
  /// </summary>
  static const int kMiddleFadeValue = 50;

  // <summary>
  //screen_handleの幅を定数kScreenHandleXに格納する
  /// <summary>
  static const int kScreenHandleX = 640;

  // <summary>
  //screen_handleの高さを定数kScreenHandleYに格納する
  /// <summary>
  static const int kScreenHandleY = 480;

  /// <summary>
  /// アルファ値に足しこむ値を定数kPlusAlphaに格納する
  /// </summary>
  static const int kPlusAlpha = 25;

  /// <summary>
  /// フェードインの待ち時間を定数kWaitTimeに格納する
  /// </summary>
  static const int kWaitTime = 100;

  /// <summary>
  //表示するX座標を定数kXcoordinateに格納する
  /// <summary>
  static const int kXcoordinate = 120;

  /// <summary>
  //表示するY座標を定数kYcoordinateに格納する
  /// <summary>
  static const int kYcoordinate = 560;

  /// <summary>
  /// BattleLevelの背景画像のファイル名を定数kBattleBackPngに格納する
  /// </summary>
  static const char* kBattleBackPng = "Assets/Images/Battle/Background/battle_back.png";

  /// <summary>
  /// BattleLevelのステージ2の背景画像のファイル名を定数kStageTwoBattleBackPngに格納する
  /// </summary>
  static const char* kStageTwoBattleBackPng = "Assets/Images/Battle/Background/stage2_back.png";

  /// <summary>
  /// キー操作情報の画像のファイル名を定数kKeyInfoPngに格納する
  /// </summary>
  static const char* kKeyInfoPng = "Assets/Images/Battle/Background/key_info.png";

  /// <summary>
  /// 黒い画像のファイル名を定数kBlackPngに格納する
  /// </summary>
  static const char* kBlackPng = "Assets/Images/Fade/black.png";

  /// <summary>
  /// ゲームオーバーの画像のファイル名を定数kGameOverPngに格納する
  /// </summary>
  static const char* kGameOverPng = "Assets/Images/gameover.png";

  /// <summary>
  /// スタートUIの画像のファイル名を定数kStartPngに格納する
  /// </summary>
  static const char* kStartPng = "Assets/Images/Ui/start.png";

  /// <summary>
  /// ポーズUIの画像のファイル名を定数kPausePngに格納する
  /// </summary>
  static const char* kPausePng = "Assets/Images/Ui/pause.png";

  /// <summary>
  /// 土管の縁部分の左側の画像のファイル名を定数kTubeRimLeftPngに格納する
  /// </summary>
  static const char* kTubeRimLeftPng = "Assets/Images/Battle/Background/tube_rim_left.png";

  /// <summary>
  /// 土管の縁部分の真ん中の画像のファイル名を定数kTubeRimMiddlePngに格納する
  /// </summary>
  static const char* kTubeRimMiddlePng = "Assets/Images/Battle/Background/tube_rim_middle.png";

  /// <summary>
  /// 土管の縁部分の右側の画像のファイル名を定数kTubeRimRightPngに格納する
  /// </summary>
  static const char* kTubeRimRightPng = "Assets/Images/Battle/Background/tube_rim_right.png";

  /// <summary>
  /// 土管の縁より下の部分の左側の画像のファイル名を定数kTubeLeftPngに格納する
  /// </summary>
  static const char* kTubeLeftPng = "Assets/Images/Battle/Background/tube_left.png";

  /// <summary>
  /// 土管の縁より下の部分の真ん中の画像のファイル名を定数kTubeMiddlePngに格納する
  /// </summary>
  static const char* kTubeMiddlePng = "Assets/Images/Battle/Background/tube_middle.png";

  /// <summary>
  /// 土管の縁より下の部分の右側の画像のファイル名を定数kTubeRightPngに格納する
  /// </summary>
  static const char* kTubeRightPng = "Assets/Images/Battle/Background/tube_right.png";

  /// <summary>
  /// 箱の画像のファイル名を定数kBoxPngに格納する
  /// </summary>
  static const char* kBoxPng = "Assets/Images/Battle/Background/float_box.png";

  /// <summary>
  /// 地面の画像のファイル名を定数kGroundPngに格納する
  /// </summary>
  static const char* kGroundPng = "Assets/Images/Battle/Background/ground.png";

  /// <summary>
  /// プレイヤーの待機時画像のファイル名を定数kPlayerIdlingPngに格納する
  /// </summary>
  static const char* kPlayerIdlingPng = "Assets/Images/Battle/Player/Idle (32x32).png";

  /// <summary>
  /// プレイヤーの歩行時画像のファイル名を定数kPlayerWalkingPngに格納する
  /// </summary>
  static const char* kPlayerWalkingPng = "Assets/Images/Battle/Player/Run (32x32).png";

  /// <summary>
  /// プレイヤーのジャンプ時画像のファイル名を定数kPlayerJumpPngに格納する
  /// </summary>
  static const char* kPlayerJumpPng = "Assets/Images/Battle/Player/Jump (32x32).png";

  /// <summary>
  /// プレイヤーの着地時画像のファイル名を定数kPlayerFallPngに格納する
  /// </summary>
  static const char* kPlayerFallPng = "Assets/Images/Battle/Player/Fall (32x32).png";

  /// <summary>
  /// プレイヤーのヒット時画像のファイル名を定数kPlayerHitPngに格納する
  /// </summary>
  static const char* kPlayerHitPng = "Assets/Images/Battle/Player/Hit (32x32).png";

  /// <summary>
  /// ゴール画像のファイル名を定数kGoalPngに格納する
  /// </summary>
  static const char* kGoalPng = "Assets/Images/Battle/Background/goal.png";

  /// <summary>
  /// 歩く敵(キノコ)の待機時画像のファイル名を定数kFirstWalkingEnemyIdlingPngに格納する
  /// </summary>
  static const char* kFirstWalkingEnemyIdlingPng = "Assets/Images/Battle/Enemy/Mushroom/Idle (32x32).png";

  /// <summary>
  /// 歩く敵(キノコ)の歩行時画像のファイル名を定数kFirstWalkingEnemyRunPngに格納する
  /// </summary>
  static const char* kFirstWalkingEnemyRunPng = "Assets/Images/Battle/Enemy/Mushroom/Run (32x32).png";

  /// <summary>
  /// 歩く敵(キノコ)のヒット時画像のファイル名を定数kFirstWalkingEnemyHitPngに格納する
  /// </summary>
  static const char* kFirstWalkingEnemyHitPng = "Assets/Images/Battle/Enemy/Mushroom/Hit.png";

  /// <summary>
  /// 歩く敵(カタツムリ)の待機時画像のファイル名を定数kSecondWalkingEnemyIdlingPngに格納する
  /// </summary>
  static const char* kSecondWalkingEnemyIdlingPng = "Assets/Images/Battle/Enemy/Snail/Idle (38x24).png";

  /// <summary>
  /// 歩く敵(カタツムリ)の歩行時画像のファイル名を定数kSecondWalkingEnemyRunPngに格納する
  /// </summary>
  static const char* kSecondWalkingEnemyRunPng = "Assets/Images/Battle/Enemy/Snail/Walk (38x24).png";

  /// <summary>
  /// 歩く敵(カタツムリ)のヒット時画像のファイル名を定数kSecondWalkingEnemyHitPngに格納する
  /// </summary>
  static const char* kSecondWalkingEnemyHitPng = "Assets/Images/Battle/Enemy/Snail/Hit (38x24).png";

  /// <summary>
  /// 飛ぶ敵の飛んでいる時の画像のファイル名を定数kFlyingEnemyFlyingPngに格納する
  /// </summary>
  static const char* kFlyingEnemyFlyingPng = "Assets/Images/Battle/Enemy/Bat/Flying (46x30).png";

  /// <summary>
  /// 飛ぶ敵のヒット時画像のファイル名を定数kFlyingEnemyHitPngに格納する
  /// </summary>
  static const char* kFlyingEnemyHitPng = "Assets/Images/Battle/Enemy/Bat/Hit (46x30).png";

  /// <summary>
  /// 土管から出て来る敵のFall画像のファイル名を定数kJumpingEnemyFallPngに格納する
  /// </summary>
  static const char* kJumpingEnemyFallPng = "Assets/Images/Battle/Enemy/Stag/stag.png";

  /// <summary>
  /// 土管から出て来る敵のGround画像のファイル名を定数kJumpingEnemyGroundPngに格納する
  /// </summary>
  static const char* kJumpingEnemyGroundPng = "Assets/Images/Battle/Enemy/FatBird/Ground (40x48).png";

  /// <summary>
  /// 土管から出て来る敵のヒット時画像のファイル名を定数kJumpingEnemyHitPngに格納する
  /// </summary>
  static const char* kJumpingEnemyHitPng = "Assets/Images/Battle/Enemy/FatBird/Hit (40x48).png";

  /// <summary>
  /// プレイヤーのジャンプ時のエフェクトの画像のファイル名を定数kJumpEffectPngに格納する
  /// </summary>
  static const char* kJumpEffectPng = "Assets/Images/Battle/Effect/jump_effect.png";

  /// <summary>
  /// プレイヤーのダッシュ時のエフェクトの画像のファイル名を定数kDashEffectPngに格納する
  /// </summary>
  static const char* kDashEffectPng = "Assets/Images/Battle/Effect/cloud_of_dust.png";

  /// <summary>
  /// パワーアップアイテム画像のファイル名を定数kPowerUpItemPngに格納する
  /// </summary>
  static const char* kPowerUpItemPng = "Assets/Images/Battle/Item/Melon.png";

  /// <summary>
  /// アイテムをゲットした時のエフェクトの画像のファイル名を定数kItemGetEffectPngに格納する
  /// </summary>
  static const char* kItemGetEffectPng = "Assets/Images/Battle/Effect/Collected.png";

  /// <summary>
  /// 星が散るエフェクトの画像のファイル名を定数kStarEffectPngに格納する
  /// </summary>
  static const char* kStarEffectPng = "Assets/Images/Battle/Effect/promi_star_anime180.png";

  /// <summary>
  /// 星が流れるエフェクトの画像のファイル名を定数kStarFlowEffectPngに格納する
  /// </summary>
  static const char* kStarFlowEffectPng = "Assets/Images/Battle/Effect/promi_star2_anime240s.png";

  /// <summary>
  /// 大きい星が流れるエフェクトの画像のファイル名を定数kBigStarFlowEffectPngに格納する
  /// </summary>
  static const char* kBigStarFlowEffectPng = "Assets/Images/Battle/Effect/big_promi_star2_anime240s.png";

  /// <summary>
  /// HPが1の時の画像のファイル名を定数kHpOnePngに格納する
  /// </summary>
  static const char* kHpOnePng = "Assets/Images/Ui/hp1.png";

  /// <summary>
  /// HPが2の時の画像のファイル名を定数kHpTwoPngに格納する
  /// </summary>
  static const char* kHpTwoPng = "Assets/Images/Ui/hp2.png";

  /// <summary>
  /// HPが3の時の画像のファイル名を定数kHpThreePngに格納する
  /// </summary>
  static const char* kHpThreePng = "Assets/Images/Ui/hp3.png";

  /// <summary>
  /// HPが4の時の画像のファイル名を定数kHpFourPngに格納する
  /// </summary>
  static const char* kHpFourPng = "Assets/Images/Ui/hp_max.png";

  /// <summary>
  /// 時計の画像のファイル名を定数kWatchPngに格納する
  /// </summary>
  static const char* kWatchPng = "Assets/Images/Ui/watch.png";

  /// <summary>
  /// カウントダウンのファイル名を定数kCountdownPngに格納する
  /// </summary>
  static const char* kCountdownPng = "Assets/Images/Ui/countdown.png";

  /// <summary>
  /// 10秒前カウントダウンの画像のファイル名を定数kTenNumberPngに格納する
  /// </summary>
  static const char* kTenNumberPng = "Assets/Images/Ui/ten_countdown.png";

  /// <summary>
  /// タイムアップの画像のファイル名を定数kTimeUpPngに格納する
  /// </summary>
  static const char* kTimeUpPng = "Assets/Images/Ui/timeup.png";

  /// <summary>
  /// ステージクリアの画像のファイル名を定数kStageClearPngに格納する
  /// </summary>
  static const char* kStageClearPng = "Assets/Images/Ui/StageClear.png";

  /// <summary>
  /// ゲームクリアの画像のファイル名を定数kGameClearPngに格納する
  /// </summary>
  static const char* kGameClearPng = "Assets/Images/Ui/congratulations.png";

  /// <summary>
  /// プレイヤー数を表示する画像のファイル名を定数kPlayerNumPngに格納する
  /// </summary>
  static const char* kPlayerNumPng = "Assets/Images/Ui/player_num.png";

  /// <summary>
  /// ゲームオーバーの動画のファイル名を定数kGameOverMp4に格納する
  /// </summary>
  static const char* kGameOverMp4 = "Assets/Images/Ui/gameover.mp4";

  /// <summary>
  /// 設定を保存するファイル名を定数kSettingCSVに格納する
  /// </summary>
  static const char* kSettingCSV = "Assets/CsvFiles/setting.csv";

  /// <summary>
  /// プレイヤーの残数を保存するファイル名を定数kPlayerNumCSVに格納する
  /// </summary>
  static const char* kPlayerNumCSV = "Assets/CsvFiles/player_num.csv";

  /// <summary>
  /// ステージ数を保存するファイル名を定数kStageNumCSVに格納する
  /// </summary>
  static const char* kStageNumCSV = "Assets/CsvFiles/stage_num.csv";

  /// <summary>
  /// 選択可能なステージを保存するファイル名を定数kSelectableStageCSVに格納する
  /// </summary>
  static const char* kSelectableStageCSV = "Assets/CsvFiles/selectable_stages.csv";

  /// <summary>
  /// 歩く敵(キノコ)の初期位置と動き始めるタイミングのデータファイル名を定数kFirstWalkingEnemyCSVsに格納する
  /// </summary>
  static const char* kFirstWalkingEnemyCSVs[] = { "Assets/CsvFiles/first_walking_enemy_data1.csv", "Assets/CsvFiles/first_walking_enemy_data2.csv", "Assets/CsvFiles/first_walking_enemy_data3.csv" };

  /// <summary>
  /// 歩く敵(カタツムリ)の初期位置と動き始めるタイミングのデータファイル名を定数kSecondWalkingEnemyCSVsに格納する
  /// </summary>
  static const char* kSecondWalkingEnemyCSVs[] = { "Assets/CsvFiles/second_walking_enemy_data1.csv", "Assets/CsvFiles/second_walking_enemy_data2.csv", "Assets/CsvFiles/second_walking_enemy_data3.csv" };

  /// <summary>
  /// ジャンプする敵(クワガタ)の初期位置と動き始めるタイミングのデータファイル名を定数kJumpingEnemyCSVsに格納する
  /// </summary>
  static const char* kJumpingEnemyCSVs[] = { "Assets/CsvFiles/jumping_enemy_data1.csv", "Assets/CsvFiles/jumping_enemy_data2.csv", "Assets/CsvFiles/jumping_enemy_data3.csv" };

  /// <summary>
  /// 飛ぶ敵(コウモリ)の初期位置と動き始めるタイミングのデータファイル名を定数kFlyingEnemyCSVsに格納する
  /// </summary>
  static const char* kFlyingEnemyCSVs[] = { "Assets/CsvFiles/flying_enemy_data1.csv", "Assets/CsvFiles/flying_enemy_data2.csv", "Assets/CsvFiles/flying_enemy_data3.csv" };

  /// <summary>
  /// アイテムの初期位置と動き始めるタイミングのデータファイル名を定数kItemCSVsに格納する
  /// </summary>
  static const char* kItemCSVs[] = { "Assets/CsvFiles/item_data1.csv", "Assets/CsvFiles/item_data2.csv", "Assets/CsvFiles/item_data3.csv" };

  /// <summary>
  /// X座標の開始位置を定数kStartPlayerXに格納する
  /// </summary>
  static const int kStartPlayerX = 5;

  /// <summary>
  /// Y座標の開始位置を定数kStartPlayerYに格納する
  /// </summary>
  static const int kStartPlayerY = 0;

  /// <summary>
  /// フェードイン時間
  /// </summary>
  const float kFadeInTime = 0.1f;

  /// <summary>
  /// 敵がヒットした時の画像の横向きの分割数を定数kEnemyHitXに格納する
  /// </summary>
  static const int kEnemyHitX = 5;

  // <summary>
  //キノコが待機している時の画像の横向きの分割数を定数kMushroomIdlingXに格納する
  /// <summary>
  static const int kMushroomIdlingX = 14;

  // <summary>
  //キノコが歩いている時の画像の横向きの分割数を定数kMushroomWalkingXに格納する
  /// <summary>
  static const int kMushroomWalkingX = 16;

  // <summary>
  //カタツムリが待機している時の画像の横向きの分割数を定数kSnailIdlingXに格納する
  /// <summary>
  static const int kSnailIdlingX = 15;

  // <summary>
  //カタツムリが歩いている時の画像の横向きの分割数を定数kSnailWalkingXに格納する
  /// <summary>
  static const int kSnailWalkingX = 10;

  // <summary>
  //キャラクターの画像の縦向きの分割数を定数kCharacterYに格納する
  /// <summary>
  static const int kCharacterY = 1;

  // <summary>
  //プレイヤーとカタツムリ以外のキャラクターの画像の幅と高さを定数kCharacterSizeに格納する
  /// <summary>
  static const int kCharacterSize = 64;

  // <summary>
  //コウモリの画像の幅を定数kBatSizeXに格納する
  /// <summary>
  static const int kBatSizeX = 92;

  // <summary>
  //コウモリの画像の高さを定数kBatSizeYに格納する
  /// <summary>
  static const int kBatSizeY = 60;

  // <summary>
  //太った鳥の画像の幅を定数kStagSizeXに格納する
  /// <summary>
  static const int kStagSizeX = 80;

  // <summary>
  //太った鳥の画像の高さを定数kFatBirdSizeYに格納する
  /// <summary>
  static const int kStagSizeY = 111;

  // <summary>
  //星が散る画像の幅と高さを定数kStarSizeに格納する
  /// <summary>
  static const int kStarSize = 180;

  // <summary>
  //星が流れる画像の幅を定数kStarFlowSizeXに格納する
  /// <summary>
  static const int kStarFlowSizeX = 35;

  // <summary>
  //星が流れる画像の高さを定数kStarFlowSizeYに格納する
  /// <summary>
  static const int kStarFlowSizeY = 70;

  // <summary>
  //大きい星が流れる画像の幅を定数kStarFlowSizeXに格納する
  /// <summary>
  static const int kBigStarFlowSizeX = 200;

  // <summary>
  //大きい星が流れる画像の高さを定数kStarFlowSizeYに格納する
  /// <summary>
  static const int kBigStarFlowSizeY = 400;

  // <summary>
  //カウントダウン画像の幅を定数kCountdownSizeXに格納する
  /// <summary>
  static const int kCountdownSizeX = 60;

  // <summary>
  //カウントダウン画像の高さを定数kCountdownSizeYに格納する
  /// <summary>
  static const int kCountdownSizeY = 85;

  /// <summary>
  /// 紙吹雪の画像のグラフィックハンドルの縦向きの分割数を定数kConfettiYに格納する
  /// </summary>
  static const int kConfettiY = 12;

  /// <summary>
  /// 紙吹雪のアニメーションコマ数を定数kConfettiCountに格納する
  /// </summary>
  static const int kConfettiCount = 5;

  /// <summary>
  /// 紙吹雪の画像のファイル名を定数kConfettiPngに格納する
  /// </summary>
  static const char* kConfettiPng = "Assets/Images/Effect/confetti.png";

  /// <summary>
  /// 整数2を定数kTwoに格納する
  /// </summary>
  static const int kTwo = 2;

  /// <summary>
  /// 整数3を定数kThreeに格納する
  /// </summary>
  static const int kThree = 3;

  /// <summary>
  /// タイムアップの画像の横向きの分割数を定数kTimeUpXに格納する
  /// </summary>
  static const int kTimeUpX = 4;

  /// <summary>
  /// タイムアップの画像の縦向きの分割数を定数kTimeUpYに格納する
  /// </summary>
  static const int kTimeUpY = 1;

  /// <summary>
  /// 文字を格納する変数bufの要素数を定数kBufElementに格納する
  /// </summary>
  static const int kBufElement = 10;

  /// <summary>
  /// 敵の設定データ2列目【敵の初期X位置】を定数kEnemyStartXに格納する
  /// </summary>
  static const int kEnemyStartX = 1;

  /// <summary>
  /// 敵の設定データ3列目【敵の初期Y位置】を定数kEnemyStartYに格納する
  /// </summary>
  static const int kEnemyStartY = 2;

  /// <summary>
  /// 敵の設定データ4列目【敵が動き始めるタイミング】を定数kEnemyStartMoveに格納する
  /// </summary>
  static const int kEnemyStartMove = 3;
}

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
BattleLevel::BattleLevel()
  : is_finish_(false)
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , field_(nullptr)
  , pipe_(nullptr)
  , player_(nullptr)
  , first_walking_enemys_{}
  , second_walking_enemys_{}
  , flying_enemys_{}
  , jumping_enemys_{}
  , game_mode_(nullptr)
  , start_ui_(nullptr)
  , pause_ui_(nullptr)
  , info_ui_(nullptr)
  , camera_(nullptr)
  , collision_(nullptr)
  , items_{}
  , end_type_(kUnloadTask)
  , gameover_handle_(0)
  , phase_type_(kPreparation)
  , gameover_fade_end_(false)
  , bgm_handle_(0)
  , gameover_sound_handle_(0)
  , fade_(0)
  , pre_field_phase_(Field::kFieldInitialized)
  , white_rectangle_handle_(0)
  , first_enter_sound_handle_(0)
  , second_enter_sound_handle_(0)
  , pre_player_status_(Player::kIdolRight)
  , player_hp_(kThree)
  , pre_player_hp_(0)
  , damage_wait_accumulation_time_(0.0f)
  , player_drop_accumulation_time_(0.0f)
  , first_enemy_drop_accumulation_times_{ 0.0f }
  , second_enemy_drop_accumulation_times_{ 0.0f }
  , flying_enemys_drop_accumulation_times_{ 0.0f }
  , clear_accumulation_time_(0.0f)
  , player_reduce_time_(0.0f)
  , is_hit_first_enemys_{ false }
  , is_hit_second_enemys_{ false }
  , is_hit_flying_enemys_{ false }
  , is_hit_jumping_enemys_{ false }
  , player_num_(0)
  , collision_type_(Collision::kCollisionNone)
  , stage_type_(kFirstStage)
  , enemy_item_type_(kFirstWalkingEnemy)
  , is_player_jump_this_frame_(false)
  , pre_player_jump_(false)
{
  DEBUG_PRINT(BattleLevelのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
BattleLevel::BattleLevel(TaskId task_id, TaskManager* task_manager)
  : Level(task_id, task_manager)
  , is_finish_(false)
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , field_(nullptr)
  , pipe_(nullptr)
  , player_(nullptr)
  , first_walking_enemys_{}
  , second_walking_enemys_{}
  , flying_enemys_{}
  , jumping_enemys_{}
  , game_mode_(nullptr)
  , start_ui_(nullptr)
  , pause_ui_(nullptr)
  , info_ui_(nullptr)
  , camera_(nullptr)
  , collision_(nullptr)
  , items_{}
  , end_type_(kUnloadTask)
  , gameover_handle_(0)
  , phase_type_(kPreparation)
  , gameover_fade_end_(false)
  , bgm_handle_(0)
  , gameover_sound_handle_(0)
  , fade_(0)
  , pre_field_phase_(Field::kFieldInitialized)
  , white_rectangle_handle_(0)
  , first_enter_sound_handle_(0)
  , second_enter_sound_handle_(0)
  , pre_player_status_(Player::kIdolRight)
  , player_hp_(kThree)
  , pre_player_hp_(0)
  , damage_wait_accumulation_time_(0.0f)
  , player_drop_accumulation_time_(0.0f)
  , first_enemy_drop_accumulation_times_{ 0.0f }
  , second_enemy_drop_accumulation_times_{ 0.0f }
  , flying_enemys_drop_accumulation_times_{ 0.0f }
  , clear_accumulation_time_(0.0f)
  , player_reduce_time_(0.0f)
  , is_hit_first_enemys_{ false }
  , is_hit_second_enemys_{ false }
  , is_hit_flying_enemys_{ false }
  , is_hit_jumping_enemys_{ false }
  , player_num_(0)
  , collision_type_(Collision::kCollisionNone)
  , stage_type_(kFirstStage)
  , enemy_item_type_(kFirstWalkingEnemy)
  , is_player_jump_this_frame_(false)
  , pre_player_jump_(false)
{
  DEBUG_PRINT(BattleLevelのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
BattleLevel::~BattleLevel() {
  DEBUG_PRINT(BattleLevelのデストラクタ);
}

/// <summary>
/// 各方向キーが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::OnPushDirectionKey() {
  DEBUG_PRINT(各方向キーが押された時のイベント);

}

/// <summary>
/// 決定ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::OnPushDecide() {
  DEBUG_PRINT(決定ボタンが押された時のイベント);
  //Enterが押された後の場合

  //is_finish_ = true;
}

/// <summary>
/// 終了ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::OnPushFinish() {
  //DEBUG_PRINT(終了ボタンが押された時のイベント);
  //SetEndButton();
  //is_finish_ = true;
}

/// <summary>
/// ポーズボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::OnPushPause() {
  DEBUG_PRINT(ポーズボタンが押された時のイベント);
  //プレイ中の場合
  if (phase_type_ == kProcessing) {

    //ポーズUIを表示中フェーズにする
    pause_ui_->SetPhaseType(PauseUi::kDisplay);

    //プレイ中断フェーズに変更する
    phase_type_ = kStop;

    //全ての動きを止める
    StopAll();

    //サウンドを止める
    audio_manager_->StopBgm(AudioManager::BgmKind::kBattleBgmMp3);
  }

  //プレイ中段中の場合
  else if (phase_type_ == kStop) {

    //ポーズUIを表示前フェーズにする
    pause_ui_->SetPhaseType(PauseUi::kPreDisplay);

    //プレイ中フェーズに変更する
    phase_type_ = kProcessing;

    //全ての動きを元に戻す
    SetPlayingAll();

    //BGMを再生する
    audio_manager_->PlayBgm(AudioManager::BgmKind::kBattleBgmMp3);
  }
}

/// <summary>
/// BackSpaceボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::OnPushBackSpace() {
  DEBUG_PRINT(BackSpaceボタンが押された時のイベント);
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool BattleLevel::InitializeUpdate(float time) {
  DEBUG_PRINT(BattleLevelの初期化処理);

  //ファイルマネージャーのインスタンスを取得
  FileManager* file_manager = FileManager::GetInstance();

  //設定のファイルを読み込む
  std::vector<int> setting = file_manager->ReadDataFromFile(kSettingCSV);
  std::vector<int> player_num = file_manager->ReadDataFromFile(kPlayerNumCSV);
  std::vector<int> stage_num = file_manager->ReadDataFromFile(kStageNumCSV);

  //現在のステージを設定する
  stage_type_ = static_cast<StageType>(stage_num.at(0));
  DEBUG_PRINT_VAR(stage_type_);

  //画像データをロードする
  ImageInfo battle_back_info;
  DEBUG_PRINT_VAR(stage_type_);
  if (stage_type_ == kSecondStage) {
    battle_back_info = LoadImage(kStageTwoBattleBackPng);
  }
  else {
    battle_back_info = LoadImage(kBattleBackPng);
  }
  ImageInfo key_info = LoadImage(kKeyInfoPng);
  ImageInfo black_info = LoadImage(kBlackPng);
  ImageInfo start_info = LoadImage(kStartPng);
  ImageInfo pause_info = LoadImage(kPausePng); 
  ImageInfo tube_rim_left_info = LoadImage(kTubeRimLeftPng);
  ImageInfo tube_rim_middle_info = LoadImage(kTubeRimMiddlePng);
  ImageInfo tube_rim_right_info = LoadImage(kTubeRimRightPng);
  ImageInfo tube_left_info = LoadImage(kTubeLeftPng);
  ImageInfo tube_middle_info = LoadImage(kTubeMiddlePng);
  ImageInfo tube_right_info = LoadImage(kTubeRightPng);
  ImageInfo ground_info = LoadImage(kGroundPng);
  ImageInfo box_info = LoadImage(kBoxPng);
  ImageInfo goal_info = LoadImage(kGoalPng);
  ImageInfo player_jump_info = LoadImage(kPlayerJumpPng);
  ImageInfo player_fall_info = LoadImage(kPlayerFallPng);
  ImageInfo hp_one_info = LoadImage(kHpOnePng);
  ImageInfo hp_two_info = LoadImage(kHpTwoPng);
  ImageInfo hp_three_info = LoadImage(kHpThreePng);
  ImageInfo hp_four_info = LoadImage(kHpFourPng);
  ImageInfo watch_info = LoadImage(kWatchPng);
  ImageInfo stage_clear_info = LoadImage(kStageClearPng);

  //アイテムゲット時のエフェクトの画像データをロードする
  std::array<int, kItemGetEffectX> items_get_handle;
  LoadDivGraph(kItemGetEffectPng, kItemGetEffectX, kItemGetEffectX, kCharacterY, kCharacterSize, kCharacterSize, &items_get_handle[0]);
  //1種類目の歩く敵の画像データをロードする
  std::array<int, kEnemyHitX> first_enemy_hit_handle;
  LoadDivGraph(kFirstWalkingEnemyHitPng, kEnemyHitX, kEnemyHitX, kCharacterY, kCharacterSize, kCharacterSize, &first_enemy_hit_handle[0]);
  std::array<int, kMushroomIdlingX> first_enemy_idling_handle;
  LoadDivGraph(kFirstWalkingEnemyIdlingPng, kMushroomIdlingX, kMushroomIdlingX, kCharacterY, kCharacterSize, kCharacterSize, &first_enemy_idling_handle[0]);
  std::array<int, kMushroomWalkingX> first_enemy_walking_handle;
  LoadDivGraph(kFirstWalkingEnemyRunPng, kMushroomWalkingX, kMushroomWalkingX, kCharacterY, kCharacterSize, kCharacterSize, &first_enemy_walking_handle[0]);
  //2種類目の歩く敵の画像データをロードする
  std::array<int, kEnemyHitX> second_enemy_hit_handle;
  LoadDivGraph(kSecondWalkingEnemyHitPng, kEnemyHitX, kEnemyHitX, kCharacterY, kSnailSizeX, kSnailSizeY, &second_enemy_hit_handle[0]);
  std::array<int, kSnailIdlingX> second_enemy_idling_handle;
  LoadDivGraph(kSecondWalkingEnemyIdlingPng, kSnailIdlingX, kSnailIdlingX, kCharacterY, kSnailSizeX, kSnailSizeY, &second_enemy_idling_handle[0]);
  std::array<int, kSnailWalkingX> second_enemy_walking_handle;
  LoadDivGraph(kSecondWalkingEnemyRunPng, kSnailWalkingX, kSnailWalkingX, kCharacterY, kSnailSizeX, kSnailSizeY, &second_enemy_walking_handle[0]);
  //飛ぶ敵の画像データをロードする
  std::array<int, kEnemyHitX> flying_enemys_hit_handle;
  LoadDivGraph(kFlyingEnemyHitPng, kFlyingEnemyHitX, kFlyingEnemyHitX, kCharacterY, kBatSizeX, kBatSizeY, &flying_enemys_hit_handle[0]);
  std::array<int, kFlyingEnemyFlyingX> flying_enemys_flying_handle;
  LoadDivGraph(kFlyingEnemyFlyingPng, kFlyingEnemyFlyingX, kFlyingEnemyFlyingX, kCharacterY, kBatSizeX, kBatSizeY, &flying_enemys_flying_handle[0]);

  //土管から出て来る敵の画像データをロードする
  std::array<int, kJumpingEnemyJumpingX> jump_enemy_jumping_handle;
  LoadDivGraph(kJumpingEnemyFallPng, kJumpingEnemyJumpingX, kJumpingEnemyJumpingX, kCharacterY, kStagSizeX, kStagSizeY, &jump_enemy_jumping_handle[0]);

  //プレイヤーの画像データをロードする
  std::array<int, kPlayerHitX> player_hit_handle;
  LoadDivGraph(kPlayerHitPng, kPlayerHitX, kPlayerHitX, kCharacterY, kPlayerSize, kPlayerSize, &player_hit_handle[0]);
  std::array<int, kPlayerIdlingX> player_idling_handle;
  LoadDivGraph(kPlayerIdlingPng, kPlayerIdlingX, kPlayerIdlingX, kCharacterY, kPlayerSize, kPlayerSize, &player_idling_handle[0]);
  std::array<int, kPlayerWalkingX> player_walking_handle;
  LoadDivGraph(kPlayerWalkingPng, kPlayerWalkingX, kPlayerWalkingX, kCharacterY, kPlayerSize, kPlayerSize, &player_walking_handle[0]);
  //パワーアップアイテムの画像データをロードする
  std::array<int, kWatermelonX> watermelon_handle;
  LoadDivGraph(kPowerUpItemPng, kWatermelonX, kWatermelonX, kCharacterY, kCharacterSize, kCharacterSize, &watermelon_handle[0]);
  //ダッシュ時のエフェクトの画像データをロードする
  std::array<int, kDashEffectX> dash_info;
  LoadDivGraph(kDashEffectPng, kDashEffectX, kDashEffectX, kCharacterY, kDashEffectSize, kDashEffectSize, &dash_info[0]);
  //ジャンプ時のエフェクトの画像データをロードする
  std::array<int, kJumpEffectX> jump_info;
  LoadDivGraph(kJumpEffectPng, kJumpEffectX, kJumpEffectX, kCharacterY, kJumpEffectSize, kJumpEffectSize, &jump_info[0]);
  //星が散るエフェクトの画像データをロードする
  std::array<int, kStarEffectX * kStarEffectY> star_info;
  LoadDivGraph(kStarEffectPng, (kStarEffectX * kStarEffectY), kStarEffectX, kStarEffectY, kStarSize, kStarSize, &star_info[0]);
  //星が流れるエフェクトの画像データをロードする
  std::array<int, kStarFlowEffectX * kStarFlowEffectY> star_flow_info;
  LoadDivGraph(kStarFlowEffectPng, (kStarFlowEffectX * kStarFlowEffectY), kStarFlowEffectX, kStarFlowEffectY, kStarFlowSizeX, kStarFlowSizeY, &star_flow_info[0]);
  //大きい星が流れるエフェクトの画像データをロードする
  std::array<int, kStarFlowEffectX* kStarFlowEffectY> big_star_flow_info;
  LoadDivGraph(kBigStarFlowEffectPng, (kStarFlowEffectX * kStarFlowEffectY), kStarFlowEffectX, kStarFlowEffectY, kBigStarFlowSizeX, kBigStarFlowSizeY, &big_star_flow_info[0]);
  //カウントダウンの画像データをロードする
  std::array<int, kElementNumber> countdown_info;
  LoadDivGraph(kCountdownPng, kElementNumber, kStarEffectX, kStarEffectY, kCountdownSizeX, kCountdownSizeY, &countdown_info[0]);
  //10秒前カウントダウンの画像データをロードする
  std::array<int, kElementNumber> ten_countdown_info;
  LoadDivGraph(kTenNumberPng, kElementNumber, kStarEffectX, kStarEffectY, kCountdownSizeX, kCountdownSizeY, &ten_countdown_info[0]);
  //タイムアップの画像データをロードする
  std::array<int, kTimeUpElementNumber> timeup_handle;
  LoadDivGraph(kTimeUpPng, kTimeUpElementNumber, kTimeUpX, kTimeUpY, kScreenSizeX, kScreenSizeY, &timeup_handle[0]);
  //プレイヤー数を表示する画像データをロードする
  std::array<int, kPlayerNumX> player_num_handle;
  LoadDivGraph(kPlayerNumPng, kPlayerNumX, kPlayerNumX, 1, kScreenSizeX, kScreenSizeY, &player_num_handle[0]);

  //ゲームクリアの画像データをロードする
  std::array<int, kElementNumber> game_clear_handle;
  LoadDivGraph(kGameClearPng, kElementNumber, 1, kElementNumber, kScreenSizeX, kScreenSizeY, &game_clear_handle[0]);

  //オーディオマネージャーを生成する
  audio_manager_ = new AudioManager();

  //効果音をロードする
  audio_manager_->LoadSe(AudioManager::SeKind::kHpUpMp3);
  audio_manager_->LoadSe(AudioManager::SeKind::kPlayerDeadMp3);
  audio_manager_->LoadSe(AudioManager::SeKind::kGameOverMp3);
  audio_manager_->LoadSe(AudioManager::SeKind::kStageClearMp3);
  audio_manager_->LoadSe(AudioManager::SeKind::kJumpMp3);
  audio_manager_->LoadSe(AudioManager::SeKind::kPlayerFalledMp3);
  audio_manager_->LoadSe(AudioManager::SeKind::kPlayerDamageMp3);
  audio_manager_->LoadSe(AudioManager::SeKind::kAttackEnemyMp3);
  audio_manager_->LoadSe(AudioManager::SeKind::kTimeUpMp3);
  //BGMをロードする
  audio_manager_->LoadBgm(AudioManager::BgmKind::kBattleBgmMp3);

  //フィールドのインスタンスを生成する
  field_ = new Field(Task::kField, task_manager_, stage_num.at(0));

  //土管のインスタンスを生成する
  pipe_ = new Pipe(Task::kPipe, task_manager_, stage_num.at(0));

  //ブロックのインスタンスを生成する
  player_ = new Player(Task::kPlayer, task_manager_);

  //スタートUIのインスタンスを生成する
  start_ui_ = new StartUi(Task::kStartUi);

  //ポーズUIのインスタンスを生成する
  pause_ui_ = new PauseUi(Task::kPauseUi, pause_info.handle);

  //情報UIのインスタンスを生成する
  info_ui_ = new InfoUi(Task::kInfoUi, countdown_info, ten_countdown_info, timeup_handle, star_flow_info, big_star_flow_info, player_num_handle, stage_num.at(0), game_clear_handle);

  //カメラのインスタンスを生成する
  camera_ = new Camera(Task::kCamera);

  //ゲームモードを生成する
  game_mode_ = new GameMode(Task::kGameMode);

  //バトル終了時のフェードを呼び出すクラスのインスタンスを生成する
  battle_fade_ = new BattleFade(Task::kBattleFade);

  ////衝突判定のインスタンスを作成する
  Collision::CreateInstance(stage_num.at(0));

  ////インスタンスを取得する
  Collision* collision = Collision::GetInstance();

  ////衝突判定を初期化する
  if (collision != nullptr) {
    collision->InitializeMapData();
  }

  //生成したインスタンスをタスクマネージャーに積む
  task_manager_->AddTask(field_);
  task_manager_->AddTask(pipe_);
  task_manager_->AddTask(player_);
  task_manager_->AddTask(pause_ui_);
  task_manager_->AddTask(start_ui_);
  task_manager_->AddTask(info_ui_);
  task_manager_->AddTask(camera_);
  task_manager_->AddTask(game_mode_);
  task_manager_->AddTask(battle_fade_);

  for (int j = 0; j < static_cast<int>(kThirdStage) + 1; j++) {
    if (stage_type_ == static_cast<StageType>(j)) {
      DEBUG_PRINT_VAR(j);
      
      //アイテムのインスタンスを生成する
      for (int i = 0; i < kItemNum; i++) {
        items_[i] = new Item(static_cast<TaskId>(static_cast<int>(TaskId::kItem) + i));
        //タスクマネージャーに積む
        task_manager_->AddTask(items_[i]);
        //グラフィックハンドルを設定する
        items_[i]->SetGrHandle(watermelon_handle);
        items_[i]->SetEffectGrHandle(items_get_handle);
      }
      for (int i = 0; i < kFirstWalkingEnemyNums[j]; i++) {
        TaskId first_task_id = static_cast<TaskId>(static_cast<int>(TaskId::kFirstWalkingEnemy) + i);
        //敵を生成する
        first_walking_enemys_[i] = new FirstWalkingEnemy(first_task_id, task_manager_);
        //敵の生成したインスタンスをタスクマネージャーに積む
        task_manager_->AddTask(first_walking_enemys_[i]);
        //敵の画像のグラフィックハンドルを設定する
        first_walking_enemys_[i]->SetIdlingGrHandle(first_enemy_idling_handle);
        first_walking_enemys_[i]->SetWalkingGrHandle(first_enemy_walking_handle);
        first_walking_enemys_[i]->SetHitGrHandle(first_enemy_hit_handle);
        //キノコの画像の幅と高さの半分を設定する
        first_walking_enemys_[i]->SetHalfWidth(kPlayerSize / kTwo);
        first_walking_enemys_[i]->SetHalfHeight(kPlayerSize / kTwo);
      }

      for (int i = 0; i < kSecondWalkingEnemyNums[j]; i++) {
        TaskId second_task_id = static_cast<TaskId>(static_cast<int>(TaskId::kSecondWalkingEnemy) + i);
        second_walking_enemys_[i] = new SecondWalkingEnemy(second_task_id, task_manager_);
        task_manager_->AddTask(second_walking_enemys_[i]);
        second_walking_enemys_[i]->SetIdlingGrHandle(second_enemy_idling_handle);
        second_walking_enemys_[i]->SetWalkingGrHandle(second_enemy_walking_handle);
        second_walking_enemys_[i]->SetHitGrHandle(second_enemy_hit_handle);

        //カタツムリの画像の幅と高さの半分を設定する
        second_walking_enemys_[i]->SetHalfWidth(kSnailSizeX / kTwo);
        second_walking_enemys_[i]->SetHalfHeight(kSnailSizeY / kTwo);
      }

      for (int i = 0; i < kFlyingEnemyNums[j]; i++) {
        TaskId fly_task_id = static_cast<TaskId>(static_cast<int>(TaskId::kFlyingEnemy) + i);
        flying_enemys_[i] = new FlyingEnemy(fly_task_id, task_manager_);
        task_manager_->AddTask(flying_enemys_[i]);
        flying_enemys_[i]->SetWalkingGrHandle(flying_enemys_flying_handle);
        flying_enemys_[i]->SetHitGrHandle(flying_enemys_hit_handle);

        //飛ぶ敵の画像の幅と高さの半分を設定する
        flying_enemys_[i]->SetHalfWidth(kBatSizeX / kTwo);
        flying_enemys_[i]->SetHalfHeight(kBatSizeY / kTwo);
      }

      for (int i = 0; i < kJumpingEnemyNums[j]; i++) {
        TaskId jump_task_id = static_cast<TaskId>(static_cast<int>(TaskId::kJumpingEnemy) + i);
        jumping_enemys_[i] = new JumpingEnemy(jump_task_id, task_manager_);
        task_manager_->AddTask(jumping_enemys_[i]);
        jumping_enemys_[i]->SetJumpingGrHandle(jump_enemy_jumping_handle);

        //下から出て来る敵の画像の幅と高さの半分を設定する
        jumping_enemys_[i]->SetHalfWidth(kStagSizeX / kTwo);
        jumping_enemys_[i]->SetHalfHeight(kStagSizeY / kTwo);
      }
      InitializeEnemyData(kFirstWalkingEnemyNums[j], kFirstWalkingEnemyCSVs[j], kFirstWalkingEnemy);
      InitializeEnemyData(kSecondWalkingEnemyNums[j], kSecondWalkingEnemyCSVs[j], kSecondWalkingEnemy);
      InitializeEnemyData(kJumpingEnemyNums[j], kJumpingEnemyCSVs[j], kJumpingEnemy);
      InitializeEnemyData(kFlyingEnemyNums[j], kFlyingEnemyCSVs[j], kFlyingEnemy);
      InitializeEnemyData(kItemNum, kItemCSVs[j], kItem);
    }
  }

  //ロードした画像データのグラフィックハンドルを渡す
  field_->SetBattleBackGrHandle(battle_back_info.handle);
  pipe_->SetTubeRimLeftGrHandle(tube_rim_left_info.handle);
  pipe_->SetTubeRimMiddleGrHandle(tube_rim_middle_info.handle);
  pipe_->SetTubeRimRightGrHandle(tube_rim_right_info.handle);
  pipe_->SetTubeLeftGrHandle(tube_left_info.handle);
  pipe_->SetTubeMiddleGrHandle(tube_middle_info.handle);
  pipe_->SetTubeRightGrHandle(tube_right_info.handle);
  field_->SetGroundGrHandle(ground_info.handle);
  field_->SetBoxGrHandle(box_info.handle);
  start_ui_->SetGrHandle(start_info.handle);
  pause_ui_->SetGrHandle(pause_info.handle);
  player_->SetIdlingGrHandle(player_idling_handle);
  player_->SetWalkingGrHandle(player_walking_handle);
  player_->SetHitGrHandle(player_hit_handle);
  player_->SetJumpGrHandle(player_jump_info.handle);
  player_->SetFallGrHandle(player_fall_info.handle);
  player_->SetDashEffectGrHandle(dash_info);
  player_->SetJumpEffectGrHandle(jump_info);
  player_->SetStarEffectGrHandle(star_info);
  info_ui_->SetHpOneGrHandle(hp_one_info.handle);
  info_ui_->SetHpTwoGrHandle(hp_two_info.handle);
  info_ui_->SetHpThreeGrHandle(hp_three_info.handle);
  info_ui_->SetHpFourGrHandle(hp_four_info.handle);
  info_ui_->SetWatchGrHandle(watch_info.handle);
  info_ui_->SetStageClearGrHandle(stage_clear_info.handle);

  //ロードした画像から取得した幅をスタートUI画像の幅に設定する
  start_ui_->SetWidth(start_info.size_x);
  //ロードした画像から取得した高さをスタートUI画像の幅に設定する
  start_ui_->SetHeight(start_info.size_y);

  //ロードした画像から取得した幅の半分のサイズを計算する
  float half_width = static_cast<float> (start_info.size_x) / kTwo;
  //ロードした画像から取得した高さの半分のサイズを計算する
  float half_height = static_cast<float> (start_info.size_y) / kTwo;

  //スタートUI画像の幅の半分を設定する
  start_ui_->SetHalfWidth(half_width);
  //スタートUI画像の高さの半分を設定する
  start_ui_->SetHalfHeight(half_height);

  //ロードした画像から取得した幅をポーズUI画像の幅に設定する
  pause_ui_->SetWidth(pause_info.size_x);
  //ロードした画像から取得した高さをポーズUI画像の幅に設定する
  pause_ui_->SetHeight(pause_info.size_y);

  //ロードした画像から取得した幅の半分のサイズを計算する
  half_width = static_cast<float> (pause_info.size_x) / kTwo;
  //ロードした画像から取得した高さの半分のサイズを計算する
  half_height = static_cast<float> (pause_info.size_y) / kTwo;

  //ポーズUI画像の幅の半分を設定する
  pause_ui_->SetHalfWidth(half_width);
  //ポーズUI画像の高さの半分を設定する
  pause_ui_->SetHalfHeight(half_height);

  //プレイヤーの画像の幅と高さの半分を設定する
  player_->SetHalfWidth(kPlayerSize/ kTwo);
  player_->SetHalfHeight(kPlayerSize / kTwo);

  //ゲーム情報のインスタンスを取得する
  GameInfo* game_info = GameInfo::GetInstance();

  //プレイヤーの残数を設定する
  player_num_ = player_num.at(0);

  //BGMを再生する
  audio_manager_->PlayBgm(AudioManager::BgmKind::kBattleBgmMp3);

  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name ="time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool BattleLevel::ProcessingUpdate(float time) {
  //DEBUG_PRINT(BattleLevelの毎フレーム更新処理のフェーズ処理);

  for (int j = 0; j < static_cast<int>(kThirdStage) + 1; j++) {
    if (stage_type_ == static_cast<StageType>(j)) {

      //Fieldクラスが処理中フェーズになった時から、Playerクラスを処理中フェーズにする
      Field::FieldPhaseType field_phase = field_->GetFieldPhaseType();
      StartUi::PhaseType start_phase = start_ui_->GetPhaseType();
      InfoUi::PhaseType info_phase = info_ui_->GetPhaseType();
      if (field_phase == Field::kProcessing && field_phase != pre_field_phase_) {
        pre_field_phase_ = Field::kProcessing;
        player_->SetPhaseType(Player::kPlaying);
        for (int i = 0; i < kFirstWalkingEnemyNums[j]; i++) {
          first_walking_enemys_[i]->SetPhaseType(FirstWalkingEnemy::kPlaying);
        }
        for (int i = 0; i < kSecondWalkingEnemyNums[j]; i++) {
          second_walking_enemys_[i]->SetPhaseType(SecondWalkingEnemy::kPlaying);
        }
        for (int i = 0; i < kFlyingEnemyNums[j]; i++) {
          flying_enemys_[i]->SetPhaseType(FlyingEnemy::kPlaying);
        }
        for (int i = 0; i < kJumpingEnemyNums[j]; i++) {
          jumping_enemys_[i]->SetPhaseType(JumpingEnemy::kPlaying);
        }
        for (int i = 0; i < kItemNum; i++) {
          items_[i]->SetPhaseType(Item::kPlaying);
        }
      }

      if (info_phase == InfoUi::kPlaying) {
        player_->SetCanMove(true);
      }
      else {
        player_->SetCanMove(false);
      }

      //入力管理を取得
      InputManager* input_manager = InputManager::GetInstance();

      //プレイヤーの現在の状態を取得する
      Player::PhaseType player_phase = player_->GetPhaseType();
      Player::StatusType player_status = player_->GetStatusType();

      //プレイヤーが落下状態でも落下時の演出が終わった状態でもないか判定する
      bool isnt_drop_and_finish_drop = player_->IsNotDropAndFinishDrop();

      //プレイヤーが下に落ちるアニメーションが終わった後、プレイヤー数を減らすフェーズに遷移する
      if (player_status == Player::StatusType::kFinishDrop && phase_type_ != kDecreasedPlayer && phase_type_ != kFadeIn) {
        player_reduce_time_ = player_reduce_time_ + time;
        if (player_reduce_time_ > kDamageLimitTime) {
          player_reduce_time_ = 0.0f;
          phase_type_ = kDecreasedPlayer;
        }
      }

      //タイムアップの場合
      bool timeup = info_ui_->GetTimeUpRenderEnd();
      if (timeup && player_status != Player::StatusType::kFinishDrop) {
        //BGMを止める
        audio_manager_->StopBgm(AudioManager::BgmKind::kBattleBgmMp3);
        player_hp_ = info_ui_->GetPlayerHp();
        if (player_hp_ >= 1) {
          //タイムアップの効果音を再生する
          audio_manager_->PlaySe(AudioManager::SeKind::kTimeUpMp3);
        }
        info_ui_->SetPlayerHp(0);
        StopEnemyAndCountdown();
        player_->SetPhaseType(Player::PhaseType::kStop);
        player_drop_accumulation_time_ = player_drop_accumulation_time_ + time;
        if (player_drop_accumulation_time_ >= kTimeUpLimitTime) {
          //プレイヤー死亡の効果音を再生する
          if (isnt_drop_and_finish_drop) {
            audio_manager_->PlaySe(AudioManager::SeKind::kPlayerDeadMp3);
          }
          player_->SetStatusType(Player::StatusType::kDrop);
          player_->SetPhaseType(Player::PhaseType::kPlaying);
        }
      }

      //プレイヤーがジャンプしているか判定する
      is_player_jump_this_frame_ = player_->IsPlayerJumping();
      //プレイヤーがジャンプし始めたフレームである場合
      if (is_player_jump_this_frame_ && (!pre_player_jump_)) {
        //プレイヤーのジャンプの効果音を再生する
        audio_manager_->PlaySe(AudioManager::SeKind::kJumpMp3);
      }

      //前回のプレイヤーの状態が左向きの場合、今回が右向きであればカメラにプレイヤーの向きが元に戻ったことを伝える
      if ((static_cast<int>(pre_player_status_) % kTwo) == 1) {
        if ((static_cast<int>(player_status) % kTwo) == 0) {
          camera_->SetPlayerTurned(false);
        }
      }
      //前回のプレイヤーの状態が右向きの場合、今回が左向きであればカメラにプレイヤーが逆行したことを伝える
      if ((static_cast<int>(pre_player_status_) % kTwo) == 0) {
        if ((static_cast<int>(player_status) % kTwo) == 1) {
          camera_->SetPlayerTurned(true);
        }
      }

      //プレイヤーの現在位置を取得する
      int x_pos = player_->GetXPosition();
      int y_pos = player_->GetYPosition();
      //カメラにプレイヤーのX位置をセットする
      camera_->SetPlayerXPos(x_pos);

      //描画X位置を調整するための整数を設定する
      if (player_status != Player::kDrop && player_status != Player::kFinishDrop) {
        int difference_x_pos = camera_->GetDifferenceXpos();
        player_->SetDifferenceXpos(difference_x_pos);
        field_->SetDifferenceXpos(difference_x_pos);
        pipe_->SetDifferenceXpos(difference_x_pos);
        for (int i = 0; i < kFirstWalkingEnemyNums[j]; i++) {
          first_walking_enemys_[i]->SetDifferenceXpos(difference_x_pos);
        }
        for (int i = 0; i < kSecondWalkingEnemyNums[j]; i++) {
          if (second_walking_enemys_[i] != nullptr) {
            second_walking_enemys_[i]->SetDifferenceXpos(difference_x_pos);
          } 
        }
        for (int i = 0; i < kFlyingEnemyNums[j]; i++) {
          flying_enemys_[i]->SetDifferenceXpos(difference_x_pos);
        }
        for (int i = 0; i < kJumpingEnemyNums[j]; i++) {
          jumping_enemys_[i]->SetDifferenceXpos(difference_x_pos);
        }
        for (int i = 0; i < kItemNum; i++) {
          items_[i]->SetDifferenceXpos(difference_x_pos);
        }
      }

      //プレイヤーが画面の下まで落ちた場合
      if ((y_pos > (kTotalRow) * kMapSize)) {
        //BGMを止める
        audio_manager_->StopBgm(AudioManager::BgmKind::kBattleBgmMp3);
        if (player_drop_accumulation_time_ == 0.0f) {
          audio_manager_->PlaySe(AudioManager::SeKind::kPlayerFalledMp3);
        }
        StopEnemyAndCountdown();
        player_->SetPhaseType(Player::PhaseType::kStop);
        player_drop_accumulation_time_ = player_drop_accumulation_time_ + time;
        if (player_drop_accumulation_time_ >= kPlayerHpZeroLimitTime) {
          //プレイヤー死亡の効果音を再生する
          if (isnt_drop_and_finish_drop) {
            audio_manager_->PlaySe(AudioManager::SeKind::kPlayerDeadMp3);
          }
          if (isnt_drop_and_finish_drop) {
            player_->SetStatusType(Player::StatusType::kDrop);
          }
          player_->SetPhaseType(Player::PhaseType::kPlaying);
        }
      }

      //衝突判定のインスタンスを取得する
      Collision* collision_ = Collision::GetInstance();

      //プレイヤーがゴールしたか確認する
      if (phase_type_ != kStageClear && isnt_drop_and_finish_drop && (y_pos > 0) && (y_pos < (kTotalRow)*kMapSize)) {
        bool player_goal = collision_->IsPlayerGoal(x_pos, y_pos, kPlayerSize);
        if (player_goal) {
          StopAll();
          clear_accumulation_time_ = clear_accumulation_time_ + time;
          if (clear_accumulation_time_ >= kLimitTime) {
            audio_manager_->PlaySe(AudioManager::SeKind::kStageClearMp3);
            phase_type_ = kStageClear;
            clear_accumulation_time_ = 0.0f;
          }
        }
      }

      //ステージクリアの場合
      if (phase_type_ == kStageClear) {
        InfoUi::PhaseType info_phase = info_ui_->GetPhaseType();
        if (info_phase != InfoUi::kStageClear) {
          //BGMを止める
          audio_manager_->StopBgm(AudioManager::BgmKind::kBattleBgmMp3);
          //ステージクリアの効果音を再生する
          audio_manager_->PlaySe(AudioManager::SeKind::kStageClearMp3);
        }
        //ファイルマネージャーのインスタンスを取得
        FileManager* file_manager = FileManager::GetInstance();
        //選択可能なステージのデータを読み込む
        std::vector<int> selectable_stages = file_manager->ReadDataFromFile(kSelectableStageCSV);
        info_ui_->SetPhaseType(InfoUi::kStageClear);
        //ゲームクリアの場合
        if (stage_type_ == kThirdStage) {
          SetGameClear(true);
          //ゲーム情報のインスタンスを取得する
          GameInfo* game_info = GameInfo::GetInstance();
          game_info->SetGameClear(true);
          //プレイヤーの数を最大に戻す
          std::vector<int> player_num;
          player_num.push_back(kThree);
          file_manager->WriteDataToFile(kPlayerNumCSV, player_num);
          //選択可能なステージ数を一時的に格納するvector
          std::vector<int> selectable_stages_num;
          selectable_stages_num.push_back(static_cast<int>(stage_type_) + 1);
          //次回起動時から全てのステージを選択できる様に選択可能なステージのデータを更新する
          file_manager->WriteDataToFile(kSelectableStageCSV, selectable_stages_num);
        }
        clear_accumulation_time_ = clear_accumulation_time_ + time;
        //一定時間経過後にフェードを表示する
        if (clear_accumulation_time_ >= kClearLimitTime) {
          battle_fade_->SetFade(true);
          bool is_fade_end = battle_fade_->GetFadeEnd();
          if (is_fade_end) {
            //ステージ数を一時的に格納するvector
            std::vector<int> stage_num;
            //ステージ3でなければ、ステージ数を増やす
            if (static_cast<int>(stage_type_) < kThirdStage) {
              stage_num.push_back(static_cast<int>(stage_type_) + 1);
              file_manager->WriteDataToFile(kStageNumCSV, stage_num);
              //新しいステージをクリアした時のみ、選択可能なステージのデータを更新する
              if (selectable_stages.at(0) < stage_num.at(0)) {
                file_manager->WriteDataToFile(kSelectableStageCSV, stage_num);
              }
            }
            is_finish_ = true;
          }
          clear_accumulation_time_ = 0.0f;
        }
      }

      //プレイヤーのX位置が特定の位置以上になったら、歩く敵が動き始める様に設定する
      for (int i = 0; i < kFirstWalkingEnemyNums[j]; i++) {
        int start_move_x = first_walking_enemys_[i]->GetStartMoveX();
        if (x_pos >= start_move_x) {
          first_walking_enemys_[i]->SetMove(true);
        }
      }
      for (int i = 0; i < kSecondWalkingEnemyNums[j]; i++) {
        int start_move_x = second_walking_enemys_[i]->GetStartMoveX();
        if (x_pos >= start_move_x) {
          second_walking_enemys_[i]->SetMove(true);
        }
      }

      //プレイヤーと敵の衝突判定
      for (int i = 0; i < kFirstWalkingEnemyNums[j]; i++) {
        //敵の現在位置を取得する
        int first_walking_enemys_x = first_walking_enemys_[i]->GetXPosition();
        int first_walking_enemys_y = first_walking_enemys_[i]->GetYPosition();

        //敵の状態を取得する
        FirstWalkingEnemy::StatusType first_status = first_walking_enemys_[i]->GetStatusType();

        //プレイヤーが敵とぶつかったかの有無を設定する
        if (first_status != FirstWalkingEnemy::StatusType::kDrop && isnt_drop_and_finish_drop) {
          is_hit_first_enemys_[i] = collision_->IsHitPlayerEnemy(x_pos, y_pos, kPlayerSize, first_walking_enemys_x, first_walking_enemys_y, kCharacterSize, kCharacterSize, static_cast<TaskId>(static_cast<int>(TaskId::kFirstWalkingEnemy) + i));
        }

        //敵とプレイヤーの衝突判定の状態を取得する
        collision_type_ = collision_->GetPlayerEnemyCollisionType();
        //敵を倒した場合
        if (collision_type_ == Collision::PlayerEnemyCollisionType::kAttackEnemy) {
          //1種類目の歩く敵を倒した場合
          if (is_hit_first_enemys_[i]) {
            if (first_status != FirstWalkingEnemy::StatusType::kHitRight && first_status != FirstWalkingEnemy::StatusType::kHitLeft) {
              //敵を倒した時の効果音を再生する
              audio_manager_->PlaySe(AudioManager::SeKind::kAttackEnemyMp3);
            }
            //敵をヒットの状態にする
            if (first_status == FirstWalkingEnemy::StatusType::kFallRight || first_status == FirstWalkingEnemy::StatusType::kIdolRight || first_status == FirstWalkingEnemy::StatusType::kWalkRight) {
              first_walking_enemys_[i]->SetStatusType(FirstWalkingEnemy::StatusType::kHitRight);
            }
            else if (first_status == FirstWalkingEnemy::StatusType::kFallLeft || first_status == FirstWalkingEnemy::StatusType::kIdolLeft || first_status == FirstWalkingEnemy::StatusType::kWalkLeft) {
              first_walking_enemys_[i]->SetStatusType(FirstWalkingEnemy::StatusType::kHitLeft);
            }
            //プレイヤーとカウントダウンを止める
            StopPlayerAndCountdown();
            first_enemy_drop_accumulation_times_[i] = first_enemy_drop_accumulation_times_[i] + time;
            //DEBUG_PRINT_VAR(first_enemy_drop_accumulation_times_[i]);
            if (first_enemy_drop_accumulation_times_[i] >= kHitLimitTime) {
              //一定時間経過すると敵が画面下に落ちる
              first_walking_enemys_[i]->SetStatusType(FirstWalkingEnemy::StatusType::kDrop);
              SetPlayerAndCountdown();
              first_enemy_drop_accumulation_times_[i] = 0.0f;
              collision_->SetPlayerEnemyCollisionType(Collision::PlayerEnemyCollisionType::kCollisionNone);
              is_hit_first_enemys_[i] = false;
              //DEBUG_PRINT_VAR(i);
            }
          }
        }
      }

      for (int i = 0; i < kSecondWalkingEnemyNums[j]; i++) {
        int second_walking_enemys_x = second_walking_enemys_[i]->GetXPosition();
        int second_walking_enemys_y = second_walking_enemys_[i]->GetYPosition();
        SecondWalkingEnemy::StatusType second_status = second_walking_enemys_[i]->GetStatusType();
        if (second_status != SecondWalkingEnemy::StatusType::kDrop && isnt_drop_and_finish_drop) {
          is_hit_second_enemys_[i] = collision_->IsHitPlayerEnemy(x_pos, y_pos, kPlayerSize, second_walking_enemys_x, second_walking_enemys_y, kSnailSizeX, kSnailSizeY, static_cast<TaskId>(static_cast<int>(TaskId::kSecondWalkingEnemy) + i));
        }

        //敵とプレイヤーの衝突判定の状態を取得する
        collision_type_ = collision_->GetPlayerEnemyCollisionType();
        //敵を倒した場合
        if (collision_type_ == Collision::PlayerEnemyCollisionType::kAttackEnemy) {
          //2種類目の歩く敵を倒した場合
          if (is_hit_second_enemys_[i]) {
            if (second_status != SecondWalkingEnemy::StatusType::kHitRight && second_status != SecondWalkingEnemy::StatusType::kHitLeft) {
              //敵を倒した時の効果音を再生する
              audio_manager_->PlaySe(AudioManager::SeKind::kAttackEnemyMp3);
            }
            //敵をヒットの状態にする
            if (second_status == SecondWalkingEnemy::StatusType::kFallRight || second_status == SecondWalkingEnemy::StatusType::kIdolRight || second_status == SecondWalkingEnemy::StatusType::kWalkRight) {
              second_walking_enemys_[i]->SetStatusType(SecondWalkingEnemy::StatusType::kHitRight);
            }
            else if (second_status == SecondWalkingEnemy::StatusType::kFallLeft || second_status == SecondWalkingEnemy::StatusType::kIdolLeft || second_status == SecondWalkingEnemy::StatusType::kWalkLeft) {
              second_walking_enemys_[i]->SetStatusType(SecondWalkingEnemy::StatusType::kHitLeft);
            }
            //プレイヤーとカウントダウンを止める
            StopPlayerAndCountdown();
            second_enemy_drop_accumulation_times_[i] = second_enemy_drop_accumulation_times_[i] + time;
            //DEBUG_PRINT_VAR(second_enemy_drop_accumulation_times_[i]);
            if (second_enemy_drop_accumulation_times_[i] >= kHitLimitTime) {
              //一定時間経過すると敵が画面下に落ちる
              second_walking_enemys_[i]->SetStatusType(SecondWalkingEnemy::StatusType::kDrop);
              SetPlayerAndCountdown();
              second_enemy_drop_accumulation_times_[i] = 0.0f;
              collision_->SetPlayerEnemyCollisionType(Collision::PlayerEnemyCollisionType::kCollisionNone);
              is_hit_second_enemys_[i] = false;
              //DEBUG_PRINT_VAR(i);
            }
          }
        }
      }
      for (int i = 0; i < kFlyingEnemyNums[j]; i++) {
        int flying_enemys_x = flying_enemys_[i]->GetXPosition();
        int flying_enemys_y = flying_enemys_[i]->GetYPosition();
        FlyingEnemy::StatusType flying_status = flying_enemys_[i]->GetStatusType();
        if (flying_status != FlyingEnemy::StatusType::kDrop && isnt_drop_and_finish_drop) {
          is_hit_flying_enemys_[i] = collision_->IsHitPlayerEnemy(x_pos, y_pos, kPlayerSize, flying_enemys_x, flying_enemys_y, kBatSizeX, kBatSizeY, static_cast<TaskId>(static_cast<int>(TaskId::kFlyingEnemy) + i));
        }
        //敵とプレイヤーの衝突判定の状態を取得する
        collision_type_ = collision_->GetPlayerEnemyCollisionType();
        //敵を倒した場合
        if (collision_type_ == Collision::PlayerEnemyCollisionType::kAttackEnemy) {
          //飛ぶ敵を倒した場合
          if (is_hit_flying_enemys_[i]) {
            if (flying_status != FlyingEnemy::StatusType::kHitRight && flying_status != FlyingEnemy::StatusType::kHitLeft) {
              //敵を倒した時の効果音を再生する
              audio_manager_->PlaySe(AudioManager::SeKind::kAttackEnemyMp3);
            }
            //敵をヒットの状態にする
            if (flying_status == FlyingEnemy::StatusType::kIdolRight || flying_status == FlyingEnemy::StatusType::kWalkRight) {
              flying_enemys_[i]->SetStatusType(FlyingEnemy::StatusType::kHitRight);
            }
            else if (flying_status == FlyingEnemy::StatusType::kIdolLeft || flying_status == FlyingEnemy::StatusType::kWalkLeft) {
              flying_enemys_[i]->SetStatusType(FlyingEnemy::StatusType::kHitLeft);
            }
            //プレイヤーとカウントダウンを止める
            StopPlayerAndCountdown();
            flying_enemys_drop_accumulation_times_[i] = flying_enemys_drop_accumulation_times_[i] + time;
            //DEBUG_PRINT_VAR(flying_enemys_drop_accumulation_times_[i]);
            if (flying_enemys_drop_accumulation_times_[i] >= kHitLimitTime) {
              //一定時間経過すると敵が画面下に落ちる
              flying_enemys_[i]->SetStatusType(FlyingEnemy::StatusType::kDrop);
              SetPlayerAndCountdown();
              flying_enemys_drop_accumulation_times_[i] = 0.0f;
              collision_->SetPlayerEnemyCollisionType(Collision::PlayerEnemyCollisionType::kCollisionNone);
              is_hit_flying_enemys_[i] = false;
              //DEBUG_PRINT_VAR(i);
            }
          }
        }
      }
      for (int i = 0; i < kJumpingEnemyNums[j]; i++) {
        int jumping_enemys_x = jumping_enemys_[i]->GetXPosition();
        int jumping_enemys_y = jumping_enemys_[i]->GetYPosition();
        JumpingEnemy::StatusType jumping_status = jumping_enemys_[i]->GetStatusType();

        //プレイヤーが土管の周りにいるか確認する
        bool is_player_tube = collision_->IsPlayerWithTube(x_pos, y_pos, kPlayerSize);
        jumping_enemys_[i]->SetPlayerWithTube(is_player_tube);

        if (jumping_status != JumpingEnemy::StatusType::kDrop) {
          is_hit_jumping_enemys_[i] = collision_->IsHitPlayerEnemy(x_pos, y_pos, kPlayerSize, jumping_enemys_x, jumping_enemys_y, kStagSizeX, kStagSizeY, static_cast<TaskId>(static_cast<int>(TaskId::kJumpingEnemy) + i));
        }
        //敵とプレイヤーの衝突判定の状態を取得する
        Collision::PlayerEnemyCollisionType collision_type = collision_->GetPlayerEnemyCollisionType();
      }

      //プレイヤーがダメージを受けた場合
      if (collision_type_ == Collision::PlayerEnemyCollisionType::kDamage) {
        //ヒットの状態にする
        if (player_status == Player::StatusType::kFallRight || player_status == Player::StatusType::kIdolRight || player_status == Player::StatusType::kJumpRight || player_status == Player::StatusType::kWalkRight) {
          player_->SetStatusType(Player::StatusType::kHitRight);
        }
        else if (player_status == Player::StatusType::kFallLeft || player_status == Player::StatusType::kIdolLeft || player_status == Player::StatusType::kJumpLeft || player_status == Player::StatusType::kWalkLeft) {
          player_->SetStatusType(Player::StatusType::kHitLeft);
        }
        //プレイヤーの現在のHPを取得し、1減らしてから新しく設定する
        player_hp_ = info_ui_->GetPlayerHp();
        //プレイヤーのHPが1だった場合、1減らすと0になるのでプレイヤー死亡の状態に入る
        if (player_hp_ <= 1 && player_status != Player::StatusType::kFinishDrop) {
          if (player_hp_ == 1) {
            //BGMを止める
            audio_manager_->StopBgm(AudioManager::BgmKind::kBattleBgmMp3);
            //プレイヤーがダメージを受けた効果音を再生する
            audio_manager_->PlaySe(AudioManager::SeKind::kPlayerDamageMp3);
          }
          info_ui_->SetPlayerHp(0);
          StopEnemyAndCountdown();
          player_drop_accumulation_time_ = player_drop_accumulation_time_ + time;
          if (player_drop_accumulation_time_ >= kPlayerHpZeroLimitTime) {
            //プレイヤー死亡の効果音を再生する
            audio_manager_->PlaySe(AudioManager::SeKind::kPlayerDeadMp3);
            player_drop_accumulation_time_ = 0.0f;
            player_->SetStatusType(Player::StatusType::kDrop);
          }
        }
        else if (player_hp_ > 1) {
          //プレイヤーがダメージを受けた効果音を再生する
          audio_manager_->PlaySe(AudioManager::SeKind::kPlayerDamageMp3);
          info_ui_->SetPlayerHp(player_hp_ - 1);
          //衝突判定をダメージを受けた後の待ち時間状態にする
          collision_->SetPlayerEnemyCollisionType(Collision::PlayerEnemyCollisionType::kDamageWait);
          //敵とカウントダウンを止める
          StopEnemyAndCountdown();
        }
      }
      else if (collision_type_ == Collision::PlayerEnemyCollisionType::kDamageWait) {
        damage_wait_accumulation_time_ = damage_wait_accumulation_time_ + time;
        if (damage_wait_accumulation_time_ >= kLimitTime) {
          //敵とカウントダウンを動く状態にし、プレイヤーを待機状態に戻す
          SetEnemyAndCountdown();
          if (player_status == Player::StatusType::kHitRight) {
            player_->SetStatusType(Player::StatusType::kIdolRight);
          }
          else if (player_status == Player::StatusType::kHitLeft) {
            player_->SetStatusType(Player::StatusType::kIdolLeft);
          }
        }
        //待ち時間が終わったら、衝突判定の状態を衝突していない状態に戻す
        if (damage_wait_accumulation_time_ >= kDamageLimitTime) {
          collision_->SetPlayerEnemyCollisionType(Collision::PlayerEnemyCollisionType::kCollisionNone);
          damage_wait_accumulation_time_ = 0.0f;
        }
      }

      //アイテムの現在位置を取得する
      for (int i = 0; i < kItemNum; i++) {
        int items_x = items_[i]->GetXPosition();
        int items_y = items_[i]->GetYPosition();

        //アイテムの現在の状態を取得する
        Item::StatusType status_type = items_[i]->GetStatusType();

        //アイテムとプレイヤーの衝突判定を取得する
        bool is_hit_item = collision_->IsHitPlayerItem(x_pos, y_pos, kPlayerSize, items_x, items_y, kCharacterSize, kCharacterSize, static_cast<TaskId>(static_cast<int>(TaskId::kItem) + i));

        if (is_hit_item && status_type == Item::kExist) {
          audio_manager_->PlaySe(AudioManager::SeKind::kHpUpMp3);
          //衝突していたら、アイテムを消す
          items_[i]->SetStatusType(Item::kEffect);
          //HPを1増やす
          player_hp_ = info_ui_->GetPlayerHp();
          info_ui_->SetPlayerHp(player_hp_ + 1);
        }
      }

      if (phase_type_ == kDecreasedPlayer) {
        collision_->SetPlayerEnemyCollisionType(Collision::PlayerEnemyCollisionType::kCollisionNone);
        damage_wait_accumulation_time_ = 0.0f;
        phase_type_ = kFadeIn;
      }

      //黒い画像フェードインフェーズの場合
      if (phase_type_ == kFadeIn) {
        battle_fade_->SetFade(true);
        bool is_fade_end = battle_fade_->GetFadeEnd();
        if (is_fade_end) {
          player_num_--;
          DEBUG_PRINT_VAR(player_num_);
          if (player_num_ > 0) {
            SetPlayerAlive(true);
            is_finish_ = true;
          }
          else if (player_num_ <= 0) {
            SetPlayerAlive(false);
            phase_type_ = kGameOver;
            player_num_ = kThree;
          }
          //ファイルマネージャーのインスタンスを取得
          FileManager* file_manager = FileManager::GetInstance();
          //プレイヤーの残機数を一時的に格納するvector
          std::vector<int> player_num;
          player_num.push_back(player_num_);
          file_manager->WriteDataToFile(kPlayerNumCSV, player_num);
        }
      }

      //ゲームオーバーフェーズの場合
      if (phase_type_ == kGameOver) {
        SetGameOver();
      }

      //準備中フェーズの場合
      if (phase_type_ == kPreparation) {
        //スタートUI表示フェーズに変更する
        phase_type_ = kStartUiDisplay;
      }
      //スタートUI表示フェーズの場合
      else if (phase_type_ == kStartUiDisplay) {
        //スタートUIを積む
        //task_manager_->AddTask(start_ui_);
        //スタートUI終了待機フェーズに変更する
        phase_type_ = kStartUiFinishWaiting;
      }
      //スタートUI待機フェーズの場合
      else if (phase_type_ == kStartUiFinishWaiting) {
        //プレイ中フェーズに変更する
        phase_type_ = kProcessing;
      }

      //フィニッシュUI表示フェーズの場合
      else if (phase_type_ == kFinishUiDisplay) {

      }
      //フィニッシュUI終了待機フェーズの場合
      else if (phase_type_ == kFinishUiFinishWaiting) {
        //バトル終了フェーズに遷移する
        phase_type_ = kBattleFinish;
      }
      //バトル終了フェーズの場合
      else if (phase_type_ == kBattleFinish) {
        //BattleLevelを終了できるようにする
        is_finish_ = true;
      }

      if (GetWindowUserCloseFlag()) {
        SetEndButton();
        //ファイルマネージャーのインスタンスを取得
        FileManager* file_manager = FileManager::GetInstance();
        //プレイヤーの数を最大に戻す
        std::vector<int> player_num;
        player_num.push_back(kThree);
        file_manager->WriteDataToFile(kPlayerNumCSV, player_num);
        accumulation_time_ = 0.0f;
        display_accumulation_time_ = 0.0f;
        damage_wait_accumulation_time_ = 0.0f;
        player_drop_accumulation_time_ = 0.0f;
        for (int i = 0; i < kFirstWalkingEnemyNums[j]; i++) {
          first_enemy_drop_accumulation_times_[i] = { 0.0f };
        }
        for (int i = 0; i < kSecondWalkingEnemyNums[j]; i++) {
          second_enemy_drop_accumulation_times_[i] = { 0.0f };
        }
        for (int i = 0; i < kFlyingEnemyNums[j]; i++) {
          flying_enemys_drop_accumulation_times_[i] = { 0.0f };
        }
        clear_accumulation_time_ = 0.0f;
        player_reduce_time_ = 0.0f;

        is_finish_ = true;
        DEBUG_PRINT(×ボタン);
      }

      //Enterが押されたら、決定ボタンが押された時のイベントを呼び出す
      if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kDecide)) {
        collision_->SetPlayerEnemyCollisionType(Collision::PlayerEnemyCollisionType::kCollisionNone);
        damage_wait_accumulation_time_ = 0.0f;
        OnPushDecide();
      }

      //ポーズボタンが押されたら、ポーズボタンが押された時のイベントを呼び出す
      if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kPause) && player_phase != Player::kPreraration && collision_type_ == Collision::PlayerEnemyCollisionType::kCollisionNone && isnt_drop_and_finish_drop && (y_pos < (kTotalRow)*kMapSize)) {
        OnPushPause();
      }

      if (field_phase == Field::kProcessing) {
        //同士の衝突を判定
        CheckIsHitPlayersBottom();
        CheckIsHitPlayersRight();
        CheckIsHitPlayersLeft();
      }

      pre_player_status_ = player_status;

    }
  }
  pre_player_hp_ = player_hp_;
  pre_player_jump_ = is_player_jump_this_frame_;

  return is_finish_;
}

/// <summary>
/// 毎フレームの描画処理
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::ProcessingRender() {
  //DEBUG_PRINT(BattleLevelの毎フレームの描画処理);
}

/// <summary>
/// 終了処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool BattleLevel::PhaseFinalize(float time) {
  DEBUG_PRINT(BattleLevelの終了処理);

  for (int j = 0; j < static_cast<int>(kThirdStage) + 1; j++) {
    if (stage_type_ == static_cast<StageType>(j)) {

      if (end_type_ == kUnloadTask) {
        DEBUG_PRINT(kUnloadTask);

        //描画をクリアする
        ClearDrawScreen();

        //画像のグラフィックハンドルを取得する
        //取得したグラフィックハンドルを使い、リソースを破棄する
        DeleteGraph(field_->GetBattleBackGrHandle());
        DeleteGraph(pipe_->GetTubeRimRightGrHandle());
        DeleteGraph(pipe_->GetTubeRimMiddleGrHandle());
        DeleteGraph(pipe_->GetTubeRimLeftGrHandle());
        DeleteGraph(pipe_->GetTubeRightGrHandle());
        DeleteGraph(pipe_->GetTubeMiddleGrHandle());
        DeleteGraph(pipe_->GetTubeLeftGrHandle());
        DeleteGraph(field_->GetGroundGrHandle());
        DeleteGraph(field_->GetBoxGrHandle());
        DeleteGraph(start_ui_->GetGrHandle());
        DeleteGraph(pause_ui_->GetGrHandle());
        for (int i = 0; i < kPlayerIdlingX; ++i) {
          DeleteGraph(player_->GetIdlingGrHandle(i));
        }
        for (int i = 0; i < kPlayerWalkingX; ++i) {
          DeleteGraph(player_->GetWalkingGrHandle(i));
        }
        for (int i = 0; i < kPlayerHitX; ++i) {
          DeleteGraph(player_->GetHitGrHandle(i));
        }
        DeleteGraph(player_->GetJumpGrHandle());
        DeleteGraph(player_->GetFallGrHandle());
        for (int k = 0; k < kJumpingEnemyNums[j]; k++) {
          for (int i = 0; i < kJumpingEnemyJumpingX; i++) {
            DeleteGraph(jumping_enemys_[k]->GetJumpingGrHandle(i));
          }
        }
        for (int k = 0; k < kFlyingEnemyNums[j]; k++) {
          for (int i = 0; i < kFlyingEnemyFlyingX; i++) {
            DeleteGraph(flying_enemys_[k]->GetWalkingGrHandle(i));
          }
          for (int i = 0; i < kFlyingEnemyHitX; i++) {
            DeleteGraph(flying_enemys_[k]->GetHitGrHandle(i));
          }
        }
        for (int k = 0; k < kSecondWalkingEnemyNums[j]; k++) {
          for (int i = 0; i < kSecondWalkingEnemyIdlingX; i++) {
            DeleteGraph(second_walking_enemys_[k]->GetIdlingGrHandle(i));
          }
          for (int i = 0; i < kSecondWalkingEnemyWalkingX; i++) {
            DeleteGraph(second_walking_enemys_[k]->GetWalkingGrHandle(i));
          }
          for (int i = 0; i < kSecondWalkingEnemyHitX; i++) {
            DeleteGraph(second_walking_enemys_[k]->GetHitGrHandle(i));
          }
        }
        for (int k = 0; k < kFirstWalkingEnemyNums[j]; k++) {
          for (int i = 0; i < kFirstWalkingEnemyIdlingX; i++) {
            DeleteGraph(first_walking_enemys_[k]->GetIdlingGrHandle(i));
          }
          for (int i = 0; i < kFirstWalkingEnemyWalkingX; i++) {
            DeleteGraph(first_walking_enemys_[k]->GetWalkingGrHandle(i));
          }
          for (int i = 0; i < kFirstWalkingEnemyHitX; i++) {
            DeleteGraph(first_walking_enemys_[k]->GetHitGrHandle(i));
          }
        }
        for (int i = 0; i < kDashEffectX; i++) {
          DeleteGraph(player_->GetDashEffectGrHandle(i));
        }
        for (int i = 0; i < kJumpEffectX; i++) {
          DeleteGraph(player_->GetJumpEffectGrHandle(i));
        }
        for (int i = 0; i < (kStarEffectX * kStarEffectY); i++) {
          DeleteGraph(player_->GetStarEffectGrHandle(i));
        }
        for (int i = 0; i < (kStarFlowEffectX * kStarFlowEffectY); i++) {
          DeleteGraph(info_ui_->GetStarFlowGrHandle(i));
        }
        for (int i = 0; i < (kStarFlowEffectX * kStarFlowEffectY); i++) {
          DeleteGraph(info_ui_->GetBigStarFlowGrHandle(i));
        }
        DeleteGraph(info_ui_->GetWatchGrHandle());
        DeleteGraph(info_ui_->GetHpOneGrHandle());
        DeleteGraph(info_ui_->GetHpTwoGrHandle());
        DeleteGraph(info_ui_->GetHpThreeGrHandle());
        DeleteGraph(info_ui_->GetHpFourGrHandle());
        DeleteGraph(info_ui_->GetStageClearGrHandle());
        for (int i = 0; i < kElementNumber; ++i) {
          DeleteGraph(info_ui_->GetGrHandle(i));
        }
        for (int i = 0; i < kTimeUpElementNumber; ++i) {
          DeleteGraph(info_ui_->GetTimeUpGrHandle(i));
        }
        for (int i = 0; i < kElementNumber; ++i) {
          DeleteGraph(info_ui_->GetTenGrHandle(i));
        }
        for (int i = 0; i < kElementNumber; ++i) {
          DeleteGraph(info_ui_->GetGameClearGrHandle(i));
        }
        for (int i = 0; i < kItemNum; i++) {
          DeleteGraph(items_[i]->GetGrHandle(i));
          DeleteGraph(items_[i]->GetEffectGrHandle(i));
        }
        for (int i = 0; i < kPlayerNumX; ++i) {
          DeleteGraph(info_ui_->GetPlayerNumGrHandle(i));
        }

        //敵クラスを解放する
        for (int i = 0; i < kJumpingEnemyNums[j]; i++) {
          Task* jumping_enemys_release_task = task_manager_->UnloadTask(static_cast<TaskId>(static_cast<int>(TaskId::kJumpingEnemy) + i));
        }
        for (int i = 0; i < kFlyingEnemyNums[j]; i++) {
          Task* flying_enemys_release_task = task_manager_->UnloadTask(static_cast<TaskId>(static_cast<int>(TaskId::kFlyingEnemy) + i));
        }
        for (int i = 0; i < kSecondWalkingEnemyNums[j]; i++) {
          Task* second_enemy_release_task = task_manager_->UnloadTask(static_cast<TaskId>(static_cast<int>(TaskId::kSecondWalkingEnemy) + i));
        }
        for (int i = 0; i < kFirstWalkingEnemyNums[j]; i++) {
          Task* first_enemy_release_task = task_manager_->UnloadTask(static_cast<TaskId>(static_cast<int>(TaskId::kFirstWalkingEnemy) + i));
        }

        //アイテムクラスを解放する
        for (int i = 0; i < kItemNum; i++) {
          Task* items_release_task = task_manager_->UnloadTask(static_cast<TaskId>(static_cast<int>(TaskId::kItem) + i));
          //delete items_release_task;
        }

        //タスクマネージャーに積んでいたタスクを解放するためにrelease_taskに格納する
        Task* battle_fade_release_task = task_manager_->UnloadTask(kBattleFade);
        Task* gamemode_release_task = task_manager_->UnloadTask(kGameMode);
        Task* camera_release_task = task_manager_->UnloadTask(kCamera);
        Task* infoui_release_task = task_manager_->UnloadTask(kInfoUi);
        Task* pause_release_task = task_manager_->UnloadTask(kPauseUi);
        Task* start_release_task = task_manager_->UnloadTask(kStartUi);
        Task* player_release_task = task_manager_->UnloadTask(kPlayer);
        Task* pipe_release_task = task_manager_->UnloadTask(kPipe);
        Task* field_release_task = task_manager_->UnloadTask(kField);

        //フェーズを破棄フェーズに変更する
        end_type_ = kDelete;
      }
      else if (end_type_ == kDelete) {
        DEBUG_PRINT(kDelete);

        //リソースを破棄する

        for (int i = 0; i < kJumpingEnemyNums[j]; i++) {
          delete jumping_enemys_[i];
          jumping_enemys_[i] = nullptr;
        }
        for (int i = 0; i < kFlyingEnemyNums[j]; i++) {
          delete flying_enemys_[i];
          flying_enemys_[i] = nullptr;
        }
        for (int i = 0; i < kSecondWalkingEnemyNums[j]; i++) {
          delete second_walking_enemys_[i];
          second_walking_enemys_[i] = nullptr;
        }
        for (int i = 0; i < kFirstWalkingEnemyNums[j]; i++) {
          delete first_walking_enemys_[i];
          first_walking_enemys_[i] = nullptr;
        }

        for (int i = 0; i < kItemNum; i++) {
          delete items_[i];
          items_[i] = nullptr;
        }

        //衝突判定のインスタンスを取得する
        Collision* collision = Collision::GetInstance();
        //衝突判定情報を解放する
        collision->ReleaseInstance();

        delete battle_fade_;
        battle_fade_ = nullptr;

        delete game_mode_;
        game_mode_ = nullptr;

        delete camera_;
        camera_ = nullptr;

        delete info_ui_;
        info_ui_ = nullptr;

        delete pause_ui_;
        pause_ui_ = nullptr;

        delete start_ui_;
        start_ui_ = nullptr;

        delete player_;
        player_ = nullptr;

        delete pipe_;
        pipe_ = nullptr;

        delete field_;
        field_ = nullptr;

        //オーディオマネージャーの後処理と破棄
        audio_manager_->FinAudioManager();
        delete audio_manager_;
        audio_manager_ = nullptr;

        return true;
      }
    }
  }
  return false;
}

/// <summary>
/// ゲームオーバーを設定する処理
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::SetGameOver() {
  //DEBUG_PRINT(ゲームオーバー);

  //ゲーム情報のインスタンスを取得する
  GameInfo* game_info = GameInfo::GetInstance();
  game_info->SetGameClear(false);

  //サウンドを再生する
  audio_manager_->PlaySe(AudioManager::SeKind::kGameOverMp3);
  //動画を再生する
  PlayMovie(kGameOverMp4, 1, DX_MOVIEPLAYTYPE_NORMAL);

  //フェードアウトでレベルを終了する
  FadeOut();
}

/// <summary>
/// UI終了のイベント
/// </summary>
/// <param name="task_id">終了するUIのタスクID</param>
/// <returns>なし</returns>
void BattleLevel::EndUi(TaskId task_id) {
  DEBUG_PRINT(UI終了のイベント);

  //引数のキャラのタスクを解放するためにtaskに格納する
  Task* task = task_manager_->UnloadTask(task_id);

  //release_taskのメモリを解放する
  delete task;

}

/// <summary>
/// LoadImage関数の定義
/// </summary>
/// <param = "filename">画像のファイル名</param>
/// <returns>ImageInfo構造体型のinfo</returns>
BattleLevel::ImageInfo BattleLevel::LoadImage(const char* filename) {
  BattleLevel::ImageInfo info;
  info.handle = LoadGraph(filename);
  GetGraphSize(info.handle, &info.size_x, &info.size_y);
  return info;
}

/// <summary>
/// StopAll関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::StopAll() {
  player_->SetPhaseType(Player::kStop);
  field_->SetFieldPhaseType(Field::kStop);
  for (int j = 0; j < static_cast<int>(kThirdStage) + 1; j++) {
    if (stage_type_ == static_cast<StageType>(j)) {
      for (int i = 0; i < kFirstWalkingEnemyNums[j]; i++) {
        first_walking_enemys_[i]->SetPhaseType(FirstWalkingEnemy::kStop);
      }
      for (int i = 0; i < kSecondWalkingEnemyNums[j]; i++) {
        second_walking_enemys_[i]->SetPhaseType(SecondWalkingEnemy::kStop);
      }
      for (int i = 0; i < kFlyingEnemyNums[j]; i++) {
        flying_enemys_[i]->SetPhaseType(FlyingEnemy::kStop);
      }
      for (int i = 0; i < kJumpingEnemyNums[j]; i++) {
        jumping_enemys_[i]->SetPhaseType(JumpingEnemy::kStop);
      }
    }
  }
  for (int i = 0; i < kItemNum; i++) {
    items_[i]->SetPhaseType(Item::kStop);
  }
  info_ui_->SetPhaseType(InfoUi::kStop);
}

/// <summary>
/// SetPlayingAll関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::SetPlayingAll() {
  player_->SetPhaseType(Player::kPlaying);
  field_->SetFieldPhaseType(Field::kProcessing);
  for (int j = 0; j < static_cast<int>(kThirdStage) + 1; j++) {
    if (stage_type_ == static_cast<StageType>(j)) {
      for (int i = 0; i < kFirstWalkingEnemyNums[j]; i++) {
        first_walking_enemys_[i]->SetPhaseType(FirstWalkingEnemy::kPlaying);
      }
      for (int i = 0; i < kSecondWalkingEnemyNums[j]; i++) {
        second_walking_enemys_[i]->SetPhaseType(SecondWalkingEnemy::kPlaying);
      }
      for (int i = 0; i < kFlyingEnemyNums[j]; i++) {
        flying_enemys_[i]->SetPhaseType(FlyingEnemy::kPlaying);
      }
      for (int i = 0; i < kJumpingEnemyNums[j]; i++) {
        jumping_enemys_[i]->SetPhaseType(JumpingEnemy::kPlaying);
      }
    }
  }
  for (int i = 0; i < kItemNum; i++) {
    items_[i]->SetPhaseType(Item::kPlaying);
  }
  info_ui_->SetPhaseType(InfoUi::kPlaying);
}

/// <summary>
/// StopEnemyAndCountdown関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::StopEnemyAndCountdown() {
  for (int j = 0; j < static_cast<int>(kThirdStage) + 1; j++) {
    if (stage_type_ == static_cast<StageType>(j)) {
      for (int i = 0; i < kFirstWalkingEnemyNums[j]; i++) {
        first_walking_enemys_[i]->SetPhaseType(FirstWalkingEnemy::kStop);
      }
      for (int i = 0; i < kSecondWalkingEnemyNums[j]; i++) {
        second_walking_enemys_[i]->SetPhaseType(SecondWalkingEnemy::kStop);
      }
      for (int i = 0; i < kFlyingEnemyNums[j]; i++) {
        flying_enemys_[i]->SetPhaseType(FlyingEnemy::kStop);
      }
      for (int i = 0; i < kJumpingEnemyNums[j]; i++) {
        jumping_enemys_[i]->SetPhaseType(JumpingEnemy::kStop);
      }
    }
  }
  for (int i = 0; i < kItemNum; i++) {
    items_[i]->SetPhaseType(Item::kStop);
  }
  info_ui_->SetPhaseType(InfoUi::kStop);
}

/// <summary>
/// SetEnemyAndCountdown関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::SetEnemyAndCountdown() {
  for (int j = 0; j < static_cast<int>(kThirdStage) + 1; j++) {
    if (stage_type_ == static_cast<StageType>(j)) {
      for (int i = 0; i < kFirstWalkingEnemyNums[j]; i++) {
        first_walking_enemys_[i]->SetPhaseType(FirstWalkingEnemy::kPlaying);
      }
      for (int i = 0; i < kSecondWalkingEnemyNums[j]; i++) {
        second_walking_enemys_[i]->SetPhaseType(SecondWalkingEnemy::kPlaying);
      }
      for (int i = 0; i < kFlyingEnemyNums[j]; i++) {
        flying_enemys_[i]->SetPhaseType(FlyingEnemy::kPlaying);
      }
      for (int i = 0; i < kJumpingEnemyNums[j]; i++) {
        jumping_enemys_[i]->SetPhaseType(JumpingEnemy::kPlaying);
      }
    }
  }
  for (int i = 0; i < kItemNum; i++) {
    items_[i]->SetPhaseType(Item::kPlaying);
  }
  info_ui_->SetPhaseType(InfoUi::kPlaying);
}

/// <summary>
/// StopPlayerAndCountdown関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::StopPlayerAndCountdown() {
  player_->SetPhaseType(Player::kStop);
  info_ui_->SetPhaseType(InfoUi::kStop);
}

/// <summary>
/// SetPlayerAndCountdown関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::SetPlayerAndCountdown() {
  player_->SetPhaseType(Player::kPlaying);
  info_ui_->SetPhaseType(InfoUi::kPlaying);
}

/// <summary>
/// フェードアウト表示する関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "handle">グラフィックハンドル</param>
/// <param = "is_transparent">透過の有無</param>
/// <returns>なし</returns>
void BattleLevel::FadeOut() {

  //DEBUG_PRINT(フェードアウト開始);

  //アルファ値を少しずつ変化させて表示する
  for (int alpha = 0; alpha <= kFadeValue; alpha += kPlusAlpha) {
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawBox(0, 0, kScreenSizeX, kScreenSizeY, Cr, TRUE);

    if (alpha >= kFadeValue) {
      is_finish_ = true;
    }

    //DEBUG_PRINT_VAR(alpha);

    //アルファ値の変化に待ち時間を設ける
    WaitTimer(kPlusAlpha);
  }

  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

/// <summary>
/// SetWhiteRectangleGrHandle関数の定義
/// </summary>
/// <param = "white_rectangle_handle">文字表示のグラフィックハンドル</param>
/// <returns>なし</returns>
void BattleLevel::SetWhiteRectangleGrHandle(int white_rectangle_handle) {
  white_rectangle_handle_ = white_rectangle_handle;
}

/// <summary>
/// GetWhiteRectangleGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>文字表示のグラフィックハンドル</returns>
int BattleLevel::GetWhiteRectangleGrHandle() {
  return white_rectangle_handle_;
}

/// <summary>
/// SetGameOverGrHandle関数の定義
/// </summary>
/// <param = "gameover_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void BattleLevel::SetGameOverGrHandle(int gameover_handle) {
  gameover_handle_ = gameover_handle;
}

/// <summary>
/// GetGameOverGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int BattleLevel::GetGameOverGrHandle() {
  return gameover_handle_;
}

/// <summary>
/// 下に移動する時に衝突したかを確認する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::CheckIsHitPlayersBottom() {

  //現在位置を取得する
  int x_coordinate = player_->GetXPosition();
  int y_coordinate = player_->GetYPosition();

}

/// <summary>
/// 右に移動する時に衝突したかを確認する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::CheckIsHitPlayersRight() {

  //現在位置を取得する
  int x_coordinate = player_->GetXPosition();
  int y_coordinate = player_->GetYPosition();
}

/// <summary>
/// 左に移動する時に衝突したかを確認する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::CheckIsHitPlayersLeft() {

  //現在位置を取得する
  int x_coordinate = player_->GetXPosition();
  int y_coordinate = player_->GetYPosition();

}

/// <summary>
/// InitializeEnemyData関数の定義
/// </summary>
/// <param>なし</param>
/// <returns></returns>
void BattleLevel::InitializeEnemyData(int enemy_num, const char* filename, EnemyItemType enemy_item_type) {
  //敵データを初期化するための一時的な二次元配列を用意する
  int cell[kMaxEnemyNum][kEnemyDataColumn] = {0};

  //ファイルのポインタを宣言する
  FILE* fp;

  //ファイルを開く
  if ((fopen_s(&fp, filename, "r")) != 0) {
    printf("ファイルを開けませんでした");
  }

  //文字を格納する変数
  int cha;
  //行と列の整数を格納する変数
  int row = 0;
  int width = 0;
  //文字列を格納する配列
  char buf[kBufElement];
  //bufを初期化する
  memset(buf, 0, sizeof(buf));
  //テキストファイルの末尾であるかを示す変数
  bool eof_flag = false;

  while (1) {
    while (1) {
      //ファイルを読み込む
      cha = fgetc(fp);
      //テキストファイルの末尾の場合、ループを2回抜けるためにeof_flagをtrueにする
      if (cha == EOF) {
        eof_flag = true;
        break;
      }
      //chaがカンマ区切りか改行でなければ、bufに連結する
      if (cha != ',' && cha != '\n') {
        strcat_s(buf, (const char*)&cha);
      }
      else {
        //bufをint型に変換し、cellの要素として代入する
        int num = atoi(buf);
        cell[row][width] = num;
        //bufを初期値に戻す
        memset(buf, 0, sizeof(buf));
        break;
      }
    }
    //テキストファイルの末尾の場合
    if (eof_flag) {
      break;
    }
    //カンマ区切りの場合
    if (cha == ',') {
      width++;
    }
    //改行の場合
    if (cha == '\n') {
      row++;
      width = 0;
    }
  }

  for (int i = 0; i < kMaxEnemyNum; i++) {
    int element_value = cell[i][kEnemyStartY];
    if (element_value != 0) {
      if (enemy_item_type == kFirstWalkingEnemy) {
        //CSVファイル上の敵のX位置データをi番目の敵のX位置に設定する
        first_walking_enemys_[i]->SetXPosition(cell[i][kEnemyStartX]);
        //CSVファイル上の敵のY位置データをi番目の敵のY位置に設定する
        first_walking_enemys_[i]->SetYPosition(cell[i][kEnemyStartY]);
        first_walking_enemys_[i]->SetStartMoveX(cell[i][kEnemyStartMove]);
      }
      if (enemy_item_type == kSecondWalkingEnemy) {
        //CSVファイル上の敵のX位置データをi番目の敵のX位置に設定する
        second_walking_enemys_[i]->SetXPosition(cell[i][kEnemyStartX]);
        //CSVファイル上の敵のY位置データをi番目の敵のY位置に設定する
        second_walking_enemys_[i]->SetYPosition(cell[i][kEnemyStartY]);
        second_walking_enemys_[i]->SetStartMoveX(cell[i][kEnemyStartMove]);
      }
      if (enemy_item_type == kFlyingEnemy) {
        //CSVファイル上の敵のX位置データをi番目の敵のX位置に設定する
        flying_enemys_[i]->SetXPosition(cell[i][kEnemyStartX]);
        //CSVファイル上の敵のY位置データをi番目の敵のY位置に設定する
        flying_enemys_[i]->SetYPosition(cell[i][kEnemyStartY]);
      }
      if (enemy_item_type == kJumpingEnemy) {
        //CSVファイル上の敵のX位置データをi番目の敵のX位置に設定する
        jumping_enemys_[i]->SetXPosition(cell[i][kEnemyStartX]);
        //CSVファイル上の敵のY位置データをi番目の敵のY位置に設定する
        jumping_enemys_[i]->SetYPosition(cell[i][kEnemyStartY]);
      }
      if (enemy_item_type == kItem) {
        //CSVファイル上の敵のX位置データをi番目の敵のX位置に設定する
        items_[i]->SetXPosition(cell[i][kEnemyStartX]);
        //CSVファイル上の敵のY位置データをi番目の敵のY位置に設定する
        items_[i]->SetYPosition(cell[i][kEnemyStartY]);
      }
      DEBUG_PRINT_VAR(i);
      //DEBUG_PRINT_VAR(cell[i][kEnemyStartX]);
      //DEBUG_PRINT_VAR(cell[i][kEnemyStartY]);
      //DEBUG_PRINT_VAR(cell[i][kEnemyStartMove]);
    }
  }
  DEBUG_PRINT(敵データを初期化した);
}

/// <summary>
/// IsPlayerDropThisFrame関数の定義
/// </summary>
/// <param name = "player_status">プレイヤーの現在の状態</param>
/// <returns>プレイヤーの状態がkDropになった瞬間であるかのフラグ</returns>
bool BattleLevel::IsPlayerDropThisFrame(Player::StatusType player_status) {
  if (player_status == Player::kDrop && pre_player_status_ != Player::kDrop) {
    return true;
  }
  return false;
}