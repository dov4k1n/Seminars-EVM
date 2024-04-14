#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// #define 0.0001 0.0001

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
      if (fabs(mat->data[i][j]) < 0.0001) {
        printf("\t....");
      } else {
        printf("\t%.2lf", mat->data[i][j]);
      }
    }
    if (fabs(mat->data[i][mat->cols - 1]) < 0.0001) {
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
    mat[row][j] *= scalar;
  }
}

void add_scaled_row(matrix *mat, int src_row, int dest_row, double scalar) {
  for (int j = 0; j < mat->cols; j++) {
    mat[dest_row][j] += scalar * mat[src_row][j];
  }
}

// void swap_columns(double **A, int colsize, int i, int j) {
//   double tmp;
//   for (int k = 0; k < colsize; k++) {
//     tmp = A[k][i];
//     A[k][i] = A[k][j];
//     A[k][j] = tmp;
//   }
// }

/*
 * Source:
 * https://en.wikipedia.org/wiki/Gaussian_elimination#:~:text=order%2D2%20tensors).-,Pseudocode%5Bedit%5D,-As%20explained%20above
 */
void new_row_echelon_form(matrix *A) {
  A->rank = 0;
  int h = 0; // Initialization of the pivot row
  int k = 0; // Initialization of the pivot column
  double max_value;
  int max_value_row_index;

  while (h < A->rows && k < A->cols - 1) {
    max_value = fabs(A->data[h][k]);
    max_value_row_index = h;

    // Find the k-th pivot:
    for (int i = h; i < A->rows; i++) {
      if (fabs(A->data[i][k]) > max_value) {
        max_value = fabs(A->data[i][k]);
        max_value_row_index = i; 
      }
    }

    if (max_value < 0.0001) {
      // No pivot in this column, pass to next column
      k += 1;
    } 

    else {
      if (max_value_row_index != h) {
        swap_rows(A, h, max_value_row_index);
      }

      A->rank += 1;

      // Do for all rows below pivot:
      for (int i = h + 1; i < A->rows; i++) {
        double f = A->data[i][k] / A->data[h][k];
        // Fill with zeros the lower part of pivot column:
        A->data[i][k] = 0;
        // Do for all remaining elements in current row:
        for (int j = k + 1; j < A->cols; j++) {
          A->data[i][j] -= A->data[h][j] * f;
        }
      }

      // Increase pivot row and column
      h += 1;
      k += 1;
    }
  }
}

void reduced_row_echelon_form(matrix *A) {
  int h = A->rank - 1; // Initialization of the pivot row
  int k = 0; // Initialization of the pivot column
  double max_value;
  int max_value_row_index;

  while (h > 0 && k < A->cols - 1) {
    k = h;
    max_value = fabs(A->data[h][k]);
    max_value_row_index = h;

    // Find the k-th pivot:
    for (int j = h; j < A->cols; j++) {
      if (fabs(A->data[h][j]) < 0.0001) {
        // No pivot in this column, pass to next column
        k += 1;
      }
    }
    else {
      if (max_value_row_index != h) {
        swap_rows(A, h, max_value_row_index);
      }

      A->rank += 1;

      // Do for all rows below pivot:
      for (int i = h + 1; i < A->rows; i++) {
        double f = A->data[i][k] / A->data[h][k];
        // Fill with zeros the lower part of pivot column:
        A->data[i][k] = 0;
        // Do for all remaining elements in current row:
        for (int j = k + 1; j < A->cols; j++) {
          A->data[i][j] -= A->data[h][j] * f;
        }
      }

      // Increase pivot row and column
      h += 1;
      k += 1;
    }
  }
}

/* 
 * Requires row echelon form of matrix A 
 */ 
void new_reduced_row_echelon_form(matrix *A) {
  int h = A->rank - 1; // Initialization of the pivot row (last nonzero)

  while (h > 0) {
    for (int i = h - 1; i >= 0; i--) {
      for (int j = h; j < A->cols; j++) {
        A->data[i][j] -= A->data[h][j] / A->data[h][h] * A->data[i][j] ;
      }
    }
    h -= 1;
  }
}

// /* 
//  * Requires reduced row echelon form of matrix A 
//  */ 
// double *find_root(const double * const *A, const int n, const int rank) {
//   int i, j;
//   double *root = (double*)malloc((n-1)*sizeof(double));
//   if (root == NULL) {
//     return NULL;
//   }

//   for (i = 0; i < rank; i++) {
//     root[i] = A[i][n-1];
//     for (j = rank; j < n-1; j++)
//       root[i] -= A[i][j];
//   }
//   for (i = rank; i < n-1; i++)
//     root[i] = 1;

//   return root;
// }

// void nullspace(double **A, int n, int leadi, int it, double *root) {
//   int i, j = n-1-it-1;
//   for (i = 0; i < leadi; i++) {
//     root[i] = 0;
//     root[i] -= A[i][j];
//   }

//   for (i = leadi; i < n-1; i++)
//     root[i] = 0;
//   root[j] = 1;
// }

// int check_answer(double **B, int m, int n, double *root) {

// }

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

  new_row_echelon_form(A);
  printf("\nrank = %d, row echelon form:\n\n", A->rank);
  print_matrix(A);

  new_reduced_row_echelon_form(A);
  printf("\nreduced row echelon form:\n\n");
  print_matrix(A);

  free_matrix(A);
  free_matrix(B);
  printf("\n");
  return 0;
}

  // for (i = rank; i < m; i++)
  //   if (A[i][n-1] != 0) { //we got equation like 0 = b, where b != 0
  //     printf("\nno solution\n");//for wide matrix A[rank+][n-1] will be incorrect, so ok
  //     for (i = 0; i < m; i++)
  //       free(A[i]);
  //     free(A);
  //     return 0;
  //   }
  
  // int *perm = (int*)malloc(n*sizeof(int));
  // if (perm == NULL) {
  //   printf("error: couldn't create perm\n");
  //   for (i = 0; i < m; i++)
  //       free(A[i]);
  //     free(A);
  //   return -1;
  // }
  // for (i = 0; i < n; i++)
  //   perm[i] = i;

  // reduced_row_echelon_form(A, m, n, perm);

  // printf("\nreduced row echelon form:\n");
  // for (i = 0; i < m; i++) {
  //   for (j = 0; j < n-1; j++)
  //     printf("\t%.2lf", A[i][j]);
  //   printf("\t|\t%.2lf\n", A[i][n-1]);
  // }

  // // double *root;
  // // root = (double*)malloc((n-1)*sizeof(double));

  // double *root = find_root(A, n, rank);

  // if (root == NULL) {
  //   printf("erorr: root is NULL\n");
  //   for (i = 0; i < m; i++)
  //       free(A[i]);
  //   free(A);
  //   return -1;
  // }

  // printf("\nsolution of augmented matrix:\nv0: ");
  // for (i = 0; i < n-1; i++)
  //   printf("\t%.2lf", root[i]);
  // printf("\n");

  // printf("\nkernel dimension = %d:\n", n-1-leadi);
  // for (j = 0; j < n-1-leadi; j++) {
  //   nullspace(A, n, leadi, j, root);
  //   printf("v%d: ", j+1);
  //   for (i = 0; i < n-1; i++)
  //     printf("\t%.2lf", root[perm[i]]);
  //   printf("\n");
  // }

  // for (i = 0; i < m; i++)
  //   free(A[i]);
  // free(A);
  // free(root);
  // return 0;
// }