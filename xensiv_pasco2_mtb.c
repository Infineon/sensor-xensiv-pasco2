/***********************************************************************************************//**
 * \file xensiv_pasco2_mtb.c
 *
 * Description: This file contains the MTB platform functions implementation 
 *              for interacting with the XENSIV™ PAS CO2 sensor.
 *
 ***************************************************************************************************
 * \copyright
 * Copyright 2021 Infineon Technologies AG
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

#if defined(CY_USING_HAL)

#include "cyhal_system.h"

#include "xensiv_pasco2_mtb.h"

#define XENSIV_PASCO2_I2C_TIMEOUT_MS            (500U)
#define XENSIV_PASCO2_UART_TIMEOUT_MS           (500U)

#define XENSIV_PASCO2_MEAS_RATE_S               (10)

#define XENSIV_PASCO2_ERROR(x)                  (((x) == XENSIV_PASCO2_OK) ? CY_RSLT_SUCCESS :\
                                                 CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2, (x)))

cy_rslt_t xensiv_pasco2_mtb_init_i2c(xensiv_pasco2_t * dev, cyhal_i2c_t * i2c)
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

cy_rslt_t xensiv_pasco2_mtb_init_uart(xensiv_pasco2_t * dev, cyhal_uart_t * uart)
{
    CY_ASSERT(dev != NULL);
    CY_ASSERT(uart != NULL);

    int32_t res = xensiv_pasco2_init_uart(dev, uart);
    if (XENSIV_PASCO2_OK == res)
    {
        res = xensiv_pasco2_start_continuous_mode(dev, XENSIV_PASCO2_MEAS_RATE_S);
    }
    return XENSIV_PASCO2_ERROR(res);
}

cy_rslt_t xensiv_pasco2_mtb_interrupt_init(const xensiv_pasco2_t * dev, 
                                           const xensiv_pasco2_interrupt_config_t int_config, 
                                           uint16_t alarm_threshold,
                                           cyhal_gpio_t pin, 
                                           uint8_t intr_priority,
                                           cyhal_gpio_event_callback_t callback,
                                           void* callback_arg)
{
    CY_ASSERT(dev != NULL);

    int32_t res  = xensiv_pasco2_set_interrupt_config(dev, int_config);

    if (XENSIV_PASCO2_OK == res)
    {
        res = xensiv_pasco2_set_alarm_threshold(dev, alarm_threshold);
    }
    
    if (XENSIV_PASCO2_OK == res)
    {
        CY_ASSERT(callback != NULL);

        cy_rslt_t status = cyhal_gpio_init(pin, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, (int_config.b.int_typ == (uint32_t)XENSIV_PASCO2_INTERRUPT_TYPE_LOW_ACTIVE) ? true : false);
        if (CY_RSLT_SUCCESS == status)
        {
        #if defined(CYHAL_API_VERSION) && (CYHAL_API_VERSION >= 2)
            cyhal_gpio_callback_data_t cb_data =
            {
                .callback = callback,
                .callback_arg = callback_arg
            };
            cyhal_gpio_register_callback(pin, &cb_data);
        #else
            cyhal_gpio_register_callback(pin, callback, callback_arg);
        #endif
            cyhal_gpio_enable_event(pin, (int_config.b.int_typ == (uint32_t)XENSIV_PASCO2_INTERRUPT_TYPE_LOW_ACTIVE) ? CYHAL_GPIO_IRQ_FALL : CYHAL_GPIO_IRQ_RISE, intr_priority, true);
        }

        return status;
    }

    return XENSIV_PASCO2_ERROR(res);
}

cy_rslt_t xensiv_pasco2_mtb_read(const xensiv_pasco2_t * dev, uint16_t press_ref, uint16_t * co2_ppm_val)
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

/**************************** driver platform specific implementation  **********************************/

int32_t xensiv_pasco2_plat_i2c_transfer(void * ctx, uint16_t dev_addr, const uint8_t * tx_buffer, size_t tx_len, uint8_t * rx_buffer, size_t rx_len)
{
    CY_ASSERT(ctx != NULL);
    CY_ASSERT(tx_buffer != NULL);

    cyhal_i2c_t * i2c = (cyhal_i2c_t *)ctx;
    bool send_stop = (rx_buffer != NULL) ? false : true;
    cy_rslt_t result = cyhal_i2c_master_write(i2c, dev_addr, tx_buffer, tx_len, XENSIV_PASCO2_I2C_TIMEOUT_MS, send_stop);

    if ((CY_RSLT_SUCCESS == result) && (rx_buffer != NULL))
    {
        result = cyhal_i2c_master_read(i2c, dev_addr, rx_buffer, rx_len, XENSIV_PASCO2_I2C_TIMEOUT_MS, true);
    }

    return (CY_RSLT_SUCCESS == result)
        ? XENSIV_PASCO2_OK
        : XENSIV_PASCO2_ERR_COMM;
}

int32_t xensiv_pasco2_plat_uart_read(void * ctx, uint8_t * data, size_t len)
{
    CY_ASSERT(ctx != NULL);
    CY_ASSERT(data != NULL);

    cy_rslt_t result = XENSIV_PASCO2_ERR_COMM;

    cyhal_uart_t * uart = (cyhal_uart_t *)ctx;
    uint32_t timeout = XENSIV_PASCO2_UART_TIMEOUT_MS;
    while ((cyhal_uart_readable(uart) < len) && (timeout > 0U))
    {
        (void)cyhal_system_delay_ms(1);
        timeout--;
    }

    size_t xfer_len = len;
    if (timeout != 0U)
    {
        result = cyhal_uart_read(uart, data, &xfer_len);
    }

    return ((CY_RSLT_SUCCESS == result) && (len == xfer_len)) ? 
            XENSIV_PASCO2_OK : 
            XENSIV_PASCO2_ERR_COMM;
}

int32_t xensiv_pasco2_plat_uart_write(void * ctx, uint8_t * data, size_t len)
{
    CY_ASSERT(ctx != NULL);
    CY_ASSERT(data != NULL);

    cy_rslt_t result = XENSIV_PASCO2_ERR_COMM;

    cyhal_uart_t * uart = (cyhal_uart_t *)ctx;

    (void)cyhal_uart_clear(uart);

    size_t xfer_len = len;
    result = cyhal_uart_write(uart, data, &xfer_len);

    return ((CY_RSLT_SUCCESS == result) && (len == xfer_len)) ? 
            XENSIV_PASCO2_OK : 
            XENSIV_PASCO2_ERR_COMM;
}

void xensiv_pasco2_plat_delay(uint32_t ms)
{
    (void)cyhal_system_delay_ms(ms);
}

uint16_t xensiv_pasco2_plat_htons(uint16_t x)
{
    return __REV16(x);
}

void xensiv_pasco2_plat_assert(int expr)
{
    CY_ASSERT(expr);
}

#endif // defined(CY_USING_HAL)
