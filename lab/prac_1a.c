// Linear Search

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linearSearch(int arr[], int n, int key)
{
  for (int i = 0; i < n; i++)
  {
    if (arr[i] == key)
    {
      return i;
    }
  }
  return -1;
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
  for (int i = 0; i < repeat; i++)
  {
    linearSearch(arr, n, key);
  }
  clock_t end = clock();

  double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC / (float)repeat;

  printf("Time taken to search through %d elements: %f seconds\n", n, time_taken);
  free(arr);
  return 0;
}