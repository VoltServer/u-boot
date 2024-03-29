/*
 * am335x_evm.h
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __CONFIG_OLIMEX_AM335x_SOM_H
#define __CONFIG_OLIMEX_AM335x_SOM_H

#include <linux/sizes.h>
#include <configs/ti_am335x_common.h>

#undef CONFIG_SYS_I2C
#undef CONFIG_SPL_I2C_SUPPORT
#undef CONFIG_SPL_OS_BOOT
#define CONFIG_HW_WATCHDOG
#define CONFIG_OMAP_WATCHDOG

#define MACH_TYPE_TIAM335EVM		3589	/* Until the next sync */
#define CONFIG_MACH_TYPE		MACH_TYPE_TIAM335EVM
#define CONFIG_BOARD_LATE_INIT

/* Clock Defines */
#define V_OSCK				24000000  /* Clock output from T2 */
#define V_SCLK				(V_OSCK)

/* Custom script for NOR */
#define CONFIG_SYS_LDSCRIPT		"board/olimex/am335x_som/u-boot.lds"

/* Always 128 KiB env size */
#define CONFIG_ENV_SIZE			(128 << 10)

/* Enhance our eMMC support / experience. */
#define CONFIG_CMD_GPT
#define CONFIG_EFI_PARTITION
#define CONFIG_PARTITION_UUIDS
#define CONFIG_CMD_PART

/* UBI Support */
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_PARTITIONS
#define CONFIG_MTD_DEVICE
#define CONFIG_RBTREE
#define CONFIG_LZO
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS

#ifdef CONFIG_NAND
#define CONFIG_SYS_NAND_U_BOOT_OFFS	0x000c0000
#ifdef CONFIG_SPL_OS_BOOT
#define CONFIG_CMD_SPL_NAND_OFS 0x00080000 /* os parameters */
#define CONFIG_SYS_NAND_SPL_KERNEL_OFFS 0x00200000 /* kernel offset */
#define CONFIG_CMD_SPL_WRITE_SIZE	0x2000
#endif
#define NANDARGS \
    "mtdids=" MTDIDS_DEFAULT "\0" \
    "mtdparts=" MTDPARTS_DEFAULT "\0" \
    "nandargs=setenv bootargs console=${console} " \
        "${optargs} " \
        "root=${nandroot} " \
        "rootfstype=${nandrootfstype}\0" \
    "nandroot=ubi0:rootfs rw ubi.mtd=NAND.file-system,512\0" \
    "nandrootfstype=ubifs rootwait=1\0" \
    "nandboot=echo Booting from nand ...; " \
        "run nandargs; " \
        "nand read ${fdtaddr} NAND.u-boot-spl-os; " \
        "nand read ${loadaddr} NAND.kernel; " \
        "bootz ${loadaddr} - ${fdtaddr}\0"
#else
#define NANDARGS ""
#endif

#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG

#ifndef CONFIG_SPL_BUILD
#define CONFIG_EXTRA_ENV_SETTINGS \
	DEFAULT_LINUX_BOOT_ENV \
	"boot_fdt=try\0" \
	"bootpart=0:1\0" \
	"bootdir=/boot\0" \
	"bootfile=zImage\0" \
	"fdtfile=olimex-am335x-som.dtb\0" \
	"console=ttyO0,115200n8\0" \
	"optargs=\0" \
	"mmcdev=0\0" \
	"mmcroot=/dev/mmcblk0p1 rw\0" \
	"mmcrootfstype=ext4 rootwait\0" \
	"rootpath=/export/rootfs\0" \
	"nfsopts=nolock\0" \
	"mmcargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"${mtdparts} " \
		"root=${mmcroot} " \
		"rootfstype=${mmcrootfstype}\0" \
	"bootenv=uEnv.txt\0" \
	"loadbootenv=load mmc ${bootpart} ${loadaddr} ${bootenv}\0" \
	"importbootenv=echo Importing environment from mmc ...; " \
		"env import -t $loadaddr $filesize\0" \
	"loadimage=load mmc ${bootpart} ${loadaddr} ${bootdir}/${bootfile}\0" \
	"loadfdt=load mmc ${bootpart} ${fdtaddr} ${bootdir}/${fdtfile}\0" \
	"mmcloados=run mmcargs; " \
		"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
			"if run loadfdt; then " \
				"bootz ${loadaddr} - ${fdtaddr}; " \
			"else " \
				"if test ${boot_fdt} = try; then " \
					"bootz; " \
				"else " \
					"echo WARN: Cannot load the DT; " \
				"fi; " \
			"fi; " \
		"else " \
			"bootz; " \
		"fi;\0" \
	"mmcboot=mmc dev ${mmcdev};" \
		"if mmc rescan; then " \
			"echo SD/MMC found on device ${mmcdev};" \
			"for part in 1 2 3 4 5; do " \
				"setenv bootpart ${mmcdev}:${part};" \
				"echo Trying to boot from ${bootpart};" \
				"if run loadbootenv; then " \
					"echo Loaded environment from ${bootenv};" \
					"run importbootenv;" \
				"fi;" \
				"if test -n $uenvcmd; then " \
					"echo Running uenvcmd ...;" \
					"run uenvcmd;" \
				"fi;" \
				"if run loadimage; then " \
					"run mmcloados;" \
				"fi;" \
			"done;" \
		"fi;\0" \
	NANDARGS
	/*DFUARGS*/
#endif

#ifdef CONFIG_NAND_BOOT
#define CONFIG_BOOTCOMMAND "run nandboot;"
#else
#define CONFIG_BOOTCOMMAND "run mmcboot;"
#endif

/* NS16550 Configuration */
#define CONFIG_SYS_NS16550_COM1		0x44e09000
#define CONFIG_BAUDRATE			115200
#define CONFIG_CONS_INDEX		1

/* Bootcount using the RTC block */
#define CONFIG_BOOTCOUNT_LIMIT
#define CONFIG_BOOTCOUNT_AM33XX

#define CONFIG_SPL_LDSCRIPT		"$(CPUDIR)/am33xx/u-boot-spl.lds"

#ifdef CONFIG_NAND
#define CONFIG_SPL_NAND_BOOT
#define CONFIG_NAND_OMAP_GPMC
#define CONFIG_NAND_OMAP_GPMC_PREFETCH
#define CONFIG_NAND_OMAP_ELM
#define CONFIG_SYS_NAND_5_ADDR_CYCLE
#define CONFIG_SYS_NAND_PAGE_COUNT	(CONFIG_SYS_NAND_BLOCK_SIZE / \
					 CONFIG_SYS_NAND_PAGE_SIZE)
#define CONFIG_SYS_NAND_PAGE_SIZE	2048
#define CONFIG_SYS_NAND_OOBSIZE		64
#define CONFIG_SYS_NAND_BLOCK_SIZE	(128*1024)
#define CONFIG_SYS_NAND_BAD_BLOCK_POS	NAND_LARGE_BADBLOCK_POS
#define CONFIG_SYS_NAND_ECCPOS		{ 2, 3, 4, 5, 6, 7, 8, 9, \
					 10, 11, 12, 13, 14, 15, 16, 17, \
					 18, 19, 20, 21, 22, 23, 24, 25, \
					 26, 27, 28, 29, 30, 31, 32, 33, \
					 34, 35, 36, 37, 38, 39, 40, 41, \
					 42, 43, 44, 45, 46, 47, 48, 49, \
					 50, 51, 52, 53, 54, 55, 56, 57, }

#define CONFIG_SYS_NAND_ECCSIZE		512
#define CONFIG_SYS_NAND_ECCBYTES	14
#define CONFIG_SYS_NAND_ONFI_DETECTION
#define CONFIG_NAND_OMAP_ECCSCHEME	OMAP_ECC_BCH8_CODE_HW
#define CONFIG_SYS_NAND_U_BOOT_START	CONFIG_SYS_TEXT_BASE
#endif

#ifdef CONFIG_NAND_BOOT
#define CONFIG_ENV_IS_IN_NAND
#define CONFIG_ENV_OFFSET		0x001c0000
#define CONFIG_ENV_OFFSET_REDUND	0x001e0000
#define CONFIG_SYS_ENV_SECT_SIZE	CONFIG_SYS_NAND_BLOCK_SIZE
#else
#define CONFIG_ENV_IS_IN_EXT4
#define EXT4_ENV_INTERFACE		"mmc"
#define EXT4_ENV_DEVICE_AND_PART		"0:1"
#define EXT4_ENV_FILE			"/boot/uboot.env"
#endif

/* NAND support */
#ifdef CONFIG_NAND
#define CONFIG_CMD_NAND
#define GPMC_NAND_ECC_LP_x8_LAYOUT	1
#if !defined(CONFIG_SPI_BOOT) && !defined(CONFIG_NOR_BOOT)
#define MTDIDS_DEFAULT			"nand0=nand.0"
#define MTDPARTS_DEFAULT		"mtdparts=nand.0:" \
					"128k(NAND.SPL)," \
					"128k(NAND.SPL.backup1)," \
					"128k(NAND.SPL.backup2)," \
					"128k(NAND.SPL.backup3)," \
					"256k(NAND.u-boot-spl-os)," \
					"1m(NAND.u-boot)," \
					"128k(NAND.u-boot-env)," \
					"128k(NAND.u-boot-env.backup1)," \
					"8m(NAND.kernel)," \
					"-(NAND.file-system)"
#endif
#endif

#endif	/* ! __CONFIG_OLIMEX_AM335x_SOM_H */
