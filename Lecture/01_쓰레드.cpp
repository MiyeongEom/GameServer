#include "pch.h"
#include "CorePch.h"
#include <iostream>
#include <thread>

// 서버는 다른 컴퓨터에서 연결이 가능하도록
// 대기 상태로 상시 실행 중인 프로그램

// 웹 서버 
// 드물게 정보 요청/갱신
// 실시간 상호작용이 필요하지 않음
// 웹 서비스를 만드는 데 사용
// 처음 만드는 경우보단 프레임 워크를 하나 골라서 사용

// 게임서버
// 요청과 갱신 횟수가 많음
// 실시간 상호작용 필요
// 언제라도 클라에 접근 가능
// 게임/장르에 따라 요구사항이 너무나도 다르다

#include <iostream>
#include <thread>

void HelloThread()
{
	cout << "Hello Thread" << endl;
}

void HelloThread_2(int32 num)
{
	cout << num << endl;
}

int main()
{
	// thread t(HelloThread); // 새로운 쓰레드

	// int32 count = t.hardware_concurrency(); CPU 코어 개수?
	// auto id = t.get_id(); 쓰레드마다 id

	// t.detach(); std:thread 객체에서 실제쓰레드 분리
	
	vector<thread> v;

	for (int32 i = 0; i <10; ++i)
		v.push_back(thread(HelloThread_2, i));

	for (int32 i = 0; i < 10; ++i) {
		if (v[i].joinable()) // 쓰레드 살아있니
			v[i].join(); // 우리가 만든 쓰레드 t 대기
	}
	cout << "Hello Main" << endl;
}