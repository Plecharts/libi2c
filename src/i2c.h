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

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h> // uintN_t


#ifdef __cplusplus
extern "C" {
#endif

int i2c_open(char*);
int i2c_close(int);
int i2c_select_address(int, uint8_t);
int i2c_read(int, uint8_t*, uint8_t);
int i2c_read_byte(int, uint8_t*);
int i2c_read_word(int, uint16_t*);
int i2c_write(int, uint8_t*, uint8_t);
int i2c_write_byte(int, uint8_t);
int i2c_write_word(int, uint16_t);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* I2C_H_ */
