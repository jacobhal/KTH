#include <stdio.h>
#include <iostream>
#include <vector>
// GMP
#include <gmpxx.h>
#include <gmp.h>

// Own header files
#include "factorial.h"

using namespace std;

int main() {

    vector<mpz_class> data;
    vector<mpz_class> tmp;
    mpz_class res;
    bool IP = false;

    srand(time(NULL));
    string line;
    while(getline(cin, line)) {
        mpz_class n = (mpz_class) line;
        IP = is_prime(n.get_mpz_t(), 3);

        // Print if prime
        if(IP) {
            cout << line << endl;
        } 
        // Perform Pollard Rho or Trial Division
        else 
        {
            // Perform Pollard Rho for larger numbers
            if(n > 1000000) {
                bool factorization_success = true;

                while(n > 1) {

                    res = pollard_rho(n);

                    // If still no result, mark this number as failed
                    if(res == -1) {
                        factorization_success = false;
                        cout << "fail\n";
                        break;
                    }

                    // If the factor returned is not prime, perform trial division to get the full prime factorization
                    if(is_prime(res.get_mpz_t(), 2)) {
                    	data.push_back(res);
                    } else {
                    	tmp = trial_division(res);
                    	for(int i = 0; i < tmp.size(); ++i) {
                    		data.push_back(tmp[i]);
                    	}
                    }

                    // Compute next n
                    n = n/res;
                    // If the next n is prime we are done
                    if(is_prime(n.get_mpz_t(), 2)) {
                        data.push_back(n);
                        break;
                    }   
                    
                }
                // Print numbers if we got all prime factors
                if(factorization_success) {
                    for(int i = 0; i < data.size(); ++i) {
                        cout << data[i] << endl;
                    }
                }
            } else { 
                data = trial_division(n); // Perform trial division for smaller numbers
                for(int i = 0; i < data.size(); ++i) {
                    cout << data[i] << endl;
                }
            }


        }
        data.clear();
        cout << endl;
    }


    return 0;
}