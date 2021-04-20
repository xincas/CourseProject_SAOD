#pragma once
#include <iostream>
#include <string>

template<typename T>
class AVL
{
private:
	template<typename T>
	class Node {
	public:
		T Data_;
		int height_;
		Node<T>* left_;
		Node<T>* right_;

		Node<T>(T data = T()) {
			this->Data_ = data;
			this->left_ = nullptr;
			this->right_ = nullptr;
			this->height_ = 1;
		};

		~Node<T>() { };
	};

	//fields
	int Height_;
	Node<T>* Root_;

	//Private methods

	//adding new value
	Node<T>* add(Node<T>* node, T data);

	//balancing methods
	Node<T>* rotR(Node<T>* node);
	Node<T>* rotL(Node<T>* node);
	Node<T>* balance(Node<T>* node);
	void postOrder(Node<T>* node);
	int bFactor(Node<T>* node);
	int getHeightOfNode(Node<T>* node);
	int max(int a, int b);

	//free memory
	void clear(Node<T>* node);

	//print
	void print(Node<T>* node, int spacer);

	//removing node
	Node<T>* remove(Node<T>* node, T data);
	Node<T>* findMin(Node<T>* node);
	Node<T>* removeMin(Node<T>* node);

public:
	//public methods
	int getHeight();

	void add(T data);
	void remove(T n) { this->Root_ = remove(this->Root_, n); };

	void postOrder() { postOrder(this->Root_); };
	void print(int spacer = 0) { print(this->Root_, spacer); };


	AVL();
	~AVL();
};

template<typename T>
AVL<T>::AVL() {
	this->Height_ = 0;
	this->Root_ = nullptr;
};

template<typename T>
AVL<T>::~AVL() {
	clear(this->Root_);
}

template<typename T>
int AVL<T>::getHeight()
{
	return max(getHeightOfNode(this->Root_->left_), getHeightOfNode(this->Root_->right_));
}

template<typename T>
inline int AVL<T>::getHeightOfNode(Node<T>* node)
{
	return node ? node->height_ : 0;
}

template<typename T>
inline int AVL<T>::max(int a, int b)
{
	return a > b ? a : b;
}

template<typename T>
void AVL<T>::clear(Node<T>* node)
{
	if (node != nullptr) {
		clear(node->left_);
		clear(node->right_);
		delete node;
	}
}

template<typename T>
void AVL<T>::print(Node<T>* node, int spacer)
{
	if (node == nullptr)
	{
		return;
	}

	spacer += 5;
	print(node->right_, spacer);

	std::cout << "\n";
	for (int i = 5; i < spacer; i++)
		std::cout << " ";

	std::cout << node->Data_;

	print(node->left_, spacer);
}

template<typename T>
typename AVL<T>::template Node<T>* AVL<T>::add(Node<T>* node, T data)
{
	if (node == nullptr)
	{
		return node = new Node<T>(data);
	}	
	else 
	{
		if (data < node->Data_)
		{
			node->left_ = add(node->left_, data);
		}
		else if (data > node->Data_)
		{
			node->right_ = add(node->right_, data);
		}	
	}

	return balance(node);
}

template<typename T>
void AVL<T>::add(T data)
{
	this->Root_ = add(this->Root_, data);
}

template<typename T>
typename AVL<T>::template Node<T>* AVL<T>::remove(Node<T>* node, T data)
{
	if (node == nullptr)
		;
	else if (data == node->Data_) 
	{
		Node<T>* left = node->left_;
		Node<T>* right = node->right_;
		
		delete node;

		Node<T>* min = findMin(right);

		if (!min)
		{
			return balance(left);
		}

		min->right_ = removeMin(right);
		min->left_ = left;

		return node = balance(min);
	}
	else if (data < node->Data_)
	{
		node->left_ = remove(node->left_, data);
	}
	else if (data > node->Data_)
	{
		node->right_ = remove(node->right_, data);
	}	

	return balance(node);
}

template<typename T>
typename AVL<T>::template Node<T>* AVL<T>::findMin(Node<T>* node)
{
	if (!node)
	{
		return nullptr;
	}
		
	while (node->left_ != nullptr)
	{
		node = node->left_;
	}
		
	return node;
}

template<typename T>
typename AVL<T>::template Node<T>* AVL<T>::removeMin(Node<T>* node)
{
	if (!node)
	{
		return nullptr;
	}
		
	if (node->left_ == nullptr)
	{
		return node->right_;
	}
		
	node->left_ = removeMin(node->left_);

	return balance(node);
}

template<typename T>
typename AVL<T>::template Node<T>* AVL<T>::rotR(Node<T>* node)
{
	Node<T>* p2 = node->left_;
	node->left_ = p2->right_;
	p2->right_ = node;

	node->height_ = max(getHeightOfNode(node->left_), getHeightOfNode(node->right_)) + 1;
	p2->height_ = max(getHeightOfNode(p2->left_), getHeightOfNode(node)) + 1;

	return p2;
}

template<typename T>
typename AVL<T>::template Node<T>* AVL<T>::rotL(Node<T>* node)
{
	Node<T>* p2 = node->right_;
	node->right_ = p2->left_;
	p2->left_ = node;

	node->height_ = max(getHeightOfNode(node->left_), getHeightOfNode(node->right_)) + 1;
	p2->height_ = max(getHeightOfNode(p2->right_), getHeightOfNode(node)) + 1;

	return p2;
}

template<typename T>
typename AVL<T>::template Node<T>* AVL<T>::balance(Node<T>* node)
{
	if (!node)
	{
		return NULL;
	}

	node->height_ = max(getHeightOfNode(node->left_), getHeightOfNode(node->right_)) + 1;
	int bfac = bFactor(node);

	if (bfac == 2) 
	{
		if (bFactor(node->right_) < 0)
		{
			node->right_ = rotR(node->right_);
		}
			
		return rotL(node);
	}
	if (bfac == -2) 
	{
		if (bFactor(node->left_) > 0)
		{
			node->left_ = rotL(node->left_);
		}
			
		return rotR(node);
	}

	return node;
}

template<typename T>
void AVL<T>::postOrder(Node<T>* node)
{
	if (node != nullptr) {
		postOrder(node->left_);
		postOrder(node->right_);
		std::cout << node->Data_;
	}
}

template<typename T>
inline int AVL<T>::bFactor(Node<T>* node)
{
	return getHeightOfNode(node->right_) - getHeightOfNode(node->left_);
}
