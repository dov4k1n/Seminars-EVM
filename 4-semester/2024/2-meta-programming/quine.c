#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void generate_gaussian_elimination_code(int rows, int cols, FILE *out) {
  fprintf(out, "double* solve(matrix *A) {\n");
  fprintf(out, "  double *root = (double*)malloc((A->cols - 1)*sizeof(double)\n");
  fprintf(out, "  if (root == NULL) {\n");
  fprintf(out, "    return NULL;\n");
  fprintf(out, "  }\n");
  fprintf(out, "  A->rank = 0;\n");
  fprintf(out, "  int pivot_row, pivot_col;\n");
  fprintf(out, "  double *tmp;\n");
  fprintf(out, "  double scalar;\n\n");
  
  /*
   * ROW ECHELON FORM:
   */
  for (int j = 0; j < cols - 1; j++) {
    fprintf(out, "  pivot_row = -1;\n");
    fprintf(out, "  pivot_col = -1;\n\n");

    for (int i = j; i < rows; i++) {
      if (i == j) {
        fprintf(out, "  if (fabs(A->data[%d][%d]) > EPSILON) {\n", i, j);
      } else {
        fprintf(out, "  else if (fabs(A->data[%d][%d]) > EPSILON) {\n", i, j);
      }
      if (i != j) {
        fprintf(out, "    // swap rows(%d, %d):\n", i, j);
        fprintf(out, "    tmp = A->data[%d];\n", i);
        fprintf(out, "    A->data[%d] = A->data[%d];\n", i, j);
        fprintf(out, "    A->data[%d] = tmp;\n\n", j);
      }
      fprintf(out, "    pivot_row = %d;\n", j);
      fprintf(out, "    pivot_col = %d;\n", j);
      fprintf(out, "    A->rank += 1;\n");
      fprintf(out, "  }\n\n");
    }

    if (j + 1 < rows) {
      fprintf(out, "  if (pivot_row != -1) {\n");
      for (int h = j + 1; h < rows; h++) {
        fprintf(out, "    scalar = (-1) * A->data[%d][pivot_col] / A->data[pivot_row][pivot_col];\n", h);
        for (int k = 0; k < cols; k++) {
          fprintf(out, "    A->data[%d][%d] += scalar * A->data[pivot_row][%d];\n", h, k, k);
          if (k == cols - 1 && i < rows - 1) {
            fprintf(out, "\n");
          }
        }
      }
      fprintf(out, "  }\n\n");
    }
  }

  /*
   * REDUCED ROW ECHELON FORM:
   */
  int pivot_row = fmin(rows, cols);
  for (int i = pivot_row - 1; i >= 0; i--) {
    fprintf(out, "  pivot_row = %d;\n", i);
    fprintf(out, "  pivot_col = -1;\n");

    for (int j = i; j < cols - 1; j++) {
      if (j == i) {
        fprintf(out, "  if (fabs(A->data[pivot_row][%d]) > EPSILON) {\n", j);
      } else {
        fprintf(out, "  else if (fabs(A->data[pivot_row][%d]) > EPSILON) {\n", j);
      }
      fprintf(out, "    pivot_col = %d;\n", j);
      fprintf(out, "  }\n\n");
    }
    
    fprintf(out, "  if (pivot_col != -1) {\n");
    fprintf(out, "    scalar = 1 / A->data[pivot_row][pivot_col];\n");
    for (int l = i; l < cols; l++) {
      fprintf(out, "    A->data[pivot_row][%d] *= scalar;\n", l);
    }
    fprintf(out, "\n");

    if (i != 0) {
      for (int h = i - 1; h >= 0; h--) {
        fprintf(out, "    scalar = (-1) * A->data[%d][pivot_col] / A->data[pivot_row][pivot_col];\n", h);
        for (int k = h; k < cols; k++) {
          fprintf(out, "    A->data[%d][%d] += scalar * A->data[pivot_row][%d];\n", h, k, k);
          if (k == cols - 1) {
            fprintf(out, "\n");
          }
        }
      }
    }
    fprintf(out, "  }\n");
  }

  for (int i = pivot_row - 1; i >= 0; i--) {
    fprintf(out, "  pivot_row = %d;\n", i);
    fprintf(out, "  pivot_col = -1;\n");

    for (int j = i; j < cols - 1; j++) {
      if (j == i) {
        fprintf(out, "  if (fabs(A->data[pivot_row][%d]) > EPSILON) {\n", j);
      } else {
        fprintf(out, "  else if (fabs(A->data[pivot_row][%d]) > EPSILON) {\n", j);
      }
      fprintf(out, "    pivot_col = %d;\n", j);
      fprintf(out, "  }\n\n");
    }
  }

  fprintf(out, "}");
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("need matrix's dimensions\n");
    return 1;
  }

  int rows = atoi(argv[1]);
  int cols = atoi(argv[2]);

  FILE *out = fopen("output.txt", "wt");
  if (out == NULL) {
    printf("error: can't open file\n");
    return -1;
  }

  generate_gaussian_elimination_code(rows, cols, out);

  fclose(out);
  return 0;
}