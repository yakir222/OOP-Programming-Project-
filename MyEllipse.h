#pragma once
#include "Shape.h"
class MyEllipse : public Shape
{
	DECLARE_SERIAL(MyEllipse)
public:
	MyEllipse(CPoint s, CPoint e, COLORREF fillcol, COLORREF pencol);
	~MyEllipse();
	MyEllipse();
	void Draw(CDC* dc) const;
};

