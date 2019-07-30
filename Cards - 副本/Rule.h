#pragma once
#include "oobject.h"
#include "CardsRank.h"

class CRule :
	public COObject
{
public:
	int m_nGetCardsListID;  //  记录在哪个链表上拿起来的牌
public:
	CRule(void);
	~CRule(void);
public:
	bool ReceiveCards(POINT point, CCardsRank* pCardsRank, list<Node*>& lstCursor);
	void GetCards(POINT point, CCardsRank* pCardsRank, list<Node*>& lstCursor);
	void RevertCards(CCardsRank* pCardsRank, list<Node*>& lstCursor);
public:
	//  拿牌的规则
	virtual bool IsGetCardsRule(CCardsRank* pCardsRank, int nlstID, list<Node*>::iterator iteCursorPos) = 0;
	//  发牌
	virtual bool IsOpenCards(POINT point, CCardsRank* pCardsRank) = 0;
	virtual void OpenCards(CCardsRank* pCardsRank) = 0;
	//  接收牌的规则
	virtual bool IsReceiveCardsRule(POINT point, int nlstID, CCardsRank* pCardsRank, list<Node*>& lstCursorCards) = 0;
	//  更新坐标
	virtual void UpDatePos(CCardsRank* pCardsRank, int nlstID) = 0;
};

