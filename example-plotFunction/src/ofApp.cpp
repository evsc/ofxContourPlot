#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){


	functionNo = 1;

	drawSize = 480;
	inputGridSize = 25;


	// define the input function for the contour plot
	contour.SetFieldFcn(fieldFunction, this);
	// define the function that will draw the contour-plot
	contour.SetDrawFcn(drawPlot, this);

	// sampling size of input function
	contour.SetFirstGrid(inputGridSize,inputGridSize);

	// this is the drawing resolution of the plot generated
	contour.SetSecondaryGrid(drawSize,drawSize);


	// set the number of contour planes 
	numPlanes = 20;
	contourInterval = 0.15;
    vector<double> vIso(numPlanes); 
	for (unsigned int i=0;i<vIso.size();i++) {
		vIso[i]=(i-vIso.size()/2.0)*contourInterval;
	}
    contour.SetPlanes(vIso); 

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(0);
	ofFill();
	
	ofPushMatrix();
	ofTranslate(20,150);


	drawOriginal();

	ofTranslate(drawSize+20,0);

	// this calculates and draws the contour plot
	// by calling (1) fieldFunction
	//        and (2) drawPlot
	contour.Generate();

	ofPopMatrix();



	ofSetColor(255);

	stringstream infoText;
	infoText << "CONTOUR PLOT" << endl;
	infoText << "-------------------------------" << endl;
	infoText << "plotting function\t" << functionNo << "\t < 1 - 3 >" << endl << endl;
	infoText << "inputGridSize \t\t" << inputGridSize << "\t < g | h > " << endl;
	infoText << "numPlanes \t\t" << numPlanes << "\t < o | p > " << endl;
	infoText << "contourInterval \t" << contourInterval << "\t < u | i > " << endl;

	ofDrawBitmapString(infoText.str(), 20, 30);

}


//--------------------------------------------------------------
// Callback function for CContour object:
// This is the function that feeds the contour-plot.
// inputs for x and y range from 0 to 5
//--------------------------------------------------------------
double ofApp::fieldFunction(ofApp * parent, double x, double y) {

	// if you want to refer back to objects/variables in the
	// the main ofApp do it like this:
	// parent->inputGridSize

	switch(parent->functionNo) {
		case 1: return sin(x*2) + cos(y*2);
				break;
		case 2: return cos(x*y)*( pow(x,2.0f) - pow(y,2.0f));
				break;
		default:	
				return 0.7*(cos(x+3.14/7)+tan(y+3.14/4));
	}

}

//--------------------------------------------------------------
// Callback function for CContour object:
// Here you draw the contour plot.
// It hands you back individual lines > x1, y1, x2, y2
// and the plane number > iPlane
//--------------------------------------------------------------
void ofApp::drawPlot(ofApp * parent, int iPlane,int x1, int y1, int x2, int y2) {

	ofSetColor( ofMap(iPlane, 0, parent->contour.GetNPlanes(), 0, 255)  );
	ofLine(x1,y1,x2,y2);

}

//--------------------------------------------------------------
void ofApp::drawOriginal() {

	int res = 2;
	ofFill();
	ofSetColor(0,255,0);

	for (int i=0; i<drawSize; i+=res) {
		for (int j=0; j<drawSize; j+=res) {
			ofSetColor(min(255.0,126+75*fieldFunction(this,(i*5.f)/float(drawSize), (j*5.f)/float(drawSize))));
			ofRect(i,j,res,res);
		}
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	if (key >= '1' && key <= '3') {
		functionNo = int(key) - int('0');
	}
	else if (key == 'h') {
		inputGridSize++;
		contour.SetFirstGrid(inputGridSize,inputGridSize);
	}
	else if (key == 'g') {
		inputGridSize--;
		if (inputGridSize < 2) inputGridSize = 2;
		contour.SetFirstGrid(inputGridSize,inputGridSize);
	}
	else if (key == 'p') {
		numPlanes++;
	}
	else if (key == 'o') {
		numPlanes--;
	}
	else if (key == 'i') {
		contourInterval+=0.05;
	}
	else if (key == 'u') {
		contourInterval-=0.05;
	}


	if (key == 'o' || key == 'p' || key == 'u' || key == 'i') {
		vector<double> vIso(numPlanes); 
		for (unsigned int i=0;i<vIso.size();i++) {
			vIso[i]=(i-vIso.size()/2.0)*contourInterval;
		}
	    contour.SetPlanes(vIso); 
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
