#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **createMatrix(int size)
{
  int **matrix = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++)
  {
    matrix[i] = calloc(size, sizeof(int));
    for (int j = 0; j < size; j++)
    {
      matrix[i][j] = 0;
    }
  }
  return matrix;
}

int **multiplyMatrix(int **matrixA, int **matrixB, int size)
{
  int **product = createMatrix(size);
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      int sum = 0;
      for (int k = 0; k < size; k++)
      {
        sum += matrixA[i][k] * matrixB[k][j];
      }
      product[i][j] = sum;
    }
  }
  return product;
}

int **addMatrix(int **matrixA, int **matrixB, int size)
{
  int **sum = createMatrix(size);
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      sum[i][j] = matrixA[i][j] + matrixB[i][j];
    }
  }

  return sum;
}

int **subMatrix(int **matrixA, int **matrixB, int size)
{
  int **diff = createMatrix(size);
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      diff[i][j] = matrixA[i][j] - matrixB[i][j];
    }
  }

  return diff;
}

int **subDivideMatrix(int **matrix, int size, int row, int col)
{
  int half = size / 2;

  int **subMatrix = createMatrix(size);
  int r = row, c = col;
  for (int i = 0; i < half; i++)
  {
    c = col;
    for (int j = 0; j < half; j++)
    {
      subMatrix[i][j] = matrix[r][c];
      c++;
    }
    r++;
  }
  return subMatrix;
}

int **matMuxStrassen(int **matrixA, int **matrixB, int size)
{
  int **product = createMatrix(size);
  if (size > 1)
  {
    int half = size / 2;

    int **a11 = subDivideMatrix(matrixA, size, 0, 0);
    int **a12 = subDivideMatrix(matrixA, size, 0, half);
    int **a21 = subDivideMatrix(matrixA, size, half, 0);
    int **a22 = subDivideMatrix(matrixA, size, half, half);
    int **b11 = subDivideMatrix(matrixB, size, 0, 0);
    int **b12 = subDivideMatrix(matrixB, size, 0, half);
    int **b21 = subDivideMatrix(matrixB, size, half, 0);
    int **b22 = subDivideMatrix(matrixB, size, half, half);

    int **matrixP = matMuxStrassen(addMatrix(a11, a22, half), addMatrix(b11, b22, half), half);
    int **matrixQ = matMuxStrassen(addMatrix(a21, a22, half), b11, half);
    int **matrixR = matMuxStrassen(a11, subMatrix(b12, b22, half), half);
    int **matrixS = matMuxStrassen(a22, subMatrix(b21, b11, half), half);
    int **matrixT = matMuxStrassen(addMatrix(a11, a12, half), b22, half);
    int **matrixU = matMuxStrassen(subMatrix(a21, a11, half), addMatrix(b11, b12, half), half);
    int **matrixV = matMuxStrassen(subMatrix(a12, a22, half), addMatrix(b21, b22, half), half);

    int **c11 = addMatrix(subMatrix(addMatrix(matrixP, matrixS, half), matrixT, half), matrixV, half);
    int **c12 = addMatrix(matrixR, matrixT, half);
    int **c21 = addMatrix(matrixQ, matrixS, half);
    int **c22 = addMatrix(subMatrix(addMatrix(matrixP, matrixR, half), matrixQ, half), matrixU, half);

    for (int i = 0; i < half; i++)
    {
      for (int j = 0; j < half; j++)
      {
        product[i][j] = c11[i][j];
        product[i][j + half] = c12[i][j];
        product[i + half][j] = c21[i][j];
        product[i + half][j + half] = c22[i][j];
      }
    }
  }
  else
  {
    product[0][0] = matrixA[0][0] * matrixB[0][0];
  }
  return product;
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

void printMatrix(int **matrix, int size)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

int max2power(int n)
{
  int product = 2;
  while (1)
  {
    if (n / product == 0 || n == product)
    {
      return product;
    }
    product *= 2;
  }
}

int main()
{
  int n;
  printf("Enter the size of the matrix: ");
  scanf("%d", &n);
  int N = max2power(n);

  // printf("%d\n", N);

  int **A = createMatrix(N);
  int **B = createMatrix(N);
  fillMatrix(A, n);
  fillMatrix(B, n);

  // printf("A:\n");
  // printMatrix(A, N);
  // printf("\nB:\n");
  // printMatrix(B, N);

  clock_t start = clock();
  int **C = matMuxStrassen(A, B, N);
  clock_t end = clock();

  double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

  // printf("\nC:\n");
  // printMatrix(C, N);
  printf("Time taken to multiply matrices: %f seconds\n", time_taken);

  return 0;
}