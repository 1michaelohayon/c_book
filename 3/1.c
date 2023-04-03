#include <stdio.h>

int binsearch(int x, int v[], int n) {
  int low = 0, high = n - 1;
  int mid = (low + high) / 2;

  while (low <= high && x != v[mid]) {
    if (x < v[mid])
      high = mid;
    else
      low = mid + 1;

    mid = (low + high) / 2;
  }
  return v[mid] == x ? mid : -1;
}

int main() {
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 8, 9, 10, 11};
  printf("%d\n", binsearch(7, arr, 12));
  return 0;
}