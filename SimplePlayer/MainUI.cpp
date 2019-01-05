#include "pch.h"
#include "MainUI.h"


MainUI::MainUI()
{
}


MainUI::~MainUI()
{
}

void MainUI::prepare(AudioPlayer & p)
{
	player = &p;
	offsetY = 8;
	offsetX = 1;
	isFirst = true;
}

void MainUI::drawName()
{
	std::string filename = player->getFileName();
	out(0 + offsetX, 0 + offsetY, filename);
}

void MainUI::drawMenu()
{
	out(0 + offsetX, 1 + offsetY, "shortcut key  #   key description");

	out(0 + offsetX, 3 + offsetY, "      p       #        play");
	out(0 + offsetX, 4 + offsetY, "      s       #        stop");
	out(0 + offsetX, 5 + offsetY, "      x       #        pause");
	out(0 + offsetX, 6 + offsetY, "      v       #        volume");
	out(0 + offsetX, 7 + offsetY, "      l       #        load");
	out(0 + offsetX, 8 + offsetY, "      q       #        quit");

}

void MainUI::drawTimeLine()
{
	if (isFirst)
		isFirst = false;
	unsigned int per = ((player->getPlayedTime() / 1000) / (double)player->getAudioTime()) * 100;

	for (unsigned int i = 0; i <= per; i++) {
		out(i + offsetX, 10 + offsetY, "-");
	}
	std::string s = std::to_string(per) + "%";
	out(per+1, 10 + offsetY, s);
	for (unsigned int i = per + 2; i <= 100; i++) {
		out(i + offsetX, 10 + offsetY, " ");
	}
	std::string time = "";
	//time += "play time/all time # ";
	time += std::to_string(player->getPlayedTime() / 1000);
	time += " / ";
	time += std::to_string(player->getAudioTime());
	out(101 + offsetX, 10 + offsetY, time);
	out(0+offsetX, 13 + offsetY, " ");
}

void MainUI::drawEdge()
{
	int right = 110;
	int bottom = 12;
	int edge = 0;
	for (unsigned int i = 0; i <= 110; i++) {
		out(i, 2 + offsetY, "-");
	}
	for (unsigned int i = 0; i <= 110; i++) {
		out(i, 9 + offsetY, "-");
	}
	/*
	left
	#
	#
	#
	*/
	for (unsigned int i = 0; i <= bottom; i++) {
		out(0 + edge, i + offsetY, "#");
	}

	/*
	right
	 #
	 #
	 #
	*/
	for (unsigned int i = 0; i <= bottom; i++) {
		out(right + edge, i + offsetY, "#");
	}
	/*
	top
	###
	*/
	for (unsigned int i = 0; i <= right; i++) {
		out(i + edge, 0 + offsetY, "-");
	}
	/*
	bottom

	###
	*/
	for (unsigned int i = 0; i <= right; i++) {
		out(i + edge, bottom + offsetY, "-");
	}

}
