#pragma once
#include "sys.h"
#include "Cards.h"
class CPoker
{
public:
	CPoker(void);
	~CPoker(void);
public:
	vector<CCards*> m_vecCards;   //  װ  13 ����
public:
	void InitPoker(HINSTANCE hIns, int nColor);
};

