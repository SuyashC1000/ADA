// Insertion Sort

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int arr[], int n)
{
  for (int i = 1; i < n; i++)
  {
    int key = arr[i];
    int j = i - 1;
    while (j >= 0 && key < arr[j])
    {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
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
    insertionSort(arr, n);
  }
  clock_t end = clock();

  double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC / 10.0;

  printf("Time taken to sort %d elements: %f seconds\n", n, time_taken);
  free(arr);
  return 0;
}