/*
 * SPDX-License-Identifier:     GPL-2.0+
 *
 * Copyright (c) 2026
 */

#ifndef __CONFIGS_H20PLUS_H
#define __CONFIGS_H20PLUS_H

#include <configs/rk3528_common.h>

#ifndef CONFIG_SPL_BUILD

#undef BOOT_TARGET_MMC
#define BOOT_TARGET_MMC(func) \
		func(MMC, mmc, 0) \
		func(MMC, mmc, 1)

#undef RKIMG_DET_BOOTDEV
#define RKIMG_DET_BOOTDEV \
		"rkimg_bootdev=" \
		"if mmc dev 0 && rkimgtest mmc 0; then " \
			"setenv devtype mmc; setenv devnum 0; echo Boot from SDcard;" \
		"elif mmc dev 1; then " \
			"setenv devtype mmc; setenv devnum 1; echo Boot from eMMC;" \
		"elif mtd_blk dev 0; then " \
			"setenv devtype mtd; setenv devnum 0;" \
		"elif mtd_blk dev 1; then " \
			"setenv devtype mtd; setenv devnum 1;" \
		"elif mtd_blk dev 2; then " \
			"setenv devtype mtd; setenv devnum 2;" \
		"elif rknand dev 0; then " \
			"setenv devtype rknand; setenv devnum 0;" \
		"elif rksfc dev 0; then " \
			"setenv devtype spinand; setenv devnum 0;" \
		"elif rksfc dev 1; then " \
			"setenv devtype spinor; setenv devnum 1;" \
		"else;" \
			"setenv devtype ramdisk; setenv devnum 0;" \
		"fi; \0"

#undef ROCKCHIP_DEVICE_SETTINGS
#define ROCKCHIP_DEVICE_SETTINGS \
		"stdin=serial,usbkbd\0" \
		"stdout=serial,vidconsole\0" \
		"stderr=serial,vidconsole\0" \
		"bootpart=2\0" \
		"bootscript=/boot.scr\0" \
		"bootcmd_bootimg=" \
			"if test -z \"${devtype}\"; then setenv devtype mmc; fi; " \
			"if test -z \"${devnum}\"; then setenv devnum 1; fi; " \
			"if test -z \"${bootpart}\"; then setenv bootpart 2; fi; " \
			"if test \"${devtype}\" = \"mmc\"; then " \
				"echo Loading ${bootscript} from ${devtype} ${devnum}:${bootpart}; " \
				"if load ${devtype} ${devnum}:${bootpart} ${scriptaddr} ${bootscript}; then " \
					"echo Running ${bootscript} from ${devtype} ${devnum}:${bootpart}; " \
					"source ${scriptaddr}; " \
				"fi; " \
			"fi\0"

#define CONFIG_SYS_MMC_ENV_DEV		0

#undef CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND \
	"run rkimg_bootdev;" \
	"run bootcmd_bootimg;" \
	"boot_android ${devtype} ${devnum};" \
	"boot_fit;" \
	"bootrkp;" \
	"run distro_bootcmd;"
#endif

#endif /* __CONFIGS_H20PLUS_H */
