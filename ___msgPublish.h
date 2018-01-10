#ifndef _____MSGPUBLISH
#define _____MSGPUBLISH

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>
#include <cstdarg>

#include <atomic>
#include <queue>
#include <map>

#include "___msgSubscribeInterface.h"

class ___msgPublish
{	
// [ SINGLETON ]	 
public:
	static ___msgPublish& getInstance()
	{
		static ___msgPublish    instance;
		return instance;
	}
private:
	___msgPublish() {}
	~___msgPublish() {}
public:
	___msgPublish(___msgPublish const&) = delete;
	void operator=(___msgPublish const&) = delete;

//end  [ SINGLETON ]

private: 
	std::mutex m_mutexSubscribe;
	std::condition_variable m_notificationSubscribe;
	
	std::queue<char*> m_MSG;
	std::vector<void*> m_Subscribe;
	//std::map<void*, void*> m_Items; 
public:  
	std::mutex* get_mutexSubscribe(){ return &m_mutexSubscribe; }
	std::condition_variable* get_notificationSubscribe(){ return &m_notificationSubscribe; }
	
	void join(void* pClient, const char* pName) {
		m_Subscribe.push_back(pClient); 
		//m_Items.insert(pClient, pFunc); 
		std::cout << "registerSubscribe(): " << pName << " = " << pClient << std::endl;
	}

	void sendBroadcast(char* pData) {
		std::cout << "sendBroadcast(): " << m_Subscribe.size() << " = " << pData << std::endl;
		
		//for (std::vector<void*>::iterator it = m_Subscribe.begin(); it != m_Subscribe.end(); ++it) {
		//	___msgSubscribeInterface* p = (___msgSubscribeInterface*)(*it);
		//	if (p != NULL) {
		//		p->m_pData = pData;
		//		p->Subscribe();
		//	}
		//}
		
		std::unique_lock<std::mutex> lk(m_mutexSubscribe);
		m_MSG.push(pData);
		char *pBufMsg = m_MSG.front();
		m_MSG.pop();
		// if(m_pipeOpen == true)
		// 	WriteFile(m_pipeHandle, pBufMsg, strlen(pBufMsg) + 1, NULL, NULL);
		delete pBufMsg; 
		lk.unlock();
		m_notificationSubscribe.notify_all();
	}

	void release() {
		std::cout << "release(): " << m_Subscribe.size() << std::endl;
		for (std::vector<void*>::iterator it = m_Subscribe.begin(); it != m_Subscribe.end(); ++it) {
			//___msgSubscribe* p = (___msgSubscribe*)*it;
			void* p = *it;
			//if (p != NULL)  delete p;
		}
	}
};

#endif // !_____MSGPUBLISH
