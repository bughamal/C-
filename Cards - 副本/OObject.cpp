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
	//  遍历链表
	RunTimeClass* pTemp = pHead;
	while(pTemp)
	{
		if( !strcmp(pTemp->szClassName,pszClassName) )
			return (*(pTemp->pfnCreateObject))();   //  调用函数指针 创建对象
		pTemp = pTemp->pNext;
	}
	return NULL;
}