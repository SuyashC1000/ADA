// Bubble Sort

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void bubbleSort(int arr[], int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    int isSwapped = 0;
    for (int j = 0; j < n - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        swap(&arr[j], &arr[j + 1]);
        isSwapped = 1;
      }
    }
    if (!isSwapped)
    {
      break;
    }
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
    bubbleSort(arr, n);
  }
  clock_t end = clock();

  double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC / 10.0;

  printf("Time taken to sort %d elements: %f seconds\n", n, time_taken);
  free(arr);
  return 0;
}