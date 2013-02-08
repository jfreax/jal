cmake_minimum_required(VERSION 2.8)

# Project
project(simpletests)

# Programmer specific
SET(PROG_ID arduino) # avrisp2

# Add header location
include_directories(${CMAKE_SOURCE_DIR}/extern/)

# Include avr makefile
INCLUDE(cmake/1280.cmake)

# Add source directory
add_subdirectory(extern)

# Source files
add_executable(simpletests
  src/main.c
)

TARGET_LINK_LIBRARIES(simpletests
  uart
)




# Add documentation
# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(doc
      ${DOXYGEN_EXECUTABLE} ${sfxaedeeui_SOURCE_DIR}/doc/Doxyfile
      WORKING_DIRECTORY ${sfxaedeeui_SOURCE_DIR}
      COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
else(DOXYGEN_FOUND)
    message(WARNING "No doxygen package found")
endif(DOXYGEN_FOUND)