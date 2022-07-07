# XENSIV™ PAS CO2 (1st generation) release notes
This library provides functions for interfacing with the XENSIV™ PAS CO2 sensor.

### What's included?
* APIs for configuring the XENSIV™ PAS CO2 sensor
* APIs for reading CO2 PPM value out of the XENSIV™ PAS CO2 sensor

### What Changed?
#### v1.1.0
* Added new xensiv_pasco2_mtb_interrupt_init_ex() to fix compatibility with HAL v2. 
  It deprecates usage of xensiv_pasco2_mtb_interrupt_init().
#### v1.0.0
* New API
* Added support for UART communication interface
* Added support for using with HAL v1 or v2
#### v0.6.0
* Baseline offset and forced compensation calibration configurable
* Pressure reference can be configured from external source
#### v0.5.0
* Initial release

### Supported software and tools
This version of the XENSIV™ PAS CO2 library was validated for compatibility with the following software and tools:

| Software and tools                        | Version |
| :---                                      | :----:  |
| ModusToolbox™ Software Environment        | 2.4.0   |
| GCC Compiler                              | 10.3.1  |
| IAR Compiler                              | 8.4     |
| ARM Compiler 6                            | 6.11    |

Minimum required ModusToolbox&trade; software environment: v2.2

### More information

- [XENSIV™ PAS CO2 sensor](https://www.infineon.com/cms/en/product/sensor/co2-sensors/)
- [Connected sensor kit](https://www.infineon.com/connectedsensorkit)
- [Infineon Technologies website](https://www.infineon.com)
- [Infineon Semiconductor GitHub](https://github.com/infineon)
- [ModusToolbox&trade; software](https://www.cypress.com/products/modustoolbox-software-environment)

---

© Infineon Technologies AG, 2021-2022.
