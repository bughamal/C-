#pragma once
#include "oobject.h"
#include "Poker.h"

class CCardsRank :
	public COObject
{
public:
	CPoker* m_pPoker;    // 装几副扑克
	HBITMAP m_hBmpCardsBack; //  牌的背面
	HBITMAP m_nBmpWndBack;   // 窗口的背景图
	vector<list<Node*>> m_vecRank;   // 多少链表
public: 
	CCardsRank(int nCount);
	~CCardsRank(void);
public:
	void ShowRank(HDC hMem, HINSTANCE hIns);   //  显示所有的牌
public:  
	virtual void InitCardsRank(HINSTANCE hIns)=0;   //  牌的初始化
};

