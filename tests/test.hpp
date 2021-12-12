#include <iostream>
#include <string>
#include <vector>
#include "npy.hpp"

using namespace std;

int test_load(void) {
  vector<unsigned long> shape;
  bool fortran_order;
  vector<double> data;

  for (auto path : {"data/f8.npy", "data/f8_t.npy"}) {
    shape.clear();
    data.clear();
    npy::LoadArrayFromNumpy(path, shape, fortran_order, data);

    cout << "shape: ";
    for (size_t i = 0; i<shape.size(); i++)
      cout << shape[i] << ", ";
    cout << endl;
    cout << "fortran order: " << (fortran_order ? "+" : "-");
    cout << endl;
    cout << "data: ";
    for (size_t i = 0; i<data.size(); i++)
      cout << data[i] << ", ";
    cout << endl << endl;
  }

  return 0;
}

int test_save(void) {
  const long unsigned leshape [] = {2,3};
  vector<double> data {1, 2, 3, 4, 5, 6};
  npy::SaveArrayAsNumpy("data/out.npy", false, 2, leshape, data);

  const long unsigned leshape2 [] = {6};
  npy::SaveArrayAsNumpy("data/out2.npy", false, 1, leshape2, data);

  return 0;
}

// int main() {
//   test_load();

//   test_save();

//   return 0;
// }

