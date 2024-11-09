
// MyPainterDlg.h : header file
//
#include "Shape.h"
#include <windows.h>
#include <windowsx.h>
#pragma once


// CMyPainterDlg dialog
class CMyPainterDlg : public CDialogEx
{
// Construction
public:
	CMyPainterDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYPAINTER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFillcolorbutton();
private:
	CMFCColorButton btn_FillColor;
	CButton btn_Load;
	CButton btn_Save;
	int figureSelection;
	COLORREF selectedFillColor;
	COLORREF selectedPenColor;
	bool isPressed;
	CPoint start, end;
	CTypedPtrArray< CObArray, Shape *> shapes;
	HPEN hPen, hOldPen;
	HBRUSH newBrush, oldBrush;
	void setShapeStyle(Shape* sh, CDC* dc);
	void revertOldStyle(CDC* dc);
	CRect selectedShapeRect;
public:
	afx_msg void OnBnClickedRadioEllipse();
	afx_msg void OnBnClickedRadioRectangle();
	afx_msg void OnBnClickedRadioTriangle();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	CListBox listbox_PenSize;
private:
	CMFCColorButton btn_PenColor;
	void setWindowByAction(int action);
	int currentAction;
	Shape * selectedShape;
	CPoint currentCursorLocation;
	bool modifiedCanvas;
public:
	afx_msg void OnBnClickedPencolorbutton();
	CButton btn_Draw;
	CButton btn_Select;
	afx_msg void OnBnClickedButtonDraw();
	afx_msg void OnBnClickedButtonSelect();
	CStatic lbl_ShapeSelection;
	CButton radio_Ellipse;
	CButton radio_Rectangle;
	CButton radio_Triangle;
	CStatic lbl_fillColor;
	CStatic lbl_penColor;
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	CButton btn_Eraser;
	afx_msg void OnBnClickedButtonEraser();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedCancel();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CStatic lbl_Canvas;
	CButton btn_ChangeColors;
	afx_msg void OnBnClickedButtonFill();
};
