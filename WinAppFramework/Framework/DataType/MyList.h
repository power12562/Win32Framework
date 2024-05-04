#pragma once
#include <iostream>

namespace My
{
	template<typename T> class List
	{
	public:
		struct Node
		{
			T data;

			Node* Prev;
			Node* Next;
		};

		class Iterator
		{
		public:
			Node* pCurrentNode;
			Iterator() = default;
			Iterator(Node* pNode)
			{
				this->pCurrentNode = pNode;
			}
			~Iterator() = default;
			Iterator& operator++() //���� ���� ���� �����ε�
			{
				if (pCurrentNode != nullptr)
				{
					pCurrentNode = pCurrentNode->Next;
				}
				return *this;
			}
			Iterator& operator--() //���� ���� ���� �����ε�
			{
				if (pCurrentNode != nullptr)
				{
					pCurrentNode = pCurrentNode->Prev;
				}
				return *this;
			}
			T& operator*() //������ ������ �����ε�
			{
				return pCurrentNode->data;
			}
			bool operator==(const Iterator& ref)
			{
				return pCurrentNode == ref.pCurrentNode;
			}
			bool operator!=(const Iterator& ref)
			{
				return pCurrentNode != ref.pCurrentNode;
			}
		};
		List();
		~List();
		Node* GetpHead() { return pHead; }
		Node* GetpTail() { return pTail; }
		bool Empty(); //��� �ֳ�?
		int Size();  //�ڷ� ����
		void Clear(); //����Ʈ ��ü ����

		bool Insert(int index, T data); //������ ����

		bool Erase(int index);
		bool Erase(Node* pNode);//������ �����

		Node* PushBack(T data) //���� ���ʿ� �߰�
		{
			Node* pCurr = new Node;
			if (pCurr != nullptr)
			{
				if (Empty())
				{
					pCurr->data = data;
					pCurr->Next = nullptr;
					pCurr->Prev = nullptr;
					pTail = pCurr;
					pHead = pTail;
				}
				else
				{
					pCurr->data = data;
					pCurr->Prev = pTail;
					pCurr->Next = nullptr;

					pTail->Next = pCurr;
					pTail = pCurr;
				}
				size++;
				return pCurr;
			}
			return nullptr;
		}

		Node* PushFront(T data) //���� ���ʿ� �߰�	
		{
			Node* pCurr = new Node;
			if (pCurr != nullptr)
			{
				if (Empty())
				{
					pCurr->data = data;
					pCurr->Next = nullptr;
					pCurr->Prev = nullptr;
					pTail = pCurr;
					pHead = pTail;
				}
				else
				{
					pCurr->data = data;
					pCurr->Prev = nullptr;
					pCurr->Next = pHead;

					pHead->Prev = pCurr;
					pHead = pCurr;
				}
				size++;
				return pCurr;
			}
			return nullptr;
		}

		T& GetData(int index); //�� ��������
	private:
		int size;
		Node* pHead; //����
		Node* pTail; //��
	};

	template<typename T> List<T>::List() //������
	{
		pHead = nullptr;
		pTail = nullptr;
		size = 0;
	}
	template<typename T> List<T>::~List() //�Ҹ���
	{
		if (pHead != nullptr && pTail != nullptr)
		{
			Clear();
		}
	}
	template <typename T> bool List<T>::Empty()
	{
		if (size <= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	template<typename T> int List<T>::Size()
	{
		return size;
	}
	template<typename T> void List<T>::Clear()
	{
		Node* pCurrent = pHead->Next;
		for (int i = 1; i < this->size; i++)
		{
			pCurrent->Prev->Next = nullptr;
			delete pCurrent->Prev;
			pCurrent->Prev = nullptr;

			pCurrent = pCurrent->Next;
		}
		delete pTail;

		pHead = nullptr;
		pTail = nullptr;
		size = 0;
	}
	template<typename T> bool List<T>::Insert(int index, T data)
	{
		Node* pCurr = pHead;
		if (size > 0 && 0 <= index && index < size)
		{
			for (int i = 0; i < index; i++)
			{
				pCurr = pCurr->Next;
			}
			Node* pPrev = pCurr->Prev;
			Node* pNext = pCurr;
			pCurr = new Node;
			if (pCurr == nullptr) false;

			pCurr->data = data;
			pCurr->Prev = pPrev;
			pCurr->Next = pNext;

			pNext->Prev = pCurr;
			pPrev->Next = pCurr;

			if (index == 0) pHead = pCurr;
			if (index == (size - 1)) pTail = pCurr;

			size++;
			return true;
		}
		else
		{
			return false;
		}
	}
	template<typename T> bool List<T>::Erase(int index)
	{
		Node* pCurr = pHead;
		if (size > 0 && 0 <= index && index < size)
		{
			for (int i = 0; i < index; i++)
			{
				pCurr = pCurr->Next;
			}
			Node* pPrev = pCurr->Prev;
			Node* pNext = pCurr->Next;
			pCurr->Prev = nullptr;
			pCurr->Next = nullptr;
			delete pCurr;

			if (pPrev != nullptr)
				pPrev->Next = pNext;
			else if (pNext != nullptr)
				pNext->Prev = nullptr;

			if (pNext != nullptr)
				pNext->Prev = pPrev;
			else if (pPrev != nullptr)
				pPrev->Next = nullptr;

			if (index == 0) pHead = pNext;
			if (index == (size - 1)) pTail = pPrev;

			size--;
			return true;
		}
		else
		{
			return false;
		}
	}

	template<typename T> bool List<T>::Erase(Node* pNode)
	{
		Node* pCurr = pNode;
		Node* pPrev = pCurr->Prev;
		Node* pNext = pCurr->Next;
		pCurr->Prev = nullptr;
		pCurr->Next = nullptr;
		delete pCurr;

		if (pNext == nullptr)
			pTail = pPrev;
		if (pPrev == nullptr)
			pHead = pNext;

		if (pPrev != nullptr)
			pPrev->Next = pNext;
		else if (pNext != nullptr)
			pNext->Prev = nullptr;

		if (pNext != nullptr)
			pNext->Prev = pPrev;
		else if (pPrev != nullptr)
			pPrev->Next = nullptr;

		size--;
		return true;
	}

	template<typename T> T& List<T>::GetData(int index)
	{
		if (0 <= index && index < size)
		{
			Node* pCurr = nullptr;

			pCurr = pHead;
			for (int i = 0; i < index; i++)
			{
				pCurr = pCurr->Next;
			}

			return pCurr->data;
		}
		throw std::out_of_range("out of index");
	}
}

