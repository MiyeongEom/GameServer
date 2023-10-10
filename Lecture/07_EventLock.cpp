#include "pch.h"
#include "CorePch.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>  
#include <windows.h>  //event

// event lock
// 갑질메타, 관리자한테 부탁함.

mutex m;
queue<int32> q;
HANDLE handle;

void Producer() {
	while (true) {
		unique_lock<mutex> lock(m);
		q.push(100);
	}
	::SetEvent(handle);
	this_thread::sleep_for(1000ms);
}

void Consumer() {   // 얘 무한루프 -> 낭비
	while (true) {
		::WaitForSingleObject(handle, INFINITE); // 잠들다
		// 작업후 자동으로 Non-Signal 됨
		unique_lock<mutex> lock(m);
		if (q.empty() == false) {
			int32 data = q.front();
			q.pop();
			cout << data << endl;
		}
	}
}

int main()
{
	// 커널 오브젝트
	// Usage Count
	// Siginal (파란불), Non-Signal(빨간불) << bool
	// Auto / Manual << bool
	handle = ::CreateEvent(NULL/*보안속성*/, FALSE/*bManualReset*/, FALSE/*binitialState*/, NULL);
	
	thread t1(Producer);
	thread t2(Consumer);

	t1.join();
	t2.join();

	::CloseHandle(handle);
}
