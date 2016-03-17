#include <bits/stdc++.h>
#include "../../utils.h"

using namespace std;

int main() {
	cout<<"--utils: qpow()"<<endl;
	cout<<"case 2^10 % (1e9+7)"<<endl;
	cout<<acm::utils::qpow(2, 10, 1e9+7)<<endl;
	cout<<"case 1e9 + 8 % (1e9+7)"<<endl;
	cout<<acm::utils::qpow(1e9 + 8, 1, 1e9+7)<<endl;
	cout<<"--"<<endl;
	cout<<"--utils::qmul()"<<endl;
	cout<<"case 11 * 11 % (1e9+7)"<<endl;
	cout<<acm::utils::qmul(11, 11, 1e9+7)<<endl;
	cout<<"case 2 * (5e8+4) % (1e9+7)"<<endl;
	cout<<acm::utils::qmul(5e8 + 4, 2, 1e9+7)<<endl;
	cout<<"--"<<endl;
	cout<<"--utils::reverse()"<<endl;
	/*
	cout<<"case 11 * 11 % (1e9+7)"<<endl;
	cout<<acm::utils::qmul(11, 11, 1e9+7)<<endl;
	cout<<"case 2 * (5e8+4) % (1e9+7)"<<endl;
	cout<<acm::utils::qmul(5e8 + 4, 2, 1e9+7)<<endl;
	*/
	cout<<"--"<<endl;
	cout<<"--utils::gcd()"<<endl;
	cout<<"--"<<endl;
	cout<<"--utils::extgcd()"<<endl;

	return 0;
}
