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

			Node* Prev = nullptr;
			Node* Next = nullptr;
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
			Iterator& operator++() //전위 증감 연산 오버로딩
			{
				if (pCurrentNode != nullptr)
				{
					pCurrentNode = pCurrentNode->Next;
				}
				return *this;
			}
			Iterator& operator--() //전위 후위 연산 오버로딩
			{
				if (pCurrentNode != nullptr)
				{
					pCurrentNode = pCurrentNode->Prev;
				}
				return *this;
			}
			T& operator*() //역참조 연산자 오버로딩
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
		bool Empty(); //비어 있나?
		int Size();  //자료 개수
		void Clear(); //리스트 전체 삭제

		bool Erase(Node* pNode);//데이터 지우기

		Node* PushBack(T data) //제일 뒤쪽에 추가
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

		Node* PushFront(T data) //제일 앞쪽에 추가	
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
	private:
		int size;
		Node* pHead; //시작
		Node* pTail; //끝
	};

	template<typename T> List<T>::List() //생성자
	{
		pHead = nullptr;
		pTail = nullptr;
		size = 0;
	}
	template<typename T> List<T>::~List() //소멸자
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
#pragma warning( disable : 6011 ) 
			pCurrent->Prev->Next = nullptr;
#pragma warning( default : 6011 ) 
			delete pCurrent->Prev;
			pCurrent->Prev = nullptr;

			pCurrent = pCurrent->Next;
		}
		delete pTail;

		pHead = nullptr;
		pTail = nullptr;
		size = 0;
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
}

