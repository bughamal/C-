#include "CardsApp.h"

IMPLEMENT(CCardsApp)
CCardsApp::CCardsApp(void)
{
	m_pRank = 0;
	m_pRule = 0;
}


CCardsApp::~CCardsApp(void)
{
	delete m_pRank;
	m_pRank = 0;
	delete m_pRule;
	m_pRule = 0;
	

	list<Node*>::iterator ite = m_lstCursor.begin();
	while(ite != m_lstCursor.end())
	{
		delete (*ite);
		++ite;
	}
}
void CCardsApp::OnCreateGame()   // WM_CREATE
{
	m_pRank = (CCardsRank*)COObject::Create("CCardsRank");   //  ����һ�����е�  ����Ķ���
	m_pRule = (CRule*)COObject::Create("CRule");

	if(m_pRank == NULL || m_pRule == NULL)
		::MessageBox(NULL,"��Ϸ��ʼ��ʧ��","��ʾ",MB_OK);
	else
		m_pRank->InitCardsRank(m_hIns);                   //  ��ʼ����Ϸ
}
void CCardsApp::OnGameDraw()// WM_PAINT
{
	HDC dc = ::GetDC(m_hMainWnd);
	HDC hMemDC = ::CreateCompatibleDC(dc);
	HBITMAP hBitmap = ::CreateCompatibleBitmap(dc,850,600);
	::SelectObject(hMemDC,hBitmap);

	//--------------------------------------------------
	if(m_pRank != NULL)
		m_pRank->ShowRank(hMemDC,m_hIns);
	this->ShowCursorCards(hMemDC);
	//-------------------------------------------------
	::BitBlt(dc,0,0,850,600,hMemDC,0,0,SRCCOPY);
	::DeleteObject(hBitmap);
	::DeleteDC(hMemDC);
	::ReleaseDC(m_hMainWnd,dc);
}
void CCardsApp::ShowCursorCards(HDC hMemDC)
{
	//  ����һ���ƶ�����
	int X = pointMouseMove.x - pointMouseDown.x;
	int Y = pointMouseMove.y - pointMouseDown.y;

	list<Node*>::iterator ite = m_lstCursor.begin();
	while(ite != m_lstCursor.end())
	{
		//----------------------------------------
		HDC hTempDC = ::CreateCompatibleDC(hMemDC);
		::SelectObject(hTempDC,(*ite)->pCards->m_hBmpCards);
		::BitBlt(hMemDC,(*ite)->x+X,(*ite)->y+Y,71,96,hTempDC,0,0,SRCCOPY);
		::DeleteDC(hTempDC);
		//----------------------------------------
		++ite;
	}
}
void CCardsApp::OnLButtonDown(POINT point)
{
	pointMouseDown = point;
	//  ����
	if(m_pRule != NULL)
	{
		m_pRule->GetCards(point,m_pRank,m_lstCursor);
		this->OnGameDraw();
	}
}
void CCardsApp::OnLButtonUp(POINT point)
{
	if(m_pRule != NULL)
	{
		if(m_lstCursor.empty() == true)  // ���û����
		{
			if(m_pRule->IsOpenCards(point,m_pRank) == true)   //  �Ƿ���
			{
				m_pRule->OpenCards(m_pRank);
			}
		}
		else   //  �������
		{
			//  �����ܽ���
			if(m_pRule->ReceiveCards(point,m_pRank,m_lstCursor) == false)
			{
				//  �ص�ԭ����λ��
				m_pRule->RevertCards(m_pRank,m_lstCursor);
			}
		}

		this->OnGameDraw();
	}
}
void CCardsApp::OnMouseMove(POINT point)
{
	pointMouseMove = point;
	this->OnGameDraw();
}