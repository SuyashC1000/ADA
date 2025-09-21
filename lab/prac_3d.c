// Matrix Multiplication Methods Aggregation

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

void freeMatrix(int **matrix, int size)
{
  for (int i = 0; i < size; i++)
  {
    free(matrix[i]);
  }
  free(matrix);
}

int **matMuxIterative(int **matrixA, int **matrixB, int size)
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

int **matMuxDivideConquer(int **matrixA, int **matrixB, int size)
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

    int **c11 = addMatrix(matMuxDivideConquer(a11, b11, half),
                          matMuxDivideConquer(a12, b21, half), half);
    int **c12 = addMatrix(matMuxDivideConquer(a11, b12, half),
                          matMuxDivideConquer(a12, b22, half), half);
    int **c21 = addMatrix(matMuxDivideConquer(a21, b11, half),
                          matMuxDivideConquer(a22, b21, half), half);
    int **c22 = addMatrix(matMuxDivideConquer(a21, b12, half),
                          matMuxDivideConquer(a22, b22, half), half);

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
    freeMatrix(a11, half);
    freeMatrix(a12, half);
    freeMatrix(a21, half);
    freeMatrix(a22, half);
    freeMatrix(b11, half);
    freeMatrix(b12, half);
    freeMatrix(b21, half);
    freeMatrix(b22, half);
    freeMatrix(c11, half);
    freeMatrix(c12, half);
    freeMatrix(c21, half);
    freeMatrix(c22, half);
  }

  else
  {
    product[0][0] = matrixA[0][0] * matrixB[0][0];
  }

  return product;
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
    freeMatrix(a11, half);
    freeMatrix(a12, half);
    freeMatrix(a21, half);
    freeMatrix(a22, half);
    freeMatrix(b11, half);
    freeMatrix(b12, half);
    freeMatrix(b21, half);
    freeMatrix(b22, half);

    int **c11 = addMatrix(subMatrix(addMatrix(matrixP, matrixS, half), matrixT, half), matrixV, half);
    int **c12 = addMatrix(matrixR, matrixT, half);
    int **c21 = addMatrix(matrixQ, matrixS, half);
    int **c22 = addMatrix(subMatrix(addMatrix(matrixP, matrixR, half), matrixQ, half), matrixU, half);
    freeMatrix(matrixP, half);
    freeMatrix(matrixQ, half);
    freeMatrix(matrixR, half);
    freeMatrix(matrixS, half);
    freeMatrix(matrixT, half);
    freeMatrix(matrixU, half);
    freeMatrix(matrixV, half);

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
    freeMatrix(c11, half);
    freeMatrix(c12, half);
    freeMatrix(c21, half);
    freeMatrix(c22, half);
  }
  else
  {
    product[0][0] = matrixA[0][0] * matrixB[0][0];
  }
  return product;
}

int main()
{
  int n;
  printf("Enter n for creating matrices of size 2^n: ");
  scanf("%d", &n);
  n = pow(2, n);

  int **m1 = createMatrix(n);
  int **m2 = createMatrix(n);
  fillMatrix(m1, n);
  fillMatrix(m2, n);

  int **m3 = createMatrix(n);

  clock_t start_1 = clock();
  m3 = matMuxIterative(m1, m2, n);
  clock_t end_1 = clock();

  clock_t start_2 = clock();
  m3 = matMuxDivideConquer(m1, m2, n);
  clock_t end_2 = clock();

  clock_t start_3 = clock();
  m3 = matMuxStrassen(m1, m2, n);
  clock_t end_3 = clock();

  double time_taken_1 = ((double)(end_1 - start_1)) / CLOCKS_PER_SEC;
  double time_taken_2 = ((double)(end_2 - start_2)) / CLOCKS_PER_SEC;
  double time_taken_3 = ((double)(end_3 - start_3)) / CLOCKS_PER_SEC;

  // printf("Product:\n");
  // printMatrix(m3, n);

  printf("Time taken to multiply matrices (Iterative): %f seconds\n", time_taken_1);
  printf("Time taken to multiply matrices (Divide & Conquer): %f seconds\n", time_taken_2);
  printf("Time taken to multiply matrices (Strassen): %f seconds\n", time_taken_3);
}