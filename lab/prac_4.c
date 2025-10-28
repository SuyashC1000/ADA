// Fibonacci Sequence

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long *createArray(int n)
{
  long *arr = (long *)malloc(n * sizeof(long));
  for (int i = 0; i < n; i++)
  {
    arr[i] = -1;
  }
  return arr;
}

void printArray(int *arr, int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

long fibRecursive(int n)
{
  if (n <= 1)
  {
    return n;
  }
  else if (n > 1)
  {
    return fibRecursive(n - 1) + fibRecursive(n - 2);
  }
}

long fibIterative(int n)
{
  long x = 0;
  if (n == 0)
    return x;
  long y = 1;
  if (n == 1)
    return y;
  for (int i = 2; i < n + 1; i++)
  {
    long temp = x + y;
    x = y;
    y = temp;
  }
  return y;
}

long fibMemo(long *arr, int n)
{
  if (arr[n] != -1)
  {
    return arr[n];
  }
  else
  {
    if (n <= 1)
    {
      arr[n] = n;
      return n;
    }
    else if (n > 1)
    {
      long val = fibMemo(arr, n - 1) + fibMemo(arr, n - 2);
      arr[n] = val;
      return val;
    }
  }
}

long fibMemoization(int n)
{
  long *arr = createArray(n + 1);
  fibMemo(arr, n);
  return arr[n];
}

long fibTabulation(int n)
{
  long *arr = createArray(n + 1);
  arr[0] = 0;
  if (n == 0)
    return arr[n];
  arr[1] = 1;
  if (n == 1)
    return arr[n];
  for (int i = 2; i < n + 1; i++)
  {
    arr[i] = arr[i - 1] + arr[i - 2];
  }
  return arr[n];
}

int main()
{
  int n;
  printf("Enter the nth term to generate: ");
  scanf("%d", &n);

  long ans;

  clock_t start_1 = clock();
  ans = fibRecursive(n - 1);
  // printf("%ld\n", ans);
  clock_t end_1 = clock();

  clock_t start_2 = clock();
  int repeat_2 = 1;
  for (int i = 0; i < repeat_2; i++)
  {
    ans = fibIterative(n - 1);
    // printf("%ld\n", ans);
  }
  clock_t end_2 = clock();

  clock_t start_3 = clock();
  int repeat_3 = 1;
  for (int i = 0; i < repeat_3; i++)
  {
    ans = fibMemoization(n - 1);
    // printf("%ld\n", ans);
  }
  clock_t end_3 = clock();

  clock_t start_4 = clock();
  int repeat_4 = 1;
  for (int i = 0; i < repeat_4; i++)
  {
    ans = fibTabulation(n - 1);
    // printf("%ld\n", ans);
  }
  clock_t end_4 = clock();

  double time_taken_1 = ((double)(end_1 - start_1)) / CLOCKS_PER_SEC;
  double time_taken_2 = ((double)(end_2 - start_2)) / CLOCKS_PER_SEC / (float)repeat_2;
  double time_taken_3 = ((double)(end_3 - start_3)) / CLOCKS_PER_SEC / (float)repeat_3;
  double time_taken_4 = ((double)(end_4 - start_4)) / CLOCKS_PER_SEC / (float)repeat_4;

  printf("Time taken to get nth Fibonacci Sequence (Recursive): %f seconds\n", time_taken_1);
  printf("Time taken to get nth Fibonacci Sequence (Iterative): %f seconds\n", time_taken_2);
  printf("Time taken to get nth Fibonacci Sequence (Memoization): %f seconds\n", time_taken_3);
  printf("Time taken to get nth Fibonacci Sequence (Tabulation): %f seconds\n", time_taken_4);
}