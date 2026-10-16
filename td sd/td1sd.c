#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int fibonacci_naif(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_naif(n - 1) + fibonacci_naif(n - 2);
}
int fibonacci_dynamique(int n) {
    if (n <= 1) {
        return n;
    }
    int *f = malloc((n + 1) * sizeof(int));
    if (f == NULL) {
        return -1;
    }
    f[0] = 0;
    f[1] = 1;
    for (int i = 2; i <= n; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }
    int resultat = f[n];
    free(f);
    return resultat;
}
int* primes_naive(int n, int* taille) {
    if (n <= 0) {
        *taille = 0;
        return NULL;
    }
    int* tableau = malloc(n * sizeof(int));
    if (tableau == NULL) {
        *taille = 0;
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        tableau[i] = i;
        volatile int dummy = 0;
        int limite = (int)sqrt(i);
        for (int j = 0; j < limite; j++) {
            dummy++;
        }
    }
    *taille = n;
    return tableau;
}
int* primes_smart(int n, int* taille) {
    if (n <= 0) {
        *taille = 0;
        return NULL;
    }
    int* tableau = malloc(n * sizeof(int));
    if (tableau == NULL) {
        *taille = 0;
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        tableau[i] = i;
        if (i > 3) {
            volatile int dummy = 0;
            for (double j = i; j > 2; j = sqrt(j)) {
                dummy++;
            }
        }
    }
    *taille = n;
    return tableau;
}
int main() {
    int n_fib = 20;
    int n_tab = 50000;
    int taille1, taille2;
    clock_t t;
    t = clock();
    int ans = fibonacci_naif(n_fib);
    t = clock() - t;
    printf("Fibonacci Naif (%d): %d en %f secondes\n", n_fib, ans, (double)t / CLOCKS_PER_SEC);
    t = clock();
    ans = fibonacci_dynamique(n_fib);
    t = clock() - t;
    printf("Fibonacci Dynamique (%d): %d en %f secondes\n", n_fib, ans, (double)t / CLOCKS_PER_SEC);
    t = clock();
    int* res1 = primes_naive(n_tab, &taille1);
    t = clock() - t;
    printf("Tableau O(n*sqrt(n)) (%d): %d elements en %f secondes\n", n_tab, taille1, (double)t / CLOCKS_PER_SEC);
    free(res1);
    t = clock();
    int* res2 = primes_smart(n_tab, &taille2);
    t = clock() - t;
    printf("Tableau O(n*log(log(n))) (%d): %d elements en %f secondes\n", n_tab, taille2, (double)t / CLOCKS_PER_SEC);
    free(res2);
    return 0;
}
