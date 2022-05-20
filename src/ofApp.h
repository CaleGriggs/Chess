#pragma once

#include "ofMain.h"
#include <vector>
#include <algorithm>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


		ofImage BKing, BQueen, BKnight, BBishop, BRook, BPawn, WKing, WQueen, WKnight, WBishop, WRook, WPawn;
		std::map<int, ofImage>WhitePieces;
		std::map<int, ofImage>BlackPieces;
		vector<std::map<int, ofImage>>piecePics;
		int click = 0, moveFrom = 0, moveTo = 0;
		std::vector<int> availableMoves;
};
