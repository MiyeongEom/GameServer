#include "pch.h"
#include "CorePch.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>  

// SpinLock 
// 면접 단골 질문, 멀티쓰레드의 이해도에 대한 질문

// : 존버메타, 어느 한 스레드가 먼저 들어가있으면 기다린다
// 

class SpinLock {
public:
	void lock(){
		// CAS (Compare-And-Swap)
		bool expected = false;
		bool desired = true;

		// CAS 의사코드
	/*	if (_locked == expected) {
			expected = _locked;
			_locked = desired;
			return true;
		}
		else{
			expected = _locked;
			return false;
		}*/
		

		while (_locked.compare_exchange_strong(expected, desired) == false) {
			expected = false;
		}

		/*
		while (_locked) {   // 하나의 스레드가 아닌 동시에 들어와서 락걸수도?

		}
		_locked = true;
		*/
	}

	void unlock(){
		//_locked = false;
		_locked.store(false);
	}

private:
	atomic<bool> _locked = false;   // false - 잠기지 않음 , ture - 잠김
};

// volatile : 컴파일러에게 최적화를 하지 말아줘

int32 sum = 0;
mutex m;
SpinLock spinLock;

void Add()
{
	for (int32 i = 0; i < 10'0000; ++i) {
		lock_guard<mutex> guard(m);
		sum++;
	}
}

void Sub()
{
	for (int32 i = 0; i < 10'0000; ++i) {
		lock_guard<mutex> guard(m);
		sum--;
	}
}

int main()
{

	// 컴파일러 최적화하지 말아 : 왜케 쓸모 없는 짓 왜해. 걍 4를 넣을게
	// volatile : 의도한거야 ㅠ 최적하지 말아 : a = 4만을 넣는게 아니라 모두 넣은 결과값 보여줌
	int32 a = 0;
	a = 1;
	a = 2;
	a = 3;
	a = 4;
	cout << a << endl;

	thread t1(Add);
	thread t2(Sub);

	t1.join();
	t2.join();

	cout << sum << endl;
}
