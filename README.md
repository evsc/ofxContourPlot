ofxContourPlot
==============

This ofxAddon is basically a wrapper/adaptation of Jonathan de Halleux's contour-plotting c++ code ([A C++ implementation of an improved contour plotting algorithm](http://www.codeproject.com/Articles/1727/A-C-implementation-of-an-improved-contour-plotting)) which is based on Michael Joseph Aramini's thesis [Implementation of an improved Contour Plotting Algorithm](http://members.bellatlantic.net/~vze2vrva/thesis.html). 


Function Plot
-------------

The first example demonstrates contour-plotting of mathematical functions `f(x,y)`. On the left is a pixel drawing of the function, on the right the contour-plot based on the same function. 

<p align="center">
	<img src="https://raw.github.com/evsc/ofxContourPlot/master/example-plotFunction/function_1.png"/>
</p>

<p align="center">
	<img src="https://raw.github.com/evsc/ofxContourPlot/master/example-plotFunction/function_2.png"/>
</p>



How To
------

In the header file you need to instantiate a `CContour` object and two callback functions. One callback functions lets the CContour object sample what you want to draw, and the other one lets you draw the generated contour plot. Both callback functions are defined as static function of ofApp. 


```cpp
class ofApp : public ofBaseApp{

	CContour contour;

	static double fieldFunction(ofApp * parent, double x, double y);
	static void drawPlot(ofApp * parent, int iPlane,int x1, int y1, int x2, int y2);

};
```

Define the callback function that feeds the contour plot algorithm. Default input range from CContour for x|y is 0 to 5. 

```cpp
double ofApp::fieldFunction(ofApp * parent, double x, double y) {

	// if you want to refer back to objects/variables in the
	// the main ofApp do it like this:
	// parent->inputGridSize

	return sin(x*2) + cos(y*2);

}
```

Define the callback function that lets you draw the contour plot. It hands you back individual lines (x1, y1, x2, y2) and the number of the contour plane (iPlane). 

```cpp
void ofApp::drawPlot(ofApp * parent, int iPlane,int x1, int y1, int x2, int y2) {

	ofSetColor( ofMap(iPlane, 0, parent->contour.GetNPlanes(), 0, 255)  );
	ofLine(x1,y1,x2,y2);

}
```

In setup() you need to register the two callback functions and can define parameters for the contour plot.

```cpp
void ofApp::setup(){

	// register callback functions
	contour.SetFieldFcn(fieldFunction, this);
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
```

In the draw() function you generate and draw the contour plot with one call.

```cpp
void ofApp::draw(){

	// this calculates and draws the contour plot
	// by calling (1) fieldFunction
	//        and (2) drawPlot
	contour.Generate();

}
```





TODO
----

* draw function return float / not int
* example to demonstrate contour-plotting from image
* implementation of ListContour class that hands back full opengl-data of contour planes
* proper header info