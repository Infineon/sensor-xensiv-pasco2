# XENSIV™ PAS CO2 Sensor

## Overview

Note: This is an Early Access Software for PASCO2 devices in ModusToolbox. This software is made available for evaluation purposes only and is not recommended for production development.

This library provides APIs to interface with the PAS CO2 sensor that allows user to read the CO2 concentration.

## Features

- Ability to configure measurement period of sensor
- Values are given in CO2 parts per million

## Requirements

- [ModusToolbox® software](https://www.cypress.com/products/modustoolbox-software-environment) v2.2

    **Note:** This code example version requires ModusToolbox software version 2.2 or later and is not backward compatible with v2.1 or older versions.  
- Board Support Package (BSP) minimum required version: 2.0.0
- Programming Language: C
- Associated Parts: All [PSoC® 6 MCU](http://www.cypress.com/PSoC6) parts

## Supported Toolchains (make variable 'TOOLCHAIN')

- GNU Arm® Embedded Compiler v9.3.1 (`GCC_ARM`) - Default value of `TOOLCHAIN`

## Supported Kits (make variable 'TARGET')

- Rapid IoT Connect Developer Kit (`CYSBSYSKIT-DEV-01`)

## Hardware Setup

This code example requires the XENSIV™ PAS CO2 Wing Board as part of the Connected Sensor Kit.

1. Connect PAS CO2 Wing Board to `CYSBSYSKIT-DEV-01` kit with the pin headers.
2. Connect `CYSBSYSKIT-DEV-01` kit to PC with USB cable.
3. Place the `CYSBSYSKIT-DEV-01` kit at desired location.

## Software Setup

### Quick Start

**Note:** Please refer to the PAS CO2 library API documentation for details.

### More information

- [Connected Sensor Kit](https://www.infineon.com/connectedsensorkit)
- [CYSBSYSKIT-DEV-01](https://github.com/cypresssemiconductorco/TARGET_CYSBSYSKIT-DEV-01)
- [API Reference Guide](https://cypresssemiconductorco.github.io/sensor-xensiv-pasco2/pasco2_api_reference_manual/html/index.html)
- [CO2 Sensors](https://www.infineon.com/cms/en/product/sensor/co2-sensors)
- [ModusToolbox](https://www.cypress.com/products/modustoolbox-software-environment)
- [PSoC 6 Code Examples using ModusToolbox IDE](https://github.com/cypresssemiconductorco/Code-Examples-for-ModusToolbox-Software)
- [PSoC 6 Resources](https://community.cypress.com/)

---
**Engineering Samples Release**

© Infineon Technologies AG, 2021.
