/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Mini AM335x boards information header
 *
 * Copyright (C) 2020, Texas Instruments, Incorporated - http://www.ti.com/
 */

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * We have three pin mux functions that must exist.  We must be able to enable
 * uart0, for initial output and i2c0 to read the main EEPROM.  We then have a
 * main pinmux function that can be overridden to enable all other pinmux that
 * is required on the board.
 */
void enable_uart0_pin_mux(void);
void enable_uart1_pin_mux(void);
void enable_uart2_pin_mux(void);
void enable_uart3_pin_mux(void);
void enable_uart4_pin_mux(void);
void enable_uart5_pin_mux(void);
void enable_i2c0_pin_mux(void);
void enable_board_pin_mux(void);

#ifdef CONFIG_DM_I2C
#define i2c_init(speed, slaveaddr)
#define i2c_probe(chip) (NULL)
#endif

#endif
