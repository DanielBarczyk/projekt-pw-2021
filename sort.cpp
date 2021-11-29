#include <algorithm>
#include <stdio.h>
using namespace std;

#define MAX_POINT_NUM 300000
#define SORT_CONST 16

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

point A[MAX_POINT_NUM];

void merge_sort(int beg, int end) {
    if (end - beg <= SORT_CONST) {
        sort(A + beg, A + end, cmp);
        return;
    }

    int mid = (beg + end) / 2;
    merge_sort(beg, mid);
    merge_sort(mid, end);

    point * tmp = new point[end - beg];
    for (int i = 0; i < end - beg; i++) {
        tmp[i] = A[beg + i];
    }

    int i = 0, j = 0, k = mid - beg;
    while (i < end - beg) {
        if ((j < mid - beg && cmp(tmp[j], tmp[k])) || (k == end - beg)) {
            A[beg + i] = tmp[j];
            j++;
        } else {
            A[beg + i] = tmp[k];
            k++;
        }
        i++;
    }
    
    delete tmp;
}

int main() {
    int z;
    scanf("%d", &z);
    scanf("%d", &z);
    for (int i=0; i<z; i++) {
        scanf("%lld %lld", &A[i].x, &A[i].y);
    }
    merge_sort(0, z);
    for (int i=0; i<z; i++) {
        printf("%lld %lld\n", A[i].x, A[i].y);
    }
}