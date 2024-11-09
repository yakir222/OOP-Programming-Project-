#include "pch.h"
#include "MyPolygon.h"

IMPLEMENT_SERIAL(MyPolygon, CObject, 1)

MyPolygon::MyPolygon(CPoint s, CPoint e, COLORREF fillcol, COLORREF pencol, int sides) : Shape(s,e,fillcol,pencol)
{
	numSides = sides;
}
MyPolygon::MyPolygon()
{

}
MyPolygon::~MyPolygon()
{

}
void MyPolygon::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << start;
		ar << end;
		ar << numSides;
		ar << fillColor;
		ar << penColor;
	}
	else // Loading, not storing
	{
		ar >> start;
		ar >> end;
		ar >> numSides;
		ar >> fillColor;
		ar >> penColor;
	}
}