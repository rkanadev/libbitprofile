add_definitions(-D__ABI_ENABLED__)
add_definitions(-DBOOST_PP_VARIADICS)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/MakeIncludesLink.cmake)

include_directories(${Boost_INCLUDE_DIRS} ${JSONCPP_INCLUDE_DIR} ${ETHCRYPTO_INCLUDE_DIRS} ${ETHRPC_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE SOURCES "src/*.cpp")

MakeIncludesLink()
add_library(bitprofile STATIC ${SOURCES})

if(NOT SKIP_LIBRARY_INSTALL)
    install(DIRECTORY ${PROJECT_BINARY_DIR}/include/bitprofile DESTINATION include OPTIONAL)
    install (TARGETS bitprofile ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin OPTIONAL)
endif()

