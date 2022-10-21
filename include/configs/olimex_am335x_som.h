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

/* Clock Defines */
#define V_OSCK				24000000  /* Clock output from T2 */
#define V_SCLK				(V_OSCK)

/* NS16550 Configuration */
#define CONFIG_SYS_NS16550_COM1 0x44e09000

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

#ifndef CONFIG_SPL_BUILD
#define CONFIG_EXTRA_ENV_SETTINGS \
	DEFAULT_LINUX_BOOT_ENV \
	"boot_fdt=try\0" \
	"bootpart=0:1\0" \
	"bootdir=/boot\0" \
	"bootfile=zImage\0" \
	"fdtfile=undefined\0" \
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
	"loadbootenv=load mmc ${mmcdev} ${loadaddr} ${bootenv}\0" \
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
	"mmcboot=mmc dev ${mmcdev}; " \
		"if mmc rescan; then " \
			"echo SD/MMC found on device ${mmcdev};" \
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
		"fi;\0" \
	NANDARGS
	/*DFUARGS*/
#endif

#endif /* ! __CONFIG_OLIMEX_AM335x_SOM_H */
