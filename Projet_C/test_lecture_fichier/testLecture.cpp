#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[]) {

  ifstream infile;
  infile.open("AND2.dot");

  char x;

  while ( !infile.eof()){
    cout << x << endl;
    infile.get(x);
  }

  infile.clear();
  infile.seekg(0);

  string ligne;

  while(getline(infile, ligne)){
    cout << ligne << endl;
  }

  infile.close();
  return 0;
}
