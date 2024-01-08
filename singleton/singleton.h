
#include<iostream>

// Singleton  basic
class Singleton {
	public:

		static Singleton* getInstance() {

			static Singleton* instance = new Singleton();

			/*if(!instance) {
				instance = new Singleton();
				return instance;
			}

			else return instance;*/
			return instance;

		}

		//Singleton(const Singleton&) = delete;

		private:

		Singleton() {

			std::cout<<"constructor called"<<std::endl;

		}

		int data1;
		int data2;

		static Singleton* instance;

};
