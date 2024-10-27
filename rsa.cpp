#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <numeric>
#include <vector>

using namespace std;

class RSA {

    private:
        long long e;
        long long n;
        long long m;
        vector<long long> c;
        vector<long long> decryptedInt;
        vector<string> decryptedString;

    public:
        RSA(long long e, long long n, long long m, vector<long long> c) {
            this->e = e;
            this->n = n;
            this->m = m;
            this->c = c;
        }
        
        void compute() {
            long long p, q;
            stringstream factors = primeFactors(n);
            factors >> p >> q;

            long long phi = (p-1)*(q-1);
            long long d = modInverse(e, phi);
            
            for (int i = 0; i < c.size(); i++) {
                long long text = modPow(c[i], d, n);
                decryptedInt.push_back(text);
                decryptedString.push_back(toAlpha(text));
            }

            printVariables(p, q, phi, d);
            printDecrypted();
        }

    private:
        long long modInverse(long long e, long long phi) {
            if (std::gcd(e, phi) > 1) {
                return -1;
            }
            for (long long i = 1; i < phi; i++) {
                if (((e % phi) * (i % phi)) % phi == 1) {
                    return i;
                }
            }
            return -1;
        }

        stringstream primeFactors(long long n) { 
            stringstream res;
 
            while (n % 2 == 0) { 
                res << 2 << " ";
                n = n / 2; 
            } 

            for (long long i = 3; i <= sqrt(n); i = i + 2) { 
                while (n % i == 0) { 
                    res << i << " ";
                    n = n / i; 
                } 
            } 

            if (n > 2) {
                res << n << " ";
            }

            return res;
        }

        long long modPow(long long base, long long exp, long long mod) {
            long long result = 1;
            base = base % mod;
            while (exp > 0) {
                if (exp % 2 == 1) {
                    result = (result * base) % mod;
                }
                exp = exp >> 1;
                base = (base * base) % mod;
            }
            return result;
        }
        
        string toAlpha(long long text) {
            if (text > 6 && text < 33) {
                return string(1, 'A' + text - 7);
            }
            else if (text == 33) {
                return " ";
            }
            else if (text == 34) {
                return "\"";
            }
            else if (text == 35) {
                return ",";
            }
            else if (text == 36) {
                return ".";
            }
            else if (text == 37) {
                return "\'";
            }
            return "out of bounds";
        }

        void printVariables(long long p, long long q, long long phi, long long d) {
            cout << "p: " << p << endl;
            cout << "q: " << q << endl;
            cout << "phi: " << phi << endl;
            cout << "d: " << d << endl;
        }

        void printDecrypted() {
            for (int i = 0; i < decryptedInt.size(); i++) {
                cout << decryptedInt[i] << " ";
            }
            cout << endl;
            for (int i = 0; i < decryptedString.size(); i++) {
                cout << decryptedString[i];
            }
            cout << endl;
        }
};

int main() {
    long long input;
    vector<long long> inputs;

    while (cin >> input) {
        inputs.push_back(input);
    }

    RSA rsa(7, 4453, 13*8, inputs);
    rsa.compute();

    return 0;
}
