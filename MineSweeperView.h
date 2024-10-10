
// MineSweeperView.h: CMineSweeperView 類別的介面
//

#pragma once


class CMineSweeperView : public CFormView
{
protected: // 僅從序列化建立
	CMineSweeperView() noexcept;
	DECLARE_DYNCREATE(CMineSweeperView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MINESWEEPER_FORM };
#endif

// 屬性
public:
	CMineSweeperDoc* GetDocument() const;

// 作業
public:

// 覆寫
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	virtual void OnInitialUpdate(); // 建構後第一次呼叫
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// 程式碼實作
public:
	virtual ~CMineSweeperView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawMinesweeper();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void SetPic(CPoint p, char c);
	void ShowMap(int x1, int x2, int y1, int y2, char situation);
	void CheckArea(int x, int y);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // 對 MineSweeperView.cpp 中的版本進行偵錯
inline CMineSweeperDoc* CMineSweeperView::GetDocument() const
   { return reinterpret_cast<CMineSweeperDoc*>(m_pDocument); }
#endif
