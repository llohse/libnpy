find_package(Python3 REQUIRED COMPONENTS Interpreter)
find_package(Catch2 2.13.8...<3 CONFIG REQUIRED)

add_executable(npy-test-read test-read.cpp)
target_link_libraries(npy-test-read PRIVATE libnpy::npy Catch2::Catch2)

add_executable(npy-test-write test-write.cpp)
target_link_libraries(npy-test-write PRIVATE libnpy::npy)

add_test(NAME libnpy.prepare COMMAND Python3::Interpreter
                                     "${CMAKE_CURRENT_SOURCE_DIR}/createnpy.py")
set_tests_properties(libnpy.prepare PROPERTIES FIXTURES_SETUP libnpy_data)

add_test(NAME libnpy.read COMMAND npy-test-read)
add_test(NAME libnpy.write COMMAND npy-test-write)
set_tests_properties(libnpy.read libnpy.write PROPERTIES FIXTURES_REQUIRED
                                                         libnpy_data)
