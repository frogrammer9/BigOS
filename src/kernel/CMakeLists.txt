SETUP_EXECUTABLE(kernel)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions(kernel PRIVATE __DEBUG__)
	target_compile_definitions(kernel PRIVATE __LOGLVL__=3)
else()
	target_compile_definitions(kernel PRIVATE __LOGLVL__=1)
endif()

target_link_libraries(kernel PRIVATE stdbigos)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
target_link_libraries(kernel PRIVATE Debug)
endif()

target_link_options(kernel PRIVATE -static-pie -e kinit)
target_compile_options(kernel PRIVATE -fPIE -static)

COMPILE_BINARY(kernel)
ADD_QEMU_TARGET(kernel)

