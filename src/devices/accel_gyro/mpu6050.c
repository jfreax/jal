/*
    Copyright (C) 2013  Jens Dieskau <jens.dieskau@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "defines.h"
#if defined(JAL_USE_ACCEL_GYRO_MPU6050_H)

#include "mpu6050.h"
#include <io/twi.h>
#include <stdio.h>


uint8_t MPU6050_device_id(void)
{
//     printf("Start\n");
//     TWI_start(MPU6050_DEFAULT_ADDRESS, TWI_WRITE);

    printf("Write ");
    printf("%i\n", TWI_write(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_WHO_AM_I, 0));

//     printf("Start #2\n");
//     TWI_start(MPU6050_DEFAULT_ADDRESS, TWI_READ);

    printf("Read");
    
    uint8_t data;
    printf("%i\n", TWI_read(MPU6050_DEFAULT_ADDRESS, &data,1));
    return (data >> 1) & 0x3F; // 6 bit only! (0xxxxxx0)
}


void MPU6050_reset(void)
{
    //writeBit(devAddr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_DEVICE_RESET_BIT, true);

}




#endif // JAL_USE_ACCEL_GYRO_MPU6050_H
