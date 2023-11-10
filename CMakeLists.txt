cmake_minimum_required(VERSION 3.5)
project("holghol" C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 90)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

file(GLOB PROJECT_HEADERS src/*.h)
file(GLOB PROJECT_SOURCES src/*.c)

add_library(holghol_lib STATIC ${PROJECT_SOURCES})
target_include_directories(holghol_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR})

if(TARGET_GROUP STREQUAL test)
	SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/tests)
	add_library(unity STATIC test/unity/unity.c)
	target_include_directories(unity PUBLIC .)

	add_executable(test_holghol_h_app test/test_holghol_h.c)
	target_link_libraries(test_holghol_h_app holghol_lib unity)
	add_test(test_holghol_h_app test_holghol_h)

	add_executable(test_utils_app test/test_utils.c)
	target_link_libraries(test_utils_app holghol_lib unity)
	add_test(test_utils_app test_utils)

else()
	add_executable(${PROJECT_NAME} "build.c" ${PROJECT_SOURCES} ${PROJECT_HEADERS})
	target_link_libraries(${PROJECT_NAME} holghol_lib)
endif()

