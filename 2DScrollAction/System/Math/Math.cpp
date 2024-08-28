#include "System/Math/Math.h"

/// <summary>
/// 線形補間
/// </summary>
/// <param name="start">開始の値</param>
/// <param name="end">終了の値</param>
/// <param name="t">経過時間（0～1）</param>
/// <returns></returns>
float Math::Lerp(float start, float end, float t) {
  return (1 - t) * start + t * end;
}

