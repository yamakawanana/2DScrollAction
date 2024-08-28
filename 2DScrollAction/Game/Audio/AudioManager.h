#pragma once
#include <vector>
#include "System/Task/Task.h"

/// <summary>
/// オーディオマネージャークラス
/// </summary>
class AudioManager : public Task {

public:

  /// <summary>
  /// 効果音の種類
  /// </summary>
  enum class SeKind {

    /// <summary>
    /// カーソル操作効果音
    /// </summary>
    kCursorMp3,

    /// <summary>
    /// Enterを押した時の音
    /// </summary>
    kEnterMp3,

    /// <summary>
    /// ゲームオーバーの効果音
    /// </summary>
    kGameOverMp3,

    /// <summary>
    /// ステージクリアの効果音
    /// </summary>
    kStageClearMp3,

    /// <summary>
    /// プレイヤー死亡時の効果音
    /// </summary>
    kPlayerDeadMp3,

    /// <summary>
    /// ジャンプの効果音
    /// </summary>
    kJumpMp3,

    /// <summary>
    /// プレイヤーがダメージを受けた時の効果音
    /// </summary>
    kPlayerDamageMp3,

    /// <summary>
    /// プレイヤーが画面下に落下した時の効果音
    /// </summary>
    kPlayerFalledMp3,

    /// <summary>
    /// 敵を倒した時の効果音
    /// </summary>
    kAttackEnemyMp3,

    /// <summary>
    /// HPを回復した時の効果音
    /// </summary>
    kHpUpMp3,

    /// <summary>
    /// タイムアップの効果音
    /// </summary>
    kTimeUpMp3,

    /// <summary>
    /// 総数
    /// </summary>
    kNum,

  };

  /// <summary>
  /// BGMの種類
  /// </summary>
  enum class BgmKind {

    /// <summary>
    /// タイトルBGM
    /// </summary>
    kTitleBgmMp3,

    /// <summary>
    /// 操作説明画面BGM
    /// </summary>
    kGuideBgmMp3,

    /// <summary>
    /// ステージ選択画面のBGM
    /// </summary>
    kStageSelectBgmMp3,

    /// <summary>
    /// 設定画面のBGM
    /// </summary>
    kSettingBgmMp3,

    /// <summary>
    /// バトルBGM
    /// </summary>
    kBattleBgmMp3,

    /// <summary>
    /// ゲームクリア時のリザルトBGM
    /// </summary>
    kGameClearBgmMp3,

    /// <summary>
    /// ゲームオーバー時のリザルトBGM
    /// </summary>
    kGameOverBgmMp3,

    /// <summary>
    /// 総数
    /// </summary>
    kNum,
  };

public:

  /// <summary>
  /// コンストラクタ
  /// </summary>
  explicit AudioManager();

  /// <summary>
  /// デストラクタ
  /// </summary>
  virtual ~AudioManager();

  /// <summary>
  /// 毎フレームの更新処理
  /// </summary>
  /// <param name="delta_time">前回実行フレームからの経過時間（秒）</param>
  void UpdateFrame(float delta_time) override;

  /// <summary>
  /// オーディオマネージャー初期化
  /// </summary>
  void InitAudioManager();

  /// <summary>
  /// オーディオマネージャー後処理
  /// </summary>
  void FinAudioManager();

  /// <summary>
  /// 効果音の読み込み
  /// </summary>
  /// <param name="se_kind">読み込む効果音の種類</param>
  void LoadSe(SeKind se_kind);

  /// <summary>
  /// BGMの読み込み
  /// </summary>
  /// <param name="bgm_kind">読み込むBGMの種類</param>
  void LoadBgm(BgmKind bgm_kind);

  /// <summary>
  /// 効果音の再生
  /// </summary>
  /// <param name="se_kind">再生する効果音の種類</param>
  void PlaySe(SeKind se_kind);

  /// <summary>
  /// BGMの再生
  /// </summary>
  /// <param name="se_kind">再生するBGMの種類</param>
  void PlayBgm(BgmKind bgm_kind);

  /// <summary>
  /// BGMの停止
  /// </summary>
  /// <param name="bgm_kind">停止するBGMの種類</param>
  void StopBgm(BgmKind bgm_kind);

  /// <summary>
  /// 効果音の音量変更
  /// </summary>
  /// <param name="se_kind">読み込む効果音の種類</param
  /// <param name="sound_volume">音量</param>
  void ChangeSeVolume(SeKind se_kind, int sound_volume);

  /// <summary>
  /// BGMの音量変更
  /// </summary>
  /// <param name="bgm_kind">読み込むBGMの種類</param>
  /// <param name="sound_volume">音量</param>
  void ChangeBgmVolume(BgmKind bgm_kind, int sound_volume);

private:

  /// <summary>
  /// 効果音情報
  /// </summary>
  struct SeInfo {

    /// <summary>
    /// 効果音のハンドル
    /// </summary>
    int se_handle;

    /// <summary>
    /// 効果音の種類
    /// </summary>
    SeKind se_kind;
  };

  /// <summary>
  /// BGM情報
  /// </summary>
  struct BgmInfo {

    /// <summary>
    /// BGMのハンドル
    /// </summary>
    int bgm_handle;

    /// <summary>
    /// BGMの種類
    /// </summary>
    BgmKind bgm_kind;
  };

private:

  /// <summary>
  /// 効果音リスト
  /// </summary>
  std::vector<SeInfo*> se_list_;

  /// <summary>
  /// BGMリスト
  /// </summary>
  std::vector<BgmInfo*> bgm_list_;

  /// <summary>
  /// 音量
  /// </summary>
  int sound_volume_;

};
