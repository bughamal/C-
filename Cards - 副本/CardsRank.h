#pragma once
#include "oobject.h"
#include "Poker.h"

class CCardsRank :
	public COObject
{
public:
	CPoker* m_pPoker;    // װ�����˿�
	HBITMAP m_hBmpCardsBack; //  �Ƶı���
	HBITMAP m_nBmpWndBack;   // ���ڵı���ͼ
	vector<list<Node*>> m_vecRank;   // ��������
public: 
	CCardsRank(int nCount);
	~CCardsRank(void);
public:
	void ShowRank(HDC hMem, HINSTANCE hIns);   //  ��ʾ���е���
public:  
	virtual void InitCardsRank(HINSTANCE hIns)=0;   //  �Ƶĳ�ʼ��
};

