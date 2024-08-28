#pragma once
#include <iostream>
#include <windows.h>
#include <stdio.h>

/// <summary>
/// LogConsoleクラス
/// </summary>
class LogConsole {
public:

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  LogConsole();

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~LogConsole();

  /// <summary>
  /// CreateConsole関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void CreateConsole();
  
  /// <summary>
  /// DestroyConsole関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void DestroyConsole();

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// <summary>
  /// 標準出力のファイルハンドル
  /// </summary>
  FILE* std_output_;

  /// <summary>
  /// 標準エラー出力のファイルハンドル
  /// </summary>
  FILE* std_errput_;
};

/// <summary>
/// ログ出力処理
/// </summary>
#define DEBUG_ON
#ifdef DEBUG_ON
#define DEBUG_PRINT(variable) std::cout << #variable << std::endl
#else
#define DEBUG_PRINT(variable)
#endif

#define DEBUG_ON
#ifdef DEBUG_ON
#define DEBUG_PRINT_VAR(variable) std::cout << #variable << "：" << (variable) << std::endl
#else
#define DEBUG_PRINT_VAR(variable)
#endif

