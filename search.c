#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned long long base = 11;

unsigned long long hash(char *begin, char *end) {
    unsigned long long result = 0;
    
    for (char *it = begin; it != end; it++) {
        result *= base;
        result += (unsigned long long)((*it)-'0'+1);
    }

    return result;
}

unsigned long long power;

void calc_power(int n) {
    power = 1;
    while (--n)
        power *= base;
}

char streq(char *s1, char *e1, char *s2) {
    int n = e1 - s1;

    while (n--) {
        if (*(s1+n) != *(s2+n)) {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        puts("Usage: program accepts 2 arguments - the text to search for, the number of decimal digits of pi to search in");
        return 1;
    }
    
    char *pattern = argv[1];
    int pat_len = strlen(pattern);

    calc_power(pat_len);

    int pi_len = atoi(argv[2]);
    char *pi = malloc( pi_len+2+1 );
    char *pi_start = pi+2;
    char *pi_end = pi_start + pi_len - pat_len + 1;

    scanf("%s", pi);

    unsigned long long curr_hash = hash(pi_start, pi_start + pat_len);
    unsigned long long pattern_hash = hash(pattern, pattern + pat_len);

    char matchMsg[] = "Match found at %d decimal digit.\n";
    char falseMsg[] = "False positive at %d decimal digit.\n";

    for (char *it = pi_start; it != pi_end; it++) {
        if (curr_hash == pattern_hash) {
            int dec = it - pi_start + 1;
            if (streq(it, it+pat_len, pattern)) {
                printf(matchMsg, dec);
            } else {
                printf(falseMsg, dec); 
                for (char* jt = it; jt != it+pat_len; jt++) {
                    printf("%c", *jt);
                }
                puts("");
            }
        }

        int hdigit = *(it)-'0'+1;
        int tdigit = *(it + pat_len)-'0'+1;

        curr_hash -= power * hdigit;
        curr_hash *= base;
        curr_hash += tdigit;
    }

    return 0;
}
