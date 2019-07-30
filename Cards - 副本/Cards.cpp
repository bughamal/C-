#include "Cards.h"


CCards::CCards(void)
{
	m_hBmpCards = 0;
	m_nCardsColor = 0;
	m_nCardsNum = 0;
}


CCards::~CCards(void)
{
	::DeleteObject(m_hBmpCards);
	m_hBmpCards = NULL;
}
void CCards::InitCards(HINSTANCE hIns, int nBmpID, int nColor, int nNum)
{
	m_hBmpCards = ::LoadBitmap(hIns,MAKEINTRESOURCE(nBmpID));
	m_nCardsColor = nColor;
	m_nCardsNum = nNum;
}