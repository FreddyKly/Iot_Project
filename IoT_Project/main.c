//Author: Frederik Kliemt (1465987)
#include <shell.h>
#include <msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "shell.h"
#include "saul_reg.h"
#include "msg.h"
#include "net/emcute.h"
#include "net/ipv6/addr.h"
#include "thread.h"
#include "ztimer.h"

#ifndef EMCUTE_ID
#define EMCUTE_ID           ("gertrud")
#endif
#define EMCUTE_PRIO         (THREAD_PRIORITY_MAIN - 1)

#define NUMOFSUBS           (16U)
#define TOPIC_MAXLEN        (64U)

static char stack[THREAD_STACKSIZE_DEFAULT];
static msg_t queue[8];

static emcute_sub_t subscriptions[NUMOFSUBS];
//static char topics[NUMOFSUBS][TOPIC_MAXLEN];


static void init_driver(void) {
    static saul_reg_t saul_entry;
    extern saul_driver_t custom_driver_saul_driver;
    saul_entry.name = "Custom_Driver";
    saul_entry.dev = NULL;
    saul_entry.driver = &custom_driver_saul_driver;
    saul_reg_add(&saul_entry);
}

static void *emcute_thread(void *arg)
{
    (void)arg;
    emcute_run(CONFIG_EMCUTE_DEFAULT_PORT, EMCUTE_ID);
    return NULL;    /* should never be reached */
} 

static int cmd_con(int argc, char **argv)
{
    sock_udp_ep_t gw = { .family = AF_INET6, .port = CONFIG_EMCUTE_DEFAULT_PORT };
    char *topic = NULL;
    char *message = NULL;
    size_t len = 0;

    if (argc < 2) {
        printf("usage: %s <ipv6 addr> [port] [<will topic> <will message>]\n",
                argv[0]);
        return 1;
    }

    /* parse address */
    if (ipv6_addr_from_str((ipv6_addr_t *)&gw.addr.ipv6, argv[1]) == NULL) {
        printf("error parsing IPv6 address\n");
        return 1;
    }

    if (argc >= 3) {
        gw.port = atoi(argv[2]);
    }
    if (argc >= 5) {
        topic = argv[3];
        message = argv[4];
        len = strlen(message);
    }

    if (emcute_con(&gw, true, topic, message, len, 0) != EMCUTE_OK) {
        printf("error: unable to connect to [%s]:%i\n", argv[1], (int)gw.port);
        return 1;
    }
    printf("Successfully connected to gateway at [%s]:%i\n",
           argv[1], (int)gw.port);

    return 0;
}

// static int pub(char *topic, char *message)
// {
//     emcute_topic_t t;
//     unsigned flags = EMCUTE_QOS_0;

//     /* step 1: get topic id */
//     t.name = topic;
//     if (emcute_reg(&t) != EMCUTE_OK) {
//         puts("error: unable to obtain topic ID");
//         return 1;
//     }

//     /* step 2: publish data */
//     if (emcute_pub(&t, message, strlen(message), flags) != EMCUTE_OK) {
//         printf("error: unable to publish data to topic '%s [%i]'\n",
//                 t.name, (int)t.id);
//         return 1;
//     }

//     printf("Published %i bytes to topic '%s [%i]'\n",
//             (int)strlen(message), t.name, t.id);

//     return 0;
// }

static int cmd_start(int argc, char **argv) {
    init_driver();
    if(argc > 0) {
        printf("%s", argv[0]);
    }
    phydat_t random_values;
    static saul_reg_t *custom_driver;
    custom_driver = saul_reg_find_name("Custom_Driver");
    char dataStr[7];
    while (true)
    {
        saul_reg_read(custom_driver, &random_values);
        printf("Read-Value: %i \n", (int)random_values.val[0]);
        sprintf(dataStr, "%i", random_values.val[0]);

        //pub("data", dataStr);
        ztimer_sleep(ZTIMER_SEC, 1);
    }
    return 0;
}

static const shell_command_t shell_commands[] = {
    { "con", "connect to MQTT broker", cmd_con },
    { "start", "start sending data", cmd_start },
    { NULL, NULL, NULL }
};

int main(void){
    /* the main thread needs a msg queue to be able to run `ping`*/
    msg_init_queue(queue, ARRAY_SIZE(queue));

    /* initialize our subscription buffers */
    memset(subscriptions, 0, (NUMOFSUBS * sizeof(emcute_sub_t)));

    /* start the emcute thread */
    thread_create(stack, sizeof(stack), EMCUTE_PRIO, 0,
                  emcute_thread, NULL, "emcute");

    /* start shell */
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    /* should be never reached */
    return 0;
}
