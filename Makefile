NAME		= ft_containers

SRC			= main.cpp

OBJ			= $(SRC:.cpp=.o)
INC			= -I.

CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 $(INC)
CXX			= clang++

DEBUG		= -g3
SANITIZE	= -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

sanitize: CXXFLAGS += $(SANITIZE) $(DEBUG)
sanitize: all

run:
	./$(NAME)

tag:
	ctags $(SRC)

re: fclean all

.SILENT: run tag fclean clean
.PHONY: all clean fclean re
