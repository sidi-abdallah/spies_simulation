#ifndef TIMER_H
#define TIMER_H

#define ROUND_NUMBER 2016 
 
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



#endif /* TIMER_H */