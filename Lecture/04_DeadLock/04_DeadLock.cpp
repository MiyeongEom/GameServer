#include "pch.h"
#include "CorePch.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>  //lock
#include "AccountManager.h"
#include "UserManager.h"

void Func1()
{
	for (int32 i = 0; i < 1000; ++i)
		UserManager::Instance()->ProcessSave();
}

void Func2()
{
	for (int32 i = 0; i < 1000; ++i)
		AccountManager::Instance()->ProcessLogin();
}

int main()
{
	// lcok을 안 닫아주는건 1차원적 문제
	// 좀더 까다로운 문제가 생기는 문제 -> nullptr, deadlock 등

	thread t1(Func1);
	thread t2(Func2);

	t1.join();
	t2.join();

	// 무한 대기 걸림 -> 교착 상태
	// Lock 2개 -> 순서가 다른 경우 어디 먼저 잠궈? :  락순서 필요

	cout << "Jobs Done" << endl;

	// deadlock -> 동접이 많아질 때마다 터질 확률 올라감
	// 락 사이의 순서를 맞추기 위해 번호(ID)를 부여하기도

	// 참고
	mutex m1;
	mutex m2;
	lock(m1, m2); // m1.lock()  m2.lock()
	lock_guard<mutex> g1(m1, adopt_lock);
	lock_guard<mutex> g1(m1, adopt_lock);
	// adopt_lock : 이미 lock된 상태니까, 나중에 소멸될 때 풀어주기만 해
}

// 이미 락에 걸린 상황에서 ?
// 1. 기다린다 - 스핀락 (면접 자주)
//  - 나오기 전까지 시간을 낭비
//  - 왔다갔다 하는 비용을 줄임
// 2. 자리로 되돌아가고 나중에 다시 (슬립)
//  - 운빨에 맡김
// 3. 직원에게 맡김 (이벤트)