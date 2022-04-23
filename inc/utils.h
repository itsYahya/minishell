#ifndef UTILS_H
# define UTILS_H

# include "token.h"

typedef struct s_mut {
	void	**content;
	int		len;
	int		size;
	int		defsize;
}	t_mut;

int		is_space(char c);
int		is_alphanum(char c);
int		has_chars(char c, char *chrs);
int		is_special(char *s);
int		ft_putstr(int fd, char *s);
char	*ft_strndup(char *src, int len);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2, int s2_len);
void	ft_strncpy(char *dest, char *src, unsigned int size);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_itoa(int nbr);
int		mut_add(t_mut *arr, void *new_value);
void	init_mut(t_mut *arr, int defsize);
int		search_mut(t_mut *arr, char *name);
int		clone_env(t_mut *arr, char *env[]);
int		show_errno(char *basename, char *filename);
int		til_set(char *str, char *set, int n);
int		expandable(t_list *tks);
char	*get_tmp(void);
int		ft_append(char *dest, char *src, int len);
int		til_set(char *str, char *set, int n);
int		is_word(t_list *item);
int		has_chars(char c, char *chrs);
int		ft_strlen(char *s);
int		ft_intlen(int n);

#endif
