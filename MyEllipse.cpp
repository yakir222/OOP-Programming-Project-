#include "pch.h"
#include "MyEllipse.h"

IMPLEMENT_SERIAL(MyEllipse, CObject, 1)

MyEllipse::MyEllipse(CPoint s, CPoint e, COLORREF fillcol, COLORREF pencol) : Shape(s, e, fillcol, pencol)
{
}
MyEllipse::MyEllipse()
{
}
MyEllipse::~MyEllipse()
{
}
void MyEllipse::Draw(CDC* dc) const
{
	dc->Ellipse(start.x, start.y, end.x, end.y);
}