#include <stdio.h>

double expansion(double x, int n) {
    double curr = 1, prev = 0;
    if (n < 0) return prev;
    if (n == 0) return curr;
    for (int i = 1; i <= n; i++) {
        double temp = (1 + x / i) * curr - (x / i) * prev;
        prev = curr;
        curr = temp;
    }

    return curr;
}

int sum(int n) {
    int sum = 0;

    while (n) {
        sum += n % 10;
        n = n / 10;
    }

    return sum;
}

int odd_sum(int n) {
    int odd_sum = 0;
    int e;

    while (n > 0) {
        e = n % 10;
        if (e % 2) {
            odd_sum += e;
        }
        n /= 10;
    }

    return odd_sum;
}

int harshad_check(int n) {
    int check_sum = sum(n);
    if (n % check_sum) {
        return odd_sum(n);
    } else {
        return sum(n);
    }
}


int main() {
    printf("%f\n", expansion(1, 10000000));
    printf("%d\n", harshad_check(152));
    printf("%d\n", harshad_check(158));

    return 0;
}
