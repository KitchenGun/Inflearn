#include <iostream>
#include <vector>
#include <string>
#include <istream>
#include <queue>
using namespace std;


int binomialCoeff(int n, int k) {
    if (k == 0 || k == n)
        return 1;
    return binomialCoeff(n - 1, k - 1) + binomialCoeff(n - 1, k);
}

int main() {
    int N, K;
    cin >> N >> K;
    cout << binomialCoeff(N, K);
    return 0;
}
