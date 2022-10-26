/*
 * An Observer design pattern.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "observer.h"
#include "logger.h"

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
            log_info("Shared memory attaching observer %d", obs->pid);
            memory->obs[i] = obs;
            break;
        }
    }
}

void memory_detach(memory_t *memory, observer_t *obs)
{
    for (int i = 0; i < MAX_OBSERVERS; i++) {
        if (memory->obs[i] == obs) {
            log_info("Memory detaching observer %d", obs->pid);
            memory->obs[i] = NULL;
            break;
        }
    }
}

void memory_notify(memory_t *memory, event_t e)
{
    log_info("Memory notifies event %u", (unsigned) e);

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
        log_info("Observer %d has received the update for event %d", obs->pid, e);
    }
}
