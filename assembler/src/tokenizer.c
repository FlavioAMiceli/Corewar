/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/18 15:31:22 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/23 15:08:34 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_asm_obj(t_asm *asm_obj)
{
	t_token *tokens;

	tokens = asm_obj->token_head;
	ft_printf("file_name: [%s]", asm_obj->file_name);
	while (tokens != asm_obj->token_tail)
	{
		ft_printf("t string: %s\n", tokens->string);
		ft_printf("t type: %s\n", tokens->type);
		ft_printf("t row: %s\n", tokens->row);
		ft_printf("t col: %s\n", tokens->col);
		ft_printf("end of current token\n\n");
		tokens = tokens->next;
	}
}

t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

// static t_hmap   *init_token_hmap(void)
// {
//     t_hmap  *token_hmap;
//
//     token_hmap = hmap_new(N_TOKENS);
//
// }

/*
**  Duplicates substring from start of str to next whitespace.
**  Updates *str, starting position of string after extracting current substring.
**  Also updates start, the index for starting position.
**	*col is the character count for that line, (one more than char index)
**	*col's incremented value is for the next token, not current
**
**  Params: str, a string starting at the first char of a token.
			start, the index of the starting character for next token.
**	Initial whitespace jumped over before *str arrives to func()
**  Return: Literal string of a single token.
**	called by:	tokenize()
*/

static char *get_token_string(char *str, int *col)
{
	int		i;

	i = 0;
	if (ft_strchr("\n,\"*;", *str))
		i++;
	if (*str == '"' || *str == '#' || *str == ';')
	{
		i = ft_strchr_int(&str[i], *str == '"' ? '"' : '\n');
		if (i == -1)
			return (NULL);
		++i;
	}
	else
	{
		while (str[i] && ft_isspace(str[i]) == FALSE && str[i] != ',')
			++i;
			
	}
	*col += i;
	return (ft_strndup(str, i));
}
// static char *get_token_string(char *str, int *col)
// {
// 	char    *curr;
// 	char	*token_string;
// 	int		i;
// 	// TODO: check that separator character doesn't end up together with previous token
// 	curr = str;

// 	/*

// 	<.name> until space found or newline
// 	<"Candy"> until '"' found
// 	<# some comment> from # until newline

// 	.name "Candy"
// 	.comment "content"

// 		st		r1, r12
// 		ld      %0 , r14
// 		zjmp    %:base

// 	def:
// 		st		r9, -256
// 		st		r10, -256

// 	*/
// 	// if first character NEWLINE(\n) or COMMA(,)
// 	// if (*str == '\n' || *str == ',')
// 	// {
// 	// 	(*col)++;
// 	// 	return (*str == '\n' ? ft_strdup("\n") : ft_strdup(","));
// 	// }

// 	if (ft_strchr("\n,\"*;", *str))
// 		i++;

// 	// if (*str == '\n' || *str == ',')
// 	// 	i++;

// 	else if (*str == '"' || *str == '#' || *str == ';')
// 	{
// 		i = ft_strchr_int(str + 1, *str == '"' ? '"' : '\n');
// 		if (i == -1)
// 			return (NULL);
// 		++i; // ft_strchr_int returns index, so must increase by one
// 		// return (ft_strndup(str, i + 1));
// 	}

// 	// else if (*str == '"')
// 	// {
// 	// 	i = ft_strchr_int(str + 1, '"');
// 	// 	if (i == -1)
// 	// 		return (NULL);
// 	// 	return (ft_strndup(str, i + 1));
// 	// }

// 	// else if (*str == '#' || *str == ';')
// 	// {
// 	// 	i = ft_strchr_int(str + 1, '\n');
// 	// 	if (i == -1)
// 	// 		return (NULL);
// 	// 	return (ft_strndup(str, i + 1));
// 	// }

// 	else
// 	{
// 		while (str[i] && ft_isspace(str[i]) == FALSE && str[i] != ',')
// 			++i;
			
// 	}

// 	*col += i;
// 	token_string = ft_strndup(str, i);
// 	return (token_string);





// 	else if (*curr != COMMENT_CHAR && *curr != ';')
// 	{
// 		i = ft_strchr_int(str + 1, *str == '"' ? '"' : '/n');
// 		if (i == -1)
// 			return (NULL);
// 		return (ft_strndup(str, i + 1));
// 	}


// 	if (*str == '"')
// 	{
// 		curr++;
// 		while (*curr && *curr != '"')
// 			curr++;
// 		if (*curr == '"')
// 			curr++;
// 	}
// 	else
// 	{
// 		while (*curr && *curr != '\n')
// 		{
// 			curr++;
// 			i++;
// 		}
// 	}
// 	*col += i;
// 	token_string = ft_strndup(str, i);
// 	return (token_string);
// }


// static int	validate_registry_lexical(char *str)
// {
//
//
// 	return (FALSE);
// }
/*
**  TOKENS:
**	1-20 intructions
**	20-29 plain text
**	30-39 non action signifiers
**	40-49 arguments
**	50-59 syntax character
**
*/

static int		get_opcode(char *str)
{
	char	i;

	i = 0;

	while (i < N_OPCODES)
	{
		if (ft_strequ(str, op_tab[i].op_str))
			return(op_tab[i].opcode);
		++i;
	}
	return (0);
}

/*
**	*str argument will only be token string
**		ex:
**			arriere:	ld	%-5, r5
**				-> [arrieere:][ld][%-5][,][r5][\n]
**
**
**	called by:	tokenize()
*/

static int  get_type(char *str)
{
    if (*str == COMMENT_CHAR || *str == ';')
        return (COMMENT_TKN);
    else if (*str == COMMAND_CHAR)
        return (COMMAND_TKN);
    else if (*str == DIRECT_CHAR)
        return (DIRECT_TKN);
	else if (*str == REGISTRY_CHAR)
        return (REGISTRY_TKN);
    else if (*str == LABEL_CHAR)
        return (INDIRECT_LABEL_TKN);
	else if (*str == '-' || ft_isdigit(*str))
        return (INDIRECT_TKN);
	else if (ft_strchr(LABEL_CHARS, *str))
	{
		if (str[ft_strlen(str) - 1] == ':')
        	return (LABEL_TKN);
		return (get_opcode(str));
	}
    else if (*str == SEPARATOR_CHAR)
        return (SEPARATOR_TKN);
	else if (*str == '\n')
        return (ENDLINE_TKN);
	else if (*str == '"')
        return (STRING_TKN);
	return (-1);
}

/*
**  Tokenizes one line of asm.
**
**  Params: str, a single line from the source retrieved using gnl.
**                  expected to be sequential.
**  Return:
**
**	called by:	read_file()
**
*/


void	tokenize(char *str, t_asm *info)
{
	static int      row;
	static t_token	*tail;
	int             col;
	t_token         *token;
	// int		ch;

	// printf("entering tokenize(), row:%d\n", row);
	col = 1;
	if (!row)
		row = 1;
	while (*str)
	{

		// while ((ch = getchar()) != '\n' && ch != EOF)
    	// 	continue;
		while (*str != '\n' && ft_isspace(*str))
		{
			col++;
			str++;
			// printf("str: %s %p		col:%d\n", str, str, col);
		}
		token = (t_token *)ft_memalloc(sizeof(t_token));
		token->row = row;
		token->col = col;
		token->string = get_token_string(str, &col);
		// printf("str addr:%p\n", str);
		str += ft_strlen(token->string);
		token->type = get_type(token->string);
		if (info->token_head == NULL)
			info->token_head = token;
		else
			tail->next = token;
		tail = token;
		// if (*str == '\n')
		// 	break ;
		// if (token->type == 51)
		// 	ft_printf("{%d}, {'nl'}\n", token->type); // remove
		// else
		// 	ft_printf("{%d}, {%s}\n", token->type, token->string); // remove
	}
	row++;
}
