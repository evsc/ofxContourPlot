// Contour.h: interface for the CContour class.
//
// CContour implements Contour plot algorithm descrided in 
//		IMPLEMENTATION OF
//		AN IMPROVED CONTOUR
//		PLOTTING ALGORITHM
//		BY 
//
//		MICHAEL JOSEPH ARAMINI 
//
//		B.S., Stevens Institute of Technology, 1980 
// See http://www.ultranet.com/~aramini/thesis.html
//
// Ported to C++ by Jonathan de Halleux.
//
// Using CContour :
//
// CContour is not directly usable. The user has to 
//	1. derive the function ExportLine that is 
//		supposed to draw/store the segment of the contour
//	2. Set the function draw contour of. (using  SetFieldFn
//		The function must be declared as follows
//		double (*myF)(double x , double y);
//
//	History:
//		31-07-2002: 
//			- A lot of contribution from Chenggang Zhou (better strip compressions, merging, area, weight),
//			- Got rid of ugly MFC lists for STL.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTOUR_H__45A84754_43CD_414A_80A0_9211F954B0DA__INCLUDED_)
#define AFX_CONTOUR_H__45A84754_43CD_414A_80A0_9211F954B0DA__INCLUDED_

#include "ofMain.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// A structure used internally by CContour
struct CFnStr {
    double m_dFnVal;
    short m_sLeftLen;
	short m_sRightLen;
	short m_sTopLen;
	short m_sBotLen;
};

class ofApp;

class CContour  
{
public:
	CContour();
	virtual ~CContour();

	// Initialize memory. Called in Generate
	virtual void InitMemory();
	// Clean work arrays
	virtual void CleanMemory();
	// Generates contour
	// Before calling this functions you must
	//	1. derive the function ExportLine that is 
	//		supposed to draw/store the segment of the contour
	//	2. Set the function draw contour of. (using  SetFieldFn
	//		The function must be declared as follows
	//		double (*myF)(double x , double y);
	virtual void Generate();

	// Set the dimension of the primary grid
	void SetFirstGrid(int iCol, int iRow);
	// Set the dimension of the base grid
	void SetSecondaryGrid(int iCol, int iRow);
	// Sets the region [left, right, bottom,top] to generate contour 
	void SetLimits(double pLimits[4]);
	// Sets the isocurve values
	void SetPlanes(const std::vector<double>& vPlanes);
	// Sets the pointer to the F(x,y) funtion
	// void SetFieldFcn(double (*_pFieldFcn)(ofApp*,double, double));
	void SetFieldFcn(double (*_pFieldFcn)(ofApp*, double, double), ofApp * call_oject);
	void SetDrawFcn(void (*_drawPlotFcn)(ofApp*,int, int,int,int,int),ofApp * call_object);

	// Retrieve dimension of grids, contouring region and isocurve
	int GetColFir() const		{	return m_iColFir;};
	int GetRowFir() const		{	return m_iRowFir;};
	int GetColSec() const		{	return m_iColSec;};
	int GetRowSec() const		{	return m_iRowSec;};
	void GetLimits(double pLimits[4]);
	unsigned int GetNPlanes() const							{ return m_vPlanes.size();};
	const std::vector<double>& GetPlanes() const	{	return m_vPlanes;};
	// double GetPlane(unsigned int i)	const	{	ASSERT(i>=0); ASSERT(i<m_vPlanes.size()); return m_vPlanes[i];};
	double GetPlane(unsigned int i)	const	{	return m_vPlanes[i];};

	// For an indexed point i on the sec. grid, returns x(i)
	double GetXi(int i) const {	return m_pLimits[0] +  i%(m_iColSec+1)*(m_pLimits[1]-m_pLimits[0])/(double)( m_iColSec );};
	// For an indexed point i on the fir. grid, returns y(i)
	// double GetYi(int i) const { ASSERT(i>=0); return m_pLimits[2] +  i/(m_iColSec+1)*(m_pLimits[3]-m_pLimits[2])/(double)( m_iRowSec );};
	double GetYi(int i) const { return m_pLimits[2] +  i/(m_iColSec+1)*(m_pLimits[3]-m_pLimits[2])/(double)( m_iRowSec );};

	ofApp * app;


protected:
	// Accesibles variables
	std::vector<double> m_vPlanes;			// value of contour planes
	double m_pLimits[4];						// left, right, bottom, top
	int m_iColFir;								// primary	grid, number of columns
	int m_iRowFir;								// primary	grid, number of rows
	int m_iColSec;								// secondary grid, number of columns
	int m_iRowSec;								// secondary grid, number of rows
	double (*m_pFieldFcn)(ofApp* parent, double x, double y); // pointer to F(x,y) function
	void (*m_drawPlotFcn)(ofApp* parent, int iPlane,int x1, int y1, int x2, int y2);

	// Protected function
	// virtual
	void ExportLine(int iPlane, int x1, int y1, int x2, int y2); // plots a line from (x1,y1) to (x2,y2)

	// Work functions and variables
	double m_dDx;
	double m_dDy;
	CFnStr** m_ppFnData;	// pointer to mesh parts
	CFnStr* FnctData(int i,int j)  {	return (m_ppFnData[i]+j);};
	double Field(int x, int y);	 /* evaluate funct if we must,	*/
	void Cntr1(int x1, int x2, int y1, int y2);
	void Pass2(int x1, int x2, int y1, int y2);	  /* draws the contour lines */
};

// A simple test function
double TestFunction(ofApp* parent, double x,double y);

// drawing 

void TestDraw(ofApp* parent, int iPlane, int x1, int y1, int x2, int y2);


#endif // !defined(AFX_CONTOUR_H__45A84754_43CD_414A_80A0_9211F954B0DA__INCLUDED_)
