ifeq ($(CONFIG_SOC_MEDIATEK_MT8192),y)

bootblock-y += ../common/auxadc.c
bootblock-y += bootblock.c
bootblock-y += ../common/eint_event.c
bootblock-y += ../common/flash_controller.c
bootblock-y += ../common/gpio.c gpio.c
bootblock-y += ../common/i2c.c i2c.c
bootblock-y += ../common/mmu_operations.c
bootblock-y += ../common/pll.c pll.c
bootblock-$(CONFIG_SPI_FLASH) += ../common/spi.c spi.c
bootblock-y += ../common/timer.c
bootblock-y += ../common/tracker.c ../common/tracker_v2.c
bootblock-y += ../common/uart.c
bootblock-y += ../common/wdt.c wdt.c

verstage-y += ../common/auxadc.c
verstage-y += ../common/flash_controller.c
verstage-y += ../common/gpio.c gpio.c
verstage-y += ../common/i2c.c i2c.c
verstage-$(CONFIG_SPI_FLASH) += ../common/spi.c spi.c
verstage-y += ../common/timer.c
verstage-y += ../common/uart.c

romstage-y += ../common/auxadc.c
romstage-y += ../common/cbmem.c
romstage-y += ../common/clkbuf.c srclken_rc.c
romstage-y += ../common/dram_init.c
romstage-y += ../common/dramc_param.c
romstage-y += ../common/flash_controller.c
romstage-y += ../common/gpio.c gpio.c
romstage-y += ../common/i2c.c i2c.c
romstage-y += ../common/memory.c ../common/memory_test.c
romstage-y += ../common/mmu_operations.c ../common/mmu_cmops.c
romstage-y += ../common/pll.c pll.c
romstage-$(CONFIG_SPI_FLASH) += ../common/spi.c spi.c
romstage-y += ../common/timer.c
romstage-y += ../common/uart.c
romstage-y += ../common/pmif.c ../common/pmif_clk.c pmif_clk.c
romstage-y += ../common/pmif_spi.c pmif_spi.c
romstage-y += ../common/pmif_spmi.c pmif_spmi.c
romstage-y += ../common/rtc.c ../common/rtc_osc_init.c ../common/rtc_mt6359p.c
romstage-y += ../common/mt6315.c mt6315.c
romstage-y += ../common/mt6359p.c mt6359p.c

ramstage-y += apusys.c
ramstage-y += ../common/auxadc.c
ramstage-y += ../common/ddp.c ddp.c
ramstage-y += devapc.c
ramstage-y += ../common/dfd.c
ramstage-y += ../common/dpm.c
ramstage-y += ../common/dsi.c ../common/mtk_mipi_dphy.c
ramstage-y += ../common/flash_controller.c
ramstage-y += ../common/gpio.c gpio.c
ramstage-y += ../common/i2c.c i2c.c
ramstage-$(CONFIG_SPI_FLASH) += ../common/spi.c spi.c
ramstage-y += ../common/mcu.c
ramstage-y += ../common/mcupm.c
ramstage-y += ../common/mmu_operations.c ../common/mmu_cmops.c
ramstage-$(CONFIG_COMMONLIB_STORAGE_MMC) += ../common/msdc.c msdc.c
ramstage-y += ../common/mtcmos.c mtcmos.c
ramstage-y += ../common/pmif.c
ramstage-y += ../common/rtc.c ../common/rtc_mt6359p.c
ramstage-y += soc.c
ramstage-y += ../common/spm.c spm.c
ramstage-y += ../common/sspm.c
ramstage-y += ../common/timer.c
ramstage-y += ../common/uart.c
ramstage-y += ../common/ufs.c
ramstage-y += ../common/usb.c usb.c

MT8192_BLOB_DIR := 3rdparty/blobs/soc/mediatek/mt8192

mcu-firmware-files := \
	$(CONFIG_DPM_DM_FIRMWARE) \
	$(CONFIG_DPM_PM_FIRMWARE) \
	$(CONFIG_MCUPM_FIRMWARE) \
	$(CONFIG_SSPM_FIRMWARE) \
	$(CONFIG_SPM_FIRMWARE)

$(foreach fw, $(call strip_quotes,$(mcu-firmware-files)), \
	  $(eval $(fw)-file := $(MT8192_BLOB_DIR)/$(fw)) \
	  $(eval $(fw)-type := raw) \
	  $(eval $(fw)-compression := LZ4) \
	  $(if $(wildcard $($(fw)-file)), $(eval cbfs-files-y += $(fw)), ) \
)

DRAM_CBFS := $(CONFIG_CBFS_PREFIX)/dram
$(DRAM_CBFS)-file := $(MT8192_BLOB_DIR)/dram.elf
$(DRAM_CBFS)-type := stage
$(DRAM_CBFS)-compression := $(CBFS_PRERAM_COMPRESS_FLAG)
ifneq ($(wildcard $($(DRAM_CBFS)-file)),)
        cbfs-files-y += $(DRAM_CBFS)
endif

BL31_MAKEARGS += PLAT=mt8192

CPPFLAGS_common += -Isrc/soc/mediatek/mt8192/include
CPPFLAGS_common += -Isrc/soc/mediatek/common/include
CPPFLAGS_common += -Isrc/vendorcode/mediatek/mt8192/include

$(objcbfs)/bootblock.bin: $(objcbfs)/bootblock.raw.bin
	./util/mtkheader/gen-bl-img.py mt8183 sf $< $@

endif
