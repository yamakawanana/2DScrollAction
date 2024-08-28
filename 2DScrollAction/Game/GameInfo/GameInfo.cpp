#include <iostream>
#include "Game/GameInfo/GameInfo.h"

//ゲーム情報インスタンスの初期化
GameInfo* GameInfo::game_info_ = nullptr;

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  // <summary>
  //画面の幅を定数kScreenSizeXに格納する
  /// <summary>
  static const int kScreenSizeX = 800;

  // <summary>
  //画面の高さを定数kScreenSizeYに格納する
  /// <summary>
  static const int kScreenSizeY = 600;
}


/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
GameInfo::GameInfo()
  : resolution_x_size_(0)
  , resolution_y_size_(0)
  , center_x_(0)
  , center_y_(0)
  , map_x_size_(0)
  , map_y_size_(0)
  , map_left_x_(0)
  , map_left_y_(0)
  , game_clear_(false)
{
  DEBUG_PRINT(GameInfoのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
GameInfo::~GameInfo() {
  DEBUG_PRINT(GameInfoのデストラクタ);
}

/// <summary>
/// インスタンスを生成する
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void GameInfo::CreateInstance() {
  //まだインスタンスが生成されていなければ、インスタンスを生成する
  if (game_info_ == nullptr) {
    game_info_ = new GameInfo();
  }
}

/// <summary>
/// インスタンスを取得する
/// </summary>
/// <param>なし</param>
/// <returns>ゲーム情報のインスタンス</returns>
GameInfo* GameInfo::GetInstance() {
  return game_info_;
}

/// <summary>
/// インスタンスを解放する
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void GameInfo::ReleaseInstance() {
  if (game_info_ != nullptr) {
    delete game_info_;
    game_info_ = nullptr;
  }
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void GameInfo::InitGameInfo() {
  DEBUG_PRINT(GameInfoクラスの初期化処理);
  //解像度を設定する
  resolution_x_size_ = kScreenSizeX;
  resolution_y_size_ = kScreenSizeY;

  //画面の中心点の座標を設定する
  center_x_ = resolution_x_size_ / 2;
  center_y_ = resolution_y_size_ / 2;
}

/// <summary>
/// GetResolutionXSize関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>解像度のXサイズ</returns>
int GameInfo::GetResolutionXSize() {
  return resolution_x_size_;
}

/// <summary>
/// GetResolutionYSize関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>解像度のYサイズ</returns>
int GameInfo::GetResolutionYSize() {
  return resolution_y_size_;
}

/// <summary>
/// GetCenterX関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>画面の中心のX座標</returns>
int GameInfo::GetCenterX() {
  return center_x_;
}

/// <summary>
/// GetCenterY関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>画面の中心のY座標</returns>
int GameInfo::GetCenterY() {
  return center_y_;
}

/// <summary>
/// SetMapSize関数の宣言
/// </summary>
/// <param>mapのXサイズ、Yサイズ</param>
/// <returns>なし</returns>
void GameInfo::SetMapSize(int x, int y) {
  map_x_size_ = x;
  map_y_size_ = y;
  DEBUG_PRINT_VAR(map_x_size_);
  DEBUG_PRINT_VAR(map_y_size_);

  //マップの左上のX位置を取得する
  map_left_x_ = center_x_ - (map_x_size_ / 2);
  //マップの左上のY位置を取得する
  map_left_y_ = center_y_ - (map_y_size_ / 2);
}

/// <summary>
/// GetMapLeftX関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>マップの左上のX座標</returns>
int GameInfo::GetMapLeftX() {
  return map_left_x_;
}

/// <summary>
/// GetMapLeftY関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>マップの左上のY座標</returns>
int GameInfo::GetMapLeftY() {
  return map_left_y_;
}

/// <summary>
/// SetGameClear関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void GameInfo::SetGameClear(bool is_game_clear) {
  game_clear_ = is_game_clear;
}

/// <summary>
/// IsGameClear関数
/// </summary>
/// <param name>なし</param>
/// <returns>設定に遷移するかの有無</returns>
bool GameInfo::IsGameClear() {
  return game_clear_;
}