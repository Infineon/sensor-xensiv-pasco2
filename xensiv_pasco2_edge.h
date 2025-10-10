/***********************************************************************************************//**
 * \file xensiv_pasco2_mtb.h
 *
 * Description: This file contains the MTB platform functions declarations
 *              for interacting with the XENSIV PAS CO2 sensor.
 *
 ***************************************************************************************************
 * \copyright
 * Copyright 2021-2025 Infineon Technologies AG
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

#include "mtb_hal.h"
#include "cy_result.h"
#include "mtb_hal_i2c.h"
#include "xensiv_pasco2.h"

/**
 * \addtogroup group_board_libs_edge XENSIV PAS CO2 sensor Edge interface
 * \{
 * Basic set of APIs for interacting with the XENSIV PAS CO2 sensor on the Edge platform.
 *
 * \note XENSIV PAS CO2 sensor support requires delays. If the RTOS_AWARE component is set or
 * CY_RTOS_AWARE is defined, the HAL driver will defer to the RTOS for delays.
 * Because of this, make sure that the RTOS scheduler has started before calling any functions.
 */



/************************************** Macros *******************************************/

/** PASCO2 module identifier */
#ifndef CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2
#define CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2 0x01CA
#endif

/** Result code indicating a communication error */
#define XENSIV_PASCO2_RSLT_ERR_COMM\
    (CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2, XENSIV_PASCO2_ERR_COMM))

/** Result code indicating that an unexpectedly large I2C write was requested which is not supported
 */
#define XENSIV_PASCO2_RSLT_ERR_WRITE_TOO_LARGE\
    (CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2, XENSIV_PASCO2_ERR_WRITE_TOO_LARGE))

/** Result code indicating that the sensor is not yet ready after reset */
#define XENSIV_PASCO2_RSLT_ERR_NOT_READY\
    (CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2, XENSIV_PASCO2_ERR_NOT_READY))

/** Result code indicating whether an invalid command has been received by the serial communication
   interface */
#define XENSIV_PASCO2_RSLT_ICCERR\
    (CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2, XENSIV_PASCO2_ICCERR))

/** Result code indicating whether a condition where VDD12V has been outside the specified valid
   range has been detected */
#define XENSIV_PASCO2_RSLT_ORVS\
    (CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2, XENSIV_PASCO2_ORVS))

/** Result code indicating whether a condition where the temperature has been outside the specified
   valid range has been detected */
#define XENSIV_PASCO2_RSLT_ORTMP\
    (CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2, XENSIV_PASCO2_ORTMP))

/** Result code indicating that a new CO2 value is not yet ready */
#define XENSIV_PASCO2_RSLT_READ_NRDY\
    (CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_BOARD_HARDWARE_XENSIV_PASCO2, XENSIV_PASCO2_READ_NRDY))

/******************************* Function prototypes *************************************/

#ifdef __cplusplus
extern "C" {
#endif


/** Initializes the XENSIV PAS CO2 sensor and configures it to use the specified I2C peripheral
 *
 * @param[inout]  dev       Pointer to the ModusToolbox&trade PAS CO2 object. The caller must
 * allocate the
 * memory for this object but the init function will initialize its contents
 * @param[in]   i2c         Pointer to an initialized I2C object
 * @return CY_RSLT_SUCCESS if the initialization was successful; an error indicating what went wrong
 * otherwise
 */
cy_rslt_t xensiv_pasco2_mtb_init_i2c(xensiv_pasco2_t* dev, mtb_hal_i2c_t* i2c);

/** Reads the CO2 value value if available.
 * This checks whether a new CO2 value is available, in which case it returns it and sets the new
 * pressure reference value for the next measurement
 * @param[in] dev           Pointer to the ModusToolbox&trade PAS CO2 object
 * @param[in] press_ref     New pressure reference value to apply
 * @param[out] co2_ppm_val  Pointer to populate with the CO2 ppm value
 * @return CY_RSLT_SUCCESS if PPM value was successfully read.
 *         XENSIV_PASCO2_RSLT_READ_NRDY if the measurement value is not ready yet; an error
 * indicating what went wrong otherwise
 */
cy_rslt_t xensiv_pasco2_mtb_read(const xensiv_pasco2_t* dev, uint16_t press_ref,
                                 uint16_t* co2_ppm_val);

#ifdef __cplusplus
}
#endif

/** \} group_board_libs_mtb */

#endif // ifndef XENSIV_PASCO2_MTB_H_
