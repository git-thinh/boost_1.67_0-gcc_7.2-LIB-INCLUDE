#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/regex.hpp>

using namespace std;

struct Hello 
{
	Hello(){ 
		cout << "Hello constructor" << endl;
	}

	~Hello(){
		cout << "Hello destructor" << endl;
		cin.get();
	}
};


int main(int argc, char**argv)
{
	//Boost regex, compiled library
	boost::regex regex("^(Hello|Bye) Boost$");
	boost::cmatch helloMatches;
	boost::regex_search("Hello Boost", helloMatches, regex);
	cout << "The word between () is: " << helloMatches[1] << endl;

	//Boost shared pointer, header only library
	boost::shared_ptr<Hello> sharedHello(new Hello);
	
	return 0;
}