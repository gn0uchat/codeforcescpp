#include<iostream>
#include<functional>

using namespace std;

template <typename T>
class lazy_list{
	private:

	T head;
	
	lazy_list<T> *tail = NULL;

	public:

	function< lazy_list<T>& () > delay;


	lazy_list(){}

	lazy_list( T head ){
		this->head = head;
	}

	lazy_list( T head, function< lazy_list<T>& () > delay ){
		this->head = head;
		this->delay = delay;
	}

	T& car(){
		return this->head;
	}

	lazy_list<T>& cdr(){
		//cout << "cdr" << endl;
		if( this->tail == NULL ){
			this->tail = new lazy_list<T>;
			* this->tail = this->delay();
		}
		return * this->tail;
	}

};

template <typename T>
lazy_list<T>& add( lazy_list<T>& a, lazy_list<T>& b ){
	//cout << a.car() << " plus " << b.car() << endl;
	return *( new lazy_list<T>( a.car() + b.car(), [&]() -> lazy_list<T>& {
				return add( a.cdr(), b.cdr() ); }));
}

template <typename T>
T list_ref( lazy_list<T>& l, int n ){
	//cout << "list_ref " << n << endl;
	if( n == 0 ){
		return l.car();
	}else{
		return list_ref( l.cdr(), n - 1 );
	}
}

int main(){

	int i = 0;

	lazy_list<int> fib1( 1 );

	lazy_list<int> fib( 0, [&]()-> lazy_list<int>&{ return fib1; } );

	fib1.delay = [&]() -> lazy_list<int>& {
		return add<int>( fib, fib1 );
	};

	int n = 100;
	
	///*
	cout << list_ref( fib, n );
	//*/

	///*
	int f[2] = {0, 1};

	for( int i = 0; i <= n - 2; i ++ ){
		f[ i % 2 ] = f[ 0 ] + f[ 1 ];
	}

	cout << f[ n % 2 ];
	//*/
	return 0;
}
