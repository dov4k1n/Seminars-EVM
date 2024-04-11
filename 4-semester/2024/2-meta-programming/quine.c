#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void generate_linear_solver_code(int matrix_size) {
  printf("#include <stdio.h>\n");
  printf("#include <math.h>\n\n");
  printf("int solve(double *matrix, double *rhs) {\n");

  for (int i = 0; i < matrix_size; i++) {
    for (int j = 0; j < matrix_size; j++) {
      if (i != j) {
        printf("  if (fabs(matrix[%d]) < 1e-16) {\n", i*matrix_size + i);
        printf("    return 1;\n");
        printf("  }\n");
        printf(
          "  matrix[%d] = matrix[%d] - matrix[%d] * matrix[%d] / matrix[%d];\n",
          i*matrix_size + j, 
          i*matrix_size + j, 
          i*matrix_size + i, 
          j*matrix_size + i, 
          i*matrix_size + i
        );
      }
    }
    
    printf(
      "  rhs[%d] = rhs[%d] - matrix[%d] * rhs[%d] / matrix[%d];\n",
      i, 
      i, 
      i*matrix_size + i, 
      i, 
      i*matrix_size + i
    );
  }

  printf("    return 0;\n");
  printf("}\n");
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("need matrix dimension\n");
    return 1;
  }

  int matrix_size = atoi(argv[1]);
  generate_linear_solver_code(matrix_size);

  return 0;
}