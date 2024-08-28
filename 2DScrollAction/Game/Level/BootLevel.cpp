#include <iostream>
#include "DxLib.h"
#include "Game/Level/BootLevel.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// 次の画面に遷移するまでの時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 2.0f;

  /// <summary>
  /// 「Boot」から「Boot.」に文字表示を切り替えるタイミングを定数kFirstBootDrawに格納する
  /// </summary>
  static const float kFirstBootDraw = 0.25f;

  /// <summary>
  /// 「Boot.」から「Boot..」に文字表示を切り替えるタイミングを定数kSecondBootDrawに格納する
  /// </summary>
  static const float kSecondBootDraw = 0.5f;

  /// <summary>
  /// 「Boot..」から「Boot...」に文字表示を切り替えるタイミングを定数kThirdBootDrawに格納する
  /// </summary>
  static const float kThirdBootDraw = 0.75f;

  /// <summary>
  /// 「Boot...」から「Boot」に戻すタイミングを定数kLastBootDrawに格納する
  /// </summary>
  static const float kLastBootDraw = 1.00f;

  /// <summary>
  //白色の値を取得
  /// <summary>
  unsigned int Cr = GetColor(255, 255, 255);

  /// <summary>
  //DrawString関数のX座標を定数kXcoordinateに格納する
  /// <summary>
  static const int kXcoordinate = 480;

  /// <summary>
  //DrawString関数のY座標を定数kYcoordinateに格納する
  /// <summary>
  static const int kYcoordinate = 470;

  /// <summary>
  //フォントサイズを定数kFontSizeに格納するFontThickness
  /// <summary>
  static const int kFontSize = 27;

  /// <summary>
  //フォントの太さを定数kFontThicknessに格納する
  /// <summary>
  static const int kFontThickness = 8;

  /// <summary>
  //星の描画位置を少しずらすための調整する値を定数kFineControlに格納する
  /// <summary>
  static const int kFineControl = 50;

  /// <summary>
  //星の描画位置を大きくずらすための調整する値を定数kBigControlに格納する
  /// <summary>
  static const int kBigControl = 220;
}

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
BootLevel::BootLevel()
  : is_finish_(false)
  , accumulation_time_(0.0f)
  , boot_display_count_(0)
  , end_type_(kUnloadTask)
{
  DEBUG_PRINT(BootLevelのデフォルトコンストラクタ);
}

/// <summary>
/// コンスラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
BootLevel::BootLevel(TaskId task_id, TaskManager* task_manager)
  : Level(task_id, task_manager)
  , is_finish_(false)
  , accumulation_time_(0.0f)
  , boot_display_count_(0)
  , end_type_(kUnloadTask)
{
  DEBUG_PRINT(BootLevelのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
BootLevel::~BootLevel() {
  DEBUG_PRINT(BootLevelのデストラクタ);
  //accumulation_time_ = 0.0f;
}

/// <summary>
/// 決定ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BootLevel::OnPushDecide() {
  DEBUG_PRINT(決定ボタンが押された時のイベント);
  //is_finish_ = true;
}

/// <summary>
/// 終了ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BootLevel::OnPushFinish() {
  //DEBUG_PRINT(終了ボタンが押された時のイベント);
  //SetEndButton();
  //is_finish_ = true;
}

/// <summary>
/// スペースボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BootLevel::OnPushPause() {
  DEBUG_PRINT(スペースボタンが押された時のイベント);
}

/// <summary>
/// BackSpaceボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BootLevel::OnPushBackSpace() {
  DEBUG_PRINT(BackSpaceボタンが押された時のイベント);
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool BootLevel::InitializeUpdate(float time) {
  DEBUG_PRINT(BootLevelの初期化処理);

  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool BootLevel::ProcessingUpdate(float time) {
  //DEBUG_PRINT(BootLevelの毎フレーム更新処理のフェーズ処理);
  accumulation_time_ = accumulation_time_ + time;
  boot_display_count_ = boot_display_count_ + time;

  if (GetWindowUserCloseFlag()) {
    SetEndButton();
    is_finish_ = true;
    DEBUG_PRINT(×ボタン);
  }
  else if (accumulation_time_ >= kLimitTime) {
    DEBUG_PRINT(1秒経った);
    is_finish_ = true;
  }

  //描画処理を実行する
  ProcessingRender();

  return is_finish_;
}

/// <summary>
/// 毎フレームの描画処理
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BootLevel::ProcessingRender() {
  //DEBUG_PRINT(BootLevelの毎フレームの描画処理);

  //サイズ変更
  SetFontSize(kFontSize);
  //太さを変更
  SetFontThickness(kFontThickness);
  //種類をMS明朝に変更
  ChangeFont("ＭＳ 明朝");
  //アンチエイリアスフォントに変更
  ChangeFontType(DX_FONTTYPE_ANTIALIASING);

  //0.25f、0.5f、0.75fのタイミングで文字の表示を切り替える
   if (boot_display_count_ < kFirstBootDraw) {
     DrawString(kXcoordinate - kFineControl, kYcoordinate - kFineControl, "★", Cr);
     DrawString(kXcoordinate, kYcoordinate, "NowLoading", Cr);
  }
    else if (boot_display_count_ >= kFirstBootDraw && boot_display_count_ < kSecondBootDraw) {
     //前の描画をクリアする
     ClearDrawScreen();
     DrawString(kXcoordinate + kBigControl, kYcoordinate - kFineControl, "★", Cr);
     DrawString(kXcoordinate, kYcoordinate, "NowLoading.", Cr);
  }
    else if (boot_display_count_ >= kSecondBootDraw && boot_display_count_ < kThirdBootDraw) {
     //前の描画をクリアする
     ClearDrawScreen();
     DrawString(kXcoordinate + kBigControl, kYcoordinate + kFineControl, "★", Cr);
     DrawString(kXcoordinate, kYcoordinate, "NowLoading..", Cr);
  }
    else if (boot_display_count_ >= kThirdBootDraw && boot_display_count_ < kLastBootDraw) {
     //前の描画をクリアする
     ClearDrawScreen();
     DrawString(kXcoordinate - kFineControl, kYcoordinate + kFineControl, "★", Cr);
     DrawString(kXcoordinate, kYcoordinate, "NowLoading...", Cr);
  }
    else if (boot_display_count_ >= kLastBootDraw) {
     //前の描画をクリアする
     ClearDrawScreen();
     boot_display_count_ = 0;
   }
}

/// <summary>
/// 終了処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool BootLevel::PhaseFinalize(float time) {
  DEBUG_PRINT(BootLevelの終了処理);

  //描画をクリアする
  ClearDrawScreen();

  if (end_type_ == kUnloadTask) {


    //フェーズを破棄フェーズに変更する
    end_type_ = kDelete;
  }
  else if (end_type_ == kDelete) {

  }
  return true;
}