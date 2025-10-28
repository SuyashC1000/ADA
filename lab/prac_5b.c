// 0/1 Knapsack

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int table[100][100];

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

int max(int a, int b)
{
  if (a > b)
    return a;
  return b;
}

int knapSackMemo(int maxWeight, Item items[], int itemCount)
{
  if (itemCount == 0 || maxWeight == 0)
    return 0;

  if (table[itemCount][maxWeight] != -1)
    return table[itemCount][maxWeight];

  if (items[itemCount - 1].weight > maxWeight)
    return table[itemCount][maxWeight] = knapSackMemo(maxWeight, items, itemCount - 1);

  else
    return table[itemCount][maxWeight] = max(items[itemCount - 1].profit + knapSackMemo(maxWeight - items[itemCount - 1].weight, items, itemCount - 1),
                                             knapSackMemo(maxWeight, items, itemCount - 1));
}

Solution *knapsack01(Knapsack *knapsack)
{
  int totalProfit = knapSackMemo(knapsack->maxWeight, knapsack->items, knapsack->itemCount);
  printf("Profit: %d\n", totalProfit);

  float *selectedItems = (float *)calloc(knapsack->itemCount, sizeof(float));

  int i = knapsack->itemCount, j = knapsack->maxWeight;
  while (i >= 1 && table[i][j] > 0)
  {
    int diff = table[i][j] - table[i - 1][j];
    if (diff > 0)
    {
      selectedItems[i - 1] = 1;
      int sub = knapsack->items[i - 1].weight;
      j -= sub;
    }
    i--;
  }

  Solution *solution = (Solution *)malloc(sizeof(Solution));
  solution->totalProfit = totalProfit;
  solution->selectedItems = selectedItems;
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

  for (int i = 0; i <= n; ++i)
  {
    for (int j = 0; j <= w; ++j)
    {
      table[i][j] = -1;
    }
  }

  clock_t start = clock();
  Solution *s = knapsack01(k);
  clock_t end = clock();

  double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

  printf("Time taken to optimize knapsack with %d items: %f seconds\n", n, time_taken);
}