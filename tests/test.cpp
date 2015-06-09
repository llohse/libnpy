#include <iostream>
#include <string>
#include <vector>
#include "../npy.hpp"

using namespace std;

int test_parse_header(void) {
//  std::string test_header = "{'descr': '<f8', 'fortran_order': False, 'shape': (2, 3), }          \n";
//  npy::ParseHeader(s, &fortran_order, shape, descr);

  return 0;
}

int test_load(void) {
  vector<unsigned long> shape;
  vector<double> data;
  npy::LoadArrayFromNumpy("double.npy", shape, data);

  cout << "shape: ";
  for (size_t i = 0; i<shape.size(); i++)
    cout << shape[i] << ", ";
  cout << endl;
  cout << "data: ";
  for (size_t i = 0; i<data.size(); i++)
    cout << data[i] << ", ";
  cout << endl;

  return 0;
}

int test_save(void) {
  const long unsigned leshape [] = {2,3};
//  npy::SaveArrayAsNumpy("../../out.npy", false, 2, leshape, data);

  return 0;
}

int main(int argc, char **argv) {
  test_load();

  return 0;
}

