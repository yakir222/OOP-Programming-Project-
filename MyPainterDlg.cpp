
// MyPainterDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MyPainter.h"
#include "MyPainterDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include "Shape.h"
#include "MyPolygon.h"
#include "MyEllipse.h"
#include "MyRectangle.h"
#include "MyTriangle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define ELLIPSE_SELECTION 1
#define RECTANGLE_SELECTION 2
#define TRIANGLE_SELECTION 3
#define COLOR_BLACK 0x00000000
#define ACTION_DRAW 1
#define ACTION_SELECT 2
#define ACTION_ERASE 3
#define ACTION_FILL 4
#define PEN_WIDTH 3

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyPainterDlg dialog



CMyPainterDlg::CMyPainterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYPAINTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyPainterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILLCOLORBUTTON, btn_FillColor);
	DDX_Control(pDX, IDC_BUTTON_LOAD, btn_Load);
	DDX_Control(pDX, IDC_BUTTON_SAVE, btn_Save);
	DDX_Control(pDX, IDC_PENCOLORBUTTON, btn_PenColor);
	DDX_Control(pDX, IDC_BUTTON_DRAW, btn_Draw);
	DDX_Control(pDX, IDC_BUTTON_SELECT, btn_Select);
	DDX_Control(pDX, IDC_LABEL_SHAPE, lbl_ShapeSelection);
	DDX_Control(pDX, IDC_RADIO_ELLIPSE, radio_Ellipse);
	DDX_Control(pDX, IDC_RADIO_RECTANGLE, radio_Rectangle);
	DDX_Control(pDX, IDC_RADIO_TRIANGLE, radio_Triangle);
	DDX_Control(pDX, IDC_LABEL_FILLCOLOR, lbl_fillColor);
	DDX_Control(pDX, IDC_LABEL_PENCOLOR, lbl_penColor);
	DDX_Control(pDX, IDC_BUTTON_ERASER, btn_Eraser);
	DDX_Control(pDX, IDC_STATIC_CANVAS, lbl_Canvas);
	DDX_Control(pDX, IDC_BUTTON_CHNG_COLRS, btn_ChangeColors);
}

BEGIN_MESSAGE_MAP(CMyPainterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_FILLCOLORBUTTON, &CMyPainterDlg::OnBnClickedFillcolorbutton)
	ON_BN_CLICKED(IDC_RADIO_ELLIPSE, &CMyPainterDlg::OnBnClickedRadioEllipse)
	ON_BN_CLICKED(IDC_RADIO_RECTANGLE, &CMyPainterDlg::OnBnClickedRadioRectangle)
	ON_BN_CLICKED(IDC_RADIO_TRIANGLE, &CMyPainterDlg::OnBnClickedRadioTriangle)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_PENCOLORBUTTON, &CMyPainterDlg::OnBnClickedPencolorbutton)
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &CMyPainterDlg::OnBnClickedButtonDraw)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, &CMyPainterDlg::OnBnClickedButtonSelect)
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_BUTTON_ERASER, &CMyPainterDlg::OnBnClickedButtonEraser)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMyPainterDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CMyPainterDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDCANCEL, &CMyPainterDlg::OnBnClickedCancel)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_CHNG_COLRS, &CMyPainterDlg::OnBnClickedButtonFill)
END_MESSAGE_MAP()


// CMyPainterDlg message handlers

BOOL CMyPainterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CheckRadioButton(IDC_RADIO_ELLIPSE, IDC_RADIO_TRIANGLE, IDC_RADIO_ELLIPSE);
	figureSelection = ELLIPSE_SELECTION;
	selectedFillColor = COLOR_BLACK;
	selectedPenColor = COLOR_BLACK;
	btn_FillColor.SetColor(COLOR_BLACK);
	btn_PenColor.SetColor(COLOR_BLACK);
	SetCursor(::LoadCursor(NULL, IDC_ARROW));
	modifiedCanvas = false;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyPainterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.


void CMyPainterDlg::OnBnClickedFillcolorbutton()
{
	selectedFillColor = btn_FillColor.GetColor();
}
void CMyPainterDlg::OnBnClickedRadioEllipse()
{
	figureSelection = ELLIPSE_SELECTION;
}


void CMyPainterDlg::OnBnClickedRadioRectangle()
{
	figureSelection = RECTANGLE_SELECTION;
}


void CMyPainterDlg::OnBnClickedRadioTriangle()
{
	figureSelection = TRIANGLE_SELECTION;
}

void CMyPainterDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	isPressed = true;
	modifiedCanvas = true;
	btn_Save.EnableWindow(TRUE);
	switch (currentAction)
	{
		case ACTION_DRAW:
			SetCursor(::LoadCursor(NULL, IDC_CROSS));
			start = point;
			switch (figureSelection)
			{
			case ELLIPSE_SELECTION:
				shapes.Add(new MyEllipse(start, start, selectedFillColor, selectedPenColor));
				break;
			case RECTANGLE_SELECTION:
				shapes.Add(new MyRectangle(start, start, selectedFillColor, selectedPenColor));
				break;
			case TRIANGLE_SELECTION:
				shapes.Add(new MyTriangle(start, start, selectedFillColor, selectedPenColor));
				break;
			}
			break;
		case ACTION_SELECT:
			int i;
			for (i = shapes.GetSize() - 1;i >= 0;i--)
			{
				if (shapes[i]->isInside(point))
				{
					OnPaint(); //this is to repaint the canvas, for case when selected shape and then selecting other shape, so need to remove recttracker from first selected shape
					currentCursorLocation = point;
					//have selected shape!
					selectedShapeRect.SetRect(shapes[i]->getStartPoint(), shapes[i]->getEndPoint());
					CRectTracker crt(selectedShapeRect, CRectTracker::dottedLine);
					crt.Draw(this->GetDC());
					SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
					selectedShape = shapes[i];
					break;
				}
			}
			if (i == -1) //this with the break above is when clicking somewhere and not on any shape, so want to remove rect tracker from selected shape
			{
				selectedShape = nullptr;
				Invalidate();
			}
			break;
		case ACTION_ERASE:
			for (int i = shapes.GetSize() - 1;i >= 0;i--)
			{
				if (shapes[i]->isInside(point))
				{
					shapes.RemoveAt(i);
					Invalidate();
					break;
				}
			}
			break;
		case ACTION_FILL:
			for (int i = shapes.GetSize() - 1;i >= 0;i--)
			{
				if (shapes[i]->isInside(point))
				{
					shapes[i]->setFillColor(selectedFillColor);
					shapes[i]->setPenColor(selectedPenColor);
					Invalidate();
					break;
				}
			}
			break;
		}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CMyPainterDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	isPressed = false;
	switch (currentAction)
	{
		case ACTION_DRAW:
			//SetCursor(::LoadCursor(NULL, IDC_ARROW));
			if ((shapes[shapes.GetSize() - 1]->getStartPoint().x == point.x) && (shapes[shapes.GetSize() - 1]->getStartPoint().y == point.y)) //check if start and end point are same, so no need in shape
			{
				shapes.RemoveAt(shapes.GetSize() - 1);
			}
			break;
	}
	SetCursor(::LoadCursor(NULL, IDC_ARROW));
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMyPainterDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	if (isPressed)
	{
		switch (currentAction)
		{
		case ACTION_DRAW:
			end = point;
			shapes[shapes.GetSize() - 1]->Redefine(start, end);
			Invalidate(); //simulates the WM_PAINT message to redraw window
			break;
		case ACTION_ERASE:
			for (int i = shapes.GetSize() - 1;i >= 0;i--)
			{
				if (shapes[i]->isInside(point))
				{
					shapes.RemoveAt(i);
					Invalidate();
					break;
				}
			}
			break;
		case ACTION_SELECT:
			if (selectedShape != nullptr)
			{
				int dx=0, dy=0;
				dx = point.x - currentCursorLocation.x;
				dy = point.y - currentCursorLocation.y;
				selectedShape->Shift(dx, dy);
				Invalidate();
				currentCursorLocation = point;
			}
			break;
		}
		
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CMyPainterDlg::setShapeStyle(Shape* sh, CDC* dc)
{
	hPen = CreatePen(PS_SOLID, PEN_WIDTH, sh->getPenColor());
	hOldPen = SelectPen(dc->GetSafeHdc(), hPen);

	newBrush = CreateSolidBrush(sh->getFillColor());
	oldBrush = SelectBrush(dc->GetSafeHdc(), newBrush);
}
void CMyPainterDlg::revertOldStyle(CDC* dc)
{
	SelectBrush(dc->GetSafeHdc(), oldBrush);
	DeleteObject(newBrush);

	SelectPen(dc->GetSafeHdc(), hOldPen);
	DeleteObject(hPen);
}
void CMyPainterDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRect rectLabel;
		CRect rectWindow;
		CRect rect1;
		CRect canvasRect;
		GetWindowRect(&rectWindow);
		lbl_Canvas.GetClientRect(&rectLabel);
		canvasRect.SetRect(rectWindow.TopLeft(), rectLabel.BottomRight());
		CDC memDC;
		CBitmap memBM;
		memDC.CreateCompatibleDC(GetDC());
		memBM.CreateCompatibleBitmap(GetDC(), canvasRect.right, canvasRect.bottom);
		CBitmap* pOldBitmap = (CBitmap*)memDC.SelectObject(&memBM);
		memDC.FillSolidRect(0, 0, canvasRect.right, canvasRect.bottom, RGB(255, 255, 255));
		for (int i = 0; i < shapes.GetSize(); i++)
		{
			setShapeStyle(shapes[i], &memDC);
			shapes[i]->Draw(&memDC);
			revertOldStyle(&memDC);
		}
		GetDC()->BitBlt(0, 0, canvasRect.right, canvasRect.bottom, &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(pOldBitmap);

		ReleaseDC(&memDC);
		CDialogEx::OnPaint();
	}
}


void CMyPainterDlg::OnBnClickedPencolorbutton()
{
	selectedPenColor = btn_PenColor.GetColor();
}


void CMyPainterDlg::OnBnClickedButtonDraw()
{
	setWindowByAction(ACTION_DRAW);
}
void CMyPainterDlg::OnBnClickedButtonSelect()
{
	setWindowByAction(ACTION_SELECT);
}
void CMyPainterDlg::setWindowByAction(int action)
{

	switch (action)
	{
		case ACTION_DRAW:
			currentAction = ACTION_DRAW;
			btn_Draw.ModifyStyleEx(0, WS_EX_CLIENTEDGE, SWP_DRAWFRAME);
			btn_Select.ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_DRAWFRAME);
			btn_ChangeColors.ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_DRAWFRAME);
			btn_Eraser.ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_DRAWFRAME);
			lbl_ShapeSelection.EnableWindow(TRUE);
			radio_Ellipse.EnableWindow(TRUE);
			radio_Rectangle.EnableWindow(TRUE);
			radio_Triangle.EnableWindow(TRUE);
			lbl_fillColor.EnableWindow(TRUE);
			lbl_penColor.EnableWindow(TRUE);
			btn_FillColor.EnableWindow(TRUE);
			btn_PenColor.EnableWindow(TRUE);
			break;
		case ACTION_SELECT:
			currentAction = ACTION_SELECT;
			btn_Select.ModifyStyleEx(0, WS_EX_CLIENTEDGE, SWP_DRAWFRAME);
			btn_Draw.ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_DRAWFRAME);
			btn_ChangeColors.ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_DRAWFRAME);
			btn_Eraser.ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_DRAWFRAME);
			lbl_ShapeSelection.EnableWindow(FALSE);
			radio_Ellipse.EnableWindow(FALSE);
			radio_Rectangle.EnableWindow(FALSE);
			radio_Triangle.EnableWindow(FALSE);
			lbl_fillColor.EnableWindow(FALSE);
			lbl_penColor.EnableWindow(FALSE);
			btn_FillColor.EnableWindow(FALSE);
			btn_PenColor.EnableWindow(FALSE);
			break;
		case ACTION_ERASE:
			currentAction = ACTION_ERASE;
			btn_Select.ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_DRAWFRAME);
			btn_Draw.ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_DRAWFRAME);
			btn_ChangeColors.ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_DRAWFRAME);
			btn_Eraser.ModifyStyleEx(0, WS_EX_CLIENTEDGE, SWP_DRAWFRAME);
			lbl_ShapeSelection.EnableWindow(FALSE);
			radio_Ellipse.EnableWindow(FALSE);
			radio_Rectangle.EnableWindow(FALSE);
			radio_Triangle.EnableWindow(FALSE);
			lbl_fillColor.EnableWindow(FALSE);
			lbl_penColor.EnableWindow(FALSE);
			btn_FillColor.EnableWindow(FALSE);
			btn_PenColor.EnableWindow(FALSE);
			break;
		case ACTION_FILL:
			currentAction = ACTION_FILL;
			btn_Draw.ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_DRAWFRAME);
			btn_Select.ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_DRAWFRAME);
			btn_ChangeColors.ModifyStyleEx(0, WS_EX_CLIENTEDGE, SWP_DRAWFRAME);
			btn_Eraser.ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_DRAWFRAME);
			lbl_ShapeSelection.EnableWindow(FALSE);
			radio_Ellipse.EnableWindow(FALSE);
			radio_Rectangle.EnableWindow(FALSE);
			radio_Triangle.EnableWindow(FALSE);
			lbl_fillColor.EnableWindow(TRUE);
			lbl_penColor.EnableWindow(TRUE);
			btn_FillColor.EnableWindow(TRUE);
			btn_PenColor.EnableWindow(TRUE);
			break;
	}
}

BOOL CMyPainterDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	//return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


void CMyPainterDlg::OnBnClickedButtonEraser()
{
	setWindowByAction(ACTION_ERASE);
}


void CMyPainterDlg::OnBnClickedButtonSave()
{
	CFileDialog dlg(FALSE, _T(".shps"), NULL, 0, _T("Shapes (*.shps)|*.shps||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		shapes.Serialize(ar);
		ar.Close();
		file.Close();
		btn_Save.EnableWindow(FALSE);
		modifiedCanvas = false;
	}
}
void CMyPainterDlg::OnBnClickedButtonLoad()
{
	CFileDialog dlg(TRUE, _T(".shps"), NULL, 0, _T("Shapes (*.shps)|*.shps||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		shapes.Serialize(ar);
		ar.Close();
		file.Close();
		Invalidate();
	}
}


void CMyPainterDlg::OnBnClickedCancel()
{
	if (modifiedCanvas)
	{
		const int result = MessageBox(_T("You have unsaved changes, are you sure you want to quit?"), _T("Confirm Quit"), MB_YESNOCANCEL);

		switch (result)
		{
		case IDYES:
			CDialogEx::OnCancel();
			break;
		case IDNO:
			// Do something
			break;
		case IDCANCEL:
			// Do something
			break;
		}
	}
	else
	{
		CDialogEx::OnCancel();
	}
}


BOOL CMyPainterDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	// this is overriden to enable double buffering to avoid flickering
	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}


void CMyPainterDlg::OnBnClickedButtonFill()
{
	setWindowByAction(ACTION_FILL);
}
