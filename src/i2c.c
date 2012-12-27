/*
    libi2c - Library aiming to provide I2C functionality for C programs.
    Copyright (C) 2012  Jaroslav Peska

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

#ifdef __linux__
    #include <fcntl.h> // open()
    #include <linux/i2c-dev.h> // Some I2C constants
    #include <sys/ioctl.h> // ioctl()
    #include <unistd.h> // read(), write(), close()
#endif

#include <stdint.h> // uintN_t

#include "i2c.h"

int i2c_open(char* interface_name)
{
    #ifdef __linux__ // Linux
        int file_handle = open((const char*) interface_name, O_RDWR);

        if(file_handle < 0)
        {
            //TODO: Assign specific return code
            return -1;
        }
        else return file_handle;
    #else // Unsupported platform
        return -1; //TODO: Assign specific return code
    #endif
}

int i2c_close(int file_handle)
{
    #ifdef __linux__ // Linux
        if(close(file_handle) < 0)
        {
            return -1; //TODO: Assign specific return code
        }
        else return 0;
    #else // Unsupported platform
        return -1; //TODO: Assign specific return code
    #endif
}

int i2c_select_address(int file_handle, uint8_t address)
{
    #ifdef __linux__ // Linux
        if(ioctl(file_handle, I2C_SLAVE, address) < 0)
        {
            return -1; // Could not select address
        }
        else return 0;
    #else // Unsupported platform
        return -1; //TODO: Assign specific return code
    #endif
}

int i2c_read(int file_handle, uint8_t* destination, uint8_t amount)
{
    #ifdef __linux__ // Linux
        return read(file_handle, destination, amount);
    #else // Unsupported platform
        return -1; //TODO: Assign specific return code
    #endif
}

int i2c_read_byte(int file_handle, uint8_t* destination)
{
    #ifdef __linux__ // Linux
        int return_value = i2c_read(file_handle, destination, 1);

        if(return_value < 0) return -1; // Something happened
        else if(return_value != 1) return -1; // No byte was received
        else return 0;
    #else // Unsupported platform
        return -1; //TODO: Assign specific return code
    #endif
}

int i2c_read_word(int file_handle, uint16_t* destination)
{
    #ifdef __linux__ // Linux
        uint8_t bytes_received[2];
        int16_t return_value = i2c_read(file_handle, bytes_received, 2);

        if(return_value < 0) return -1; // Something happened
        else if(return_value != 2) return -1; // We didn't receive 2 bytes
        else
        {
            // Shift first byte eight bits to the left and add second byte
            *destination = ((bytes_received[0] << 8) + bytes_received[1]);
            return 0;
        }
    #else // Unsupported platform
        return -1; //TODO: Assign specific return code
    #endif
}

int i2c_write(int file_handle, uint8_t* source, uint8_t amount)
{
    #ifdef __linux__ // Linux
        return write(file_handle, source, amount);
    #else // Unsupported platform
        return -1; //TODO: Assign specific return code
    #endif
}

int i2c_write_byte(int file_handle, uint8_t value)
{
    #ifdef __linux__ // Linux
        int return_value = i2c_write(file_handle, &value, 1);

        if(return_value < 0) return -1; // Something happened
        else if(return_value != 1) return -1; // No byte was sent
        else return 0;
    #else // Unsupported platform
        return -1; //TODO: Assign specific return code
    #endif
}

int i2c_write_word(int file_handle, uint16_t word_value)
{
    #ifdef __linux__ // Linux
        // Split the word into two bytes
        uint8_t byte_value[2];
        byte_value[0] = ((word_value & 0xFF00) >> 8);
        byte_value[1] = (word_value & 0x00FF);

        int16_t return_value = i2c_write(file_handle, byte_value, 2);

        if(return_value < 0) return -1; // Something happened
        else if(return_value != 2) return -1; // We didn't send 2 bytes
        else return 0;
    #else // Unsupported platform
        return -1; //TODO: Assign specific return code
    #endif
}
