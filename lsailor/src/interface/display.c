/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:44:46 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/19 20:53:03 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sail.h"
/*
static void		init_colors(void)
{
	start_color();
	init_color(COLOR_YELLOW, 180, 180, 180);
	init_color(COLOR_CYAN, 0, 850, 850);
	init_color(COLOR_BLUE, 400, 400, 1000);
	init_color(COLOR_GREEN, 0, 800, 0);
	init_color(COLOR_RED, 900, 0, 0);
	init_color(COLOR_BLACK, 0, 0, 0);
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_YELLOW);
}
*/

void			resize_window(WINDOW *w_nav, WINDOW *w_cont)
{
	clear();
	refresh();
	delwin(w_nav);
	delwin(w_cont);
	w_nav = newwin(LINES, COLS / 2, 0, 0);
	w_cont= newwin(LINES, COLS / 2, 0,	COLS / 2);
	//fill_arena(vm->height, vm, init_m(), vm->m_win);
	//print_panel(vm->s_win, vm->processes, vm);
	box(w_nav, 0, 0);
	box(w_cont, 0, 0);
	wrefresh(w_nav);
	wrefresh(w_cont);
}

void	display_files(void)
{
	int key;
	WINDOW *w_nav;
	WINDOW *w_cont;

	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	intrflush(stdscr, FALSE);
	setlocale(LC_ALL, "");
	curs_set(0);
	w_nav = NULL;
	w_cont = NULL;
	resize_window(w_nav, w_cont);
	while ((key = getch()) != 'q') {
		if (key == KEY_RESIZE) {
			resize_window(w_nav, w_cont);
			refresh();
		}
	}
    endwin();
}
