#pragma once

//���� �ڷᱸ�� ���ø� Ŭ����
template<typename T> class myStack
{
private:
	//���� ���� ����Ʈ�� ����ü
	struct Node
	{
		T data; //���� ����Ǵ� ������
		Node* pNext; //���� ��带 ����Ű�� ������
	};
	Node* topPointer = nullptr; //������ LIFO�� ���� �������� ���� ��带 ����Ű�� ������
	int size; //���ÿ� ����� ������ ����

public:
	myStack();//�⺻ ������
	~myStack(); //�⺻ �Ҹ���

	bool Empty(); //���ÿ� ����� ���� ������ Ȯ���ϴ� �Լ�
	int Size(); //���� �� �� ����Ǿ� �ִ��� Ȯ���ϴ� �Լ�
	void Push(T data); //���ÿ� �ڷḦ �״´�.
	T POP(); //���� ���� �����ִ� �����͸� ��ȯ�ϰ�, �����Ѵ�. (������)
	T TOP(); //���� ���� ���� �ִ� �����͸� �ϳ� ��´� (�б�).
	void Clear(); //���� ������ ���� ����
};
//�⺻ ������
template<typename T> myStack<T>::myStack()
{
	topPointer = nullptr;
	size = 0;
}

//�⺻ �Ҹ���
template<typename T> myStack<T>::~myStack()
{
	Clear();
}

//����ִ��� Ȯ��
template<typename T> bool myStack<T>::Empty()
{
	return (topPointer == nullptr); //�������� ����Ű�� �����Ͱ� null�̸� ������ ���°Ŵ�
}
//����� ������ ���� ��ȯ
template<typename T> int myStack<T>::Size()
{
	return size;
}
//���� ���� ���ÿ� �ڷḦ �״´�.
template<typename T> void myStack<T>::Push(T data)
{
	Node* nextNode = nullptr; //������ �ִ� ���� ���
	nextNode = topPointer; //���� ��带 ����
	topPointer = new Node; //���ο� ��� ����
	if (nextNode != nullptr) //���� ��尡 ������ ����
	{
		topPointer->pNext = nextNode;
		topPointer->data = data;
	}
	else //���� ��� ������
	{
		topPointer->pNext = nullptr; //���� �ؿ� �ִ� ���� null ����Ų��.
		topPointer->data = data;
	}

	size++;
}
//���� ���� �����ִ� �����͸� ��ȯ�ϰ�, �����Ѵ�. (������)
template<typename T> T myStack<T>::POP()
{
	if (!Empty())
	{
		T data = topPointer->data; //��ȯ���� ������
		//������ ������ ���� �����Ͱ� �ֻ�� �����Ͱ� �ȴ�
		Node* nextNode = topPointer->pNext;
		delete topPointer; //�޸� �ݳ�
		topPointer = nextNode; //���� ��带 �ֻ�� �޸𸮷� �����.
		size--;

		return data;
	}

	else throw; //����ó��
}
//���� ���� �����ִ� �����͸� �д´�.
template<typename T> T myStack<T>::TOP()
{
	if (!Empty()) return topPointer->data;

	else throw; //����ó��
}

template<typename T> void myStack<T>::Clear()
{
	//������ ��� ���� ����
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