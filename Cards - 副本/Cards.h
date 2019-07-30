#pragma once
#include "sys.h"

class CCards
{
public:
	CCards(void);
	~CCards(void);
public:
	HBITMAP m_hBmpCards;
	int m_nCardsColor;
	int m_nCardsNum;
public:
	void InitCards(HINSTANCE hIns, int nBmpID, int nColor, int nNum);
};

