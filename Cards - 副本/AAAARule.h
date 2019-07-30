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
	//  ���ƵĹ���
	virtual bool IsGetCardsRule(CCardsRank* pCardsRank, int nlstID, list<Node*>::iterator iteCursorPos);
	//  ����
	virtual bool IsOpenCards(POINT point, CCardsRank* pCardsRank);
	virtual void OpenCards(CCardsRank* pCardsRank);
	//  �����ƵĹ���
	virtual bool IsReceiveCardsRule(POINT point, int nlstID, CCardsRank* pCardsRank, list<Node*>& lstCursorCards);
	//  ��������
	virtual void UpDatePos(CCardsRank* pCardsRank, int nlstID);
public:
	void DeleteLine(CCardsRank* pCardsRank, int nlstID);  //  ɾ��  1-13
};

