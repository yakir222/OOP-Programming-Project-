#include "pch.h"
#include "MyTriangle.h"

IMPLEMENT_SERIAL(MyTriangle, CObject, 1)

MyTriangle::MyTriangle(CPoint s, CPoint e, COLORREF fillcol, COLORREF pencol, int sides) : MyPolygon(s,e,fillcol,pencol,numSides)
{

}
MyTriangle::~MyTriangle()
{

}
MyTriangle::MyTriangle()
{

}
void MyTriangle::Draw(CDC* dc) const
{
	CPoint p1, p2, p3; //p1 - left point, p2 - right point, p3 - top middle point
	p1.SetPoint(start.x, end.y);
	p2.SetPoint(end.x, end.y);
	p3.SetPoint(start.x + ((end.x - start.x) / 2 ), start.y);
	CPoint points[3];
	points[0] = p1;
	points[1] = p2;
	points[2] = p3;
	Polygon(dc->GetSafeHdc(), points, sizeof(points) / sizeof(points[0]));
}