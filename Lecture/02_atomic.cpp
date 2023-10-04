#include "pch.h"
#include "CorePch.h"
#include <iostream>
#include <thread>
#include <atomic>

// atomic : All - Or - Nothing

// DB -> 여기서도 아토믹한 상황 있음
// A라는 유저인벤에서 집행검을 빼고
// B라는 유저 인벤에서 집행검을 추가

atomic<int32> sum = 0;

void Add()
{
	for (int32 i = 0; i < 100'0000; ++i) {
		sum.fetch_add(1);
		//sum++;  -> 한 줄 코드지만 3번에 나뉘어 작업함
		/*
		int32 eax = sum;
		// eax = 0
		eax = eax + 1;
		// eax = 1;
		sum = eax;
		// sum = 1
		*/
	}
}

void Sub()
{
	for (int32 i = 0; i < 100'0000; ++i) {
		sum.fetch_add(-1);
		//sum--;  
		/*
		int32 eax = sum;
		// eax = 0
		eax = eax - 1;
		// eax = -1;
		sum = eax;
		// sum = -1
		*/
	}
}

int main()
{
	Add();
	Sub();
	cout << sum << endl;

	thread t1(Add);
	thread t2(Sub);
	t1.join();
	t2.join();
	cout << sum << endl;

	// 왜 멀티쓰레드 상황에서 다른가?
	// 데이터 공유 상황에서의 문제점
	// 이 공유 데이터를 수정하기 시작하면 문제가 생기게 됨
	// -> 순서가 보장되어야 함
}