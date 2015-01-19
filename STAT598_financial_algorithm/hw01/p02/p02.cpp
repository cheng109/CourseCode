#include <iostream>

# define SUCCESS 0;

using namespace std;

int combine(int n, int k) {
	if(n==k || k==0) return 1;
	return combine(n-1,k-1)+combine(n-1, k);
}

int main() {
	cout << combine(30, 6) << endl;
	return SUCCESS;
}



