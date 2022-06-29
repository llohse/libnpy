#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <complex>
#include "npy.hpp"

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

const std::vector<unsigned long> expect_shape {2, 3};
const std::vector<unsigned long> expect_shape_t {3, 2};
const std::vector<int> expect_data_int {1, 2, 3, 4, 5, 6};
const std::vector<bool> expect_data_bool {false, true, false, true, false, true};
const int expect_scalar = 42;

template <typename Scalar>
std::vector<Scalar> cast_data(const std::vector<int> &input){
  std::vector<Scalar> output;
  output.resize(input.size());
  std::transform(input.cbegin(), 
		 input.cend(),
		 output.begin(),
		 [](int i) { return static_cast<Scalar>(i); });
  return output;
}

template <typename Scalar>
struct npy_data {
  std::vector<unsigned long> shape;
  bool fortran_order;
  std::vector<Scalar> data;
};

template <typename Scalar>
npy_data<Scalar> test_load(const char * path) {
  npy_data<Scalar> d;
  npy::LoadArrayFromNumpy(path, d.shape, d.fortran_order, d.data);
  return d;
}

TEST_CASE( "Load single precision data", "[read]" ) {
  auto d = test_load<float>("data/matrix_f4.npy");

  REQUIRE(d.shape == expect_shape);
  REQUIRE(d.data == cast_data<float>(expect_data_int));
  REQUIRE(d.fortran_order == false);

  auto dt = test_load<float>("data/matrix_f4_t.npy");

  REQUIRE(dt.shape == expect_shape_t);
  REQUIRE(dt.data == cast_data<float>(expect_data_int));
  REQUIRE(dt.fortran_order == true);
}

TEST_CASE( "Load double precision data", "[read]" ) {
  auto d = test_load<double>("data/matrix_f8.npy");

  REQUIRE(d.shape == expect_shape);
  REQUIRE(d.data == cast_data<double>(expect_data_int));
  REQUIRE(d.fortran_order == false);

  auto dt = test_load<double>("data/matrix_f8_t.npy");

  REQUIRE(dt.shape == expect_shape_t);
  REQUIRE(dt.data == cast_data<double>(expect_data_int));
  REQUIRE(dt.fortran_order == true);
}

TEST_CASE( "Load single precision complex data", "[read]" ) {
  auto d = test_load<std::complex<float>>("data/matrix_c8.npy");

  REQUIRE(d.shape == expect_shape);
  REQUIRE(d.data == cast_data<std::complex<float>>(expect_data_int));
  REQUIRE(d.fortran_order == false);

  auto dt = test_load<std::complex<float>>("data/matrix_c8_t.npy");

  REQUIRE(dt.shape == expect_shape_t);
  REQUIRE(dt.data == cast_data<std::complex<float>>(expect_data_int));
  REQUIRE(dt.fortran_order == true);
}

TEST_CASE( "Load double precision complex data", "[read]" ) {
  auto d = test_load<std::complex<double>>("data/matrix_c16.npy");

  REQUIRE(d.shape == expect_shape);
  REQUIRE(d.data == cast_data<std::complex<double>>(expect_data_int));
  REQUIRE(d.fortran_order == false);

  auto dt = test_load<std::complex<double>>("data/matrix_c16_t.npy");

  REQUIRE(dt.shape == expect_shape_t);
  REQUIRE(dt.data == cast_data<std::complex<double>>(expect_data_int));
  REQUIRE(dt.fortran_order == true);
}

TEST_CASE( "Load int8 data", "[read]" ) {
  auto d = test_load<signed char>("data/matrix_i1.npy");

  REQUIRE(d.shape == expect_shape);
  REQUIRE(d.data == cast_data<signed char>(expect_data_int));
  REQUIRE(d.fortran_order == false);

  auto dt = test_load<signed char>("data/matrix_i1_t.npy");

  REQUIRE(dt.shape == expect_shape_t);
  REQUIRE(dt.data == cast_data<signed char>(expect_data_int));
  REQUIRE(dt.fortran_order == true);
}

TEST_CASE( "Load int16 data", "[read]" ) {
  auto d = test_load<signed short>("data/matrix_i2.npy");

  REQUIRE(d.shape == expect_shape);
  REQUIRE(d.data == cast_data<signed short>(expect_data_int));
  REQUIRE(d.fortran_order == false);

  auto dt = test_load<signed short>("data/matrix_i2_t.npy");

  REQUIRE(dt.shape == expect_shape_t);
  REQUIRE(dt.data == cast_data<signed short>(expect_data_int));
  REQUIRE(dt.fortran_order == true);
}

TEST_CASE( "Load int32 data", "[read]" ) {
  auto d = test_load<signed int>("data/matrix_i4.npy");

  REQUIRE(d.shape == expect_shape);
  REQUIRE(d.data == cast_data<signed int>(expect_data_int));
  REQUIRE(d.fortran_order == false);

  auto dt = test_load<signed int>("data/matrix_i4_t.npy");

  REQUIRE(dt.shape == expect_shape_t);
  REQUIRE(dt.data == cast_data<signed int>(expect_data_int));
  REQUIRE(dt.fortran_order == true);
}

TEST_CASE( "Load int64 data", "[read]" ) {
  auto d = test_load<signed long>("data/matrix_i8.npy");

  REQUIRE(d.shape == expect_shape);
  REQUIRE(d.data == cast_data<signed long>(expect_data_int));
  REQUIRE(d.fortran_order == false);

  auto dt = test_load<signed long>("data/matrix_i8_t.npy");

  REQUIRE(dt.shape == expect_shape_t);
  REQUIRE(dt.data == cast_data<signed long>(expect_data_int));
  REQUIRE(dt.fortran_order == true);
}

TEST_CASE( "Load uint8 data", "[read]" ) {
  auto d = test_load<unsigned char>("data/matrix_u1.npy");

  REQUIRE(d.shape == expect_shape);
  REQUIRE(d.data == cast_data<unsigned char>(expect_data_int));
  REQUIRE(d.fortran_order == false);

  auto dt = test_load<unsigned char>("data/matrix_u1_t.npy");

  REQUIRE(dt.shape == expect_shape_t);
  REQUIRE(dt.data == cast_data<unsigned char>(expect_data_int));
  REQUIRE(dt.fortran_order == true);
}

TEST_CASE( "Load uint16 data", "[read]" ) {
  auto d = test_load<unsigned short>("data/matrix_u2.npy");

  REQUIRE(d.shape == expect_shape);
  REQUIRE(d.data == cast_data<unsigned short>(expect_data_int));
  REQUIRE(d.fortran_order == false);

  auto dt = test_load<unsigned short>("data/matrix_u2_t.npy");

  REQUIRE(dt.shape == expect_shape_t);
  REQUIRE(dt.data == cast_data<unsigned short>(expect_data_int));
  REQUIRE(dt.fortran_order == true);
}

TEST_CASE( "Load uint32 data", "[read]" ) {
  auto d = test_load<unsigned int>("data/matrix_u4.npy");

  REQUIRE(d.shape == expect_shape);
  REQUIRE(d.data == cast_data<unsigned int>(expect_data_int));
  REQUIRE(d.fortran_order == false);

  auto dt = test_load<unsigned int>("data/matrix_u4_t.npy");

  REQUIRE(dt.shape == expect_shape_t);
  REQUIRE(dt.data == cast_data<unsigned int>(expect_data_int));
  REQUIRE(dt.fortran_order == true);
}

TEST_CASE( "Load uint64 data", "[read]" ) {
  auto d = test_load<unsigned long>("data/matrix_u8.npy");

  REQUIRE(d.shape == expect_shape);
  REQUIRE(d.data == cast_data<unsigned long>(expect_data_int));
  REQUIRE(d.fortran_order == false);

  auto dt = test_load<unsigned long>("data/matrix_u8_t.npy");

  REQUIRE(dt.shape == expect_shape_t);
  REQUIRE(dt.data == cast_data<unsigned long>(expect_data_int));
  REQUIRE(dt.fortran_order == true);
}

/*
 * bool not supported
TEST_CASE( "Load bool data", "[read]" ) {
  auto d = test_load<bool>("data/bool.npy");

  REQUIRE(d.shape == expect_shape);
  REQUIRE(d.data == expect_data_bool);
  REQUIRE(d.fortran_order == false);

  auto dt = test_load<bool>("data/bool_t.npy");

  REQUIRE(dt.shape == expect_shape_t);
  REQUIRE(d.data == expect_data_bool);
  REQUIRE(dt.fortran_order == true);
}
*/

TEST_CASE( "Load _scalar_ single precision data", "[read]" ) {
  auto d = test_load<float>("data/scalar_f4.npy");

  REQUIRE(d.shape.size() == 0);
  REQUIRE(d.data.size() == 1);
  REQUIRE(d.data[0] == static_cast<float>(expect_scalar));
  REQUIRE(d.fortran_order == false);

  auto dt = test_load<float>("data/scalar_f4_t.npy");

  REQUIRE(dt.shape.size() == 0);
  REQUIRE(dt.data.size() == 1);
  REQUIRE(dt.data[0] == static_cast<float>(expect_scalar));
  REQUIRE(dt.fortran_order == false);
}

TEST_CASE( "Load _empty_ single precision data", "[read]" ) {
  auto d = test_load<float>("data/empty_f4.npy");

  REQUIRE(d.shape.size() == 2);
  REQUIRE(d.data.size() == 0);
  REQUIRE(d.fortran_order == false);

  auto dt = test_load<float>("data/empty_f4_t.npy");

  REQUIRE(dt.shape.size() == 2);
  REQUIRE(dt.data.size() == 0);
  REQUIRE(dt.fortran_order == false);
}

TEST_CASE( "Load _empty_ single precision data with wrong data type", "[read]" ) {
  REQUIRE_THROWS_WITH([](){auto d = test_load<float>("data/empty_i8.npy");}(), "formatting error: typestrings not matching");
}
