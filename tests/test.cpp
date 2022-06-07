#include <array>
#include <iostream>
#include <string>
#include <vector>
#include "npy.hpp"

using namespace std;

int test_load(void) {
  vector<unsigned long> shape;
  bool fortran_order;
  vector<double> data;

  vector<const char*> allpaths {
    "data/matrix_f8.npy",
    "data/matrix_f8_t.npy",
    "data/empty_f8.npy",
    "data/empty_f8_t.npy",
    "data/scalar_f8.npy",
    "data/scalar_f8_t.npy",
  };

  for (auto path : allpaths) {
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
  const vector<double> data1 {1, 2, 3, 4, 5, 6};
  array<long unsigned, 2> leshape11 {{2,3}};
  array<long unsigned, 1> leshape12 {{6}};

  const double data2[] = {7};
  array<long unsigned, 3> leshape21 {{1,1,1}};
  array<long unsigned, 0> leshape22 {};

  const array<double, 0> data3;
  array<long unsigned, 2> leshape31 {{4,0}};

  npy::SaveArrayAsNumpy("data/out11.npy", false, leshape11.size(), leshape11.data(), data1);
  npy::SaveArrayAsNumpy("data/out12.npy", false, leshape12.size(), leshape12.data(), data1);

  npy::SaveArrayAsNumpy("data/out21.npy", false, leshape21.size(), leshape21.data(), data2);
  npy::SaveArrayAsNumpy("data/out22.npy", false, leshape22.size(), leshape22.data(), data2);

  npy::SaveArrayAsNumpy("data/out31.npy", false, leshape31.size(), leshape31.data(), data3.data());

  return 0;
}

int main() {
  test_load();

  test_save();

  return 0;
}

