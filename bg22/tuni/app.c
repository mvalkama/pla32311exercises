/***************************************************************************//**
 * @file app.c
 * @brief Silicon Labs Empty Example Project
 *
 * This example demonstrates the bare minimum needed for a Blue Gecko C application
 * that allows Over-the-Air Device Firmware Upgrading (OTA DFU). The application
 * starts advertising after boot and restarts advertising after a connection is closed.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

/* Bluetooth stack headers */
#include "bg_types.h"
#include "native_gecko.h"
#include "gatt_db.h"

#include "app.h"
#include "em_emu.h"
#include "infrastructure.h"

void temperatureMeasure()
{
	uint8_t htmTempBuffer[5]; /* Stores temp data in the Health Thermometer (HTM) format. */
	uint8_t flags = 0x00; /* HTM flags set as 0 for Celsius, no time stamp or temp type. */
	uint32_t temperature; /* Stores temp data read from the sensor in the correct format */
	uint8_t *p = htmTempBuffer; /* Pointer to buffer needed to convert values to bitstream. */
	/* Convert flags to bitstream and append them in HTM temp data buffer (htmTempBuffer) */
	UINT8_TO_BITSTREAM(p, flags);
	/* Convert sensor data to correct temperature format */
	temperature = FLT_TO_UINT32(EMU_TemperatureGet()*10, -1);
	/* Convert temp to bitstream and place it in the HTM temp data buffer (htmTempBuffer) */
	UINT32_TO_BITSTREAM(p, temperature);
	/* Send indication of the temperature in htmTempBuffer to all "listening" clients.
	 * This enables the Health Thermometer in the Blue Gecko app to display the temperature.
	 * 0xFF as connection ID will send indications to all connections. */
	gecko_cmd_gatt_server_send_characteristic_notification(
			0xFF, gattdb_temperature_measurement, 5, htmTempBuffer);
}

/* Print boot message */
static void bootMessage(struct gecko_msg_system_boot_evt_t *bootevt);

/* Flag for indicating DFU Reset must be performed */
static uint8_t boot_to_dfu = 0;

/* Main application */
void appMain(gecko_configuration_t *pconfig)
{
#if DISABLE_SLEEP > 0
	pconfig->sleep.flags = 0;
#endif

	/* Initialize debug prints. Note: debug prints are off by default. See DEBUG_LEVEL in app.h */
	initLog();

	/* Initialize stack */
	gecko_init(pconfig);

	while (1) {
		/* Event pointer for handling events */
		struct gecko_cmd_packet* evt;

		/* if there are no events pending then the next call to gecko_wait_event() may cause
		 * device go to deep sleep. Make sure that debug prints are flushed before going to sleep */
		if (!gecko_event_pending()) {
			flushLog();
		}

		/* Check for stack event. This is a blocking event listener. If you want non-blocking please see UG136. */
		evt = gecko_wait_event();

		/* Handle events */
		switch (BGLIB_MSG_ID(evt->header)) {
		/* This boot event is generated when the system boots up after reset.
		 * Do not call any stack commands before receiving the boot event.
		 * Here the system is set to start advertising immediately after boot procedure. */
		case gecko_evt_system_boot_id:

			bootMessage(&(evt->data.evt_system_boot));
			printLog("boot event - starting advertising\r\n");
			/* Set tx power to 0dBm */
			gecko_cmd_system_set_tx_power(0);

			/* Set adv on channel 37 only */
			// gecko_cmd_le_gap_set_advertise_channel_map(0, 1);
			/* Set adv on all 3 channels */
			gecko_cmd_le_gap_set_advertise_channel_map(0, 7);

			/* Set the device name to BG22 */
			uint8_t name[] = {9,9,'T','U','N','I','t','e','m','p'};
			gecko_cmd_le_gap_bt5_set_adv_data(0, 0, sizeof(name), name);

			/* Set advertising parameters. 1000ms advertisement interval.
			 * The first parameter is advertising set handle
			 * The next two parameters are minimum and maximum advertising interval, both in
			 * units of (milliseconds * 1.6).
			 * The last two parameters are duration and maxevents left as default. */
			gecko_cmd_le_gap_set_advertise_timing(0, 1600, 1600, 0, 0);

			/* Start general advertising and enable connections. */
			gecko_cmd_le_gap_start_advertising(0, le_gap_general_discoverable, le_gap_connectable_scannable);
			/* Start advertising and disable connections. */
			//gecko_cmd_le_gap_start_advertising(0,le_gap_user_data, le_gap_non_connectable);
			break;

		case gecko_evt_le_connection_opened_id:

			printLog("connection opened\r\n");
			gecko_cmd_hardware_set_soft_timer(32768,0,0);

			/*Set timing parameters
			* Connection interval: 200 msec
			* Slave latency: as defined
			* Supervision timeout: 4500 msec The value in milliseconds must be larger than
			* (1 + latency) * max_interva * 2, where max_interval is given in milliseconds
			*/ gecko_cmd_le_connection_set_timing_parameters(evt->data.evt_le_connection_opened.connection, 160, 160, 5, 450, 0, 0xFFFF);

			break;

		case gecko_evt_hardware_soft_timer_id:
			temperatureMeasure();
			break;

		case gecko_evt_le_connection_closed_id:

			printLog("connection closed, reason: 0x%2.2x\r\n", evt->data.evt_le_connection_closed.reason);

			/* Check if need to boot to OTA DFU mode */
			if (boot_to_dfu) {
				/* Enter to OTA DFU mode */
				gecko_cmd_system_reset(2);
			} else {
				/* Restart advertising after client has disconnected */
				gecko_cmd_le_gap_start_advertising(0, le_gap_general_discoverable, le_gap_connectable_scannable);
			}
			break;

			/* Events related to OTA upgrading
         ----------------------------------------------------------------------------- */

			/* Check if the user-type OTA Control Characteristic was written.
			 * If ota_control was written, boot the device into Device Firmware Upgrade (DFU) mode. */
		case gecko_evt_gatt_server_user_write_request_id:

			if (evt->data.evt_gatt_server_user_write_request.characteristic == gattdb_ota_control) {
				/* Set flag to enter to OTA mode */
				boot_to_dfu = 1;
				/* Send response to Write Request */
				gecko_cmd_gatt_server_send_user_write_response(
						evt->data.evt_gatt_server_user_write_request.connection,
						gattdb_ota_control,
						bg_err_success);

				/* Close connection to enter to DFU OTA mode */
				gecko_cmd_le_connection_close(evt->data.evt_gatt_server_user_write_request.connection);
			}
			break;

			/* Add additional event handlers as your application requires */

		default:
			break;
		}
	}
}

/* Print stack version and local Bluetooth address as boot message */
static void bootMessage(struct gecko_msg_system_boot_evt_t *bootevt)
{
#if DEBUG_LEVEL
	bd_addr local_addr;
	int i;

	printLog("stack version: %u.%u.%u\r\n", bootevt->major, bootevt->minor, bootevt->patch);
	local_addr = gecko_cmd_system_get_bt_address()->address;

	printLog("local BT device address: ");
	for (i = 0; i < 5; i++) {
		printLog("%2.2x:", local_addr.addr[5 - i]);
	}
	printLog("%2.2x\r\n", local_addr.addr[0]);
#endif
}
