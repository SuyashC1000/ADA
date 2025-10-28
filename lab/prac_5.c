#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int table[500][500];

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

int max(int a, int b)
{
  if (a > b)
    return a;
  return b;
}

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
  int weight = 3, profit = 4;
  for (int i = 0; i < n; i++)
  {
    items[i].profit = profit++;
    items[i].weight = weight++;
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
  return solution;
}

int main()
{
  int n;
  printf("Enter number of elements: ");
  scanf("%d", &n);

  int w = 3 * n;

  Knapsack *k = createKnapsack(n, w);

  for (int i = 0; i <= n; ++i)
  {
    for (int j = 0; j <= w; ++j)
    {
      table[i][j] = -1;
    }
  }

  fillProfitWeight(k->items, n);

  Solution *s;

  clock_t start_1 = clock();
  s = fractionalKnapsack(k);
  // printf("Profit (Greedy): %f\n", s->totalProfit);
  clock_t end_1 = clock();

  clock_t start_2 = clock();
  s = knapsack01(k);
  // printf("Profit (DP): %f\n", s->totalProfit);
  clock_t end_2 = clock();

  double time_taken1 = ((double)(end_1 - start_1)) / CLOCKS_PER_SEC;
  double time_taken2 = ((double)(end_2 - start_2)) / CLOCKS_PER_SEC;

  printf("Time taken to optimize knapsack with %d items (Greedy): %f seconds\n", n, time_taken1);
  printf("Time taken to optimize knapsack with %d items (Dynamic): %f seconds\n", n, time_taken2);
  printf("\n");
}