/*
 *  ======== ti_drivers_config.h ========
 *  Configured TI-Drivers module declarations
 *
 *  The macros defines herein are intended for use by applications which
 *  directly include this header. These macros should NOT be hard coded or
 *  copied into library source code.
 *
 *  Symbols declared as const are intended for use with libraries.
 *  Library source code must extern the correct symbol--which is resolved
 *  when the application is linked.
 *
 *  DO NOT EDIT - This file is generated for the CC3220SF_LAUNCHXL
 *  by the SysConfig tool.
 */
#ifndef ti_drivers_config_h
#define ti_drivers_config_h

#define CONFIG_SYSCONFIG_PREVIEW

#define CONFIG_CC3220SF_LAUNCHXL
#ifndef DeviceFamily_CC3220
#define DeviceFamily_CC3220
#endif

#include <ti/devices/DeviceFamily.h>

#include <stdint.h>

/* support C++ sources */
#ifdef __cplusplus
extern "C" {
#endif


/*
 *  ======== ADC ========
 */

/* P58 */
extern const uint_least8_t          CONFIG_ADC_0_CONST;
#define CONFIG_ADC_0                0


/*
 *  ======== Crypto ========
 */

extern const uint_least8_t          CONFIG_Crypto_0_CONST;
#define CONFIG_Crypto_0             0

/*
 *  ======== GPIO ========
 */

/* P04, LaunchPad User Button SW2 (left) */
extern const uint_least8_t          CONFIG_GPIO_BUTTON_0_CONST;
#define CONFIG_GPIO_BUTTON_0        0
/* P15, LaunchPad User Button SW3 (right) */
extern const uint_least8_t          CONFIG_GPIO_BUTTON_1_CONST;
#define CONFIG_GPIO_BUTTON_1        1
/* P64, LaunchPad LED D10 (Red) */
extern const uint_least8_t          CONFIG_GPIO_LED_0_CONST;
#define CONFIG_GPIO_LED_0           2
/* P01, LaunchPad LED D9 (Yellow) */
extern const uint_least8_t          CONFIG_GPIO_LED_1_CONST;
#define CONFIG_GPIO_LED_1           3
/* P02, LaunchPad LED D8 (Green) */
extern const uint_least8_t          CONFIG_GPIO_LED_2_CONST;
#define CONFIG_GPIO_LED_2           4
/* P03 */
extern const uint_least8_t          CONFIG_GPIO_0_CONST;
#define CONFIG_GPIO_0               5
/* P18 */
extern const uint_least8_t          CONFIG_GPIO_1_CONST;
#define CONFIG_GPIO_1               6
/* P21 */
extern const uint_least8_t          CONFIG_GPIO_2_CONST;
#define CONFIG_GPIO_2               7
/* P50 */
extern const uint_least8_t          CONFIG_GPIO_3_CONST;
#define CONFIG_GPIO_3               8
/* P53 */
extern const uint_least8_t          CONFIG_GPIO_4_CONST;
#define CONFIG_GPIO_4               9
/* P61 */
extern const uint_least8_t          CONFIG_GPIO_5_CONST;
#define CONFIG_GPIO_5               10
/* P62 */
extern const uint_least8_t          CONFIG_GPIO_6_CONST;
#define CONFIG_GPIO_6               11
/* P63 */
extern const uint_least8_t          CONFIG_GPIO_7_CONST;
#define CONFIG_GPIO_7               12
/* P45 */
extern const uint_least8_t          CONFIG_GPIO_8_CONST;
#define CONFIG_GPIO_8               13

/* LEDs are active high */
#define CONFIG_GPIO_LED_ON  (1)
#define CONFIG_GPIO_LED_OFF (0)

#define CONFIG_LED_ON  (CONFIG_GPIO_LED_ON)
#define CONFIG_LED_OFF (CONFIG_GPIO_LED_OFF)


/*
 *  ======== PWM ========
 */

/* P01, LaunchPad LED D9 (Yellow) */
extern const uint_least8_t          CONFIG_PWM_0_CONST;
#define CONFIG_PWM_0                0
/* P02, LaunchPad LED D8 (Green) */
extern const uint_least8_t          CONFIG_PWM_1_CONST;
#define CONFIG_PWM_1                1


/*
 *  ======== SPI ========
 */

extern const uint_least8_t          CONFIG_NWP_SPI_CONST;
#define CONFIG_NWP_SPI              0
/*
 *  MOSI: P07
 *  MISO: P06
 *  SCLK: P05
 *  SS: P08
 */
extern const uint_least8_t          CONFIG_SPI_0_CONST;
#define CONFIG_SPI_0                1


/*
 *  ======== Timer ========
 */

extern const uint_least8_t          CONFIG_TIMER_0_CONST;
#define CONFIG_TIMER_0              0
extern const uint_least8_t          CONFIG_TIMER_1_CONST;
#define CONFIG_TIMER_1              1
extern const uint_least8_t          CONFIG_TIMER_2_CONST;
#define CONFIG_TIMER_2              2

/*
 *  ======== UART ========
 */

/*
 *  TX: P55
 *  RX: P57
 *  XDS110 UART
 */
extern const uint_least8_t          CONFIG_UART_0_CONST;
#define CONFIG_UART_0               0


/*
 *  ======== Watchdog ========
 */

extern const uint_least8_t          CONFIG_WATCHDOG_0_CONST;
#define CONFIG_WATCHDOG_0           0


/*
 *  ======== Board_init ========
 *  Perform all required TI-Drivers initialization
 *
 *  This function should be called once at a point before any use of
 *  TI-Drivers.
 */
extern void Board_init(void);

/*
 *  ======== Board_initGeneral ========
 *  (deprecated)
 *
 *  Board_initGeneral() is defined purely for backward compatibility.
 *
 *  All new code should use Board_init() to do any required TI-Drivers
 *  initialization _and_ use <Driver>_init() for only where specific drivers
 *  are explicitly referenced by the application.  <Driver>_init() functions
 *  are idempotent.
 */
#define Board_initGeneral Board_init

#ifdef __cplusplus
}
#endif

#endif /* include guard */
