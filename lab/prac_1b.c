// Binary Search

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binarySearch(int arr[], int left, int right, int key)
{
  if (left < right)
  {
    int mid = left + (right - left) / 2;
    if (arr[mid] == key)
    {
      return mid;
    }
    else if (arr[mid] < key)
    {
      return binarySearch(arr, mid + 1, right, key);
    }
    else if (arr[mid] > key)
    {
      return binarySearch(arr, left, mid - 1, key);
    }
  }
  else
    return -1;
}

void generateRandomArray(int arr[], int n)
{
  int sum = 0;
  for (int i = 0; i < n; i++)
  {
    sum += rand() % 10;
    arr[i] = sum;
  }
}

int main()
{
  int n;
  printf("Enter the number of elements: ");
  scanf("%d", &n);
  int key;
  printf("Enter the element to search for: ");
  scanf("%d", &key);

  int *arr = (int *)malloc(n * sizeof(int));
  if (arr == NULL)
  {
    printf("Memory allocation failed\n");
    return 1;
  }
  generateRandomArray(arr, n);

  clock_t start = clock();
  int repeat = 1000;
  for (int i = 0; i < repeat * 1000; i++)
  {
    binarySearch(arr, 0, n - 1, key);
  }
  clock_t end = clock();

  double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC / (double)repeat;

  printf("Time taken to search through %d elements: %f milliseconds\n", n, time_taken);
  free(arr);
  return 0;
}