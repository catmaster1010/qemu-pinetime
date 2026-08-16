/*
 * Nordic Semiconductor nRF52832 SoC
 */


#include "qemu/osdep.h"
#include "qapi/error.h"

#include "hw/core/qdev-clock.h"
#include "hw/arm/boot.h"
#include "qemu/units.h"
#include "hw/core/qdev-properties.h"
#include "hw/arm/nrf52_soc.h"
#include "hw/arm/nrf52832.h"


static void nrf52_soc_realize(DeviceState *dev, Error **errp){

    NRF52State *s = NRF52_SOC(dev);
    //MemoryRegion *mr;

    if (!s->board_memory) {
        error_setg(errp, "memory property was not set");
        return;
    }
    /*
     * TODO: I blindly coppied this from nrf51_soc.c, check if this is true
     * HCLK on this SoC is fixed, so we set up sysclk ourselves and
     * the board shouldn't connect it.
     */
    if (clock_has_source(s->sysclk)) {
        error_setg(errp, "sysclk clock must not be wired up by the board code");
        return;
    }
    /* This clock doesn't need migration because it is fixed-frequency */
    clock_set_hz(s->sysclk, NRF52832_HCLK_FRQ);
    qdev_connect_clock_in(DEVICE(&s->armv7m), "cpuclk", s->sysclk);
    object_property_set_link(OBJECT(&s->armv7m), "memory", OBJECT(&s->container),
                             &error_abort);

    memory_region_add_subregion_overlap(&s->container, 0, s->board_memory, -1);


    object_property_set_link(OBJECT(&s->armv7m), "memory", OBJECT(&s->container),
                             &error_abort);
    printf("x2");
    if (!sysbus_realize(SYS_BUS_DEVICE(&s->armv7m), errp)) {  
        return;  
    }

}

static void nrf52_soc_init(Object *obj) {

    NRF52State *s = NRF52_SOC(obj);

    memory_region_init(&s->container, obj, "nrf52-container", UINT64_MAX);

    object_initialize_child(obj, "armv7m", &s->armv7m, TYPE_ARMV7M);
    qdev_prop_set_string(DEVICE(&s->armv7m), "cpu-type",
                         ARM_CPU_TYPE_NAME("cortex-m4"));
    qdev_prop_set_uint32(DEVICE(&s->armv7m), "num-irq", 37);

    s->sysclk = qdev_init_clock_in(DEVICE(s), "sysclk", NULL, NULL, 0);

}

static const Property nrf52_soc_properties[] = {
    DEFINE_PROP_LINK("memory", NRF52State, board_memory, TYPE_MEMORY_REGION,
                     MemoryRegion *),
    DEFINE_PROP_UINT32("sram-size", NRF52State, sram_size, NRF52832_SRAM_SIZE),
    DEFINE_PROP_UINT32("flash-size", NRF52State, flash_size, NRF52832_FLASH_SIZE)
};

static void nrf52_soc_class_init(ObjectClass *klass, const void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->realize = nrf52_soc_realize;
    device_class_set_props(dc, nrf52_soc_properties);
}


static const TypeInfo nrf52_soc_info = {
    .name          = TYPE_NRF52_SOC,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(NRF52State),
    .instance_init = nrf52_soc_init,
    .class_init    = nrf52_soc_class_init,
};

static void nrf52_soc_types(void)
{
    type_register_static(&nrf52_soc_info);
}
type_init(nrf52_soc_types)
