#pragma once

//顺序存储
#include <iostream>
using namespace std;

#define Hash_Size 50
#define Hash_Bucket 128

typedef struct _HashMem//哈希表存储的数据类型
{
	int key;
	void* data;
}HashMember;

typedef struct _hash
{
	HashMember Hash_Tab[Hash_Bucket][Hash_Size];
	int _HashSize;//哈希桶的索引
}Hash_Table;

//多个计数器不能指向同一个计数器变量，并且不能是局部变量，所以在这里创建一个全局计数器变量数组
int CountArry[Hash_Bucket];

bool initHashTable(Hash_Table* hashtable)
{
	if (!hashtable)
	{
		return false;
	}

	hashtable->_HashSize = Hash_Bucket;//哈希桶

	if (!hashtable->Hash_Tab)
	{
		return false;
	}

	//为每个哈希桶再第[0]个位置添加一个记录当前桶中元素个数的计数器
	for (int i = 0; i < Hash_Bucket; i++)
	{
		HashMember Count;
		int* count = &(CountArry[i]);
		Count.data = count;
		Count.key = -(i + 1);
		hashtable->Hash_Tab[i][0] = Count;
	}
	return true;
}

//计算要存储元素的哈希桶索引
int Hash(int key, int hash_bucket)
{
	return (hash_bucket % Hash_Bucket);
}

//查找元素
bool findHashtable(Hash_Table* hashtable, int key)
{
	//找到对应的哈希桶
	int index = Hash(key, Hash_Bucket);
	int count = *((int*)(hashtable->Hash_Tab[index][0].data));
	for (int i = 0; i < count+1 ; i++)
	{
		if (hashtable->Hash_Tab[index][i].key==key)
		{
			return true;
		}
	}
	return false;
}

void insertHashtable(Hash_Table* hashtable, int key, void* data)
{
	if (!hashtable)
	{
		return;
	}

	int index = Hash(key, hashtable->_HashSize);
	HashMember newHashMember;
	newHashMember.data = data;
	newHashMember.key = key;
	bool isExt = findHashtable(hashtable, key);

	if (!isExt)
	{
		//找到每个哈希桶的计数器，再当前计数器数量所指向的位置的下一个位置放入元素，然后自增计数器
		hashtable->Hash_Tab[index][*((int*)(hashtable->Hash_Tab[index][0].data)) + 1] = newHashMember;
		(*((int*)(hashtable->Hash_Tab[index][0].data)))++;
	}
	else
	{
		cout << "This key has already exist!" << endl;
	}
}

bool deleteHashtable(Hash_Table* hashtable, int key)
{
	if (!hashtable)
	{
		return false;
	}

	//如果找到了，就去拿对应的哈希桶
	if (findHashtable(hashtable,key))
	{
		int index = Hash(key, hashtable->_HashSize);
		//拿到哈希桶中元素的个数
		int count = *((int*)hashtable->Hash_Tab[index][0].data);
		int i = 1;
		for (i;i<count+1;i++)
		{
			if (hashtable->Hash_Tab[index][i].key == key)
			{
				break;
			}
		}
		//此时的i的位置就是对应的key的位置
		for (int j = i; j < count-1 ; j++)
		{
			hashtable->Hash_Tab[index][j] = hashtable->Hash_Tab[index][j + 1];
		}

		//计数器--
		(*((int*)hashtable->Hash_Tab[index][0].data))--;
		return true;
	}
	else
	{
		return false;
	}
}

bool cleanHashtable(Hash_Table* hashtable)
{
	if (!hashtable)
	{
		return false;
	}

	//将每个哈希桶的计数器设为0
	for (int i=0;i<Hash_Bucket;i++)
	{
		*((int*)hashtable->Hash_Tab[i][0].data) = 0;
	}

	return true;
}

// int main()
// {
// 	Hash_Table* hashtable = new Hash_Table;
// 	initHashTable(hashtable);
// 	char ele1[] = "李明";
// 	char ele2[] = "李毅超";
// 	char ele3[] = "叶礼明";
// 	char ele4[] = "许爱斌";
// 	char ele5[] = "孙经雨";
// 
// 	insertHashtable(hashtable, 1, ele1);
// 	insertHashtable(hashtable, 2, ele2);
// 	insertHashtable(hashtable, 3, ele3);
// 	insertHashtable(hashtable, 4, ele4);
// 	insertHashtable(hashtable, 5, ele5);
// 
// 	bool ret1 = deleteHashtable(hashtable, 1);
// 	bool ret = findHashtable(hashtable, 1);
// 	if (ret)
// 	{
// 		cout << "Conform..." << endl;
// 	}
// 	else
// 	{
// 		cout << "Cannot find" << endl;
// 	}
// 
// 	cleanHashtable(hashtable);
// 	delete hashtable;
// 	hashtable = nullptr;
// 	return 0;
// }