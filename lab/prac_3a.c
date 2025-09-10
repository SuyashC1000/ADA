// Matrix Multiplication by Iterative Method

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **createMatrix(int size)
{
  int **matrix = (int **)malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++)
  {
    matrix[i] = (int *)malloc(size * sizeof(int));
  }
  return matrix;
}

void fillMatrix(int **matrix, int size)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      matrix[i][j] = rand() % 10;
    }
  }
}

int **multiplyMatrix(int **matrix1, int **matrix2, int size)
{
  int **product = createMatrix(size);
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      int sum = 0;
      for (int k = 0; k < size; k++)
      {
        sum += matrix1[i][k] * matrix2[k][j];
      }
      product[i][j] = sum;
    }
  }
  return product;
}

// void printMatrix(int **matrix, int row, int col)
// {
//   for (int i = 0; i < row; i++)
//   {
//     for (int j = 0; j < col; j++)
//     {
//       printf("%d ", matrix[i][j]);
//     }
//     printf("\n");
//   }
// }

int main()
{
  int n;
  printf("Enter the size of the matrix: ");
  scanf("%d", &n);

  int **m1 = createMatrix(n);
  fillMatrix(m1, n);
  // printMatrix(m1, r1, c1);

  int r2 = n, c2 = n;
  int **m2 = createMatrix(n);
  fillMatrix(m2, n);
  // printMatrix(m2, r2, c2);

  clock_t start = clock();
  int **p = multiplyMatrix(m1, m2, n);
  clock_t end = clock();

  // printMatrix(p, r1, c2);

  double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

  printf("Time taken to multiply matrices of size %d: %f seconds\n", n, time_taken);
}