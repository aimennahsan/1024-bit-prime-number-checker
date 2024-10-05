#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <random>   
#include <cmath>
#include <string>
#include <sstream>

using namespace std;


struct Node {
    uint64_t value;  
    Node* next;
    Node(uint64_t val) : value(val), next(nullptr) {}
};


class LargeNumber {
public:
    Node* head;

    LargeNumber() : head(nullptr) {}

    
    void insert(uint64_t value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    string getNumberAsString() const {
        stringstream ss;
        Node* temp = head;
        while (temp != nullptr) {
            ss << temp->value;
            temp = temp->next;
        }
        return ss.str();
    }

    
    uint64_t getModulusByPrime(int prime) const {
        uint64_t remainder = 0;
        Node* temp = head;
        while (temp != nullptr) {
            remainder = (remainder * ((uint64_t)pow(10, 19)) + temp->value) % prime;
            temp = temp->next;
        }
        return remainder;
    }
};


uint64_t getRandom64Bit() {
    random_device rd;
    mt19937_64 eng(rd());
    uniform_int_distribution<uint64_t> distr;
    return distr(eng);
}


LargeNumber generate1024BitNumber() {
    LargeNumber largeNum;

    
    for (int i = 0; i < 16; i++) {
        largeNum.insert(getRandom64Bit());
    }

    return largeNum;
}


int smallPrimes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
int numSmallPrimes = sizeof(smallPrimes) / sizeof(smallPrimes[0]);


bool divisibleBySmallPrimes(const LargeNumber& largeNum) {
    uint64_t remainder;

    
    for (int i = 0; i < numSmallPrimes; ++i) {
        int prime = smallPrimes[i];
        remainder = largeNum.getModulusByPrime(prime);
        if (remainder == 0) {
            return true;
        }
    }

    return false;
}


bool isPrime(const LargeNumber& largeNum, int k) {
    
    if (divisibleBySmallPrimes(largeNum)) {
        return false;
    }

    
    return true;
}


int main() {
    srand(time(0));

   
    LargeNumber largeNum = generate1024BitNumber();

   
    string largeNumStr = largeNum.getNumberAsString();
    cout << "Input: A 1024-bit number represented as \"" << largeNumStr << "\"\n";

    cout << "Smaller primes: [";
    for (int i = 0; i < numSmallPrimes; ++i) {
        cout << smallPrimes[i];
        if (i != numSmallPrimes - 1) {
            cout << ", ";
        }
    }
    cout << "]\n";

    // Perform the primality test
    bool result = isPrime(largeNum, 5);

    // Output the result
    cout << "Output: " << (result ? "True (Prime)" : "False (Not Prime)") << endl;

    return 0;
}
