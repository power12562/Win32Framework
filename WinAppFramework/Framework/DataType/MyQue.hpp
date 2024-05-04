#pragma once
#include <iostream>

template <typename T> class MyQueue
{
	T* p_Data;
public:
	MyQueue(const int size = 10); //������ �⺻ ������� 10
	~MyQueue(); //�Ҹ��� �����Ҵ�� ������ ����

	int GetSize(); //����� ������ ���� �������ش�.
	int GetMaxSize(); //ť ũ�� �������ش�.
	bool IsEmpty(); //ť ������ �ڷᰡ ������ Ȯ�����ִ� �޼���
	T GetFront(); //���ʿ��� ������ �д´�
	void Push_back(T data); //�ڿ��� ������ ����
	T Pop_front(); //�տ��� ������ ���� (��ȯ���� ������ ������)
	bool IsFull() { return isfull; }

private:
	int maxSize; //�迭 ���� (ũ��) �����ϴ� �ʵ�
	int dataSize; //������ � �����ϰ� �ִ��� �����ϴ� �ʵ�
	int FrontIndex; //���� ���� ����Ű�� �ε��� (������)
	int RearIndex; //���� ������ ����Ű�� �ε��� (������)
	bool isfull; //�����Ͱ� ���� �� ���θ� �����ϴ� �÷��� ����
	void QFull(); //������ ���� ���� ���ο��� ȣ��Ǵ� �޼���
};

//������
template <typename T> MyQueue<T>::MyQueue(const int size)
{
	//�ʱ�ȭ
	this->FrontIndex = 0; 
	this->RearIndex = 0; 
	this->dataSize = 0; 
	this->isfull = false; 

	this->p_Data = new T[size]; //�迭 ���� �Ҵ�
	this->maxSize = size;	
}
//�Ҹ���
template <typename T> MyQueue<T>::~MyQueue()
{
	delete[] p_Data;
}

//�ִ� ũ�� �������ִ� �Լ�
template <typename T> int MyQueue<T>::GetMaxSize()
{
	return maxSize;
}

//����� ������ ���� ���� ���ִ� �Լ�
template <typename T> int MyQueue<T>::GetSize()
{
	return dataSize;
}

//ť�� ������ ����.
template <typename T> void MyQueue<T>::Push_back(T data)
{
	if (!isfull) //������ �������� ���� �� �ִ�.
	{
		p_Data[RearIndex] = data; //���ʿ� �����͸� �ִ´�
		RearIndex++; //���� �ڸ� ����Ű�� �ε��� �ϳ� ����
		RearIndex = RearIndex % this->maxSize; //�迭 �ε����� �ִ뿡 �����ϸ� �ٽ� 0���� ���ư���. (���� ť)
		this->dataSize++;

		if (dataSize == maxSize) isfull = true;	//������ ������ �ִ� ������ ������ ���� ���Ŵ�		
	}
	else QFull();
}

//ť�� ������ ����. ��ȯ���� ���� ���ʿ� �ִ� �������̴�.
template <typename T> T MyQueue<T>::Pop_front()
{
	T null = static_cast<T>(NULL);
	//������ ��������� ���� �Ұ�
	if (!IsEmpty() || isfull)
	{
		T forntData = p_Data[FrontIndex]; //���ʿ� �ִ� ������ ����
		p_Data[FrontIndex] = null; //���ʿ� �ִ� ������ ����.
		FrontIndex++; //���� ���� ����Ű�� �ε��� �ϳ� ����
		FrontIndex = FrontIndex % this->maxSize; //�迭 �ε����� �ִ뿡 �����ϸ� �ٽ� 0���� ���ư���. (���� ť)
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

//ť�� �����Ͱ� ������ Ȯ�� �� �ִ� �޼���
template <typename T> bool MyQueue<T>::IsEmpty()
{
	if (!isfull)
	{
		return FrontIndex == RearIndex; //���� ���� �ε����� ����Ű�� �����Ͱ� ����ִٴ� ���̴�.
	}
	else
	{
		return false;
	}
}

//���� ���ʿ��� �����͸� �б⸸ �Ѵ�.
template <typename T> T MyQueue<T>::GetFront()
{
	T null = static_cast<T>(NULL);
	if (isfull || !IsEmpty()) //������ ���� ���ְų� ������� �������� �� ��ȯ
	{
		return p_Data[FrontIndex]; //���� �� ����
	}
	else
	{
		std::cout << "\nQueue is Empy!" << std::endl;
		return null; //������ ������ 0 ��ȯ
	}
}

//������ ���� ���� ȣ��Ǵ� �޼���
template <typename T> void MyQueue<T>::QFull() 
{
	std::cout << "Queue is Full!" << std::endl;
}