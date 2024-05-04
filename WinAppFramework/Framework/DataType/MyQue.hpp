#pragma once
#include <iostream>

template <typename T> class MyQueue
{
	T* p_Data;
public:
	MyQueue(const int size = 10); //생성자 기본 사이즈는 10
	~MyQueue(); //소멸자 동적할당된 데이터 제거

	int GetSize(); //저장된 데이터 개수 리턴해준다.
	int GetMaxSize(); //큐 크기 리턴해준다.
	bool IsEmpty(); //큐 공간에 자료가 없는지 확인해주는 메서드
	T GetFront(); //앞쪽에서 데이터 읽는다
	void Push_back(T data); //뒤에서 데이터 삽입
	T Pop_front(); //앞에서 데이터 삭제 (반환값은 삭제된 데이터)
	bool IsFull() { return isfull; }

private:
	int maxSize; //배열 길이 (크기) 저장하는 필드
	int dataSize; //데이터 몇개 저장하고 있는지 저장하는 필드
	int FrontIndex; //제일 앞을 가리키는 인덱스 (꺼낼때)
	int RearIndex; //제일 뒤쪽을 가리키는 인덱스 (넣을때)
	bool isfull; //데이터가 가득 찬 여부를 저장하는 플래그 변수
	void QFull(); //데이터 가득 차면 내부에서 호출되는 메서드
};

//생성자
template <typename T> MyQueue<T>::MyQueue(const int size)
{
	//초기화
	this->FrontIndex = 0; 
	this->RearIndex = 0; 
	this->dataSize = 0; 
	this->isfull = false; 

	this->p_Data = new T[size]; //배열 동적 할당
	this->maxSize = size;	
}
//소멸자
template <typename T> MyQueue<T>::~MyQueue()
{
	delete[] p_Data;
}

//최대 크기 리턴해주는 함수
template <typename T> int MyQueue<T>::GetMaxSize()
{
	return maxSize;
}

//저장된 데이터 개수 리턴 해주는 함수
template <typename T> int MyQueue<T>::GetSize()
{
	return dataSize;
}

//큐에 데이터 삽입.
template <typename T> void MyQueue<T>::Push_back(T data)
{
	if (!isfull) //공간이 있을때만 넣을 수 있다.
	{
		p_Data[RearIndex] = data; //뒤쪽에 데이터를 넣는다
		RearIndex++; //가장 뒤를 가리키는 인덱스 하나 증가
		RearIndex = RearIndex % this->maxSize; //배열 인덱스가 최대에 도달하면 다시 0으로 돌아간다. (원형 큐)
		this->dataSize++;

		if (dataSize == maxSize) isfull = true;	//데이터 개수가 최대 개수랑 같으면 가득 찬거다		
	}
	else QFull();
}

//큐에 데이터 삭제. 반환값은 제일 앞쪽에 있는 데이터이다.
template <typename T> T MyQueue<T>::Pop_front()
{
	T null = static_cast<T>(NULL);
	//데이터 비어있으면 삭제 불가
	if (!IsEmpty() || isfull)
	{
		T forntData = p_Data[FrontIndex]; //앞쪽에 있는 데이터 복사
		p_Data[FrontIndex] = null; //앞쪽에 있는 데이터 삭제.
		FrontIndex++; //가장 앞을 가리키는 인덱스 하나 증가
		FrontIndex = FrontIndex % this->maxSize; //배열 인덱스가 최대에 도달하면 다시 0으로 돌아간다. (원형 큐)
		isfull = false;
		this->dataSize--;

		return forntData;
	}
	else
	{
		std::cout << "\nQueue is Empy!" << std::endl;
		return null;
	}		
}

//큐에 데이터가 없는지 확인 해 주는 메서드
template <typename T> bool MyQueue<T>::IsEmpty()
{
	if (!isfull)
	{
		return FrontIndex == RearIndex; //둘이 같은 인덱스를 가리키면 데이터가 비어있다는 뜻이다.
	}
	else
	{
		return false;
	}
}

//제일 앞쪽에서 데이터를 읽기만 한다.
template <typename T> T MyQueue<T>::GetFront()
{
	T null = static_cast<T>(NULL);
	if (isfull || !IsEmpty()) //데이터 가득 차있거나 비어있지 않을때만 값 반환
	{
		return p_Data[FrontIndex]; //앞쪽 값 리턴
	}
	else
	{
		std::cout << "\nQueue is Empy!" << std::endl;
		return null; //데이터 없으면 0 반환
	}
}

//데이터 가득 차면 호출되는 메서드
template <typename T> void MyQueue<T>::QFull() 
{
	std::cout << "Queue is Full!" << std::endl;
}