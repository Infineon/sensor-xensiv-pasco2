/***********************************************************************************************//**
 * \file xensiv_pasco2_mtb.h
 *
 * Description: This file contains the MTB platform functions declarations
 *              for interacting with the XENSIV™ PAS CO2 sensor.
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

#ifndef XENSIV_PASCO2_MTB_H_
#define XENSIV_PASCO2_MTB_H_

#include "cy_result.h"

#include "xensiv_pasco2.h"

/**
 * \addtogroup group_board_libs_mtb XENSIV™ PAS CO2 sensor ModusToolbox&trade; interface
 * \{
 * Basic set of APIs for interacting with the XENSIV™ PAS CO2 sensor. This
 * provides basic initialization and access to the CO2 ppm value.
 * It also provides access to the base XENSIV™ PAS CO2 driver for full
 * control.
 *
 * \note XENSIV™ PAS CO2 sensor support requires delays. If the RTOS_AWARE component is set or
 * CY_RTOS_AWARE is defined, the HAL driver will defer to the RTOS for delays.
 * Because of this, make sure that the RTOS scheduler has started before calling any functions.
 *
 * \section subsection_board_libs_snippets Code snippets
 * \subsection subsection_board_libs_snippet_1 Snippet 1: Simple initialization with I2C
 * The following snippet initializes an I2C instance and the XENSIV™ PAS CO2 sensor, and then reads
 * from the XENSIV™ PAS CO2 sensor.
 * \snippet xensiv_pasco2_mtb_example.c snippet_xensiv_pasco2_i2c_init
 *
 * \subsection subsection_board_libs_snippet_2 Snippet 2: XENSIV™ PAS CO2 sensor interrupt configuration
 * The following snippet demonstrates how to configure a XENSIV™ PAS CO2 sensor interrupt.
 * \snippet xensiv_pasco2_mtb_example.c snippet_xensiv_pasco2_configure_interrupt
 */

#if defined(CY_USING_HAL)
#include "cyhal_gpio.h"
#include "cyhal_i2c.h"
#include "cyhal_uart.h"

/************************************** Macros *******************************************/

#ifndef CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2
#define CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2 0x01CA
#endif

/** Result code indicating a communication error */
#define XENSIV_PASCO2_RSLT_ERR_COMM\
    (CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2, XENSIV_PASCO2_ERR_COMM))

/** Result code indicating that an unexpectedly large I2C write was requested which is not supported */
#define XENSIV_PASCO2_RSLT_ERR_WRITE_TOO_LARGE\
    (CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2, XENSIV_PASCO2_ERR_WRITE_TOO_LARGE))

/** Result code indicating that the sensor is not yet ready after reset */
#define XENSIV_PASCO2_RSLT_ERR_NOT_READY\
    (CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2, XENSIV_PASCO2_ERR_NOT_READY))

/** Result code indicating whether an invalid command has been received by the serial communication interface */
#define XENSIV_PASCO2_RSLT_ICCERR\
    (CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2, XENSIV_PASCO2_ICCERR))

/** Result code indicating whether a condition where VDD12V has been outside the specified valid range has been detected */
#define XENSIV_PASCO2_RSLT_ORVS\
    (CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2, XENSIV_PASCO2_ORVS))

/** Result code indicating whether a condition where the temperature has been outside the specified valid range has been detected */
#define XENSIV_PASCO2_RSLT_ORTMP\
    (CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2, XENSIV_PASCO2_ORTMP))

/** Result code indicating that a new CO2 value is not yet ready */
#define XENSIV_PASCO2_RSLT_READ_NRDY\
    (CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2, XENSIV_PASCO2_READ_NRDY))

/******************************** Type declarations **************************************/

/** Structure containing callback data for handling interrupts from sensor. */
#if defined(CYHAL_API_VERSION) && (CYHAL_API_VERSION >= 2)
typedef cyhal_gpio_callback_data_t xensiv_pasco2_mtb_interrupt_cb_t;
#else
typedef struct
{
    cyhal_gpio_event_callback_t cb; /**< The callback function to run */
    void * arg;                     /**< Optional argument for the callback */
} xensiv_pasco2_mtb_interrupt_cb_t;
#endif

/******************************* Function prototypes *************************************/

#ifdef __cplusplus
extern "C" {
#endif


/** Initializes the XENSIV™ PAS CO2 sensor and configures it to use the specified I2C peripheral
 *
 * @param[inout]  obj       Pointer to the ModusToolbox&trade PAS CO2 object. The caller must allocate the
 * memory for this object but the init function will initialize its contents
 * @param[in]   i2c         Pointer to an initialized I2C object
 * @return CY_RSLT_SUCCESS if the initialization was successful; an error indicating what went wrong otherwise
 */
cy_rslt_t xensiv_pasco2_mtb_init_i2c(xensiv_pasco2_t * dev, cyhal_i2c_t * i2c);

/** Initializes the XENSIV™ PAS CO2 sensor, and configures it to use the specified UART peripheral
 *
 * @param[inout]  obj       Pointer to the ModusToolbox&trade PAS CO2 object. The caller must allocate the
 * memory for this object but the init function will initialize its contents
 * @param[in]   uart        Pointer to an initialized UART object
 * @return CY_RSLT_SUCCESS if the initialization was successful; an error indicating what went wrong otherwise
 */
cy_rslt_t xensiv_pasco2_mtb_init_uart(xensiv_pasco2_t * dev, cyhal_uart_t * uart);

/** Configures a GPIO pin as an interrupt for the PAS CO2 sensor.
 * This initializes and configures the pin as an interrupt, and calls the PAS CO2 interrupt
 * configuration API with the application-supplied settings structure
 * \note Should be called only after \ref xensiv_pasco2_mtb_init_i2c or \ref xensiv_pasco2_mtb_init_uart.
 * \deprecated Use \ref xensiv_pasco2_mtb_interrupt_init_ex
 * @param[in] dev               Pointer to the PAS CO2 sensor device
 * @param[in] int_config        New sensor device interrupt configuration to apply
 * @param[in] alarm_threshold   New alarm threshold value to apply
 * @param[in] pin               Pin connected to the INT pin of the sensor
 * @param[in] intr_priority     Priority for NVIC interrupt events
 * @param[in] callback          Function to call when the specified event happens. Pass NULL to unregister the handler
 * @param[in] callback_arg      Generic argument that will be provided to the callback when called; can be NULL
 * @return CY_RSLT_SUCCESS if interrupt was successfully enabled; an error occurred while initializing the pin otherwise
 */
cy_rslt_t xensiv_pasco2_mtb_interrupt_init(const xensiv_pasco2_t * dev,
                                           const xensiv_pasco2_interrupt_config_t int_config,
                                           uint16_t alarm_threshold,
                                           cyhal_gpio_t pin,
                                           uint8_t intr_priority,
                                           cyhal_gpio_event_callback_t callback,
                                           void* callback_arg);

/** Configures a GPIO pin as an interrupt for the PAS CO2 sensor.
 * This initializes and configures the pin as an interrupt, and calls the PAS CO2 interrupt
 * configuration API with the application-supplied settings structure
 * \note Should be called only after \ref xensiv_pasco2_mtb_init_i2c or \ref xensiv_pasco2_mtb_init_uart.
 * @param[in] obj               Pointer to the ModusToolbox&trade PAS CO2 sensor object
 * @param[in] int_config        New sensor device interrupt configuration to apply
 * @param[in] alarm_threshold   New alarm threshold value to apply
 * @param[in] pin               Pin connected to the INT pin of the sensor
 * @param[in] intr_priority     Priority for NVIC interrupt events
 * @param[in] interrupt_cb      Interrupt callback
 * @note Instances of this object are expected to persist for the length of time the callback is
 * registered. As such, care must be given if declaring it on the stack to ensure the frame does
 * not go away while the callback is still registered.
 * @return CY_RSLT_SUCCESS if interrupt was successfully enabled; an error occurred while initializing the pin otherwise
 */
cy_rslt_t xensiv_pasco2_mtb_interrupt_init_ex(xensiv_pasco2_t * dev,
                                              const xensiv_pasco2_interrupt_config_t int_config,
                                              uint16_t alarm_threshold,
                                              cyhal_gpio_t pin,
                                              uint8_t intr_priority,
                                              xensiv_pasco2_mtb_interrupt_cb_t * interrupt_cb);

/** Reads the CO2 value value if available.
 * This checks whether a new CO2 value is available, in which case it returns it and sets the new pressure reference value for the next measurement
 * @param[in] obj           Pointer to the ModusToolbox&trade PAS CO2 object
 * @param[in] press_ref     New pressure reference value to apply
 * @param[out] co2_ppm_val  Pointer to populate with the CO2 ppm value
 * @return CY_RSLT_SUCCESS if PPM value was successfully read.
 *         XENSIV_PASCO2_RSLT_READ_NRDY if the measurement value is not ready yet; an error indicating what went wrong otherwise
 */
cy_rslt_t xensiv_pasco2_mtb_read(const xensiv_pasco2_t * dev, uint16_t press_ref, uint16_t * co2_ppm_val);

#ifdef __cplusplus
}
#endif

#endif // defined(CY_USING_HAL)

/** \} group_board_libs_mtb */

#endif
