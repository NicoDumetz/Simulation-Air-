##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile compile my radar
##

SRC	=	main.c \
		ressources/my_radar.c \
		ressources/set_game.c \
		ressources/display.c \
		ressources/my_getnbr.c \
		ressources/my_str_to_word_array.c \
		ressources/my_strcat.c \
		ressources/my_strlen.c \
		ressources/settings.c \
		ressources/colision_plane.c \
		ressources/colision_tower.c

OBJ	=	$(SRC:.c=.o)

CFLAGS += -g

NAME 	= 	my_radar

LDFLAGS = -lcsfml-graphics -lcsfml-system -lcsfml-audio -lcsfml-window -lm

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm *.o
	cd ressources && rm *.o

fclean:		clean
	rm -f $(NAME)

re:	fclean all
