#pragma once

/// <summary>
/// インプットマネージャー処理
/// </summary>
/// <remarks>
/// キーボードやパッドからの入力を管理する
/// （サンプルなのでパッドは未実装）
/// </remarks>
class InputManager {

public:

  /// <summary>
  /// 使用するゲームでのキーの種類
  /// </summary>
  enum class GameKeyKind {

    /// <summary>
    /// 決定
    /// </summary>
    kDecide,

    /// <summary>
    /// キャンセル
    /// </summary>
    kCancel,

    /// <summary>
    /// 上ボタン
    /// </summary>
    kUp,

    /// <summary>
    /// 下ボタン
    /// </summary>
    kDown,

    /// <summary>
    /// 左ボタン
    /// </summary>
    kLeft,

    /// <summary>
    /// 右ボタン
    /// </summary>
    kRight,

    /// <summary>
    /// ポーズ
    /// </summary>
    kPause,

    /// <summary>
    /// スペース
    /// </summary>
    kSpace,

    /// <summary>
    /// Z
    /// </summary>
    kZ,

    /// <summary>
    /// X
    /// </summary>
    kX,

    /// <summary>
    /// C
    /// </summary>
    kC,

    /// <summary>
    /// 総数
    /// </summary>
    kNum,
  };

public:

  /// <summary>
  /// InputManagerのインスタンスを取得する
  /// （シングルトンデザインパターン）
  /// </summary>
  /// <returns></returns>
  static InputManager* GetInstance() {

    //生成されてないなら動的生成
    if (instance_ == nullptr) {
      instance_ = new InputManager();
    }

    //InputManagerのインスタンスを返す
    return instance_;
  }

  /// <summary>
  /// InputManagerのインスタンスを削除
  /// ゲーム終了時に必ず呼ぶ
  /// </summary>
  static void Destroy() {

    //生成済みなら削除
    if (instance_ != nullptr) {
      delete instance_;
      instance_ = nullptr;
    }
  }

private:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  InputManager();

  /// <summary>
  /// デストラクタ
  /// </summary>
  virtual ~InputManager();

public:

  /// <summary>
  /// タスクの更新の前に呼ばれる関数
  /// </summary>
  /// <param name="delta_time">前回実行フレームからの経過時間（秒）</param>
  void UpdateKeyStateAll(float delta_time);

  /// <summary>
  /// タスクの更新の後に呼ばれる関数
  /// </summary>
  /// <param name="delta_time">前回実行フレームからの経過時間（秒）</param>
  void RecordKeyStateAll(float delta_time);

  /// <summary>
  /// 引数のキーはこのフレームで押されたか
  /// </summary>
  /// <param name="key_kind">調べるキー</param>
  /// <returns>押されているならtrue</returns>
  bool IsPushThisFlame(GameKeyKind game_key_kind);

  /// <summary>
  /// 引数のキーは押されているか
  /// </summary>
  /// <param name="game_key_kind">調べるキー</param>
  /// <returns>押されているならtrue</returns>
  bool IsDown(GameKeyKind game_key_kind);

  /// <summary>
  /// 引数のキーはこのフレームで離されたか
  /// </summary>
  /// <param name="key_kind">調べるキー</param>
  /// <returns>離されているならtrue</returns>
  bool IsReleasedKeyThisFlame(GameKeyKind game_key_kind);


private:

  /// <summary>
  /// キー状態を格納するバッファのサイズ
  /// </summary>
  static const int kKeyBufferSize = 256;

private:

  /// <summary>
  /// InputManagerのインスタンス
  /// </summary>
  static InputManager* instance_;

  /// <summary>
  /// 現在のフレームのキー情報
  /// </summary>
  char current_key_buffer_[kKeyBufferSize];

  /// <summary>
  /// 前回フレームのキー情報
  /// </summary>
  char pre_key_buffer_[kKeyBufferSize];
};

