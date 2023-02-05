//Author: Frederik Kliemt (1465987)

#include <string.h>
#include <stdio.h>
#include "saul.h"
#include "ztimer.h"

static int random_output(const void *dev, phydat_t *res)
{
    //Driver to increment value each second
    uint64_t now = ztimer_now(ZTIMER_SEC);

    (void) dev;

    int result = now % 10;

    res->val[0] = result;

    return 1;
}

const saul_driver_t custom_driver_saul_driver = {
    .read = random_output,
    .write = saul_write_notsup,
    .type = SAUL_SENSE_ANALOG,
};

