/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_arena.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/17 13:00:39 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	BELOW NOTES TAKEN FROM COOKBOOK:
**	Cursors are added to the beginning of the list. This means the cursor of the
**	last player (with the biggest id) will be executed first.
**	All registries excepting r1 are initialised with 0. r1 is initialised with
**	the negated player id (r1 = -player_id).
*/

void				create_cursor(t_arena *arena, int i, bool start)
{
	t_cursor		*cursor;

	arena->num_cursors += 1;
	cursor = (t_cursor*)ft_memalloc(sizeof(t_cursor));
	cursor->registry[0] = (i + 1) * -1;
	cursor->position = (MEM_SIZE / arena->num_champs) * i;
	cursor->id = arena->num_cursors;
	cursor->opcode = arena->field[cursor->position];
	if (arena->cursor_head != NULL)
	{
		cursor->next = arena->cursor_head;
		arena->cursor_head->prev = cursor;
	}
	arena->cursor_head = cursor;
	if (start)
		arena->last_champ_alive = i + 1;
}

/*
**	each operation requires a wait time, measured in cycles. func() populates
**	array with wait times, where wait_cycle_arr[opcode - 1] = wait cycles.
**	array is added to arena struct.
*/

static void			cursor_wait_cycle(int *wait_cycle_arr)
{
	wait_cycle_arr[0] = 10;
	wait_cycle_arr[1] = 5;
	wait_cycle_arr[2] = 5;
	wait_cycle_arr[3] = 10;
	wait_cycle_arr[4] = 10;
	wait_cycle_arr[5] = 6;
	wait_cycle_arr[6] = 6;
	wait_cycle_arr[7] = 6;
	wait_cycle_arr[8] = 20;
	wait_cycle_arr[9] = 25;
	wait_cycle_arr[10] = 25;
	wait_cycle_arr[11] = 800;
	wait_cycle_arr[12] = 10;
	wait_cycle_arr[13] = 50;
	wait_cycle_arr[14] = 1000;
	wait_cycle_arr[15] = 2;
}

/*
**	creates all the components necessary for the gameplay to happen. the start
**	of the game will create the same number of cursors as number of champions,
**	though other cursors could be created throughtout the game. create_cursor()
**	requires that the first cursor be the last champion, see not above
**	create_cursor() for more details.
*/

void				initialize_arena(t_arena *arena)
{
	int				i;
	t_champ			*champ;

	i = 0;
	champ = NULL;
	arena->field = (unsigned char *)ft_memalloc(MEM_SIZE);
	cursor_wait_cycle(arena->wait_cycle_arr);
	while (i < arena->num_champs)
	{
		champ = arena->champs[i];
		ft_memcpy(&arena->field[(MEM_SIZE / arena->num_champs) * i],\
		champ->exec_code, champ->real_exec_size);
		create_cursor(arena, i, TRUE);
		++i;
	}
	arena->max_cycle_die = CYCLE_TO_DIE;
}
