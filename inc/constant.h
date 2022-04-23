#ifndef CONSTANT_H
# define CONSTANT_H

# include "token.h"
# include "astree.h"

# define PROMPT "\x1B[36m[minishell]\x1B[32m$\x1B[0m "
# define PROMPT_2 "> "
# define CHAR_DOUBLE_QOUTE '"'
# define CHAR_SINGLE_QOUTE '\''
# define SH_SPECAIL_PARMS "?"
# define SET_WHITESPACE " \r\n\v\t"
# define O_CREAT_PERMISSIONS (0644)

/* 
 * This macro is used to easily
 * cast t_list content to t_token
 * avoiding extra lines
 * @params node should be t_list pointer
 *
 * TK(node)->len = -1;
 * */
t_token			*tk(t_list *head);
t_simple_cmd	*ncmd(t_node *node);
t_re_stat		*nred(t_node *node);
t_redirect		*lred(t_list *head);
t_complex_cmd	get_ccmd(t_node *node);

#endif
