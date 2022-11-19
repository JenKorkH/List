#pragma once
#include <iostream>
#include <vector>
using namespace std;
template<typename T>
class MyList
{
private:
	template<typename T>
	class Node
	{
	public:
		Node* pNext;
		T data;
		Node(T _data = T(), Node* _pNext = nullptr)
		{
			data = _data;
			pNext = _pNext;
		}
	};

	int size;
	Node<T> *head;

public:
	MyList();
	~MyList();

	int GetSize() { return size; }
	T& operator[](const int index);
	void push_back(T data);
	void push_front(T data);
	void insert(T data, int index);
	void pop_front();
	void update(T data, int index);
	void pop_back();
	void remove(int index);
	void concat(MyList<T> *second);
	void sort();
	void sortD();
	void copy(MyList<T>* second);
	MyList<T>& createNew(MyList<T> *second);
	void clear();
	void deleveryn(int n);
	void move(int elem, int on);
};

template<typename T>
MyList<T>::MyList()
{
	size = 0;
	head = nullptr;
}

template<typename T>
MyList<T>::~MyList()
{
	clear();
}

template<typename T>
T& MyList<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* cur = this->head;
	while (cur->pNext != nullptr)
	{
		if (counter == index)
		{
			return cur->data;
		}
		cur = cur->pNext;
		counter++;
	}
}

template<typename T>
void MyList<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T> *cur = this->head;

		while (cur->pNext != nullptr)
		{
			cur = cur->pNext;
		}
		cur->pNext = new Node<T>(data);
	}
	size++;
}

template<typename T>
void MyList<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	size++;
}

template<typename T>
void MyList<T>::insert(T data, int index)
{
	if (index == 0)
	{
		push_front(data);
	}
	if (index >= size)
	{
		return;
	}
	if (index < 0)
	{
		return;
	}
	else
	{
		Node<T>* prev = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			prev = prev->pNext;
		}

		Node<T>* temp = new Node<T>(data, prev->pNext);
		prev->pNext = temp;
		size++;
	}
}

template<typename T>
void MyList<T>::pop_front()
{
	Node<T> *temp = head;
	head = head->pNext;
	delete temp;
	size--;
}

template<typename T>
void MyList<T>::update(T data, int index)
{
	int counter = 0;
	Node<T> *temp = head;
	while (counter != index)
	{
		temp = temp->pNext;
		counter++;
	}
	temp->data = data;
}

template<typename T>
void MyList<T>::pop_back()
{
	remove(size - 1);
}

template<typename T>
void MyList<T>::remove(int index)
{
	if (index < 0 || index >= size)
	{
		return;
	}
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		Node<T>* prev = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			prev = prev->pNext;
		}

		Node<T>* next = prev->pNext;

		prev->pNext = next->pNext;
		delete next;
		size--;
	}
}

template<typename T>
void MyList<T>::concat(MyList<T> *second)
{
	Node<T>* temp = second->head;
	while (temp != nullptr)
	{
		push_back(temp->data);
		temp = temp->pNext;
	}
}

template<typename T>
void MyList<T>::sort()
{
	Node<T>* cur;
	bool found;
	do
	{
		found = false;
		cur = head;
		while (cur->pNext != nullptr)
		{
			if (cur->data > cur->pNext->data)
			{
				T temp = cur->data;
				cur->data = cur->pNext->data;
				cur->pNext->data = temp;
				found = true;
			}
			cur = cur->pNext;
		}
	} while (found);
}

template<typename T>
void MyList<T>::sortD()
{
	Node<T>* cur;
	bool found;
	do
	{
		found = false;
		cur = head;
		while (cur->pNext != nullptr)
		{
			if (cur->data < cur->pNext->data)
			{
				T temp = cur->data;
				cur->data = cur->pNext->data;
				cur->pNext->data = temp;
				found = true;
			}
			cur = cur->pNext;
		}
	} while (found);
}

template<typename T>
void MyList<T>::copy(MyList<T>* second)
{
	if (second->head == nullptr)
	{
		return;
	}
	if (size != 0)
	{
		clear();
	}
	Node<T>* temp = second->head;
	while (temp != nullptr)
	{
		push_back(temp->data);
		temp = temp->pNext;
	}
}

template<typename T>
MyList<T>& MyList<T>::createNew(MyList<T>* second)
{
	vector<T> elements;
	MyList<T> *newList = new MyList<T>();
	Node<T>* temp = head;
	Node<T>* temp2 = second->head;
	while (temp != nullptr)
	{
		while (temp2 != nullptr)
		{
			if (temp->data == temp2->data)
			{
				int counter = 0;
				for (int i = 0; i < elements.size(); i++)
				{
					if (elements[i] == temp->data)
					{
						counter = 1;
						break;
					}
				}
				if (counter != 1)
				{
					elements.push_back(temp2->data);
					newList->push_back(temp->data);
				}
			}
			temp2 = temp2->pNext;
		}
		temp = temp->pNext;
		temp2 = second->head;
	}
	return *newList;
}
	

template<typename T>
void MyList<T>::clear()
{
	while (size)
	{
		pop_front();
	}
}

template<typename T>
void MyList<T>::deleveryn(int n)
{
	if (n > size)
	{
		return;
	}
	if (n == 1)
	{
		clear();
	}
	int b = 1;
	Node<T>* cur = head;
	Node<T>* prev = head;
	while (cur != nullptr)
	{
		if (b == n)
		{
			Node<T>* temp = cur;
			prev->pNext = temp->pNext;
			cur = temp->pNext;
			delete temp;
			b = 1;
			size--;
			continue;
		}
		prev = cur;
		cur = cur->pNext;
		b++;
	}
}

template<typename T>
void MyList<T>::move(int elem, int on)
{
	int counter = 0;
	if (elem >= size || elem < 0 || elem + on >= size || size == 1 || on == 0)
	{
		return;
	}
	if (size == 2)
	{
		Node<T>* temp = head;
		head = head->pNext;
		head->pNext = temp;
	}
	if (elem == 0)
	{
		Node<T>* temp = head;
		head = head->pNext;
		insert(temp->data, on);
		delete temp;
		return;
	}
	Node<T>* cur = head;
	Node<T>* prev = head;
	while (counter != elem)
	{
		prev = cur;
		cur = cur->pNext;
		counter++;
	}
	prev->pNext = prev->pNext->pNext;
	insert(cur->data, (elem + on));
	size--;
	delete cur;
}
