#include <shell.h>
#include <msg.h>
#include "example_driver.c"

extern saul_driver_t adc_saul_driver;

int main(void){
    saul_reg_t reg;
    reg.name = "name";
    reg.dev = (void *) 1;
    reg.driver = &adc_saul_driver;
    saul_reg_add(reg);
    msg_t msg_q[8];
    msg_init_queue(msg_q, 8);
    static char buf[SHELL_DEFAULT_BUFSIZE];
    
    shell_run_forever(NULL, buf, sizeof(buf)); //RIOT method -> documentation riot-os.org
    
    return 0;
}
