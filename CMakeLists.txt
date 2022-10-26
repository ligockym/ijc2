cmake_minimum_required(VERSION 3.16)
project(ijc2)
set(CMAKE_C_STANDARD 99)

include(GoogleTest.cmake)

# Test targets
enable_testing()


add_executable(htab_test
        htab_test.cpp
        # list your htab .c files here
        htab.h
        htab_internal.h
        htab_init.c
        htab_move.c
        htab_size.c
        htab_bucket_count.c
        htab_find.c
        htab_lookup_add.c
        htab_hash_function.c
        htab_init_item.c
        htab_erase.c
        htab_clean_item.c
        htab_free.c
        htab_clear.c
        htab_for_each.c
        # ...
        )

target_link_libraries(htab_test gtest_main)
GTEST_ADD_TESTS(htab_test "" htab_test.cpp)

add_executable(tail tail.c)
add_executable(wordcount wordcount.c io.h io.c htab.h htab_internal.h htab_init.c htab_move.c htab_size.c htab_bucket_count.c htab_find.c htab_lookup_add.c htab_hash_function.c htab_init_item.c wordcount.c htab_erase.c htab_clean_item.c htab_free.c htab_clear.c htab_for_each.c)