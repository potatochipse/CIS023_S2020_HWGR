// Module:	BubbleClass.h
// Author:	Miguel Antonio Logarta
// Date:	February 20, 2020
// Purpose:	Implementation file for Bubble Class

#include "CIS023_S2020_HWGR Miguel Antonio Logarta.h"

BubbleClass::BubbleClass(HWND hWnd)
{
	// Get window rectangle
	RECT rClient;									// Get size of window
	GetClientRect(hWnd, &rClient);

	// Select starting location and size
	dDim.left = GetRandomInt(0, rClient.right);		// Start anywhere at the bottom
	dDim.top = rClient.bottom;						// Start at the bottom
	double dSize = GetRandomInt(10, 25);			// Bubbles are round
	dDim.right = dDim.left + dSize;					// Set the bubble size
	dDim.bottom = dDim.top + dSize;

	// Pick a random color for the bubble
	r = GetRandomInt(0, 255);						// Red
	g = GetRandomInt(0, 255);						// Green 
	b = GetRandomInt(0, 255);						// Blue

	// Set the speed
	// dSpeed.x = GetRandomInt(1, 15);				// Set horizontal speed
	dSpeedY = GetRandomInt(1, 10) * -1.0;			// Set vertical speed
}

void BubbleClass::Draw(HDC hdc)
{
	// Create BRUSHES
	HBRUSH brush, oldBrush;
	brush = CreateSolidBrush(RGB(r, g, b));
	oldBrush = (HBRUSH)SelectObject(hdc, brush);

	// Convert double dimensions to int for draw command
	RECT rDim;
	rDim.left = trunc(dDim.left);
	rDim.right = trunc(dDim.right);
	rDim.top = trunc(dDim.top);
	rDim.bottom = trunc(dDim.bottom);

	// Draw the circle
	Ellipse(hdc, rDim.left, rDim.top, rDim.right, rDim.bottom);

	// Release brushes
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}

bool BubbleClass::Move(HWND hWnd)
{
	// Move() makes the bubbles go up. If they touch the ceiling or go off the border, they pop.

	// Get client window rectangle
	RECT rClient;									// Get size of the window
	GetClientRect(hWnd, &rClient);

	// Check for collisions with the window borders. Returns false to delete objects
	//if (dDim.left <= 0.0)							// Did it touch the left wall?
	//	return false;								
	//if (dDim.right >= rClient.bottom)				// Did we hit the bottom?
	//	return false;
	if (dDim.top <= 0.0)							// Did it touch the top?
		return false;								
	if (dDim.right >= rClient.right)				// Did it touch the right wall?
		return false;
	

	// Make the bubbles float up. Move vertically 
	dDim.top += dSpeedY;
	dDim.bottom += dSpeedY;
	
	return TRUE;
}

RECT BubbleClass::GetInvalidateRect()
{
	// Copy double dimension to int rect
	rRectangle.left = trunc(dDim.left);
	rRectangle.right = trunc(dDim.right);
	rRectangle.top = trunc(dDim.top);
	rRectangle.bottom = trunc(dDim.bottom);

	// Make adjustments for movement. They are only moving up 
	//if (dSpeed.x < 0.0)								// If moving left
	//	rRectangle.right -= (dSpeed.x - 1.0);
	//if (dSpeed.x > 0.0)								// If moving right
	//	rRectangle.left -= dSpeed.x;
	//if (dSpeedY > 0.0)								// If they are moving down
	//	rRectangle.top -= dSpeedY;

	if (dSpeedY < 0.0)									// If moving up
		rRectangle.bottom -= (dSpeedY - 1.0);
	

	return rRectangle;
}

int BubbleClass::GetRandomInt(int iMin, int iMax)
{
	random_device rd;								// Non-deterministic generator
	mt19937 gen(rd());								// Seed mersenne twister
	uniform_int_distribution<> dist(iMin, iMax);	// Distribute results inside center rect

	return dist(gen);								// Return a random number in between iMin and iMax
}
