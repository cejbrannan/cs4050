#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long ops;

long fibrecurse(long n){
    if(n <= 1){
        return n;
    }else{
        ops++;
        return (fibrecurse(n-1)+fibrecurse(n-2));
    }
}

long fibdynamic(long n){
    long f[n+2];
    f[0]=0;
    f[1]=1;

    for(long i = 2; i <=n; i++){
        f[i] = f[i-1] + f[i-2];
        ops++;
    }
    return f[n];
}

int main(int argc, char **argv){
    if(argc < 1){
        printf("Error, no arguments");
    }
    long start = atoi(argv[1]);
    ops = 0;

    clock_t t;
    t = clock();

    printf("FibRecurse(%ld) = %ld\n", start, fibrecurse(start));

    t = clock() - t;

    double recursivetime = (((double)t)/CLOCKS_PER_SEC);

    printf("%ld operations, %f seconds \n", ops, recursivetime);
    ops = 0;

    clock_t u;
    u = clock();

    printf("FibDynamic(%ld) = %ld\n", start, fibdynamic(start));
    u = clock() - u;
    double dynamictime = (((double)u)/CLOCKS_PER_SEC);
    printf("%ld operations, %f seconds \n", ops, dynamictime);
    return 0;
}
