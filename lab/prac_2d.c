// Selection Sort

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int arr[], int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    int key = arr[i];
    int min = i + 1;
    for (int j = i + 1; j < n; j++)
    {
      if (arr[j] < arr[min])
        min = j;
    }
    arr[i] = arr[min];
    arr[min] = key;
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
    selectionSort(arr, n);
  }
  clock_t end = clock();

  double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC / 10.0;

  printf("Time taken to sort %d elements: %f seconds\n", n, time_taken);
  free(arr);
  return 0;
}