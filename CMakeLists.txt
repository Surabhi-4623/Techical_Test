cmake_minimum_required(VERSION 3.10)

project(CanonicalTest)

# Find CURL
find_package(CURL REQUIRED)

if(NOT CURL_FOUND)
    if(UNIX)
        message(STATUS "On Linux, you can install libcurl using your package manager, e.g., 'sudo apt install libcurl4-openssl-dev' or 'sudo yum install libcurl-devel'.")
    elseif(WIN32)
        message(STATUS "On Windows, please download and install libcurl from the official website or use a package manager like vcpkg.")
    elseif(APPLE)
        message(STATUS "On macOS, you can install libcurl using Homebrew with 'brew install curl'.")
    endif()
endif()

# Create the executable
add_executable(main src/main.cpp src/fetchUbuntuImage.cpp)

# Include the JSON header file
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR})

# Include CURL headers
target_include_directories(main PRIVATE ${CURL_INCLUDE_DIRS})

# Link against CURL
target_link_libraries(main PRIVATE ${CURL_LIBRARIES})