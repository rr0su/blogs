#include <stdio.h>

int add(int a, int b) {
    int c = a + b;
    return c;
}

int sum_array(int *arr, int n) {
    int s = 0;
    for (int i = 0; i < n; i++) {
        s += arr[i];
    }
    return s;
}

int test_local_array() {
    int arr[4];
    arr[0] = 5;
    return arr[0];
}

int main() {
    int x = add(3, 4);
    int y = test_local_array();
    int z = sum_array((int[]){1,2,3}, 3);
    return x + y + z;
}
