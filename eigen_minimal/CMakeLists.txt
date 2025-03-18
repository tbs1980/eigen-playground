find_package(Eigen3 3.4 REQUIRED NO_MODULE)
add_executable(eigen_minimal eigen_minimal.cpp)
target_link_libraries(eigen_minimal Eigen3::Eigen)


