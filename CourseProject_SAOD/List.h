#pragma once
#include <iostream>
#include <string>

template <typename T>
class List
{
private:

	template <typename T>
	class Node
	{
	public:
		T data;
		Node<T>* lvl_next_[10];

		Node(T data = T(), Node<T>* pNextLvl0 = nullptr)
		{
			this->data = data;
			for (int i = 0; i < 10; i++)
			{
				lvl_next_[i] = nullptr;
			}
			lvl_next_[0] = pNextLvl0;
		}
		~Node() {}
	};

	//fields
	Node<T>* head_;
	Node<T>* back_;
	int Size_;
	int CountOfLvls_;

	//Private methods
	//Lvls fixing functions
	List<T>::Node<T>* getNodeByIndexLvl_0(int index);
	void countsOfLvls();
	void lvlsFixing_pushBack();
	void lvlDeletPointers(int indexOfLvl, Node<T>* node);
	const int smallestSizeLvl();

	//Getting node by index (using all lvls to fast skip incorrect data)
	Node<T>* getNodeByIndex(int index);

	//Sorting functions
	void selectionSort();
	void swapDataInNode(Node<T>* a, Node<T>* b);

	//Removing
	void pop_front();

	//find
	Node<T>* find(T data);
	
public:
	bool contains(T data);
	T& findData(T data);
	void clear();
	
	void insert(T data, int index);
	void push_front(T data);
	void push_back(T data);
	int size();

	T& getByIndex(int index);
	T& operator[](const int index);

	List();
	~List();
};

template <typename T>
List<T>::List()
{
	this->head_ = nullptr;
	this->back_ = nullptr;
	this->Size_ = 0;
	this->CountOfLvls_ = 1;
}

template <typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
void List<T>::clear()
{
	while (this->Size_)
	{
		this->pop_front();
	}
}

template<typename T>
List<T>::Node<T>* List<T>::getNodeByIndex(int index)
{
	if (this->Size_ <= index || index < 0)
	{
		return NULL;
	}

	Node<T>* curNode = this->head_;
	int cur_i = 0;
	for (int i = this->CountOfLvls_ - 1; i >= 0; i--)
	{
		int offset = pow(smallestSizeLvl(), i);
		while (index >= cur_i + offset)
		{
			cur_i += offset;
			curNode = curNode->lvl_next_[i];
		}
		if (index == cur_i)
		{
			return curNode;
		}
	}
}

template<typename T>
T& List<T>::getByIndex(int index)
{
	return getNodeByIndex(index)->data;
}

template<typename T>
int List<T>::size()
{
	return this->Size_;
}

template<typename T>
T& List<T>::operator[](const int index)
{
	/*Node<T>* cur = head_;

	for (int i = 0; i < index; i++)
	{
		cur = cur->lvl_next_[0];
	}

	return cur->data;*/
	return getByIndex(index);
}

template<typename T>
void List<T>::selectionSort()
{
	if (this->Size_ < 2)
	{
		return;
	}

	for (int i = 0; i < this->Size_; i++)
	{
		int min = i;

		for (int j = i + 1; j < this->Size_; j++)
		{
			if (this->getByIndex(j) < this->getByIndex(min))
			{
				min = j;
			}
		}

		swapDataInNode(this->getNodeByIndex(i), this->getNodeByIndex(min));
	}
}

template<typename T>
inline void List<T>::swapDataInNode(Node<T>* a, Node<T>* b)
{
	T tmp = a->data;
	a->data = b->data;
	b->data = tmp;
}

template<typename T>
void List<T>::lvlsFixing_pushBack()
{
	countsOfLvls();

	for (int i = 1; i < this->CountOfLvls_; i++)
	{
		int offset = pow(smallestSizeLvl(), i);
		int j = 0;
		Node<T>* prevInLvl = this->head_;

		while (this->Size_ > j + offset)
		{
			if (!prevInLvl->lvl_next_[i]) 
			{
				prevInLvl->lvl_next_[i] = getNodeByIndexLvl_0(j + offset);
			}
			prevInLvl = prevInLvl->lvl_next_[i];
			j += offset;
		}
	}
}

template<typename T>
void List<T>::lvlDeletPointers(int indexOfLvl, List<T>::Node<T>* node)
{
	if (node->lvl_next_[indexOfLvl] != nullptr)
	{
		lvlDeletPointers(indexOfLvl, node->lvl_next_[indexOfLvl]);

		node->lvl_next_[indexOfLvl] = nullptr;
	}
}

template<typename T>
inline const int List<T>::smallestSizeLvl()
{
	return 2;
}

template<typename T>
List<T>::Node<T>* List<T>::getNodeByIndexLvl_0(int index)
{
	Node<T>* cur = head_;

	for (int i = 0; i < index; i++)
	{
		cur = cur->lvl_next_[0];
	}

	return cur;
}

template<typename T>
void List<T>::countsOfLvls()
{
	int needlvl = 1;
	while (this->Size_ >= pow(smallestSizeLvl(), needlvl) && needlvl != 10) { needlvl++; }
	this->CountOfLvls_ = needlvl;
}

template <typename T>
void List<T>::push_back(T data)
{
	if (this->head_ == nullptr)
	{
		this->head_ = new Node<T>(data);
	}
	else
	{
		Node<T>* last = getNodeByIndex(this->Size_ - 1);
		last->lvl_next_[0] = new Node<T>(data);
	}

	this->Size_++;
	lvlsFixing_pushBack();

	selectionSort();
}

template<typename T>
bool List<T>::contains(T data)
{
	if (find(data))
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
List<T>::Node<T>* List<T>::find(T data)
{
	Node<T>* curNode;
	int cur_i = 0;

	if (data > getByIndex(this->Size_ - 1))
	{
		return nullptr;
	}

	for (int i = this->CountOfLvls_ - 1; i >= 0; i--)
	{
		int offset = pow(smallestSizeLvl(), i);
		while (data >= getByIndex(cur_i + offset))
		{
			cur_i += offset;
		}
		curNode = getNodeByIndex(cur_i);
		if (data == curNode->data)
		{
			return curNode;
		}
	}

	return nullptr;
}

template<typename T>
T& List<T>::findData(T data)
{
	Node<T>* find = List<T>::find(data);

	if (find)
	{
		return find->data;
	}
}



//unused
template<typename T>
void List<T>::push_front(T data)
{
	this->head_ = new Node<T>(data, this->head_);

	this->Size_++;
	countsOfLvls();
	//lvlFixing();
}
template<typename T>
void List<T>::insert(T data, int index)
{
	if (index == 0)
	{
		push_front(data);
		return;
	}
	Node<T>* previous = getNodeByIndex(index - 1);

	previous->lvl_next_[0] = new Node<T>(data, previous->lvl_next_[0]);

	this->Size_++;

	countsOfLvls();
	//lvlFixing();
}
template<typename T>
void List<T>::pop_front()
{
	if (this->Size_ == 0)
	{
		return;
	}

	Node<T>* oldHead = this->head_;
	this->head_ = this->head_->lvl_next_[0];
	delete oldHead;

	this->Size_--;
}
//