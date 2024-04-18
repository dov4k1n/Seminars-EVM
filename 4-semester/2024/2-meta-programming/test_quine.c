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
                                      ▓▓▓▓              ████                                            
                                      ██▓▓▓▓          ▓▓▓▓██                                            
                                      ██▓▓▒▒██      ██▓▓▒▒██                                            
                                      ██▓▓▓▓▓▓██████▓▓▓▓▒▒██                                            
                              ██▓▓    ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██    ▓▓▓▓                                    
                              ░░░░██  ██▓▓▓▓░░▓▓▓▓▓▓░░▓▓▒▒██  ▓▓░░░░                                    
                                  ░░  ██▓▓▓▓  ▓▓▓▓██  ▓▓▒▒██  ░░                                        
                              ██████  ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██  ██████                                    
                                        ██▓▓▓▓▓▓▓▓▓▓▓▓▒▒██              ██▓▓              ▓▓██          
                                        ░░██████████████░░              ██▓▓▓▓          ▓▓▓▓██          
                            ██████      ██▓▓▓▓▓▓▓▓▓▓▒▒▒▒██              ██▓▓▒▒██      ██▓▓▒▒██          
                          ██▓▓▓▓██    ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██              ██▓▓▓▓▓▓██████▓▓▓▓▒▒██          
                          ██▓▓██      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██      ████    ██▓▓▓▓██▓▓▓▓▓▓▓▓▓▓▒▒██    ████  
                          ██▓▓██    ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██          ██  ██▓▓██  ▓▓▓▓▓▓  ▓▓▒▒██  ██      
                          ██▓▓██  ██▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▒▒██              ██▓▓██  ▓▓▓▓▓▓  ▓▓▒▒██          
                          ██▓▓██    ██▓▓▓▓▓▓▒▒▒▒▒▒▓▓▓▓▒▒██      ██████  ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██  ██████  
                          ██▓▓██    ██▓▓▓▓▓▓▓▓▒▒▒▒▒▒██▒▒██                ██▓▓▓▓▓▓▓▓▓▓▓▓▒▒██            
                            ██▓▓▓▓  ██▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▓▓██            ▓▓▓▓██████████████████            
                            ██▓▓██  ██▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▓▓██          ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒██          
                              ████████▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒██          ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██        
                            ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒██    ▓▓▓▓▓▓▓▓████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██      
                        ▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████▓▓▓▓▓▓▓▓▓▓▓▓▒▒██      
                      ▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒░░░░▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▓▓▒▒░░░░▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓    
                    ▓▓▒▒░░░░▒▒▒▒░░▒▒░░░░░░▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒░░░░░░░░▒▒▒▒░░▒▒▒▒██▓▓▓▓▓▓▓▓▓▓▒▒██    
                  ▓▓▒▒▒▒░░▒▒▒▒▒▒░░░░░░░░▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒▒▒▒▒░░▒▒▒▒██▓▓▓▓▓▓▓▓▓▓▒▒██  
                  ▓▓▒▒░░▒▒▒▒░░░░░░░░░░▒▒▒▒░░▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░▒▒▒▒░░░░▒▒██▓▓▓▓▓▓▓▓▓▓▒▒██  
                ██▒▒░░▒▒▒▒░░░░░░░░░░▒▒▒▒░░▒▒▒▒░░▒▒░░▒▒▒▒░░▒▒▒▒▒▒░░▒▒▒▒░░░░░░▒▒▒▒▒▒▒▒░░▒▒██▓▓▓▓▓▓▓▓▒▒██  
                ▓▓░░░░▒▒▒▒░░░░░░░░▒▒▒▒░░░░▒▒▒▒░░░░▒▒▒▒▒▒░░████▒▒░░▒▒▒▒▒▒░░░░████▒▒▒▒░░░░██▓▓▓▓▓▓▓▓▒▒██  
              ▓▓▒▒░░▒▒▒▒░░░░░░░░░░▒▒▒▒░░░░▒▒▒▒░░░░▒▒▒▒▒▒░░██▒▒██░░▒▒▒▒▒▒▒▒██▒▒██▒▒▒▒▒▒▒▒░░██▓▓▓▓▓▓▒▒██  
              ▓▓░░░░▒▒▒▒░░░░░░░░▒▒▒▒▒▒░░░░▒▒▒▒░░░░░░▒▒▒▒░░██▓▓▒▒▓▓░░▒▒▒▒▓▓▓▓▒▒██▒▒▒▒▒▒░░▒▒██▓▓▓▓▓▓▒▒██  
            ▒▒▒▒░░░░▒▒▒▒░░░░░░░░▒▒▒▒▒▒░░▒▒▒▒▒▒░░░░░░▒▒▒▒░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██▒▒▒▒▒▒░░░░▒▒██▓▓▓▓▒▒██  
            ▓▓░░░░░░▒▒▒▒░░░░░░▒▒▒▒▒▒▒▒░░▒▒▒▒░░░░░░▓▓▓▓▒▒░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██▒▒▒▒▓▓▓▓░░▒▒██▓▓▓▓▓▓██  
            ▓▓▒▒░░▒▒▒▒▒▒░░░░░░▒▒▒▒▒▒░░░░▒▒▒▒░░░░░░░░▒▒██░░██▓▓▓▓  ▓▓▓▓▓▓  ▓▓▒▒██▒▒██▒▒▒▒░░░░██▓▓▒▒████  
            ▓▓▒▒░░▒▒▒▒░░░░░░░░▒▒▒▒░░░░▒▒▒▒░░░░░░░░▒▒▒▒▒▒░░██▓▓██  ▓▓▓▓▓▓  ▓▓▒▒██░░▒▒▒▒▒▒░░▒▒██▓▓▒▒████  
            ▓▓▒▒░░▒▒▒▒▒▒░░░░▒▒▒▒▒▒░░░░▒▒▒▒░░░░░░░░██████░░██▓▓▓▓██▓▓▓▓▓▓▓▓▓▓▒▒██░░██████░░▒▒██▓▓██▓▓██  
            ▓▓▒▒░░▒▒▒▒▒▒░░░░▒▒▒▒▒▒░░░░▒▒▒▒░░░░░░░░░░▒▒▒▒░░░░██▓▓▓▓▓▓▓▓▓▓▓▓▒▒██░░░░▒▒▒▒▒▒░░░░▓▓████▓▓██  
            ▓▓▒▒░░▒▒▒▒▒▒░░░░▒▒▒▒░░░░░░▒▒▒▒░░░░░░░░░░▒▒▒▒░░░░▒▒██████████████▒▒░░░░▒▒▒▒▒▒░░░░▓▓  ██▓▓██  
            ▓▓▒▒░░▒▒▒▒░░░░░░▒▒▒▒░░░░░░▒▒▒▒░░░░░░░░░░▒▒▒▒░░░░██▓▓▓▓▓▓▓▓▓▓▒▒▓▓██░░░░████▓▓░░▒▒▓▓  ██▓▓██  
            ░░▓▓░░░░▒▒▒▒░░░░▒▒▒▒░░░░░░▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒░░░░██▓▓▓▓▓▓▓▓▓▓▓▓▒▒██░░▒▒██▓▓▓▓▓▓▓▓░░  ██▓▓██  
              ▓▓▒▒░░▒▒▒▒░░░░▒▒▒▒▒▒░░░░▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒░░░░██▓▓▓▓▓▓▓▓▓▓▓▓▒▒██░░▒▒▓▓██▓▓██▓▓    ██▓▓██  
                ▓▓░░▒▒▒▒░░░░░░▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██▒▒▒▒██▓▓██      ██▓▓██  
                ▓▓▒▒▒▒▒▒░░░░░░▒▒▒▒░░░░░░▒▒▒▒░░░░░░░░▒▒▒▒░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██▒▒▒▒██▓▓██      ██▓▓██  
                ░░▓▓░░▒▒▒▒▒▒░░░░▒▒▒▒▒▒░░▒▒▒▒▒▒░░░░░░▒▒▒▒░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██▒▒▒▒██▓▓██      ░░██░░  
    ██████████████▓▓▒▒▒▒▒▒▒▒░░░░▒▒▒▒░░▒▒▒▒▒▒░░░░░░░░▒▒▒▒░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██▒▒▒▒██▓▓██              
  ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░▒▒▒▒░░░░▒▒▒▒░░▒▒▒▒░░▒▒░░░░▒▒▒▒░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██░░▒▒██▓▓██              
    ██████████████████▓▓▒▒▒▒▒▒▒▒░░░░▒▒▒▒░░▒▒▒▒▒▒░░░░▒▒▒▒░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██▒▒██▓▓██                
      ░░░░░░      ░░    ▓▓▓▓▓▓▓▓▒▒░░▒▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██▓▓██▓▓██                
                        ░░░░░░░░▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒░░░░▒▒▒▒▒▒██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒████▓▓██░░                
                                          ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██████████████████████▓▓    
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

  else if (fabs(A->data[3][0]) > EPSILON) {
    // swap rows(3, 0):
    tmp = A->data[3];
    A->data[3] = A->data[0];
    A->data[0] = tmp;

    pivot_row = 0;
    pivot_col = 0;
    A->rank += 1;
  }

  else if (fabs(A->data[4][0]) > EPSILON) {
    // swap rows(4, 0):
    tmp = A->data[4];
    A->data[4] = A->data[0];
    A->data[0] = tmp;

    pivot_row = 0;
    pivot_col = 0;
    A->rank += 1;
  }

  else if (fabs(A->data[5][0]) > EPSILON) {
    // swap rows(5, 0):
    tmp = A->data[5];
    A->data[5] = A->data[0];
    A->data[0] = tmp;

    pivot_row = 0;
    pivot_col = 0;
    A->rank += 1;
  }

  else if (fabs(A->data[6][0]) > EPSILON) {
    // swap rows(6, 0):
    tmp = A->data[6];
    A->data[6] = A->data[0];
    A->data[0] = tmp;

    pivot_row = 0;
    pivot_col = 0;
    A->rank += 1;
  }

  else if (fabs(A->data[7][0]) > EPSILON) {
    // swap rows(7, 0):
    tmp = A->data[7];
    A->data[7] = A->data[0];
    A->data[0] = tmp;

    pivot_row = 0;
    pivot_col = 0;
    A->rank += 1;
  }

  else if (fabs(A->data[8][0]) > EPSILON) {
    // swap rows(8, 0):
    tmp = A->data[8];
    A->data[8] = A->data[0];
    A->data[0] = tmp;

    pivot_row = 0;
    pivot_col = 0;
    A->rank += 1;
  }

  else if (fabs(A->data[9][0]) > EPSILON) {
    // swap rows(9, 0):
    tmp = A->data[9];
    A->data[9] = A->data[0];
    A->data[0] = tmp;

    pivot_row = 0;
    pivot_col = 0;
    A->rank += 1;
  }

  if (pivot_row != -1) {
    scalar = (-1) * A->data[1][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[1][0] += scalar * A->data[0][0];
    A->data[1][1] += scalar * A->data[0][1];
    A->data[1][2] += scalar * A->data[0][2];
    A->data[1][3] += scalar * A->data[0][3];
    A->data[1][4] += scalar * A->data[0][4];
    A->data[1][5] += scalar * A->data[0][5];
    A->data[1][6] += scalar * A->data[0][6];
    A->data[1][7] += scalar * A->data[0][7];
    A->data[1][8] += scalar * A->data[0][8];
    A->data[1][9] += scalar * A->data[0][9];
    A->data[1][10] += scalar * A->data[0][10];

    scalar = (-1) * A->data[2][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[2][0] += scalar * A->data[0][0];
    A->data[2][1] += scalar * A->data[0][1];
    A->data[2][2] += scalar * A->data[0][2];
    A->data[2][3] += scalar * A->data[0][3];
    A->data[2][4] += scalar * A->data[0][4];
    A->data[2][5] += scalar * A->data[0][5];
    A->data[2][6] += scalar * A->data[0][6];
    A->data[2][7] += scalar * A->data[0][7];
    A->data[2][8] += scalar * A->data[0][8];
    A->data[2][9] += scalar * A->data[0][9];
    A->data[2][10] += scalar * A->data[0][10];

    scalar = (-1) * A->data[3][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[3][0] += scalar * A->data[0][0];
    A->data[3][1] += scalar * A->data[0][1];
    A->data[3][2] += scalar * A->data[0][2];
    A->data[3][3] += scalar * A->data[0][3];
    A->data[3][4] += scalar * A->data[0][4];
    A->data[3][5] += scalar * A->data[0][5];
    A->data[3][6] += scalar * A->data[0][6];
    A->data[3][7] += scalar * A->data[0][7];
    A->data[3][8] += scalar * A->data[0][8];
    A->data[3][9] += scalar * A->data[0][9];
    A->data[3][10] += scalar * A->data[0][10];

    scalar = (-1) * A->data[4][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[4][0] += scalar * A->data[0][0];
    A->data[4][1] += scalar * A->data[0][1];
    A->data[4][2] += scalar * A->data[0][2];
    A->data[4][3] += scalar * A->data[0][3];
    A->data[4][4] += scalar * A->data[0][4];
    A->data[4][5] += scalar * A->data[0][5];
    A->data[4][6] += scalar * A->data[0][6];
    A->data[4][7] += scalar * A->data[0][7];
    A->data[4][8] += scalar * A->data[0][8];
    A->data[4][9] += scalar * A->data[0][9];
    A->data[4][10] += scalar * A->data[0][10];

    scalar = (-1) * A->data[5][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[5][0] += scalar * A->data[0][0];
    A->data[5][1] += scalar * A->data[0][1];
    A->data[5][2] += scalar * A->data[0][2];
    A->data[5][3] += scalar * A->data[0][3];
    A->data[5][4] += scalar * A->data[0][4];
    A->data[5][5] += scalar * A->data[0][5];
    A->data[5][6] += scalar * A->data[0][6];
    A->data[5][7] += scalar * A->data[0][7];
    A->data[5][8] += scalar * A->data[0][8];
    A->data[5][9] += scalar * A->data[0][9];
    A->data[5][10] += scalar * A->data[0][10];

    scalar = (-1) * A->data[6][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[6][0] += scalar * A->data[0][0];
    A->data[6][1] += scalar * A->data[0][1];
    A->data[6][2] += scalar * A->data[0][2];
    A->data[6][3] += scalar * A->data[0][3];
    A->data[6][4] += scalar * A->data[0][4];
    A->data[6][5] += scalar * A->data[0][5];
    A->data[6][6] += scalar * A->data[0][6];
    A->data[6][7] += scalar * A->data[0][7];
    A->data[6][8] += scalar * A->data[0][8];
    A->data[6][9] += scalar * A->data[0][9];
    A->data[6][10] += scalar * A->data[0][10];

    scalar = (-1) * A->data[7][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[7][0] += scalar * A->data[0][0];
    A->data[7][1] += scalar * A->data[0][1];
    A->data[7][2] += scalar * A->data[0][2];
    A->data[7][3] += scalar * A->data[0][3];
    A->data[7][4] += scalar * A->data[0][4];
    A->data[7][5] += scalar * A->data[0][5];
    A->data[7][6] += scalar * A->data[0][6];
    A->data[7][7] += scalar * A->data[0][7];
    A->data[7][8] += scalar * A->data[0][8];
    A->data[7][9] += scalar * A->data[0][9];
    A->data[7][10] += scalar * A->data[0][10];

    scalar = (-1) * A->data[8][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[8][0] += scalar * A->data[0][0];
    A->data[8][1] += scalar * A->data[0][1];
    A->data[8][2] += scalar * A->data[0][2];
    A->data[8][3] += scalar * A->data[0][3];
    A->data[8][4] += scalar * A->data[0][4];
    A->data[8][5] += scalar * A->data[0][5];
    A->data[8][6] += scalar * A->data[0][6];
    A->data[8][7] += scalar * A->data[0][7];
    A->data[8][8] += scalar * A->data[0][8];
    A->data[8][9] += scalar * A->data[0][9];
    A->data[8][10] += scalar * A->data[0][10];

    scalar = (-1) * A->data[9][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[9][0] += scalar * A->data[0][0];
    A->data[9][1] += scalar * A->data[0][1];
    A->data[9][2] += scalar * A->data[0][2];
    A->data[9][3] += scalar * A->data[0][3];
    A->data[9][4] += scalar * A->data[0][4];
    A->data[9][5] += scalar * A->data[0][5];
    A->data[9][6] += scalar * A->data[0][6];
    A->data[9][7] += scalar * A->data[0][7];
    A->data[9][8] += scalar * A->data[0][8];
    A->data[9][9] += scalar * A->data[0][9];
    A->data[9][10] += scalar * A->data[0][10];
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

  else if (fabs(A->data[3][1]) > EPSILON) {
    // swap rows(3, 1):
    tmp = A->data[3];
    A->data[3] = A->data[1];
    A->data[1] = tmp;

    pivot_row = 1;
    pivot_col = 1;
    A->rank += 1;
  }

  else if (fabs(A->data[4][1]) > EPSILON) {
    // swap rows(4, 1):
    tmp = A->data[4];
    A->data[4] = A->data[1];
    A->data[1] = tmp;

    pivot_row = 1;
    pivot_col = 1;
    A->rank += 1;
  }

  else if (fabs(A->data[5][1]) > EPSILON) {
    // swap rows(5, 1):
    tmp = A->data[5];
    A->data[5] = A->data[1];
    A->data[1] = tmp;

    pivot_row = 1;
    pivot_col = 1;
    A->rank += 1;
  }

  else if (fabs(A->data[6][1]) > EPSILON) {
    // swap rows(6, 1):
    tmp = A->data[6];
    A->data[6] = A->data[1];
    A->data[1] = tmp;

    pivot_row = 1;
    pivot_col = 1;
    A->rank += 1;
  }

  else if (fabs(A->data[7][1]) > EPSILON) {
    // swap rows(7, 1):
    tmp = A->data[7];
    A->data[7] = A->data[1];
    A->data[1] = tmp;

    pivot_row = 1;
    pivot_col = 1;
    A->rank += 1;
  }

  else if (fabs(A->data[8][1]) > EPSILON) {
    // swap rows(8, 1):
    tmp = A->data[8];
    A->data[8] = A->data[1];
    A->data[1] = tmp;

    pivot_row = 1;
    pivot_col = 1;
    A->rank += 1;
  }

  else if (fabs(A->data[9][1]) > EPSILON) {
    // swap rows(9, 1):
    tmp = A->data[9];
    A->data[9] = A->data[1];
    A->data[1] = tmp;

    pivot_row = 1;
    pivot_col = 1;
    A->rank += 1;
  }

  if (pivot_row != -1) {
    scalar = (-1) * A->data[2][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[2][0] += scalar * A->data[1][0];
    A->data[2][1] += scalar * A->data[1][1];
    A->data[2][2] += scalar * A->data[1][2];
    A->data[2][3] += scalar * A->data[1][3];
    A->data[2][4] += scalar * A->data[1][4];
    A->data[2][5] += scalar * A->data[1][5];
    A->data[2][6] += scalar * A->data[1][6];
    A->data[2][7] += scalar * A->data[1][7];
    A->data[2][8] += scalar * A->data[1][8];
    A->data[2][9] += scalar * A->data[1][9];
    A->data[2][10] += scalar * A->data[1][10];

    scalar = (-1) * A->data[3][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[3][0] += scalar * A->data[1][0];
    A->data[3][1] += scalar * A->data[1][1];
    A->data[3][2] += scalar * A->data[1][2];
    A->data[3][3] += scalar * A->data[1][3];
    A->data[3][4] += scalar * A->data[1][4];
    A->data[3][5] += scalar * A->data[1][5];
    A->data[3][6] += scalar * A->data[1][6];
    A->data[3][7] += scalar * A->data[1][7];
    A->data[3][8] += scalar * A->data[1][8];
    A->data[3][9] += scalar * A->data[1][9];
    A->data[3][10] += scalar * A->data[1][10];

    scalar = (-1) * A->data[4][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[4][0] += scalar * A->data[1][0];
    A->data[4][1] += scalar * A->data[1][1];
    A->data[4][2] += scalar * A->data[1][2];
    A->data[4][3] += scalar * A->data[1][3];
    A->data[4][4] += scalar * A->data[1][4];
    A->data[4][5] += scalar * A->data[1][5];
    A->data[4][6] += scalar * A->data[1][6];
    A->data[4][7] += scalar * A->data[1][7];
    A->data[4][8] += scalar * A->data[1][8];
    A->data[4][9] += scalar * A->data[1][9];
    A->data[4][10] += scalar * A->data[1][10];

    scalar = (-1) * A->data[5][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[5][0] += scalar * A->data[1][0];
    A->data[5][1] += scalar * A->data[1][1];
    A->data[5][2] += scalar * A->data[1][2];
    A->data[5][3] += scalar * A->data[1][3];
    A->data[5][4] += scalar * A->data[1][4];
    A->data[5][5] += scalar * A->data[1][5];
    A->data[5][6] += scalar * A->data[1][6];
    A->data[5][7] += scalar * A->data[1][7];
    A->data[5][8] += scalar * A->data[1][8];
    A->data[5][9] += scalar * A->data[1][9];
    A->data[5][10] += scalar * A->data[1][10];

    scalar = (-1) * A->data[6][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[6][0] += scalar * A->data[1][0];
    A->data[6][1] += scalar * A->data[1][1];
    A->data[6][2] += scalar * A->data[1][2];
    A->data[6][3] += scalar * A->data[1][3];
    A->data[6][4] += scalar * A->data[1][4];
    A->data[6][5] += scalar * A->data[1][5];
    A->data[6][6] += scalar * A->data[1][6];
    A->data[6][7] += scalar * A->data[1][7];
    A->data[6][8] += scalar * A->data[1][8];
    A->data[6][9] += scalar * A->data[1][9];
    A->data[6][10] += scalar * A->data[1][10];

    scalar = (-1) * A->data[7][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[7][0] += scalar * A->data[1][0];
    A->data[7][1] += scalar * A->data[1][1];
    A->data[7][2] += scalar * A->data[1][2];
    A->data[7][3] += scalar * A->data[1][3];
    A->data[7][4] += scalar * A->data[1][4];
    A->data[7][5] += scalar * A->data[1][5];
    A->data[7][6] += scalar * A->data[1][6];
    A->data[7][7] += scalar * A->data[1][7];
    A->data[7][8] += scalar * A->data[1][8];
    A->data[7][9] += scalar * A->data[1][9];
    A->data[7][10] += scalar * A->data[1][10];

    scalar = (-1) * A->data[8][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[8][0] += scalar * A->data[1][0];
    A->data[8][1] += scalar * A->data[1][1];
    A->data[8][2] += scalar * A->data[1][2];
    A->data[8][3] += scalar * A->data[1][3];
    A->data[8][4] += scalar * A->data[1][4];
    A->data[8][5] += scalar * A->data[1][5];
    A->data[8][6] += scalar * A->data[1][6];
    A->data[8][7] += scalar * A->data[1][7];
    A->data[8][8] += scalar * A->data[1][8];
    A->data[8][9] += scalar * A->data[1][9];
    A->data[8][10] += scalar * A->data[1][10];

    scalar = (-1) * A->data[9][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[9][0] += scalar * A->data[1][0];
    A->data[9][1] += scalar * A->data[1][1];
    A->data[9][2] += scalar * A->data[1][2];
    A->data[9][3] += scalar * A->data[1][3];
    A->data[9][4] += scalar * A->data[1][4];
    A->data[9][5] += scalar * A->data[1][5];
    A->data[9][6] += scalar * A->data[1][6];
    A->data[9][7] += scalar * A->data[1][7];
    A->data[9][8] += scalar * A->data[1][8];
    A->data[9][9] += scalar * A->data[1][9];
    A->data[9][10] += scalar * A->data[1][10];
  }

  pivot_row = -1;
  pivot_col = -1;

  if (fabs(A->data[2][2]) > EPSILON) {
    pivot_row = 2;
    pivot_col = 2;
    A->rank += 1;
  }

  else if (fabs(A->data[3][2]) > EPSILON) {
    // swap rows(3, 2):
    tmp = A->data[3];
    A->data[3] = A->data[2];
    A->data[2] = tmp;

    pivot_row = 2;
    pivot_col = 2;
    A->rank += 1;
  }

  else if (fabs(A->data[4][2]) > EPSILON) {
    // swap rows(4, 2):
    tmp = A->data[4];
    A->data[4] = A->data[2];
    A->data[2] = tmp;

    pivot_row = 2;
    pivot_col = 2;
    A->rank += 1;
  }

  else if (fabs(A->data[5][2]) > EPSILON) {
    // swap rows(5, 2):
    tmp = A->data[5];
    A->data[5] = A->data[2];
    A->data[2] = tmp;

    pivot_row = 2;
    pivot_col = 2;
    A->rank += 1;
  }

  else if (fabs(A->data[6][2]) > EPSILON) {
    // swap rows(6, 2):
    tmp = A->data[6];
    A->data[6] = A->data[2];
    A->data[2] = tmp;

    pivot_row = 2;
    pivot_col = 2;
    A->rank += 1;
  }

  else if (fabs(A->data[7][2]) > EPSILON) {
    // swap rows(7, 2):
    tmp = A->data[7];
    A->data[7] = A->data[2];
    A->data[2] = tmp;

    pivot_row = 2;
    pivot_col = 2;
    A->rank += 1;
  }

  else if (fabs(A->data[8][2]) > EPSILON) {
    // swap rows(8, 2):
    tmp = A->data[8];
    A->data[8] = A->data[2];
    A->data[2] = tmp;

    pivot_row = 2;
    pivot_col = 2;
    A->rank += 1;
  }

  else if (fabs(A->data[9][2]) > EPSILON) {
    // swap rows(9, 2):
    tmp = A->data[9];
    A->data[9] = A->data[2];
    A->data[2] = tmp;

    pivot_row = 2;
    pivot_col = 2;
    A->rank += 1;
  }

  if (pivot_row != -1) {
    scalar = (-1) * A->data[3][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[3][0] += scalar * A->data[2][0];
    A->data[3][1] += scalar * A->data[2][1];
    A->data[3][2] += scalar * A->data[2][2];
    A->data[3][3] += scalar * A->data[2][3];
    A->data[3][4] += scalar * A->data[2][4];
    A->data[3][5] += scalar * A->data[2][5];
    A->data[3][6] += scalar * A->data[2][6];
    A->data[3][7] += scalar * A->data[2][7];
    A->data[3][8] += scalar * A->data[2][8];
    A->data[3][9] += scalar * A->data[2][9];
    A->data[3][10] += scalar * A->data[2][10];

    scalar = (-1) * A->data[4][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[4][0] += scalar * A->data[2][0];
    A->data[4][1] += scalar * A->data[2][1];
    A->data[4][2] += scalar * A->data[2][2];
    A->data[4][3] += scalar * A->data[2][3];
    A->data[4][4] += scalar * A->data[2][4];
    A->data[4][5] += scalar * A->data[2][5];
    A->data[4][6] += scalar * A->data[2][6];
    A->data[4][7] += scalar * A->data[2][7];
    A->data[4][8] += scalar * A->data[2][8];
    A->data[4][9] += scalar * A->data[2][9];
    A->data[4][10] += scalar * A->data[2][10];

    scalar = (-1) * A->data[5][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[5][0] += scalar * A->data[2][0];
    A->data[5][1] += scalar * A->data[2][1];
    A->data[5][2] += scalar * A->data[2][2];
    A->data[5][3] += scalar * A->data[2][3];
    A->data[5][4] += scalar * A->data[2][4];
    A->data[5][5] += scalar * A->data[2][5];
    A->data[5][6] += scalar * A->data[2][6];
    A->data[5][7] += scalar * A->data[2][7];
    A->data[5][8] += scalar * A->data[2][8];
    A->data[5][9] += scalar * A->data[2][9];
    A->data[5][10] += scalar * A->data[2][10];

    scalar = (-1) * A->data[6][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[6][0] += scalar * A->data[2][0];
    A->data[6][1] += scalar * A->data[2][1];
    A->data[6][2] += scalar * A->data[2][2];
    A->data[6][3] += scalar * A->data[2][3];
    A->data[6][4] += scalar * A->data[2][4];
    A->data[6][5] += scalar * A->data[2][5];
    A->data[6][6] += scalar * A->data[2][6];
    A->data[6][7] += scalar * A->data[2][7];
    A->data[6][8] += scalar * A->data[2][8];
    A->data[6][9] += scalar * A->data[2][9];
    A->data[6][10] += scalar * A->data[2][10];

    scalar = (-1) * A->data[7][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[7][0] += scalar * A->data[2][0];
    A->data[7][1] += scalar * A->data[2][1];
    A->data[7][2] += scalar * A->data[2][2];
    A->data[7][3] += scalar * A->data[2][3];
    A->data[7][4] += scalar * A->data[2][4];
    A->data[7][5] += scalar * A->data[2][5];
    A->data[7][6] += scalar * A->data[2][6];
    A->data[7][7] += scalar * A->data[2][7];
    A->data[7][8] += scalar * A->data[2][8];
    A->data[7][9] += scalar * A->data[2][9];
    A->data[7][10] += scalar * A->data[2][10];

    scalar = (-1) * A->data[8][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[8][0] += scalar * A->data[2][0];
    A->data[8][1] += scalar * A->data[2][1];
    A->data[8][2] += scalar * A->data[2][2];
    A->data[8][3] += scalar * A->data[2][3];
    A->data[8][4] += scalar * A->data[2][4];
    A->data[8][5] += scalar * A->data[2][5];
    A->data[8][6] += scalar * A->data[2][6];
    A->data[8][7] += scalar * A->data[2][7];
    A->data[8][8] += scalar * A->data[2][8];
    A->data[8][9] += scalar * A->data[2][9];
    A->data[8][10] += scalar * A->data[2][10];

    scalar = (-1) * A->data[9][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[9][0] += scalar * A->data[2][0];
    A->data[9][1] += scalar * A->data[2][1];
    A->data[9][2] += scalar * A->data[2][2];
    A->data[9][3] += scalar * A->data[2][3];
    A->data[9][4] += scalar * A->data[2][4];
    A->data[9][5] += scalar * A->data[2][5];
    A->data[9][6] += scalar * A->data[2][6];
    A->data[9][7] += scalar * A->data[2][7];
    A->data[9][8] += scalar * A->data[2][8];
    A->data[9][9] += scalar * A->data[2][9];
    A->data[9][10] += scalar * A->data[2][10];
  }

  pivot_row = -1;
  pivot_col = -1;

  if (fabs(A->data[3][3]) > EPSILON) {
    pivot_row = 3;
    pivot_col = 3;
    A->rank += 1;
  }

  else if (fabs(A->data[4][3]) > EPSILON) {
    // swap rows(4, 3):
    tmp = A->data[4];
    A->data[4] = A->data[3];
    A->data[3] = tmp;

    pivot_row = 3;
    pivot_col = 3;
    A->rank += 1;
  }

  else if (fabs(A->data[5][3]) > EPSILON) {
    // swap rows(5, 3):
    tmp = A->data[5];
    A->data[5] = A->data[3];
    A->data[3] = tmp;

    pivot_row = 3;
    pivot_col = 3;
    A->rank += 1;
  }

  else if (fabs(A->data[6][3]) > EPSILON) {
    // swap rows(6, 3):
    tmp = A->data[6];
    A->data[6] = A->data[3];
    A->data[3] = tmp;

    pivot_row = 3;
    pivot_col = 3;
    A->rank += 1;
  }

  else if (fabs(A->data[7][3]) > EPSILON) {
    // swap rows(7, 3):
    tmp = A->data[7];
    A->data[7] = A->data[3];
    A->data[3] = tmp;

    pivot_row = 3;
    pivot_col = 3;
    A->rank += 1;
  }

  else if (fabs(A->data[8][3]) > EPSILON) {
    // swap rows(8, 3):
    tmp = A->data[8];
    A->data[8] = A->data[3];
    A->data[3] = tmp;

    pivot_row = 3;
    pivot_col = 3;
    A->rank += 1;
  }

  else if (fabs(A->data[9][3]) > EPSILON) {
    // swap rows(9, 3):
    tmp = A->data[9];
    A->data[9] = A->data[3];
    A->data[3] = tmp;

    pivot_row = 3;
    pivot_col = 3;
    A->rank += 1;
  }

  if (pivot_row != -1) {
    scalar = (-1) * A->data[4][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[4][0] += scalar * A->data[3][0];
    A->data[4][1] += scalar * A->data[3][1];
    A->data[4][2] += scalar * A->data[3][2];
    A->data[4][3] += scalar * A->data[3][3];
    A->data[4][4] += scalar * A->data[3][4];
    A->data[4][5] += scalar * A->data[3][5];
    A->data[4][6] += scalar * A->data[3][6];
    A->data[4][7] += scalar * A->data[3][7];
    A->data[4][8] += scalar * A->data[3][8];
    A->data[4][9] += scalar * A->data[3][9];
    A->data[4][10] += scalar * A->data[3][10];

    scalar = (-1) * A->data[5][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[5][0] += scalar * A->data[3][0];
    A->data[5][1] += scalar * A->data[3][1];
    A->data[5][2] += scalar * A->data[3][2];
    A->data[5][3] += scalar * A->data[3][3];
    A->data[5][4] += scalar * A->data[3][4];
    A->data[5][5] += scalar * A->data[3][5];
    A->data[5][6] += scalar * A->data[3][6];
    A->data[5][7] += scalar * A->data[3][7];
    A->data[5][8] += scalar * A->data[3][8];
    A->data[5][9] += scalar * A->data[3][9];
    A->data[5][10] += scalar * A->data[3][10];

    scalar = (-1) * A->data[6][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[6][0] += scalar * A->data[3][0];
    A->data[6][1] += scalar * A->data[3][1];
    A->data[6][2] += scalar * A->data[3][2];
    A->data[6][3] += scalar * A->data[3][3];
    A->data[6][4] += scalar * A->data[3][4];
    A->data[6][5] += scalar * A->data[3][5];
    A->data[6][6] += scalar * A->data[3][6];
    A->data[6][7] += scalar * A->data[3][7];
    A->data[6][8] += scalar * A->data[3][8];
    A->data[6][9] += scalar * A->data[3][9];
    A->data[6][10] += scalar * A->data[3][10];

    scalar = (-1) * A->data[7][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[7][0] += scalar * A->data[3][0];
    A->data[7][1] += scalar * A->data[3][1];
    A->data[7][2] += scalar * A->data[3][2];
    A->data[7][3] += scalar * A->data[3][3];
    A->data[7][4] += scalar * A->data[3][4];
    A->data[7][5] += scalar * A->data[3][5];
    A->data[7][6] += scalar * A->data[3][6];
    A->data[7][7] += scalar * A->data[3][7];
    A->data[7][8] += scalar * A->data[3][8];
    A->data[7][9] += scalar * A->data[3][9];
    A->data[7][10] += scalar * A->data[3][10];

    scalar = (-1) * A->data[8][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[8][0] += scalar * A->data[3][0];
    A->data[8][1] += scalar * A->data[3][1];
    A->data[8][2] += scalar * A->data[3][2];
    A->data[8][3] += scalar * A->data[3][3];
    A->data[8][4] += scalar * A->data[3][4];
    A->data[8][5] += scalar * A->data[3][5];
    A->data[8][6] += scalar * A->data[3][6];
    A->data[8][7] += scalar * A->data[3][7];
    A->data[8][8] += scalar * A->data[3][8];
    A->data[8][9] += scalar * A->data[3][9];
    A->data[8][10] += scalar * A->data[3][10];

    scalar = (-1) * A->data[9][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[9][0] += scalar * A->data[3][0];
    A->data[9][1] += scalar * A->data[3][1];
    A->data[9][2] += scalar * A->data[3][2];
    A->data[9][3] += scalar * A->data[3][3];
    A->data[9][4] += scalar * A->data[3][4];
    A->data[9][5] += scalar * A->data[3][5];
    A->data[9][6] += scalar * A->data[3][6];
    A->data[9][7] += scalar * A->data[3][7];
    A->data[9][8] += scalar * A->data[3][8];
    A->data[9][9] += scalar * A->data[3][9];
    A->data[9][10] += scalar * A->data[3][10];
  }

  pivot_row = -1;
  pivot_col = -1;

  if (fabs(A->data[4][4]) > EPSILON) {
    pivot_row = 4;
    pivot_col = 4;
    A->rank += 1;
  }

  else if (fabs(A->data[5][4]) > EPSILON) {
    // swap rows(5, 4):
    tmp = A->data[5];
    A->data[5] = A->data[4];
    A->data[4] = tmp;

    pivot_row = 4;
    pivot_col = 4;
    A->rank += 1;
  }

  else if (fabs(A->data[6][4]) > EPSILON) {
    // swap rows(6, 4):
    tmp = A->data[6];
    A->data[6] = A->data[4];
    A->data[4] = tmp;

    pivot_row = 4;
    pivot_col = 4;
    A->rank += 1;
  }

  else if (fabs(A->data[7][4]) > EPSILON) {
    // swap rows(7, 4):
    tmp = A->data[7];
    A->data[7] = A->data[4];
    A->data[4] = tmp;

    pivot_row = 4;
    pivot_col = 4;
    A->rank += 1;
  }

  else if (fabs(A->data[8][4]) > EPSILON) {
    // swap rows(8, 4):
    tmp = A->data[8];
    A->data[8] = A->data[4];
    A->data[4] = tmp;

    pivot_row = 4;
    pivot_col = 4;
    A->rank += 1;
  }

  else if (fabs(A->data[9][4]) > EPSILON) {
    // swap rows(9, 4):
    tmp = A->data[9];
    A->data[9] = A->data[4];
    A->data[4] = tmp;

    pivot_row = 4;
    pivot_col = 4;
    A->rank += 1;
  }

  if (pivot_row != -1) {
    scalar = (-1) * A->data[5][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[5][0] += scalar * A->data[4][0];
    A->data[5][1] += scalar * A->data[4][1];
    A->data[5][2] += scalar * A->data[4][2];
    A->data[5][3] += scalar * A->data[4][3];
    A->data[5][4] += scalar * A->data[4][4];
    A->data[5][5] += scalar * A->data[4][5];
    A->data[5][6] += scalar * A->data[4][6];
    A->data[5][7] += scalar * A->data[4][7];
    A->data[5][8] += scalar * A->data[4][8];
    A->data[5][9] += scalar * A->data[4][9];
    A->data[5][10] += scalar * A->data[4][10];

    scalar = (-1) * A->data[6][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[6][0] += scalar * A->data[4][0];
    A->data[6][1] += scalar * A->data[4][1];
    A->data[6][2] += scalar * A->data[4][2];
    A->data[6][3] += scalar * A->data[4][3];
    A->data[6][4] += scalar * A->data[4][4];
    A->data[6][5] += scalar * A->data[4][5];
    A->data[6][6] += scalar * A->data[4][6];
    A->data[6][7] += scalar * A->data[4][7];
    A->data[6][8] += scalar * A->data[4][8];
    A->data[6][9] += scalar * A->data[4][9];
    A->data[6][10] += scalar * A->data[4][10];

    scalar = (-1) * A->data[7][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[7][0] += scalar * A->data[4][0];
    A->data[7][1] += scalar * A->data[4][1];
    A->data[7][2] += scalar * A->data[4][2];
    A->data[7][3] += scalar * A->data[4][3];
    A->data[7][4] += scalar * A->data[4][4];
    A->data[7][5] += scalar * A->data[4][5];
    A->data[7][6] += scalar * A->data[4][6];
    A->data[7][7] += scalar * A->data[4][7];
    A->data[7][8] += scalar * A->data[4][8];
    A->data[7][9] += scalar * A->data[4][9];
    A->data[7][10] += scalar * A->data[4][10];

    scalar = (-1) * A->data[8][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[8][0] += scalar * A->data[4][0];
    A->data[8][1] += scalar * A->data[4][1];
    A->data[8][2] += scalar * A->data[4][2];
    A->data[8][3] += scalar * A->data[4][3];
    A->data[8][4] += scalar * A->data[4][4];
    A->data[8][5] += scalar * A->data[4][5];
    A->data[8][6] += scalar * A->data[4][6];
    A->data[8][7] += scalar * A->data[4][7];
    A->data[8][8] += scalar * A->data[4][8];
    A->data[8][9] += scalar * A->data[4][9];
    A->data[8][10] += scalar * A->data[4][10];

    scalar = (-1) * A->data[9][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[9][0] += scalar * A->data[4][0];
    A->data[9][1] += scalar * A->data[4][1];
    A->data[9][2] += scalar * A->data[4][2];
    A->data[9][3] += scalar * A->data[4][3];
    A->data[9][4] += scalar * A->data[4][4];
    A->data[9][5] += scalar * A->data[4][5];
    A->data[9][6] += scalar * A->data[4][6];
    A->data[9][7] += scalar * A->data[4][7];
    A->data[9][8] += scalar * A->data[4][8];
    A->data[9][9] += scalar * A->data[4][9];
    A->data[9][10] += scalar * A->data[4][10];
  }

  pivot_row = -1;
  pivot_col = -1;

  if (fabs(A->data[5][5]) > EPSILON) {
    pivot_row = 5;
    pivot_col = 5;
    A->rank += 1;
  }

  else if (fabs(A->data[6][5]) > EPSILON) {
    // swap rows(6, 5):
    tmp = A->data[6];
    A->data[6] = A->data[5];
    A->data[5] = tmp;

    pivot_row = 5;
    pivot_col = 5;
    A->rank += 1;
  }

  else if (fabs(A->data[7][5]) > EPSILON) {
    // swap rows(7, 5):
    tmp = A->data[7];
    A->data[7] = A->data[5];
    A->data[5] = tmp;

    pivot_row = 5;
    pivot_col = 5;
    A->rank += 1;
  }

  else if (fabs(A->data[8][5]) > EPSILON) {
    // swap rows(8, 5):
    tmp = A->data[8];
    A->data[8] = A->data[5];
    A->data[5] = tmp;

    pivot_row = 5;
    pivot_col = 5;
    A->rank += 1;
  }

  else if (fabs(A->data[9][5]) > EPSILON) {
    // swap rows(9, 5):
    tmp = A->data[9];
    A->data[9] = A->data[5];
    A->data[5] = tmp;

    pivot_row = 5;
    pivot_col = 5;
    A->rank += 1;
  }

  if (pivot_row != -1) {
    scalar = (-1) * A->data[6][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[6][0] += scalar * A->data[5][0];
    A->data[6][1] += scalar * A->data[5][1];
    A->data[6][2] += scalar * A->data[5][2];
    A->data[6][3] += scalar * A->data[5][3];
    A->data[6][4] += scalar * A->data[5][4];
    A->data[6][5] += scalar * A->data[5][5];
    A->data[6][6] += scalar * A->data[5][6];
    A->data[6][7] += scalar * A->data[5][7];
    A->data[6][8] += scalar * A->data[5][8];
    A->data[6][9] += scalar * A->data[5][9];
    A->data[6][10] += scalar * A->data[5][10];

    scalar = (-1) * A->data[7][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[7][0] += scalar * A->data[5][0];
    A->data[7][1] += scalar * A->data[5][1];
    A->data[7][2] += scalar * A->data[5][2];
    A->data[7][3] += scalar * A->data[5][3];
    A->data[7][4] += scalar * A->data[5][4];
    A->data[7][5] += scalar * A->data[5][5];
    A->data[7][6] += scalar * A->data[5][6];
    A->data[7][7] += scalar * A->data[5][7];
    A->data[7][8] += scalar * A->data[5][8];
    A->data[7][9] += scalar * A->data[5][9];
    A->data[7][10] += scalar * A->data[5][10];

    scalar = (-1) * A->data[8][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[8][0] += scalar * A->data[5][0];
    A->data[8][1] += scalar * A->data[5][1];
    A->data[8][2] += scalar * A->data[5][2];
    A->data[8][3] += scalar * A->data[5][3];
    A->data[8][4] += scalar * A->data[5][4];
    A->data[8][5] += scalar * A->data[5][5];
    A->data[8][6] += scalar * A->data[5][6];
    A->data[8][7] += scalar * A->data[5][7];
    A->data[8][8] += scalar * A->data[5][8];
    A->data[8][9] += scalar * A->data[5][9];
    A->data[8][10] += scalar * A->data[5][10];

    scalar = (-1) * A->data[9][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[9][0] += scalar * A->data[5][0];
    A->data[9][1] += scalar * A->data[5][1];
    A->data[9][2] += scalar * A->data[5][2];
    A->data[9][3] += scalar * A->data[5][3];
    A->data[9][4] += scalar * A->data[5][4];
    A->data[9][5] += scalar * A->data[5][5];
    A->data[9][6] += scalar * A->data[5][6];
    A->data[9][7] += scalar * A->data[5][7];
    A->data[9][8] += scalar * A->data[5][8];
    A->data[9][9] += scalar * A->data[5][9];
    A->data[9][10] += scalar * A->data[5][10];
  }

  pivot_row = -1;
  pivot_col = -1;

  if (fabs(A->data[6][6]) > EPSILON) {
    pivot_row = 6;
    pivot_col = 6;
    A->rank += 1;
  }

  else if (fabs(A->data[7][6]) > EPSILON) {
    // swap rows(7, 6):
    tmp = A->data[7];
    A->data[7] = A->data[6];
    A->data[6] = tmp;

    pivot_row = 6;
    pivot_col = 6;
    A->rank += 1;
  }

  else if (fabs(A->data[8][6]) > EPSILON) {
    // swap rows(8, 6):
    tmp = A->data[8];
    A->data[8] = A->data[6];
    A->data[6] = tmp;

    pivot_row = 6;
    pivot_col = 6;
    A->rank += 1;
  }

  else if (fabs(A->data[9][6]) > EPSILON) {
    // swap rows(9, 6):
    tmp = A->data[9];
    A->data[9] = A->data[6];
    A->data[6] = tmp;

    pivot_row = 6;
    pivot_col = 6;
    A->rank += 1;
  }

  if (pivot_row != -1) {
    scalar = (-1) * A->data[7][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[7][0] += scalar * A->data[6][0];
    A->data[7][1] += scalar * A->data[6][1];
    A->data[7][2] += scalar * A->data[6][2];
    A->data[7][3] += scalar * A->data[6][3];
    A->data[7][4] += scalar * A->data[6][4];
    A->data[7][5] += scalar * A->data[6][5];
    A->data[7][6] += scalar * A->data[6][6];
    A->data[7][7] += scalar * A->data[6][7];
    A->data[7][8] += scalar * A->data[6][8];
    A->data[7][9] += scalar * A->data[6][9];
    A->data[7][10] += scalar * A->data[6][10];

    scalar = (-1) * A->data[8][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[8][0] += scalar * A->data[6][0];
    A->data[8][1] += scalar * A->data[6][1];
    A->data[8][2] += scalar * A->data[6][2];
    A->data[8][3] += scalar * A->data[6][3];
    A->data[8][4] += scalar * A->data[6][4];
    A->data[8][5] += scalar * A->data[6][5];
    A->data[8][6] += scalar * A->data[6][6];
    A->data[8][7] += scalar * A->data[6][7];
    A->data[8][8] += scalar * A->data[6][8];
    A->data[8][9] += scalar * A->data[6][9];
    A->data[8][10] += scalar * A->data[6][10];

    scalar = (-1) * A->data[9][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[9][0] += scalar * A->data[6][0];
    A->data[9][1] += scalar * A->data[6][1];
    A->data[9][2] += scalar * A->data[6][2];
    A->data[9][3] += scalar * A->data[6][3];
    A->data[9][4] += scalar * A->data[6][4];
    A->data[9][5] += scalar * A->data[6][5];
    A->data[9][6] += scalar * A->data[6][6];
    A->data[9][7] += scalar * A->data[6][7];
    A->data[9][8] += scalar * A->data[6][8];
    A->data[9][9] += scalar * A->data[6][9];
    A->data[9][10] += scalar * A->data[6][10];
  }

  pivot_row = -1;
  pivot_col = -1;

  if (fabs(A->data[7][7]) > EPSILON) {
    pivot_row = 7;
    pivot_col = 7;
    A->rank += 1;
  }

  else if (fabs(A->data[8][7]) > EPSILON) {
    // swap rows(8, 7):
    tmp = A->data[8];
    A->data[8] = A->data[7];
    A->data[7] = tmp;

    pivot_row = 7;
    pivot_col = 7;
    A->rank += 1;
  }

  else if (fabs(A->data[9][7]) > EPSILON) {
    // swap rows(9, 7):
    tmp = A->data[9];
    A->data[9] = A->data[7];
    A->data[7] = tmp;

    pivot_row = 7;
    pivot_col = 7;
    A->rank += 1;
  }

  if (pivot_row != -1) {
    scalar = (-1) * A->data[8][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[8][0] += scalar * A->data[7][0];
    A->data[8][1] += scalar * A->data[7][1];
    A->data[8][2] += scalar * A->data[7][2];
    A->data[8][3] += scalar * A->data[7][3];
    A->data[8][4] += scalar * A->data[7][4];
    A->data[8][5] += scalar * A->data[7][5];
    A->data[8][6] += scalar * A->data[7][6];
    A->data[8][7] += scalar * A->data[7][7];
    A->data[8][8] += scalar * A->data[7][8];
    A->data[8][9] += scalar * A->data[7][9];
    A->data[8][10] += scalar * A->data[7][10];

    scalar = (-1) * A->data[9][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[9][0] += scalar * A->data[7][0];
    A->data[9][1] += scalar * A->data[7][1];
    A->data[9][2] += scalar * A->data[7][2];
    A->data[9][3] += scalar * A->data[7][3];
    A->data[9][4] += scalar * A->data[7][4];
    A->data[9][5] += scalar * A->data[7][5];
    A->data[9][6] += scalar * A->data[7][6];
    A->data[9][7] += scalar * A->data[7][7];
    A->data[9][8] += scalar * A->data[7][8];
    A->data[9][9] += scalar * A->data[7][9];
    A->data[9][10] += scalar * A->data[7][10];
  }

  pivot_row = -1;
  pivot_col = -1;

  if (fabs(A->data[8][8]) > EPSILON) {
    pivot_row = 8;
    pivot_col = 8;
    A->rank += 1;
  }

  else if (fabs(A->data[9][8]) > EPSILON) {
    // swap rows(9, 8):
    tmp = A->data[9];
    A->data[9] = A->data[8];
    A->data[8] = tmp;

    pivot_row = 8;
    pivot_col = 8;
    A->rank += 1;
  }

  if (pivot_row != -1) {
    scalar = (-1) * A->data[9][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[9][0] += scalar * A->data[8][0];
    A->data[9][1] += scalar * A->data[8][1];
    A->data[9][2] += scalar * A->data[8][2];
    A->data[9][3] += scalar * A->data[8][3];
    A->data[9][4] += scalar * A->data[8][4];
    A->data[9][5] += scalar * A->data[8][5];
    A->data[9][6] += scalar * A->data[8][6];
    A->data[9][7] += scalar * A->data[8][7];
    A->data[9][8] += scalar * A->data[8][8];
    A->data[9][9] += scalar * A->data[8][9];
    A->data[9][10] += scalar * A->data[8][10];
  }

  pivot_row = -1;
  pivot_col = -1;

  if (fabs(A->data[9][9]) > EPSILON) {
    pivot_row = 9;
    pivot_col = 9;
    A->rank += 1;
  }

  pivot_row = 9;
  pivot_col = -1;
  if (fabs(A->data[9][9]) > EPSILON) {
    pivot_col = 9;
  }

  if (pivot_col != -1) {
    scalar = 1 / A->data[pivot_row][pivot_col];
    A->data[pivot_row][9] *= scalar;
    A->data[pivot_row][10] *= scalar;

    scalar = (-1) * A->data[8][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[8][8] += scalar * A->data[pivot_row][8];
    A->data[8][9] += scalar * A->data[pivot_row][9];
    A->data[8][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[7][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[7][7] += scalar * A->data[pivot_row][7];
    A->data[7][8] += scalar * A->data[pivot_row][8];
    A->data[7][9] += scalar * A->data[pivot_row][9];
    A->data[7][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[6][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[6][6] += scalar * A->data[pivot_row][6];
    A->data[6][7] += scalar * A->data[pivot_row][7];
    A->data[6][8] += scalar * A->data[pivot_row][8];
    A->data[6][9] += scalar * A->data[pivot_row][9];
    A->data[6][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[5][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[5][5] += scalar * A->data[pivot_row][5];
    A->data[5][6] += scalar * A->data[pivot_row][6];
    A->data[5][7] += scalar * A->data[pivot_row][7];
    A->data[5][8] += scalar * A->data[pivot_row][8];
    A->data[5][9] += scalar * A->data[pivot_row][9];
    A->data[5][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[4][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[4][4] += scalar * A->data[pivot_row][4];
    A->data[4][5] += scalar * A->data[pivot_row][5];
    A->data[4][6] += scalar * A->data[pivot_row][6];
    A->data[4][7] += scalar * A->data[pivot_row][7];
    A->data[4][8] += scalar * A->data[pivot_row][8];
    A->data[4][9] += scalar * A->data[pivot_row][9];
    A->data[4][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[3][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[3][3] += scalar * A->data[pivot_row][3];
    A->data[3][4] += scalar * A->data[pivot_row][4];
    A->data[3][5] += scalar * A->data[pivot_row][5];
    A->data[3][6] += scalar * A->data[pivot_row][6];
    A->data[3][7] += scalar * A->data[pivot_row][7];
    A->data[3][8] += scalar * A->data[pivot_row][8];
    A->data[3][9] += scalar * A->data[pivot_row][9];
    A->data[3][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[2][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[2][2] += scalar * A->data[pivot_row][2];
    A->data[2][3] += scalar * A->data[pivot_row][3];
    A->data[2][4] += scalar * A->data[pivot_row][4];
    A->data[2][5] += scalar * A->data[pivot_row][5];
    A->data[2][6] += scalar * A->data[pivot_row][6];
    A->data[2][7] += scalar * A->data[pivot_row][7];
    A->data[2][8] += scalar * A->data[pivot_row][8];
    A->data[2][9] += scalar * A->data[pivot_row][9];
    A->data[2][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[1][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[1][1] += scalar * A->data[pivot_row][1];
    A->data[1][2] += scalar * A->data[pivot_row][2];
    A->data[1][3] += scalar * A->data[pivot_row][3];
    A->data[1][4] += scalar * A->data[pivot_row][4];
    A->data[1][5] += scalar * A->data[pivot_row][5];
    A->data[1][6] += scalar * A->data[pivot_row][6];
    A->data[1][7] += scalar * A->data[pivot_row][7];
    A->data[1][8] += scalar * A->data[pivot_row][8];
    A->data[1][9] += scalar * A->data[pivot_row][9];
    A->data[1][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[0][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[0][0] += scalar * A->data[pivot_row][0];
    A->data[0][1] += scalar * A->data[pivot_row][1];
    A->data[0][2] += scalar * A->data[pivot_row][2];
    A->data[0][3] += scalar * A->data[pivot_row][3];
    A->data[0][4] += scalar * A->data[pivot_row][4];
    A->data[0][5] += scalar * A->data[pivot_row][5];
    A->data[0][6] += scalar * A->data[pivot_row][6];
    A->data[0][7] += scalar * A->data[pivot_row][7];
    A->data[0][8] += scalar * A->data[pivot_row][8];
    A->data[0][9] += scalar * A->data[pivot_row][9];
    A->data[0][10] += scalar * A->data[pivot_row][10];

  }
  pivot_row = 8;
  pivot_col = -1;
  if (fabs(A->data[8][8]) > EPSILON) {
    pivot_col = 8;
  }

  else if (fabs(A->data[8][9]) > EPSILON) {
    pivot_col = 9;
  }

  if (pivot_col != -1) {
    scalar = 1 / A->data[pivot_row][pivot_col];
    A->data[pivot_row][8] *= scalar;
    A->data[pivot_row][9] *= scalar;
    A->data[pivot_row][10] *= scalar;

    scalar = (-1) * A->data[7][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[7][7] += scalar * A->data[pivot_row][7];
    A->data[7][8] += scalar * A->data[pivot_row][8];
    A->data[7][9] += scalar * A->data[pivot_row][9];
    A->data[7][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[6][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[6][6] += scalar * A->data[pivot_row][6];
    A->data[6][7] += scalar * A->data[pivot_row][7];
    A->data[6][8] += scalar * A->data[pivot_row][8];
    A->data[6][9] += scalar * A->data[pivot_row][9];
    A->data[6][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[5][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[5][5] += scalar * A->data[pivot_row][5];
    A->data[5][6] += scalar * A->data[pivot_row][6];
    A->data[5][7] += scalar * A->data[pivot_row][7];
    A->data[5][8] += scalar * A->data[pivot_row][8];
    A->data[5][9] += scalar * A->data[pivot_row][9];
    A->data[5][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[4][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[4][4] += scalar * A->data[pivot_row][4];
    A->data[4][5] += scalar * A->data[pivot_row][5];
    A->data[4][6] += scalar * A->data[pivot_row][6];
    A->data[4][7] += scalar * A->data[pivot_row][7];
    A->data[4][8] += scalar * A->data[pivot_row][8];
    A->data[4][9] += scalar * A->data[pivot_row][9];
    A->data[4][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[3][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[3][3] += scalar * A->data[pivot_row][3];
    A->data[3][4] += scalar * A->data[pivot_row][4];
    A->data[3][5] += scalar * A->data[pivot_row][5];
    A->data[3][6] += scalar * A->data[pivot_row][6];
    A->data[3][7] += scalar * A->data[pivot_row][7];
    A->data[3][8] += scalar * A->data[pivot_row][8];
    A->data[3][9] += scalar * A->data[pivot_row][9];
    A->data[3][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[2][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[2][2] += scalar * A->data[pivot_row][2];
    A->data[2][3] += scalar * A->data[pivot_row][3];
    A->data[2][4] += scalar * A->data[pivot_row][4];
    A->data[2][5] += scalar * A->data[pivot_row][5];
    A->data[2][6] += scalar * A->data[pivot_row][6];
    A->data[2][7] += scalar * A->data[pivot_row][7];
    A->data[2][8] += scalar * A->data[pivot_row][8];
    A->data[2][9] += scalar * A->data[pivot_row][9];
    A->data[2][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[1][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[1][1] += scalar * A->data[pivot_row][1];
    A->data[1][2] += scalar * A->data[pivot_row][2];
    A->data[1][3] += scalar * A->data[pivot_row][3];
    A->data[1][4] += scalar * A->data[pivot_row][4];
    A->data[1][5] += scalar * A->data[pivot_row][5];
    A->data[1][6] += scalar * A->data[pivot_row][6];
    A->data[1][7] += scalar * A->data[pivot_row][7];
    A->data[1][8] += scalar * A->data[pivot_row][8];
    A->data[1][9] += scalar * A->data[pivot_row][9];
    A->data[1][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[0][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[0][0] += scalar * A->data[pivot_row][0];
    A->data[0][1] += scalar * A->data[pivot_row][1];
    A->data[0][2] += scalar * A->data[pivot_row][2];
    A->data[0][3] += scalar * A->data[pivot_row][3];
    A->data[0][4] += scalar * A->data[pivot_row][4];
    A->data[0][5] += scalar * A->data[pivot_row][5];
    A->data[0][6] += scalar * A->data[pivot_row][6];
    A->data[0][7] += scalar * A->data[pivot_row][7];
    A->data[0][8] += scalar * A->data[pivot_row][8];
    A->data[0][9] += scalar * A->data[pivot_row][9];
    A->data[0][10] += scalar * A->data[pivot_row][10];

  }
  pivot_row = 7;
  pivot_col = -1;
  if (fabs(A->data[7][7]) > EPSILON) {
    pivot_col = 7;
  }

  else if (fabs(A->data[7][8]) > EPSILON) {
    pivot_col = 8;
  }

  else if (fabs(A->data[7][9]) > EPSILON) {
    pivot_col = 9;
  }

  if (pivot_col != -1) {
    scalar = 1 / A->data[pivot_row][pivot_col];
    A->data[pivot_row][7] *= scalar;
    A->data[pivot_row][8] *= scalar;
    A->data[pivot_row][9] *= scalar;
    A->data[pivot_row][10] *= scalar;

    scalar = (-1) * A->data[6][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[6][6] += scalar * A->data[pivot_row][6];
    A->data[6][7] += scalar * A->data[pivot_row][7];
    A->data[6][8] += scalar * A->data[pivot_row][8];
    A->data[6][9] += scalar * A->data[pivot_row][9];
    A->data[6][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[5][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[5][5] += scalar * A->data[pivot_row][5];
    A->data[5][6] += scalar * A->data[pivot_row][6];
    A->data[5][7] += scalar * A->data[pivot_row][7];
    A->data[5][8] += scalar * A->data[pivot_row][8];
    A->data[5][9] += scalar * A->data[pivot_row][9];
    A->data[5][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[4][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[4][4] += scalar * A->data[pivot_row][4];
    A->data[4][5] += scalar * A->data[pivot_row][5];
    A->data[4][6] += scalar * A->data[pivot_row][6];
    A->data[4][7] += scalar * A->data[pivot_row][7];
    A->data[4][8] += scalar * A->data[pivot_row][8];
    A->data[4][9] += scalar * A->data[pivot_row][9];
    A->data[4][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[3][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[3][3] += scalar * A->data[pivot_row][3];
    A->data[3][4] += scalar * A->data[pivot_row][4];
    A->data[3][5] += scalar * A->data[pivot_row][5];
    A->data[3][6] += scalar * A->data[pivot_row][6];
    A->data[3][7] += scalar * A->data[pivot_row][7];
    A->data[3][8] += scalar * A->data[pivot_row][8];
    A->data[3][9] += scalar * A->data[pivot_row][9];
    A->data[3][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[2][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[2][2] += scalar * A->data[pivot_row][2];
    A->data[2][3] += scalar * A->data[pivot_row][3];
    A->data[2][4] += scalar * A->data[pivot_row][4];
    A->data[2][5] += scalar * A->data[pivot_row][5];
    A->data[2][6] += scalar * A->data[pivot_row][6];
    A->data[2][7] += scalar * A->data[pivot_row][7];
    A->data[2][8] += scalar * A->data[pivot_row][8];
    A->data[2][9] += scalar * A->data[pivot_row][9];
    A->data[2][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[1][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[1][1] += scalar * A->data[pivot_row][1];
    A->data[1][2] += scalar * A->data[pivot_row][2];
    A->data[1][3] += scalar * A->data[pivot_row][3];
    A->data[1][4] += scalar * A->data[pivot_row][4];
    A->data[1][5] += scalar * A->data[pivot_row][5];
    A->data[1][6] += scalar * A->data[pivot_row][6];
    A->data[1][7] += scalar * A->data[pivot_row][7];
    A->data[1][8] += scalar * A->data[pivot_row][8];
    A->data[1][9] += scalar * A->data[pivot_row][9];
    A->data[1][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[0][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[0][0] += scalar * A->data[pivot_row][0];
    A->data[0][1] += scalar * A->data[pivot_row][1];
    A->data[0][2] += scalar * A->data[pivot_row][2];
    A->data[0][3] += scalar * A->data[pivot_row][3];
    A->data[0][4] += scalar * A->data[pivot_row][4];
    A->data[0][5] += scalar * A->data[pivot_row][5];
    A->data[0][6] += scalar * A->data[pivot_row][6];
    A->data[0][7] += scalar * A->data[pivot_row][7];
    A->data[0][8] += scalar * A->data[pivot_row][8];
    A->data[0][9] += scalar * A->data[pivot_row][9];
    A->data[0][10] += scalar * A->data[pivot_row][10];

  }
  pivot_row = 6;
  pivot_col = -1;
  if (fabs(A->data[6][6]) > EPSILON) {
    pivot_col = 6;
  }

  else if (fabs(A->data[6][7]) > EPSILON) {
    pivot_col = 7;
  }

  else if (fabs(A->data[6][8]) > EPSILON) {
    pivot_col = 8;
  }

  else if (fabs(A->data[6][9]) > EPSILON) {
    pivot_col = 9;
  }

  if (pivot_col != -1) {
    scalar = 1 / A->data[pivot_row][pivot_col];
    A->data[pivot_row][6] *= scalar;
    A->data[pivot_row][7] *= scalar;
    A->data[pivot_row][8] *= scalar;
    A->data[pivot_row][9] *= scalar;
    A->data[pivot_row][10] *= scalar;

    scalar = (-1) * A->data[5][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[5][5] += scalar * A->data[pivot_row][5];
    A->data[5][6] += scalar * A->data[pivot_row][6];
    A->data[5][7] += scalar * A->data[pivot_row][7];
    A->data[5][8] += scalar * A->data[pivot_row][8];
    A->data[5][9] += scalar * A->data[pivot_row][9];
    A->data[5][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[4][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[4][4] += scalar * A->data[pivot_row][4];
    A->data[4][5] += scalar * A->data[pivot_row][5];
    A->data[4][6] += scalar * A->data[pivot_row][6];
    A->data[4][7] += scalar * A->data[pivot_row][7];
    A->data[4][8] += scalar * A->data[pivot_row][8];
    A->data[4][9] += scalar * A->data[pivot_row][9];
    A->data[4][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[3][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[3][3] += scalar * A->data[pivot_row][3];
    A->data[3][4] += scalar * A->data[pivot_row][4];
    A->data[3][5] += scalar * A->data[pivot_row][5];
    A->data[3][6] += scalar * A->data[pivot_row][6];
    A->data[3][7] += scalar * A->data[pivot_row][7];
    A->data[3][8] += scalar * A->data[pivot_row][8];
    A->data[3][9] += scalar * A->data[pivot_row][9];
    A->data[3][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[2][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[2][2] += scalar * A->data[pivot_row][2];
    A->data[2][3] += scalar * A->data[pivot_row][3];
    A->data[2][4] += scalar * A->data[pivot_row][4];
    A->data[2][5] += scalar * A->data[pivot_row][5];
    A->data[2][6] += scalar * A->data[pivot_row][6];
    A->data[2][7] += scalar * A->data[pivot_row][7];
    A->data[2][8] += scalar * A->data[pivot_row][8];
    A->data[2][9] += scalar * A->data[pivot_row][9];
    A->data[2][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[1][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[1][1] += scalar * A->data[pivot_row][1];
    A->data[1][2] += scalar * A->data[pivot_row][2];
    A->data[1][3] += scalar * A->data[pivot_row][3];
    A->data[1][4] += scalar * A->data[pivot_row][4];
    A->data[1][5] += scalar * A->data[pivot_row][5];
    A->data[1][6] += scalar * A->data[pivot_row][6];
    A->data[1][7] += scalar * A->data[pivot_row][7];
    A->data[1][8] += scalar * A->data[pivot_row][8];
    A->data[1][9] += scalar * A->data[pivot_row][9];
    A->data[1][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[0][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[0][0] += scalar * A->data[pivot_row][0];
    A->data[0][1] += scalar * A->data[pivot_row][1];
    A->data[0][2] += scalar * A->data[pivot_row][2];
    A->data[0][3] += scalar * A->data[pivot_row][3];
    A->data[0][4] += scalar * A->data[pivot_row][4];
    A->data[0][5] += scalar * A->data[pivot_row][5];
    A->data[0][6] += scalar * A->data[pivot_row][6];
    A->data[0][7] += scalar * A->data[pivot_row][7];
    A->data[0][8] += scalar * A->data[pivot_row][8];
    A->data[0][9] += scalar * A->data[pivot_row][9];
    A->data[0][10] += scalar * A->data[pivot_row][10];

  }
  pivot_row = 5;
  pivot_col = -1;
  if (fabs(A->data[5][5]) > EPSILON) {
    pivot_col = 5;
  }

  else if (fabs(A->data[5][6]) > EPSILON) {
    pivot_col = 6;
  }

  else if (fabs(A->data[5][7]) > EPSILON) {
    pivot_col = 7;
  }

  else if (fabs(A->data[5][8]) > EPSILON) {
    pivot_col = 8;
  }

  else if (fabs(A->data[5][9]) > EPSILON) {
    pivot_col = 9;
  }

  if (pivot_col != -1) {
    scalar = 1 / A->data[pivot_row][pivot_col];
    A->data[pivot_row][5] *= scalar;
    A->data[pivot_row][6] *= scalar;
    A->data[pivot_row][7] *= scalar;
    A->data[pivot_row][8] *= scalar;
    A->data[pivot_row][9] *= scalar;
    A->data[pivot_row][10] *= scalar;

    scalar = (-1) * A->data[4][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[4][4] += scalar * A->data[pivot_row][4];
    A->data[4][5] += scalar * A->data[pivot_row][5];
    A->data[4][6] += scalar * A->data[pivot_row][6];
    A->data[4][7] += scalar * A->data[pivot_row][7];
    A->data[4][8] += scalar * A->data[pivot_row][8];
    A->data[4][9] += scalar * A->data[pivot_row][9];
    A->data[4][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[3][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[3][3] += scalar * A->data[pivot_row][3];
    A->data[3][4] += scalar * A->data[pivot_row][4];
    A->data[3][5] += scalar * A->data[pivot_row][5];
    A->data[3][6] += scalar * A->data[pivot_row][6];
    A->data[3][7] += scalar * A->data[pivot_row][7];
    A->data[3][8] += scalar * A->data[pivot_row][8];
    A->data[3][9] += scalar * A->data[pivot_row][9];
    A->data[3][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[2][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[2][2] += scalar * A->data[pivot_row][2];
    A->data[2][3] += scalar * A->data[pivot_row][3];
    A->data[2][4] += scalar * A->data[pivot_row][4];
    A->data[2][5] += scalar * A->data[pivot_row][5];
    A->data[2][6] += scalar * A->data[pivot_row][6];
    A->data[2][7] += scalar * A->data[pivot_row][7];
    A->data[2][8] += scalar * A->data[pivot_row][8];
    A->data[2][9] += scalar * A->data[pivot_row][9];
    A->data[2][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[1][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[1][1] += scalar * A->data[pivot_row][1];
    A->data[1][2] += scalar * A->data[pivot_row][2];
    A->data[1][3] += scalar * A->data[pivot_row][3];
    A->data[1][4] += scalar * A->data[pivot_row][4];
    A->data[1][5] += scalar * A->data[pivot_row][5];
    A->data[1][6] += scalar * A->data[pivot_row][6];
    A->data[1][7] += scalar * A->data[pivot_row][7];
    A->data[1][8] += scalar * A->data[pivot_row][8];
    A->data[1][9] += scalar * A->data[pivot_row][9];
    A->data[1][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[0][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[0][0] += scalar * A->data[pivot_row][0];
    A->data[0][1] += scalar * A->data[pivot_row][1];
    A->data[0][2] += scalar * A->data[pivot_row][2];
    A->data[0][3] += scalar * A->data[pivot_row][3];
    A->data[0][4] += scalar * A->data[pivot_row][4];
    A->data[0][5] += scalar * A->data[pivot_row][5];
    A->data[0][6] += scalar * A->data[pivot_row][6];
    A->data[0][7] += scalar * A->data[pivot_row][7];
    A->data[0][8] += scalar * A->data[pivot_row][8];
    A->data[0][9] += scalar * A->data[pivot_row][9];
    A->data[0][10] += scalar * A->data[pivot_row][10];

  }
  pivot_row = 4;
  pivot_col = -1;
  if (fabs(A->data[4][4]) > EPSILON) {
    pivot_col = 4;
  }

  else if (fabs(A->data[4][5]) > EPSILON) {
    pivot_col = 5;
  }

  else if (fabs(A->data[4][6]) > EPSILON) {
    pivot_col = 6;
  }

  else if (fabs(A->data[4][7]) > EPSILON) {
    pivot_col = 7;
  }

  else if (fabs(A->data[4][8]) > EPSILON) {
    pivot_col = 8;
  }

  else if (fabs(A->data[4][9]) > EPSILON) {
    pivot_col = 9;
  }

  if (pivot_col != -1) {
    scalar = 1 / A->data[pivot_row][pivot_col];
    A->data[pivot_row][4] *= scalar;
    A->data[pivot_row][5] *= scalar;
    A->data[pivot_row][6] *= scalar;
    A->data[pivot_row][7] *= scalar;
    A->data[pivot_row][8] *= scalar;
    A->data[pivot_row][9] *= scalar;
    A->data[pivot_row][10] *= scalar;

    scalar = (-1) * A->data[3][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[3][3] += scalar * A->data[pivot_row][3];
    A->data[3][4] += scalar * A->data[pivot_row][4];
    A->data[3][5] += scalar * A->data[pivot_row][5];
    A->data[3][6] += scalar * A->data[pivot_row][6];
    A->data[3][7] += scalar * A->data[pivot_row][7];
    A->data[3][8] += scalar * A->data[pivot_row][8];
    A->data[3][9] += scalar * A->data[pivot_row][9];
    A->data[3][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[2][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[2][2] += scalar * A->data[pivot_row][2];
    A->data[2][3] += scalar * A->data[pivot_row][3];
    A->data[2][4] += scalar * A->data[pivot_row][4];
    A->data[2][5] += scalar * A->data[pivot_row][5];
    A->data[2][6] += scalar * A->data[pivot_row][6];
    A->data[2][7] += scalar * A->data[pivot_row][7];
    A->data[2][8] += scalar * A->data[pivot_row][8];
    A->data[2][9] += scalar * A->data[pivot_row][9];
    A->data[2][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[1][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[1][1] += scalar * A->data[pivot_row][1];
    A->data[1][2] += scalar * A->data[pivot_row][2];
    A->data[1][3] += scalar * A->data[pivot_row][3];
    A->data[1][4] += scalar * A->data[pivot_row][4];
    A->data[1][5] += scalar * A->data[pivot_row][5];
    A->data[1][6] += scalar * A->data[pivot_row][6];
    A->data[1][7] += scalar * A->data[pivot_row][7];
    A->data[1][8] += scalar * A->data[pivot_row][8];
    A->data[1][9] += scalar * A->data[pivot_row][9];
    A->data[1][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[0][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[0][0] += scalar * A->data[pivot_row][0];
    A->data[0][1] += scalar * A->data[pivot_row][1];
    A->data[0][2] += scalar * A->data[pivot_row][2];
    A->data[0][3] += scalar * A->data[pivot_row][3];
    A->data[0][4] += scalar * A->data[pivot_row][4];
    A->data[0][5] += scalar * A->data[pivot_row][5];
    A->data[0][6] += scalar * A->data[pivot_row][6];
    A->data[0][7] += scalar * A->data[pivot_row][7];
    A->data[0][8] += scalar * A->data[pivot_row][8];
    A->data[0][9] += scalar * A->data[pivot_row][9];
    A->data[0][10] += scalar * A->data[pivot_row][10];

  }
  pivot_row = 3;
  pivot_col = -1;
  if (fabs(A->data[3][3]) > EPSILON) {
    pivot_col = 3;
  }

  else if (fabs(A->data[3][4]) > EPSILON) {
    pivot_col = 4;
  }

  else if (fabs(A->data[3][5]) > EPSILON) {
    pivot_col = 5;
  }

  else if (fabs(A->data[3][6]) > EPSILON) {
    pivot_col = 6;
  }

  else if (fabs(A->data[3][7]) > EPSILON) {
    pivot_col = 7;
  }

  else if (fabs(A->data[3][8]) > EPSILON) {
    pivot_col = 8;
  }

  else if (fabs(A->data[3][9]) > EPSILON) {
    pivot_col = 9;
  }

  if (pivot_col != -1) {
    scalar = 1 / A->data[pivot_row][pivot_col];
    A->data[pivot_row][3] *= scalar;
    A->data[pivot_row][4] *= scalar;
    A->data[pivot_row][5] *= scalar;
    A->data[pivot_row][6] *= scalar;
    A->data[pivot_row][7] *= scalar;
    A->data[pivot_row][8] *= scalar;
    A->data[pivot_row][9] *= scalar;
    A->data[pivot_row][10] *= scalar;

    scalar = (-1) * A->data[2][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[2][2] += scalar * A->data[pivot_row][2];
    A->data[2][3] += scalar * A->data[pivot_row][3];
    A->data[2][4] += scalar * A->data[pivot_row][4];
    A->data[2][5] += scalar * A->data[pivot_row][5];
    A->data[2][6] += scalar * A->data[pivot_row][6];
    A->data[2][7] += scalar * A->data[pivot_row][7];
    A->data[2][8] += scalar * A->data[pivot_row][8];
    A->data[2][9] += scalar * A->data[pivot_row][9];
    A->data[2][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[1][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[1][1] += scalar * A->data[pivot_row][1];
    A->data[1][2] += scalar * A->data[pivot_row][2];
    A->data[1][3] += scalar * A->data[pivot_row][3];
    A->data[1][4] += scalar * A->data[pivot_row][4];
    A->data[1][5] += scalar * A->data[pivot_row][5];
    A->data[1][6] += scalar * A->data[pivot_row][6];
    A->data[1][7] += scalar * A->data[pivot_row][7];
    A->data[1][8] += scalar * A->data[pivot_row][8];
    A->data[1][9] += scalar * A->data[pivot_row][9];
    A->data[1][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[0][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[0][0] += scalar * A->data[pivot_row][0];
    A->data[0][1] += scalar * A->data[pivot_row][1];
    A->data[0][2] += scalar * A->data[pivot_row][2];
    A->data[0][3] += scalar * A->data[pivot_row][3];
    A->data[0][4] += scalar * A->data[pivot_row][4];
    A->data[0][5] += scalar * A->data[pivot_row][5];
    A->data[0][6] += scalar * A->data[pivot_row][6];
    A->data[0][7] += scalar * A->data[pivot_row][7];
    A->data[0][8] += scalar * A->data[pivot_row][8];
    A->data[0][9] += scalar * A->data[pivot_row][9];
    A->data[0][10] += scalar * A->data[pivot_row][10];

  }
  pivot_row = 2;
  pivot_col = -1;
  if (fabs(A->data[2][2]) > EPSILON) {
    pivot_col = 2;
  }

  else if (fabs(A->data[2][3]) > EPSILON) {
    pivot_col = 3;
  }

  else if (fabs(A->data[2][4]) > EPSILON) {
    pivot_col = 4;
  }

  else if (fabs(A->data[2][5]) > EPSILON) {
    pivot_col = 5;
  }

  else if (fabs(A->data[2][6]) > EPSILON) {
    pivot_col = 6;
  }

  else if (fabs(A->data[2][7]) > EPSILON) {
    pivot_col = 7;
  }

  else if (fabs(A->data[2][8]) > EPSILON) {
    pivot_col = 8;
  }

  else if (fabs(A->data[2][9]) > EPSILON) {
    pivot_col = 9;
  }

  if (pivot_col != -1) {
    scalar = 1 / A->data[pivot_row][pivot_col];
    A->data[pivot_row][2] *= scalar;
    A->data[pivot_row][3] *= scalar;
    A->data[pivot_row][4] *= scalar;
    A->data[pivot_row][5] *= scalar;
    A->data[pivot_row][6] *= scalar;
    A->data[pivot_row][7] *= scalar;
    A->data[pivot_row][8] *= scalar;
    A->data[pivot_row][9] *= scalar;
    A->data[pivot_row][10] *= scalar;

    scalar = (-1) * A->data[1][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[1][1] += scalar * A->data[pivot_row][1];
    A->data[1][2] += scalar * A->data[pivot_row][2];
    A->data[1][3] += scalar * A->data[pivot_row][3];
    A->data[1][4] += scalar * A->data[pivot_row][4];
    A->data[1][5] += scalar * A->data[pivot_row][5];
    A->data[1][6] += scalar * A->data[pivot_row][6];
    A->data[1][7] += scalar * A->data[pivot_row][7];
    A->data[1][8] += scalar * A->data[pivot_row][8];
    A->data[1][9] += scalar * A->data[pivot_row][9];
    A->data[1][10] += scalar * A->data[pivot_row][10];

    scalar = (-1) * A->data[0][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[0][0] += scalar * A->data[pivot_row][0];
    A->data[0][1] += scalar * A->data[pivot_row][1];
    A->data[0][2] += scalar * A->data[pivot_row][2];
    A->data[0][3] += scalar * A->data[pivot_row][3];
    A->data[0][4] += scalar * A->data[pivot_row][4];
    A->data[0][5] += scalar * A->data[pivot_row][5];
    A->data[0][6] += scalar * A->data[pivot_row][6];
    A->data[0][7] += scalar * A->data[pivot_row][7];
    A->data[0][8] += scalar * A->data[pivot_row][8];
    A->data[0][9] += scalar * A->data[pivot_row][9];
    A->data[0][10] += scalar * A->data[pivot_row][10];

  }
  pivot_row = 1;
  pivot_col = -1;
  if (fabs(A->data[1][1]) > EPSILON) {
    pivot_col = 1;
  }

  else if (fabs(A->data[1][2]) > EPSILON) {
    pivot_col = 2;
  }

  else if (fabs(A->data[1][3]) > EPSILON) {
    pivot_col = 3;
  }

  else if (fabs(A->data[1][4]) > EPSILON) {
    pivot_col = 4;
  }

  else if (fabs(A->data[1][5]) > EPSILON) {
    pivot_col = 5;
  }

  else if (fabs(A->data[1][6]) > EPSILON) {
    pivot_col = 6;
  }

  else if (fabs(A->data[1][7]) > EPSILON) {
    pivot_col = 7;
  }

  else if (fabs(A->data[1][8]) > EPSILON) {
    pivot_col = 8;
  }

  else if (fabs(A->data[1][9]) > EPSILON) {
    pivot_col = 9;
  }

  if (pivot_col != -1) {
    scalar = 1 / A->data[pivot_row][pivot_col];
    A->data[pivot_row][1] *= scalar;
    A->data[pivot_row][2] *= scalar;
    A->data[pivot_row][3] *= scalar;
    A->data[pivot_row][4] *= scalar;
    A->data[pivot_row][5] *= scalar;
    A->data[pivot_row][6] *= scalar;
    A->data[pivot_row][7] *= scalar;
    A->data[pivot_row][8] *= scalar;
    A->data[pivot_row][9] *= scalar;
    A->data[pivot_row][10] *= scalar;

    scalar = (-1) * A->data[0][pivot_col] / A->data[pivot_row][pivot_col];
    A->data[0][0] += scalar * A->data[pivot_row][0];
    A->data[0][1] += scalar * A->data[pivot_row][1];
    A->data[0][2] += scalar * A->data[pivot_row][2];
    A->data[0][3] += scalar * A->data[pivot_row][3];
    A->data[0][4] += scalar * A->data[pivot_row][4];
    A->data[0][5] += scalar * A->data[pivot_row][5];
    A->data[0][6] += scalar * A->data[pivot_row][6];
    A->data[0][7] += scalar * A->data[pivot_row][7];
    A->data[0][8] += scalar * A->data[pivot_row][8];
    A->data[0][9] += scalar * A->data[pivot_row][9];
    A->data[0][10] += scalar * A->data[pivot_row][10];

  }
  pivot_row = 0;
  pivot_col = -1;
  if (fabs(A->data[0][0]) > EPSILON) {
    pivot_col = 0;
  }

  else if (fabs(A->data[0][1]) > EPSILON) {
    pivot_col = 1;
  }

  else if (fabs(A->data[0][2]) > EPSILON) {
    pivot_col = 2;
  }

  else if (fabs(A->data[0][3]) > EPSILON) {
    pivot_col = 3;
  }

  else if (fabs(A->data[0][4]) > EPSILON) {
    pivot_col = 4;
  }

  else if (fabs(A->data[0][5]) > EPSILON) {
    pivot_col = 5;
  }

  else if (fabs(A->data[0][6]) > EPSILON) {
    pivot_col = 6;
  }

  else if (fabs(A->data[0][7]) > EPSILON) {
    pivot_col = 7;
  }

  else if (fabs(A->data[0][8]) > EPSILON) {
    pivot_col = 8;
  }

  else if (fabs(A->data[0][9]) > EPSILON) {
    pivot_col = 9;
  }

  if (pivot_col != -1) {
    scalar = 1 / A->data[pivot_row][pivot_col];
    A->data[pivot_row][0] *= scalar;
    A->data[pivot_row][1] *= scalar;
    A->data[pivot_row][2] *= scalar;
    A->data[pivot_row][3] *= scalar;
    A->data[pivot_row][4] *= scalar;
    A->data[pivot_row][5] *= scalar;
    A->data[pivot_row][6] *= scalar;
    A->data[pivot_row][7] *= scalar;
    A->data[pivot_row][8] *= scalar;
    A->data[pivot_row][9] *= scalar;
    A->data[pivot_row][10] *= scalar;

  }
}

/*
                                      ▓▓▓▓              ████                                            
                                      ██▓▓▓▓          ▓▓▓▓██                                            
                                      ██▓▓▒▒██      ██▓▓▒▒██                                            
                                      ██▓▓▓▓▓▓██████▓▓▓▓▒▒██                                            
                              ██▓▓    ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██    ▓▓▓▓                                    
                              ░░░░██  ██▓▓▓▓░░▓▓▓▓▓▓░░▓▓▒▒██  ▓▓░░░░                                    
                                  ░░  ██▓▓▓▓  ▓▓▓▓██  ▓▓▒▒██  ░░                                        
                              ██████  ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██  ██████                                    
                                        ██▓▓▓▓▓▓▓▓▓▓▓▓▒▒██              ██▓▓              ▓▓██          
                                        ░░██████████████░░              ██▓▓▓▓          ▓▓▓▓██          
                            ██████      ██▓▓▓▓▓▓▓▓▓▓▒▒▒▒██              ██▓▓▒▒██      ██▓▓▒▒██          
                          ██▓▓▓▓██    ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██              ██▓▓▓▓▓▓██████▓▓▓▓▒▒██          
                          ██▓▓██      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██      ████    ██▓▓▓▓██▓▓▓▓▓▓▓▓▓▓▒▒██    ████  
                          ██▓▓██    ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██          ██  ██▓▓██  ▓▓▓▓▓▓  ▓▓▒▒██  ██      
                          ██▓▓██  ██▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▒▒██              ██▓▓██  ▓▓▓▓▓▓  ▓▓▒▒██          
                          ██▓▓██    ██▓▓▓▓▓▓▒▒▒▒▒▒▓▓▓▓▒▒██      ██████  ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██  ██████  
                          ██▓▓██    ██▓▓▓▓▓▓▓▓▒▒▒▒▒▒██▒▒██                ██▓▓▓▓▓▓▓▓▓▓▓▓▒▒██            
                            ██▓▓▓▓  ██▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▓▓██            ▓▓▓▓██████████████████            
                            ██▓▓██  ██▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▓▓██          ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒██          
                              ████████▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒██          ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██        
                            ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒██    ▓▓▓▓▓▓▓▓████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██      
                        ▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████▓▓▓▓▓▓▓▓▓▓▓▓▒▒██      
                      ▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒░░░░▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▓▓▒▒░░░░▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓    
                    ▓▓▒▒░░░░▒▒▒▒░░▒▒░░░░░░▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒░░░░░░░░▒▒▒▒░░▒▒▒▒██▓▓▓▓▓▓▓▓▓▓▒▒██    
                  ▓▓▒▒▒▒░░▒▒▒▒▒▒░░░░░░░░▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒▒▒▒▒░░▒▒▒▒██▓▓▓▓▓▓▓▓▓▓▒▒██  
                  ▓▓▒▒░░▒▒▒▒░░░░░░░░░░▒▒▒▒░░▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░▒▒▒▒░░░░▒▒██▓▓▓▓▓▓▓▓▓▓▒▒██  
                ██▒▒░░▒▒▒▒░░░░░░░░░░▒▒▒▒░░▒▒▒▒░░▒▒░░▒▒▒▒░░▒▒▒▒▒▒░░▒▒▒▒░░░░░░▒▒▒▒▒▒▒▒░░▒▒██▓▓▓▓▓▓▓▓▒▒██  
                ▓▓░░░░▒▒▒▒░░░░░░░░▒▒▒▒░░░░▒▒▒▒░░░░▒▒▒▒▒▒░░████▒▒░░▒▒▒▒▒▒░░░░████▒▒▒▒░░░░██▓▓▓▓▓▓▓▓▒▒██  
              ▓▓▒▒░░▒▒▒▒░░░░░░░░░░▒▒▒▒░░░░▒▒▒▒░░░░▒▒▒▒▒▒░░██▒▒██░░▒▒▒▒▒▒▒▒██▒▒██▒▒▒▒▒▒▒▒░░██▓▓▓▓▓▓▒▒██  
              ▓▓░░░░▒▒▒▒░░░░░░░░▒▒▒▒▒▒░░░░▒▒▒▒░░░░░░▒▒▒▒░░██▓▓▒▒▓▓░░▒▒▒▒▓▓▓▓▒▒██▒▒▒▒▒▒░░▒▒██▓▓▓▓▓▓▒▒██  
            ▒▒▒▒░░░░▒▒▒▒░░░░░░░░▒▒▒▒▒▒░░▒▒▒▒▒▒░░░░░░▒▒▒▒░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██▒▒▒▒▒▒░░░░▒▒██▓▓▓▓▒▒██  
            ▓▓░░░░░░▒▒▒▒░░░░░░▒▒▒▒▒▒▒▒░░▒▒▒▒░░░░░░▓▓▓▓▒▒░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██▒▒▒▒▓▓▓▓░░▒▒██▓▓▓▓▓▓██  
            ▓▓▒▒░░▒▒▒▒▒▒░░░░░░▒▒▒▒▒▒░░░░▒▒▒▒░░░░░░░░▒▒██░░██▓▓▓▓  ▓▓▓▓▓▓  ▓▓▒▒██▒▒██▒▒▒▒░░░░██▓▓▒▒████  
            ▓▓▒▒░░▒▒▒▒░░░░░░░░▒▒▒▒░░░░▒▒▒▒░░░░░░░░▒▒▒▒▒▒░░██▓▓██  ▓▓▓▓▓▓  ▓▓▒▒██░░▒▒▒▒▒▒░░▒▒██▓▓▒▒████  
            ▓▓▒▒░░▒▒▒▒▒▒░░░░▒▒▒▒▒▒░░░░▒▒▒▒░░░░░░░░██████░░██▓▓▓▓██▓▓▓▓▓▓▓▓▓▓▒▒██░░██████░░▒▒██▓▓██▓▓██  
            ▓▓▒▒░░▒▒▒▒▒▒░░░░▒▒▒▒▒▒░░░░▒▒▒▒░░░░░░░░░░▒▒▒▒░░░░██▓▓▓▓▓▓▓▓▓▓▓▓▒▒██░░░░▒▒▒▒▒▒░░░░▓▓████▓▓██  
            ▓▓▒▒░░▒▒▒▒▒▒░░░░▒▒▒▒░░░░░░▒▒▒▒░░░░░░░░░░▒▒▒▒░░░░▒▒██████████████▒▒░░░░▒▒▒▒▒▒░░░░▓▓  ██▓▓██  
            ▓▓▒▒░░▒▒▒▒░░░░░░▒▒▒▒░░░░░░▒▒▒▒░░░░░░░░░░▒▒▒▒░░░░██▓▓▓▓▓▓▓▓▓▓▒▒▓▓██░░░░████▓▓░░▒▒▓▓  ██▓▓██  
            ░░▓▓░░░░▒▒▒▒░░░░▒▒▒▒░░░░░░▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒░░░░██▓▓▓▓▓▓▓▓▓▓▓▓▒▒██░░▒▒██▓▓▓▓▓▓▓▓░░  ██▓▓██  
              ▓▓▒▒░░▒▒▒▒░░░░▒▒▒▒▒▒░░░░▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒░░░░██▓▓▓▓▓▓▓▓▓▓▓▓▒▒██░░▒▒▓▓██▓▓██▓▓    ██▓▓██  
                ▓▓░░▒▒▒▒░░░░░░▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██▒▒▒▒██▓▓██      ██▓▓██  
                ▓▓▒▒▒▒▒▒░░░░░░▒▒▒▒░░░░░░▒▒▒▒░░░░░░░░▒▒▒▒░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██▒▒▒▒██▓▓██      ██▓▓██  
                ░░▓▓░░▒▒▒▒▒▒░░░░▒▒▒▒▒▒░░▒▒▒▒▒▒░░░░░░▒▒▒▒░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██▒▒▒▒██▓▓██      ░░██░░  
    ██████████████▓▓▒▒▒▒▒▒▒▒░░░░▒▒▒▒░░▒▒▒▒▒▒░░░░░░░░▒▒▒▒░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██▒▒▒▒██▓▓██              
  ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░▒▒▒▒░░░░▒▒▒▒░░▒▒▒▒░░▒▒░░░░▒▒▒▒░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██░░▒▒██▓▓██              
    ██████████████████▓▓▒▒▒▒▒▒▒▒░░░░▒▒▒▒░░▒▒▒▒▒▒░░░░▒▒▒▒░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██▒▒██▓▓██                
      ░░░░░░      ░░    ▓▓▓▓▓▓▓▓▒▒░░▒▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██▓▓██▓▓██                
                        ░░░░░░░░▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒░░░░▒▒▒▒▒▒██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒████▓▓██░░                
                                          ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██████████████████████▓▓    
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