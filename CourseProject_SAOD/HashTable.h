#pragma once

template <class K, class T>
class HashTable
{
private:
	int HashTableSize_;
	T* Data;


	bool ReSize();

public:
	HashTable();
	~HashTable();

	bool AddData(T data);
	bool RemoveData(T data);
	T FindData(T data);
};

