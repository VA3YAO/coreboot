/* SPDX-License-Identifier: GPL-2.0-or-later */

#ifndef MAINBOARD_EC_H
#define MAINBOARD_EC_H

#include <ec/ec.h>
#include <ec/google/chromeec/ec_commands.h>
#include <variant/gpio.h>

#define MAINBOARD_EC_SCI_EVENTS \
	(EC_HOST_EVENT_MASK(EC_HOST_EVENT_LID_CLOSED)        |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_LID_OPEN)          |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_AC_CONNECTED)      |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_AC_DISCONNECTED)   |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY_LOW)       |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY_CRITICAL)  |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY)           |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_THERMAL_THRESHOLD) |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_THROTTLE_START)    |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_THROTTLE_STOP)     |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_USB_CHARGER)       |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_PD_MCU)            |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_MKBP)              |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_MODE_CHANGE))

#define MAINBOARD_EC_SMI_EVENTS \
	(EC_HOST_EVENT_MASK(EC_HOST_EVENT_LID_CLOSED))

/* EC can wake from S5 with lid or power button */
#define MAINBOARD_EC_S5_WAKE_EVENTS \
	(EC_HOST_EVENT_MASK(EC_HOST_EVENT_LID_OPEN)     |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_POWER_BUTTON))

/*
 * EC can wake from S3 with lid or power button or key press or
 * mode change event
 */
#define MAINBOARD_EC_S3_WAKE_EVENTS \
	(MAINBOARD_EC_S5_WAKE_EVENTS |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_KEY_PRESSED) |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_MODE_CHANGE) |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_MKBP))

/* Log EC wake events plus EC shutdown events */
#define MAINBOARD_EC_LOG_EVENTS \
	(EC_HOST_EVENT_MASK(EC_HOST_EVENT_THERMAL_SHUTDOWN) |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY_SHUTDOWN) |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_PANIC))

/* EC device events to enable and log in S3 */
#define MAINBOARD_EC_S3_DEVICE_EVENTS 0

/* Enable LID switch */
#define EC_ENABLE_LID_SWITCH

/* Enable EC backed ALS device in ACPI */
#define EC_ENABLE_ALS_DEVICE

/* Enable EC backed PD MCU device in ACPI */
#define EC_ENABLE_PD_MCU_DEVICE

#define SIO_EC_MEMMAP_ENABLE	/* EC Memory Map Resources */
#define SIO_EC_HOST_ENABLE	/* EC Host Interface Resources */
#define SIO_EC_ENABLE_PS2K	/* Enable PS/2 Keyboard */

/*
 * Enable EC sync interrupt via GPIO controller, EC_SYNC_IRQ is defined in
 * variant/gpio.h
 */
#define EC_ENABLE_SYNC_IRQ_GPIO

/* Enable EC backed Keyboard Backlight in ACPI */
#define EC_ENABLE_KEYBOARD_BACKLIGHT

/* Enable Tablet switch */
#define EC_ENABLE_TBMC_DEVICE

#endif
