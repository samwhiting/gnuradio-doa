#include <stdio.h>
#include <vector>
#include <algorithm>
#include <numeric>

// prints out a 3x3 matrix that is a 2d vector
void printMatrix(std::vector<std::vector<float> > a){
  printf("| %6.2f %6.2f %6.2f |\n",a[0][0],a[0][1],a[0][2]);
  printf("| %6.2f %6.2f %6.2f |\n",a[1][0],a[1][1],a[1][2]);
  printf("| %6.2f %6.2f %6.2f |\n",a[2][0],a[2][1],a[2][2]);
}

// permutes a 3x3 matrix, swapping rows b and c
void permute(std::vector<std::vector<float> >& a, int b, int c){
  float temp;
  for(int i=0; i<3; ++i){
    temp = a[b][i];
    a[b][i] = a[c][i];
    a[c][i] = temp;
  }
}

int main(){
  //original matrix
  std::vector<std::vector<float> > upper(3, std::vector<float>(3, 0));
  upper[0][0] = 2;upper[0][1] =  4;upper[0][2] = -5;
  upper[1][0] = 6;upper[1][1] =  8;upper[1][2] = 1;
  upper[2][0] = 4;upper[2][1] = -8;upper[2][2] = -3;

  //permutation matrix, initialized to identity 
  std::vector<std::vector<float> > perm(3, std::vector<float>(3, 0));
  perm[0][0] = 1;perm[0][1] = 0;perm[0][2] = 0;
  perm[1][0] = 0;perm[1][1] = 1;perm[1][2] = 0;
  perm[2][0] = 0;perm[2][1] = 0;perm[2][2] = 1;

  //lower triange matrix, initialized to identity 
  std::vector<std::vector<float> > lower(3, std::vector<float>(3, 0));
  lower[0][0] = 1;lower[0][1] = 0;lower[0][2] = 0;
  lower[1][0] = 0;lower[1][1] = 1;lower[1][2] = 0;
  lower[2][0] = 0;lower[2][1] = 0;lower[2][2] = 1;


  printf("\n**********************************************\n\n");
  printf(" The original matrix:\n");
  printMatrix(upper);

  float factor = 0;

  // clear [1][0]
  if(upper[0][0] == 0) return 1; //error - divide by zero
  factor = upper[1][0]/upper[0][0];
  lower[1][0] = factor; //save for lower matrix
  for(int i=0; i<3; ++i){upper[1][i] -= factor*upper[0][i];}
  
  printf("\n first row operation with factor: %6.2f\n",factor);
  printMatrix(upper);
 

  // clear [2][0]
  factor = upper[2][0]/upper[0][0];
  lower[2][0] = factor; //save for lower matrix
  for(int i=0; i<3; ++i){upper[2][i] -= factor*upper[0][i];}
  
  printf("\n second row operation with factor: %6.2f\n",factor);
  printMatrix(upper);

  // clear [2][1]
  if(upper[1][1] == 0) return 1; //error - divide by zero
  factor = upper[2][1]/upper[1][1];
  lower[2][1] = factor; //save for lower matrix
  for(int i=0; i<3; ++i){upper[2][i] -= factor*upper[1][i];}
  
  printf("\n third row operation with factor: %6.2f\n",factor);
  printMatrix(upper);

  // Show our lower matrix
  printf("\n The lower matrix:\n");
  printMatrix(lower);

  //testing permute()
  printf("\n Perm:\n");
  printMatrix(perm);

  permute(perm,1,2);
  printf("\n P12:\n");
  printMatrix(perm);


  printf("**********************************************\n\n");
  return 0;
}
