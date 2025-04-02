cmake_minimum_required(VERSION 3.10)

project(CanonicalTest)

# Include FetchContent module
include(FetchContent)

# Fetch nlohmann/json
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.10.5  # Specify the version you want to use
)

FetchContent_MakeAvailable(json)

# Find CURL
find_package(CURL REQUIRED)

# Check if CURL is found
if (NOT CURL_FOUND)
    message(FATAL_ERROR "libcurl is required but not found. Please install it using your package manager.")
endif()

# Create the executable
add_executable(main src/main.cpp src/fetchUbuntuImage.cpp)

# Link against CURL and nlohmann/json
target_include_directories(main PRIVATE ${CURL_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR} nlohmann_json::nlohmann_json)
target_link_libraries(main PRIVATE ${CURL_LIBRARIES})

# Provide instructions for installing libcurl based on the platform
if(NOT CURL_FOUND)
    if(UNIX)
        message(STATUS "On Linux, you can install libcurl using your package manager, e.g., 'sudo apt install libcurl4-openssl-dev' or 'sudo yum install libcurl-devel'.")
    elseif(WIN32)
        message(STATUS "On Windows, please download and install libcurl from the official website or use a package manager like vcpkg.")
    elseif(APPLE)
        message(STATUS "On macOS, you can install libcurl using Homebrew with 'brew install curl'.")
    endif()
endif()cmake_minimum_required(VERSION 3.10)

project(CanonicalTest)

find_package(CURL REQUIRED)

add_executable(main src/main.cpp src/fetchUbuntuImage.cpp)

target_include_directories(main PRIVATE ${CURL_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
target_link_libraries(main PRIVATE ${CURL_LIBRARIES})
