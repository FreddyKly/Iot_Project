//Author: Frederik Kliemt (1465987)
/*
 * Copyright (C) 2016 Eistec AB
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_saul
 * @{
 *
 * @file
 * @brief       SAUL wrapper for direct access to analog pins
 *
 * @author      Joakim Nohlgård <joakim.nohlgard@eistec.se>
 *
 * @}
 */

#include <string.h>
#include <stdio.h>
#include "saul.h"
#include "ztimer.h"

static int random_output(const void *dev, phydat_t *res)
{
    uint64_t now = ztimer_now(ZTIMER_MSEC);

    (void) dev;

    int result = now % 10;

    printf("result: %i \n", result);

    res->val[0] = result;

    return 1;
}

const saul_driver_t custom_driver_saul_driver = {
    .read = random_output,
    .write = saul_write_notsup,
    .type = SAUL_SENSE_ANALOG,
};

