#include <iostream>
#include <sys/time.h>
#include <stdio.h>
#include <math.h>
using namespace std;

void sleep(long long int delay){
    for(long long int i=1; i<=delay; i++)
        for(long long int j=1; j<=delay; j++)
            (i*j)%2;
}

void sleep2(long long int delay){
    int j=456;
    for(long long int i=1; i<=delay; i++)
        {
            (i*j)%2;
        }
}

void sleep3(long long int delay){
    int j=1;
    for(long long int i=1; i<=log(delay); i++)
        for(long long int j=1; j<=delay; j++)
            (i*j)%2;
}


float diftime(struct timeval t0, struct timeval t1){
    return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

int main(void){
   struct timeval t0;
   struct timeval t1;
   float cont;
   long long int n;
   printf("Enter n: \n");
   scanf("%lld",&n);


   gettimeofday(&t0, 0);
   sleep2(n);
   gettimeofday(&t1, 0);

   cont = diftime(t0, t1);

   printf("O(n) executed in %f milliseconds.\n", cont);

   gettimeofday(&t0, 0);
   sleep3(n);
   gettimeofday(&t1, 0);

   cont = diftime(t0, t1);

   printf("O(n*log(n)) executed in %f milliseconds.\n", cont);

   gettimeofday(&t0, 0);
   sleep(n);
   gettimeofday(&t1, 0);

   cont = diftime(t0, t1);

   printf("O(n2) executed in %f milliseconds.\n", cont);


   return 0;
}
