#pragma once
class WaveFile
{
public:
	WaveFile();
	~WaveFile();
	typedef struct wave_tag
	{
		char ChunkID[4];					// "RIFF"标志
		unsigned int ChunkSize;				// 文件长度(WAVE文件的大小, 不含前8个字节)
		char Format[4];						// "WAVE"标志
		char SubChunk1ID[4];				// "fmt "标志
		unsigned int SubChunk1Size;			// 过渡字节(不定)
		unsigned short int AudioFormat;		// 格式类别(10H为PCM格式的声音数据)
		unsigned short int NumChannels;		// 通道数(单声道为1, 双声道为2)
		unsigned short int SampleRate;		// 采样率(每秒样本数), 表示每个通道的播放速度
		unsigned int ByteRate;				// 波形音频数据传输速率, 其值为:通道数*每秒数据位数*每样本的数据位数/8
		unsigned short int BlockAlign;		// 每样本的数据位数(按字节算), 其值为:通道数*每样本的数据位值/8
		unsigned short int BitsPerSample;	// 每样本的数据位数, 表示每个声道中各个样本的数据位数.
		char deathDate[4];
		char SubChunk2ID[4];				// 数据标记"data"
		unsigned int SubChunk2Size;			// 语音数据的长度

	} WAVE;
	/*
	*	WAVE文件头
	*/
	WAVE header;
	/*
	*	音频数据
	*/
	unsigned char *data;
	/*
	*	读取文件
	*/
	bool open(const char* filename);
	/*
	*	获取所需要的格式
	*/
	WAVEFORMATEX getFormat();
};

