#pragma once
#include <afx.h>
#include <windows.h>
#include <windowsx.h>


class Shape : public CObject
{
	DECLARE_SERIAL(Shape)
public:
	Shape(CPoint s, CPoint e, COLORREF fillCol, COLORREF penCol);
	Shape();
	void setStartPoint(CPoint s);
	void setEndPoint(CPoint e);
	CPoint getStartPoint() const;
	CPoint getEndPoint() const;
	void setFillColor(COLORREF fillcol);
	COLORREF getFillColor();
	void setPenColor(COLORREF pencol);
	COLORREF getPenColor();
	virtual bool isInside(const CPoint& P) const;
	virtual void Shift(int dx, int dy);
	virtual void Serialize(CArchive& ar);
	virtual void Redefine(CPoint p1, CPoint p2) { start = p1; end = p2; }
	virtual void Draw(CDC* dc) const;
protected:
	CPoint start, end;
	COLORREF fillColor, penColor;
};

