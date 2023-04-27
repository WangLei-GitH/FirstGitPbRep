#pragma once
#include <iostream>
using namespace std;
//add commit message for git
//定义默认哈希表尺寸 16
#define DEFAULT_SIZE 16

//索引：数组的下标(0,1,2,3,4..),用以快速定位和检索数据
//哈希桶：保存索引的数组或链表，数组成员为每一个索引值相同的多个元素
//哈希函数：将组员编号映射到索引上，采用求余法。例如key%5
typedef struct _ListNode
{
	struct _ListNode* next;
	int key;
	void* data;
}ListNode;

typedef ListNode* List;
typedef ListNode* Element;

typedef struct _HashTable
{
	int TableSize;//哈希桶的大小
	List* ThisList;
}HashTable;

//根据哈希函数计算Hash桶的位置
int Hash(int key, int TableSize)
{
	return (key % TableSize);
}

//初始化哈希表
HashTable* initHash(int TableSize)
{
	HashTable* hTable = nullptr;
	if (TableSize <= 0)
	{
		TableSize = DEFAULT_SIZE;
	}

	hTable = new HashTable;
	hTable->TableSize = TableSize;
	hTable->ThisList = new List[TableSize];
	if (!hTable->ThisList)
	{
		return nullptr;
	}

	for (int i = 0; i < TableSize; i++)
	{
		hTable->ThisList[i] = new ListNode;
		if (!hTable->ThisList[i])
		{
			return nullptr;
		}
		else
		{
			memset(hTable->ThisList[i], 0, sizeof(ListNode));
		}
	}

	return hTable;
}

//hash表查找元素
Element findHash(HashTable* hashtable, int key)
{
	int i = 0;
	List  L = nullptr;
	Element e = nullptr;
	i = Hash(key, hashtable->TableSize);
	L = hashtable->ThisList[i];
	e = L->next;
	while (e && e->key != key)
	{
		e = e->next;
	}
	return e;
}

void insertHash(HashTable* hashtable, int key, void* value)
{
	Element e = nullptr, tmp = nullptr;
	List L = nullptr;
	e = findHash(hashtable, key);

	if (!e)
	{
		tmp = new ListNode;
		if (!tmp)
		{
			return;
		}
		L = hashtable->ThisList[Hash(key, hashtable->TableSize)];
		tmp->data = value;
		tmp->key = key;
		tmp->next = L->next;
		L->next = tmp;
	}
	else
	{
		cout << " This Key has already exist!" << endl;
	}
}

void DeleteHash(HashTable* hashtable, int key)
{
	Element e = nullptr, last = nullptr;
	List L = nullptr;
	int i = Hash(key, hashtable->TableSize);
	L = hashtable->ThisList[i];
	last = L;
	e = L->next;
	while (e && e->key != key)
	{
		last = e;
		e = e->next;
	}
	if (e)
	{
		last->next = e->next;
		delete e;
	}
	else
	{
		cout << "This Key is not exist;" << endl;
	}
}

//找到对应的ListNode提取元素
void* extractNode(Element e)
{
	return e ? e->data : nullptr;
}