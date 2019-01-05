#pragma once
class WaveFile
{
public:
	WaveFile();
	~WaveFile();
	typedef struct wave_tag
	{
		char ChunkID[4];					// "RIFF"��־
		unsigned int ChunkSize;				// �ļ�����(WAVE�ļ��Ĵ�С, ����ǰ8���ֽ�)
		char Format[4];						// "WAVE"��־
		char SubChunk1ID[4];				// "fmt "��־
		unsigned int SubChunk1Size;			// �����ֽ�(����)
		unsigned short int AudioFormat;		// ��ʽ���(10HΪPCM��ʽ����������)
		unsigned short int NumChannels;		// ͨ����(������Ϊ1, ˫����Ϊ2)
		unsigned short int SampleRate;		// ������(ÿ��������), ��ʾÿ��ͨ���Ĳ����ٶ�
		unsigned int ByteRate;				// ������Ƶ���ݴ�������, ��ֵΪ:ͨ����*ÿ������λ��*ÿ����������λ��/8
		unsigned short int BlockAlign;		// ÿ����������λ��(���ֽ���), ��ֵΪ:ͨ����*ÿ����������λֵ/8
		unsigned short int BitsPerSample;	// ÿ����������λ��, ��ʾÿ�������и�������������λ��.
		char deathDate[4];
		char SubChunk2ID[4];				// ���ݱ��"data"
		unsigned int SubChunk2Size;			// �������ݵĳ���

	} WAVE;
	/*
	*	WAVE�ļ�ͷ
	*/
	WAVE header;
	/*
	*	��Ƶ����
	*/
	unsigned char *data;
	/*
	*	��ȡ�ļ�
	*/
	bool open(const char* filename);
	/*
	*	��ȡ����Ҫ�ĸ�ʽ
	*/
	WAVEFORMATEX getFormat();
};

