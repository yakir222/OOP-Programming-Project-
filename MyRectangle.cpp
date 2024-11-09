#include "pch.h"
#include "MyRectangle.h"

IMPLEMENT_SERIAL(MyRectangle, CObject, 1)

MyRectangle::MyRectangle(CPoint s, CPoint e, COLORREF fillcol, COLORREF pencol, int sides) : MyPolygon(s,e,fillcol,pencol,numSides)
{

}
MyRectangle::~MyRectangle()
{

}
MyRectangle::MyRectangle()
{

}
void MyRectangle::Draw(CDC* dc) const
{
	dc->Rectangle(start.x, start.y, end.x, end.y);
}