#include "pch.h"
#include "WaveFile.h"
#include <fstream>

WaveFile::WaveFile()
{
	header = WAVE();
}


WaveFile::~WaveFile()
{
}

bool WaveFile::open(const char * filename)
{
	//WAVE & header = this->header;
	std::ifstream fs;
	fs.open(filename, std::ios::binary | std::ios::in);
	//读取wav文件的所有字段
	fs.read((char*)&header, sizeof(struct wave_tag));
	fs.seekg(0x28);
	fs.read((char*)&header.SubChunk2Size, sizeof(header.SubChunk2Size));
	//一次性全部读入内存
	this->data = new unsigned char[header.SubChunk2Size];
	fs.seekg(0x2c);
	fs.read((char *)this->data, header.SubChunk2Size);
	fs.close();
	return true;
}

WAVEFORMATEX WaveFile::getFormat()
{
	WAVEFORMATEX format = WAVEFORMATEX();
	format.wFormatTag = WAVE_FORMAT_PCM;
	format.nChannels = header.NumChannels;
	format.cbSize = header.SubChunk2Size;
	format.nSamplesPerSec = header.SampleRate;
	format.nAvgBytesPerSec = header.ByteRate;
	format.nBlockAlign = header.BlockAlign;
	format.wBitsPerSample = header.BitsPerSample;
	return format;
}
