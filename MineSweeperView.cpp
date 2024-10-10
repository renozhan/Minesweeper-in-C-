
// MineSweeperView.cpp: CMineSweeperView 類別的實作
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "MineSweeper.h"
#endif

#include "MineSweeperDoc.h"
#include "MineSweeperView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMineSweeperView

IMPLEMENT_DYNCREATE(CMineSweeperView, CFormView)

BEGIN_MESSAGE_MAP(CMineSweeperView, CFormView)
	// 標準列印命令
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_COMMAND(ID_DRAW_MINESWEEPER, &CMineSweeperView::OnDrawMinesweeper)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()


char map[9][9] = { {'1', 'o', 'o', '2', '1', '1', ' ', ' ', ' '},
					   {'1', '2', '2', '2', 'o', '1', ' ', ' ', ' '},
					   {' ', '1', '1', '2', '1', '1', ' ', ' ', ' '},
					   {' ', '1', 'o', '1', ' ', ' ', ' ', ' ', ' '},
					   {' ', '1', '1', '1', ' ', ' ', ' ', ' ', ' '},
					   {' ', ' ', ' ', '1', '2', '3', '3', '3', '2'},
					   {' ', ' ', ' ', '1', 'o', 'o', 'o', 'o', 'o'},
					   {' ', ' ', ' ', '1', '2', '4', '4', '4', '2'},
					   {' ', ' ', ' ', ' ', ' ', '1', 'o', '1', ' '} };
char explore[9][9] = { {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
					   {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
					   {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
					   {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
					   {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
					   {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
					   {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
					   {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
					   {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'} };

int flag = 10, t = 0;
CString s;

// CMineSweeperView 建構/解構
CMineSweeperView::CMineSweeperView() noexcept
	: CFormView(IDD_MINESWEEPER_FORM)
{
	// TODO: 在此加入建構程式碼
}

CMineSweeperView::~CMineSweeperView()
{
}

void CMineSweeperView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CMineSweeperView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的

	return CFormView::PreCreateWindow(cs);
}

void CMineSweeperView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CMineSweeperView 列印

BOOL CMineSweeperView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 預設的準備列印程式碼
	return DoPreparePrinting(pInfo);
}

void CMineSweeperView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印前額外的初始設定
}

void CMineSweeperView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印後的清除程式碼
}

void CMineSweeperView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 在此加入自訂的列印程式碼
}


// CMineSweeperView 診斷

#ifdef _DEBUG
void CMineSweeperView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMineSweeperView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMineSweeperDoc* CMineSweeperView::GetDocument() const // 內嵌非偵錯版本
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMineSweeperDoc)));
	return (CMineSweeperDoc*)m_pDocument;
}
#endif //_DEBUG


// CMineSweeperView 訊息處理常式


void CMineSweeperView::OnDrawMinesweeper()
{
	SetTimer(1, 1000, NULL);
	CBitmap aBitmap;
	aBitmap.LoadBitmap(IDB_BITMAP_UNKNOWN);
	CBitmap bBitmap;
	bBitmap.LoadBitmap(IDB_BITMAP_RETRY);
	CClientDC aDC(this);
	CDC memDC;
	memDC.CreateCompatibleDC(&aDC);
	memDC.SelectObject(&aBitmap);
	for (int i = 0; i <= 640; i += 80) {
		for (int j = 0; j <= 584; j += 73) {
			aDC.BitBlt(i, j, 80, 73, &memDC, 0, 0, SRCCOPY);
		}
	}
	memDC.SelectObject(&bBitmap);
	aDC.BitBlt(80, 700, 48, 48, &memDC, 0, 0, SRCCOPY);

	s.Format(L"%d", flag);
	GetDlgItem(IDC_STATIC_FLAG_CONTENT)->SetWindowText(s);
	GetDlgItem(IDC_STATIC_FLAG)->SetWindowText(L"Flags:");
	GetDlgItem(IDC_STATIC_TIME)->SetWindowText(L"Time:");


}

void CMineSweeperView::OnRButtonDown(UINT nFlags, CPoint point)
{
	SetPic(point, 'R');

	CFormView::OnRButtonDown(nFlags, point);
}


void CMineSweeperView::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetPic(point, 'L');

	CFormView::OnLButtonDown(nFlags, point);
}

void CMineSweeperView::SetPic(CPoint p, char c)
{
	if (c == 'L') {
		if (p.x >= 80 && p.x <= 128 && p.y >= 700 && p.y <= 748) {
			flag = 10;
			t = 0;
			for (int i = 0; i <= 8; i++) {
				for (int j = 0; j <= 8; j++) {
					explore[i][j] = 'x';
				}
			}
			OnDrawMinesweeper();
		}
	}
	if (p.x < 720 && p.y < 657) {
		CBitmap aBitmap;
		CClientDC aDC(this);
		CDC memDC;
		memDC.CreateCompatibleDC(&aDC);

		int x = p.x / 80;
		int y = p.y / 73;

		if (c == 'L') {
			
			if (explore[x][y] == 'e') {
				AfxMessageBox(L"You have already explored this location.", MB_OK);
				return;
			}
			if (map[x][y] == 'o') {
				ShowMap(0, 8, 0, 8, '2');
				aBitmap.LoadBitmap(IDB_BITMAP_WRONGMINE);
				memDC.SelectObject(&aBitmap);
				aDC.BitBlt(x * 80, y * 73, 80, 73, &memDC, 0, 0, SRCCOPY);
				AfxMessageBox(L"You failed. :(", MB_OK);
			}
			else if (explore[x][y] == 'f') {
				explore[x][y] = 'x';
				SetPic(p, 'L');
			}
			else if (map[x][y] == '1') {
				explore[x][y] = 'e';
				aBitmap.LoadBitmap(IDB_BITMAP_1);
				memDC.SelectObject(&aBitmap);
				aDC.BitBlt(x * 80, y * 73, 80, 73, &memDC, 0, 0, SRCCOPY);
			}
			else if (map[x][y] == '2') {
				explore[x][y] = 'e';
				aBitmap.LoadBitmap(IDB_BITMAP_2);
				memDC.SelectObject(&aBitmap);
				aDC.BitBlt(x * 80, y * 73, 80, 73, &memDC, 0, 0, SRCCOPY);
			}
			else if (map[x][y] == '3') {
				explore[x][y] = 'e';
				aBitmap.LoadBitmap(IDB_BITMAP_3);
				memDC.SelectObject(&aBitmap);
				aDC.BitBlt(x * 80, y * 73, 80, 73, &memDC, 0, 0, SRCCOPY);
			}
			else if (map[x][y] == '4') {
				explore[x][y] = 'e';
				aBitmap.LoadBitmap(IDB_BITMAP_4);
				memDC.SelectObject(&aBitmap);
				aDC.BitBlt(x * 80, y * 73, 80, 73, &memDC, 0, 0, SRCCOPY);
			}
			else {
				CheckArea(x, y);
			}
			
		}
		else if (c == 'R') {
			if (explore[x][y] == 'f') {
				aBitmap.LoadBitmap(IDB_BITMAP_UNKNOWN);
				memDC.SelectObject(&aBitmap);
				aDC.BitBlt(x * 80, y * 73, 80, 73, &memDC, 0, 0, SRCCOPY);
				explore[x][y] = 'x';
				flag += 1;
				s.Format(L"%d", flag);
				GetDlgItem(IDC_STATIC_FLAG_CONTENT)->SetWindowText(s);
			}
			else {
				aBitmap.LoadBitmap(IDB_BITMAP_FLAG);
				memDC.SelectObject(&aBitmap);
				aDC.BitBlt(x * 80, y * 73, 80, 73, &memDC, 0, 0, SRCCOPY);
				explore[x][y] = 'f';
				flag -= 1;
				s.Format(L"%d", flag);
				GetDlgItem(IDC_STATIC_FLAG_CONTENT)->SetWindowText(s);
			}
		}
		int count = 0, count2 = 0;
		for (int i = 0; i <= 8; i++) {
			for (int j = 0; j <= 8; j++) {
				if (explore[i][j] == 'e') {
					count += 1;
				}
				if (explore[i][j] == 'f' && map[i][j] == 'o') {
					count2 += 1;
				}
			}
		}
		if (count == 71 || count2 == 10) {
			ShowMap(0, 8, 0, 8, '1');
			KillTimer(1);
			AfxMessageBox(L"Congratulations! You Win! :D", MB_OK);
		}
	}
}


void CMineSweeperView::ShowMap(int x1, int x2, int y1, int y2, char situation)
{
	CBitmap BITMAP_0;
	BITMAP_0.LoadBitmap(IDB_BITMAP_0);
	CBitmap BITMAP_1;
	BITMAP_1.LoadBitmap(IDB_BITMAP_1);
	CBitmap BITMAP_2;
	BITMAP_2.LoadBitmap(IDB_BITMAP_2);
	CBitmap BITMAP_3;
	BITMAP_3.LoadBitmap(IDB_BITMAP_3);
	CBitmap BITMAP_4;
	BITMAP_4.LoadBitmap(IDB_BITMAP_4);
	CBitmap BITMAP_MINE;
	BITMAP_MINE.LoadBitmap(IDB_BITMAP_MINE);
	CBitmap BITMAP_FLAG;
	BITMAP_FLAG.LoadBitmap(IDB_BITMAP_FLAG);
	CBitmap BITMAP_WRONGFLAG;
	BITMAP_WRONGFLAG.LoadBitmap(IDB_BITMAP_WRONGFLAG);

	CClientDC aDC(this);
	CDC memDC;
	memDC.CreateCompatibleDC(&aDC);
	for (int i = x1; i <= x2; i++) {
		for (int j = y1; j <= y2; j++) {
			if (explore[i][j] == 'f') {
				if (situation == '2') {
					if (map[i][j] == 'o') {
						memDC.SelectObject(&BITMAP_FLAG);
						aDC.BitBlt(i * 80, j * 73, 80, 73, &memDC, 0, 0, SRCCOPY);
					}
					else {
						memDC.SelectObject(&BITMAP_WRONGFLAG);
						aDC.BitBlt(i * 80, j * 73, 80, 73, &memDC, 0, 0, SRCCOPY);
					}
				}
			}
			else {
				if (map[i][j] == 'o') {
					if (situation == '1') {
						memDC.SelectObject(&BITMAP_FLAG);
						aDC.BitBlt(i * 80, j * 73, 80, 73, &memDC, 0, 0, SRCCOPY);
					}
					else {
						memDC.SelectObject(&BITMAP_MINE);
						aDC.BitBlt(i * 80, j * 73, 80, 73, &memDC, 0, 0, SRCCOPY);
					}
				}
				else if (map[i][j] == '1') {
					memDC.SelectObject(&BITMAP_1);
					aDC.BitBlt(i * 80, j * 73, 80, 73, &memDC, 0, 0, SRCCOPY);
				}
				else if (map[i][j] == '2') {
					memDC.SelectObject(&BITMAP_2);
					aDC.BitBlt(i * 80, j * 73, 80, 73, &memDC, 0, 0, SRCCOPY);
				}
				else if (map[i][j] == '3') {
					memDC.SelectObject(&BITMAP_3);
					aDC.BitBlt(i * 80, j * 73, 80, 73, &memDC, 0, 0, SRCCOPY);
				}
				else if (map[i][j] == '4') {
					memDC.SelectObject(&BITMAP_4);
					aDC.BitBlt(i * 80, j * 73, 80, 73, &memDC, 0, 0, SRCCOPY);
				}
				else {
					memDC.SelectObject(&BITMAP_0);
					aDC.BitBlt(i * 80, j * 73, 80, 73, &memDC, 0, 0, SRCCOPY);
				}
			}
		}
	}
}


void CMineSweeperView::CheckArea(int x, int y)
{
	if ((x <= 4 && y >= 6) || ((x == 3 || x == 4) && y >= 4)) {
		ShowMap(0, 1, 5, 8, '3');
		ShowMap(2, 5, 3, 8, '3');
		for (int i = 0; i <= 1; i++) {
			for (int j = 5; j <= 8; j++) {
				if (explore[i][j] != 'f') {
					explore[i][j] = 'e';
				}
			}
		}
		for (int i = 2; i <= 5; i++) {
			for (int j = 3; j <= 8; j++) {
				if (explore[i][j] != 'f') {
					explore[i][j] = 'e';
				}
			}
		}
	}
	else if ((x >= 2 && y == 0) || (x >= 5 && y <= 2) || (x == 8 && y == 4)) {
		ShowMap(1, 8, 0, 1, '3');
		ShowMap(4, 8, 2, 3, '3');
		ShowMap(7, 8, 4, 5, '3');
		for (int i = 1; i <= 8; i++) {
			for (int j = 0; j <= 1; j++) {
				explore[i][j] = 'e';
			}
		}
		for (int i = 4; i <= 8; i++) {
			for (int j = 2; j <= 3; j++) {
				explore[i][j] = 'e';
			}
		}
		for (int i = 7; i <= 8; i++) {
			for (int j = 4; j <= 5; j++) {
				explore[i][j] = 'e';
			}
		}
	}
	else if (x == 8 && y == 8) {
		ShowMap(7, 8, 7, 8, '3');
		for (int i = 7; i <= 8; i++) {
			for (int j = 7; j <= 8; j++) {
				explore[i][j] = 'e';
			}
		}
	}
}


void CMineSweeperView::OnTimer(UINT_PTR nIDEvent)
{
	CMineSweeperDoc* pDoc = GetDocument();

	t += 1;
	s.Format(L"%d", t);
	GetDlgItem(IDC_STATIC_TIME_CONTENT)->SetWindowText(s);

	// pDoc->UpdateAllViews(NULL);
	CFormView::OnTimer(nIDEvent);
}
