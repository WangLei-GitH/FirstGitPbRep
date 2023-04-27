#pragma once

//˳��洢
#include <iostream>
using namespace std;

#define Hash_Size 50
#define Hash_Bucket 128

typedef struct _HashMem//��ϣ��洢����������
{
	int key;
	void* data;
}HashMember;

typedef struct _hash
{
	HashMember Hash_Tab[Hash_Bucket][Hash_Size];
	int _HashSize;//��ϣͰ������
}Hash_Table;

//�������������ָ��ͬһ�����������������Ҳ����Ǿֲ����������������ﴴ��һ��ȫ�ּ�������������
int CountArry[Hash_Bucket];

bool initHashTable(Hash_Table* hashtable)
{
	if (!hashtable)
	{
		return false;
	}

	hashtable->_HashSize = Hash_Bucket;//��ϣͰ

	if (!hashtable->Hash_Tab)
	{
		return false;
	}

	//Ϊÿ����ϣͰ�ٵ�[0]��λ�����һ����¼��ǰͰ��Ԫ�ظ����ļ�����
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

//����Ҫ�洢Ԫ�صĹ�ϣͰ����
int Hash(int key, int hash_bucket)
{
	return (hash_bucket % Hash_Bucket);
}

//����Ԫ��
bool findHashtable(Hash_Table* hashtable, int key)
{
	//�ҵ���Ӧ�Ĺ�ϣͰ
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
		//�ҵ�ÿ����ϣͰ�ļ��������ٵ�ǰ������������ָ���λ�õ���һ��λ�÷���Ԫ�أ�Ȼ������������
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

	//����ҵ��ˣ���ȥ�ö�Ӧ�Ĺ�ϣͰ
	if (findHashtable(hashtable,key))
	{
		int index = Hash(key, hashtable->_HashSize);
		//�õ���ϣͰ��Ԫ�صĸ���
		int count = *((int*)hashtable->Hash_Tab[index][0].data);
		int i = 1;
		for (i;i<count+1;i++)
		{
			if (hashtable->Hash_Tab[index][i].key == key)
			{
				break;
			}
		}
		//��ʱ��i��λ�þ��Ƕ�Ӧ��key��λ��
		for (int j = i; j < count-1 ; j++)
		{
			hashtable->Hash_Tab[index][j] = hashtable->Hash_Tab[index][j + 1];
		}

		//������--
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

	//��ÿ����ϣͰ�ļ�������Ϊ0
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
// 	char ele1[] = "����";
// 	char ele2[] = "���㳬";
// 	char ele3[] = "Ҷ����";
// 	char ele4[] = "����";
// 	char ele5[] = "�ﾭ��";
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