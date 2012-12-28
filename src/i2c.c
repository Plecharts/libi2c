/**
 * @file
 * @author  Jaroslav Peska
 * @version 0.1
 *
 * @section LICENSE
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * @section DESCRIPTION
 *
 * C library aiming to provide clean and easy interface for I2C buses.
 */

#ifdef __linux__
    #include <fcntl.h> // open()
    #include <linux/i2c-dev.h> // Some I2C constants
    #include <sys/ioctl.h> // ioctl()
    #include <unistd.h> // read(), write(), close()
#endif

#include <stdint.h> // uintN_t

#include "i2c.h"

/**
 * Open the I2C interface.
 *
 * @param interface_name Full path to the I2C interface file (/dev/i2c-X).
 * @return File handle on succes, negative value on error.
 */
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

/**
 * Close the I2C interface.
 *
 * @param file_handle An int file handle to already open I2C interface.
 * @return 0 on success, negative value on error.
 */
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

/**
 * Select a target I2C device address on a bus opened by the file handle.
 *
 * @param file_handle A file handle of an I2C bus
 *                    opened by the i2c_open(char*) function.
 * @param address A 7-bit address of the target device.
 * @return 0 on success, negative value on error.
 */
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

/**
 * Read a block of bytes from the target device.
 *
 * @param file_handle A file handle of an I2C bus
 *                    opened by the i2c_open(char*) function.
 * @param destination A pointer to an uint8_t array where the read bytes
 *                    will be stored. The array will NOT be NULL terminated.
 * @param amount An amount of bytes to be read.
 * @return Amount of bytes read, negative value on error.
 */
int i2c_read(int file_handle, uint8_t* destination, uint8_t amount)
{
    #ifdef __linux__ // Linux
        return read(file_handle, destination, amount);
    #else // Unsupported platform
        return -1; //TODO: Assign specific return code
    #endif
}

/**
 * Read a byte from the target device.
 *
 * @param file_handle A file handle of an I2C bus
 *                    opened by the i2c_open(char*) function.
 * @param destination A pointer to an uint8_t variable where the byte
 *                    will be stored.
 * @return 0 on success, negative value on error.
 */
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

/**
 * Read a word (2 bytes) from the target device.
 *
 * @param file_handle A file handle of an I2C bus
 *                    opened by the i2c_open(char*) function.
 * @param destination A pointer to an uint16_t variable where the word
 *                    will be stored.
 * @return 0 on success, negative value on error.
 */
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

/**
 * Write a block of bytes to the target device.
 *
 * @param file_handle A file handle of an I2C bus
 *                    opened by the i2c_open(char*) function.
 * @param source A pointer to an uint8_t array containing the
 *               bytes to be written.
 * @param amount An amount of bytes to be written
 *               from the source array to the target device.
 * @return Amount of bytes written, negative value on error.
 */
int i2c_write(int file_handle, uint8_t* source, uint8_t amount)
{
    #ifdef __linux__ // Linux
        return write(file_handle, source, amount);
    #else // Unsupported platform
        return -1; //TODO: Assign specific return code
    #endif
}

/**
 * Write a byte to the target device.
 *
 * @param file_handle A file handle of an I2C bus
 *                    opened by the i2c_open(char*) function.
 * @param value A pointer to an uint8_t variable
 *              containing the byte to be written.
 * @return 0 on success, negative value on error.
 */
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

/**
 * Write a word (2 bytes) to the target device.
 *
 * @param file_handle A file handle of an I2C bus
 *                    opened by the i2c_open(char*) function.
 * @param word_value A pointer to an uint16_t variable
 *                   containing the word to be written.
 * @return 0 on success, negative value on error.
 */
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
