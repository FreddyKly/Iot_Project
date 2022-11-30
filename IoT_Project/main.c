#include <shell.h>


int main(void){
    msg_t msg_q[8];
    msg_init_queue(msg_q, 8);
    static char buf[SHELL_DEFAULT_BUFSIZE];
    
    shell_run_forever(null, buf, sizeof(buf)); //RIOT method -> documentation riot-os.org
    
    return 0;
}