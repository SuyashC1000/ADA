// Quick Sort

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int partition(int arr[], int left, int right)
{
  int pivot = arr[right];
  int i = left - 1;
  for (int j = left; j < right; j++)
  {
    if (arr[j] <= pivot)
    {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[right]);

  return i + 1;
}

void quickSort(int arr[], int left, int right)
{
  if (left < right)
  {
    int middle = partition(arr, left, right);
    quickSort(arr, left, middle - 1);
    quickSort(arr, middle + 1, right);
  }
}

void generateRandomArray(int arr[], int n)
{
  for (int i = 0; i < n; i++)
    arr[i] = rand() % 10000;
}

int main()
{
  int n;
  printf("Enter the number of elements: ");
  scanf("%d", &n);

  int *arr = (int *)malloc(n * sizeof(int));
  if (arr == NULL)
  {
    printf("Memory allocation failed\n");
    return 1;
  }
  generateRandomArray(arr, n);

  clock_t start = clock();
  for (int i = 0; i < 10; i++)
  {
    quickSort(arr, 0, n - 1);
  }
  clock_t end = clock();

  double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC / 10.0;

  printf("Time taken to sort %d elements: %f seconds\n", n, time_taken);
  free(arr);
  return 0;
}