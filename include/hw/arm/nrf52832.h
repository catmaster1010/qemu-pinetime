

/*
 * Nordic Semiconductor nRF52832 SOC Common Defines
 *
 * The nRF52832 is a chip within the nRF52 series
 *
 * Reference Manual: https://docs.nordicsemi.com/r/bundle/ps_nrf52832/page/nrf52832_ps.html
 *
 */

#ifndef NRF52832_H
#define NRF52832_H

#include "hw/arm/nrf52.h"


#define NRF52832_FLASH_PAGES    128
#define NRF52832_SRAM_PAGES     16

#define NRF52832_SRAM_SIZE      (NRF52832_SRAM_PAGES * NRF52_PAGE_SIZE)
#define NRF52832_FLASH_SIZE      (NRF52832_FLASH_PAGES * NRF52_PAGE_SIZE)

#define NRF52832_HCLK_FRQ 64000000

#endif
