#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define EPSILON 0.0000000001

typedef struct {
  int rows;
  int cols;
  int rank;
  double **data;
} matrix;

matrix *create_matrix(const int rows, const int cols) {
  matrix *mat = malloc(sizeof(matrix));
  if (mat == NULL) {
    return NULL;
  }
  mat->rows = rows;
  mat->cols = cols;
  mat->data = (double**)malloc(rows * sizeof(double*));
  if (mat->data == NULL) {
    free(mat);
    return NULL;
  }
  for (int i = 0; i < rows; i++) {
    mat->data[i] = (double*)malloc(cols * sizeof(double));
    if (mat->data[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(mat->data[j]);
      }
      free(mat->data);
      free(mat);
      return NULL;
    }
  }
  return mat;
}

void free_matrix(matrix *mat) {
  for (int i = 0; i < mat->rows; i++) {
    free(mat->data[i]);
  }
  free(mat->data);
  free(mat);
}

int load_matrix(matrix *mat, FILE *in) {
  for (int i = 0; i < mat->rows; i++) {
    for (int j = 0; j < mat->cols; j++) {
      if (fscanf(in, "%lf", &mat->data[i][j]) != 1) {
        printf("error: couldn't read mat[%d][%d]\n", i, j);
        rewind(in);
        return 1;
      }
    }
  }
  rewind(in);
  return 0;
}

int generate_matrix(FILE *in, const int rows, const int cols, int choice) {
  int i, j;
  double input;

  if (choice == 1) {
    printf("enter augmented %dx%d matrix's elements line by line:\n", rows, cols);
    for (i = 0; i < rows; i++) {
      for (j = 0; j < cols; j++) {
        if (scanf("%lf", &input) != 1)
          return 1;
        if (j == cols - 1)
          fprintf(in, "%.2lf", input);
        else
          fprintf(in, "%.2lf ", input);
      }
    if (i != rows - 1) fprintf(in, "\n");
    }
    return 0;
  }

  else if (choice == 0) {
    srand(time(NULL));
    for (i = 0; i < rows; i++) {
      for (j = 0; j < cols; j++) {
        //input = (double)rand()/RAND_MAX * 300 - 150;
        input = rand() % 10;
        if (j == cols - 1)
          fprintf(in, "%.2lf", input);
        else
          fprintf(in, "%.2lf ", input);
      }
      if (i != rows - 1) fprintf(in, "\n");
    }
    return 0;
  }

  return 1;
}

void print_matrix(matrix *mat) {
  int i, j;
  for (i = 0; i < mat->rows; i++) {
    for (j = 0; j < mat->cols - 1; j++) {
      if (fabs(mat->data[i][j]) < EPSILON) {
        printf("\t....");
      } else {
        printf("\t%.2lf", mat->data[i][j]);
      }
    }
    if (fabs(mat->data[i][mat->cols - 1]) < EPSILON) {
      printf("\t|\t....\n");
    } else {
      printf("\t|\t%.2lf\n", mat->data[i][mat->cols - 1]);
    }
  }
}

/*
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░█║░░░░░░░░░░░░▄▄░░░░░░░░░░░░▄░░▄░░░
░░█║░░░░░░░▄░▄░█▄▄█║░░░░░░▄▄░░​█║░█║░░
░░█║░░░▄▄░░█║█║█║░▄║▄░░▄║█║░█║​█║▄█║░░
░░█║░░█║░█║█║█║░▀▀░░█║░█║█║░█║​░▀░▀░░░
░░█║▄║█║░█║─▀░░░░░░░█║▄█║░▀▀░░░░░░░░░
░░▀▀▀░░▀▀░░░░░░░░░░░░▀░█║░░░░░░░░░░░░
░░░░░░░▄▄─▄▄▀▀▄▀▀▄░░▀▄▄▀░░░░░░░░░░░░░
░░░░░░███████░░░▄▀░░░░░░░░░░░░░░░░░░░
░░░░░░▀█████▀▀▄▀░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░▀█▀░░░░░░░░░░░░░░░░░░░░░░░░░░
*/

void solve(matrix *A) {
  A->rank = 0;
  int pivot_row, pivot_col;
  double *tmp;
  double scalar;

  pivot_row = -1;
  pivot_col = -1;

  if (fabs(A->data[0][0]) > EPSILON) {
    pivot_row = 0;
    pivot_col = 0;
    A->rank += 1;
  }

  else if (fabs(A->data[1][0]) > EPSILON) {
    // swap rows(1, 0):
    tmp = A->data[1];
    A->data[1] = A->data[0];
    A->data[0] = tmp;

    pivot_row = 0;
    pivot_col = 0;
    A->rank += 1;
  }

  else if (fabs(A->data[2][0]) > EPSILON) {
    // swap rows(2, 0):
    tmp = A->data[2];
    A->data[2] = A->data[0];
    A->data[0] = tmp;

    pivot_row = 0;
    pivot_col = 0;
    A->rank += 1;
  }

  if (pivot_row != -1) {
    scalar = (-1) * A->data[1][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[1][0] += scalar * A->data[pivot_row][0];
    A->data[1][1] += scalar * A->data[pivot_row][1];
    A->data[1][2] += scalar * A->data[pivot_row][2];
    A->data[1][3] += scalar * A->data[pivot_row][3];

    scalar = (-1) * A->data[2][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[2][0] += scalar * A->data[pivot_row][0];
    A->data[2][1] += scalar * A->data[pivot_row][1];
    A->data[2][2] += scalar * A->data[pivot_row][2];
    A->data[2][3] += scalar * A->data[pivot_row][3];
  }

  pivot_row = -1;
  pivot_col = -1;

  if (fabs(A->data[1][1]) > EPSILON) {
    pivot_row = 1;
    pivot_col = 1;
    A->rank += 1;
  }

  else if (fabs(A->data[2][1]) > EPSILON) {
    // swap rows(2, 1):
    tmp = A->data[2];
    A->data[2] = A->data[1];
    A->data[1] = tmp;

    pivot_row = 1;
    pivot_col = 1;
    A->rank += 1;
  }

  if (pivot_row != -1) {
    scalar = (-1) * A->data[2][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[2][0] += scalar * A->data[pivot_row][0];
    A->data[2][1] += scalar * A->data[pivot_row][1];
    A->data[2][2] += scalar * A->data[pivot_row][2];
    A->data[2][3] += scalar * A->data[pivot_row][3];
  }

  pivot_row = -1;
  pivot_col = -1;

  if (fabs(A->data[2][2]) > EPSILON) {
    pivot_row = 2;
    pivot_col = 2;
    A->rank += 1;
  }

  pivot_row = 2;
  pivot_col = -1;
  if (fabs(A->data[pivot_row][2]) > EPSILON) {
    pivot_col = 2;
  }

  if (pivot_col != -1) {
    scalar = 1 / A->data[pivot_row][pivot_col];
    A->data[pivot_row][2] *= scalar;
    A->data[pivot_row][3] *= scalar;

    scalar = (-1) * A->data[1][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[1][1] += scalar * A->data[pivot_row][1];
    A->data[1][2] += scalar * A->data[pivot_row][2];
    A->data[1][3] += scalar * A->data[pivot_row][3];

    scalar = (-1) * A->data[0][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[0][0] += scalar * A->data[pivot_row][0];
    A->data[0][1] += scalar * A->data[pivot_row][1];
    A->data[0][2] += scalar * A->data[pivot_row][2];
    A->data[0][3] += scalar * A->data[pivot_row][3];

  }
  pivot_row = 1;
  pivot_col = -1;
  if (fabs(A->data[pivot_row][1]) > EPSILON) {
    pivot_col = 1;
  }

  else if (fabs(A->data[pivot_row][2]) > EPSILON) {
    pivot_col = 2;
  }

  if (pivot_col != -1) {
    scalar = 1 / A->data[pivot_row][pivot_col];
    A->data[pivot_row][1] *= scalar;
    A->data[pivot_row][2] *= scalar;
    A->data[pivot_row][3] *= scalar;

    scalar = (-1) * A->data[0][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[0][0] += scalar * A->data[pivot_row][0];
    A->data[0][1] += scalar * A->data[pivot_row][1];
    A->data[0][2] += scalar * A->data[pivot_row][2];
    A->data[0][3] += scalar * A->data[pivot_row][3];

  }
  pivot_row = 0;
  pivot_col = -1;
  if (fabs(A->data[pivot_row][0]) > EPSILON) {
    pivot_col = 0;
  }

  else if (fabs(A->data[pivot_row][1]) > EPSILON) {
    pivot_col = 1;
  }

  else if (fabs(A->data[pivot_row][2]) > EPSILON) {
    pivot_col = 2;
  }

  if (pivot_col != -1) {
    scalar = 1 / A->data[pivot_row][pivot_col];
    A->data[pivot_row][0] *= scalar;
    A->data[pivot_row][1] *= scalar;
    A->data[pivot_row][2] *= scalar;
    A->data[pivot_row][3] *= scalar;

  }
}

/*
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░█║░░░░░░░░░░░░▄▄░░░░░░░░░░░░▄░░▄░░░
░░█║░░░░░░░▄░▄░█▄▄█║░░░░░░▄▄░░​█║░█║░░
░░█║░░░▄▄░░█║█║█║░▄║▄░░▄║█║░█║​█║▄█║░░
░░█║░░█║░█║█║█║░▀▀░░█║░█║█║░█║​░▀░▀░░░
░░█║▄║█║░█║─▀░░░░░░░█║▄█║░▀▀░░░░░░░░░
░░▀▀▀░░▀▀░░░░░░░░░░░░▀░█║░░░░░░░░░░░░
░░░░░░░▄▄─▄▄▀▀▄▀▀▄░░▀▄▄▀░░░░░░░░░░░░░
░░░░░░███████░░░▄▀░░░░░░░░░░░░░░░░░░░
░░░░░░▀█████▀▀▄▀░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░▀█▀░░░░░░░░░░░░░░░░░░░░░░░░░░
*/

int main() {
  int rows_input, cols_input;

  printf(
    "\nenter augmented matrix dimensions "
    "(two numbers: M for rows, N for columns):\n"
  );
  
  if (scanf("%d %d", &rows_input, &cols_input) != 2 ||
      rows_input <= 0 || cols_input <= 0
  ) {
    printf("error: couldn't read M or N, or wrong format\n");
    return -1;
  }

  const int rows = rows_input;
  const int cols = cols_input;

  int choice = 0;
  printf("type 1 to enter manual matrix, or 0 to generate random:\n");

  if (scanf("%d", &choice) != 1 || choice > 1 || choice < 0) {
    printf("error: couldn't read choice or wrong format\n");
    return -1;
  }

  FILE *in = fopen("input.txt", "wt");
  if (in == NULL) {
    printf("error: couldn't open input.txt\n");
    return -1;
  }
  
  if (generate_matrix(in, rows, cols, choice)) {
    printf("error: wrong format\n");
    fclose(in);
    return -1;
  }

  fclose(in);

  matrix *A = create_matrix(rows, cols);
  if (A == NULL) {
    printf("error: couldn't create matrix A\n");
    return -1;
  }

  matrix *B = create_matrix(rows, cols);
  if (B == NULL) {
    printf("error: couldn't create matrix B\n");
    free_matrix(A);
    return -1;
  }
  
  in = fopen("input.txt", "rt");
  if (in == NULL) {
    printf("error: couldn't reopen input.txt\n");
    free_matrix(A);
    free_matrix(B);
    return -1;
  }

  if (load_matrix(A, in) || load_matrix(B, in)) {
    free_matrix(A);
    free_matrix(B);
    fclose(in);
    return -1;
  }

  fclose(in);

  printf("\ninputed:\n\n");
  print_matrix(A);

  solve(A);
  printf("\nrank = %d, reduced row echelon form:\n\n", A->rank);
  print_matrix(A);

  free_matrix(A);
  free_matrix(B);
  // free_matrix(nullspace);
  // free(root);
  printf("\n");
  return 0;
}