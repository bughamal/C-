#pragma once

#include <Windows.h>
#include "resource.h"
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

//  牌的颜色
enum {Cards_Flower,Cards_Square,Cards_Red,Cards_Black};

//  链表的节点
class CCards;
struct Node
{
	bool bFlag;   //  牌的 正反面
	int x;
	int y;
	CCards* pCards;   //  装一张牌
};