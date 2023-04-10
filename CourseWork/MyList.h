#pragma once
#include <iostream>
#include "Node.h"
using namespace std;
template<typename T>
class MyList :protected Node<T>
{
private:
	Node<T>* head;
	int Size;

public:
	MyList();

	MyList(std::initializer_list<T> init);
	void clear();
	void pop_first();
	void push_back(T data);
	int size();
	void push_front(T data);
	void insert(T data, int index);
	T& operator[](const int index);
	void removeAt(int index);
	void pop_back();
	void pop_front();
};
template<typename T>
MyList<T>::MyList()
{
	Size = 0;
	head = nullptr;
}
template<typename T>
MyList<T>::MyList(std::initializer_list<T> init)
{
	typename std::initializer_list<T>::iterator it;
	it = init.begin();
	for (int i = 0; i < init.size(); i++)
	{
		if (head == nullptr)
		{
			head = new Node<T>(*it);
		}
		else
		{
			Node<T>* current = this->head;
			while (current->pNext != nullptr)
			{
				current = current->pNext;
			}
			current->pNext = new Node<T>(*it);
		}
		it++;
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
		Node<T>* current = this->head;
		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node<T>(data);
	}
	Size++;
}
template<typename T>
int MyList<T>::size()
{
	return Size;
}
template<typename T>
T& MyList<T>::operator[](const int index)
{
	Node<T>* current = this->head;
	int count = 0;
	while (current != nullptr)
	{
		if (count == index)
		{
			return current->data;
		}
		current = current->pNext;
		count++;
	}
}
template<typename T>
void MyList<T>::pop_first()
{
	Node<T>* temp = head;
	head = head->pNext;
	delete temp;
	Size--;
}
template<typename T>
void MyList<T>::clear()
{
	while (Size) pop_first();
}
template<typename T>
void MyList<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	Size++;
}
template<typename T>
void MyList<T>::insert(T data, int index)
{

	if (index == 0)
	{
		push_front(data);
	}
	else
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}
		Node<T>* newNode = new Node<T>(data, previous->pNext);
		previous->pNext = newNode;
		Size++;
	}
}
template<typename T>
void MyList<T>::removeAt(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}
		Node<T>* toDelete = previous->pNext;
		previous->pNext = toDelete->pNext;
		delete toDelete;
		Size--;
	}

}
template<typename T>
void MyList<T>::pop_back()
{
	removeAt(Size - 1);
}
template<typename T>
void MyList<T>::pop_front()
{
	Node<T>* temp = head;
	head = head->pNext;
	delete temp;
	Size--;
}