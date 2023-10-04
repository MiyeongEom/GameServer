#pragma once
#include <mutex>

class Account {
	// ID, 이름 등 온갖 정보
};

class AccountManager{
public:
	static AccountManager* Instance() 
	{
		static AccountManager instance;
		return &instance;
	}

	Account* GetAccount(int32 id)
	{
		lock_guard<mutex> guard(_mutex);
		// 뭔가를 갖고 옴
		return nullptr;
	}

	void ProcessLogin();

private:
	mutex _mutex;
	// map<int32, Account*> _accounts;  // 일련의 아이디와 계정
};

