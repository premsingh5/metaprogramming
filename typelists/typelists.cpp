#include<iostream>
#include "typelists.h"

int main(){
	typedef TYPELIST_3(int,float,char) t;
	std::cout<<Length<t>::length<<std::endl;
	std::cout<<IndexOf<t,float>::value<<std::endl;
	int i,j;
	std::cin>>i>>j;
	switch(i){
		case 0:{
				   TypeAt<t,0>::result r = j;
				   std::cout<<r<<std::endl;
				   break;
			   }
		case 1:{
				   TypeAt<t,1>::result r = j;
				   std::cout<<r<<std::endl;
				   break;
			   }
		case 2:{
				   TypeAt<t,2>::result r = j;
				   std::cout<<r<<std::endl;
				   break;
			   }
		default:
			   std::cout<<"default"<<std::endl;
	}

}
