/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/08/19 14:07:46 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H

# include "libft.h"
# include "ft_printf.h"
# include <stdbool.h>


# define C_RED		"\x1b[31m"
# define C_GREEN	"\x1b[32m"
# define C_YELLOW	"\x1b[33m"
# define C_BLUE		"\x1b[34m"
# define C_MAGENTA	"\x1b[35m"
# define C_CYAN		"\x1b[36m"
# define C_RESET	"\x1b[0m"

/*
** op.h header provided as attachment for Corewar project
*/

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				4096
#define IDX_MOD					512
#define CHAMP_MAX_SIZE			768

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define N_LABEL_CHARS			37      // needs a recount
#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

/*
**
*/

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		header_s
{
  unsigned int		magic;
  char				prog_name[PROG_NAME_LENGTH + 1];
  unsigned int		prog_size;
  char				comment[COMMENT_LENGTH + 1];
}					header_t;

/*
**  Bla
*/

typedef struct		s_info
{
	char            *file_name;
    t_list          *file_content;
}					t_info;

/*
**  Tokenizer
**    token_string = raw input string
**    type = unique integer indentifier 
**    start = character count from start of line to start of token string
**    line = line number where token string starts
*/

typedef struct		s_token
{
	char			*token_string;
	unsigned char	type;
	unsigned char	start;
	unsigned char	line;
}					t_token;

#endif