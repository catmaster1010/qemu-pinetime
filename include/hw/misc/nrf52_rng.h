/*
 * nRF52 Random Number Generator
 *
 * Based on hw/misc/nrf51_rng.c by Steffen Görtz. The nRF52 RNG shares the
 * nRF51 register layout; this model adjusts timing to the nRF52832
 * production specification.
 *
 * Reference Manual: https://docs.nordicsemi.com/r/bundle/ps_nrf52832/page/nrf52832_ps.html
 *
 * QEMU interface:
 * + Property "period_unfiltered_us": Time between two biased values in
 *   microseconds.
 * + Property "period_filtered_us": Time between two unbiased values in
 *   microseconds.
 * + sysbus MMIO regions 0: Memory Region with tasks, events and registers
 *   to be mapped to the peripherals instance address by the SOC.
 * + Named GPIO output "irq": Interrupt line of the peripheral. Must be
 *   connected to the associated peripheral interrupt line of the NVIC.
 * + Named GPIO output "eep_valrdy": Event set when new random value is ready
 *   to be read.
 * + Named GPIO input "tep_start": Task that triggers start of continuous
 *   generation of random values.
 * + Named GPIO input "tep_stop": Task that ends continuous generation of
 *   random values.
 *
 * Accuracy of the peripheral model:
 * + Stochastic properties of different configurations of the random source
 *   are not modeled.
 * + Generation of unfiltered and filtered random values take at least the
 *   average generation time stated in the production specification;
 *   non-deterministic generation times are not modeled.
 *
 * Copyright 2026 sirrobindoger <solomonortegais@gmail.com>
 * Copyright 2018 Steffen Görtz <contrib@steffen-goertz.de>
 *
 * This code is licensed under the GPL version 2 or later.  See
 * the COPYING file in the top-level directory.
 */

#ifndef NRF52_RNG_H
#define NRF52_RNG_H

#include "qemu/osdep.h"
#include "hw/core/sysbus.h"
#include "qemu/timer.h"
#include "qom/object.h"
#define TYPE_NRF52_RNG "nrf52_soc.rng"
OBJECT_DECLARE_SIMPLE_TYPE(NRF52RNGState, NRF52_RNG)

#define NRF52_RNG_SIZE         0x1000

#define NRF52_RNG_TASK_START   0x000
#define NRF52_RNG_TASK_STOP    0x004
#define NRF52_RNG_EVENT_VALRDY 0x100
#define NRF52_RNG_REG_SHORTS   0x200
#define NRF52_RNG_REG_SHORTS_VALRDY_STOP 0
#define NRF52_RNG_REG_INTEN    0x300
#define NRF52_RNG_REG_INTEN_VALRDY 0
#define NRF52_RNG_REG_INTENSET 0x304
#define NRF52_RNG_REG_INTENCLR 0x308
#define NRF52_RNG_REG_CONFIG   0x504
#define NRF52_RNG_REG_CONFIG_DECEN 0
#define NRF52_RNG_REG_VALUE    0x508

struct NRF52RNGState {
    SysBusDevice parent_obj;

    MemoryRegion mmio;
    qemu_irq irq;

    /* Event End Points */
    qemu_irq eep_valrdy;

    QEMUTimer timer;

    /* Time between generation of successive unfiltered values in us */
    uint16_t period_unfiltered_us;
    /* Time between generation of successive filtered values in us */
    uint16_t period_filtered_us;

    uint8_t value;

    uint32_t active;
    uint32_t event_valrdy;
    uint32_t shortcut_stop_on_valrdy;
    uint32_t interrupt_enabled;
    uint32_t filter_enabled;

};


#endif /* NRF52_RNG_H */
