#include <unistd.h>
#include <sys/wait.h>

int main() {
    if(fork() == 0) {
        if(fork() == 0) {
            if(fork() == 0) {
                execlp("./bin/spy_simulation", "./bin/spy_simulation", (char *)NULL);
            }
            sleep(0.5);
            execlp("./bin/citizen_manager", "./bin/citizen_manager", (char *)NULL);
            wait(NULL);
        }
        sleep(0.5);
        execlp("./bin/monitor", "./bin/monitor", (char *)NULL);
        wait(NULL);
    }
    sleep(1);
    execlp("./bin/timer", "./bin/timer", (char *)NULL);
    wait(NULL);
}