#ifndef TIMER_H
#define TIMER_H

#define ROUND_NUMBER 2016 
#define TIME_STEP 200000

// struct Processes_Pids {
//      int pid;
//      int a;
//      int pid_spy_simulation;
//      // int pid_spy_simulation;
//      // int pid_spy_simulation;
//      // int pid_spy_simulation;
// };

 
/**
 * \brief Sets up the timer using the TIME_STEP value.
 */
void set_timer(void);

/**
 * \brief Defines signal handler for the monitor (used by \fn set_signals()).
 *
 * \param signum The signal number.
 */
void handler(int signum);

/**
 * \brief Sets up the signal handler.
 */
void set_signals(void);

void create_sem_memory_for_test(void);

void sent_sig(void);

#endif /* TIMER_H */