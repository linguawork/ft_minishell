#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

//We setup the signal handler before setting a jump point. But there is no guarantee that a signal
// will only be delivered after the jump point has been set. And if this scenario takes place,
// our program will crash. To avoid this we add a global flag that is false by default.
// Once the jump point has been set, we set the flag to true and add a check on this flag in
// our signal handler. If the flag is false, we skip the call to longjmp() and return from
// the handler instead. Here’s our updated signal handler and main function:

// to run: gcc -g -lreadline filename.c && ./a.out

static sigjmp_buf env;

static volatile sig_atomic_t jump_active = 0;

void sigint_handler(int signo) {
    if (!jump_active) {
        return;
    }
    siglongjmp(env, 42);
}

int main() {
    signal(SIGINT, sigint_handler);
    while (1){                  /* Infinite loop */
        if (sigsetjmp(env, 1) == 42) {
            printf("Restart.\n");
        }
        jump_active = 1;        /* Set the flag */
        printf("next iteration...\n");
        sleep(2);
    }
}
// Можно суммировать - при нажатии ctrl+с
// программа будет получать сигнал и выполнять переход к коду который запускает событие
