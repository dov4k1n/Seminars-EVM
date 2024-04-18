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

void swap_rows(matrix *A, int i, int j) {
  double *tmp = A->data[i];
  A->data[i] = A->data[j];
  A->data[j] = tmp;
}

void scale_row(matrix *mat, int row, double scalar) {
  for (int j = 0; j < mat->cols; j++) {
    mat->data[row][j] *= scalar;
  }
}

void add_scaled_row(matrix *mat, int dest_row, int src_row, double scalar) {
  for (int j = 0; j < mat->cols; j++) {
    mat->data[dest_row][j] += scalar * mat->data[src_row][j];
  }
}

void _row_echelon_form(matrix *A) {
  A->rank = 0;
  
  for (int j = 0; j < A->cols - 1; j++) {
    int pivot_row = -1;
    int pivot_col = -1;

    for (int i = j; i < A->rows; i++) {
      if (fabs(A->data[i][j]) > EPSILON) {
        pivot_row = i;
        pivot_col = j;
        if (i != j) {
          swap_rows(A, i, j);
        }
        A->rank += 1;
        break;
      }
    }

    if (pivot_row != -1) {
      for (int i = j + 1; i < A->rows; i++) {
        double scalar = (-1) * A->data[i][j] / A->data[j][j];
        add_scaled_row(A, i, j, scalar);
      }
    }
  }
}

/*
 * Requires row echelon form
 */
void _reduced_row_echelon_form(matrix *A) {
  // go upwards from the row indexed 'rank - 1', this is the last non-zero row:
  for (int i = A->rank - 1; i >= 0; i--) {
    int pivot_col = -1;

    // searching for the first non-zero element's column index in this row:
    for (int j = i; j < A->cols - 1; j++) {
      if (fabs(A->data[i][j]) > EPSILON) {
        pivot_col = j;
        break;
      }
    }

    if (pivot_col == -1) {
      break;
    }

    // for all the rows above the pivot row
    // subtract the pivot row with proper coefficient from them:
    for (int h = i - 1; h >= 0; h--) { 
      double scalar = (-1) * A->data[h][pivot_col] / A->data[i][pivot_col];
      add_scaled_row(A, h, i, scalar); 
    }

    // normalize each row:
    scale_row(A, i, 1 / A->data[i][pivot_col]);
  }
}

/* 
 * Requires reduced row echelon form of matrix A 
 */ 
double *find_root(matrix *A) {
  double *root = (double*)malloc((A->cols - 1)*sizeof(double));
  if (root == NULL) {
    return NULL;
  }

  for (int i = 0; i < A->rank; i++) {
    root[i] = A->data[i][A->cols - 1];
    for (int j = A->rank; j < A->cols - 1; j++) {
      root[i] -= A->data[i][j];
    }
  }

  for (int i = A->rank; i < A->cols - 1; i++) {
    root[i] = 1;
  }
  return root;
}

matrix *find_nullspace(matrix *A) {
  int _rows = A->cols - 1 - A->rank;
  int _cols = A->cols - 1;
  matrix *nullspace = create_matrix(_rows, _cols);
  if (nullspace == NULL) {
    return NULL;
  }

  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      nullspace->data[i][j] = 0;
    }
  }

  for (int i = 0; i < _rows; i++) {
    nullspace->data[i][i] -= A->data[i % A->rows][A->rank + i];
    nullspace->data[i][A->rank + i] = 1;
  }

  return nullspace;
}

void check_solution(matrix *B, double *root) {
  printf("\nchecking solution... differences:\n\n");

  for (int i = 0; i < B->rows; i++) {
    double sum = 0;
    for (int j = 0; j < B->cols - 1; j++) {
      sum += B->data[i][j] * root[j];
    }

    long double difference = fabs(sum - B->data[i][B->cols - 1]);
    printf("row %d:\t %Le\n", i + 1, difference);
  }
  printf("\n");
}

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

  _row_echelon_form(A);
  printf("\nrank = %d, row echelon form:\n\n", A->rank);
  print_matrix(A);

  _reduced_row_echelon_form(A);
  printf("\nreduced row echelon form:\n\n");
  print_matrix(A);

  for (int i = A->rank; i < A->rows; i++) {
    if (A->data[i][A->cols - 1] != 0) { //got equation like 0 = b, where b != 0
      printf("\nno solution\n");
      free_matrix(A);
      free_matrix(B);
      return 0;
    }
  }

  double *root = find_root(A);

  if (root == NULL) {
    printf("erorr: root is NULL\n");
    free_matrix(A);
    free_matrix(B);
    return -1;
  }

  printf("\nsolution of augmented matrix:\n\nv0: ");
  for (int i = 0; i < A->cols - 1; i++)
    printf("\t%.2lf", root[i]);
  printf("\n");

  matrix *nullspace = find_nullspace(A);
  if (nullspace == NULL) {
    printf("error: couldn't create matrix nullspace\n");
    free_matrix(A);
    free_matrix(B);
    free(root);
    return -1;
  }

  printf("\nnullspace dimension = %d, basis:\n\n", A->cols - 1 - A->rank);

  for (int i = 0; i < nullspace->rows; i++) {
    printf("v%d: ", i + 1);
    for (int j = 0; j < nullspace->cols - 1; j++) {
      if (fabs(nullspace->data[i][j]) < EPSILON) {
        printf("\t....");
      } else {
        printf("\t%.2lf", nullspace->data[i][j]);
      }
    }
    if (fabs(nullspace->data[i][nullspace->cols - 1]) < EPSILON) {
      printf("\t....\n");
    } else {
      printf("\t%.2lf\n", nullspace->data[i][nullspace->cols - 1]);
    }
  }

  check_solution(B, root);

  free_matrix(A);
  free_matrix(B);
  free_matrix(nullspace);
  free(root);
  printf("\n");
  return 0;
}