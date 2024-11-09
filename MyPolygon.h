#pragma once
#include "Shape.h"
class MyPolygon : public Shape
{
	DECLARE_SERIAL(MyPolygon)
public:
	MyPolygon(CPoint s, CPoint e, COLORREF fillcol, COLORREF pencol, int sides);
	MyPolygon();
	~MyPolygon();
	void Serialize(CArchive& ar);
protected:
	int numSides;
};

