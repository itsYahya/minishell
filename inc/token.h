#ifndef TOKEN_H
# define TOKEN_H

# include "list.h"

typedef enum e_token_type
{
	TK_WHITESPACE = 1,
	TK_EXPRESSION = 2,
	TK_TEMPLATE_LITERAL = 4,
	TK_LITERAL = 8,
	TK_REDIRICT_OUT = 16,
	TK_REDIRICT_IN = 32,
	TK_APPEND = 64,
	TK_HEREDOC = 128,
	TK_VAR = 256,
	TK_ASTERISK = 512,
	TK_AND = 1024,
	TK_OR = 2048,
	TK_PIPE = 4096,
	TK_SUB_CMD = 8192,
	TK_PARNETHESIS = 16384,
	TK_EOF = 32768,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				len;
}	t_token;

/*
 * this constant is related to e_token_type
 * TK_ASTERISK
 * TK_VAR
 * TK_LITERAL
 * TK_TEMPLATE_LITERAL
 * TK_EXPRESSION
 * any change to its values should effect this too.
 * */
# define TK_WORDABLE 0b1100001110

t_list			*tokenizer(char *line);
t_list			*new_token(enum e_token_type type, char *value);
void			free_token(void *ptr);
int				tk_set(t_token *tk,
					enum e_token_type type, char *value, int len);
int				tk_cpy(char *dst, t_token *tk);
int				tk_len(t_token *tk);
int				tk_cmp(t_token *tk, char *str);
unsigned int	scan_word(char *s);
unsigned int	scan_literal(char *s);
unsigned int	scan_var(char *s);
t_list			*tk_ignore(t_list *cur,
					enum e_token_type types, int should_free);
void			free_token_only(void *ptr);
int				is_var(char *line);
int				check_whitespace(char *line, t_token *token);

#endif
