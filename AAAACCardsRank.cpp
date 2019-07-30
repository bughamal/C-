#include "AAAACCardsRank.h"

IMPLEMENT_DYNCREATE(CAAAACCardsRank,CCardsRank)
CAAAACCardsRank::CAAAACCardsRank(void):CCardsRank(11)   //  创建11个链表
{
}


CAAAACCardsRank::~CAAAACCardsRank(void)
{
}
void CAAAACCardsRank::InitCardsRank(HINSTANCE hIns)
{
	//  0.  是否加载 背景图

	//-----------------------------------------------------------
	//  1.  创建 8个 扑克
	m_pPoker = new CPoker[8];
	for(int i=0;i<8;i++)
		m_pPoker[i].InitPoker(hIns,Cards_Black);   //  初始化扑克的对象

	//  1.1 把  8个 扑克里牌  放到一个大的数组里  洗牌
	int j=0;  //  第几张牌
	int k=0;  //  第几副扑克
	vector<CCards*> vec(104);
	for(int i=0;i<104;i++)
	{
		if(j == 13)
		{
			k++;
			j=0;
		}
		vec[i] = m_pPoker[k].m_vecCards[j++];
	}
	::random_shuffle(vec.begin(),vec.end());
	//-----------------------------------------------------------


	//-----------------------------------------------------------
	// 2.  把 vec里的牌  放到  m_vecRank 链表里
	// 2.1  创建前4个链表
	int n = 0;
	for(int i=0;i<4;i++)   //  i代表第几个链表
	{
		for(int j=0;j<6;j++)  //  j 代表  第i个链表中的 第几章牌
		{
			Node* node = new Node;
			node->bFlag = false;   // 背面
			node->pCards = vec[n++];   //  装一张牌
			node->x = 10+81*i;
			node->y = 10+20*j;

			m_vecRank[i].push_back(node);
		}
		//  最后一张牌是 正面的
		m_vecRank[i].back()->bFlag = true;
	}
	// 2.2  创建后6个
	for(int i=4;i<10;i++)   //  i代表第几个链表
	{
		for(int j=0;j<5;j++)  //  j 代表  第i个链表中的 第几章牌
		{
			Node* node = new Node;
			node->bFlag = false;   // 背面
			node->pCards = vec[n++];   //  装一张牌
			node->x = 10+81*i;
			node->y = 10+20*j;

			m_vecRank[i].push_back(node);
		}
		//  最后一张牌是 正面的
		m_vecRank[i].back()->bFlag = true;
	}
	//  2.3  把 剩余的 50张牌 放到  最后一个链表里
	for(int j=49;j>=0;j--)  //  j 代表  第i个链表中的 第几章牌
	{
		Node* node = new Node;
		node->bFlag = false;   // 背面
		node->pCards = vec[n++];   //  装一张牌
		node->x = 500+3*j;
		node->y = 500;

		m_vecRank[10].push_back(node);
	}
	//-------------------------------------------------------------
}