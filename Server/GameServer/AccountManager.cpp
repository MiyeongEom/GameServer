#include "pch.h"
#include "AccountManager.h"
#include "UserManager.h"

void AccountManager::ProcessLogin()
{
	// 락순서 account 먼저로 맞춰주기
	//accountLock
	lock_guard<mutex> guard(_mutex);

	// userLock
	User* user = UserManager::Instance()->GetUser(100);
}