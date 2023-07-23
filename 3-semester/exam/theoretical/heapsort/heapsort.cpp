#include <iostream>
using namespace std;

void heapify(int arr[], int n, int i) {
  int left = 2*i + 1;
  int right = 2*i + 2;

  int max = i;

  if (left < n && arr[left] > arr[i])
    max = left;
  if (right < n && arr[right] > arr[max])
    max = right;

  if (max != i) {
    swap(arr[i], arr[max]);
    heapify(arr, n, max);
  }
}

void build_max_heap(int arr[], int n) {
  for (int i = n/2 - 1; i >= 0; i--)
    heapify(arr, n, i);
}

void heapsort(int arr[], int n) {
  build_max_heap(arr, n);
  for (int i = n-1; i >= 0; i--) {
    swap(arr[0], arr[i]);
    n--;
    heapify(arr, n, 0);
  }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

int main() {
  int arr[] = { 2, 8, 100, 5, 3, 9, 1, 99 };
  int n = sizeof(arr) / sizeof(arr[0]);

  printArray(arr, n);
  heapsort(arr, n);
  printArray(arr, n);

  return 0;
}