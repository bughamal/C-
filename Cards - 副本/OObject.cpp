#include "OObject.h"

RunTimeClass* COObject::pHead = 0;
COObject::COObject(void)
{
}


COObject::~COObject(void)
{
}
COObject* COObject::Create(const char* pszClassName)
{
	//  ��������
	RunTimeClass* pTemp = pHead;
	while(pTemp)
	{
		if( !strcmp(pTemp->szClassName,pszClassName) )
			return (*(pTemp->pfnCreateObject))();   //  ���ú���ָ�� ��������
		pTemp = pTemp->pNext;
	}
	return NULL;
}