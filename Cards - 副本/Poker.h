#pragma once
#include "sys.h"
#include "Cards.h"
class CPoker
{
public:
	CPoker(void);
	~CPoker(void);
public:
	vector<CCards*> m_vecCards;   //  в╟  13 уееф
public:
	void InitPoker(HINSTANCE hIns, int nColor);
};

