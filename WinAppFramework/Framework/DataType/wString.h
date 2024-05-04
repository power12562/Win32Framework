#pragma once
#include <iostream>

//wchar_t �迭 �������� �����ϱ� ���� Ŭ����
class wString
{
public:
	
	const wchar_t* wstrcat(const wchar_t* str1, const wchar_t* str2); //���ڿ� �ΰ� �����ְ� �������ִ� �Լ�

	const wchar_t* GetString(); // ���ڿ� �������� Get�Լ� ���۷����� ()�����ε��� �߸� ���۵ɶ� ���

	wString& This = *this; //�ν��Ͻ��� ����Ű�� �ʵ� �ɹ� �̸� ȣ��� this�� ȣ���� ����� ��� �ʵ�� �������ش�.

	wString(); //�⺻ ������
	wString(const wchar_t string[]); //���� ���Կ� ������

	~wString(); //�Ҹ���

	int Count(); //���� ���� �������ִ� �Լ�

	operator const wchar_t* (); // () �����ε�
	wchar_t& operator[] (int index); // [] �����ε�
	//���� ������ �����ε�
	wString& operator=(const wString& other); //Ŭ���� ���Խ�
	wString& operator=(const wchar_t word[]); //���ڿ� ���Խ�
	wString& operator+=(const wString& other); //Ŭ���� ���Խ�
	wString& operator+=(const wchar_t word[]); //���ڿ� ���Խ�

private:
	wchar_t* string; //���� ���ڿ� �ּ� ������ �ִ� ������
	int count_char; //���� ���� �����ϴ� �ʵ�

	void SetString(const wchar_t* word); //���ڿ� �ּ� �������� �Ҵ����ִ� �Լ�
};
