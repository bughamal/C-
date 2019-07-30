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
		//  ���������ж����� ��  ���յĹ���
		if(this->IsReceiveCardsRule(point,i,pCardsRank,lstCursor) == true)
		{
			//  �� ��i������ ����
			pCardsRank->m_vecRank[i].splice(pCardsRank->m_vecRank[i].end(),lstCursor);
			//  ����λ��
			this->UpDatePos(pCardsRank,i);
			//  ����
			if(pCardsRank->m_vecRank[m_nGetCardsListID].empty() == false)
				pCardsRank->m_vecRank[m_nGetCardsListID].back()->bFlag = true;

			m_nGetCardsListID = -1;
			return true;  // ������
		}
	}
	return false;
}
void CRule::GetCards(POINT point, CCardsRank* pCardsRank, list<Node*>& lstCursor)
{
	// 1.  �ù�������  ���������ж�
	for(size_t i=0;i<pCardsRank->m_vecRank.size();i++)
	{
		// �����������
		list<Node*>::reverse_iterator rev_ite = pCardsRank->m_vecRank[i].rbegin();
		while(rev_ite != pCardsRank->m_vecRank[i].rend())
		{
			if(point.x >= (*rev_ite)->x && point.x <= (*rev_ite)->x+71
				&& point.y >= (*rev_ite)->y && point.y <= (*rev_ite)->y+96)
			{
				if((*rev_ite)->bFlag == true)  //   �ж��Ƿ�������
				{
					list<Node*>::iterator ite = --(rev_ite.base());
					//  2.  �ж��Ƿ���������������ƵĹ���
					if(this->IsGetCardsRule(pCardsRank,i,ite) == true)
					{
						//  3.  �ŵ� lstCursor ������  ��һ���ƶ�
						lstCursor.splice(lstCursor.end(),pCardsRank->m_vecRank[i],ite,pCardsRank->m_vecRank[i].end());
						//  ��¼���������±�
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