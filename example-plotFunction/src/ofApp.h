#pragma once

#include "ofMain.h"
#include "ofxContourPlot.h"

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		CContour contour;

		int functionNo;

		int inputGridSize;
		int drawSize;
		int numPlanes;
		float contourInterval;

		static double fieldFunction(ofApp * parent, double x, double y);
		static void drawPlot(ofApp * parent, int iPlane,int x1, int y1, int x2, int y2);
		
		void drawOriginal();

};
