#include <iostream>
#include "Game/GameMode/GameMode.h"
#include "System/LogConsole/LogConsole.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
GameMode::GameMode(TaskId task_id)
  : Task(task_id)
  , game_clear_(false)
{
  DEBUG_PRINT(GameModeのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
GameMode::~GameMode() {
  DEBUG_PRINT(GameModeのデストラクタ);
}