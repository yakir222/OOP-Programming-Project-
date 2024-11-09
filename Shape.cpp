#include "pch.h"
#include "Shape.h"

IMPLEMENT_SERIAL(Shape, CObject, 1)

Shape::Shape(CPoint s, CPoint e, COLORREF fillCol, COLORREF penCol)
{
	start = s;
	end = e;
	fillColor = fillCol;
	penColor = penCol;
}
Shape::Shape()
{}
void Shape::setStartPoint(CPoint s)
{
	start = s;
}
void Shape::setEndPoint(CPoint e)
{
	end = e;
}
CPoint Shape::getStartPoint() const
{
	return start;
}
CPoint Shape::getEndPoint() const
{
	return end;
}
void Shape::setFillColor(COLORREF c)
{
	fillColor = c;
}
COLORREF Shape::getFillColor()
{
	return fillColor;
}
void Shape::setPenColor(COLORREF c)
{
	penColor = c;
}
COLORREF Shape::getPenColor()
{
	return penColor;
}
bool Shape::isInside(const CPoint& P) const
{
	return (start.x <= P.x && P.x <= end.x || start.x >= P.x && P.x >= end.x) &&
		(start.y <= P.y && P.y <= end.y || start.y >= P.y && P.y >= end.y);
}
void Shape::Shift(int dx, int dy)
{
	start.x = start.x + dx;
	start.y = start.y + dy;

	end.x = end.x + dx;
	end.y = end.y + dy;
}
void Shape::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << start;
		ar << end;
		ar << fillColor;
		ar << penColor;
	}
	else // Loading, not storing
	{
		ar >> start;
		ar >> end;
		ar >> fillColor;
		ar >> penColor;
	}
}

void Shape::Draw(CDC* dc) const
{
}
