#include "AAAARule.h"

IMPLEMENT_DYNCREATE(CAAAARule,CRule)
CAAAARule::CAAAARule(void)
{
}


CAAAARule::~CAAAARule(void)
{
}
//  ���ƵĹ���
bool CAAAARule::IsGetCardsRule(CCardsRank* pCardsRank, int nlstID, list<Node*>::iterator iteCursorPos)
{
	int num = (*iteCursorPos)->pCards->m_nCardsNum;
	//  �ж�  �ǲ���������
	while(iteCursorPos != pCardsRank->m_vecRank[nlstID].end())
	{
		if((*iteCursorPos)->pCards->m_nCardsNum != num)  // ������
			return false;

		++iteCursorPos;
		--num;
	}

	return true;
}
//  ����
bool CAAAARule::IsOpenCards(POINT point, CCardsRank* pCardsRank)
{
	//  ���һ�������Ƿ��ж���
	if(pCardsRank->m_vecRank[10].empty() == false)
	{
		//  �ж� �Ƿ��������һ������
		if(point.x >= pCardsRank->m_vecRank[10].back()->x && point.x <= pCardsRank->m_vecRank[10].back()->x+71
			&& point.y >= pCardsRank->m_vecRank[10].back()->y && point.y <= pCardsRank->m_vecRank[10].back()->y+96)
		{
			//  �ж�  ǰ10�������Ƿ��п�����
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
	//  ��  ���һ�������  β�� ��10��   �ֱ�ŵ�ÿһ�������β��
	for(int i=0;i<10;i++)
	{
		//  �޸�����
		pCardsRank->m_vecRank[10].back()->bFlag = true;
		pCardsRank->m_vecRank[10].back()->x = pCardsRank->m_vecRank[i].back()->x;
		pCardsRank->m_vecRank[10].back()->y = pCardsRank->m_vecRank[i].back()->y+20;
		//  ������ڵ� ��ӵ�  pCardsRank->m_vecRank[i] ����β��
		pCardsRank->m_vecRank[i].push_back(pCardsRank->m_vecRank[10].back());
		pCardsRank->m_vecRank[10].pop_back();

		//  ����
		this->DeleteLine(pCardsRank,i);
	}
}
//  �����ƵĹ���
bool CAAAARule::IsReceiveCardsRule(POINT point, int nlstID, CCardsRank* pCardsRank, list<Node*>& lstCursorCards)
{
	//  ǰ10��������Խ���
	if(nlstID >= 0 && nlstID <= 9)
	{
		//  �����ǿ�
		if(pCardsRank->m_vecRank[nlstID].empty() == true)
		{
			//  �ж� �����Ƿ���һ�� �̶��ľ��ο�ķ�Χ
			if(point.x >= 10+81*nlstID && point.x <= 10+81*nlstID+71
				&& point.y >= 10 && point.y <= 10+96)
			{
				return true;
			}
		}
		else
		{
			//  ����ǿ� �ж�  ���� �ǲ����� nlstID �����Ϊ�ڵ�ķ�Χ 
			if(point.x >= pCardsRank->m_vecRank[nlstID].back()->x && point.x <= pCardsRank->m_vecRank[nlstID].back()->x+71
				&& point.y >= pCardsRank->m_vecRank[nlstID].back()->y && point.y <= pCardsRank->m_vecRank[nlstID].back()->y+96)
			{
				//  �ж��Ƿ��������
				if(pCardsRank->m_vecRank[nlstID].back()->pCards->m_nCardsNum-1 == lstCursorCards.front()->pCards->m_nCardsNum)
				{
					return true;
				}
			}
		}
	}
	


	return false;
}
//  ��������
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

	//  ����
	this->DeleteLine(pCardsRank,nlstID);
}

void CAAAARule::DeleteLine(CCardsRank* pCardsRank, int nlstID)
{
	if(pCardsRank->m_vecRank[nlstID].size() >= 13 && pCardsRank->m_vecRank[nlstID].back()->pCards->m_nCardsNum == 1)
	{
		int num = 1;
		list<Node*>::reverse_iterator rev_ite = pCardsRank->m_vecRank[nlstID].rbegin();
		//  �����������
		for(int i=0;i<13;i++)
		{
			//  �б���� ���Խ���
			if((*rev_ite)->bFlag == false)
				return;

			//  �ǲ�������
			if((*rev_ite)->pCards->m_nCardsNum != num)
				return;

			++rev_ite;
			++num;
		}

		//  �������� ����������
		list<Node*>::iterator ite = rev_ite.base();
		while(ite != pCardsRank->m_vecRank[nlstID].end())
		{
			delete(*ite);
			ite = pCardsRank->m_vecRank[nlstID].erase(ite);
		}
		//  ���һ���Ʒ�����
		if(pCardsRank->m_vecRank[nlstID].empty() == false)
			pCardsRank->m_vecRank[nlstID].back()->bFlag = true;
	}
}