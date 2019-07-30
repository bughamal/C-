#pragma once
#include <iostream>
using namespace std;

#define DECLARE_DYNCREATE()\
	public:\
	static RunTimeClass run;\
	static COObject* CreateObject();

#define IMPLEMENT_DYNCREATE(ThisClass,BaseClass)\
	RunTimeClass ThisClass::run={#BaseClass,&ThisClass::CreateObject,0};\
	InitObject initobject##ThisClass(&ThisClass::run);\
	COObject* ThisClass::CreateObject()\
	{\
		return new ThisClass;\
	}

class COObject;
struct RunTimeClass   //  动态创建对象 链表的节点
{
	char szClassName[20];   //  装一个类名
	COObject* (*pfnCreateObject)();   //  创建 szClassName 类对象的
	RunTimeClass* pNext;
};


class COObject
{
public:
	static RunTimeClass* pHead;   //  链表的头
public:
	COObject(void);
	virtual ~COObject(void);
public:
	static COObject* Create(const char* pszClassName);   //  匹配 创建对象
};

class InitObject
{
public:
	InitObject(RunTimeClass* pTemp)   //  通过构造函数 给pHead这个链表头添加节点
	{
		pTemp->pNext = COObject::pHead;
		COObject::pHead = pTemp;
	}
};