#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

//source  https://indradhanush.github.io/blog/writing-a-unix-shell-part-3/

static jmp_buf env;

void sigint_handler(int signo) {
    longjmp(env, 42);
}

int main() {
    signal(SIGINT, sigint_handler);
    while (1){                  /* Infinite loop */
        if (setjmp(env) == 42) {
            printf("Restart.\n");
        }
        printf("next iteration...\n");
        sleep(2);
    }
}
//A few important things to note about the code above:
//
//The call to signal() takes a pointer to the sigint_handler() function instead of SIG_IGN (line 13).
//When the code reaches line 15 for the first time, setjmp() is invoked and returns 0.
//After the signal handler has been registered, if we type Ctrl-C, the longjmp() function call is invoked
// where we pass 42 to it. The code jumps to line 15 and this time setjmp() returns the value
// that was passed in longjmp() on line 9, i.e. 42. Thus the check evaluates to true, which signifies
// that we reached this code from a non local jump. This is also referred to as a fake return by setjmp().