project(theater CXX)

cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")

set(THEATER_INCLUDE_DIRS "include")

find_package(NlohmannJson)

if (NOT NLOHMANN_JSON_INCLUDE_DIR)
  set(NLOHMANN_JSON_DIR "nlohmann-json-3.11.3")

  file(DOWNLOAD https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp
      "${CMAKE_BINARY_DIR}/deps/${NLOHMANN_JSON_DIR}/nlohmann/json.hpp"
      STATUS NLOHMANN_JSON_DOWNLOAD_STATUS_LIST LOG NLOHMANN_JSON_DOWNLOAD_LOG
      SHOW_PROGRESS)

  list(GET NLOHMANN_JSON_DOWNLOAD_STATUS_LIST 0 NLOHMANN_JSON_DOWNLOAD_STATUS)

  if (NLOHMANN_JSON_DOWNLOAD_STATUS EQUAL 0)

    file(SHA256 "${CMAKE_BINARY_DIR}/deps/${NLOHMANN_JSON_DIR}/nlohmann/json.hpp" NLOHMANN_JSON_LOCAL_HASH)

    set(NLOHMANN_JSON_EXPECTED_HASH "9bea4c8066ef4a1c206b2be5a36302f8926f7fdc6087af5d20b417d0cf103ea6")

    if (NLOHMANN_JSON_LOCAL_HASH STREQUAL NLOHMANN_JSON_EXPECTED_HASH)
      set(NLOHMANN_JSON_INCLUDE_DIR "${CMAKE_BINARY_DIR}/deps/${NLOHMANN_JSON_DIR}")

      set(THEATER_INCLUDE_DIRS ${THEATER_INCLUDE_DIRS} "${NLOHMANN_JSON_INCLUDE_DIR}")

      message(STATUS
          "Successfully downloaded nlohmann json into ${CMAKE_BINARY_DIR}/deps/${NLOHMANN_JSON_DIR}/")
    else ()
      message(FATAL_ERROR "Error checking hash for nlohmann json!"
        " Try removing the directory ${CMAKE_BINARY_DIR}/deps and reconfiguring.")
    endif ()
  else ()
    list(GET NLOHMANN_JSON_DOWNLOAD_STATUS_LIST 1 NLOHMANN_JSON_DOWNLOAD_ERROR)
    message(FATAL_ERROR
        "Could not download nlohmann::json! Error code ${NLOHMANN_JSON_DOWNLOAD_STATUS}: ${NLOHMANN_JSON_DOWNLOAD_ERROR}!"
        "  Error log: ${NLOHMANN_JSON_DOWNLOAD_LOG}")
  endif ()
else ()
  set(THEATER_INCLUDE_DIRS ${THEATER_INCLUDE_DIRS} "${NLOHMANN_JSON_INCLUDE_DIR}")
endif ()

include_directories(${THEATER_INCLUDE_DIRS})

add_executable(
  theater
  # include/theater.hpp
  # include/theater_algorithms_edit.hpp
  # include/theater_algorithms_print.hpp
  # include/theater_algorithms_rate.hpp
  # include/theater_algorithms_sort.hpp
  # include/theater_loading.hpp
  # include/io_helpers.hpp
  src/main/main.cpp
)