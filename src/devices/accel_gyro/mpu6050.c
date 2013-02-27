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
    uint8_t data;
    TWI_read_register(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_WHO_AM_I, &data, 1);

    return (data >> 1) & 0x3F; // 6 bit only! (0xxxxxx0)
}


__attribute__((always_inline))
uint8_t MPU6050_reset(void)
{
    return TWI_change_bit(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_DEVICE_RESET_BIT, 1, 1);
}


__attribute__((always_inline))
uint8_t MPU6050_reset_sensors(void)
{
    return TWI_change_bit(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_SIG_COND_RESET_BIT, 1, 1);
}


void MPU6050_set_wakeCycle(uint8_t enabled)
{
    TWI_change_bit(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CYCLE_BIT, enabled, 1);
}


void MPU6050_set_sleep(uint8_t enabled)
{
    TWI_change_bit(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, enabled, 1);
}


void MPU6050_set_tempsensor_enabled(uint8_t enabled)
{
    // 1 is actually disabled here
    TWI_change_bit(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_TEMP_DIS_BIT, !enabled, 1);
}


uint16_t MPU6050_temperature(void)
{
    uint8_t buffer[2];
    TWI_read_registers(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_TEMP_OUT_H, 2, buffer, 1);

    return (((uint16_t)buffer[0]) << 8) | buffer[1];
}



#endif // JAL_USE_ACCEL_GYRO_MPU6050_H

