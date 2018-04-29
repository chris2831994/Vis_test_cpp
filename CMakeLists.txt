cmake_minimum_required(VERSION 3.9)
project(Vis_test_cpp)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)

add_subdirectory(src_dir)