/*
 * The License to Kill Project
 *
 * Copyright (C) 2021 Alain Lebret <alain.lebret [at] ensicaen [dot] fr>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*temporaire*/
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
//#include "monitor_common.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>        /* Pour les constantes des modes */
#include <fcntl.h>  
#include <string.h>
/*end temporaire*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <sys/mman.h> 
#include <sys/stat.h>

#include "monitor_common.h"
#include "monitor.h"
#include "memory.h"
#include "posix_semaphore.h"

extern WINDOW *main_window;
extern int old_cursor;

/**
 * \file main.c
 *
 * \brief Creates a new "Terminal User Interface" using ncurses and associated
 * with the given shared memory.
 *
 * The size of the terminal must have at least 40 rows and 145 columns. It
 * is decomposed in four sub-windows:
 * - The "city map and status" window (upper-left)
 * - The "character information" window (upper-right)
 * - The "mailbox content" window (bottom-left)
 * - The "enemy country monitor" window (bottom-right)
 * 'Q', 'q' and 'Esc' keys are used to exit from the TUI.
 */
int main(int argc, char **argv)
{
    int rows;
    int cols;
    int key;
    memory_t *memory;
    monitor_t *monitor;
    sem_t *sem; 
    
    /* ---------------------------------------------------------------------- */ 
    /* The following code only allows to avoid segmentation fault !           */ 
    /* Change it to access to the real shared memory.                         */
    // memory = (memory_t *)malloc(sizeof(memory_t)); 
    // memory->memory_has_changed =  1;
    /* ---------------------------------------------------------------------- */ 

    int shmd = shm_open("/spy_simulation", O_RDWR, (mode_t)0600);
    if(shmd == -1) {
        perror("shmd failed");
    }
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd,0);
    if (memory == MAP_FAILED) {
        perror("mmap failed");
        return -1;
    }

    monitor = (monitor_t *)malloc(sizeof(monitor_t));
    monitor->has_to_update = 0;

    set_timer();
    set_signals();

    if ((main_window = initscr()) == NULL) {
        quit_after_error("Error initializing library ncurses!");
    }

    clear();                  /* Start from an empty screen. */
    cbreak();                 /* No line buffering, pass every key pressed. */
    noecho();                 /* Do not echo the keyboard input. */
    old_cursor = curs_set(0); /* Use and invisible cursor. */
    keypad(stdscr, TRUE);     /* Allows functions keys, arrows, etc. */

    start_color();            /* Allow using colors... */
    create_color_pairs();     /* ... and create color pairs to use */

    if (!is_terminal_size_larger_enough(&rows, &cols)) {
        quit_after_error("Minimal terminal dimensions: 45 rows and 140 columns!");
    }

    /* Initialize terminal user interface elements */
    init_monitor_elements(main_window, memory, rows, cols);

    /*  Loop and get user input  */
    while (true) {
        key = getch();

        switch (key) {
            case 'Q':
            case 'q':
            case 27:
                munmap(memory, sizeof(memory_t));
                close(shmd);
                quit_nicely(NO_PARTICULAR_REASON);
            default:
                break;
        }
    sem = open_semaphore("sem_test-sem");
    P(sem);
    int shmd = shm_open("/share_memory__test",O_RDWR,0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE,MAP_SHARED, shmd,0);
        if (memory->memory_has_changed) {
            update_values(memory);
            memory->memory_has_changed = 0;
        }
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);
    }

}

