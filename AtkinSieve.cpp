#include <iostream>
#include <vector>
#include <cmath>

std::vector<bool> makeArPrimes(long long size) {
    std::vector<bool> arPrimes(size);

    int sqr_size = (int)sqrt((long double)size);
    long long x2 = 0, y2, n;

    for(int i = 1; i <= sqr_size; ++i) {

        x2 += (i << 1) - 1;
        y2 = 0;

        for(int j = 1; j <= sqr_size; ++j) {

            y2 += (j << 1) - 1;
            n = (x2 << 2) + y2;

            if((n <= size) && (n % 12ll == 1ll || n % 12ll == 5ll)) {
                arPrimes[n].flip();
            }

            n -= x2;

            if((n <= size) && (n % 12ll == 7ll)) {
                arPrimes[n].flip();
            }

            n -= (y2 << 1);

            if((n <= size) && (i > j) && (n % 12ll == 11ll)) {
                arPrimes[n].flip();
            }

        }
    }

    for(int i = 5; i <= sqr_size; ++i) {
        if(arPrimes[i]) {
            for(int j = i * i; j <= size; j += i * i) {
                arPrimes[j] = false;
            }
        }
    }

    if(size > 2)
        arPrimes[2].flip();
    if(size > 3)
        arPrimes[3].flip();

    return arPrimes;
}

bool isPrime(long long size) {
    std::vector<bool> arResult = makeArPrimes(size);
    return (arResult[size]) ? true : false;
}

int main() {
    long long size;
    std::cin >> size;

    std::vector<bool> arResult = makeArPrimes(size);
    std::cout << "\n";
    for (long long number = 2; number <= size; ++number)
        if(arResult[number])
            std::cout << number << ' ';

    std::cout << isPrime(size) << '\n';
}
