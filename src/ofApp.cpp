#include "ofApp.h"
#include "../Board.h"
#include "../Pieces.h"

Board board;
Pieces pieces;
const string startFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

//--------------------------------------------------------------
void ofApp::setup(){
	board.BoardLogic(startFEN);
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
	

	// ---- chess board graphic-------
	board.Draw();

	int file = 0, rank = 0; int moves = 0;
	for (int i = 0; i < size(board.squares); i++)
	{
		unsigned color;
		color = ((1 << 3) - 1) & (board.squares[i]);

		if (size(availableMoves) > 0 && availableMoves[moves] == i)
		{

			if (board.squares[i] == 0)
			{
				ofFill();
				ofSetColor(200, 200, 200);
				ofDrawCircle((file * 100) + 50, (rank * 100) + 50, 25);
			}
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
		if (board.squares[i] - color == pieces.Black) 
		{
			piecePics[0][color].draw(file*100, rank*100, 100, 100);
		}
		else if (board.squares[i] - color == pieces.White)
		{
			piecePics[1][color].draw(file*100, rank*100, 100, 100);
		}
		if (size(availableMoves) > 0 && availableMoves[moves] == i)
		{

			if (board.squares[i] == 0)
			{
				ofFill();
				ofSetColor(200, 200, 200);
				ofDrawCircle((file * 100) + 50, (rank * 100) + 50, 25);
			}
			moves++;
			if(moves >= size(availableMoves))
			{
				moves = 0;
			}
		}
		else
		{
			ofSetColor(255);
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

	if (click == -1)										//empty click
	{
		click = x + (y * 8);								//set click
		moveFrom = click;
		int selectedPiece = board.squares[click];			

		if (selectedPiece == 0)								//no piece selected
		{
			click = -1;
		}
		else
			{
			unsigned color;
			color = (0b11000) & selectedPiece;				//bit mask for selectedPiece
			if (selectedPiece - color == pieces.Pawn) 
			{
				availableMoves = pieces.PawnMove(click, color, board.squares);
			}
			else if (selectedPiece - color == pieces.Bishop)
			{
				availableMoves = pieces.BishopMove(click, color, board.squares);
			}
			else if(selectedPiece - color == pieces.Rook)
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
			}
			sort(availableMoves.begin(), availableMoves.end());
		}
	}
	else
	{
		click = x + (y * 8);
		if (std::find(availableMoves.begin(), availableMoves.end(), click) != availableMoves.end()) 
		{
			board.squares[click] = board.squares[moveFrom];
			board.squares[moveFrom] = 0;
			moveTo = x + (y * 8);
		}
		click = -1;
		availableMoves = {};
	}
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
