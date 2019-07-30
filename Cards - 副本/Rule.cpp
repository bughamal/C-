#include "Rule.h"


CRule::CRule(void)
{
	m_nGetCardsListID = -1;
}


CRule::~CRule(void)
{
}
bool CRule::ReceiveCards(POINT point, CCardsRank* pCardsRank, list<Node*>& lstCursor)
{
	for(size_t i=0;i<pCardsRank->m_vecRank.size();i++)
	{
		//  留给子类判断坐标 和  接收的规则
		if(this->IsReceiveCardsRule(point,i,pCardsRank,lstCursor) == true)
		{
			//  和 第i个链表 连接
			pCardsRank->m_vecRank[i].splice(pCardsRank->m_vecRank[i].end(),lstCursor);
			//  更新位置
			this->UpDatePos(pCardsRank,i);
			//  翻牌
			if(pCardsRank->m_vecRank[m_nGetCardsListID].empty() == false)
				pCardsRank->m_vecRank[m_nGetCardsListID].back()->bFlag = true;

			m_nGetCardsListID = -1;
			return true;  // 接收了
		}
	}
	return false;
}
void CRule::GetCards(POINT point, CCardsRank* pCardsRank, list<Node*>& lstCursor)
{
	// 1.  用光标的坐标  遍历链表判断
	for(size_t i=0;i<pCardsRank->m_vecRank.size();i++)
	{
		// 反向遍历链表
		list<Node*>::reverse_iterator rev_ite = pCardsRank->m_vecRank[i].rbegin();
		while(rev_ite != pCardsRank->m_vecRank[i].rend())
		{
			if(point.x >= (*rev_ite)->x && point.x <= (*rev_ite)->x+71
				&& point.y >= (*rev_ite)->y && point.y <= (*rev_ite)->y+96)
			{
				if((*rev_ite)->bFlag == true)  //   判断是否是正面
				{
					list<Node*>::iterator ite = --(rev_ite.base());
					//  2.  判断是否可以拿起来，拿牌的规则
					if(this->IsGetCardsRule(pCardsRank,i,ite) == true)
					{
						//  3.  放到 lstCursor 链表里  和一起移动
						lstCursor.splice(lstCursor.end(),pCardsRank->m_vecRank[i],ite,pCardsRank->m_vecRank[i].end());
						//  记录这个链表的下标
						m_nGetCardsListID = i;
					}
				}
				return;
			}
			rev_ite++;
		}
	}
}
void CRule::RevertCards(CCardsRank* pCardsRank, list<Node*>& lstCursor)
{
	if(m_nGetCardsListID != -1)
	{
		pCardsRank->m_vecRank[m_nGetCardsListID].splice(pCardsRank->m_vecRank[m_nGetCardsListID].end(),lstCursor);
		m_nGetCardsListID = -1;
	}
}