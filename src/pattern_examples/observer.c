/*
 * An Observer design pattern.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_OBSERVERS 3

typedef enum {
    EVENT_1 = 1,
    EVENT_2,
    EVENT_3,
} event_t;

typedef struct memory_s memory_t;
typedef struct observer_s observer_t;

struct memory_s {
    observer_t *obs[MAX_OBSERVERS];

    void (*attach)(memory_t *, observer_t *);
    void (*detach)(memory_t *, observer_t *);
    void (*notify)(memory_t *, event_t e);
};

struct observer_s {
    pid_t pid;
    event_t event;

    void (*update)(observer_t *, event_t e);
};

memory_t * new_memory(void);
void memory_attach(memory_t *memory, observer_t *obs);
void memory_detach(memory_t *memory, observer_t *obs);
void memory_notify(memory_t *memory, event_t e);

observer_t * new_observer(pid_t pid, memory_t *memory, event_t e);
/** This gets called from the memory */
void observer_update(observer_t *obs, event_t e);

int main(void)
{
    /* This is the memory of interest to the observers */
    memory_t *memory = new_memory();

    observer_t *process1 = new_observer(getpid(), memory, EVENT_1);
    observer_t *process2 = new_observer(getpid()+1, memory, EVENT_2);
    observer_t *process3 = new_observer(getpid()+2, memory, EVENT_3);

    printf("Expecting process1 to be notified for EVENT_1...\n");
    memory->notify(memory, EVENT_1);
    printf("Again...\n");
    memory->notify(memory, EVENT_1);
    printf("Expecting process2 to be notified for EVENT_2...\n");
    memory->notify(memory, EVENT_2);
    printf("Expecting process3 to be notified for EVENT_3...\n");
    memory->notify(memory, EVENT_3);
    printf("Expecting process2 to be notified for EVENT_2 again...\n");
    memory->notify(memory, EVENT_2);

    memory->detach(memory, process1);

    printf("Expecting process2 and process3 only to be notified...\n");
    memory->notify(memory, EVENT_1);
    memory->notify(memory, EVENT_1);
    memory->notify(memory, EVENT_2);
    memory->notify(memory, EVENT_3);
    memory->notify(memory, EVENT_2);

    memory->detach(memory, process2);
    memory->detach(memory, process3);

    printf("No more observers to be notified!\n");
    memory->notify(memory, EVENT_1);
    memory->notify(memory, EVENT_1);
    memory->notify(memory, EVENT_2);
    memory->notify(memory, EVENT_3);
    memory->notify(memory, EVENT_2);

    exit(EXIT_SUCCESS);
}


memory_t * new_memory(void)
{
    memory_t *memory;

    /* Should be a call to mmap() rather than malloc() / It is just for testing convenience. */
    memory = (memory_t *) malloc(sizeof(memory_t));

    for (int i = 0; i < MAX_OBSERVERS; i++) {
        memory->obs[i] = NULL;
    }

    memory->attach = memory_attach;
    memory->detach = memory_detach;
    memory->notify = memory_notify;

    return memory;
}

observer_t * new_observer(pid_t pid, memory_t *memory, event_t e)
{
    observer_t *observer;

    observer = (observer_t *) malloc(sizeof(observer_t));
    observer->pid = pid;
    observer->event = e;

    observer->update = observer_update;
    memory->attach(memory, observer);

    return observer;
}

void memory_attach(memory_t *memory, observer_t *obs)
{
    for (int i = 0; i < MAX_OBSERVERS; i++) {
        if (memory->obs[i] == NULL) {
            printf(">> Memory attaching observer %d\n", obs->pid);

            memory->obs[i] = obs;
            break;
        }
    }
}

void memory_detach(memory_t *memory, observer_t *obs)
{
    for (int i = 0; i < MAX_OBSERVERS; i++) {
        if (memory->obs[i] == obs) {
            printf(">> Memory detaching observer %d\n", obs->pid);

            memory->obs[i] = NULL;
            break;
        }
    }
}

void memory_notify(memory_t *memory, event_t e)
{
    printf(">> Memory notifying event %u\n", (unsigned) e);

    for (int i = 0; i < MAX_OBSERVERS; i++) {
        observer_t *obs = memory->obs[i];

        if (obs) {
            obs->update(obs, e);
        }
    }
}

void observer_update(observer_t *obs, event_t e)
{
    if (obs->event == e) {
        printf(">> Observer %d has received the update for event %d\n", obs->pid, e);
    }
}
