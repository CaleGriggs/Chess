#include "ofApp.h"
#include "../Board.h"
#include "../Pieces.h"

Board board;
Pieces pieces;
const string startFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

//--------------------------------------------------------------
void ofApp::setup(){

	// starting position
	board.BoardLogic(startFEN);

	// load piece images
	BKing.load("../data/Black_King.png");
	BQueen.load("../data/Black_Queen.png");
	BKnight.load("../data/Black_Knight.png");
	BBishop.load("../data/Black_Bishop.png");
	BRook.load("../data/Black_Rook.png");
	BPawn.load("../data/Black_Pawn.png");
	WKing.load("../data/White_King.png");
	WQueen.load("../data/White_Queen.png");
	WKnight.load("../data/White_Knight.png");
	WBishop.load("../data/White_Bishop.png");
	WRook.load("../data/White_Rook.png");
	WPawn.load("../data/White_Pawn.png");

	// mapping images to values set in Pieces.h
	BlackPieces = {
		{pieces.King	, BKing},
		{pieces.Queen	, BQueen },
		{pieces.Knight	, BKnight },
		{pieces.Bishop	, BBishop },
		{pieces.Rook	, BRook},
		{pieces.Pawn	, BPawn}
	};
	WhitePieces = {
		{pieces.King	, WKing},
		{pieces.Queen	, WQueen },
		{pieces.Knight	, WKnight },
		{pieces.Bishop	, WBishop },
		{pieces.Rook	, WRook},
		{pieces.Pawn	, WPawn}
	};
	piecePics = {BlackPieces,WhitePieces};
	click = -1;
	availableMoves = {-1};
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	

	// draw chess board
	board.Draw();

	// draw pieces
	int file = 0, rank = 0; int moves = 0;
	for (int i = 0; i < size(board.squares); i++)
	{
		unsigned color;
		color = ((1 << 3) - 1) & (board.squares[i]);

		// draw legal moves per selected piece
		if (board.squares[i] == selectedPiece)
		{
			ofSetColor(0, 0, 0);

		}
		if (size(availableMoves) > 0 && availableMoves[moves] == i)
		{

			if (board.squares[i] == 0)
			{
				ofFill();
				ofSetColor(200, 200, 200);
				ofDrawCircle((file * 100) + 50, (rank * 100) + 50, 25);
			}
			// slightly bigger circles for spaces with pieces
			else 
			{
				ofFill();
				ofSetColor(210, 210, 210);
				ofDrawCircle((file * 100) + 50, (rank * 100) + 50, 30);
			}
			moves++;
			if (moves >= size(availableMoves))
			{
				moves = 0;
			}
		}

		ofSetColor(255,255,255);

		// draw piece images

		if (board.squares[i] - color == pieces.Black) 
		{
			piecePics[0][color].draw(file*100, rank*100, 100, 100);
		}
		else if (board.squares[i] - color == pieces.White)
		{
			piecePics[1][color].draw(file*100, rank*100, 100, 100);
		}

		file++;
		if (file == 8)
		{
			rank++;
			file = 0;
		}
	}
	ofSetColor(255);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	x = ( x - (x % 100)) / 100;  
	y = (y - (y % 100)) / 100;

	// select a new square
	if (click == -1) 
	{
		click = x + (y * 8);
	}

	// if same color, different piece is selected
	if (((0b11000) & selectedPiece) == ((0b11000) & board.squares[click]))
	{
		selectedPiece = board.squares[click];			
		moveFrom = click;

		// Click empty square

		if (selectedPiece == 0)	
		{
			click = -1;
			selectedPiece = -1;
		}
		else
		{
			makingMoves();
		}
	}

	// No previously selected piece
	else if (selectedPiece == -1)
	{
		selectedPiece = board.squares[click];
		moveFrom = click;
		if (selectedPiece == 0)
		{
			click = -1;
			selectedPiece = -1;
		}
		// check if piece color == player turn
		else if ((((0b11000 & selectedPiece) == 8 && playerTurn == 1) || (0b11000 & selectedPiece) == 16 && playerTurn == 0))
		{
			selectedPiece = -1;
		}
		else 
		{
			makingMoves();
		}
	}

	// piece selected, check for legal move of selectedPice
	else
	{
		click = x + (y * 8);
		if (std::find(availableMoves.begin(), availableMoves.end(), click) != availableMoves.end()) 
		{
			board.squares[click] = board.squares[moveFrom];
			board.squares[moveFrom] = 0;
			moveTo = x + (y * 8);
			selectedPiece = -1;
			playerTurn = !playerTurn;
		}
		click = -1;
		availableMoves = {};
		selectedPiece = -1;
	}
	click = -1;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


/*
Find available moves for pieces
*/
void ofApp::makingMoves()
{
	//bit mask for selectedPiece color
	unsigned color;
	color = (0b11000) & selectedPiece;

	if (selectedPiece - color == pieces.Pawn)
	{
		availableMoves = pieces.PawnMove(click, color, board.squares);
	}
	else if (selectedPiece - color == pieces.Bishop)
	{
		availableMoves = pieces.BishopMove(click, color, board.squares);
	}
	else if (selectedPiece - color == pieces.Rook)
	{
		availableMoves = pieces.RookMove(click, color, board.squares);
	}
	else if (selectedPiece - color == pieces.Knight)
	{
		availableMoves = pieces.KnightMove(click, color, board.squares);
	}
	else if (selectedPiece - color == pieces.Queen)
	{
		availableMoves = pieces.QueenMove(click, color, board.squares);
	}
	else if (selectedPiece - color == pieces.King)
	{
		availableMoves = pieces.KingMove(click, color, board.squares);

		for (int i = 0; i < size(availableMoves); i++)
		{
			if (pieces.UnderAttack(availableMoves[i], color, board.squares))
			{
				availableMoves[i] = 99;
			}
		}
	}
	sort(availableMoves.begin(), availableMoves.end());
}