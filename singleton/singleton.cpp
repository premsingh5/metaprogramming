#include<iostream>
#include "singleton.h"
using namespace std;

int main() {
//	Singleton* Singleton::instance = 0;
	auto res = Singleton::getInstance();
	Singleton::getInstance();
//	Singleton::instance = 0;	
	
}

