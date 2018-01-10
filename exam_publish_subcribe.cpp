#include "_testClass.h"
#include "___msgPublish.h"
#include <iostream>

int main()
{ 
	_testClass* p1 = new _testClass;
	_testClass* p2 = new _testClass; 

	std::cout << "Input text to send broadCast: ";
	std::string a;
	while (a != "exit") {
		std::cin >> a;
		___msgPublish::getInstance().sendBroadcast((char*)a.c_str());		
	} 

	___msgPublish::getInstance().release();
	   
	return 0;
}

