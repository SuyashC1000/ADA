// Fractional Knapsack

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct item
{
  int profit;
  int weight;
} typedef Item;

struct solution
{
  float totalProfit;
  float *selectedItems;
} typedef Solution;

struct knapsack
{
  int maxWeight;
  int itemCount;
  Item *items;
} typedef Knapsack;

Item *createItemList(int n)
{
  Item *items = (Item *)malloc(n * sizeof(Item));
  return items;
}

Knapsack *createKnapsack(int n, int w)
{
  Knapsack *knapsack = (Knapsack *)malloc(sizeof(Knapsack));
  knapsack->maxWeight = w;
  knapsack->itemCount = n;
  knapsack->items = createItemList(n);
  return knapsack;
}

void fillProfitWeight(Item *items, int n)
{
  for (int i = 0; i < n; i++)
  {
    int profit, weight;
    printf("Enter the profit of item %d: ", i + 1);
    scanf("%d", &profit);
    printf("Enter the weight of item %d: ", i + 1);
    scanf("%d", &weight);
    items[i].profit = profit;
    items[i].weight = weight;
  }
}

void printMatrix(Item *items, int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%d: %d %d\n", i + 1, items[i].profit, items[i].weight);
  }
}

Solution *fractionalKnapsack(Knapsack *knapsack)
{
  int n = knapsack->itemCount;
  Item *items = knapsack->items;

  float *selectedItems = (float *)calloc(n, sizeof(float));
  float *ratio = (float *)malloc(n * sizeof(float));

  for (int i = 0; i < n; i++)
  {
    ratio[i] = (float)items[i].profit / (float)items[i].weight;
  }

  float totalProfit = 0.0;
  int weightLeft = knapsack->maxWeight;
  int hasNotDepleted = 1;

  while (weightLeft > 0.0 && hasNotDepleted)
  {
    // printf("loop\n");
    hasNotDepleted = 0;

    float maxRatio = 0.0;
    int maxRatioIndex = 0;
    for (int i = 0; i < n; i++)
    {
      if (selectedItems[i] == 0 && ratio[i] > maxRatio)
      {
        hasNotDepleted = 1;
        maxRatio = ratio[i];
        maxRatioIndex = i;
      }
    }

    if (!hasNotDepleted)
    {
      break;
    }

    Item maxItem = items[maxRatioIndex];
    if (weightLeft >= maxItem.weight)
    {
      weightLeft -= maxItem.weight;
      selectedItems[maxRatioIndex] = 1;
      totalProfit += maxItem.profit;
    }
    else
    {
      int difference = maxItem.weight - weightLeft;
      weightLeft -= difference;
      selectedItems[maxRatioIndex] = (float)(difference) / (float)(maxItem.weight);
      totalProfit += (float)maxRatio * (float)(difference) / (float)(maxItem.weight);
    }
  }

  Solution *solution = (Solution *)malloc(sizeof(Solution));
  solution->selectedItems = selectedItems;
  solution->totalProfit = totalProfit;
  return solution;
}

int main()
{
  int n;
  printf("Enter number of elements: ");
  scanf("%d", &n);

  int w;
  printf("Enter maximum weight of knapsack: ");
  scanf("%d", &w);

  Knapsack *k = createKnapsack(n, w);

  fillProfitWeight(k->items, n);

  clock_t start = clock();
  Solution *s = fractionalKnapsack(k);
  clock_t end = clock();

  double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

  printf("%f\n", s->totalProfit);
  for (int i = 0; i < n; i++)
  {
    printf("%d: %d %d %f\n", i + 1, k->items[i].profit, k->items[i].weight, s->selectedItems[i]);
  }

  printf("Time taken to optimize knapsack with %d items: %f seconds\n", n, time_taken);
  printf("\n");
}