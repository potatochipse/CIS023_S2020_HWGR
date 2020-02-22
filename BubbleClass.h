// Module:	BubbleClass.h
// Author:	Miguel Antonio Logarta
// Date:	February 20, 2020
// Purpose:	Header file for BubbleClass.cpp

#pragma once
class BubbleClass
{
public:
	BubbleClass(HWND);								// Contructor

	void Draw(HDC);									// Answer WM_PAINT
	bool Move(HWND);								// Move the graphics, returns false when the graphic goes off screen
	RECT GetInvalidateRect();						// Calculate rectangle for PAINT

	// Struct for doubles in POINT and RECT
	struct dRECT
	{
		double left;
		double right;
		double top;
		double bottom;
	};

	// No need for this struct since we won't be changing x
	/*struct dPOINT
	{
		double x;
		double y;
	};*/

private:
	int r, g, b;									// Color
	RECT rRectangle;								// Return value for GetInvalidateRect()

	// Specials for granulated / More precise movement
	dRECT dDim;										// Dimensions with doubles

	// No need for struct dPOINT so just replace this variable with a single double
	// dPOINT dSpeed;								// Motion, with doubles
	double dSpeedY;									// Y motion, with doubles

	int GetRandomInt(int, int);						// Return random int

};

