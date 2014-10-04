// Pang.cpp : Defines the entry point for the console application.
//

/********************************************************
Pang is a simple pong clone with score printed to the consol.

This was made with help with the following:
http://www.sfml-dev.org/tutorials/2.1/start-vc.php
and the sfml library example of pong
https://github.com/LaurentGomila/SFML/blob/master/examples/pong/Pong.cpp

*********************************************************/

#include "stdafx.h"
#include "Game.h"




int _tmain(int argc, _TCHAR* argv[])
{
	Game::Start();//starts the game.
	//system("PAUSE");
	return 0;
}

