#pragma once
#include "../Chess/src/ofApp.h"


class Board
{
	public: 
		void Draw();
		void static BoardLogic(string fen);
		int static squares[64];
};

