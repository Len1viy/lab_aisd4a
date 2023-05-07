cmake_minimum_required(VERSION 3.23)
project(lab_aisd4a C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_aisd4a main.c lib_tree/tree.c lib_tree/input.c lib_tree/item.c lib_tree/node.c lib_tree/timer.c)
add_executable(test1 main1.c lib_bst/bin_tree.c lib_bst/file_acces.c lib_bst/item.c lib_bst/node.c)
add_executable(lab4b lab4b.c lib_tree/tree.h lib_tree/node.h lib_tree/item.h)