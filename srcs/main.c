#include "tt.h"

int		ft_get_random_nb(int start, int end)
{
	return (rand() % end + start);
}

void	ft_clear_screen(int nb)
{
	while (nb--)
		dprintf(1, "\n");
}

void	delay(int nb)
{
	nb  = nb * 1000000;
	while (nb--)
		;
}

void	ft_print_tab(int tab[9], int size)
{
	int i;

	i = 0;
	printf("[");
	while (i != size)
	{
		printf("%d", tab[i]);
		if (i != size - 1)
			printf(", ");
		i++;
	}
	printf("]\n\n");
}

int		is_it_in_it(int nb, int board[9])
{
	int i;

	i = 0;
	while (i < 9)
	{
		if (board[i] == nb)
			return (1);
		i++;
	}
	if (nb == 5)
		return (1);
	return (0);
}

void	print_char(int i)
{
	if (i % 2 == 1 && i >= 0)
		dprintf(1, GREEN " ◼ " RESET);
	if (i % 2 == 0 && i >= 0)
		dprintf(1, CYAN " ◼ " RESET);
	if (i == -1)
		dprintf(1, "   ");
}

void	ft_print_sequence(int sequence[9])
{
	int i;
	int b[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};

	i = 0;
	while (sequence[i] != 0 && i < 9)
	{
		b[sequence[i] - 1] = sequence[i] - 1;
		print_char(b[0]);
		dprintf(1, "|");
		print_char(b[1]);
		dprintf(1, "|");
		print_char(b[2]);
		dprintf(1, "\n---+---+---\n");
		print_char(b[3]);
		dprintf(1, "|");
		print_char(b[4]);
		dprintf(1, "|");
		print_char(b[5]);
		dprintf(1, "\n---+---+---\n");
		print_char(b[6]);
		dprintf(1, "|");
		print_char(b[7]);
		dprintf(1, "|");
		print_char(b[8]);
		ft_clear_screen(38);
		delay(100);
		i++;
	}
}

void	ft_print_grid(int b[9])
{
	print_char(b[0]);
	dprintf(1, "|");
	print_char(b[1]);
	dprintf(1, "|");
	print_char(b[2]);
	dprintf(1, "\n---+---+---\n");
	print_char(b[3]);
	dprintf(1, "|");
	print_char(b[4]);
	dprintf(1, "|");
	print_char(b[5]);
	dprintf(1, "\n---+---+---\n");
	print_char(b[6]);
	dprintf(1, "|");
	print_char(b[7]);
	dprintf(1, "|");
	print_char(b[8]);
	ft_clear_screen(38);
}

int		ft_check_sequence(int sequence[9], int fd)
{
	int b[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
	char buf[2];
	int i;
	int tmp;

	srand(time(NULL));
	buf[0] = 0;
	buf[1] = '\0';
	i = 0;
	ft_clear_screen(100);
	//printf("EN: Your turn!\n\n");
	printf("FR: C'est votre tour!\n\n");
	ft_clear_screen(38);
	delay(200);
	ft_clear_screen(100);
	dprintf(1, "   |   |   \n---+---+---\n   |   |  \n---+---+---\n   |   |  ");
	ft_clear_screen(38);
	while (i < 9 && sequence[i] != 0)
	{
		while (buf[0] == 0 || is_it_in_it(buf[0] - '0', b))
			read(fd, buf, 1);
		tmp = buf[0] - '0';
		b[tmp - 1] = tmp;
		if (sequence[i] == tmp)
			i++;
		else
			return (0);
		ft_clear_screen(100);
		ft_print_grid(b);
	}
	delay(100);
	ft_clear_screen(100);
	if (i == 8)
	{
		dprintf(1, GREEN "Merci d'avoir joué\n" RESET);
		ft_clear_screen(41);
		return (1);
	}
	dprintf(1, GREEN "NIVEAU SUIVANT:" RESET);
	ft_clear_screen(41);
	delay(100);
	return (1);
}

int		main()
{
	int sequence[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	int fd;
	int level;
	int i;
	int tmp;
	char buf[2];

	fd = get_serial();
	//printf("\nEN: Welcome, here is how to play the game:\ntiles will lit up on screen and you'll have to tap the buttons is the same order to move on to the next stage.\n\n");
	printf("FR: Bienvenue, voici comment jouer a ce jeu:\ndes cases vont s'allumer a l'ecran et vous devrez appuyer sur les boutons dans le meme ordre pour pouvoir acceder au niveau suivant.\n\n");
	//printf("PRESS ANY BUTTON TO START\n\n");
	printf("APPUYEZ SUR N'IMPORTE QUEL BOUTON POUR COMMENCER\n\n\n");
	level = 1;
	buf[0] = 0;
	buf[1] = '\0';
	while (buf[0] == 0)
		read(fd, buf, 1);
	while (level <= 8)
	{
		i = -1;
		while (++i < level)
		{
			while (is_it_in_it((tmp = ft_get_random_nb(1, 9)), sequence))
				;
			sequence[i] = tmp;
		}
		ft_clear_screen(100);
		//ft_print_tab(sequence, 9);
		ft_print_sequence(sequence);
		delay(1000);
		if (ft_check_sequence(sequence, fd))
			level++;
		else
		{
			dprintf(1, RED "GAME OVER\n" RESET);
			ft_clear_screen(40);
			return (0);
		}
		delay(200);
	}
	return (0);
}
