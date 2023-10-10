#include "pch.h"
#include "CorePch.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>  

// sleep, 랜덤 메타 
// 실행 소유권 포기

class SpinLock {
public:
	void lock() {
		// CAS (Compare-And-Swap)
		bool expected = false;
		bool desired = true;

		while (_locked.compare_exchange_strong(expected, desired) == false) {
			expected = false;
			this_thread::sleep_for(1ms);  // 1ms동안 스케줄되지 않음
			//this_thread::yield();  //시간지정없이 일단 선점되어 양보, = this_thread::sleep_for(0ms)
		}
	}

	void unlock() {
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

	thread t1(Add);
	thread t2(Sub);

	t1.join();
	t2.join();

	cout << sum << endl;
}
