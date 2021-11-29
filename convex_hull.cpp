#include <vector>
#include <limits.h>
#include <stdio.h>
#include <algorithm>
#include <stack>
using namespace std;
 
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
 
int main()
{
    int z;
    scanf("%d", &z);
    while (z--) {
        int n;
        scanf("%d", &n);
        vector<point> Points(n);
 
        for (int i=0; i<n; i++) {
            scanf("%lld %lld", &Points[i].x, &Points[i].y);
        }
        sort(Points.begin(), Points.end(), cmp);
 
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
 
        long long suma = 0;
 
 
 
 
        point temp;
        while (!Stack.empty())
        {
            temp = StackTop;
            StackTop = Stack.top();
            Stack.pop();
            suma += wyz(StackTop, temp);
        }
 
        while (!Stack2.empty())
        {
            temp = StackTop2;
            StackTop2 = Stack2.top();
            Stack2.pop();
            suma += wyz(StackTop2, temp);
        }
        printf("%lld\n", abs(suma));
    }
}