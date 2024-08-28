#pragma once

/// <summary>
/// 数学関連の関数群
/// </summary>
class Math {

public:

  /// <summary>
  /// 線形補間
  /// </summary>
  /// <param name="start">開始の値</param>
  /// <param name="end">終了の値</param>
  /// <param name="t">経過時間（0～1）</param>
  /// <returns></returns>
  static float Lerp(float start, float end, float t);

};
