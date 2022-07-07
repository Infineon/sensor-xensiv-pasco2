/***********************************************************************************************//**
 * \file xensiv_pasco2_platform.h
 *
 * Description: XENSIV PAS CO2 sensor driver platform dependencies
 *
 ***************************************************************************************************
 * \copyright
 * Copyright 2021-2022 Infineon Technologies AG
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **************************************************************************************************/

#ifndef XENSIV_PASCO2_PLATFORM_H_
#define XENSIV_PASCO2_PLATFORM_H_

/**
 * \addtogroup group_board_libs_platform XENSIV PAS CO2 Sensor platform functions
 * \{
 * XENSIV PAS CO2 Sensor platform functions.
 * 
 * To adapt the driver to your platform you need to provide an implementation for the functions
 * declared in this file. See example implementation in xensiv_pasco2_mtb.c using the PSoC6 HAL.
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Target platform-specific function to perform I2C write/read transfer.
 * Synchronously writes a block of data and optionally receive a block of data.
 * @param[in] ctx Target platform object
 * @param[in] dev_addr device address (7-bit)
 * @param[in] tx_buffer I2C send data
 * @param[in] tx_len I2C send data size
 * @param[in] rx_buffer I2C receive data @note Can be NULL to indicate no read access.
 * @param[in] rx_len I2C receive data size
 * @return XENSIV_PASCO2_OK if the I2C transfer was successful; an error indicating what went wrong otherwise
 */
int32_t xensiv_pasco2_plat_i2c_transfer(void * ctx, uint16_t dev_addr, const uint8_t * tx_buffer, size_t tx_len, uint8_t * rx_buffer, size_t rx_len);

/**
 * @brief Target platform-specific function to read over UART
 *
 * @param[in] ctx UART object
 * @param[out] data Receive buffer
 * @param[in] len Number of bytes to receive
 * @return XENSIV_PASCO2_OK if the UART read was successful; an error indicating what went wrong otherwise
 */
int32_t xensiv_pasco2_plat_uart_read(void *ctx, uint8_t * data, size_t len);

/**
 * @brief Target platform-specific function to write over UART
 *
 * @param[in] ctx UART object
 * @param[in] data Transmit buffer
 * @param[in] len Number of bytes to transmit
 * @return XENSIV_PASCO2_OK if the UART write was successful; an error indicating what went wrong otherwise
 */
int32_t xensiv_pasco2_plat_uart_write(void *ctx, uint8_t * data, size_t len);

/**
 * @brief Target platform-specific function that waits for a specified time period in milliseconds
 *
 * @param[in] ms Number of miliseconds to wait for
 */
void xensiv_pasco2_plat_delay(uint32_t ms);

/**
 * @brief Target platform-specific function to reverse the byte order (16-bit)
 * A sample implementation would look like 
 * \code
 *  return ((uint16_t)(((x & 0x00ffU) << 8) |
 *                     ((x & 0xff00U) >> 8)));
 * \endcode
 * @param[in] x Value to reverse
 * @return Reversed value
 */
uint16_t xensiv_pasco2_plat_htons(uint16_t x);

/**
 * @brief Target platform-specific function that implements a runtime assertion; used to verify the assumptions made by the program and take appropiate actions if assumption is false
 *
 * @param[in] expr Expression to be verified
 */
void xensiv_pasco2_plat_assert(int expr);

#ifdef __cplusplus
}
#endif

/** \} group_board_libs_platform */

#endif // ifndef XENSIV_PASCO2_PLATFORM_H_
