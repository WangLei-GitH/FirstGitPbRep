#pragma once
#include <iostream>
using namespace std;
//add commit message for git
//����Ĭ�Ϲ�ϣ��ߴ� 16
#define DEFAULT_SIZE 16

//������������±�(0,1,2,3,4..),���Կ��ٶ�λ�ͼ�������
//��ϣͰ��������������������������ԱΪÿһ������ֵ��ͬ�Ķ��Ԫ��
//��ϣ����������Ա���ӳ�䵽�����ϣ��������෨������key%5
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
	int TableSize;//��ϣͰ�Ĵ�С
	List* ThisList;
}HashTable;

//���ݹ�ϣ��������HashͰ��λ��
int Hash(int key, int TableSize)
{
	return (key % TableSize);
}

//��ʼ����ϣ��
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

//hash�����Ԫ��
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

//�ҵ���Ӧ��ListNode��ȡԪ��
void* extractNode(Element e)
{
	return e ? e->data : nullptr;
}