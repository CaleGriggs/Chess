#include "Board.h"
#include "../Chess/src/ofApp.h"
#include "../Chess/Pieces.h"

int Board::squares[64] = {0};

void Board::Draw()
{
	ofFill();
	bool sqColor = false;
	for (int i = 0; i < 8; i++)
	{
		int width = 100;
		int height = 100;
		sqColor = !sqColor;
		for (int j = 0; j < 8; j++)
		{
			int posY = i * width;
			int posX = j * height;

			if (sqColor) {
				ofSetColor(255, 255, 255);
			}
			else
			{
				ofSetColor(80, 80, 80);
			}
			ofDrawRectangle((posX),(posY), width, height);
			sqColor = !sqColor;
		}
	}
}

void Board::BoardLogic(string fen) 
{
	Pieces pieces;

	map<char, int> pieceFromSymbol = {
		{'k' , pieces.King},
		{'p' , pieces.Pawn},
		{'n' , pieces.Knight},
		{'b' , pieces.Bishop},
		{'r' , pieces.Rook},
		{'q' , pieces.Queen}
	};


	char delimiter = ' ';
	string fenBoard = fen.substr(0,fen.find(delimiter));
	int file = 0, rank = 0;

	for (auto symbol : fenBoard)
	{
		if (symbol == '/')
		{
			file = 0;
			rank++;
		}
		else
		{
			if (isdigit(symbol))
			{
				file += symbol - '0';
			}
			else
			{
				int pieceColor = isupper(symbol) ? pieces.White : pieces.Black;
				int pieceType = pieceFromSymbol[tolower(symbol)];
				squares[rank * 8 + file] = pieceType | pieceColor;

				file++;
			}
		}
	}
}
