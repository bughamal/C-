#pragma once
#include "rule.h"
class CAAAARule :
	public CRule
{
public:
	DECLARE_DYNCREATE()
public:
	CAAAARule(void);
	~CAAAARule(void);
public:
	//  拿牌的规则
	virtual bool IsGetCardsRule(CCardsRank* pCardsRank, int nlstID, list<Node*>::iterator iteCursorPos);
	//  发牌
	virtual bool IsOpenCards(POINT point, CCardsRank* pCardsRank);
	virtual void OpenCards(CCardsRank* pCardsRank);
	//  接收牌的规则
	virtual bool IsReceiveCardsRule(POINT point, int nlstID, CCardsRank* pCardsRank, list<Node*>& lstCursorCards);
	//  更新坐标
	virtual void UpDatePos(CCardsRank* pCardsRank, int nlstID);
public:
	void DeleteLine(CCardsRank* pCardsRank, int nlstID);  //  删除  1-13
};

