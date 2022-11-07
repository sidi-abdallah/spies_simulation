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
#include <string.h>
#include <ncurses.h>

#include "monitor.h"
#include "xxxxxxxxxxx.h"

WINDOW *main_window;
WINDOW *city_window;
WINDOW *character_window;
WINDOW *mailbox_content_window;
WINDOW *enemy_country_monitor;

int old_cursor;
int cell_type_colors[5];
int colored_text[8];
int color_pair_black;

void detect_mouse()
{
    mmask_t mask;

    if (NCURSES_MOUSE_VERSION > 0) {
        addstr("This version of NCurses supports the mouse.\n");
    } else {
        addstr("This version of NCurses does not support the mouse.\n");
    }
    refresh();
    mask = mousemask(ALL_MOUSE_EVENTS, NULL);
    if (mask == 0) {
        addstr("Unable to access the mouse on this terminal.\n");
    } else {
        addstr("Mouse events can be captured.\n");
    }

    getch();
}

void create_color_pairs()
{
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_RED);
    init_pair(3, COLOR_WHITE, COLOR_GREEN);
    init_pair(4, COLOR_WHITE, COLOR_YELLOW);
    init_pair(5, COLOR_WHITE, COLOR_BLUE);
    init_pair(6, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(7, COLOR_WHITE, COLOR_CYAN);
    init_pair(8, COLOR_WHITE, COLOR_WHITE);

    cell_type_colors[RESIDENTIAL_BUILDING] = COLOR_PAIR(5);
    cell_type_colors[WASTELAND] = COLOR_PAIR(3);
    cell_type_colors[COMPANY] = COLOR_PAIR(2);
    cell_type_colors[SUPERMARKET] = COLOR_PAIR(4);
    cell_type_colors[CITY_HALL] = COLOR_PAIR(6);

    colored_text[COLOR_BLACK] = COLOR_PAIR(1);
    colored_text[COLOR_RED] = COLOR_PAIR(2);
    colored_text[COLOR_GREEN] = COLOR_PAIR(3);
    colored_text[COLOR_YELLOW] = COLOR_PAIR(4);
    colored_text[COLOR_BLUE] = COLOR_PAIR(5);
    colored_text[COLOR_MAGENTA] = COLOR_PAIR(6);
    colored_text[COLOR_CYAN] = COLOR_PAIR(7);
    colored_text[COLOR_WHITE] = COLOR_PAIR(8);

    init_pair(9, COLOR_BLACK, COLOR_BLACK);
    color_pair_black = COLOR_PAIR(9);
}

void init_monitor_elements(WINDOW *window, memory_t *mem, int rows, int columns)
{
    set_monitor_title(window, "LICENSE TO KILL (v. 0.2)");

    city_window = subwin(window, rows / 2 + 8, columns / 2, 2, 0);                   /* Top left */
    character_window = subwin(window, rows / 2 + 8, 0, 2, columns / 2);              /* Top right */
    mailbox_content_window = subwin(window, 0, columns / 2, rows / 2 + 10, 0);        /* Bottom left */
    enemy_country_monitor = subwin(window, 0, columns / 2, rows / 2 + 10, columns / 2);  /* Bottom right */

    box(city_window, 0, 0);
    box(character_window, 0, 0);
    box(mailbox_content_window, 0, 0);
    box(enemy_country_monitor, 0, 0);

    show_general_information(city_window);
    display_city(city_window, mem->map, rows, columns);
    display_character_information(character_window, mem);
    display_mailbox_content(mailbox_content_window, mem);
    display_enemy_country_monitor(enemy_country_monitor);
}

void set_monitor_title(WINDOW *window, const char *title)
{
    int title_column;

    title_column = main_window->_maxx / 2 - strlen(title) / 2;
    wattron(window, A_BOLD);
    mvwprintw(main_window, 0, title_column, "%s", title);
    wattroff(window, A_BOLD);
}

void set_city_legend(WINDOW *window, int row, int col)
{
    wattron(window, A_BOLD);
    mvwprintw(window, row, col, "City map caption");
    wattroff(window, A_BOLD);

    set_cell_color(window, cell_type_colors[CITY_HALL], row + 2, col);
    mvwprintw(window, row + 2, col + 4, "City Hall");

    set_cell_color(window, cell_type_colors[RESIDENTIAL_BUILDING], row + 4, col);
    mvwprintw(window, row + 4, col + 4, "Residential building");

    set_cell_color(window, cell_type_colors[COMPANY], row + 6, col);
    mvwprintw(window, row + 6, col + 4, "Company");

    set_cell_color(window, cell_type_colors[SUPERMARKET], row + 8, col);
    mvwprintw(window, row + 8, col + 4, "Supermarket");

    set_cell_color(window, cell_type_colors[WASTELAND], row + 10, col);
    mvwprintw(window, row + 10, col + 4, "Wasteland");
}

void display_city(WINDOW *window, map_t map, int rows, int columns)
{
    int row_offset;
    int col_offset;

    set_city_legend(window, 6, 2);

    for (int i = 0; i < map.columns; i++) {
        for (int j = 0; j < map.rows; j++) {
            row_offset = (rows / 6) + j;
            col_offset = (columns / 5) + (i * 3);
            switch (map.cells[j][i].type) {
                case SUPERMARKET:
                    wattron(window, colored_text[COLOR_YELLOW]);
                    mvwaddstr(window, row_offset, col_offset, " s ");
                    wattroff(window, colored_text[COLOR_YELLOW]);
                    break;
                case RESIDENTIAL_BUILDING:
                    wattron(window, colored_text[COLOR_BLUE]);
                    mvwaddstr(window, row_offset, col_offset, " r ");
                    wattroff(window, colored_text[COLOR_BLUE]);
                    break;
                case COMPANY:
                    wattron(window, colored_text[COLOR_RED]);
                    mvwaddstr(window, row_offset, col_offset, " c ");
                    wattroff(window, colored_text[COLOR_RED]);
                    break;
                case CITY_HALL:
                    wattron(window, colored_text[COLOR_MAGENTA]);
                    mvwaddstr(window, row_offset, col_offset, " * ");
                    wattroff(window, colored_text[COLOR_MAGENTA]);
                    break;
                default:
                    wattron(window, colored_text[COLOR_GREEN]);
                    mvwaddstr(window, row_offset, col_offset, " . ");
                    wattroff(window, colored_text[COLOR_GREEN]);
                    break;
            }
        }
    }
    wrefresh(window);
}

void set_cell_color(WINDOW *window, int color, int row, int col)
{
    wattron(window, color);
    mvwprintw(window, row, col, "  ");
    wattroff(window, color);
}

void show_general_information(WINDOW *window)
{
    int title_column;
    char *title = "CITY MAP AND GENERAL INFORMATION";

    title_column = window->_maxx / 2 - strlen(title) / 2;

    wattron(window, A_BOLD | A_UNDERLINE);
    mvwprintw(window, 1, title_column, "%s", title);
    wattroff(window, A_BOLD | A_UNDERLINE);

    mvwprintw(window, 20, 2, "Step: ");
    mvwprintw(window, 20, 20, "Time: ");
    wrefresh(window);
}

void display_general_information_values(WINDOW *window, memory_t *mem)
{
    double elapsed_time;
    int hour;
    int minutes;
    char *result = NULL;

    elapsed_time = steps_to_half_hours(mem->elapsed_time);
    hour = (int) elapsed_time;
    minutes = ((elapsed_time - hour) > 0) ? 30 : 00;

    mvwprintw(window, 20, 8, "%d", mem->elapsed_time);
    mvwprintw(window, 20, 26, "       ");
    mvwprintw(window, 20, 26, "%.2d h %.2d", hour, minutes);
    if (mem->simulation_has_ended > 0) {
        switch (mem->simulation_has_ended) {
            case 1:
                result = "Spies have won! The spy network has fled!";
                break;
            case 2:
                result = "Counter officer has discovered the mailbox!";
                break;
            case 3:
                result = "Spies have won! Counter officer did not find the mailbox!";
                break;
            default:
                break;
        }

        mvwprintw(window, 25, 2, "End of simulation: %s", result);
    }
    wrefresh(window);
}

void display_citizen_information(WINDOW *window, memory_t *mem, int row, int column)
{
    int i;
    int number_of_citizens_at_home = 0;
    int number_of_citizens_at_work = 0;
    int number_of_citizens_walking = 0;
    citizen_t current_citizen;

    for (i = 0; i < NUMBER_OF_CITIZENS; i++) {
        current_citizen = mem->characters.citizens[i];
        if (compare_cells(current_citizen.home, current_citizen.location)) {
            number_of_citizens_at_home++;
        } else if (compare_cells(current_citizen.working_place, current_citizen.location)) {
            number_of_citizens_at_work++;
        } else {
            number_of_citizens_walking++;
        }
    }
    wattron(window, A_BOLD);
    mvwprintw(window, row, column, "Citizens");
    wattroff(window, A_BOLD);
    mvwprintw(window, row + 1, column, "  At home: %.3d", number_of_citizens_at_home);
    mvwprintw(window, row + 2, column, "  At work: %.3d", number_of_citizens_at_work);
    mvwprintw(window, row + 3, column, "  Walking: %.3d", number_of_citizens_walking);
    wrefresh(window);
}

void display_spy_information(WINDOW *window, memory_t *mem, int row, int column, int number)
{
    spy_t spy;

    spy = mem->characters.spies[number];

    wattron(window, A_BOLD);
    mvwprintw(window, row, column, "Spy n°%d", number);
    wattroff(window, A_BOLD);
    mvwprintw(window, row + 1, column, "  Id: %d", spy.id);
    mvwprintw(window, row + 2, column, "  Health: %d", spy.health_points);
    mvwprintw(window, row + 3, column, "  Position: (%d,%d)", spy.location.row, spy.location.column);
    mvwprintw(window, row + 4, column, "  Home pos: (%d,%d)", spy.home.row, spy.home.column);
    mvwprintw(window, row + 5, column, "  Stolen companies: %d", spy.nb_of_stolen_companies);
    if (strcmp(spy.stolen_message.content, EMPTY) == 0) {
        mvwprintw(window, row + 6, column, "  Message stolen: none");
    } else {
        mvwprintw(window, row + 6, column, "  Message stolen: yes ");
    }
    if (spy.has_license_to_kill) {
        mvwaddstr(window, row + 7, column, "  License to kill: yes");
    } else {
        mvwaddstr(window, row + 7, column, "  License to kill: no ");
    }
    wrefresh(window);
}

void display_case_officer_information(WINDOW *window, memory_t *mem, int row, int column)
{
    case_officer_t co;

    co = mem->characters.case_officers[0];

    wattron(window, A_BOLD);
    mvwprintw(window, row, column, "Case Officer");
    wattroff(window, A_BOLD);
    mvwprintw(window, row + 1, column, "  Id: %d", co.id);
    mvwprintw(window, row + 2, column, "  Health: %d", co.health_points);
    mvwprintw(window, row + 3, column, "  Position: (%d,%d)", co.location.row, co.location.column);
    mvwprintw(window, row + 4, column, "  Home pos: (%d,%d)", co.home.row, co.home.column);
    mvwprintw(window, row + 5, column, "  Mailbox pos: (%d,%d)", co.mailbox.row, co.mailbox.column);
}

void display_counterintelligence_officer_information(WINDOW *window, memory_t *mem, int row, int col)
{
    counterintelligence_officer_t cio;

    cio = mem->characters.counter_officers[0];

    wattron(window, A_BOLD);
    mvwprintw(window, row, col, "Counterintelligence Officer");
    wattroff(window, A_BOLD);
    mvwprintw(window, row + 1, col, "  Id: %d", cio.id);
    mvwprintw(window, row + 2, col, "  Health: %d", cio.health_points);
    mvwprintw(window, row + 3, col, "  Position: (%d,%d)", cio.location.row, cio.location.column);
    mvwprintw(window, row + 4, col, "  City Hall pos: (%d,%d)", cio.city_hall.row, cio.city_hall.column);
    if (co.mailbox_location.row != -1) {
        mvwprintw(window, row + 5, col, "  Mailbox pos: (%d,%d)    ", cio.mailbox_location.row,
                  cio.mailbox_location.column);
    } else {
        mvwprintw(window, row + 5, col, "  Mailbox pos: not found");
    }
    mvwprintw(window, row + 6, col, "  Target:     ");
    mvwprintw(window, row + 6, col, "  Target: %d", cio.targeted_character_id);

    wrefresh(window);
}

void display_character_information(WINDOW *window, memory_t *mem)
{
    int title_column;
    int first_column;
    int second_column;
    char *title = "CHARACTERS";

    title_column = window->_maxx / 2 - strlen(title) / 2;
    first_column = 2;
    second_column = window->_maxx / 2;

    wattron(window, A_BOLD | A_UNDERLINE);
    mvwprintw(window, 1, title_column, "%s", title);
    wattroff(window, A_BOLD | A_UNDERLINE);
    display_case_officer_information(window, mem, 3, first_column);
    display_spy_information(window, mem, 3, second_column, 0);
    display_spy_information(window, mem, NB_OF_INFORMATION_FIELDS + 4, first_column, 1);
    display_spy_information(window, mem, NB_OF_INFORMATION_FIELDS + 4, second_column, 2);
	display_counterintelligence_officer_information(window, mem, NB_OF_INFORMATION_FIELDS * 2 + 5, first_column);
    display_citizen_information(window, mem, NB_OF_INFORMATION_FIELDS * 2 + 5, second_column);
    wrefresh(window);
}

void display_mailbox_content(WINDOW *window, memory_t *mem)
{
    int i;
    int title_column;
    int nb_lines;
    char *title = "MAILBOX CONTENT";

    nb_lines = 1;
    title_column = window->_maxx / 2 - strlen(title) / 2;
    wattron(window, A_BOLD | A_UNDERLINE);
    mvwprintw(window, nb_lines, title_column, "%s", title);
    wattroff(window, A_BOLD | A_UNDERLINE);

    nb_lines = 3;
    for (i = 0; i < mem->mailbox_nb_of_msgs; i++) {
		clear_line(window, nb_lines);
        if (strcmp(mem->mailbox_content[i].content, FAKE_MESSAGE) == 0) {
            mvwprintw(window, nb_lines, 2, ">> [%d] %s (P%d)", (i + 1), "FAKE MESSAGE",
                      mem->mailbox_content[i].priority);
        } else {
            mvwprintw(window, nb_lines, 2, ">> [%d] %s (P%d)", (i + 1),
                      mem->mailbox_content[i].content, mem->mailbox_content[i].priority);
        }
        nb_lines += 1;
    }

    wrefresh(window);
}

void display_enemy_country_monitor(WINDOW *window)
{
    int nb_lines;
    int title_column;
    char buffer[MAX_MESSAGE_LENGTH];
    char *title = "ENEMY COUNTRY MONITOR";

    nb_lines = 1;
    title_column = window->_maxx / 2 - strlen(title) / 2;

    wattron(window, A_BOLD | A_UNDERLINE);
    mvwprintw(window, nb_lines, title_column, "%s", title);
    wattroff(window, A_BOLD | A_UNDERLINE);

    /*
     * -------------------------------------------------------------------------
     *
     * Choose your way to display deciphered messages in this window!!!! 
     *
     * -------------------------------------------------------------------------
     */
     

    wrefresh(window);
}

void update_values(memory_t *mem) {
    display_general_information_values(city_window, mem);
    display_character_information(character_window, mem);
    display_mailbox_content(mailbox_content_window, mem);
    display_enemy_country_monitor(enemy_country_monitor);
    mem->memory_has_changed = 0;
}

