#include <cstring>
#include <iostream>

#include "shared_ptr.hpp"

using namespace std;
using namespace hrd22;

class B
{
    public:
        B(int val = 0): m_val(val){}
        int GetVal() {return m_val;}
        void SetVal(int val) {m_val = val;}

    private:
        int m_val;

};

class D : public B
{
	public:
		D(int val = 5):B(),m_dval(val){}
		int m_dval;
};

int main()
{
    int r = 0;
  //  SharedPtr<int> spr(&r);
	SharedPtr<int> sp_int(new int(10));
	cout << *sp_int << endl;
	*sp_int == 10 ? cout << "test passed" << endl :
					cout << "test failed" << endl;

	SharedPtr<B> sp_b1(new B(100));
	cout << sp_b1->GetVal() << endl;
	sp_b1->GetVal() == 100 ? cout << "test passed" << endl :
						  	cout << "test failed" << endl;

	SharedPtr<B> sp_b2(sp_b1);
	cout << sp_b2->GetVal() << endl;
	sp_b2->GetVal() == 100 ? cout << "test passed" << endl :
						  	cout << "test failed" << endl;

	SharedPtr<B> sp_b3(new B(1000));
	cout << sp_b3->GetVal() << endl;
	sp_b3->GetVal() == 1000 ? cout << "test passed" << endl :
						  	cout << "test failed" << endl;

	if(sp_b1 == sp_b2)
		cout << "test passed" << endl;
	else cout << "test failed" << endl;

	sp_b2 = sp_b3;
	cout << sp_b2->GetVal() << endl;
	sp_b2->GetVal() == 1000 ? cout << "test passed" << endl :
						  	cout << "test failed" << endl;

	sp_b3->SetVal(1);
	cout << sp_b3->GetVal() << endl;
	cout << sp_b2->GetVal() << endl;


	cout << sp_b1->GetVal() << endl;

	if(sp_b1 != sp_b2)
		cout << "test passed" << endl;
	else cout << "test failed" << endl;

	if(!sp_b3 == false)
			cout << "test passed" << endl;
	else cout << "test failed" << endl;

	/**********************inheritance***************/
	SharedPtr<D> sp_d1(new D);
	cout << sp_d1->GetVal() << endl;
	cout << (*sp_d1).m_dval << endl;

	cout << sp_b1->GetVal() << endl;
	sp_b1 = sp_d1;

	
	cout << sp_b1->GetVal() << endl;

	SharedPtr<B> sp_b5(sp_d1);

	//sp_d1 = sp_b2; should get compilation error


    return 0;
}