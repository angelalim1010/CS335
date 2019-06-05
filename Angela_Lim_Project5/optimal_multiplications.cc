//Angela Lim
//CS335
#include<iostream>
#include<fstream>
#include "OptMatrix.h"
using namespace std;

//function parses through the text file
void OptimalMatrixTest(const string & dimensions_filename){
  cout << "Dimensions file name: " << dimensions_filename << endl;

  string new_line;
  ifstream inFile(dimensions_filename);
  if(inFile.fail()) {
      cout << " Error while opening. ";
      exit(1);
  }
  vector<int> dimensions;
  int n = 0;
  //adding the dimensions to the vector
  while(getline(inFile, new_line)){
    n++;
    dimensions.push_back(stoi(new_line, nullptr));
  }
  //find the optimal multiplcation using
  int optimal_num = OptMatrix(dimensions, n);
  cout << "Optimal number of multiplications: " << optimal_num << endl;

}
int main(int argc, char ** argv){
  if(argc != 2){
    cout << "Usage:" << argv[0] << " <DIMENSTIONS_FILENAME>" << endl;
  }

  const string dimensions_filename(argv[1]);

  OptimalMatrixTest(dimensions_filename);
  return 0;

}
