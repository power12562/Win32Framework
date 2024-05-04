#include <iostream>
#include <wchar.h>
#include "wString.h"
//���� �޼���
const wchar_t* wString::wstrcat(const wchar_t* str1, const wchar_t* str2) //�ΰ��� ���ڿ� ���ļ� �������ش�.
{
	int size1 = 0, size2 = 0; //�� ���ڿ� ũ�� ������ִ� ����
	for (int i = 0; str1[i] != '\0'; i++) //null���� ���������� ����
	{
		size1 = i+1; //�ε��� + 1 ���� ���� ������
	}
	for (int i = 0; str2[i] != '\0'; i++) //null���� ���������� ����
	{
		size2 = i+1; //�ε��� + 1 ���� ���� ������
	}
	int sizeSum = size1 + size2 + 1; //�ι��� ������ ���� 1�� �� ���Ѵ�.
	wchar_t* string = new wchar_t[sizeSum]; //���ο� ũ�� ���ڿ� ���� �Ҵ�
	for (int i = 0; i < sizeSum; i++)
	{	
		if (i < size1)
		{
			string[i] = str1[i];
		}		
		else if(i < sizeSum)
		{
			string[i] = str2[i-size1];
		}
	}
	return string;
}

//�⺻ ������
wString::wString()
{
	this->count_char = 0;
	//�⺻�� null���ڷ� �ʱ�ȭ
	this->string = new wchar_t;
	*(this->string) = '\0';
}
//���ڿ� �Է½� ������
wString::wString(const wchar_t word[])
{
	SetString(word);
}

//�Ҹ���
wString::~wString()
{
	if (this->string != nullptr)
	{
		delete[] this->string; //�޸� �Ҵ� ����
	}
}

// ���ڿ� �������� Get�Լ� ���۷����� ()�����ε��� �߸� ���۵ɶ� ���
const wchar_t* wString::GetString() 
{
	return this->string;
}

// ���ڿ� �Ҵ��ϴ� �Լ�
void wString::SetString(const wchar_t* word)
{
	int size = 0;//���޹��� ���ڿ� ������ �����ϴ� ����
	for (int i = 0; true; i++) //�ι��� ã�������� �ݺ�
	{
		if (*(word + i) == '\0')
		{
			this->count_char = i; //���� ������ i��
			size = i + 1; //ũ��� �ε��� ��ȣ + 1
			break; //for �� Ż��
		}
	}
	if (this->string != nullptr) //�޸� �Ҵ� ���� Ȯ��
	{
		delete[] this->string; //���ڿ� �Ҵ� ����
	}
	this->string = new wchar_t[size];  //���� ���� ���� ũ�⸸ŭ �޸� ���� �Ҵ�)

	for (int i = 0; i < size; i++) //���� �� ��ŭ �ݺ�
	{
		*(this->string + i) = *(word + i); //�ش� �Ҵ�� �ּҿ� ���ʴ�� ���ڸ� �ִ´�. (����)
	}
}

//���ڿ� ���� ���� ���ִ� �Լ�
int wString::Count()
{
	return count_char;
};

//() ������ �����ε�
wString::operator const wchar_t* ()
{
	return this->string; // operator() �����ε��Ͽ� string �ʵ带 ��ȯ
}


//���� ������ �����ε�
wString& wString::operator=(const wString& other)
{
	if (&other != this)
	{
		SetString(other.string);
	}
	return *this;
}
wString& wString::operator=(const wchar_t word[])
{
	SetString(word);

	return *this;
}
wString& wString::operator+=(const wString& other)
{	
	const wchar_t* string = wString::wstrcat(this->GetString(), other.This.GetString()); //���ڿ� ��ģ��.
	SetString(string); //���ڿ� ����
	
	return *this;
}
wString& wString::operator+=(const wchar_t word[])
{	
	const wchar_t* string = wString::wstrcat(this->GetString(), word); //���ڿ� ��ģ��.
	SetString(string); //���ڿ� ����
	return *this;
}

//[] ������ �����ε�
wchar_t& wString::operator[](int index)
{
	if (0 <= index && index < this->count_char)
	{
		return *(this->string + index);
	}
	else
	{
		throw std::out_of_range("Invalid index");
	}
};