#pragma once
#include <iostream>

//wchar_t 배열 동적으로 제어하기 위한 클래스
class wString
{
public:
	
	const wchar_t* wstrcat(const wchar_t* str1, const wchar_t* str2); //문자열 두개 합쳐주고 리턴해주는 함수

	const wchar_t* GetString(); // 문자열 가져오는 Get함수 오퍼레이터 ()오버로딩이 잘못 동작될때 사용

	wString& This = *this; //인스턴스를 가리키는 필드 맴버 이름 호출시 this를 호출할 방법이 없어서 필드로 리턴해준다.

	wString(); //기본 생성자
	wString(const wchar_t string[]); //문자 대입용 생성자

	~wString(); //소멸자

	int Count(); //문자 개수 리턴해주는 함수

	operator const wchar_t* (); // () 오버로딩
	wchar_t& operator[] (int index); // [] 오버로딩
	//대입 연산자 오버로딩
	wString& operator=(const wString& other); //클래스 대입시
	wString& operator=(const wchar_t word[]); //문자열 대입시
	wString& operator+=(const wString& other); //클래스 대입시
	wString& operator+=(const wchar_t word[]); //문자열 대입시

private:
	wchar_t* string; //동적 문자열 주소 가지고 있는 포인터
	int count_char; //문자 갯수 저장하는 필드

	void SetString(const wchar_t* word); //문자열 주소 동적으로 할당해주는 함수
};
