cmake_minimum_required(VERSION 2.8)

SET(CMAKE_SYSTEM_NAME avr)

FILE(GLOB WILDCARD_PORT /dev/ttyUSB*)
SET(PROGR_PORT ${WILDCARD_PORT})

IF(NOT PROGR_PORT)
  SET(PROGR_PORT usb)
ENDIF(NOT PROGR_PORT)


IF(NOT MCU OR NOT PROG_ID OR NOT PROG_PART)
        message(FATAL_ERROR  "Specify all required variables (MCU PROG_ID PROGR_PORT PROG_PART)")
ENDIF(NOT MCU OR NOT PROG_ID OR NOT PROG_PART)

# compiler additional options
SET(CXXSTANDARD "-std=c++0x")
SET(CSTANDARD "-std=gnu99")
SET(COPT "-O2")
SET(CWARN "-Wall -Wstrict-prototypes")
SET(CXXWARN "-Wall")
SET(DEBUGFLAGS "-gstabs -g")
SET(HEXFORMAT "ihex")
SET(CMAKE_FIND_ROOT_PATH  "/usr/avr")

SET(CMAKE_C_COMPILER avr-gcc)
SET(CMAKE_CXX_COMPILER avr-g++)

SET(CTUNING "-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums")
SET(CXXTUNING "-fno-exceptions -fno-rtti -funsigned-char -funsigned-bitfields -fshort-enums")

SET(CFLAGS   "-mmcu=${MCU} -DF_CPU=${FCPU} ${DEBUGFLAGS} ${CDEFS} ${COPT} ${CWARN} ${CSTANDARD} ${CTUNING}")
SET(CXXFLAGS "-mmcu=${MCU} -DF_CPU=${FCPU} ${DEBUGFLAGS} ${CDEFS} ${COPT} ${CXXWARN} ${CXXSTANDARD} ${CXXTUNING}")

SET(CMAKE_C_FLAGS ${CFLAGS})
SET(CMAKE_CXX_FLAGS ${CXXFLAGS})

SET(LDFLAGS "-Wl,-Map,${PROJECT_NAME}.map -lm")

SET(CMAKE_EXE_LINKER_FLAGS ${LDFLAGS})
SET(AVR_GCC_INCLUDE_ROOT_DIR  ${CMAKE_FIND_ROOT_PATH}/include)

SET(AVR_GCC_INCLUDE_DIR
        ${AVR_GCC_INCLUDE_ROOT_DIR}
        ${AVR_GCC_INCLUDE_ROOT_DIR}/avr
        ${AVR_GCC_INCLUDE_ROOT_DIR}/compat
        ${AVR_GCC_INCLUDE_ROOT_DIR}/util
)
include_directories(${AVR_GCC_INCLUDE_DIR})

SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)


SET(GDBINITFILE "gdb-init")

add_custom_target(gdbinit
        echo file ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME} > ${GDBINITFILE}
        COMMAND echo target remote localhost:1212 >> ${GDBINITFILE}
        COMMAND echo load >> ${GDBINITFILE}
        COMMAND echo break main >> ${GDBINITFILE}
        COMMAND echo continue >> ${GDBINITFILE}
        VERBATIM)

add_custom_target(reset
        COMMAND echo 0 > ${PROGR_PORT}
        VERBATIM)


find_program(AVRDUDE avrdude)
IF(${AVRDUDE-NOTFOUND})
        message(WARNING "'avrdude' program not found. 'upload' and 'info' targets will not be available!")
ELSE(${AVRDUDE-NOTFOUND})

add_custom_target(upload
        ${AVRDUDE}
                #-v -v -v -v
                -c ${PROG_ID}
                -p ${PROG_PART}
                -P ${PROGR_PORT}
                #-e
                -b ${UPLOAD_SPEED}
                -D
                -U flash:w:${PROJECT_NAME}.hex
        DEPENDS ${PROJECT_NAME}.hex ${PROJECT_NAME}.ee.hex
        VERBATIM)

add_custom_target(info
        ${AVRDUDE} -v
                -c ${PROG_ID}
                -p ${PROG_PART}
                -P ${PROGR_PORT} -e
                -U -U hfuse:r:high.txt:r -U lfuse:r:low.txt:r
        VERBATIM)

add_custom_command(
        OUTPUT ${PROJECT_NAME}.hex
        COMMAND /usr/bin/${CMAKE_SYSTEM_NAME}-objcopy --strip-all -j .text -j .data -O ${HEXFORMAT} ${PROJECT_NAME} ${PROJECT_NAME}.hex
        DEPENDS ${PROJECT_NAME}
        VERBATIM
)

add_custom_command(
        OUTPUT ${PROJECT_NAME}.ee.hex
        COMMAND /usr/bin/${CMAKE_SYSTEM_NAME}-objcopy --strip-all -j .eeprom --change-section-lma .eeprom=0
                           -O ${HEXFORMAT} ${PROJECT_NAME} ${PROJECT_NAME}.ee.hex
        DEPENDS ${PROJECT_NAME}
        VERBATIM
)

ENDIF(${AVRDUDE-NOTFOUND})
