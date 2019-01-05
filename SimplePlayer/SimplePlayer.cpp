// SimplePlayer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <conio.h>
#include "MainUI.h"
#include "AudioPlayer.h"
int main(int argc, char** argv)
{
	std::cout << "SimpleAudioPlayer!\n";
	AudioPlayer player = AudioPlayer();
	std::cout << "Please enter audio path.\n";
	std::string path;
	if (argc == 2) {
		path = argv[1];
	}
	else
	{
		if (true) {
			path = "D:\\Micro\\source\\repos\\SimplePlayer\\Res\\6.wav";
		}
		else {
			std::cin >> path;
		}
	}
	std::cout << "Current audio path is\n" << path << "\n";
	bool ntx = true;
	bool isSuccess = player.prepare(path);
	std::cout << (isSuccess ? "Init successful" : "Init failed") << std::endl;
	MainUI ui = MainUI();
	ui.prepare(player); 
	std::thread drawText{ [&]() {
		for (;;) {
			Sleep(1000);
			/*
			if (!player.isPlaying()) break;
			if (ntx)
			printf("Played time: %us\n", player.getPlayedTime() / 1000);
			*/
			ui.draw();
		}
	} };
	if (isSuccess) {
		player.play();
		drawText.detach();
	}

	std::thread listenKeyword{ [&] {
		for (;;) {
			char keyCode = _getch();
			switch (keyCode)
			{
				//play
				case 'p':
					std::cout << "Play                        ";
					player.play();
				break;
				//stop
				case 's':
					std::cout << "Stop                        ";
					player.stop();
				break;
				//pause
				case 'x':
					if (player.isPlaying()) {
						std::cout << "Pause                        ";
						player.pause();
					}
					else {
						std::cout << "Playing                        ";
						player.play();
					}
				break;
				//set volume
				case 'v':
					ntx = false;
					std::cout << "Please input volume value.                        ";
					int vol;
					std::cin >> vol;
					if (vol < 0) vol = 0;
					if (vol > 100)vol = 100;
					player.setVolume(vol / 100.0f);
					ntx = true;
				break;
				case 'l':
					ntx = false;
					std::cout << "Please enter audio path.                        ";
					std::cin >> path;
					isSuccess = player.prepare(path);
					std::cout << (isSuccess ? "Init successful" : "Init failed") << std::endl;
					if (isSuccess) {
						player.play();
						drawText.detach();
					}
					ntx = true;
				break;
				case 'q':
					return 0;
				default:
				break;
			}
			/*
			if (player.isPlaying())
				drawText.detach();*/
		}
	} };

	listenKeyword.join();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
