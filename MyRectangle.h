#pragma once
#include "MyPolygon.h"
class MyRectangle : public MyPolygon
{
	DECLARE_SERIAL(MyRectangle)
public:
	MyRectangle(CPoint s, CPoint e, COLORREF fillcol, COLORREF pencol, int sides = 4);
	~MyRectangle();
	MyRectangle();
	void Draw(CDC* dc) const;
};

