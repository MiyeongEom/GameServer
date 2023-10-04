#include "pch.h"
#include "CorePch.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>  //lock

// push_back
// [1][2][3]
// [1][2][3][][][] 더 큰 메모리를 만들고 복사, 기존꺼 없앰

vector<int32> v;
// atomic -> vector 이용은 어려움

// mutual exclusive (상호배타적)
mutex m;
// 재귀적으로 X
// lock을 했는데 뒤에서 안풀어주면 안됨
// 이 lock의 범위에 따라 많이 바뀜

// RAII (Resource Acquisition Is Initialization)
template <typename T>
class LockGuard{
public:
	LockGuard(T& n) {
		_mutex = &n;
		_mutex->lock;
	}
	~LockGuard() {
		_mutex->unlock;
	}
private:
	T* _mutex;
};

void Push()
{
	for (int32 i = 0; i < 10000; ++i) {
		//m.lock(); // 자물쇠 채우는 느낌 (접근 불가)
		LockGuard<mutex> lockGuard(m); // -> 객체 생성되며 락 걸림, 나오면서 소멸되며 락 풀림
		v.push_back(i);
		if (i == 5000) {
			//m.unlock();  //이거 안해주면 망함  -> 근데 매번 이렇게? 복잡하다 -> RAII
			break;
		}

		//m.unlock();  // 자물쇠 풀기
	}
}

int main()
{
	//v.reserve(20000); // 값은 나오지만, 몇 개 없어짐
	thread t1(Push);
	thread t2(Push);

	t1.join();
	t2.join();

	cout << v.size() << endl;
}