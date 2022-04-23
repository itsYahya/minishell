#ifndef EXPORT_H
# define EXPORT_H

# include "utils.h"

int		ft_degit(char ch);
int		ft_valide_name(char *name, int *plus, int *equal);
int		ft_parsword(char *word, char **name, char **value);
void	ex_free(char *value, char *env);
void	ex_printenv(t_mut *genv);
int		exporting(char *word, int plus, int equal, t_mut *genv);
int		ex_add(char *name, char *value, int equal, t_mut *genv);
int		ex_overwrite(char *name, char *value, int pos, t_mut *genv);
int		ex_append(char *name, char *value, int pos, t_mut *genv);

#endif