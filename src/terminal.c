#include <stdlib.h>
#include <string.h>
#include <term.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "utils.h"
#include "minishell.h"

int	duptty(void)
{
	char	*device;
	int		dev_fd;

	device = ttyname(STDERR_FILENO);
	if (device == NULL)
	{
		ft_merror("", ": failed to get terminal device");
		return (0);
	}
	dev_fd = open(device, O_WRONLY);
	if (dev_fd == -1)
	{
		ft_merror("", ": failed to open terminal device");
		return (0);
	}
	return (dup2(dev_fd, STDOUT_FILENO) != -1);
}

int	my_atoi(char *buf, int *n)
{
	int	i;

	i = 0;
	*n = 0;
	while (buf[i] && buf[i] >= '0' && buf[i] <= '9')
	{
		*n *= 10;
		*n += buf[i] - '0';
		i++;
	}
	return (i);
}

int	read_until(char *buf, int fd, char c)
{
	char	r;
	int		i;
	int		n;

	r = '\0';
	i = 0;
	while (r != c)
	{
		n = read(fd, &r, 1);
		if (n == 0)
			return (0);
		buf[i++] = r;
	}
	buf[i] = 0;
	return (i > 1);
}

/*
 * get_cursor_position
 *
 * to get terminal curson position we need to:
 * 
 * 1. disable echo attr in terminal
 * 	so nothing typed will be showed in terminal
 *
 * 2. disable icanon attr
 * 	this enables certain commands
 *
 * 3. print \033[6n]
 * 	this command will put [pos_y;pos_xRXXX
 * 	to stdout
 * 
 * 4. parsing result to get pos_y and pos_x
 * 
 * example: [42;1RXXXXX
 * x = 1
 * y = 42
 *
 * on success it fills x and y with corresponding values
 * on error x=-1 and y=-1
 * */
int	get_cursor_position(int *x, int *y)
{
	struct termios	term;
	struct termios	restore;
	char			*buf;
	int				i;

	buf = malloc(sizeof(char) * 20);
	*y = -1;
	*x = -1;
	i = 0;
	tcgetattr(0, &term);
	tcgetattr(0, &restore);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &term);
	ft_putstr(1, "\033[6n");
	if (buf == NULL || read_until(buf, 0, 'R') == 0)
	{
		tcsetattr(0, TCSANOW, &restore);
		return (free(buf), 0);
	}
	i += my_atoi(buf + 2, y) + 3;
	my_atoi(buf + i, x);
	*x -= 1;
	tcsetattr(0, TCSANOW, &restore);
	return (free(buf), 1);
}

void	move_cursor(int init_x)
{
	int		x;
	int		y;
	char	*cap;

	cap = tgetstr("cm", 0);
	if (cap == NULL || get_cursor_position(&x, &y) == 0)
		return ;
	cap = tgoto(cap, init_x, y - 2);
	tputs(cap, 1, putchar);
}
