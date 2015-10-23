#include <iostream> 
using namespace std; 
int main( ) {
	double tx[] = {0.005, 0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1.0, 2.0 }; 
	double ty[] = {0.924, 0.896, 0.859, 0.794, 0.732, 0.656, 0.536, 0.43, 0.316}; 
	int len = 9 ;


	// Initiate a matrix; 
	double M[len][len]; 
	for(int i=0; i<len; ++i) {
		for (int j=0; j<len; ++j) {
			M[i][j] = 0; 
		}
	}
	for(int i=0; i<len; ++i) {
		M[i][0] = ty[i]; 
	}
	//double inter = 0.032; 
	double inter = 1.682; 
	for (int i = 1; i < len; i++) {
    	for (int j = 1; j <= i; j++) {
        	M[i][j] = ((inter - tx[i-j])*(M[i][j-1]) 
        		- (inter - tx[i])*(M[i-1][j-1]))/(tx[i] - tx[i - j]);
 	   }
	}

    cout << M[8][8] << endl; 
	return 0; 
}