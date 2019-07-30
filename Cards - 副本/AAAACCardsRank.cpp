#include "AAAACCardsRank.h"

IMPLEMENT_DYNCREATE(CAAAACCardsRank,CCardsRank)
CAAAACCardsRank::CAAAACCardsRank(void):CCardsRank(11)   //  ����11������
{
}


CAAAACCardsRank::~CAAAACCardsRank(void)
{
}
void CAAAACCardsRank::InitCardsRank(HINSTANCE hIns)
{
	//  0.  �Ƿ���� ����ͼ

	//-----------------------------------------------------------
	//  1.  ���� 8�� �˿�
	m_pPoker = new CPoker[8];
	for(int i=0;i<8;i++)
		m_pPoker[i].InitPoker(hIns,Cards_Black);   //  ��ʼ���˿˵Ķ���

	//  1.1 ��  8�� �˿�����  �ŵ�һ�����������  ϴ��
	int j=0;  //  �ڼ�����
	int k=0;  //  �ڼ����˿�
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
	// 2.  �� vec�����  �ŵ�  m_vecRank ������
	// 2.1  ����ǰ4������
	int n = 0;
	for(int i=0;i<4;i++)   //  i����ڼ�������
	{
		for(int j=0;j<6;j++)  //  j ����  ��i�������е� �ڼ�����
		{
			Node* node = new Node;
			node->bFlag = false;   // ����
			node->pCards = vec[n++];   //  װһ����
			node->x = 10+81*i;
			node->y = 10+20*j;

			m_vecRank[i].push_back(node);
		}
		//  ���һ������ �����
		m_vecRank[i].back()->bFlag = true;
	}
	// 2.2  ������6��
	for(int i=4;i<10;i++)   //  i����ڼ�������
	{
		for(int j=0;j<5;j++)  //  j ����  ��i�������е� �ڼ�����
		{
			Node* node = new Node;
			node->bFlag = false;   // ����
			node->pCards = vec[n++];   //  װһ����
			node->x = 10+81*i;
			node->y = 10+20*j;

			m_vecRank[i].push_back(node);
		}
		//  ���һ������ �����
		m_vecRank[i].back()->bFlag = true;
	}
	//  2.3  �� ʣ��� 50���� �ŵ�  ���һ��������
	for(int j=49;j>=0;j--)  //  j ����  ��i�������е� �ڼ�����
	{
		Node* node = new Node;
		node->bFlag = false;   // ����
		node->pCards = vec[n++];   //  װһ����
		node->x = 500+3*j;
		node->y = 500;

		m_vecRank[10].push_back(node);
	}
	//-------------------------------------------------------------
}