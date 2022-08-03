#include <cstdio>		/* 	puts, printf */
#include <iostream>		/*		*/ 

#include "shared_ptr.hpp"


using namespace hrd22;
using namespace std;


typedef enum results
{
	GOOD = 0
	
}res_ty;

static char res_str[20][60] = 	{ 		
									"Nothing to Report 🆗️"
																		
								};
								
static int Testshared_ptr(void);
static void Intro(void);
static void Outro(void);

int TestModule1(void);
int TestModule2(void);
int TestModule3(void);
int TestModule4(void);
int TestModule5(void);
int TestModule6(void);

class X
{
public:
	X(size_t def = 3): m_nothing(def){}
	virtual ~X(){} //stop javastyling please
	void virtual Print(){std::cout << "X JavaStyle is forbidden" << std::endl;}
private:
	size_t m_nothing;
};

class Y : public X
{
public:
	Y(size_t def = 5) : X(), m_nothing2(def){}
	void Print(){std::cout << "Y JavaStyle is forbidden, stop using it" << std::endl;}
private:
	size_t m_nothing2;
};


int main(void)
{
	
	int shared_ptr_status = 0;
	Intro();
	
	shared_ptr_status = Testshared_ptr();

	printf("Exit Status Task: %d \n%s\n",
	       shared_ptr_status,
	       res_str[shared_ptr_status]);
	       

	putchar('\n');
	
	Outro();
	return shared_ptr_status;
}

static int Testshared_ptr(void)
{
	int func_status = GOOD;
	int return_status = func_status;
	
	func_status = TestModule1();	
	if(!return_status)
	{
		return_status = func_status;
	}
	
	func_status = TestModule2();	
	if(!return_status)
	{
		return_status = func_status;
	}
	
	func_status = TestModule3();	
	if(!return_status)
	{
		return_status = func_status;
	}
	
	func_status = TestModule4();	
	if(!return_status)
	{
		return_status = func_status;
	}
	
	func_status = TestModule5();	
	if(!return_status)
	{
		return_status = func_status;
	}
	
	func_status = TestModule6();	
	if(!return_status)
	{
		return_status = func_status;
	}
	
	return return_status;
}

int TestModule1(void)
{
	SharedPtr<int> ptr1(new int(3)); //ctor test
	if(3 != *ptr1)
	{
		std::cout << "operator * read has failed" << std::endl;
		return 1;
	}
	*ptr1 = 4;
	if(4 != *ptr1)
	{
		std::cout << "operator * write has failed" << std::endl;
		return 2;
	}

	SharedPtr<int> ptr2; //ctor without paramater
	ptr2 = ptr1;
	if(4 != *ptr2)
	{
		std::cout << "operator= failed" << std::endl;
		return 3;
	}

	SharedPtr<int>ptr4(ptr2);
/* .......................................................................... */
						/* Boolean Operator tests */
/* .......................................................................... */

	SharedPtr<int> ptr3(new int(1));

	if(ptr1 != ptr2)//the same
	{
		std::cout << "operator != failed" << std::endl;
		return 4;
	}

	if(!(ptr3 != ptr2))//not the same
	{
		std::cout << "operator != failed" << std::endl;
		return 5;
	}

	if(!(ptr1 == ptr2))//the same
	{
		std::cout << "operator == failed" << std::endl;
		return 4;
	}

	if(ptr1 == ptr3)//not the same
	{
		std::cout << "operator == failed" << std::endl;
		return 5;
	}

	ptr1 = ptr3;
	std::cout << "1 dealloc should have been called by now" << std::endl;


	return GOOD;
}
int TestModule2(void)
{
	
	SharedPtr<unsigned char> ptr1(new unsigned char(30));
	SharedPtr<unsigned char> ptr2;


	if(!ptr1)//contains valid ptr
	{
		std::cout << "operator ! failed" << std::endl;
		return 1;
	}
	if(!!ptr2)//contains null
	{
		std::cout << "operator ! failed" << std::endl;
		return 2;
	}

	return GOOD;
}
int TestModule3(void)
{
	SharedPtr<X>x_ptr(new X);
	x_ptr->Print();

	return GOOD;
}

int TestModule4(void)
{
	
	SharedPtr<X> x_ptr(new Y);
	x_ptr->Print(); //expecting Y print


	/* SharedPtr<Y> y_ptr(new X); //!uncomment to assert compilation error - upcasting
	 y_ptr->Print();   */

	return GOOD;
}
int TestModule5(void)
{
	std::cout << "Test5" << std::endl;
	
	SharedPtr<X> x_ptr(new X);

	SharedPtr<X> y_ptr(new Y);
	SharedPtr<Y> yy_ptr(new Y);

	std::cout << "Expecting next line dealloc" << std::endl;
	x_ptr = y_ptr;
	std::cout << "is there a dealloc above this line?" << std::endl;
	std::cout << "Expecting next line dealloc" << std::endl;
	y_ptr = yy_ptr;
	x_ptr = SharedPtr<X>(new X); //assigning from last reference to something else
	std::cout << "is there a dealloc above this line?" << std::endl;

	/* yy_ptr = x_ptr; */ //! uncomment to assert compilation error
	return GOOD;
}

int TestModule6(void)
{
	SharedPtr<int> int_ptr(new int(1));
	SharedPtr<const int> cint_ptr(new int(8));

	*int_ptr = *cint_ptr;

	if(8 != *int_ptr)
	{
		std::cout << *int_ptr << "expected 8" << std::endl;
		return 8;
	}

	/* *cint_ptr = 7; *///!uncomment to assert compilation error - assignment to read-only location


	return GOOD;
}
static void Intro(void)
{
	putchar('\n');
	puts("Author: Eyal May");
	puts("Reviewer: Larisa Kryshtul");
	putchar('\n');
}

static void Outro(void)
{
	putchar('\n');
	puts("Thank You, Come Again Soon!! 😁️");
	putchar('\n');
}
