#include <iostream>
#include <vector>
#include "sort/Sort.h"

using namespace std;

int main() {
    int ele[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
    int n = 10;
    sortQuickNR<int>(ele, n);

    for (int i = 0; i < n; ++i) {
        cout << ele[i] << " ";
    }
    cout << endl;
}