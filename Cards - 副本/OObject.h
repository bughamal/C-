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
struct RunTimeClass   //  ��̬�������� ����Ľڵ�
{
	char szClassName[20];   //  װһ������
	COObject* (*pfnCreateObject)();   //  ���� szClassName ������
	RunTimeClass* pNext;
};


class COObject
{
public:
	static RunTimeClass* pHead;   //  �����ͷ
public:
	COObject(void);
	virtual ~COObject(void);
public:
	static COObject* Create(const char* pszClassName);   //  ƥ�� ��������
};

class InitObject
{
public:
	InitObject(RunTimeClass* pTemp)   //  ͨ�����캯�� ��pHead�������ͷ��ӽڵ�
	{
		pTemp->pNext = COObject::pHead;
		COObject::pHead = pTemp;
	}
};