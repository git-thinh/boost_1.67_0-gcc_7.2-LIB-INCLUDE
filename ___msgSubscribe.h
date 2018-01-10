#ifndef _____MSG_SUBSCRIBE_H
#define _____MSG_SUBSCRIBE_H

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
#include "___msgPublish.h"


template <typename T>
class ___msgSubscribe : public ___msgSubscribeInterface
{
private:
	typedef void (T::*PTR_METHOD_SUBSCRIBE)(T*);
	PTR_METHOD_SUBSCRIBE m_pMethodSubscribe;
	T* m_pClass;
	std::thread m_thread;
public:
	___msgSubscribe() {
		//m_pMethodSubscribe = NULL;
		//m_pClass = NULL;
		//m_thread = 0;
	};
	~___msgSubscribe() {
		//HANDLE hThread = m_thread.native_handle();
		//DWORD dwExit;
		//// actually wait for the thread to exit
		//WaitForSingleObject(hThread, WAIT_INFINITE);
		//// get the thread's exit code (I'm not sure why you need it)
		//GetExitCodeThread(hThread, &dwExit);
		// cleanup the thread
		//CloseHandle(hThread);
		//hThread = NULL;
	};

	virtual void TaskMsgReceiver(T* pClass) = 0;

	void registerSubscribe(T* pClass, PTR_METHOD_SUBSCRIBE pMethodSubscribe)
	{
		m_pClass = pClass;
		m_pMethodSubscribe = pMethodSubscribe;

		//___msgPublish::getInstance().join(pClass, &(typeid(pClass).name()[0]]));
		___msgPublish::getInstance().join(pClass, "");

		m_thread = std::thread([](T* _pClass, PTR_METHOD_SUBSCRIBE _pMethodSubscribe) {
			std::mutex* _mutex = ___msgPublish::getInstance().get_mutexSubscribe();
			std::unique_lock<std::mutex> lk(*_mutex);
			while (true) {
				___msgPublish::getInstance().get_notificationSubscribe()->wait(lk);
				std::cout << " receiver signal ..." << std::endl;
				(_pClass->*_pMethodSubscribe)(_pClass);
			}
		}, m_pClass, m_pMethodSubscribe);
		m_thread.detach();
	}

	void Subscribe() {
		//(m_pClass->*m_pMethodSubscribe)(m_pClass); 
	}
};

#endif // !_____MSG_SUBSCRIBE_H
