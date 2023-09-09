/*
 * flash_smg.h
 *
 *  Created on: 2023年7月5日
 *      Author: a8456
 */

#ifndef FLASH_SMG_H_
#define FLASH_SMG_H_

#include "hal_data.h"

#ifdef USE_FLASH
#define FLASH_DF_BLOCK_0                0x40100000U/*   1 KB: 0x40100000 - 0x401003FF */

#define TIME_SEC    0
#define TIME_MIN    1
#define TIME_HOUR   2
#define TIME_DAY    3
#define TIME_DATE   4
#define TIME_MONTH  5
#define TIME_YEAR   6

/*FLASH写入程序*/
void SaveTimeFlash();

/*FLASH读取打印程序*/
void ReadTimeFlash();

#endif // #ifdef USE_FLASH

#endif /* FLASH_SMG_H_ */
