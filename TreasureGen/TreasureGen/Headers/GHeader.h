//The header for the game class in the program along with many of the using statements used in the game
#ifndef GHeader_h
#define GHeader_h

//All of the using statements in the Game file and any header or source file that uses GHeader
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <time.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <regex>
#include <iterator>
#include <string>
#include <algorithm> 
#undef main
using namespace std;

//The Game class
class Game
{
public:
	//The function that initializes the game
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	//The functions that repeat every frame
	void events();
	void update();
	void render();
	//The function meant for closing the game
	void clean();

	//A list of functions in the Game source file that need access to the event, update, and render functions,
	//and need access to each other
	void buttonControl();
	void generateTreas(int type);
	void battleEnd();
	void itemLoop();
	void purchase(int treas);

	//The function that is constantly checked by the game to see if the game is still running
	bool running() { return isRunning; }

	//Variables that handle game events and rendering
	static SDL_Renderer* renderer;
	static SDL_Event event;

private:
	//The bool value that indicates the game is still running
	bool isRunning;
	//The window that shows the game being played
	SDL_Window *window;
};

#endif // !GHeader_h