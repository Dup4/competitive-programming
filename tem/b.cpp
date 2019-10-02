#include <bits/stdc++.h>
using namespace std;

#define MAXN 100000

struct custom_hash
{
    unsigned long long operator()(unsigned long long x)const
    {
        x+=0x9e3779b97f4a7c15;
        x=(x^(x>>30))*0xbf58476d1ce4e5b9;
        x=(x^(x>>27))*0x94d049bb133111eb;
        return x^(x>>31);
    }
};

void insert_numbers(long long x)
{
    clock_t timestart=clock();
    unordered_map<__int128,int, custom_hash> numbers;
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
