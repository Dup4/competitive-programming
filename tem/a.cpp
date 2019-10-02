#include <bits/stdc++.h>
using namespace std;

#define MAXN 100000

void insert_numbers(long long x)
{
    clock_t timestart=clock();
    unordered_map<long long,int> numbers;
    for(int i=1;i<=MAXN;i++)
        numbers[i*x]=i;
    long long sum=0;
    for(auto element:numbers)
        sum+=(element.first/x)*element.second;
    printf("x = %lld : %.3lfseconds, sum = %lld\n",x,(double)(clock()-timestart)/CLOCKS_PER_SEC,sum);
}

int main()
{
    insert_numbers(107897);
    insert_numbers(126271);
}
