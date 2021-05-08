#include <stdio.h>
#include <signal.h>

// typing Ctrl-C you will notice the text Caught SIGINT printed to the terminal,
// but the program will continue to run after that. You can stop it with Ctrl-Z

void sigint_handler(int signo)
{
    printf("Caught SIGINT\n");
}

int main()
{
    signal(SIGINT, sigint_handler);
    while (1);                  /* Infinite loop */
}