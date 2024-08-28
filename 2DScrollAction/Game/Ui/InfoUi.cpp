#include <iostream>
#include "Game/Ui/InfoUi.h"
#include "Game/GameInfo/GameInfo.h"
#include "Game/GameMode/GameMode.h"
#include "System/LogConsole/LogConsole.h"
#include "Game/Fade/FadeManager.h"
#include "System/FileManager/FileManager.h"
#include <DxLib.h>
#include <string>

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// 制限時間を定数kLimitTimeに格納する
  /// </summary>
  static const int kLimitTime = 300;

  /// <summary>
  /// 表示する制限時間を定数kDisplayLimitTimeに格納する
  /// </summary>
  static const int kDisplayLimitTime = 300;

  /// <summary>
  /// 白色の値を取得
  /// </summary>
  unsigned int Cr = GetColor(255, 255, 255);

  /// <summary>
  /// 黒色の値を取得
  /// </summary>
  unsigned int BlackCr = GetColor(0, 0, 0);

  /// <summary>
  /// 箱の色の値を取得
  /// </summary>
  unsigned int BoxCr = GetColor(248, 255, 255);

  /// <summary>
  //時計の画像の表示開始X位置の定数kWatchX
  /// <summary>
  static const int kWatchX = 610;

  /// <summary>
  //時計の画像の表示開始Y位置の定数kWatchY
  /// <summary>
  static const int kWatchY = 2;

  /// <summary>
  //HPの画像の表示開始X位置の定数kHpX
  /// <summary>
  static const int kHpX = 10;

  /// <summary>
  //HPの画像の表示開始Y位置の定数kHpY
  /// <summary>
  static const int kHpY = 7;

  /// <summary>
  //カウントダウンの1の位の表示開始X位置の定数kCountdownX
  /// <summary>
  static const int kCountdownX = 740;

  /// <summary>
  //カウントダウンの1の位の表示開始Y位置の定数kCountdownY
  /// <summary>
  static const int kCountdownY = 1;

  /// <summary>
  //カウントダウンの10の位の表示開始X位置の定数kTenCountdownX
  /// <summary>
  static const int kTenCountdownX = 700;

  /// <summary>
  //カウントダウンの100の位の表示開始X位置の定数kHundredCountdownX
  /// <summary>
  static const int kHundredCountdownX = 660;

  /// <summary>
  /// リセット時間を定数kResetTimeに格納する
  /// </summary>
  static const float kResetTime = 4.0f;

  /// <summary>
  /// 累積時間の制限時間を定数kStopWaitTimeに格納する
  /// </summary>
  static const float kStopWaitTime = 1.0f;

  /// <summary>
  /// 待ち時間を定数kWaitTimeに格納する
  /// </summary>
  static const int kWaitTime = 100;

  /// <summary>
  /// 描画ブレンドモードのパラメータを定数kBlendValueに格納する
  /// </summary>
  static const int kBlendValue = 100;

  /// <summary>
  /// カウント10を表す定数kCountTen
  /// </summary>
  static const int kCountTen = 10;

  /// <summary>
  /// カウント5を表す定数kCountFive
  /// </summary>
  static const int kCountFive = 5;

  /// <summary>
  /// アルファ値に足しこむ値を定数kPlusAlphaに格納する
  /// </summary>
  static const int kPlusAlpha = 10;

  /// <summary>
  /// フェード値を定数kFadeValueに格納する
  /// </summary>
  static const int kFadeValue = 250;

  /// <summary>
  /// フェードイン時間
  /// </summary>
  const float kFadeInTime = 1.0f;

  /// <summary>
  /// 整数2を定数kTwoに格納する
  /// </summary>
  static const int kTwo = 2;

  /// <summary>
  /// 整数3を定数kThreeに格納する
  /// </summary>
  static const int kThree = 3;

  /// <summary>
  /// 整数4を定数kFourに格納する
  /// </summary>
  static const int kFour = 4;

  /// <summary>
  /// 星表示累積時間のリセット時間を定数kStarLimitTimeに格納する
  /// </summary>
  static const float kStarLimitTime = 1.2f;

  /// <summary>
  /// 星の画像表示の待ち時間を定数kStarWaitTimesに格納する
  /// </summary>
  static const float kStarWaitTimes[] = { 0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f };

  /// <summary>
  /// 大きい星表示の累積時間のリセット時間を定数kBigStarLimitTimeに格納する
  /// </summary>
  static const float kBigStarLimitTime = 2.4f;

  /// <summary>
  /// 大きい星の画像表示の待ち時間を定数kBigStarWaitTimesに格納する
  /// </summary>
  static const float kBigStarWaitTimes[] = { 0.0f, 0.2f, 0.4f, 0.6f, 0.8f, 1.0f, 1.2f, 1.4f, 1.6f, 1.8f, 2.0f, 2.2f, 2.4f };

  /// <summary>
  /// ゲームクリア画像表示の待ち時間を定数kGameClearWaitTimesに格納する
  /// </summary>
  static const float kGameClearWaitTimes[] = { 0.0f, 0.2f, 0.4f, 0.6f, 0.8f, 1.0f, 1.2f, 1.4f, 1.6f, 1.8f, 2.0f};

  /// <summary>
  //描画角度を定数の配列kPiに格納する
  /// <summary>
  static const double kPi = (3 * (3.141592654) / 2);

  /// <summary>
  //ステージクリア時の星の描画角度を定数の配列kPiに格納する
  /// <summary>
  static const double kStageClearPi = 3.141592654;

  /// <summary>
  /// HPが1から2になった時のエフェクトの表示X位置を定数kTwoEffectXに格納する
  /// </summary>
  static const int kTwoEffectX = 190;

  /// <summary>
  /// HPが2から3になった時のエフェクトの表示X位置を定数kThreeEffectXに格納する
  /// </summary>
  static const int kThreeEffectX = 260;

  /// <summary>
  /// HPが3から4になった時のエフェクトの表示X位置を定数kFourEffectXに格納する
  /// </summary>
  static const int kFourEffectX = 340;

  /// <summary>
  /// HPが上がった時の上側のエフェクトの表示Y位置を定数kEffectUpYに格納する
  /// </summary>
  static const int kEffectUpY = 14;

  /// <summary>
  /// HPが上がった時の下側のエフェクトの表示Y位置を定数kEffectDownYに格納する
  /// </summary>
  static const int kEffectDownY = 57;

  /// <summary>
  /// ステージクリア時の1つ目の流れる星のエフェクトの表示X位置を定数kFirstStarEffectXに格納する
  /// </summary>
  static const int kFirstStarEffectX = 120;

  /// <summary>
  /// ステージクリア時の2つ目の流れる星のエフェクトの表示X位置を定数kSecondStarEffectXに格納する
  /// </summary>
  static const int kSecondStarEffectX = 300;

  /// <summary>
  /// ステージクリア時の2つ目の流れる星のエフェクトの表示X位置を定数kThirdStarEffectXに格納する
  /// </summary>
  static const int kThirdStarEffectX = 500;

  /// <summary>
  /// ステージクリア時の2つ目の流れる星のエフェクトの表示X位置を定数kForthStarEffectXに格納する
  /// </summary>
  static const int kForthStarEffectX = 680;

  /// <summary>
  /// ステージクリア時の外側の流れる星のエフェクトの表示X位置を定数kOutsideStarEffectYに格納する
  /// </summary>
  static const int kOutsideStarEffectY = 100;

  /// <summary>
  /// ステージクリア時の内側の流れる星のエフェクトの表示X位置を定数kInsideStarEffectYに格納する
  /// </summary>
  static const int kInsideStarEffectY = 40;

  /// <summary>
  /// ステージクリア画像の表示X位置を定数kStageClearXに格納する
  /// </summary>
  static const int kStageClearX = 80;

  /// <summary>
  /// ステージクリア画像の表示X位置を定数kStageClearYに格納する
  /// </summary>
  static const int kStageClearY = 220;

  /// <summary>
  /// プレイヤーの残数を保存するファイル名を定数kPlayerNumCSVに格納する
  /// </summary>
  static const char* kPlayerNumCSV = "Assets/CsvFiles/player_num.csv";

  // <summary>
  //画面の幅を定数kScreenSizeXに格納する
  /// <summary>
  static const int kScreenSizeX = 800;

  // <summary>
  //画面の高さを定数kScreenSizeYに格納する
  /// <summary>
  static const int kScreenSizeY = 600;

  // <summary>
  //白い箱の高さを定数kWhiteBoxYに格納する
  /// <summary>
  static const int kWhiteBoxY = 80;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
InfoUi::InfoUi(TaskId task_id, std::array<int, kElementNumber> countdown_handle, std::array<int, kElementNumber> ten_countdown_handle, std::array<int, kTimeUpElementNumber> timeup_handle, std::array<int, kStarFlowEffectX* kStarFlowEffectY> star_effect_gr_handle, std::array<int, kStarFlowEffectX* kStarFlowEffectY> big_star_effect_gr_handle, std::array<int, kPlayerNumX> player_num_gr_handle, int stage_num, std::array<int, kElementNumber> game_clear_handle)
  : Task(task_id)
  , now_phase_(PhaseType::kPreraration)
  , countdown_gr_handle_(countdown_handle)
  , ten_countdown_gr_handle_(ten_countdown_handle)
  , timeup_gr_handle_(timeup_handle)
  , star_effect_gr_handle_(star_effect_gr_handle)
  , big_star_effect_gr_handle_(big_star_effect_gr_handle)
  , player_num_gr_handle_(player_num_gr_handle)
  , watch_gr_handle_(0)
  , hp_one_handle_(0)
  , hp_two_handle_(0)
  , hp_three_handle_(0)
  , hp_four_handle_(0)
  , stage_clear_handle_(0)
  , game_clear_handle_(game_clear_handle)
  , countdown_(kLimitTime)
  , accumulation_time_(0.0f)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , timeup_end_(false)
  , player_hp_(kThree)
  , pre_player_hp_(kThree)
  , timeup_accumulation_time_(0.0f)
  , star_accumulation_time_(0.0f)
  , game_clear_accumulation_time_(0.0f)
  , index_(0)
  , clear_index_(0)
  , star_effect_type(kEffectNone)
  , player_num_(kThree)
  , stage_num_(stage_num)
{
  DEBUG_PRINT(InfoUiのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
InfoUi::~InfoUi() {
  DEBUG_PRINT(InfoUiのデストラクタ);
}

/// <summary>
/// 毎フレーム更新処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>なし</returns>
void InfoUi::UpdateFrame(float time) {
  //DEBUG_PRINT(Playerの毎フレーム更新処理);
  //DEBUG_PRINT(InfoUiクラスのHP);
  //DEBUG_PRINT_VAR(timeup_accumulation_time_);
  if (now_phase_ != kStop) {

    switch (now_phase_) {
    //フェーズが準備中フェーズの場合
    case kPreraration: {
      //ファイルマネージャーのインスタンスを取得
      FileManager* file_manager = FileManager::GetInstance();
      //ファイルを読み込む
      std::vector<int> player_num = file_manager->ReadDataFromFile(kPlayerNumCSV);
      //プレイヤーの残数を設定する
      player_num_ = player_num.at(0);
      now_phase_ = kDisplayPlayerNum;
      break;
    }
    case kDisplayPlayerNum: {
      timeup_accumulation_time_ = timeup_accumulation_time_ + time;

      //累積時間が2秒以上だったら
      if (timeup_accumulation_time_ >= (kStopWaitTime * kTwo)) {
        //now_phase_ = kFade;
        now_phase_ = kPlaying;
        timeup_accumulation_time_ = 0.0f;
      }
      //DEBUG_PRINT(プレイ中フェーズに遷移);
      break;
    }
    case kFade: {
      break;
    }
    //フェーズがプレイ中フェーズの場合
    case kPlaying: {
      //前回の1Frameにかかった時間を累積時間に足す
      accumulation_time_ = accumulation_time_ + time;

      //累積時間が1秒以上だったら
      if (accumulation_time_ >= 1.0f) {
        //残り時間を-1する
        countdown_--;
        //累積時間をリセットする
        accumulation_time_ = 0.0f;

        //残り時間が0以下になったら
        if (countdown_ <= 0) {
          timeup_accumulation_time_ = timeup_accumulation_time_ + time;

          //タイムオーバーのイベント関数を呼ぶ
          //RenderTimeUp(time);
          if (timeup_end_) {
            //now_phase_ = kFinish;
            DEBUG_PRINT(終了フェーズに遷移);
          }
        }
      }

      //星表示用の累積時間を更新する
      if (star_effect_type == kHpTwo || star_effect_type == kHpThree || star_effect_type == kHpFour) {
        star_accumulation_time_ = star_accumulation_time_ + time;
        if (star_accumulation_time_ >= kStarLimitTime) {
          star_accumulation_time_ = 0.0f;
          star_effect_type = kEffectNone;
        }
      }

      //累積時間によって表示する星のアニメーションの要素を変更する
      for (int i = 0; i < ((kStarFlowEffectX * kStarFlowEffectY) + 1); i++) {
        if (star_accumulation_time_ >= kStarWaitTimes[i] && star_accumulation_time_ < kStarWaitTimes[i + 1]) {
          index_ = i;
          //DEBUG_PRINT_VAR(star_index_);
        }
      }

      break;
    }
    //フェーズがステージクリアフェーズの場合
    case kStageClear: {
      star_accumulation_time_ = star_accumulation_time_ + time;
      if (star_accumulation_time_ >= kBigStarLimitTime) {
        star_accumulation_time_ = 0.0f;
      }

      //累積時間によって表示する星のアニメーションの要素を変更する
      for (int i = 0; i < ((kStarFlowEffectX * kStarFlowEffectY) + 1); i++) {
        if (star_accumulation_time_ >= kBigStarWaitTimes[i] && star_accumulation_time_ < kBigStarWaitTimes[i + 1]) {
          index_ = i;
        }
      }

      if (stage_num_ == kTwo) {
        game_clear_accumulation_time_ = game_clear_accumulation_time_ + time;
        if (game_clear_accumulation_time_ >= kBigStarLimitTime) {
          game_clear_accumulation_time_ = 0.0f;
        }
      }
      //累積時間によって表示するゲームクリアのアニメーションの要素を変更する
      for (int i = 0; i < (kElementNumber + 1); i++) {
        if (game_clear_accumulation_time_ >= kGameClearWaitTimes[i] && game_clear_accumulation_time_ < kGameClearWaitTimes[i + 1]) {
          clear_index_ = i;
        }
      }

      break;
    }
    //フェーズが終了フェーズの場合
    case kFinish: {

      break;
    }
    }
  }
}

/// 毎フレーム描画処理
/// </remarks>
/// <param>なし</param>
/// <returns>なし</returns>
void InfoUi::RenderFrame() {
  //DEBUG_PRINT(InfoUiの毎フレーム描画処理);

    //ゲーム情報を取得する
    GameInfo* game_info = GameInfo::GetInstance();

    //位置を取得する
    int left_x = game_info->GetCenterX();
    int left_y = game_info->GetCenterY();
    int y_resolution = game_info->GetResolutionYSize();

    if (now_phase_ == kPreraration) {
      DrawBox(0, 0, kScreenSizeX, kScreenSizeY, BlackCr, TRUE);
    }

    if (now_phase_ == kDisplayPlayerNum) {
      int display_num = (stage_num_ * kThree) + player_num_;
      //DEBUG_PRINT_VAR(stage_num_);
      //DEBUG_PRINT_VAR(player_num_);
      //DEBUG_PRINT_VAR(display_num);
      DrawGraph(0, 0, player_num_gr_handle_[display_num - 1], true);
    }

    if (now_phase_ != kFinish && now_phase_ != kPreraration && now_phase_ != kDisplayPlayerNum) {
      if (countdown_ > 0) {
        //残り時間表示の周りに白いBoxを表示
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, kFadeValue / kTwo);
        DrawBox(kWatchX, 0, kScreenSizeX, kWhiteBoxY, BoxCr, true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
      }

      //カウントダウンから各桁の値を取得する
      int countdown_hundred_digit = (countdown_ / kCountTen / kCountTen) % kCountTen;
      int countdown_ten_digit = (countdown_ / kCountTen) % kCountTen;
      int countdown_one_digit = (countdown_ / 1) % kCountTen;

      //グラフィックハンドルの幅と高さを格納する変数を用意する
      int x_size = 0, y_size = 0;

      if (countdown_ > kCountTen && countdown_ <= kDisplayLimitTime) {
        //時計の画像を描画する
        DrawGraph(kWatchX, kWatchY, watch_gr_handle_, true);
        //カウントダウンを描画する
        GetGraphSize(countdown_gr_handle_[countdown_hundred_digit], &x_size, &y_size);
        DrawGraph(kHundredCountdownX, kCountdownY, countdown_gr_handle_[countdown_hundred_digit], true);
        GetGraphSize(countdown_gr_handle_[countdown_ten_digit], &x_size, &y_size);
        DrawGraph(kTenCountdownX, kCountdownY, countdown_gr_handle_[countdown_ten_digit], true);
        GetGraphSize(countdown_gr_handle_[countdown_one_digit], &x_size, &y_size);
        DrawGraph(kCountdownX, kCountdownY, countdown_gr_handle_[countdown_one_digit], true);
      }

      //カウントダウンが10以下になった場合
      if (countdown_ > 0 && countdown_ <= kCountTen) {
        //時計の画像を描画する
        DrawGraph(kWatchX, kWatchY, watch_gr_handle_, true);
        //カウントダウンを描画する
        GetGraphSize(countdown_gr_handle_[countdown_hundred_digit], &x_size, &y_size);
        DrawGraph(kHundredCountdownX, kCountdownY, ten_countdown_gr_handle_[countdown_hundred_digit], true);
        GetGraphSize(countdown_gr_handle_[countdown_ten_digit], &x_size, &y_size);
        DrawGraph(kTenCountdownX, kCountdownY, ten_countdown_gr_handle_[countdown_ten_digit], true);
        GetGraphSize(countdown_gr_handle_[countdown_one_digit], &x_size, &y_size);
        DrawGraph(kCountdownX, kCountdownY, ten_countdown_gr_handle_[countdown_one_digit], true);
      }

      //カウントが0になったら、タイムアップの画像を描画する
      if (countdown_ <= 0) {
        timeup_end_ = true;
        DrawGraph(0, 0, timeup_gr_handle_[kThree], TRUE);
      }

      //プレイヤーのHPを表示する
      if (player_hp_ == 1) {
        DrawGraph(kHpX, kHpY, hp_one_handle_, true);
      }
      if (player_hp_ == kTwo) {
        //前回フレームよりもHPが上がった場合、HPが増えたエフェクトを表示する
        if (player_hp_ > pre_player_hp_) {
          star_effect_type = kHpTwo;
        }
        DrawGraph(kHpX, kHpY, hp_two_handle_, true);
      }
      if (player_hp_ == kThree) {
        //前回フレームよりもHPが上がった場合、HPが増えたエフェクトを表示する
        if (player_hp_ > pre_player_hp_) {
          star_effect_type = kHpThree;
        }
        DrawGraph(kHpX, kHpY, hp_three_handle_, true);
      }
      if (player_hp_ == kFour) {
        //前回フレームよりもHPが上がった場合、HPが増えたエフェクトを表示する
        if (player_hp_ > pre_player_hp_) {
          star_effect_type = kHpFour;
        }
        DrawGraph(kHpX, kHpY, hp_four_handle_, true);
      }

      //HPが2に上がった状態の場合
      if (star_effect_type == kHpTwo) {
        DrawRotaGraph((kTwoEffectX + kStarFlowEffectX / kTwo), (kEffectUpY + kStarFlowEffectY / kTwo), 1.0f, kPi, star_effect_gr_handle_[index_], TRUE, TRUE);
        DrawRotaGraph((kTwoEffectX + kStarFlowEffectX / kTwo), (kEffectDownY + kStarFlowEffectY / kTwo), 1.0f, kPi, star_effect_gr_handle_[index_], TRUE, TRUE);
      }
      //HPが3に上がった状態の場合
      if (star_effect_type == kHpThree) {
        DrawRotaGraph((kThreeEffectX + kStarFlowEffectX / kTwo), (kEffectUpY + kStarFlowEffectY / kTwo), 1.0f, kPi, star_effect_gr_handle_[index_], TRUE, TRUE);
        DrawRotaGraph((kThreeEffectX + kStarFlowEffectX / kTwo), (kEffectDownY + kStarFlowEffectY / kTwo), 1.0f, kPi, star_effect_gr_handle_[index_], TRUE, TRUE);
      }
      //HPが4に上がった状態の場合
      if (star_effect_type == kHpFour) {
        DrawRotaGraph((kFourEffectX + kStarFlowEffectX / kTwo), (kEffectUpY + kStarFlowEffectY / kTwo), 1.0f, kPi, star_effect_gr_handle_[index_], TRUE, TRUE);
        DrawRotaGraph((kFourEffectX + kStarFlowEffectX / kTwo), (kEffectDownY + kStarFlowEffectY / kTwo), 1.0f, kPi, star_effect_gr_handle_[index_], TRUE, TRUE);
      }

      //ステージクリアの場合
      if (now_phase_ == kStageClear) {
        DrawRotaGraph((kFirstStarEffectX + kStarFlowEffectX / kTwo), (kOutsideStarEffectY + kStarFlowEffectY / kTwo), 1.0f, kStageClearPi, big_star_effect_gr_handle_[(kStarFlowEffectX * kStarFlowEffectY - 1) - (index_)], TRUE, TRUE);
        DrawRotaGraph((kSecondStarEffectX + kStarFlowEffectX / kTwo), (kInsideStarEffectY + kStarFlowEffectY / kTwo), 1.0f, kStageClearPi, big_star_effect_gr_handle_[(kStarFlowEffectX * kStarFlowEffectY - 1) - (index_)], TRUE, TRUE);
        DrawRotaGraph((kThirdStarEffectX + kStarFlowEffectX / kTwo), (kInsideStarEffectY + kStarFlowEffectY / kTwo), 1.0f, kStageClearPi, big_star_effect_gr_handle_[(kStarFlowEffectX * kStarFlowEffectY - 1) - (index_)], TRUE, TRUE);
        DrawRotaGraph((kForthStarEffectX + kStarFlowEffectX / kTwo), (kOutsideStarEffectY + kStarFlowEffectY / kTwo), 1.0f, kStageClearPi, big_star_effect_gr_handle_[(kStarFlowEffectX * kStarFlowEffectY - 1) - (index_)], TRUE, TRUE);
        if (stage_num_ == kTwo) {
          DrawGraph(0, 0, game_clear_handle_[clear_index_], true);
        }
        else{
          DrawGraph(kStageClearX, kStageClearY, stage_clear_handle_, true);
        }
        
      }

      //前回フレームのHPを更新する
      pre_player_hp_ = player_hp_;
    }
}

/// <summary>
/// GetGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int InfoUi::GetGrHandle(int element_num) {
  return countdown_gr_handle_[element_num];
}

/// <summary>
/// SetGrHandle関数の定義
/// </summary>
/// <param = "gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void InfoUi::SetGrHandle(int gr_handle) {
  //gr_handle_ = gr_handle;
}

/// <summary>
/// GetTenGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int InfoUi::GetTenGrHandle(int element_num) {
  return ten_countdown_gr_handle_[element_num];
}

/// <summary>
/// SetTenGrHandle関数の定義
/// </summary>
/// <param = "gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void InfoUi::SetTenGrHandle(int gr_handle) {
  //gr_handle_ = gr_handle;
}

/// <summary>
/// GetTimeUpGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int InfoUi::GetTimeUpGrHandle(int element_num) {
  return timeup_gr_handle_[element_num];
}

/// <summary>
/// SetCountdown関数の定義
/// </summary>
/// <param = "countdown">カウントダウンの値</param>
/// <returns>なし</returns>
void InfoUi::SetCountdown(int countdown) {
  countdown_ = countdown;
}

/// <summary>
/// SetWidth関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void InfoUi::SetWidth(int size_x) {
  width_ = size_x;
}

/// <summary>
/// GetWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int InfoUi::GetWidth() {
  return width_;
}

/// <summary>
/// SetHeight関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void InfoUi::SetHeight(int size_y) {
  height_ = size_y;
}

/// <summary>
/// GetHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さ</returns>
int InfoUi::GetHeight() {
  return height_;
}

/// <summary>
/// SetHalfWidth関数の定義
/// </summary>
/// <param>画像の幅の半分</param>
/// <returns>なし</returns>
void InfoUi::SetHalfWidth(float size_half_x) {
  half_width_ = size_half_x;
}

/// <summary>
/// GetHalfWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅の半分</returns>
float InfoUi::GetHalfWidth() {
  return half_width_;
}

/// <summary>
/// SetHalfHeight関数の定義
/// </summary>
/// <param>画像の高さの半分</param>
/// <returns>なし</returns>
void InfoUi::SetHalfHeight(float size_half_y) {
  half_height_ = size_half_y;
}

/// <summary>
/// GetHalfHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さの半分</returns>
float InfoUi::GetHalfHeight() {
  return half_height_;
}

/// タイムアップを描画する
/// </remarks>
/// <param>なし</param>
/// <returns>なし</returns>
void InfoUi::RenderTimeUp(float time) {
  //if (timeup_end_ == false) {

  //}

}

/// <summary>
/// GetTimeUpRenderEnd関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>タイムアップの描画が終わったかの有無</returns>
bool InfoUi::GetTimeUpRenderEnd() {
  if (timeup_end_ == true) {
    return true;
  }
  return false;
}

/// フェードイン表示する関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "handle">グラフィックハンドル</param>
/// <param = "is_transparent">透過の有無</param>
/// <returns>なし</returns>
void InfoUi::FadeIn(int x, int y, int handle, bool is_transparent, int fade_value) {

  DEBUG_PRINT(フェードイン開始);

  //アルファ値を少しずつ変化させて画像を表示する
  for (int alpha = 0; alpha <= fade_value; alpha += kPlusAlpha) {
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawGraph(x, y, handle, is_transparent);

    //アルファ値の変化に待ち時間を設ける
    WaitTimer(kWaitTime);
  }

  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

/// <summary>
/// GetWatchGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int InfoUi::GetWatchGrHandle() {
  return watch_gr_handle_;
}

/// <summary>
/// SetWatchGrHandle関数の定義
/// </summary>
/// <param = "watch_gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void InfoUi::SetWatchGrHandle(int watch_gr_handle) {
  watch_gr_handle_ = watch_gr_handle;
}

/// <summary>
/// GetHpOneGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>HP1の時の表示グラフィックハンドル</returns>
int InfoUi::GetHpOneGrHandle() {
  return hp_one_handle_;
}

/// <summary>
/// SetHpOneGrHandle関数の定義
/// </summary>
/// <param = "hp_one_handle">HP1の時の表示グラフィックハンドル</param>
/// <returns>なし</returns>
void InfoUi::SetHpOneGrHandle(int hp_one_handle) {
  hp_one_handle_ = hp_one_handle;
}

/// <summary>
/// GetHpTwoGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>HP2の時の表示グラフィックハンドル</returns>
int InfoUi::GetHpTwoGrHandle() {
  return hp_two_handle_;
}

/// <summary>
/// SetHpTwoGrHandle関数の定義
/// </summary>
/// <param = "hp_two_handle">HP2の時の表示グラフィックハンドル</param>
/// <returns>なし</returns>
void InfoUi::SetHpTwoGrHandle(int hp_two_handle) {
  hp_two_handle_ = hp_two_handle;
}

/// <summary>
/// GetHpThreeGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>HP3の時の表示グラフィックハンドル</returns>
int InfoUi::GetHpThreeGrHandle() {
  return hp_three_handle_;
}

/// <summary>
/// SetHpThreeGrHandle関数の定義
/// </summary>
/// <param = "hp_three_handle">HP3の時の表示グラフィックハンドル</param>
/// <returns>なし</returns>
void InfoUi::SetHpThreeGrHandle(int hp_three_handle) {
  hp_three_handle_ = hp_three_handle;
}

/// <summary>
/// GetHpFourGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>HP4の時の表示グラフィックハンドル</returns>
int InfoUi::GetHpFourGrHandle() {
  return hp_four_handle_;
}

/// <summary>
/// SetHpFourGrHandle関数の定義
/// </summary>
/// <param = "hp_four_handle">HP4の時の表示グラフィックハンドル</param>
/// <returns>なし</returns>
void InfoUi::SetHpFourGrHandle(int hp_four_handle) {
  hp_four_handle_ = hp_four_handle;
}

/// <summary>
/// SetPlayerHp関数の定義
/// </summary>
/// <param = "player_hp">プレイヤーのHP</param>
/// <returns>なし</returns>
void InfoUi::SetPlayerHp(int player_hp) {
  player_hp_ = player_hp;
}

/// <summary>
/// GetPlayerHp関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>プレイヤーのHP</returns>
int InfoUi::GetPlayerHp() {
  return player_hp_;
}

/// <summary>
/// SetPhaseType関数の定義
/// </summary>
/// <param = "now_phase">グラフィックハンドル</param>
/// <returns>なし</returns>
void InfoUi::SetPhaseType(PhaseType now_phase) {
  now_phase_ = now_phase;
}

/// <summary>
/// GetPhaseType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
InfoUi::PhaseType InfoUi::GetPhaseType() {
  return now_phase_;
}

/// <summary>
/// GetStarFlowGrHandle関数の定義
/// </summary>
/// <param = "element_num">要素番号</param>
/// <returns>星が流れるエフェクトのグラフィックハンドル</returns>
int InfoUi::GetStarFlowGrHandle(int element_num) {
  return star_effect_gr_handle_[element_num];
}

/// <summary>
/// GetBigStarFlowGrHandle関数の定義
/// </summary>
/// <param = "element_num">要素番号</param>
/// <returns>星が流れるエフェクトのグラフィックハンドル</returns>
int InfoUi::GetBigStarFlowGrHandle(int element_num) {
  return big_star_effect_gr_handle_[element_num];
}

/// <summary>
/// GetStageClearGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ステージクリア画像のグラフィックハンドル</returns>
int InfoUi::GetStageClearGrHandle() {
  return stage_clear_handle_;
}

/// <summary>
/// SetStageClearGrHandle関数の定義
/// </summary>
/// <param = "stage_clear_handle">ステージクリア画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void InfoUi::SetStageClearGrHandle(int stage_clear_handle) {
  stage_clear_handle_ = stage_clear_handle;
}

/// <summary>
/// GetPlayerNumGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ステージとプレイヤー数を表示する画像のグラフィックハンドル</returns>
int InfoUi::GetPlayerNumGrHandle(int element_num) {
  return player_num_gr_handle_[element_num];
}

/// <summary>
/// GetGameClearGrHandle関数の定義
/// </summary>
/// <param = "element_num">要素番号</param>
/// <returns>ゲームクリアのグラフィックハンドル</returns>
int InfoUi::GetGameClearGrHandle(int element_num) {
  return game_clear_handle_[element_num];
}