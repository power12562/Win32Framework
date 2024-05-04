#include <iostream>
#include <wchar.h>
#include "wString.h"
//정적 메서드
const wchar_t* wString::wstrcat(const wchar_t* str1, const wchar_t* str2) //두개의 문자열 합쳐서 리턴해준다.
{
	int size1 = 0, size2 = 0; //각 문자열 크기 계산해주는 변수
	for (int i = 0; str1[i] != '\0'; i++) //null문자 만날때까지 실행
	{
		size1 = i+1; //인덱스 + 1 값이 실제 사이즈
	}
	for (int i = 0; str2[i] != '\0'; i++) //null문자 만날때까지 실행
	{
		size2 = i+1; //인덱스 + 1 값이 실제 사이즈
	}
	int sizeSum = size1 + size2 + 1; //널문자 공간을 위해 1개 더 더한다.
	wchar_t* string = new wchar_t[sizeSum]; //새로운 크기 문자열 동적 할당
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

//기본 생성자
wString::wString()
{
	this->count_char = 0;
	//기본은 null문자로 초기화
	this->string = new wchar_t;
	*(this->string) = '\0';
}
//문자열 입력시 생성자
wString::wString(const wchar_t word[])
{
	SetString(word);
}

//소멸자
wString::~wString()
{
	if (this->string != nullptr)
	{
		delete[] this->string; //메모리 할당 제거
	}
}

// 문자열 가져오는 Get함수 오퍼레이터 ()오버로딩이 잘못 동작될때 사용
const wchar_t* wString::GetString() 
{
	return this->string;
}

// 문자열 할당하는 함수
void wString::SetString(const wchar_t* word)
{
	int size = 0;//전달받은 문자열 사이즈 저장하는 변수
	for (int i = 0; true; i++) //널문자 찾을때까지 반복
	{
		if (*(word + i) == '\0')
		{
			this->count_char = i; //문자 개수는 i개
			size = i + 1; //크기는 인덱스 번호 + 1
			break; //for 문 탈출
		}
	}
	if (this->string != nullptr) //메모리 할당 여부 확인
	{
		delete[] this->string; //문자열 할당 제거
	}
	this->string = new wchar_t[size];  //새로 전달 받은 크기만큼 메모리 동적 할당)

	for (int i = 0; i < size; i++) //글자 수 만큼 반복
	{
		*(this->string + i) = *(word + i); //해당 할당된 주소에 차례대로 문자를 넣는다. (복사)
	}
}

//문자열 개수 리턴 해주는 함수
int wString::Count()
{
	return count_char;
};

//() 연산자 오버로딩
wString::operator const wchar_t* ()
{
	return this->string; // operator() 오버로딩하여 string 필드를 반환
}


//대입 연산자 오버로딩
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
	const wchar_t* string = wString::wstrcat(this->GetString(), other.This.GetString()); //문자열 합친다.
	SetString(string); //문자열 적용
	
	return *this;
}
wString& wString::operator+=(const wchar_t word[])
{	
	const wchar_t* string = wString::wstrcat(this->GetString(), word); //문자열 합친다.
	SetString(string); //문자열 적용
	return *this;
}

//[] 연산자 오버로딩
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