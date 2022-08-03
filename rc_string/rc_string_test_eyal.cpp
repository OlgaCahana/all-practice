#include <cstdio>		/* 	puts, printf */

#include "rc_string.hpp"


using namespace ilrd;
using namespace std;


typedef enum results
{
	GOOD = 0
	
}res_ty;

static char res_str[20][60] = 	{ 		
									"Nothing to Report 🆗️"
																		
								};
								
static int Testrc_string(void);
static void Intro(void);
static void Outro(void);

int TestModule1(void);
int TestModule2(void);
int TestModule3(void);
int TestModule4(void);
int TestModule5(void);
int TestModule6(void);

int main(void)
{
	
	int rc_string_status = 0;
	Intro();
	
	rc_string_status = Testrc_string();

	printf("Exit Status Task: %d \n%s\n",
	       rc_string_status,
	       res_str[rc_string_status]);
	       

	putchar('\n');
	
	Outro();
	return rc_string_status;
}

static int Testrc_string(void)
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
	RCString s1 = "bob";
	RCString s2 = s1;
	RCString s3(s1);
	RCString s4 = s2;

	cout << "s3:" << s3 << endl;
	cout << "s2:" << s2 << endl;
	DEBUG_ONLY(cout << "s1 ref= " << s1.DBG_GetRefCount() << s1.Cstr() << endl)
	DEBUG_ONLY(cout << "s2 ref= " << s2.DBG_GetRefCount() << s2.Cstr() << endl)
	DEBUG_ONLY(cout << "s3 ref= " << s3.DBG_GetRefCount() << s3.Cstr() << endl)
	DEBUG_ONLY(cout << "s4 ref= " << s4.DBG_GetRefCount() << s4.Cstr() << endl)

	cout << "assignment s3" <<endl; /*	TODO: assignment S3 */ 
	s3 = "bob2";

	DEBUG_ONLY(if(1 != s3.DBG_GetRefCount())
	{
		LOG("Bad new reference");
		return 1;
	})
	DEBUG_ONLY(if(3 != s1.DBG_GetRefCount())
	{
		LOG("Bad old reference");
	DEBUG_ONLY(cout << "s1 ref= " << s1.DBG_GetRefCount() << s1.Cstr() << endl)
        
		return 2;
	})

	if(!(s1 == s2))
	{
		LOG("bad op ==");
		return 1;
	}
	if(s1 == s3)
	{
		LOG("bad op == MISMATCH");
		return 2;
	}
	if(!(s1 == "bob"))
	{
		LOG("bad op ==");
		return 3;
	}
	if(!("bob" == s1))
	{
		LOG("bad op ==");
		return 4;
	}
	if(!(s3 > s2))
	{
		LOG("bad op >");
		return 1;
	}
	if(s2 > s3)
	{
		LOG("bad op >");
		return 2;
	}
	if(s1 > s2)
	{
		LOG("bad op >");
		return 3;
	}
	if(s1 < s2)
	{
		LOG("bad op <");
		return 1;
	}
	if(s2 < s1)
	{
		LOG("bad op <");
		return 1;
	}
	if(s3 < s2)
	{
		LOG("bad op <");
		return 3;
	}
	if(!(s1 < s3))
	{
		LOG("bad op <");
		return 4;
	}

	cout << "operator[] non const s1" <<endl;

	s1[2] = 'j';
	if(!(s1 == "boj"))
	{
		LOG("bad op [] + assignment");
		return 1;
	}
	DEBUG_ONLY(if(1 != s1.DBG_GetRefCount())
	{
		LOG("ref reset failed after assignment");
		return 1;
	})
	DEBUG_ONLY(if(2 != s2.DBG_GetRefCount())
	{
		LOG("ref dec failed after assignment");
		return 1;
	})


	DEBUG_ONLY(cout << "s2 before operator[] const:" << s2.DBG_GetRefCount() << s2.Cstr() << endl)

	if(!(static_cast<const RCString>(s2)[2] == 'b'))
	{
		LOG("bad const [] ret value");
		return 1;
	}
	DEBUG_ONLY(if(2 != s2.DBG_GetRefCount())
	{
		LOG("ref dec failed after assignment");
		return 2;
	})

	DEBUG_ONLY(cout << "s1 ref=" << s1.DBG_GetRefCount() << s1.Cstr() << endl)
	DEBUG_ONLY(cout << "s2 ref=" << s2.DBG_GetRefCount() << s2.Cstr() << endl)
	DEBUG_ONLY(cout << "s3 ref=" << s3.DBG_GetRefCount() << s3.Cstr() << endl)
	DEBUG_ONLY(cout << "s4 ref=" << s4.DBG_GetRefCount() << s4.Cstr() << endl)

	cin >> s4;
	cout << s4 << endl;
	DEBUG_ONLY(if(1 != s4.DBG_GetRefCount())
	{
		LOG("ref dec failed after cin >>");
		return 3;
	})
	DEBUG_ONLY(if(1 != s2.DBG_GetRefCount())
	{
		DEBUG_ONLY(cout << "s1 ref=" << s1.DBG_GetRefCount() << s1.Cstr() << endl)
		DEBUG_ONLY(cout << "s2 ref=" << s2.DBG_GetRefCount() << s2.Cstr() << endl)
		DEBUG_ONLY(cout << "s3 ref=" << s3.DBG_GetRefCount() << s3.Cstr() << endl)
		DEBUG_ONLY(cout << "s4 ref=" << s4.DBG_GetRefCount() << s4.Cstr() << endl)
		LOG("ref dec failed after s4 cin");
		return 2;
	})
	const RCString s5(s1);

	/*no const gets const*/
	s1[0] = s5[2];
	
	/*no const gets non const*/
	s1[1] = s2[2];

	char cstring[10] = "lalalala";

	/* char * gets char RCString::operator[](std::size_t index_) const; */
	cstring[2] = s5[2];

	cout << cstring << endl;

	/* operator char() const */
	char b = s5[2];
	if(b != s5[2])
	{
		LOG("conversion from proxy to char failed");
		return 1;
	}

	/* operator& */
	char *ch_ptr = &s1[2];
	
	// getting address of const member - not possible
	// const char *lulu = &s5[2]; 



	return GOOD;
}
int TestModule2(void)
{
	
	return GOOD;
}
int TestModule3(void)
{
	
	return GOOD;
}

int TestModule4(void)
{
	
	return GOOD;
}
int TestModule5(void)
{
	
	return GOOD;
}

int TestModule6(void)
{
	
	return GOOD;
}
static void Intro(void)
{
	putchar('\n');
	puts("Author: Eyal May");
	puts("Reviewer: ");
	putchar('\n');
}

static void Outro(void)
{
	putchar('\n');
	puts("Thank You, Come Again Soon!! 😁️");
	putchar('\n');
}
