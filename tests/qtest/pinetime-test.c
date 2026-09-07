/*
 * QTest testcase for pintetime
 *
 * Copyright (c) 2026 Goober, Inc.
 *
 * Author: Don't contact me
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "qemu/osdep.h"
#include "hw/arm/nrf52.h"
#include "hw/nvram/nrf52_nvm.h"
#include "libqtest.h"

static void test_nrf52_nvm(void) {
    QTestState *qts = qtest_init("-M pinetime");
    uint32_t value;

    qtest_writel(qts, NRF52_NVMC_BASE + NRF52_NVMC_CONFIG, NRF52_NVMC_CONFIG_WEN);
    qtest_writel(qts, NRF52_UICR_BASE | 0x80,  0xdeadbeef);

    value = qtest_readl(qts,  NRF52_UICR_BASE | 0x80);

    g_assert_cmphex(value, ==, 0xdeadbeef);

    qtest_quit(qts);
}

int main(int argc, char **argv) {
    // stub
    g_test_init(&argc, &argv, NULL);

    qtest_add_func("/pinetime/nrf52/nvm", test_nrf52_nvm);

    return g_test_run();
}