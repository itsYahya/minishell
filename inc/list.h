#ifndef LIST_H
# define LIST_H

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

void			ft_lstadd_front(t_list **list, t_list *new_);
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *head);
t_list			*ft_lstlast(t_list *head);
void			ft_lstadd_back(t_list **head, t_list *new_);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **list, void (*del)(void *));
void			ft_lstiter(t_list *node, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst,
					void *(*f)(void *), void (*del)(void *));

#endif
