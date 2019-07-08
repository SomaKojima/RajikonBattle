/// <summary>
/// ADX2���������C�u����
/// </summary>
#pragma once

#include "include\cri_adx2le.h"
#include <memory>
#include <string>

namespace MyLibrary
{
	// ADX2Le�̍Đ��v���C���[�N���X
	class ADX2Le_Player
	{
		// ACB�n���h��
		CriAtomExAcbHn m_acb_hn;

		// �v���C���[�n���h��
		CriAtomExPlayerHn m_player;

	public:

		// �R���X�g���N�^
		ADX2Le_Player();

		// �v���C���[�̍쐬
		void Create();

		// Acb�t�@�C���̃��[�h
		void LoadAcb(const char *acb, const char *awb = NULL);

		// �v���C���[�̉���֐�
		void Release();

		// �v���C���[�n���h���̎擾
		CriAtomExPlayerHn GetPlayerHandle();

		//----- �Đ� -----//

		// �w��L���[�̍Đ� 
		CriAtomExPlaybackId Play(CriAtomExCueId cue_id, float volume = 1.0f);

		//----- ���� -----//

		// �v���C���[�̉��ʂ̐ݒ�
		void SetVolume(float volume);

		// �Đ�ID�w��̉��ʂ̐ݒ�
		void SetVolumeByID(CriAtomExPlaybackId playback_id, float volume);

		//----- �|�[�Y -----//

		// �v���C���[�̃|�[�Y
		void Pause();

		// �Đ�ID�w��̃|�[�Y
		void PauseByID(CriAtomExPlaybackId playback_id);

		// �v���C���[�̃|�[�Y��Ԃ̎擾
		bool IsPause();

		// �Đ�ID�w��̃|�[�Y��Ԃ̎擾
		bool IsPauseByID(CriAtomExPlaybackId playback_id);

		//----- ��~ -----//

		// �v���C���[�̒�~
		void Stop();

		// ����̍Đ����̒�~
		void StopByID(CriAtomExPlaybackId playback_id);

		//----- �Đ���� -----//

		// ����̉��̍Đ���Ԃ̎擾
		bool IsPlayStateByID(CriAtomExPlaybackId playback_id);
	};

	// ADX2Le�N���X
	class ADX2Le
	{
		// �ő�{�C�X���𑝂₷���߂̊֘A�p�����[�^
		static const int MAX_VOICE = 24;
		static const int MAX_VIRTUAL_VOICE = 64;	// �������葽��(�ʏ�{�C�X�{HCA-MX�{�C�X�{��)
		static const int MAX_CRIFS_LOADER = 64;		// �������葽��(�ʏ�{�C�X�{HCA-MX�{�C�X�{��)

		// �ő�T���v�����O���[�g�i�s�b�`�ύX�܂ށj
		static const int MAX_SAMPLING_RATE = (48000 * 2);

		// HCA-MX�R�[�f�b�N�̃T���v�����O���[�g
		static const int SAMPLINGRATE_HCAMX = 32000;

		static const std::wstring RESOURCE_DIRECTORY;

		CriAtomExVoicePoolHn	m_standard_voice_pool;	// �{�C�X�v�[��(ADX/HCA�R�[�f�b�N�p)
		CriAtomExVoicePoolHn	m_hcamx_voice_pool;		// �{�C�X�v�[��(HCA-MX�p)
		CriAtomDbasId		m_dbas_id;				// D-BAS�n���h��

		ADX2Le_Player m_player; // �v���C���[

	public:
		static ADX2Le* GetInstance();
	private:
		static std::unique_ptr<ADX2Le> m_Instance;

	private:
		static void user_error_callback_func(const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);
		static void *user_alloc_func(void *obj, CriUint32 size);
		static void user_free_func(void *obj, void *ptr);

	public:

		// ����������
		void Initialize(const wchar_t *acf);

		// �X�V����
		void Update();

		// �I������
		void Finalize();

		// �v���C���[�̎擾�֐�
		ADX2Le_Player* GetPlayer();

		// Acb�t�@�C���̃��[�h
		void LoadAcb(const wchar_t *acb, const wchar_t *awb = NULL);

		//----- �Đ� -----//

		// �w��L���[�̍Đ� 
		CriAtomExPlaybackId Play(CriAtomExCueId cue_id, float volume = 1.0f);

		//----- ���� -----//

		// �v���C���[�̉��ʂ̐ݒ�
		void SetVolume(float volume);

		//----- �|�[�Y -----//

		// �v���C���[�̃|�[�Y
		void Pause();

		// �v���C���[�̃|�[�Y��Ԃ̎擾
		bool IsPause();

		//----- ��~ -----//

		// �v���C���[�̒�~
		void Stop();
		void Stop(CriAtomExPlaybackId playback_id);

		//----- �Đ���� -----//

		// ����̉��̍Đ���Ԃ̎擾
		bool IsPlayStateByID(CriAtomExPlaybackId playback_id);
	};
}
