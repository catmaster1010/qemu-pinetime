
/*
 * Nordic Semiconductor nRF52 Series SOC Common Defines
 *
 * Reference Manual: https://docs.nordicsemi.com/r/bundle/ps_nrf52832/page/nrf52832_ps.html
 *
 */

#ifndef NRF52_H
#define NRF52_H

#define NRF52_FLASH_BASE      0x00000000
#define NRF52_FICR_BASE       0x10000000
#define NRF52_UICR_BASE       0x10001000


#define NRF52_SRAM_BASE       0x20000000

#define NRF52_NVMC_BASE       0x4001E000

#define NRF52_PERIPHERAL_SIZE 0x00001000

#define NRF52_PAGE_SIZE       0x1000
#define NRF52_BLOCK_SIZE      0x200


#endif
