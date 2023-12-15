
// VcadView.h: CVcadView 类的接口
//

#pragma once


class CVcadView : public CView
{
protected: // 仅从序列化创建
	CVcadView() noexcept;
	DECLARE_DYNCREATE(CVcadView)

// 特性
public:
	CVcadDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CVcadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	void SetPixel(int x, int y, int color);
	int GetPixel(int x, int y);
	void DDALine(int x0, int y0, int x1, int y1, int color);
	void BresenhamLine(int x0, int y0, int x1, int y1, int color);
	void BresenhamCircle(int x0, int y0, int R, int color);
	void MidEllipse(int a, int b, int color);
	void Star(int R);
	int encode(int x, int y);
	void CohenSutherLand(int x0, int y0, int x1, int y1);
	void ScanFill();
	afx_msg void OnDDALine();
	afx_msg void OnBresenhamLine();
	afx_msg void OnBresenhamCircle();
	afx_msg void OnMidEllipse();
	afx_msg void OnStar();
	afx_msg void OnCohenSutherLandClip();
	afx_msg void OnScanFill();
};

#ifndef _DEBUG  // VcadView.cpp 中的调试版本
inline CVcadDoc* CVcadView::GetDocument() const
   { return reinterpret_cast<CVcadDoc*>(m_pDocument); }
#endif

