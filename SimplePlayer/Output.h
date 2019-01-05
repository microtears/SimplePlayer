#pragma once
#include "pch.h"

class OutHandle
{
public:
	OutHandle() {
		init();
	}
	~OutHandle() {
		release();
	}
	void setPosition(int x, int y) {
		mPos.X = x;
		mPos.Y = y;
		SetConsoleCursorPosition(handle, mPos);
	}
	HANDLE handle;
	COORD mPos;
private:
	void init() {
		mPos = { 0,0 };
		handle = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	void release() {
		//CloseHandle(handle);
	}
};

static OutHandle outHandle = OutHandle();

template<typename T>
void out(int x, int y, T &content, std::ostream &os = std::cout) {
	outHandle.setPosition(x, y);
	os << content;
}
