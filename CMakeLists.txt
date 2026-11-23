cmake_minimum_required(VERSION 3.23)

project(
  libnpy
  VERSION 1.0.1
  DESCRIPTION "C++ library for reading and writing of numpy's .npy files"
  HOMEPAGE_URL "https://github.com/llohse/libnpy"
  LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

option(BUILD_TESTING "Build tests" OFF)
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

add_library(npy INTERFACE)
add_library(libnpy::npy ALIAS npy)

target_compile_features(npy INTERFACE cxx_std_14)
target_sources(npy INTERFACE FILE_SET HEADERS BASE_DIRS include FILES
                             include/npy.hpp)

install(
  TARGETS npy
  EXPORT libnpy-targets
  FILE_SET HEADERS
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/libnpy")

install(
  EXPORT libnpy-targets
  NAMESPACE libnpy::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libnpy)

configure_package_config_file(
  cmake/libnpy-config.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/libnpy-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libnpy)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/libnpy-config-version.cmake
  COMPATIBILITY SameMajorVersion ARCH_INDEPENDENT)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libnpy-config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/libnpy-config-version.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libnpy)
