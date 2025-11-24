#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct activity
{
  int start;
  int finish;
} Activity;

Activity *createActivityArray(int n)
{
  Activity *activityArray = (Activity *)malloc(n * sizeof(Activity));
  for (int i = 0; i < n; i++)
  {
    printf("Enter start time of activity %d: ", i + 1);
    scanf("%d", &activityArray[i].start);
    printf("Enter finish time of activity %d: ", i + 1);
    scanf("%d", &activityArray[i].finish);
  }
  return activityArray;
}

void swap(Activity *a, Activity *b)
{
  Activity temp = *a;
  *a = *b;
  *b = temp;
}

int partition(Activity activityArray[], int left, int right)
{
  int pivot = activityArray[right].finish;
  int i = left - 1;
  for (int j = left; j < right; j++)
  {
    if (activityArray[j].finish <= pivot)
    {
      i++;
      swap(&activityArray[i], &activityArray[j]);
    }
  }
  swap(&activityArray[i + 1], &activityArray[right]);

  return i + 1;
}

void quickSort(Activity activityArray[], int left, int right)
{
  if (left < right)
  {
    int middle = partition(activityArray, left, right);
    quickSort(activityArray, left, middle - 1);
    quickSort(activityArray, middle + 1, right);
  }
}

int *activitySelection(Activity *activityArray, int n)
{
  quickSort(activityArray, 0, n - 1);

  int *selected = (int *)calloc(n, sizeof(int));

  int count = 0;
  int active = -1;
  for (int i = 0; i < n; i++)
  {
    if (active == -1)
    {
      selected[i] = 1;
      active = i;
      count++;
    }
    else
    {
      if (activityArray[i].start >= activityArray[active].finish)
      {
        selected[i] = 1;
        active = i;
        count++;
      }
    }
  }

  return selected;
}

void printResult(Activity *activityArray, int *selected, int n)
{
  printf("Selected activities:\n");
  printf("S.No.\tStart\tFinish\n");
  int count = 1;
  for (int i = 0; i < n; i++)
  {
    if (selected[i] == 1)
    {
      printf("%d\t%d\t%d\n", count, activityArray[i].start, activityArray[i].finish);
      count++;
    }
  }
}

int main()
{
  int n;
  printf("Enter no. of activities: ");
  scanf("%d", &n);

  clock_t start = clock();
  Activity *activityArray = createActivityArray(n);
  clock_t end = clock();

  double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

  int *selected = activitySelection(activityArray, n);
  printResult(activityArray, selected, n);
  printf("Time taken to check through %d activities: %f seconds\n", n, time_taken);
}