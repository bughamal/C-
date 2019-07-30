#include "AAAARule.h"

IMPLEMENT_DYNCREATE(CAAAARule,CRule)
CAAAARule::CAAAARule(void)
{
}


CAAAARule::~CAAAARule(void)
{
}
//  拿牌的规则
bool CAAAARule::IsGetCardsRule(CCardsRank* pCardsRank, int nlstID, list<Node*>::iterator iteCursorPos)
{
	int num = (*iteCursorPos)->pCards->m_nCardsNum;
	//  判断  是不是连续的
	while(iteCursorPos != pCardsRank->m_vecRank[nlstID].end())
	{
		if((*iteCursorPos)->pCards->m_nCardsNum != num)  // 不连续
			return false;

		++iteCursorPos;
		--num;
	}

	return true;
}
//  发牌
bool CAAAARule::IsOpenCards(POINT point, CCardsRank* pCardsRank)
{
	//  最后一个链表是否有东西
	if(pCardsRank->m_vecRank[10].empty() == false)
	{
		//  判断 是否点击到最后一张牌上
		if(point.x >= pCardsRank->m_vecRank[10].back()->x && point.x <= pCardsRank->m_vecRank[10].back()->x+71
			&& point.y >= pCardsRank->m_vecRank[10].back()->y && point.y <= pCardsRank->m_vecRank[10].back()->y+96)
		{
			//  判断  前10个链表是否有空链表
			for(int i=0;i<10;i++)
			{
				if(pCardsRank->m_vecRank[i].empty() == true)
					return false;
			}
			return true;
		}
	}
	return false;
}
void CAAAARule::OpenCards(CCardsRank* pCardsRank)
{
	//  在  最后一个链表的  尾部 拿10个   分别放到每一个链表的尾部
	for(int i=0;i<10;i++)
	{
		//  修改属性
		pCardsRank->m_vecRank[10].back()->bFlag = true;
		pCardsRank->m_vecRank[10].back()->x = pCardsRank->m_vecRank[i].back()->x;
		pCardsRank->m_vecRank[10].back()->y = pCardsRank->m_vecRank[i].back()->y+20;
		//  把这个节点 添加到  pCardsRank->m_vecRank[i] 链表尾部
		pCardsRank->m_vecRank[i].push_back(pCardsRank->m_vecRank[10].back());
		pCardsRank->m_vecRank[10].pop_back();

		//  消除
		this->DeleteLine(pCardsRank,i);
	}
}
//  接收牌的规则
bool CAAAARule::IsReceiveCardsRule(POINT point, int nlstID, CCardsRank* pCardsRank, list<Node*>& lstCursorCards)
{
	//  前10个链表可以接收
	if(nlstID >= 0 && nlstID <= 9)
	{
		//  链表是空
		if(pCardsRank->m_vecRank[nlstID].empty() == true)
		{
			//  判断 坐标是否在一个 固定的矩形框的范围
			if(point.x >= 10+81*nlstID && point.x <= 10+81*nlstID+71
				&& point.y >= 10 && point.y <= 10+96)
			{
				return true;
			}
		}
		else
		{
			//  链表非空 判断  坐标 是不是在 nlstID 链表的为节点的范围 
			if(point.x >= pCardsRank->m_vecRank[nlstID].back()->x && point.x <= pCardsRank->m_vecRank[nlstID].back()->x+71
				&& point.y >= pCardsRank->m_vecRank[nlstID].back()->y && point.y <= pCardsRank->m_vecRank[nlstID].back()->y+96)
			{
				//  判断是否可以连接
				if(pCardsRank->m_vecRank[nlstID].back()->pCards->m_nCardsNum-1 == lstCursorCards.front()->pCards->m_nCardsNum)
				{
					return true;
				}
			}
		}
	}
	


	return false;
}
//  更新坐标
void CAAAARule::UpDatePos(CCardsRank* pCardsRank, int nlstID)
{
	int j=0;
	list<Node*>::iterator ite = pCardsRank->m_vecRank[nlstID].begin();
	while(ite != pCardsRank->m_vecRank[nlstID].end())
	{
		(*ite)->x = 10+81*nlstID;
		(*ite)->y = 10+j*20;
		++j;
		++ite;
	}

	//  消除
	this->DeleteLine(pCardsRank,nlstID);
}

void CAAAARule::DeleteLine(CCardsRank* pCardsRank, int nlstID)
{
	if(pCardsRank->m_vecRank[nlstID].size() >= 13 && pCardsRank->m_vecRank[nlstID].back()->pCards->m_nCardsNum == 1)
	{
		int num = 1;
		list<Node*>::reverse_iterator rev_ite = pCardsRank->m_vecRank[nlstID].rbegin();
		//  反向遍历链表
		for(int i=0;i<13;i++)
		{
			//  有背面的 可以结束
			if((*rev_ite)->bFlag == false)
				return;

			//  是不是连续
			if((*rev_ite)->pCards->m_nCardsNum != num)
				return;

			++rev_ite;
			++num;
		}

		//  都是正面 并且是连续
		list<Node*>::iterator ite = rev_ite.base();
		while(ite != pCardsRank->m_vecRank[nlstID].end())
		{
			delete(*ite);
			ite = pCardsRank->m_vecRank[nlstID].erase(ite);
		}
		//  最后一张牌翻过来
		if(pCardsRank->m_vecRank[nlstID].empty() == false)
			pCardsRank->m_vecRank[nlstID].back()->bFlag = true;
	}
}