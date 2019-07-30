#include "CardsRank.h"


CCardsRank::CCardsRank(int nCount):m_vecRank(nCount)   //  创建多少个链表
{
	m_pPoker = 0;    // 装几副扑克
	m_hBmpCardsBack = 0; //  牌的背面
	m_nBmpWndBack = 0;   // 窗口的背景图
}


CCardsRank::~CCardsRank(void)
{
	delete[] m_pPoker;

	::DeleteObject(m_nBmpWndBack);
	::DeleteObject(m_hBmpCardsBack);

	//  删除  所有链表中的节点
	for(size_t i=0;i<m_vecRank.size();i++)
	{
		list<Node*>::iterator ite = m_vecRank[i].begin();
		while(ite != m_vecRank[i].end())
		{
			delete (*ite);
			++ite;
		}
	}
}
void CCardsRank::ShowRank(HDC hMem, HINSTANCE hIns)
{
	//  显示窗口的背景图
	if(m_nBmpWndBack == 0)  //  加载默认的背景
		m_nBmpWndBack = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_WND_BACK));

	HDC hTempDC = ::CreateCompatibleDC(hMem);
	::SelectObject(hTempDC,m_nBmpWndBack);
	::BitBlt(hMem,0,0,850,600,hTempDC,0,0,SRCCOPY);
	::DeleteDC(hTempDC);

	//  有没有牌的背景图
	if(m_hBmpCardsBack == 0)
		m_hBmpCardsBack = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_CARDS_BACK));

	// 遍历链表  显示所有的牌
	for(size_t i=0;i<m_vecRank.size();i++)
	{
		list<Node*>::iterator ite = m_vecRank[i].begin();
		while(ite != m_vecRank[i].end())
		{
			//-------------------------------------------
			HDC hTempDC = ::CreateCompatibleDC(hMem);

			if((*ite)->bFlag == true)    //  选入正面图片
				::SelectObject(hTempDC,(*ite)->pCards->m_hBmpCards);
			else
				::SelectObject(hTempDC,m_hBmpCardsBack);

			::BitBlt(hMem,(*ite)->x,(*ite)->y,71,96,hTempDC,0,0,SRCCOPY);
			::DeleteDC(hTempDC);
			//-------------------------------------------
			++ite;
		}
	}
}