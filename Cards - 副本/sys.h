#pragma once

#include <Windows.h>
#include "resource.h"
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

//  �Ƶ���ɫ
enum {Cards_Flower,Cards_Square,Cards_Red,Cards_Black};

//  ����Ľڵ�
class CCards;
struct Node
{
	bool bFlag;   //  �Ƶ� ������
	int x;
	int y;
	CCards* pCards;   //  װһ����
};