#ifndef _____msgSubscribeInterface
#define _____msgSubscribeInterface

class ___msgSubscribeInterface
{
public:
	char* m_pData;
public:
	___msgSubscribeInterface() :m_pData(0) {}
	virtual ~___msgSubscribeInterface() {}
	virtual void Subscribe() = 0;
};

#endif // !_____msgSubscribeInterface
