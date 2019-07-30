#pragma once
#include "cgamectrl.h"
#include "CardsRank.h"
#include "Rule.h"

class CCardsApp :
	public CGameCtrl
{
public:
	CCardsRank* m_pRank;   //  所有的牌
	CRule* m_pRule;         //  规则

	list<Node*> m_lstCursor;   //  装光标的牌
	POINT pointMouseDown;   //  记录坐标
	POINT pointMouseMove;
public:
	DECLARE()
public:
	CCardsApp(void);
	~CCardsApp(void);
public:
	virtual void OnCreateGame();   // WM_CREATE
	virtual void OnGameDraw();     // WM_PAINT
	virtual void OnLButtonDown(POINT point);
	virtual void OnLButtonUp(POINT point);
	virtual void OnMouseMove(POINT point);
public:
	void ShowCursorCards(HDC hMemDC) ;  //  显示光标的牌
};

