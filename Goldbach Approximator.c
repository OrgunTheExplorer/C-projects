#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void sieve(int max, char *is_prime) {
    memset(is_prime, 1, max + 1);
    is_prime[0] = 0;
    is_prime[1] = 0;
    int limit = (int)sqrt(max);
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= max; j += i) {
                is_prime[j] = 0;
            }
        }
    }
}

int goldbach_two(int number, char *is_prime) {
    for (int i = 2; i <= number / 2; i++) {
        if (is_prime[i] && is_prime[number - i]) return 1;
    }
    return 0;
}

int goldbach_three(int number, char *is_prime) {
    for (int i = 2; i <= number; i++) {
        if (!is_prime[i]) continue;
        int remainder = number - i;
        if (remainder >= 2 && goldbach_two(remainder, is_prime)) return 1;
    }
    return 0;
}

int main() {
    int a;
    printf("Enter your value: ");
    scanf("%d", &a);

    char *is_prime_arr = malloc(a + 1);
    sieve(a, is_prime_arr);

    int score = 0;
    int progress = 0;
    int range = a - 2;

    printf("Progress: [");
    fflush(stdout);

    for (int i = 2; i <= a; i++) {
        int percent = ((i - 2) * 100) / range;
        if (percent >= progress + 10) {
            progress += 10;
            printf("=");
            fflush(stdout);
        }

        if (!goldbach_two(i, is_prime_arr) && !goldbach_three(i, is_prime_arr)) {
            score--;
        } else {
            score++;
        }
    }
    printf("] Done!\n");
    if(score==a-5){
        printf("True");
    }

    free(is_prime_arr);
    return 0;
}
