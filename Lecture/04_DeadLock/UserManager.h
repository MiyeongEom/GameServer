#pragma once
#include <mutex>

class User {
	//~~
};

class UserManager{
public:
	static UserManager* Instance()
	{
		static UserManager instance;
		return &instance;
	}

	User* GetUser(int32 id)
	{
		lock_guard<mutex> guard(_mutex);
		// 뭔가를 갖고 옴
		return nullptr;
	}

	void ProcessSave();

private:
	mutex _mutex;
};

