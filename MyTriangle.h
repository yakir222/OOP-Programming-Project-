#pragma once
#include "MyPolygon.h"
class MyTriangle : public MyPolygon
{
	DECLARE_SERIAL(MyTriangle)
public:
	MyTriangle(CPoint s, CPoint e, COLORREF fillcol, COLORREF pencol, int sides = 3);
	~MyTriangle();
	MyTriangle();
	void Draw(CDC* dc) const;
};

