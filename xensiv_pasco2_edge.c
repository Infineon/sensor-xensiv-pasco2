/***********************************************************************************************//**
 * \file xensiv_pasco2_mtb.c
 *
 * Description: This file contains the MTB platform functions implementation
 *              for interacting with the XENSIV PAS CO2 sensor.
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

#ifdef COMPONENT_MTB_HAL

#include "mtb_hal_system.h"


#include "xensiv_pasco2_edge.h"

#define XENSIV_PASCO2_I2C_TIMEOUT_MS            (500U)
#define XENSIV_PASCO2_UART_TIMEOUT_MS           (500U)

#define XENSIV_PASCO2_MEAS_RATE_S               (10)

#define XENSIV_PASCO2_ERROR(x)                  (((x) == XENSIV_PASCO2_OK) ? CY_RSLT_SUCCESS :\
                                                 CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2, (x)))


cy_rslt_t xensiv_pasco2_mtb_init_i2c(xensiv_pasco2_t* dev, mtb_hal_i2c_t* i2c)
{
    CY_ASSERT(dev != NULL);
    CY_ASSERT(i2c != NULL);


    int32_t res = xensiv_pasco2_init_i2c(dev, i2c);
    if (XENSIV_PASCO2_OK == res)
    {
        res = xensiv_pasco2_start_continuous_mode(dev, XENSIV_PASCO2_MEAS_RATE_S);
    }
    return XENSIV_PASCO2_ERROR(res);
}


cy_rslt_t xensiv_pasco2_mtb_read(const xensiv_pasco2_t* dev, uint16_t press_ref,
                                 uint16_t* co2_ppm_val)
{
    CY_ASSERT(dev != NULL);
    CY_ASSERT(co2_ppm_val != NULL);


    int32_t res = xensiv_pasco2_get_result(dev, co2_ppm_val);
    if (XENSIV_PASCO2_OK == res)
    {
        res = xensiv_pasco2_set_pressure_compensation(dev, press_ref);
    }

    return XENSIV_PASCO2_ERROR(res);
}


/**************************** driver platform specific implementation
 **********************************/

int32_t xensiv_pasco2_plat_i2c_transfer(void* ctx, uint16_t dev_addr, const uint8_t* tx_buffer,
                                        size_t tx_len, uint8_t* rx_buffer, size_t rx_len)
{
    CY_ASSERT(ctx != NULL);
    CY_ASSERT(tx_buffer != NULL);

    mtb_hal_i2c_t* i2c = (mtb_hal_i2c_t*)ctx;
    bool send_stop = (rx_buffer != NULL) ? false : true;
    cy_rslt_t result =
        mtb_hal_i2c_controller_write(i2c, dev_addr, tx_buffer, (uint16_t)(tx_len & 0xffffU),
                                     XENSIV_PASCO2_I2C_TIMEOUT_MS, send_stop);

    if ((CY_RSLT_SUCCESS == result) && (rx_buffer != NULL))
    {
        send_stop = true;
        result = mtb_hal_i2c_controller_read(i2c, dev_addr, rx_buffer, (uint16_t)(rx_len & 0xffffU),
                                             XENSIV_PASCO2_I2C_TIMEOUT_MS, send_stop);
    }

    return (CY_RSLT_SUCCESS == result)
        ? XENSIV_PASCO2_OK
        : XENSIV_PASCO2_ERR_COMM;
}


int32_t xensiv_pasco2_plat_uart_read(void* ctx, uint8_t* data, size_t len)
{
    return XENSIV_PASCO2_ERR_COMM;
}


int32_t xensiv_pasco2_plat_uart_write(void* ctx, uint8_t* data, size_t len)
{
    return XENSIV_PASCO2_ERR_COMM;
}


void xensiv_pasco2_plat_delay(uint32_t ms)
{
    (void)mtb_hal_system_delay_ms(ms);
}


uint16_t xensiv_pasco2_plat_htons(uint16_t x)
{
    return (uint16_t)__REV16(x);
}


void xensiv_pasco2_plat_assert(int expr)
{
    CY_ASSERT(expr);
    (void)expr; /* make release build */
}


#endif // ifdef COMPONENT_MTB_HAL
