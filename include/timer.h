#ifndef TIMER_H
#define TIMER_H

/**
 * \file timer.h
 *
 * Defines functions used by the timer.
 */

#include "memory.h"

/**
 * \brief Collect pid of the main process.
 */
pid_t get_pids_processes(void);

/**
 * \brief Send signals to the main process a defined number of times with a span defined in common.h.
 */
void sent_sig(void);

#endif /* TIMER_H */
