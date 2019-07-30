#pragma once
#include "cgamectrl.h"
#include "CardsRank.h"
#include "Rule.h"

class CCardsApp :
	public CGameCtrl
{
public:
	CCardsRank* m_pRank;   //  ���е���
	CRule* m_pRule;         //  ����

	list<Node*> m_lstCursor;   //  װ������
	POINT pointMouseDown;   //  ��¼����
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
	void ShowCursorCards(HDC hMemDC) ;  //  ��ʾ������
};

