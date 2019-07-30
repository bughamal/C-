#include "Poker.h"


CPoker::CPoker(void):m_vecCards(13)
{
}


CPoker::~CPoker(void)
{
	//  删除  13 张牌
	for(int i=0;i<13;i++)
		delete m_vecCards[i];
}
void CPoker::InitPoker(HINSTANCE hIns, int nColor)
{
	//  创建  13张牌
	for(int i=0;i<13;i++)
	{
		m_vecCards[i] = new CCards;
		m_vecCards[i]->InitCards(hIns,IDB_BITMAP1+nColor*13+i,nColor,i+1);
	}
}
