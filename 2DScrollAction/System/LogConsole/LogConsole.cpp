#include <iostream>
#include <fcntl.h> // _O_TEXT
#include <io.h> // _open_osfhandle
#include "LogConsole.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
LogConsole::LogConsole()
//メンバ変数を初期化する
  : std_output_(0)
  , std_errput_(0)
{
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
LogConsole::~LogConsole() {
}

/// <summary>
/// CreateConsole関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void LogConsole::CreateConsole() {
  // コンソールを作成する
  AllocConsole();

  //ハンドルを取得する
  HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);

  //COORD構造体のXとYにコンソールの横と縦の長さを設定する
  COORD coord;
  coord.X = 100;
  coord.Y = 1000;

  //コンソールのバッファの設定をする
  SetConsoleScreenBufferSize(out_handle, coord);

  //標準出力と標準エラー出力をコンソールに書き込み設定で繋げる 
  freopen_s(&std_output_, "CONOUT$", "w", stdout);
  freopen_s(&std_errput_, "CONOUT$", "w", stderr);

  //printf("LogConsole関数\n");
}

/// <summary>
/// DestroyConsole関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void LogConsole::DestroyConsole() {

  //標準出力のファイルハンドルを閉じる
  fclose(std_output_);

  //標準エラー出力のファイルハンドルを閉じる
  fclose(std_errput_);

  //コンソールを解放する
  FreeConsole();
}