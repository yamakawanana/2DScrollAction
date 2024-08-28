#include "DxLib.h"
#include <string>
#include "Game/Audio/AudioManager.h"
#include "Game/Level/BattleLevel.h"
#include "System/FileManager/FileManager.h"

/// <summary>
/// AudioManager.cpp内でのみ使用する定数
/// </summary>
namespace {

  /// <summary>
  /// 効果音のファイルパス
  /// </summary>
  const std::string kSeFilePaths[static_cast<int>(AudioManager::SeKind::kNum)] = {
    "Assets/Sounds/Enter2.mp3",
    "Assets/Sounds/Enter26.mp3",
    "Assets/Sounds/Shock4.mp3",
    "Assets/Sounds/8bit-ME_Victory01.mp3",
    "Assets/Sounds/iwa_gameover011.mp3",
    "Assets/Sounds/se_jump_012.wav",
    "Assets/Sounds/se_shot_004.wav",
    "Assets/Sounds/se_hit_004.wav",
    "Assets/Sounds/punch.mp3",
    "Assets/Sounds/se_powerup_005.wav",
    "Assets/Sounds/whistle.mp3",
  };

  /// <summary>
  /// BGMのファイルパス
  /// </summary>
  const std::string kBgmFilePaths[static_cast<int>(AudioManager::BgmKind::kNum)] = {
    "Assets/Sounds/8bit-act01_title.mp3",
    "Assets/Sounds/maou_bgm_8bit02.mp3",
    "Assets/Sounds/8bit-act02_select.mp3",
    "Assets/Sounds/maou_bgm_8bit02.mp3",
    "Assets/Sounds/8bit-act04_stage01.mp3",
    "Assets/Sounds/maou_bgm_8bit22_GameClear.mp3",
    "Assets/Sounds/maou_bgm_8bit20_GameOver.mp3",
  };

  /// <summary>
  /// 設定を保存するファイル名を定数kSettingCSVに格納する
  /// </summary>
  static const char* kSettingCSV = "Assets/CsvFiles/setting.csv";

  /// <summary>
  /// 最大音量を定数kVolumeに格納する
  /// </summary>
  static const int kMaxSoundEffectVolume = 255;

  /// <summary>
  /// 100％の分母を定数kHundredに格納する
  /// </summary>
  static const int kHundred = 100;

  /// <summary>
  /// BGMのボリュームの倍率
  /// </summary>
  const float kBgmVolume = 0.8f;

}

/// <summary>
/// コンストラクタ
/// </summary>
AudioManager::AudioManager()
  : se_list_()
  , bgm_list_() {

}

/// <summary>
/// デストラクタ
/// </summary>
AudioManager::~AudioManager() {

}

/// <summary>
/// 毎フレームの更新処理
/// </summary>
/// <param name="delta_time">前回実行フレームからの経過時間（秒）</param>
void AudioManager::UpdateFrame(float delta_time) {

  
}

/// <summary>
/// オーディオマネージャー初期化
/// </summary>
void AudioManager::InitAudioManager() {

  
}

/// <summary>
/// オーディオマネージャー後処理
/// </summary>
void AudioManager::FinAudioManager() {

  //すべての効果音を削除
  while (se_list_.empty() == false) {

    //末尾の効果音情報を取得
    SeInfo* se_info = se_list_.back();

    //効果音リストから除外
    se_list_.pop_back();

    //効果音破棄
    DeleteSoundMem(se_info->se_handle);

    //効果音情報を削除
    delete se_info;
    se_info = nullptr;
  }

  //すべてのBGMを削除
  while (bgm_list_.empty() == false) {

    //末尾のBGM情報を取得
    BgmInfo* bgm_info = bgm_list_.back();

    //BGMリストから除外
    bgm_list_.pop_back();

    //BGM破棄
    DeleteSoundMem(bgm_info->bgm_handle);

    //BGM情報を削除
    delete bgm_info;
    bgm_info = nullptr;
  }
}

/// <summary>
/// 効果音の読み込み
/// </summary>
/// <param name="se_kind">読み込む効果音の種類</param>
void AudioManager::LoadSe(SeKind se_kind) {

  SeInfo* se_info = new SeInfo();

  //効果音読み込み
  se_info->se_handle = LoadSoundMem(kSeFilePaths[static_cast<int>(se_kind)].c_str());

  //効果音種類設定
  se_info->se_kind = se_kind;

  //効果音リストへ追加
  se_list_.push_back(se_info);

  //ファイルマネージャーのインスタンスを取得
  FileManager* file_manager = FileManager::GetInstance();

  //設定のファイルを読み込む
  std::vector<int> setting = file_manager->ReadDataFromFile(kSettingCSV);

  //音量の設定をセットする
  sound_volume_ = setting.at(0);
  DEBUG_PRINT_VAR(sound_volume_);

  //効果音のボリューム設定
  ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), se_info->se_handle);
}

/// <summary>
/// BGMの読み込み
/// </summary>
/// <param name="bgm_kind">読み込むBGMの種類</param>
void AudioManager::LoadBgm(BgmKind bgm_kind) {

  BgmInfo* bgm_info = new BgmInfo();

  //BGM読み込み
  bgm_info->bgm_handle = LoadSoundMem(kBgmFilePaths[static_cast<int>(bgm_kind)].c_str());

  //BGM種類設定
  bgm_info->bgm_kind = bgm_kind;

  //BGMリストへ追加
  bgm_list_.push_back(bgm_info);

  //ファイルマネージャーのインスタンスを取得
  FileManager* file_manager = FileManager::GetInstance();

  //設定のファイルを読み込む
  std::vector<int> setting = file_manager->ReadDataFromFile(kSettingCSV);

  //音量の設定をセットする
  sound_volume_ = setting.at(0);
  DEBUG_PRINT_VAR(sound_volume_);

  //BGMのボリューム設定
  ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) * kBgmVolume / static_cast<float>(kHundred))), bgm_info->bgm_handle);
}

/// <summary>
/// 効果音の再生
/// </summary>
/// <param name="se_kind">再生する効果音の種類</param>
void AudioManager::PlaySe(SeKind se_kind) {

  for (std::vector<SeInfo*>::iterator itr = se_list_.begin(); itr != se_list_.end(); ++itr) {

    //違う効果音なら次へ
    if ((*itr)->se_kind != se_kind) {
      continue;
    }

    //効果音再生
    PlaySoundMem((*itr)->se_handle, DX_PLAYTYPE_BACK);

    //再生したので抜ける
    break;
  }
}

/// <summary>
/// BGMの再生
/// </summary>
/// <param name="se_kind">再生するBGMの種類</param>
void AudioManager::PlayBgm(BgmKind bgm_kind) {

  for (std::vector<BgmInfo*>::iterator itr = bgm_list_.begin(); itr != bgm_list_.end(); ++itr) {

    //違うBGMなら次へ
    if ((*itr)->bgm_kind != bgm_kind) {
      continue;
    }

    //BGM再生
    PlaySoundMem((*itr)->bgm_handle, DX_PLAYTYPE_LOOP);

    //再生したので抜ける
    break;
  }
}

/// <summary>
/// BGMの停止
/// </summary>
/// <param name="bgm_kind">停止するBGMの種類</param>
void AudioManager::StopBgm(BgmKind bgm_kind) {

  for (std::vector<BgmInfo*>::iterator itr = bgm_list_.begin(); itr != bgm_list_.end(); ++itr) {

    //違うBGMなら次へ
    if ((*itr)->bgm_kind != bgm_kind) {
      continue;
    }

    //BGM停止
    StopSoundMem((*itr)->bgm_handle);

    //停止したので抜ける
    break;
  }
}

/// <summary>
/// 効果音の音量変更
/// </summary>
/// <param name="se_kind">読み込む効果音の種類</param
/// <param name="sound_volume">音量</param>
void AudioManager::ChangeSeVolume(SeKind se_kind, int sound_volume) {
  for (std::vector<SeInfo*>::iterator itr = se_list_.begin(); itr != se_list_.end(); ++itr) {

    //違うSEなら次へ
    if ((*itr)->se_kind != se_kind) {
      continue;
    }
    //効果音のボリューム設定
    ChangeVolumeSoundMem(sound_volume, (*itr)->se_handle);

    break;
  }

}

/// <summary>
/// BGMの音量変更
/// </summary>
/// <param name="bgm_kind">読み込むBGMの種類</param>
/// <param name="sound_volume">音量</param>
void AudioManager::ChangeBgmVolume(BgmKind bgm_kind, int sound_volume) {
  for (std::vector<BgmInfo*>::iterator itr = bgm_list_.begin(); itr != bgm_list_.end(); ++itr) {

    //違うBGMなら次へ
    if ((*itr)->bgm_kind != bgm_kind) {
      continue;
    }

    //BGMのボリューム設定
    ChangeVolumeSoundMem(sound_volume, (*itr)->bgm_handle);

    break;
  }
}

