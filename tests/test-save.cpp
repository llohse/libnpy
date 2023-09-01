#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "npy.hpp"

int test_save() {
  const std::vector<double> data1{1, 2, 3, 4, 5, 6};
  const std::vector<unsigned long> leshape11{2, 3};
  const std::vector<unsigned long> leshape12{6};

  const npy::npy_data<double> data11{leshape11, false, data1};
  write_npy("data/out11.npy", data11);

  const npy::npy_data<double> data12{leshape12, false, data1};
  write_npy("data/out12.npy", data12);

  const npy::npy_data_ptr<double> data11_ptr{leshape11, false, data1.data()};
  write_npy("data/out11_ptr.npy", data11_ptr);

  const std::vector<double> data2{7};
  const std::vector<unsigned long> leshape21{1, 1, 1};
  const std::vector<unsigned long> leshape22{};

  const npy::npy_data<double> data21{leshape21, false, data2};
  write_npy("data/out21.npy", data21);
  const npy::npy_data<double> data22{leshape22, false, data2};
  write_npy("data/out22.npy", data22);

  const std::vector<double> data3{};
  const std::vector<unsigned long> leshape31{4, 0};

  const npy::npy_data<double> data31{leshape31, false, data3};
  write_npy("data/out31.npy", data31);

  return 0;
}

int main() {
  test_save();

  return 0;
}
