#pragma once
#include "pch.h"
#include <atomic>
#include <condition_variable>
#include <mutex>
class AudioPlayer
{
public:
	AudioPlayer();
	~AudioPlayer();
	/*
		���ƹ��캯��
	*/
	AudioPlayer(const AudioPlayer& rhs) {}

	/*
		��ʼ��XAudioEngine�����캯���Զ�����
	*/
	bool init();
	/*
		��Դ�ͷţ���ֹ�ڴ�й¶�����������Զ�����
		��ֹ�ظ�����
	*/
	bool release();
	/*
		��Ƶ�ļ�װ�أ����ڲ���֮ǰ����
	*/
	bool prepare(std::string filename);
	/*
		��ͣ
	*/
	void pause();
	/*
		����
	*/
	void play();
	/*
		ֹͣ����ֹ�ظ�����
	*/
	void stop();
	/*
		��ȡ��ǰ��Ƶ����ʱ��
	*/
	unsigned int getPlayedTime() { return time; }
	/*
		��ȡ������Ƶ����ʱ��
	*/
	unsigned int getAudioTime() { return allTime; }
	/*
		��ȡ��������
		float 0.0~1.0
	*/
	float getVolume() { float vol; pSource->GetVolume(&vol); return vol; }
	/*
		�趨��������
		float 0.0~1.0
	*/
	void setVolume(float vol) { pSource->SetVolume(vol); }
	/*
		�жϵ�ǰ�Ƿ񲥷�
	*/
	bool isPlaying() { return state == PLAYING; }
	/*
		�ж��Ƿ�ֹͣ����
	*/
	bool isStop() { return state == STOPED; }
	/*
		����ļ���
	*/
	std::string getFileName() { return filename; }
private:
	unsigned int time;										// ��ǰ����ʱ��
	unsigned int allTime;									// ��Ƶ����ʱ��
	std::string filename;									// ��ǰ�����ļ���
	std::atomic<unsigned __int64> begin;					// ������ƫ����
	bool isIntenalPlaying;									// �ڲ�����״̬
	WAVEFORMATEX format;									// ���θ�ʽ
	IXAudio2 * XAudioEngine;								// IXAduio2��Ƶ����
	IXAudio2MasteringVoice * pmaster;						// ����������
	IXAudio2SourceVoice * pSource;                          // ��Դ
	XAUDIO2_BUFFER sBuffer;                                 // ��Դ������
	XAUDIO2_VOICE_STATE pState;                             // ������״̬
	enum PlayState {										// ����״̬ö����
		PLAYING, PAUSING, PREPARING, NONE, STOPED
	};
	std::atomic<PlayState> state;							// ��ǰ����״̬
	std::atomic<PlayState> lastState;						// ��һ������״̬
	std::condition_variable cVar;							// C++��������
	std::mutex m_mutex;										// ������
};