#include "../../pch.h"
#include "ADX2Le.h"
#include <codecvt> 


using namespace MyLibrary;

//////////////////////////////////
// �����N���郉�C�u�����w��		//
//////////////////////////////////
#pragma comment(lib, "ADX2/lib/cri_ware_pcx86_le_import.lib")
//#pragma comment(lib, "../")

// �萔
// ���\�[�X�f�B���N�g���p�X
const std::wstring ADX2Le::RESOURCE_DIRECTORY = L"Resources/Sounds/";

std::unique_ptr<ADX2Le> ADX2Le::m_Instance;

//--------------------------------------------------------------------------------------
// ����������
//--------------------------------------------------------------------------------------
void ADX2Le::Initialize(const wchar_t *acf)
{
	// �G���[�R�[���o�b�N�֐��̓o�^
	criErr_SetCallback(user_error_callback_func);

	// �������A���P�[�^�̓o�^
	criAtomEx_SetUserAllocator(user_alloc_func, user_free_func, NULL);

	// ���C�u����������
	CriAtomExConfig_WASAPI lib_config;
	CriFsConfig fs_config;
	criAtomEx_SetDefaultConfig_WASAPI(&lib_config);
	criFs_SetDefaultConfig(&fs_config);
	lib_config.atom_ex.max_virtual_voices = MAX_VIRTUAL_VOICE;
	lib_config.hca_mx.output_sampling_rate = SAMPLINGRATE_HCAMX;
	fs_config.num_loaders = MAX_CRIFS_LOADER;
	lib_config.atom_ex.fs_config = &fs_config;
	criAtomEx_Initialize_WASAPI(&lib_config, NULL, 0);

	// �X�g���[�~���O�p�o�b�t�@�̍쐬
	m_dbas_id = criAtomDbas_Create(NULL, NULL, 0);

	// �t���p�X�ɕ⊮
	std::wstring fullpath_wstr = RESOURCE_DIRECTORY + acf;
	// string�ɕϊ�
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	std::string fullpath_str = cv.to_bytes(fullpath_wstr);
	// ACF�t�@�C���̓ǂݍ��݂Ɠo�^
	criAtomEx_RegisterAcfFile(NULL, fullpath_str.c_str(), NULL, 0);

	// DSP�o�X�ݒ�̓o�^
	criAtomEx_AttachDspBusSetting("DspBusSetting_0", NULL, 0);

	// �{�C�X�v�[���̍쐬�i�ő�{�C�X���ύX�^�ő�s�b�`�ύX�^�X�g���[���Đ��Ή��j
	CriAtomExStandardVoicePoolConfig standard_vpool_config;
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&standard_vpool_config);
	standard_vpool_config.num_voices = MAX_VOICE;
	standard_vpool_config.player_config.max_sampling_rate = MAX_SAMPLING_RATE;
	standard_vpool_config.player_config.streaming_flag = CRI_TRUE;
	m_standard_voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(&standard_vpool_config, NULL, 0);

	// HCA-MX�Đ��p�F�{�C�X�v�[���̍쐬
	CriAtomExHcaMxVoicePoolConfig hcamx_vpool_config;
	criAtomExVoicePool_SetDefaultConfigForHcaMxVoicePool(&hcamx_vpool_config);
	hcamx_vpool_config.num_voices = MAX_VOICE;
	hcamx_vpool_config.player_config.max_sampling_rate = MAX_SAMPLING_RATE;
	hcamx_vpool_config.player_config.streaming_flag = CRI_TRUE;
	m_hcamx_voice_pool = criAtomExVoicePool_AllocateHcaMxVoicePool(&hcamx_vpool_config, NULL, 0);

	// �v���C���[�̍쐬
	m_player.Create();
}

//--------------------------------------------------------------------------------------
// �I������
//--------------------------------------------------------------------------------------
void ADX2Le::Finalize()
{
	// �v���C���[�̔j��
	m_player.Release();

	// DSP�̃f�^�b�`
	criAtomEx_DetachDspBusSetting();

	// �{�C�X�v�[���̔j��
	criAtomExVoicePool_Free(m_hcamx_voice_pool);
	criAtomExVoicePool_Free(m_standard_voice_pool);

	// ACF�̓o�^����
	criAtomEx_UnregisterAcf();

	// D-BAS�̔j��
	criAtomDbas_Destroy(m_dbas_id);

	// ���C�u�����̏I��
	criAtomEx_Finalize_WASAPI();
}

//--------------------------------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------------------------------
void ADX2Le::Update()
{
	criAtomEx_ExecuteMain();
}

ADX2Le * ADX2Le::GetInstance()
{
	if (!m_Instance)
	{
		m_Instance.reset(new ADX2Le);
	}

	return m_Instance.get();
}

//--------------------------------------------------------------------------------------
// �G���[�R�[���o�b�N�֐��̃��[�U����
//--------------------------------------------------------------------------------------
void ADX2Le::user_error_callback_func(const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray)
{
	const CriChar8 *errmsg;

	// �G���[�R�[�h����G���[������ɕϊ����ăR���\�[���o�͂���
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);

	const unsigned int dataSize = 256;
	wchar_t wlocal[dataSize + 1] = { 0x00 };

	// �}���`�o�C�g������unicode�֕ϊ�����
	MultiByteToWideChar(
		CP_ACP,
		MB_PRECOMPOSED,
		errmsg,
		dataSize,
		wlocal,
		dataSize + 1);

	// �R���\�[���o�͂���
	OutputDebugString(wlocal);

	return;
}

//--------------------------------------------------------------------------------------
//	�������m�ۊ֐��̃��[�U����
//--------------------------------------------------------------------------------------
void *ADX2Le::user_alloc_func(void *obj, CriUint32 size)
{
	void *ptr;
	ptr = malloc(size);
	return ptr;
}

//--------------------------------------------------------------------------------------
// ����������֐��̃��[�U����
//--------------------------------------------------------------------------------------
void ADX2Le::user_free_func(void *obj, void *ptr)
{
	free(ptr);
}

//--------------------------------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------------------------------
ADX2Le_Player::ADX2Le_Player()
{
	// Acb�n���h���̏�����
	m_acb_hn = nullptr;

	// �v���C���[�̏�����
	m_player = nullptr;
}

//--------------------------------------------------------------------------------------
// �v���C���[�̍쐬
//--------------------------------------------------------------------------------------
void ADX2Le_Player::Create()
{
	// �v���C���[�̍쐬
	if (m_player == nullptr) m_player = criAtomExPlayer_Create(NULL, NULL, 0);
}

//--------------------------------------------------------------------------------------
// Acb�t�@�C���̃��[�h
//--------------------------------------------------------------------------------------
void ADX2Le_Player::LoadAcb(const char *acb, const char *awb)
{
		// ACB�t�@�C���ǂݍ���
	if (m_acb_hn != nullptr)
	{
		// ACB�n���h���̔j��
		criAtomExAcb_Release(m_acb_hn);
	}
	m_acb_hn = criAtomExAcb_LoadAcbFile(NULL, acb, NULL, awb, NULL, 0);
}

//--------------------------------------------------------------------------------------
// �v���C���[�̉���֐�
//--------------------------------------------------------------------------------------
void ADX2Le_Player::Release()
{
	// �v���[���n���h���̔j��
	if (m_player != nullptr) criAtomExPlayer_Destroy(m_player);
	// ACB�n���h���̔j��
	if (m_acb_hn != nullptr) criAtomExAcb_Release(m_acb_hn);
}

//--------------------------------------------------------------------------------------
// �v���C���[�n���h���̎擾
//--------------------------------------------------------------------------------------
CriAtomExPlayerHn ADX2Le_Player::GetPlayerHandle()
{
	return m_player;
}

//--------------------------------------------------------------------------------------
// �w��L���[�̍Đ� 
//--------------------------------------------------------------------------------------
CriAtomExPlaybackId ADX2Le_Player::Play(CriAtomExCueId cue_id, float volume)
{
	// ���ʂ̐ݒ�
	criAtomExPlayer_SetVolume(m_player, volume);
	// �L���[ID�̎w��
	criAtomExPlayer_SetCueId(m_player, m_acb_hn, cue_id);

	// �Đ��̊J�n
	return criAtomExPlayer_Start(m_player);
}

//--------------------------------------------------------------------------------------
// �v���C���[�̉��ʂ̐ݒ�
//--------------------------------------------------------------------------------------
void ADX2Le_Player::SetVolume(float volume)
{
	criAtomExPlayer_SetVolume(m_player, volume);
	criAtomExPlayer_UpdateAll(m_player);
}

//--------------------------------------------------------------------------------------
// �Đ�ID�w��̉��ʂ̐ݒ�
//--------------------------------------------------------------------------------------
void ADX2Le_Player::SetVolumeByID(CriAtomExPlaybackId playback_id, float volume)
{
	criAtomExPlayer_SetVolume(m_player, volume);
	criAtomExPlayer_Update(m_player, playback_id);
}

//--------------------------------------------------------------------------------------
// �v���C���[�̃|�[�Y
//--------------------------------------------------------------------------------------
void ADX2Le_Player::Pause()
{
	// �|�[�Y���H
	if (criAtomExPlayer_IsPaused(m_player) == CRI_TRUE)
	{
		// �|�[�Y����
		criAtomExPlayer_Pause(m_player, CRI_FALSE);
	}
	else
	{
		// �|�[�Y
		criAtomExPlayer_Pause(m_player, CRI_TRUE);
	}
}

//--------------------------------------------------------------------------------------
// �Đ�ID�w��̃|�[�Y
//--------------------------------------------------------------------------------------
void ADX2Le_Player::PauseByID(CriAtomExPlaybackId playback_id)
{
	// �|�[�Y���H
	if (criAtomExPlayback_IsPaused(playback_id) == CRI_TRUE)
	{
		// �|�[�Y����
		criAtomExPlayback_Pause(playback_id, CRI_FALSE);
	}
	else
	{
		// �|�[�Y
		criAtomExPlayback_Pause(playback_id, CRI_TRUE);
	}
}

//--------------------------------------------------------------------------------------
// �v���C���[�̃|�[�Y��Ԃ̎擾
//--------------------------------------------------------------------------------------
bool ADX2Le_Player::IsPause()
{
	if (criAtomExPlayer_IsPaused(m_player) == CRI_TRUE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//--------------------------------------------------------------------------------------
// �Đ�ID�w��̃|�[�Y��Ԃ̎擾
//--------------------------------------------------------------------------------------
bool ADX2Le_Player::IsPauseByID(CriAtomExPlaybackId playback_id)
{
	if (criAtomExPlayback_IsPaused(playback_id) == CRI_TRUE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//--------------------------------------------------------------------------------------
// �v���C���[�̒�~
//--------------------------------------------------------------------------------------
void ADX2Le_Player::Stop()
{
	criAtomExPlayer_Stop(m_player);
}

//--------------------------------------------------------------------------------------
// ����̍Đ����̒�~
//--------------------------------------------------------------------------------------

void ADX2Le_Player::StopByID(CriAtomExPlaybackId playback_id)
{
	criAtomExPlayback_Stop(playback_id);
}

//--------------------------------------------------------------------------------------
// ����̉��̍Đ���Ԃ̎擾
//--------------------------------------------------------------------------------------
bool ADX2Le_Player::IsPlayStateByID(CriAtomExPlaybackId playback_id)
{
	if (criAtomExPlayback_GetStatus(playback_id) == CRIATOMEXPLAYBACK_STATUS_PLAYING)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//--------------------------------------------------------------------------------------
// �v���C���[�̎擾�֐�
//--------------------------------------------------------------------------------------
ADX2Le_Player* ADX2Le::GetPlayer()
{
	return &m_player;
}

//--------------------------------------------------------------------------------------
// Acb�t�@�C���̃��[�h
//--------------------------------------------------------------------------------------
void ADX2Le::LoadAcb(const wchar_t *acb, const wchar_t *awb)
{
	// �t���p�X�ɕ⊮
	std::wstring fullpath_acb_wstr = RESOURCE_DIRECTORY + acb;
	std::wstring fullpath_awb_wstr = RESOURCE_DIRECTORY + awb;
	// string�ɕϊ�
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	std::string fullpath_acb_str = cv.to_bytes(fullpath_acb_wstr);
	std::string fullpath_awb_str = cv.to_bytes(fullpath_awb_wstr);

	m_player.LoadAcb(fullpath_acb_str.c_str(), fullpath_awb_str.c_str());
}

//--------------------------------------------------------------------------------------
// �w��L���[�̍Đ� 
//--------------------------------------------------------------------------------------
CriAtomExPlaybackId ADX2Le::Play(CriAtomExCueId cue_id, float volume)
{
	return m_player.Play(cue_id, volume);
}

//--------------------------------------------------------------------------------------
// �v���C���[�̉��ʂ̐ݒ�
//--------------------------------------------------------------------------------------
void ADX2Le::SetVolume(float volume)
{
	m_player.SetVolume(volume);
}

//--------------------------------------------------------------------------------------
// �v���C���[�̃|�[�Y
//--------------------------------------------------------------------------------------
void ADX2Le::Pause()
{
	m_player.Pause();
}

//--------------------------------------------------------------------------------------
// �v���C���[�̃|�[�Y��Ԃ̎擾
//--------------------------------------------------------------------------------------
bool ADX2Le::IsPause()
{
	return m_player.IsPause();
}

//--------------------------------------------------------------------------------------
// �v���C���[�̒�~
//--------------------------------------------------------------------------------------
void ADX2Le::Stop()
{
	m_player.Stop();
}

void ADX2Le::Stop(CriAtomExPlaybackId playback_id)
{
	m_player.StopByID(playback_id);
}

//--------------------------------------------------------------------------------------
// ����̉��̍Đ���Ԃ̎擾
//--------------------------------------------------------------------------------------
bool ADX2Le::IsPlayStateByID(CriAtomExPlaybackId playback_id)
{
	return m_player.IsPlayStateByID(playback_id);
}