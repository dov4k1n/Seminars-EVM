#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int generate_matrix(FILE *in, int m, int n, int ch) {
  int i, j;
  double tmp;

  if (ch == 1) {
    for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++) {
        if (scanf("%lf", &tmp) != 1)
          return 1;
        fprintf(in, "%.2lf ", tmp);
      }
    fprintf(in, "\n");
    }
    return 0;
  }

  else if (ch == 0) {
    srand(time(NULL));
    for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++) {
        //tmp = (double)rand()/RAND_MAX * 300 - 150;
        tmp = rand() % 10;
        fprintf(in, "%.2lf ", tmp);
      }
      fprintf(in, "\n");
    }
    return 0;
  }

  return 1;
}

int load_matrix(double **A, FILE *in, int m, int n) {
  int i, j;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++)
      if (fscanf(in, "%lf", &A[i][j]) != 1) {
        printf("error: couldn't write A[%d][%d]", i, j);
        return 1;
      }
  }
  return 0;
}

void swap_rows(double **A, int i, int j) {
  double *tmp = A[i];
  A[i] = A[j];
  A[j] = tmp;
}

void swap_columns(double **A, int colsize, int i, int j) {
  double tmp;
  for (int k = 0; k < colsize; k++) {
    tmp = A[k][i];
    A[k][i] = A[k][j];
    A[k][j] = tmp;
  }
}

void clean_under_2(double **A, int a, int b, int c, int n) { // eliminating number under leader of a
  double alpha = A[b][c] / A[a][c];
  for (int j = 0; j < n; j++) { // j ~ columns
    A[b][j] -= alpha * A[a][j]; // substracting rows
    if (fabs(A[b][j]) < 0.0001 && A[b][j] < 0)
      A[b][j] *= -1;
  }
}

int killdown_column(double **A, int leadi, int coli, int m, int n) {
  int i, j;
  for (i = leadi; i < m; i++)
    if (fabs(A[i][coli]) > 0.0001) { // found leader
      swap_rows(A, leadi, i);
      leadi++;
      for (j = leadi; j < m; j++) // killing numbers under leader
        clean_under_2(A, leadi-1, j, coli, n); // j ~ index of a row
      return leadi; // leadi increases -> moving to the next row's leader
    }
  return leadi;
}

int row_echelon_form(double **A, int m, int n) {
  // coli ~ column_index
  int leadi = 0; // leadi ~ leader_index
  for (int coli = 0; coli < n-1; coli++)
    leadi = killdown_column(A, leadi, coli, m, n);
  return leadi; // leadi ~ rank
}

void killup_column(double **A, int rowi, int coli, int m, int n) { // cleans up column
  int nrowi;
  for (nrowi = rowi-1; nrowi >= 0; nrowi--) {
    clean_under_2(A, rowi, nrowi, coli, n); // substracts rows
  }
}

void normalize_row(double **A, int m, int n, int rowi) {
  int ncoli;
  for (int coli = 0; coli < n; coli++)
    if (fabs(A[rowi][coli]) > 0.0001) { //found leader of row
      for (ncoli = coli+1; ncoli < n; ncoli++) {
        A[rowi][ncoli] *= 1 / fabs(A[rowi][coli]);
        if (A[rowi][coli] < 0 && fabs(A[rowi][ncoli]) > 0.0001)
          A[rowi][ncoli] *= -1;
      }
      A[rowi][coli] *= 1/A[rowi][coli];
      break;
    }
}

/* 
 * Requires row echelon form of matrix A 
 */  
void reduced_row_echelon_form(double **A, int m, int n, int *perm) {
  int flag, rowi, coli, i;
  for (rowi = m-1; rowi >= 0; rowi--) { //killing cols
    flag = 0;
    for (coli = 0; coli < n-1; coli++)
      if (fabs(A[rowi][coli]) > 0.0001) { //found leader
        flag = 1;
        break;
      }

    if (flag == 1)
      killup_column(A, rowi, coli, m, n);
  }
  int permtmp;
  for (rowi = 0; rowi < m; rowi++) { //swapping cols
    flag = 0;
    for (coli = 0; coli < n-1; coli++)
      if (fabs(A[rowi][coli]) > 0.0001) {
        flag = 1;
        break;
      }
    if (flag == 1) {
      permtmp = perm[rowi];
      perm[rowi] = perm[coli];
      perm[coli] = permtmp;
      swap_columns(A, m, rowi, coli);
    }
  }
  for (rowi = 0; rowi < m; rowi++)
      normalize_row(A, m, n, rowi);
}

/* 
 * Requires reduced row echelon form of matrix A 
 */ 
double *find_root(double **A, const int n, const int rank) {
  int i, j;
  double *root = (double*)malloc((n-1)*sizeof(double));
  if (root == NULL) {
    return NULL;
  }

  for (i = 0; i < rank; i++) {
    root[i] = A[i][n-1];
    for (j = rank; j < n-1; j++)
      root[i] -= A[i][j];
  }
  for (i = rank; i < n-1; i++)
    root[i] = 1;

  return root;
}

void nullspace(double **A, int n, int leadi, int it, double *root) {
  int i, j = n-1-it-1;
  for (i = 0; i < leadi; i++) {
    root[i] = 0;
    root[i] -= A[i][j];
  }

  for (i = leadi; i < n-1; i++)
    root[i] = 0;
  root[j] = 1;
}

int main() {
  FILE *in;
  int i, j, m, n;
  in = fopen("input.txt", "wt");
  if (in == NULL) {
    printf("error: couldn't create in\n");
    return -1;
  }

  printf("enter augmented matrix dimensions (two numbers M rows N columns):\n");
  if (scanf("%d %d", &m, &n) != 2 || m <= 0 || n <= 0) {
    printf("error: couldn't read m or n, or wrong format\n");
    fclose(in);
    return -1;
  }

  int ch = 0;
  printf("type 1 to enter manual matrix, or 0 for random:\n");
  if (scanf("%d", &ch) != 1 || ch > 1 || ch < 0) {
    printf("couldn't read choice or wrong format\n");
    fclose(in);
    return -1;
  }
  if (ch)
    printf("enter augmented %dx%d matrix's elements:\n", m, n);
  
  if (generate_matrix(in, m, n, ch)) {
    printf("error: problem with typing elements\n");
    fclose(in);
    return -1;
  }
  
  fclose(in);

  double **A;
  A = (double**)malloc(m*sizeof(double*));
  if (A == NULL) {
    printf("error: couldn't create array A\n");
    return -1;
  }
  for (i = 0; i < m; i++) {
    A[i] = (double*)malloc(n*sizeof(double));
    if (A[i] == NULL) {
      printf("error: couldn't create array A[i]\n");
      for (j = 0; j < i; j++)
        free(A[j]);
      free(A);
      return -1;
    }
  }

  double **B;
  B = (double**)malloc(m*sizeof(double*));
  if (B == NULL) {
    printf("error: couldn't create array B\n");
    return -1;
  }
  for (i = 0; i < m; i++) {
    B[i] = (double*)malloc(n*sizeof(double));
    if (B[i] == NULL) {
      printf("error: couldn't create array B[%d]\n", i);
      for (j = 0; j < i; j++)
        free(B[j]);
      free(B);
      return -1;
    }
  }

  in = fopen("input.txt", "rt");
  if (load_matrix(A, in, m, n)) {
    for (i = 0; i < m; i++)
      free(A[i]);
    free(A);
    fclose(in);
    return -1;
  }
  fclose(in);

  printf("\ninputed:\n");
  for (i = 0; i < m; i++) {
    for (j = 0; j < n-1; j++)
      printf("\t%.2lf", A[i][j]);
    printf("\t|\t%.2lf\n", A[i][n-1]);
  }

  int rank = row_echelon_form(A, m, n);

  printf("\nrank = %d, row echelon form:\n", rank);
  for (i = 0; i < m; i++) {
    for (j = 0; j < n - 1; j++) {
      if (fabs(A[i][j]) < 0.0001) {
        printf("\t....");
      } else {
        printf("\t%.2lf", A[i][j]);
      }
    }
    if (fabs(A[i][n - 1]) < 0.0001) {
      printf("\t|\t....\n");
    } else {
      printf("\t|\t%.2lf\n", A[i][n - 1]);
    }
  }

  for (i = rank; i < m; i++)
    if (A[i][n-1] != 0) { //we got equation like 0 = b, where b != 0
      printf("\nno solution\n");//for wide matrix A[rank+][n-1] will be incorrect, so ok
      for (i = 0; i < m; i++)
        free(A[i]);
      free(A);
      return 0;
    }
  
  int *perm = (int*)malloc(n*sizeof(int));
  if (perm == NULL) {
    printf("error: couldn't create perm\n");
    for (i = 0; i < m; i++)
        free(A[i]);
      free(A);
    return -1;
  }
  for (i = 0; i < n; i++)
    perm[i] = i;

  reduced_row_echelon_form(A, m, n, perm);

  printf("\nreduced row echelon form:\n");
  for (i = 0; i < m; i++) {
    for (j = 0; j < n - 1; j++) {
      if (fabs(A[i][j]) < 0.0001) {
        printf("\t....");
      } else {
        printf("\t%.2lf", A[i][j]);
      }
    }
    if (fabs(A[i][n - 1]) < 0.0001) {
      printf("\t|\t....\n");
    } else {
      printf("\t|\t%.2lf\n", A[i][n - 1]);
    }
  }

  // double *root;
  // root = (double*)malloc((n-1)*sizeof(double));

  double *root = find_root(A, n, rank);

  if (root == NULL) {
    printf("erorr: root is NULL\n");
    for (i = 0; i < m; i++)
        free(A[i]);
    free(A);
    return -1;
  }

  printf("\nsolution of augmented matrix:\nv0: ");
  for (i = 0; i < n-1; i++)
    printf("\t%.2lf", root[i]);
  printf("\n");

  printf("\nkernel dimension = %d, nullspace basis:\n", n - 1 - rank);
  for (j = 0; j < n - 1 - rank; j++) {
    nullspace(A, n, rank, j, root);
    printf("v%d: ", j+1);
    for (i = 0; i < n-1; i++)
      printf("\t%.2lf", root[perm[i]]);
    printf("\n");
  }

  for (i = 0; i < m; i++)
    free(A[i]);
  free(A);
  free(root);
  return 0;
}