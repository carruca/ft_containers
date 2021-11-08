NAME		= ft_containers

SRC			= main.cpp \

UTILS		= is_integral.hpp

OBJ			= $(SRC:.cpp=.o)
INC			= -I.
DEPS		= $(SRC:.cpp=.d)

CXXFLAGS	= -Wall -Wextra -Werror -MD -std=c++98 $(INC)
CXX			= clang++

DEBUG		= -g3
SANITIZE	= -fsanitize=address

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) $(DEPS)
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME)

sanitize: CXXFLAGS += $(SANITIZE) $(DEBUG)
sanitize: all

run:		all
	./$(NAME)

tag:
	ctags $(SRC)

re:			fclean all

.SILENT: run tag fclean clean
.PHONY: all clean fclean re
