#pragma once
#include <string>
#include <functional>

template<typename K, typename T>
class HashTable
{
private:
	template<typename K, typename T>
	class Pair
	{
	public:
		K key;
		T data;

		Pair(K key, T data)
		{
			this->data = data;
			this->key = key;
		};

		Pair()
		{
			this->data = T();
			this->key = K();
		};

		bool operator==(Pair<K, T> a)
		{
			return this->key == a.key && this->data == a.data ? true : false;
		}
	};

	int size;
	int count;
	Pair<K,T>* arr;
	int c1 = 2, c2 = 3;

	int hashFun(K key);
	int collisionFix(int i , int n);
	bool isFree(int i);
	void resize();
	//T& getDataByKey(K key);

	
public:
	HashTable();
	~HashTable();

	void clear();
	bool contains(K key);
	void add(K key, T data);
	void removeByKey(K key);
	T& operator[](K key);

};

template<typename K, typename T>
HashTable<K, T>::HashTable()
{
	this->size = 2;
	this->arr = new Pair<K, T>[size]();
}

template<typename K, typename T>
HashTable<K, T>::~HashTable()
{
	delete[] arr;
}

template<typename K, typename T>
void HashTable<K, T>::clear()
{
	for (int i = 0; i < this->size; i++)
		arr[i] = Pair<K,T>();
}

template<typename K, typename T>
bool HashTable<K, T>::contains(K key)
{
	return !(arr[hashFun(key)] == Pair<K, T>()) && arr[hashFun(key)].key == key;
}

template<typename K, typename T>
void HashTable<K, T>::add(K key, T data)
{
	int i = hashFun(key);
	if (isFree(i))
		this->arr[i] = Pair<K, T>(key, data);
	else
	{
		int try_n = 1;
		do 
		{
			i = collisionFix(i, try_n++);
		} while (!isFree(i));

		this->arr[i] = Pair<K, T>(key, data);
	}
	this->count++;
	resize();
}

template<typename K, typename T>
void HashTable<K, T>::removeByKey(K key)
{
	this->arr[hashFun(key)] = Pair<K, T>();
}

template<typename K, typename T>
int HashTable<K, T>::hashFun(K key)
{
	return std::hash<K>{}(key) % this->size;
}

template<typename K, typename T>
T& HashTable<K, T>::operator[](K key)
{
	return arr[hashFun(key)].data;
}

template<typename K, typename T>
int HashTable<K, T>::collisionFix(int i , int n)
{
	int res = i + c1 * n + c2 * n * n;
	if (res < this->size)
		return res;
	else
		return res % this->size;
}

template<typename K, typename T>
bool HashTable<K, T>::isFree(int i)
{
	return arr[i] == Pair<K, T>();
}

template<typename K, typename T>
void HashTable<K, T>::resize()
{
	if ((double)count / (double)size >= 0.7)
	{
		this->size *= 2;

		Pair<K, T>* arr2 = new Pair<K, T>[size]();

		for (int i = 0; i < this->size / 2; i++)
		{
			if (this->arr[i] == Pair<K, T>())
				continue;
			else
				arr2[hashFun(this->arr[i].key)] = this->arr[i];
		}

		delete[] this->arr;

		this->arr = arr2;
	}
}