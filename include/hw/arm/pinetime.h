#ifndef PINETIME_H
#define PINETIME_H

#include "qemu/osdep.h"

#include "hw/core/boards.h"
#include "hw/arm/nrf52_soc.h"
#include "qom/object.h"


struct PinetimeMachineState {
    /* private */
    MachineState parent_obj;
    /* public */
    NRF52State nrf52;
};

struct PinetimeMachineStateClass {
    MachineClass parent_class;
};
typedef struct PinetimeMachineStateClass PinetimeMachineStateClass;


#define TYPE_PINETIME_MACHINE MACHINE_TYPE_NAME("pinetime")

OBJECT_DECLARE_SIMPLE_TYPE(PinetimeMachineState, PINETIME_MACHINE)

#endif
