enable_testing()
add_subdirectory(googletest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_executable(test1 test1.cpp)
#add_executable(test2 test2.cpp)

target_link_libraries (test1 PUBLIC gtest_main)
#target_link_libraries (test2 PUBLIC gtest_main)

add_test(NAME t1 COMMAND test1)
#add_test(NAME t2 COMMAND test2)


#source_group("test1" FILES test1.cpp)
#source_group("test2" FILES test2.cpp)