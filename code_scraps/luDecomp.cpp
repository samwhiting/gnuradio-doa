#include <stdio.h>
#include <vector>

// prints out a 3x3 matrix that is a 2d vector
void printMatrix(std::vector<std::vector<float> > a){
  printf("| %7.3f %7.3f %7.3f |\n",a[0][0],a[0][1],a[0][2]);
  printf("| %7.3f %7.3f %7.3f |\n",a[1][0],a[1][1],a[1][2]);
  printf("| %7.3f %7.3f %7.3f |\n",a[2][0],a[2][1],a[2][2]);
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

// decompose matrix 'original' into lower and upper matrices. 
void luDecomp(std::vector<std::vector<float> >& original,std::vector<std::vector<float> >& lower,std::vector<std::vector<float> >& upper){
  // intialize lower to identity
  lower[0][0] = 1;lower[0][1] = 0;lower[0][2] = 0;
  lower[1][0] = 0;lower[1][1] = 1;lower[1][2] = 0;
  lower[2][0] = 0;lower[2][1] = 0;lower[2][2] = 1;

  // copy original to upper
  upper = original;

  float factor = 0;

  // clear [1][0]
  if(upper[0][0] == 0) printf("\n\n****ERROR - DIVIDE BY ZERO ****\n\n"); //error - divide by zero
  factor = upper[1][0]/upper[0][0];
  lower[1][0] = factor; //save for lower matrix
  for(int i=0; i<3; ++i){upper[1][i] -= factor*upper[0][i];}
  
  // clear [2][0]
  factor = upper[2][0]/upper[0][0];
  lower[2][0] = factor; //save for lower matrix
  for(int i=0; i<3; ++i){upper[2][i] -= factor*upper[0][i];}
  
  // clear [2][1]
  if(upper[1][1] == 0) printf("\n\n****ERROR - DIVIDE BY ZERO ****\n\n"); //error - divide by zero
  factor = upper[2][1]/upper[1][1];
  lower[2][1] = factor; //save for lower matrix
  for(int i=0; i<3; ++i){upper[2][i] -= factor*upper[1][i];}
  
}

// invert a lower triangular matrix with 1s on the diagonal
void invert_lower(std::vector<std::vector<float> >& original,std::vector<std::vector<float> >& inverse){
  
  // the inverse is also lower, with 1s on the diagonal
  inverse[0][0] = 1;inverse[0][1] = 0;inverse[0][2] = 0;
                    inverse[1][1] = 1;inverse[1][2] = 0;
                                      inverse[2][2] = 1;
  // easy ones are just negatives
  inverse[1][0] = -1*original[1][0];
  inverse[2][1] = -1*original[2][1];
  
  // forward sub the last
  inverse[2][0] = original[1][0] * original[2][1] - original[2][0];
}

// invert an upper triangular matrix
void invert_upper(std::vector<std::vector<float> >& original,std::vector<std::vector<float> >& inverse){
  // the inverse is also an upper triangle matrix
  inverse[0][0] = 1;inverse[0][1] = 0;inverse[0][2] = 0;
  inverse[1][0] = 0;inverse[1][1] = 1;inverse[1][2] = 0;
  inverse[2][0] = 0;inverse[2][1] = 0;inverse[2][2] = 1;
  
  // diagonals are inverses
  inverse[0][0] = 1/original[0][0];
  inverse[1][1] = 1/original[1][1];
  inverse[2][2] = 1/original[2][2];

  // back sub for the rest
  inverse[1][2] = -1*original[1][2]/(original[2][2]*original[1][1]);
  inverse[0][1] = -1*original[0][1]/(original[1][1]*original[0][0]);
  inverse[0][2] = ((-1*original[0][1] * inverse[1][2]) - (original[0][2] * inverse[2][2])) / original[0][0];
}

// main
int main(){
  // original matrix
  std::vector<std::vector<float> > original(3, std::vector<float>(3, 0));
  original[0][0] = 2;original[0][1] =  4;original[0][2] = -5;
  original[1][0] = 6;original[1][1] =  8;original[1][2] = 1;
  original[2][0] = 4;original[2][1] = -8;original[2][2] = -3;

  // lower/upper triangle matrices
  std::vector<std::vector<float> > lower(3, std::vector<float>(3, 0));
  std::vector<std::vector<float> > upper(3, std::vector<float>(3, 0));

  // find the lu decomposition
  luDecomp(original,lower,upper);

  // find the inverse of the lower matrix - forward sub
  std::vector<std::vector<float> > inv_lower(3, std::vector<float>(3, 0));
  invert_lower(lower,inv_lower);

  // find the inverse of the upper matrix - back sub
  std::vector<std::vector<float> > inv_upper(3, std::vector<float>(3, 0));
  invert_upper(upper,inv_upper);

  // print everything
  printf("\n**********************************************\n\n");
  // show original matrix
  printf(" The original matrix:\n");
  printMatrix(original);

  // Show our upper matrix
  printf("\n The upper matrix:\n");
  printMatrix(upper);

  // Show our lower matrix
  printf("\n The lower matrix:\n");
  printMatrix(lower);

  // show inverse of lower
  printf("\n inverse of lower:\n");
  printMatrix(inv_lower);

  // show inverse of upper
  printf("\n inverse of upper:\n");
  printMatrix(inv_upper);

  printf("**********************************************\n\n");
  return 0;
}
