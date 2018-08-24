#include <iostream>
#include <vector>
#include "sort.h"
//#include "../list/array_list.h"

using namespace std;

int main() {
   int a[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0, 1};
   int n = 11;
   sortRadix(a, n);

    for (int i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
}