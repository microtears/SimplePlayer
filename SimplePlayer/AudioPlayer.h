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
		复制构造函数
	*/
	AudioPlayer(const AudioPlayer& rhs) {}

	/*
		初始化XAudioEngine，构造函数自动调用
	*/
	bool init();
	/*
		资源释放，防止内存泄露，析构函数自动调用
		禁止重复调用
	*/
	bool release();
	/*
		音频文件装载，需在播放之前调用
	*/
	bool prepare(std::string filename);
	/*
		暂停
	*/
	void pause();
	/*
		播放
	*/
	void play();
	/*
		停止，禁止重复调用
	*/
	void stop();
	/*
		获取当前音频播放时间
	*/
	unsigned int getPlayedTime() { return time; }
	/*
		获取完整音频播放时间
	*/
	unsigned int getAudioTime() { return allTime; }
	/*
		获取播放音量
		float 0.0~1.0
	*/
	float getVolume() { float vol; pSource->GetVolume(&vol); return vol; }
	/*
		设定播放音量
		float 0.0~1.0
	*/
	void setVolume(float vol) { pSource->SetVolume(vol); }
	/*
		判断当前是否播放
	*/
	bool isPlaying() { return state == PLAYING; }
	/*
		判断是否停止播放
	*/
	bool isStop() { return state == STOPED; }
	/*
		获得文件名
	*/
	std::string getFileName() { return filename; }
private:
	unsigned int time;										// 当前播放时间
	unsigned int allTime;									// 音频播放时间
	std::string filename;									// 当前播放文件名
	std::atomic<unsigned __int64> begin;					// 缓存区偏移量
	bool isIntenalPlaying;									// 内部播放状态
	WAVEFORMATEX format;									// 波形格式
	IXAudio2 * XAudioEngine;								// IXAduio2音频引擎
	IXAudio2MasteringVoice * pmaster;						// 声音管理器
	IXAudio2SourceVoice * pSource;                          // 音源
	XAUDIO2_BUFFER sBuffer;                                 // 音源缓冲区
	XAUDIO2_VOICE_STATE pState;                             // 缓冲区状态
	enum PlayState {										// 播放状态枚举类
		PLAYING, PAUSING, PREPARING, NONE, STOPED
	};
	std::atomic<PlayState> state;							// 当前播放状态
	std::atomic<PlayState> lastState;						// 上一个播放状态
	std::condition_variable cVar;							// C++条件变量
	std::mutex m_mutex;										// 互斥量
};