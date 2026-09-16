/*
 * QTest testcase for pintetime
 *
 * Open source Pinetime watch, see:
 * https://pine64.org/documentation/PineTime/
 * 
 * Copyright (c) 2026 Goober, Inc.
 *
 * Author: Don't contact me
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * TODO: NVMC tests
 */

#include "qemu/osdep.h"
#include "hw/arm/nrf52.h"
#include "hw/misc/nrf52_rng.h"
#include "hw/nvram/nrf52_nvm.h"
#include "libqtest.h"

static void test_nrf52_nvm(void) {
    QTestState *qts = qtest_init("-M pinetime");
    uint32_t value;

    qtest_writel(qts, NRF52_NVMC_BASE + NRF52_NVMC_CONFIG, NRF52_NVMC_CONFIG_WEN);
    qtest_writel(qts, NRF52_UICR_BASE + 0x80,  0xdeadbeef);

    value = qtest_readl(qts,  NRF52_UICR_BASE + 0x80);

    g_assert_cmphex(value, ==, 0xdeadbeef);

    qtest_quit(qts);
}

static void test_nrf52_rng_reset(void) {
    QTestState *qts = qtest_init("-M pinetime");

    // tests valready/shorts/inten/config/value = 0

    g_assert_cmpuint(qtest_readl(qts, NRF52_RNG_BASE + NRF52_RNG_EVENT_VALRDY), ==, 0);
    g_assert_cmpuint(qtest_readl(qts, NRF52_RNG_BASE + NRF52_RNG_REG_SHORTS), ==, 0);
    g_assert_cmpuint(qtest_readl(qts, NRF52_RNG_BASE + NRF52_RNG_REG_INTEN), ==, 0);
    g_assert_cmpuint(qtest_readl(qts, NRF52_RNG_BASE + NRF52_RNG_REG_CONFIG), ==, 0);
    g_assert_cmpuint(qtest_readl(qts, NRF52_RNG_BASE + NRF52_RNG_REG_VALUE), ==, 0);

    qtest_quit(qts);
}

static void test_nrf52_rng_valrdy(void) {
    QTestState *qts = qtest_init("-M pinetime");
    uint32_t value;

    qtest_writel(qts, NRF52_RNG_BASE + NRF52_RNG_TASK_START, NRF52_TRIGGER_TASK);
    g_assert_cmpuint(qtest_readl(qts, NRF52_RNG_BASE + NRF52_RNG_EVENT_VALRDY), ==, 0);

    // filter period is 30us
    qtest_clock_step(qts, 31 * 1000);
    g_assert_cmpuint(qtest_readl(qts, NRF52_RNG_BASE + NRF52_RNG_EVENT_VALRDY), ==, 1);

    /* check for a sane random number. */
    value = qtest_readl(qts, NRF52_RNG_BASE + NRF52_RNG_REG_VALUE);
    g_assert_cmpuint(value, <=, 0xff);

    qtest_quit(qts);
}


int main(int argc, char **argv) {
    // stub
    g_test_init(&argc, &argv, NULL);

    qtest_add_func("/pinetime/nrf52/nvm", test_nrf52_nvm);
    qtest_add_func("/pinetime/nrf52/rng/reset", test_nrf52_rng_reset);
    qtest_add_func("/pinetime/nrf52/rng/valrdy", test_nrf52_rng_valrdy);


    return g_test_run();
}
