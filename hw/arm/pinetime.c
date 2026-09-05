/*
 * Open source Pinetime watch machine
 * https://pine64.org/documentation/PineTime/
 *
 */

#include "qemu/osdep.h"
#include "qemu/typedefs.h"
#include "qapi/error.h"
#include "hw/arm/boot.h"
#include "hw/arm/pinetime.h"
#include "hw/core/boards.h"
#include "hw/arm/boot.h"
#include "qom/object.h"
#include "system/address-spaces.h"
#include "hw/arm/machines-qom.h"



static void pinetime_init(MachineState *machine){
    PinetimeMachineState *s = PINETIME_MACHINE(machine);
    MemoryRegion *system_memory = get_system_memory();

    object_initialize_child(OBJECT(machine), "nrf52", &s->nrf52,
                            TYPE_NRF52_SOC);
    object_property_set_link(OBJECT(&s->nrf52), "memory",
                             OBJECT(system_memory), &error_fatal);

    sysbus_realize(SYS_BUS_DEVICE(&s->nrf52), &error_fatal);


    //TODO: check if there is an image already in flash, then boot that instead
    armv7m_load_kernel(s->nrf52.armv7m.cpu, machine->kernel_filename,
                       0, s->nrf52.flash_size);
}

static void pinetime_machine_class_init(ObjectClass *oc, const void *data)
{
    MachineClass *mc = MACHINE_CLASS(oc);

    mc->desc = "Pinetime smartwatch";

    mc->init = pinetime_init;

    mc->no_floppy = 1;
    mc->no_cdrom = 1;
    mc->no_parallel = 1;

    mc->max_cpus = 1;
    mc->default_cpus = 1;
    
}

static const TypeInfo pinetime_info = {
    .name = TYPE_PINETIME_MACHINE,
    .parent = TYPE_MACHINE,
    .instance_size = sizeof(PinetimeMachineState),
    .class_init = pinetime_machine_class_init,
    .interfaces = arm_machine_interfaces,
};

static void pinetime_machine_init(void)
{
    type_register_static(&pinetime_info);
}

type_init(pinetime_machine_init);
