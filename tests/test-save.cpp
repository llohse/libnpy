#include <array>
#include <iostream>
#include <string>
#include <vector>
#include "npy.hpp"

int test_save(void) {
  const std::vector<double> data1 {1, 2, 3, 4, 5, 6};
  std::array<long unsigned, 2> leshape11 {2, 3};
  std::array<long unsigned, 1> leshape12 {6};

  const double data2[] {7};
  std::array<long unsigned, 3> leshape21 {1, 1, 1};
  std::array<long unsigned, 0> leshape22 {};

  const std::array<double, 0> data3;
  std::array<long unsigned, 2> leshape31 {4, 0};

  npy::SaveArrayAsNumpy("data/out11.npy", false, leshape11.size(), leshape11.data(), data1);
  npy::SaveArrayAsNumpy("data/out12.npy", false, leshape12.size(), leshape12.data(), data1);

  npy::SaveArrayAsNumpy("data/out21.npy", false, leshape21.size(), leshape21.data(), data2);
  npy::SaveArrayAsNumpy("data/out22.npy", false, leshape22.size(), leshape22.data(), data2);

  npy::SaveArrayAsNumpy("data/out31.npy", false, leshape31.size(), leshape31.data(), data3.data());

  return 0;
}

int main() {
  test_save();

  return 0;
}
