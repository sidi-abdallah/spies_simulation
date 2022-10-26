/*
 * An Observer design pattern.
 */

#ifndef OBSERVER_H
#define OBSERVER_H


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
void observer_update(observer_t *obs, event_t e);

#endif /* OBSERVER_H */
