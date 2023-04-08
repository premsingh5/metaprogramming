//Linearizing typelists
#define TYPELIST_1(T) TypeLists<T, NULLTYPE>
#define TYPELIST_2(H,T) TypeLists<H, TYPELIST_1(T)>
#define TYPELIST_3(a,b,c) TypeLists<a, TYPELIST_2(b,c)>
// nulltype
struct NULLTYPE{
};
//typelists
template<typename H, typename T>
class TypeLists{
	public:
		typedef H HEAD;
		typedef T TAIL;
};
//typelist with one type
template<typename H>
class TypeLists<H,NULLTYPE>{
	public:
		typedef H HEAD;
		typedef NULLTYPE TAIL;
};
/// ************ Length calculation at compile time ***********///
template<typename T>
struct Length{};
template<typename H,typename T>
struct Length<TypeLists<H,T> >{
	enum { length = 1+Length<T>::length};
};

template<>
struct Length<NULLTYPE>{
	enum { length = 0};
};
////********* Indexed access *******//

template<typename T,int n>
struct TypeAt{};
template<typename H,typename T,int n>
struct TypeAt<TypeLists<H,T>,n>{
	typedef typename TypeAt<T,n-1>::result result;
};
template<typename H,typename T>
struct TypeAt<TypeLists<H,T>,0>{
	typedef H result;
};
/////*** Search ****///
template<typename TList, typename T>
struct IndexOf{};
template<typename T>
struct IndexOf<NULLTYPE,T>{
	enum { value = -1};
};
template<typename HEAD,typename TAIL>
struct IndexOf<TypeLists<HEAD,TAIL>, HEAD>{
	enum { value = 0};
};
template<typename HEAD,typename TAIL,typename T>
struct IndexOf<TypeLists<HEAD,TAIL>,T>{
	private:
		enum { temp = IndexOf<TAIL,T>::value };
	public:
	enum{ value = (temp == -1) ? -1 : 1+temp};
};





