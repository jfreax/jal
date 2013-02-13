cmake_minimum_required(VERSION 2.8)

# Project
project(simpletests)

# Version number
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

# Settings
include(settings.cmake)

# Add header location
include_directories(${CMAKE_SOURCE_DIR}/extern/)
include_directories(${CMAKE_SOURCE_DIR}/src/)

# Include avr makefile
set(CMAKE_SYSTEM_NAME avr)
include(avr.cmake)

#enable_language(ASM)


# Source files
add_executable(simpletests
  src/main.c
  src/printf.c
  
  src/io/uart.c
  src/io/spi.c
  src/io/twi.c
  
  src/devices/eeprom/spi_eeprom.c
)



# Doygen documentation
# Add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(doc
      ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/doc/Doxyfile
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
else(DOXYGEN_FOUND)
    message(WARNING "No doxygen package found")
endif(DOXYGEN_FOUND)