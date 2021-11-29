#include <limits.h>
#include <stdio.h>
#include <algorithm>
#include <stack>
#include <thread>
using namespace std;
 
#define MAX_POINT_NUM 300000
#define SORT_CONST 2048

struct point
{
    long long x;
    long long y;
};
 
bool cmp(point &a, point &b) {
    if(a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}
 
// TRUE if a-c left of a-b, else FALSE
bool ccw(point &a, point &b, point &c) {
    point B = {b.x - a.x, b.y - a.y};
    point C = {c.x - a.x, c.y - a.y};
    long long wyz = B.x * C.y - C.x * B.y;
    return wyz > 0;
}
 
long long wyz(point &a, point &b) {
    return a.x * b.y - b.x * a.y;
}

point Points[MAX_POINT_NUM];

void merge_sort(int beg, int end) {
    if (end - beg <= SORT_CONST) {
        sort(Points + beg, Points + end, cmp);
        return;
    }

    int mid = (beg + end) / 2;
    thread sort_thread(merge_sort, beg, mid);
    merge_sort(mid, end);
    sort_thread.join();

    point * tmp = new point[end - beg];
    for (int i = 0; i < end - beg; i++) {
        tmp[i] = Points[beg + i];
    }

    int i = 0, j = 0, k = mid - beg;
    while (i < end - beg) {
        if ((j < mid - beg && cmp(tmp[j], tmp[k])) || (k == end - beg)) {
            Points[beg + i] = tmp[j];
            j++;
        } else {
            Points[beg + i] = tmp[k];
            k++;
        }
        i++;
    }
    
    delete tmp;
}

long long suma1 = 0;
long long suma2 = 0;
int n;

void getHullBottom() {
    point temp;
    stack<point> Stack;
    Stack.push(Points[0]);
    point StackTop = Points[1];
    for (int i=2; i<n; i++) {
        while(!Stack.empty() && !ccw(Stack.top(), StackTop, Points[i])) {
            StackTop = Stack.top();
            Stack.pop();
        }
        Stack.push(StackTop);
        StackTop = Points[i];
    }
    while (!Stack.empty())
    {
        temp = StackTop;
        StackTop = Stack.top();
        Stack.pop();
        suma1 += wyz(StackTop, temp);
    }
}

void getHullTop() {
    point temp;
    stack<point> Stack2;
    Stack2.push(Points[n-1]);
    point StackTop2 = Points[n-2];
    for (int i=n-3; i>=0; i--) {
        while(!Stack2.empty() && !ccw(Stack2.top(), StackTop2, Points[i])) {
            StackTop2 = Stack2.top();
            Stack2.pop();
        }
        Stack2.push(StackTop2);
        StackTop2 = Points[i];
    }
    while (!Stack2.empty())
    {
        temp = StackTop2;
        StackTop2 = Stack2.top();
        Stack2.pop();
        suma2 += wyz(StackTop2, temp);
    }
}

int main()
{
    int z;
    scanf("%d", &z);
    while (z--) {
        scanf("%d", &n);
        for (int i=0; i<n; i++) {
            scanf("%lld %lld", &Points[i].x, &Points[i].y);
        }
        merge_sort(0, n);

        thread bot_thread(getHullBottom);
        thread top_thread(getHullTop);
        bot_thread.join();
        top_thread.join();

        printf("%lld\n", abs(suma1 + suma2));
    }
}