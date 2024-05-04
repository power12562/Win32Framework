#pragma once

//스택 자료구조 템플릿 클래스
template<typename T> class myStack
{
private:
	//단일 연결 리스트용 구조체
	struct Node
	{
		T data; //실제 저장되는 데이터
		Node* pNext; //다음 노드를 가리키는 포인터
	};
	Node* topPointer = nullptr; //스택의 LIFO를 위한 마지막에 들어온 노드를 가리키는 포인터
	int size; //스택에 저장된 데이터 개수

public:
	myStack();//기본 생성자
	~myStack(); //기본 소멸자

	bool Empty(); //스택에 저장된 값이 없는지 확인하는 함수
	int Size(); //지금 몇 개 저장되어 있는지 확인하는 함수
	void Push(T data); //스택에 자료를 쌓는다.
	T POP(); //스택 제일 위에있는 데이터를 반환하고, 삭제한다. (빼가기)
	T TOP(); //스택 제일 위에 있는 데이터를 하나 얻는다 (읽기).
	void Clear(); //스텍 데이터 전부 삭제
};
//기본 생성자
template<typename T> myStack<T>::myStack()
{
	topPointer = nullptr;
	size = 0;
}

//기본 소멸자
template<typename T> myStack<T>::~myStack()
{
	Clear();
}

//비어있는지 확인
template<typename T> bool myStack<T>::Empty()
{
	return (topPointer == nullptr); //마지막을 가리키는 포인터가 null이면 데이터 없는거다
}
//저장된 데이터 개수 반환
template<typename T> int myStack<T>::Size()
{
	return size;
}
//제일 앞쪽 스택에 자료를 쌓는다.
template<typename T> void myStack<T>::Push(T data)
{
	Node* nextNode = nullptr; //이전에 있던 다음 노드
	nextNode = topPointer; //다음 노드를 변경
	topPointer = new Node; //새로운 노드 생성
	if (nextNode != nullptr) //다음 노드가 있으면 연결
	{
		topPointer->pNext = nextNode;
		topPointer->data = data;
	}
	else //최초 노드 생성시
	{
		topPointer->pNext = nullptr; //제일 밑에 있는 노드는 null 가리킨다.
		topPointer->data = data;
	}

	size++;
}
//스택 제일 위에있는 데이터를 반환하고, 삭제한다. (빼가기)
template<typename T> T myStack<T>::POP()
{
	if (!Empty())
	{
		T data = topPointer->data; //반환해줄 데이터
		//데이터 빼가면 다음 데이터가 최상단 데이터가 된다
		Node* nextNode = topPointer->pNext;
		delete topPointer; //메모리 반납
		topPointer = nextNode; //다음 노드를 최상단 메모리로 만든다.
		size--;

		return data;
	}

	else throw; //예외처리
}
//스텍 제일 위에있는 데이터를 읽는다.
template<typename T> T myStack<T>::TOP()
{
	if (!Empty()) return topPointer->data;

	else throw; //예외처리
}

template<typename T> void myStack<T>::Clear()
{
	//생성된 노드 전부 삭제
	if (topPointer != nullptr)
	{
		Node* prevNode = topPointer;
		Node* currNode = topPointer->pNext;
		while (currNode != nullptr)
		{
			delete prevNode;
			prevNode = nullptr;

			prevNode = currNode;
			currNode = currNode->pNext;
		}
		delete prevNode;
		prevNode = nullptr;

		topPointer = nullptr;
	}
}