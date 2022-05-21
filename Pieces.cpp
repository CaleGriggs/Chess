#include "Pieces.h"
#include <map>
#include <string>


std::vector<int>Pieces::PawnMove(int pos, int color, int squares[]) 
{
	std::vector<int>avail = {};
	int colorModifier;

	if (color == Pieces::White) {		// only matters for pawn, only piece that travels in one direction
		colorModifier = -1;
	}
	else {
		colorModifier = 1;
	}
	if (squares[pos + (colorModifier * 8)] == 0) {
		avail.push_back(pos + (colorModifier * 8));

		// double move start
		if (squares[pos + (colorModifier * 16)] == 0) {	
			if ((color == Pieces::Black) && (7 < pos && pos < 16)) {
				avail.push_back(pos + (colorModifier * 16));
			}
			if ((color == Pieces::White) && (47 < pos && pos < 56)) {
				avail.push_back(pos + (colorModifier * 16));
			}
		}
	}

	// Attacks
	if (((0b11000) & squares[pos + (colorModifier * 7)] )!= color && squares[pos + (colorModifier * 7)] != 0) {
		avail.push_back(pos + (colorModifier * 7));
	}
	if (((0b11000) & squares[pos + (colorModifier * 9)]) != color && squares[pos + (colorModifier * 9)] != 0) {
		avail.push_back(pos + (colorModifier * 9));
	}
	/*
		en passent goes here... maybe
	*/

	if ((edgeTop(pos - 8) && color == Pieces::White) || (edgeBottom(pos + 8) && color == Pieces::Black))// promote										
	{
		avail.push_back(-1);
	}
	return avail;
}

std::vector<int>Pieces::KnightMove(int pos, int color, int squares[])  

{ 
	std::vector<int> avail = {};

	// up check
	if (pos - 16 >= 0)
	{
		if (!edgeLeft(pos))
		{
			// up right (-17 == -16(up 2) -1(lef 1))
			if(((0b11000) & squares[pos - 17]) != color)
			{
				avail.push_back(pos - 17);
			}
		}
		if (!edgeRight(pos))
		{
			if (((0b11000) & squares[pos - 15]) != color)
			{
				avail.push_back(pos - 15);
			}
		}
	}

	// down check
	if (pos + 16 <= 63)				
	{
		if (!edgeRight(pos))
		{
			if (((0b11000) & squares[pos + 17]) != color)				
			{
				avail.push_back(pos + 17);
			}
		}
		if (!edgeLeft(pos))
		{
			if (((0b11000) & squares[pos + 15]) != color)
			{
				avail.push_back(pos + 15);
			}
		}
	}

	// left check
	if (!edgeLeft(pos) && !edgeLeft(pos - 1) )	
	{

		// left-up check
		if (!edgeTop(pos) && (0b11000 & squares[pos - 10]) != color && pos - 10 > -1)
		{
			avail.push_back(pos - 10);
		}
		
		// left-down check
		if (!edgeBottom(pos) && (0b11000 & squares[pos + 6]) != color && pos + 6 < 64)	
		{
			avail.push_back(pos + 6);
		}
	}
	
	// right check
	if (!edgeRight(pos) && !edgeRight(pos + 1))											
	{
		
		// right-up check
		if (!edgeTop(pos) && (0b11000 & squares[pos + 10]) != color && pos + 10 < 64)	
		{
			avail.push_back(pos + 10);
		}
		
		// rightt-down check
		if (!edgeBottom(pos) && (0b11000 & squares[pos - 6]) != color && pos - 6 > -1)	
		{
			avail.push_back(pos - 6);
		}
	}
	return avail; 
}
std::vector<int>Pieces::BishopMove(int pos, int color, int squares[])
{
	std::vector<int>avail = {};
	int temp, multi = 1;

	//NW
	while (true)
	{

		temp = pos - (9 * multi);
		if (temp > -1 && temp < 64)														// can't go too high
		{
			if (!edgeLeft(pos))															// can't wrap around to other side
			{
				if (((0b11000) & squares[temp]) != color)								// not friendly color
				{
					if (edgeTop(temp) || edgeLeft(temp) || squares[temp] != 0)
					{
						avail.push_back(temp);
						break;
					}
					else
					{
						avail.push_back(temp);
					}
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
		multi++;
	}
	multi = 1;

	//NE
	while (true)
	{
		temp = pos - (7 * multi);
		if (temp > -1 && temp < 64)														// can't go too high
		{
			if (!edgeRight(pos))														// can't wrap around to other side
			{
				if (((0b11000) & squares[temp]) != color)								// not friendly color
				{
					if (edgeTop(temp) || edgeRight(temp) || squares[temp] != 0)
					{
						avail.push_back(temp);
						break;
					}
					else
					{
						avail.push_back(temp);
					}
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
		multi++;
	}
	multi = 1;

	//SW
	while (true)
	{
		temp = pos + (7 * multi);
		if (temp > -1 && temp < 64)														// can't go too high
		{
			if (!edgeLeft(pos))															// can't wrap around to other side
			{
				if (((0b11000) & squares[temp]) != color)								// not friendly color
				{
					if (edgeBottom(temp) || edgeLeft(temp) || squares[temp] != 0)
					{
						avail.push_back(temp);
						break;
					}
					else
					{
						avail.push_back(temp);
					}
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
		else 
		{
			break;
		}
		multi++;
	}
	multi = 1;

	//SE
	while (true)
	{
		temp = pos + (9 * multi);
		if (temp > -1 && temp < 64)														// can't go too high
		{
			if (!edgeRight(pos))														// can't wrap around to other side
			{
				if (((0b11000) & squares[temp]) != color)								// not friendly color
				{
					if (edgeBottom(temp) || edgeRight(temp) || squares[temp] != 0)
					{
						avail.push_back(temp);
						break;
					}
					else
					{
						avail.push_back(temp);
					}
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
		multi++;
	}
	return avail;
}
std::vector<int>Pieces::RookMove(int pos, int color, int squares[])
{
	int temp = pos;
	std::vector<int> avail = {};
	while (true)																		// North move
	{
		temp -= 8;
		if (temp < 0)																	// Out of scope
		{
			break;
		}
		if (edgeTop(temp))																// Top edge of board
		{
			avail.push_back(temp);
			break;
		}
		if (squares[temp] != 0)
		{
			if (((0b11000) & squares[temp]) != color)									// Enemy piece, can't move past
			{
				avail.push_back(temp);
				break;
			}
			else if (((0b11000) & squares[temp]) == color)								// Same color blocks movement; can't move here
			{
				break;
			}
		}
		else																			// Empty square
		{
			avail.push_back(temp);
		}
	}
	temp = pos;
	while (true)																		// South move
	{
		temp += 8;
		if (temp > 63)																	// Out of scope
		{
			break;
		}
		if (edgeBottom(temp))															// Bottom edge of board
		{
			avail.push_back(temp);
			break;
		}
		if (squares[temp] != 0)
		{
			if (((0b11000) & squares[temp]) != color)									// Enemy piece, can't move past
			{
				avail.push_back(temp);
				break;
			}
			else if (((0b11000) & squares[temp]) == color)								// Same color blocks movement; can't move here
			{
				break;
			}
		}
		else																			// Empty square
		{
			avail.push_back(temp);
		}
	}
	temp = pos;
	while (true)																		// East move
	{
		temp += 1;
		if (temp < 0 || edgeRight(pos))													// Out of scope
		{
			break;
		}
		if (edgeRight(temp))															// Right edge of board
		{
			avail.push_back(temp);
			break;
		}
		if (squares[temp] != 0)
		{
			if (((0b11000) & squares[temp]) != color)									// Enemy piece, can't move past
			{
				avail.push_back(temp);
				break;
			}
			else if (((0b11000) & squares[temp]) == color)								// Same color blocks movement; can't move here
			{
				break;
			}
		}
		else																			// Empty square
		{
			avail.push_back(temp);
		}
	}
	temp = pos;
	while (true)																		// West move
	{
		temp -= 1;
		if (temp > 63 || edgeLeft(pos))													// Out of scope
		{
			break;
		}
		if (edgeLeft(temp))																// Left edge of board
		{
			avail.push_back(temp);
			break;
		}
		if (squares[temp] != 0)
		{
			if (((0b11000) & squares[temp]) != color)									// Enemy piece, can't move past
			{
				avail.push_back(temp);
				break;
			}
			else if (((0b11000) & squares[temp]) == color)								// Same color blocks movement; can't move here
			{
				break;
			}
		}
		else																			// Empty square
		{
			avail.push_back(temp);
		}
	}

	return avail;
};
std::vector<int>Pieces::QueenMove(int pos, int color, int squares[])
{
	std::vector<int> rook, bish  = {};
	rook = RookMove(pos, color, squares);
	bish = BishopMove(pos, color, squares);
	rook.insert(rook.end(), bish.begin(), bish.end());
	return rook;
};
std::vector<int>Pieces::KingMove(int pos, int color, int squares[])
{
	int moves[8] = { -9,-8,-7,-1,1,7,8,9 };
	std::vector<int> avail = {};
	if (edgeTop(pos))
	{
		moves[0] = 0;
		moves[1] = 0;
		moves[2] = 0;
	}
	if (edgeLeft(pos)) 
	{
		moves[0] = 0;
		moves[3] = 0;
		moves[5] = 0;
	}
	if (edgeRight(pos))
	{
		moves[2] = 0;
		moves[4] = 0;
		moves[7] = 0;
	}
	if (edgeBottom(pos))
	{
		moves[5] = 0;
		moves[6] = 0;
		moves[7] = 0;
	}

	for (int i = 0; i < 8 ; i++)
	{
		if ((0b11000 & squares[pos + moves[i]]) != color && moves[i] != 0)
		{
			avail.push_back(pos + moves[i]);
		}
	}
	return avail;
};