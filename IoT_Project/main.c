#include <shell.h>
#include <msg.h>
#include "example_driver.c"


int main(void){
    saul_reg_add(a pointer to idk what (driver i guess));
    msg_t msg_q[8];
    msg_init_queue(msg_q, 8);
    static char buf[SHELL_DEFAULT_BUFSIZE];
    
    shell_run_forever(NULL, buf, sizeof(buf)); //RIOT method -> documentation riot-os.org
    
    return 0;
}
