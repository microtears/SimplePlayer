\
#pragma once
#include "Output.h"
#include "AudioPlayer.h"
class MainUI
{
public:
	MainUI();
	~MainUI();
	void prepare(AudioPlayer &p);
	void draw() {
		if (isFirst) {
			drawName();
			drawMenu();
			drawEdge();
		}
		drawTimeLine();
	}
	void clear() {
		system("cls");
	}
private:
	void drawName();
	void drawMenu();
	void drawTimeLine();
	void drawEdge();
	bool isFirst;
	AudioPlayer *player;
	int offsetX;
	int offsetY;
};

