#include "pch.h"
#include "AudioPlayer.h"
#include "WaveFile.h"
#pragma comment(lib,"xaudio2.lib") 
AudioPlayer::AudioPlayer()
{
	XAudioEngine = NULL;
	pmaster = NULL;
	pSource = NULL;
	sBuffer = {};
	pState = {};
	state = NONE;
	init();
}


AudioPlayer::~AudioPlayer()
{
	release();
}

bool AudioPlayer::init()
{
	//com初始化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	//创建引擎
	if (FAILED(XAudio2Create(&XAudioEngine))) return false;
	//创建主声音，默认是输出当前扬声器
	if (FAILED(XAudioEngine->CreateMasteringVoice(&pmaster))) return false;
	//if (FAILED(XAudioEngine->CreateSourceVoice(&pSource, &format))) return false;
	isIntenalPlaying = false;
	begin = 0;
	time = 0;
	return true;
}

bool AudioPlayer::release()
{
	pmaster->DestroyVoice();
	pSource->DestroyVoice();
	XAudioEngine->Release();
	CoUninitialize();
	XAudioEngine = NULL;
	pmaster = NULL;
	pSource = NULL;
	sBuffer = {};
	pState = {};
	begin = 0;
	time = 0;
	return true;
}

bool AudioPlayer::prepare(std::string filename)
{
	state = PREPARING;
	this->filename = filename;
	WaveFile waveFile = WaveFile();
	waveFile.open(filename.c_str());
	format = waveFile.getFormat();
	BYTE *rawData = waveFile.data;
	//BYTE *nextData = new BYTE[waveFile.header.SubChunk2Size];
	//memcpy(nextData, rawData, waveFile.header.SubChunk2Size);
	sBuffer.AudioBytes = waveFile.header.SubChunk2Size;
	allTime = waveFile.header.SubChunk2Size / waveFile.header.ByteRate;
	sBuffer.pAudioData = rawData;
	sBuffer.Flags = XAUDIO2_END_OF_STREAM;
	if (FAILED(XAudioEngine->CreateSourceVoice(&pSource, &format))) return false;
	std::thread playThread{ [&]() {
		time = 0;
		sBuffer.PlayBegin = begin;
		pSource->SubmitSourceBuffer(&sBuffer);
		for (pSource->GetState(&pState);
			pState.BuffersQueued;
			pSource->GetState(&pState))
		{
			Sleep(200);
			time += 200;
			/*printf("pState.BuffersQueued is %s\n", pState.BuffersQueued ? "true" : "false");
			printf("pState.BuffersQueued num is %d\n", pState.BuffersQueued);
			printf("pState.SamplesPlayed num is %lld\n", pState.SamplesPlayed);
			printf("isplaying %s\n", isPlaying ? "true" : "false");
			printf("volume is %f\n", getVolume());*/
			switch (state)
			{
			case PLAYING:
				if (isIntenalPlaying) continue;
				isIntenalPlaying = true;
				sBuffer.PlayBegin = begin;
				pSource->SubmitSourceBuffer(&sBuffer);
				pSource->Start();
			break;
			case STOPED:break;
			case PAUSING:
			case PREPARING:
			case NONE:
				isIntenalPlaying = false;
				begin = pState.SamplesPlayed;
				pSource->Stop();
				std::unique_lock<std::mutex> locker(m_mutex);
				cVar.wait(locker, [&]() { return state == PLAYING; });
			break;
			}
			if (state == STOPED) {
				break;
			}
		}
		state = NONE;
	} };
	playThread.detach();
	return true;
}

void AudioPlayer::pause()
{
	state = PAUSING;
}

void AudioPlayer::play()
{
	if (state == STOPED || state == NONE) {
		init();
		prepare(filename);
	}
	state = PLAYING;
	cVar.notify_one();
}

void AudioPlayer::stop()
{
	state = STOPED;
	release();
}
