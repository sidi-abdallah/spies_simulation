#include "timer.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include "monitor_common.h"
#include <sys/ioctl.h>
#include <unistd.h>

void handler(int signum)
{
    switch (signum) {
        case SIGALRM:
            return;
        case SIGTERM:
        case SIGINT:
            quit_nicely(NO_PARTICULAR_REASON);
        default:
            break;
    }
}

void set_timer(void)
{
    struct itimerval it;

    /* Clear itimerval struct members */
    timerclear(&it.it_interval);
    timerclear(&it.it_value);

    /* Set timer */
    it.it_interval.tv_usec = TIME_STEP;
    it.it_value.tv_usec = TIME_STEP;
    setitimer(ITIMER_REAL, &it, NULL);
}

void set_signals()
{
    struct sigaction action;

    action.sa_handler = handler;
    action.sa_flags = 0;
    // sigemptyset(&action.sa_mask);

    /* Set signal handlers */
    // sigaction(SIGTERM, &action, NULL);
    // sigaction(SIGINT, &action, NULL);
    sigaction(SIGALRM, &action, NULL);

    // /*  Ignore SIGTSTP  */
    // action.sa_handler = SIG_IGN;
    // sigaction(SIGTSTP, &action, NULL);
    set_timer(); // attendre TIME_STEP avant d'envoyer un signal à handler
}

void sent_sig(void) {
    for(int round = 0; round < ROUND_NUMBER; round++) {
        if(/*reseau dessocié*/0) handler(SIGTERM);
        else set_signals();
    }
    handler(SIGTERM);
}

int main(int argc, char * argv[]){
    sent_sig();
}
