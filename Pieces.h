#pragma once
#include <string>
#include <vector>

class Pieces
{
	public: 
		static const int None = 0;
		static const int King = 1;
		static const int Pawn = 2;
		static const int Knight = 3;
		static const int Bishop = 4;
		static const int Rook = 5;
		static const int Queen = 6;

		static const int White = 8;
		static const int Black = 16;

		std::vector<int> PawnMove(int pos, int color, int squares[]);
		std::vector<int> KnightMove(int pos, int color, int squares[]);
		std::vector<int> BishopMove(int pos, int color, int squares[]);
		std::vector<int> RookMove(int pos, int color, int squares[]);
		std::vector<int> QueenMove(int pos, int color, int squares[]);
		std::vector<int> KingMove(int pos, int color, int squares[]);
		bool UnderAttack(int pos, int color, int squares[]);

		static bool edgeTop(int x)
		{
			if (x < 8)
			{
				return true;
			}
			else
			{
				return false;
			}
		};
		static bool edgeRight(int x)
		{
			if (x % 8 == 7)
			{
				return true;
			}
			else
			{
				return false;
			}
		};
		static const int edgeBottom(int x)
		{
			if (x > 55)
			{
				return true;
			}
			else
			{
				return false;
			}
		};
		static const int edgeLeft(int x)
		{
			if (x % 8 == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		};
};
