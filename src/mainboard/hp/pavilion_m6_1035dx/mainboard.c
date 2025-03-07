/* SPDX-License-Identifier: GPL-2.0-only */

#include "ec.h"

#include <acpi/acpi.h>
#include <cpu/x86/smm.h>
#include <device/device.h>
#include <southbridge/amd/common/amd_pci_util.h>

#include <southbridge/amd/agesa/hudson/smi.h>

static const u8 mainboard_picr_data[0x54] = {
	0x1F, 0x1f, 0x1f, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0A, 0xF1, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F,
	0x09, 0x1F, 0x1F, 0x0B, 0x1F, 0x0B, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x1F, 0x1F, 0x1F, 0x1F
};
static const u8 mainboard_intr_data[0x54] = {
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F,
	0x09, 0x1F, 0x1F, 0x10, 0x1F, 0x10, 0x1F, 0x10, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x05, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x12, 0x11, 0x12, 0x11, 0x12, 0x11, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x11, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x10, 0x11, 0x12, 0x13
};

static void pavilion_cold_boot_init(void)
{
	/* Lid SMI is only used in non-ACPI mode; leave it off in S3 resume */
	hudson_configure_gevent_smi(EC_LID_GEVENT, SMI_MODE_SMI, SMI_LVL_LOW);
	/* EC is not powered off during S3 sleep */
	pavilion_m6_1035dx_ec_init();
}

/* PIRQ Setup */
static void pirq_setup(void)
{
	intr_data_ptr = mainboard_intr_data;
	picr_data_ptr = mainboard_picr_data;
}

static void mainboard_enable(struct device *dev)
{
	pirq_setup();

	hudson_configure_gevent_smi(EC_SMI_GEVENT, SMI_MODE_SMI, SMI_LVL_HIGH);
	global_smi_enable();

	if (!acpi_is_wakeup_s3())
		pavilion_cold_boot_init();
}

struct chip_operations mainboard_ops = {
	.enable_dev = mainboard_enable,
};
