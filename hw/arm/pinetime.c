/*
 * Pinetime machine
 */
#include "qemu/osdep.h"
#include "qapi/error.h"
#include "hw/arm/boot.h"
#include "qemu/units.h"
#include "hw/core/boards.h"
#include "hw/arm/nrf52_soc.h"

struct PinetimeState {
    MachineState parent_obj;
    NRF52State nrf52;
};
