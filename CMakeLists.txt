cmake_minimum_required(VERSION 2.8)
project(simpletests)

add_executable(simpletests
  main.cpp
)


SET(CMAKE_SYSTEM_NAME avr)
SET(MCU atmega1280)   # atmega328p / atmega1280
SET(PROG_PART ${MCU}) # m328p / atmega1280
#SET(PROG_ID avrisp2)
SET(PROG_ID arduino)
SET(PROGR_PORT "/dev/ttyUSB1")
set(FCPU "16000000")
set(UPLOAD_SPEED "57600")



INCLUDE(CMakeLists_AVR.txt)