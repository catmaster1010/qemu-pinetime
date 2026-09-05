/*
 * Nordic Semiconductor nRF52 SoC
 *
 */
#ifndef HW_ARM_NRF52_SOC_H
#define HW_ARM_NRF52_SOC_H

#include "qemu/osdep.h"

#include "hw/core/sysbus.h"
#include "hw/arm/armv7m.h"
#include "qom/object.h"
#include "hw/nvram/nrf52_nvm.h"
#define TYPE_NRF52_SOC "nrf52-soc" // QOM typename of the Nrf52StateClass

OBJECT_DECLARE_SIMPLE_TYPE(NRF52State, NRF52_SOC)

struct NRF52State {
    /* Private */
    SysBusDevice parent_obj;

    /*< public >*/
    ARMv7MState armv7m;

    /*
    NRF52UARTState uart;
    NRF52RNGState rng;
    NRF52GPIOState gpio;
    NRF52TimerState timer[NRF52_NUM_TIMERS];
    */

    NRF52NVMState nvm;
    MemoryRegion iomem;
    MemoryRegion sram;
    MemoryRegion flash;
    MemoryRegion clock;
    MemoryRegion twi;

    uint32_t sram_size;
    uint32_t flash_size;

    MemoryRegion *board_memory;

    MemoryRegion container;

    Clock *sysclk;
    int a;
};
#endif
