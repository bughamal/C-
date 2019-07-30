#include "CardsRank.h"


CCardsRank::CCardsRank(int nCount):m_vecRank(nCount)   //  �������ٸ�����
{
	m_pPoker = 0;    // װ�����˿�
	m_hBmpCardsBack = 0; //  �Ƶı���
	m_nBmpWndBack = 0;   // ���ڵı���ͼ
}


CCardsRank::~CCardsRank(void)
{
	delete[] m_pPoker;

	::DeleteObject(m_nBmpWndBack);
	::DeleteObject(m_hBmpCardsBack);

	//  ɾ��  ���������еĽڵ�
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
	//  ��ʾ���ڵı���ͼ
	if(m_nBmpWndBack == 0)  //  ����Ĭ�ϵı���
		m_nBmpWndBack = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_WND_BACK));

	HDC hTempDC = ::CreateCompatibleDC(hMem);
	::SelectObject(hTempDC,m_nBmpWndBack);
	::BitBlt(hMem,0,0,850,600,hTempDC,0,0,SRCCOPY);
	::DeleteDC(hTempDC);

	//  ��û���Ƶı���ͼ
	if(m_hBmpCardsBack == 0)
		m_hBmpCardsBack = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_CARDS_BACK));

	// ��������  ��ʾ���е���
	for(size_t i=0;i<m_vecRank.size();i++)
	{
		list<Node*>::iterator ite = m_vecRank[i].begin();
		while(ite != m_vecRank[i].end())
		{
			//-------------------------------------------
			HDC hTempDC = ::CreateCompatibleDC(hMem);

			if((*ite)->bFlag == true)    //  ѡ������ͼƬ
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