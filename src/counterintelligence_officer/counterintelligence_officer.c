#include "counterintelligence_officer.h"

void set_signal_handler() {
    struct sigaction action;
    action.sa_handler = signal_handler;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);

    sigaction(SIGTERM, &action, NULL);

    sigaction(SIGALRM, &action, NULL);

    action.sa_handler = SIG_IGN;
    sigaction(SIGTSTP, &action, NULL);
}

void signal_handler(int signum) {
    switch (signum) {
        case SIGALRM:
            new_target();
            break;
        case SIGTERM:
            //printf("signal SIGTERM\n");
            break;
         case SIGINT:
            //printf("signal SIGINT\n");
            exit(0);
        default:
            break;
    }
}

void new_target() {

}