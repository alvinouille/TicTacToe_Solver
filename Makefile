NAME	= TicTacToe
SRC		= main.cpp Board.cpp SDL.cpp
OBJ		= $(SRC:.cpp=.o)
CC		= g++
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lSDL2

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -lSDL2
	
clean:
	$(RM) $(OBJ)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re