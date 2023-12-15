
// VcadView.cpp: CVcadView 类的实现
//

#include "pch.h"
#include"algorithm"
#include "framework.h"
#include"vector"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Vcad.h"
#endif

#include "VcadDoc.h"
#include "VcadView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVcadView

IMPLEMENT_DYNCREATE(CVcadView, CView)

BEGIN_MESSAGE_MAP(CVcadView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CVcadView::OnDDALine)
	ON_COMMAND(ID_32772, &CVcadView::OnBresenhamLine)
	ON_COMMAND(ID_32773, &CVcadView::OnBresenhamCircle)
	ON_COMMAND(ID_32774, &CVcadView::OnMidEllipse)
	ON_COMMAND(ID_32775, &CVcadView::OnStar)
	ON_COMMAND(ID_32777, &CVcadView::OnCohenSutherLandClip)
	ON_COMMAND(ID_32776, &CVcadView::OnScanFill)
END_MESSAGE_MAP()

// CVcadView 构造/析构

CVcadView::CVcadView() noexcept
{
	// TODO: 在此处添加构造代码

}

CVcadView::~CVcadView()
{
}

BOOL CVcadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CVcadView 绘图

void CVcadView::OnDraw(CDC* pDC)
{
	CVcadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	for (int i = 0; i < 1000; i++)
	{
		pDC->MoveTo(0, i * 10);
		pDC->LineTo(6000, i * 10);
	}
	for (int i = 0; i < 1000; i++)
	{
		pDC->MoveTo(i * 10, 0);
		pDC->LineTo(i * 10, 6000);
	}

}


// CVcadView 打印

BOOL CVcadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CVcadView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CVcadView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CVcadView 诊断

#ifdef _DEBUG
void CVcadView::AssertValid() const
{
	CView::AssertValid();
}

void CVcadView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVcadDoc* CVcadView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVcadDoc)));
	return (CVcadDoc*)m_pDocument;
}
#endif //_DEBUG


// CVcadView 消息处理程序


void CVcadView::SetPixel(int x, int y, int color)
{
	// TODO: 在此处添加实现代码.
	CClientDC dc(this);
	CBrush newbrush;
	newbrush.CreateSolidBrush(color);
	CBrush* oldbrush = dc.SelectObject(&newbrush);
	dc.Rectangle(x * 10, y * 10, x * 10 + 10, y * 10 + 10);//填充矩形
	dc.SelectObject(oldbrush);
	return;
}


int CVcadView::GetPixel(int x, int y)
{
	// TODO: 在此处添加实现代码.
	CClientDC dc(this);
	int color = dc.GetPixel(x * 10 + 5, y * 10 + 5);
	return color;
}


void CVcadView::DDALine(int x0, int y0, int x1, int y1, int color)
{
	// TODO: 在此处添加实现代码.
	int x;
	float dx, dy, y, k;
	dx = x1 - x0, dy = y1 - y0;
	k = dy / dx, y = y0;
	for (x = x0; x <= x1; x++)
	{
		SetPixel(x, int(y + 0.5), color);
		y = y + k;
	}
}
void CVcadView::OnDDALine()
{
	// TODO: 在此添加命令处理程序代码
	int color;
	color = RGB(255, 0, 0);
	int x0, x1, y0, y1;
	x0 = 0; y0 = 0;
	x1 = 70; y1 = 100;
	DDALine(x0, y0, x1, y1, color);
}

void CVcadView::BresenhamLine(int x0, int y0, int x1, int y1, int color)
{
	// TODO: 在此处添加实现代码.
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int e = dx - dy;
	while (true)
	{
		// 在这里描绘当前像素 (x1, y1)
		SetPixel(x0, y0, color);
		if (x0 == x1 && y0 == y1) {
			break;
		}
		int e2 = 2 * e;
		if (e2 > -dy) {
			e -= dy;
			x0 += sx;
		}
		if (e2 < dx) {
			e += dx;
			y0 += sy;
		}
	}
}
void CVcadView::OnBresenhamLine()
{
	// TODO: 在此添加命令处理程序代码
	int color;
	color = RGB(255, 0, 0);
	int x0, x1, y0, y1;
	x0 = 50; y0 = 20;
	x1 = 10; y1 = 40;
	BresenhamLine(x0, y0, x1, y1, color);
}

void CVcadView::BresenhamCircle(int x0, int y0, int R, int color)
{
	// TODO: 在此处添加实现代码.
	int x, y, delta, delta1, delta2, direction;
	x = 0; y = R;
	delta = 2 * (1 - R);

	while (y >= 0)
	{
		SetPixel(x + x0, y + y0, color);
		SetPixel(-x + x0, y + y0, color);
		SetPixel(-x + x0, -y + y0, color);
		SetPixel(x + x0, -y + y0, color);
		if (delta < 0)
		{
			delta1 = 2 * (delta + y) - 1;
			if (delta1 <= 0)direction = 1;
			else direction = 2;
		}
		else if (delta > 0)
		{
			delta2 = 2 * (delta - x) - 1;
			if (delta2 <= 0)direction = 2;
			else direction = 3;
		}
		else direction = 2;
		switch (direction)
		{
		case 1:x++; delta += 2 * x + 1;
			break;
		case 2:x++; y--; delta += 2 * (x - y + 1);
			break;
		case 3:y--; delta += (-2 * y + 1);
			break;
		}/*switch*/
	}/*while*/
/*Bresenham_Circle*/
}
void CVcadView::OnBresenhamCircle()
{
	// TODO: 在此添加命令处理程序代码
	int x0, y0, r;
	int color;
	r = 40;
	color = RGB(255, 0, 0);
	x0 = 120; y0 = 60;
	BresenhamCircle(x0, y0, r, color);
}

void CVcadView::MidEllipse(int a, int b, int color)
{
	// TODO: 在此处添加实现代码.
	int x, y;
	float d1, d2;
	x = 0; y = b;
	d1 = b * b + a * a * (-b + 0.25);
	SetPixel(x + 120, y + 60, color);
	SetPixel(-x + 120, y + 60, color);
	SetPixel(x + 120, -y + 60, color);
	SetPixel(-x + 120, -y + 60, color);
	while (b * b * (x + 1) < a * a * (y - 0.5))
	{
		if (d1 < 0)
		{
			d1 += b * b * (2 * x + 3);
			x++;
		}
		else
		{
			d1 += (b * b * (2 * x + 3) + a * a * (-2 * y + 3));
			x++; y--;
		}
		SetPixel(x + 120, y + 60, color);
		SetPixel(-x + 120, y + 60, color);
		SetPixel(x + 120, -y + 60, color);
		SetPixel(-x + 120, -y + 60, color);
	}//上半部分
	d2 = sqrt(b * (x + 0.25)) + sqrt(a * (y - 0.5)) - sqrt(a * b);
	while (y > 0)
	{
		if (d2 < 0)
		{
			d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
			x++; y--;
		}
		else
		{
			d2 += a * a * (-2 * y + 3);
			y--;
		}
		SetPixel(x + 120, y + 60, color);
		SetPixel(-x + 120, y + 60, color);
		SetPixel(x + 120, -y + 60, color);
		SetPixel(-x + 120, -y + 60, color);
	}
}
void CVcadView::OnMidEllipse()
{
	// TODO: 在此添加命令处理程序代码
	int a, b;
	int color;
	a = 70; b = 40;
	color = RGB(255, 0, 0);
	MidEllipse(a, b, color);
}

void CVcadView::Star(int R)
{
	// TODO: 在此处添加实现代码.
	int x, y;
	int color;
	double rad = 3.1415926 / 180;                    //每度的弧度值
	double r = R * sin(18 * rad) / cos(36 * rad);    //五角星短轴的长度
	CPoint pts[5];
	CPoint ptss[5];
	CDC* pDC = GetDC();
	color = RGB(255, 0, 0);
	for (int i = 0; i < 5; i++) {
		pts[i].x = (long)(120 - (R * cos((90 + i * 72) * rad)));
		pts[i].y = (long)(60 - (R * sin((90 + i * 72) * rad)));
	}
	for (int i = 0; i < 5; i++) {
		ptss[i].x = (long)(120 - (r * cos((90 + 36 + i * 72) * rad)));
		ptss[i].y = (long)(60 - (r * sin((90 + 36 + i * 72) * rad)));
	}
	for (int h = 0; h < 5; h++)
	{
		BresenhamLine(pts[h].x, pts[h].y, ptss[h].x, ptss[h].y, color);
	}
	for (int f = 0; f < 4; f++)
	{
		BresenhamLine(ptss[f].x, ptss[f].y, pts[f + 1].x, pts[f + 1].y, color);
		BresenhamLine(ptss[4].x, ptss[4].y, pts[0].x, pts[0].y, color);
	}
}
void CVcadView::OnStar()
{
	// TODO: 在此添加命令处理程序代码
	double R;
	COLORREF color;
	R = 40;
	color = RGB(255, 0, 0);
	Star(R);
}
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8
const int XL = 90;
const int XR = 150;
const int YB = 34;
const int YT = 86;

int CVcadView::encode(int x, int y)
{
	// TODO: 在此处添加实现代码.
	int c = 0;
	if (x < XL)  c = c | LEFT;
	else if (x > XR)  c = c | RIGHT;
	if (y < YB)  c = c | BOTTOM;
	else if (y > YT)  c = c | TOP;
	return c;
}
void CVcadView::CohenSutherLand(int x0, int y0, int x1, int y1)
{
	// TODO: 在此处添加实现代码.
	int code1, code2, code;
	int x, y;
	int color = RGB(0, 0, 255);
	for (int i = 0; i < 5; i++)
	{
		//编码两个端点
		code1 = encode(x0, y0);
		code2 = encode(x1, y1);
		//持续迭代至两个编码都为0(在裁剪窗口内）
		while (code1 != 0 || code2 != 0)//只有两个端点全在中心区内（直接保留完整线端，否则进入循环）
		{
			if (code1 & code2) //说明两个端点全在非中心区的区域，直接不画）
				return;
			if (code1 != 0) //如果端点1不在中心区
				code = code1; //使端点1与边界交换
			else  //说明端点1在中心区，端点2不在中心区
				code = code2;  //使端点2与边界交点交换

			if (code & LEFT)  //线端与左边界相交，条件成立，点必定在左边界左侧
			{
				x = XL; //求为与左边界相交的点的x值
				y = y0 + (y1 - y0) * (XL - x0) / (x1 - x0); //斜率((y1 - y0)/(x1 - x0))
			}
			else if (code & RIGHT)//线段与右边界相交，条件成立，点必定在右边界右侧
			{
				x = XR; //求出右边界的交点x值
				y = y0 + (y1 - y0) * (XR - x0) / (x1 - x0);
			}
			else if (code & BOTTOM) //线段与下边界相交
			{
				y = YB;
				x = x0 + (x1 - x0) * (YB - y0) / (y1 - y0);
			}
			else if (code & TOP) //线段与上边界相交
			{
				y = YT;
				x = x0 + (x1 - x0) * (YT - y0) / (y1 - y0);
			}

			//将端点与边界交点转换
			if (code == code1)
			{
				x0 = x;
				y0 = y;
				code1 = encode(x0, y0);//如果交换成功，新编码为0000
			}
			else
			{
				x1 = x;
				y1 = y;
				code2 = encode(x1, y1); //交换成功，新编码为0000
			}
		}
		BresenhamLine(x0, y0, x1, y1, color);
	}
}
void CVcadView::OnCohenSutherLandClip()
{
	// TODO: 在此添加命令处理程序代码
	int x, y;
	int color;
	int i = 0;
	int R = 40;
	int a = 90, b = 34;
	double rad = 3.1415926 / 180;                    //每度的弧度值
	double r = R * sin(18 * rad) / cos(36 * rad);    //五角星短轴的长度
	CPoint pts[5];
	CPoint ptss[5];
	CDC* pDC = GetDC();
	color = RGB(0, 255, 0);
	for (int i = 0; i <= 60; i++) {
		for (int j = 0; j < 52; j++) {
			SetPixel(a + i, b, color);
			SetPixel(a, b + j, color);
			SetPixel(a + i, b + 52, color);
			SetPixel(a + 60, b + j, color);
		}
	}//定义矩形
	for (int i = 0; i < 5; i++) {
		pts[i].x = (long)(120 - (R * cos((90 + i * 72) * rad)));
		pts[i].y = (long)(60 - (R * sin((90 + i * 72) * rad)));
	}
	for (int i = 0; i < 5; i++) {
		ptss[i].x = (long)(120 - (r * cos((90 + 36 + i * 72) * rad)));
		ptss[i].y = (long)(60 - (r * sin((90 + 36 + i * 72) * rad)));
	}
	for (int h = 0; h < 5; h++)
	{
		CVcadView::CohenSutherLand(pts[h].x, pts[h].y, ptss[h].x, ptss[h].y);
	}
	for (int f = 0; f < 4; f++)
	{
		CVcadView::CohenSutherLand(ptss[f].x, ptss[f].y, pts[f + 1].x, pts[f + 1].y);
		CVcadView::CohenSutherLand(pts[0].x, pts[0].y, ptss[4].x, ptss[4].y);
	}
}

void CVcadView::ScanFill()
{
	// TODO: 在此处添加实现代码.
	CPoint pts[50];
	CDC* pDC = GetDC();
	pts[0].x = 116; pts[0].y = 34;
	pts[1].x = 123; pts[1].y = 34;
	pts[2].x = 128; pts[2].y = 48;
	pts[3].x = 149; pts[3].y = 48;
	pts[4].x = 149; pts[4].y = 52;
	pts[5].x = 133; pts[5].y = 64;
	pts[6].x = 141; pts[6].y = 86;
	pts[7].x = 135; pts[7].y = 86;
	pts[8].x = 119; pts[8].y = 74;
	pts[9].x = 103; pts[9].y = 86;
	pts[10].x = 99; pts[10].y = 86;
	pts[11].x = 106; pts[11].y = 65;
	pts[12].x = 91; pts[12].y = 53;
	pts[13].x = 91; pts[13].y = 48;
	pts[14].x = 111; pts[14].y = 48;
	int i, y;
	int color = RGB(255, 255, 0);

	//扫描线填充
	for (y = 34; y <= 86; ++y)
	{
		std::vector<int> xjs;//动态数组xjs，可随时调整大小

		//寻找与扫描线的交点
		for (i = 0; i <= 15; i++)
		{
			int next = (i + 1) % 15;
			int y0 = pts[i].y, y1 = pts[next].y;
			if ((y0 <= y && y < y1) || (y1 <= y && y < y0))
			{
				if (y1 - y0 != 0)
				{
					int xj = pts[i].x + (y - y0) * (pts[next].x - pts[i].x) / (y1 - y0);
					xjs.push_back(xj);//将xj添加到xjs容器的末尾
				}
			}
		}
		std::sort(xjs.begin(), xjs.end());//对焦点进行排序

		//填充两个交点之间的像素
		for (size_t i = 0; i < xjs.size(); i += 2)
		{
			int x0 = xjs[i], x1 = xjs[i + 1];
			BresenhamLine(x0, y, x1, y, color);
		}
	}
}
void CVcadView::OnScanFill()
{
	// TODO: 在此添加命令处理程序代码
	ScanFill();
}
