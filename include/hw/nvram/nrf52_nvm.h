/*
 * Nordic Semiconductor nRF52 non-volatile memory
 *
 * It provides an interface to erase regions in flash memory.
 * Furthermore it provides the user and factory information registers.
 *
 */
#ifndef NRF52_NVM_H
#define NRF52_NVM_H

#include "glib.h"
#include "qemu/osdep.h"
#include "hw/core/sysbus.h"
#include "qom/object.h"
#define TYPE_NRF52_NVM "nrf52_soc.nvm"
OBJECT_DECLARE_SIMPLE_TYPE(NRF52NVMState, NRF52_NVM)

#define NRF52_UICR_FIXTURE_SIZE 132 // 128 are actually used, first 20 bytes are reserved

#define NRF52_NVMC_SIZE         0x1000

/* READY */
#define NRF52_NVMC_READY        0x400
#define NRF52_NVMC_READY_READY  0x01

/* CONFIG */
#define NRF52_NVMC_CONFIG       0x504 
#define NRF52_NVMC_CONFIG_MASK  0x03
#define NRF52_NVMC_CONFIG_REN   0x0
#define NRF52_NVMC_CONFIG_WEN   0x01
#define NRF52_NVMC_CONFIG_EEN   0x02

/* ERASEPAGE */
#define NRF52_NVMC_ERASEPAGE    0x508 //  ERASEPCR1 is deprecated

/* ERASEALL */
#define NRF52_NVMC_ERASEALL     0x50C 
#define NRF52_NVMC_ERASEALL_ERASE    0x1

/* ERASEUICR */
#define NRF52_NVMC_ERASEUICR    0x514
#define NRF52_NVMC_ERASEUICR_ERASE  0x1

/* ICACHECNF */
#define NRF52_NVMC_ICACHECNF    0x540
#define NRF52_NVMC_ICACHECNF_CHACHEEN_ENABLE    0x1
#define NRF52_NVMC_ICACHECNF_CACHEPROFEN_ENABLE 0x100

/* IHIT */
#define NRF52_NVMC_IHIT         0x548

/* IMISS */
#define NRF52_NVMC_IMISS        0x54C

#define NRF52_UICR_SIZE         0x210

#define NRF52_NVMC_N_WRITE 181

struct NRF52NVMState {
    SysBusDevice parent_obj;

    MemoryRegion mmio;
    MemoryRegion ficr;
    MemoryRegion uicr;
    MemoryRegion flash;

    uint32_t uicr_content[NRF52_UICR_FIXTURE_SIZE];
    uint32_t flash_size;
    uint8_t *storage;

    uint32_t config;
    uint32_t icachecnf;

    GHashTable *num_flash_writes_hash;

};


#endif
