#include <unistd.h>

int main() {
    execlp("./bin/spy_simulation", "./bin/spy_simulation", "", NULL);
    execlp("./bin/timer", "./bin/timer", "", NULL);
}