NAME		= ft_containers

UTILS_TEST	= testIs_integral.cpp \
			  testEnable_if.cpp

SRC			= main.cpp \
			  $(UTILS_TEST)

UTILS		= is_integral.hpp \
			  enable_if.hpp

INC			= -I.
OBJ			= $(SRC:.cpp=.o)
DEPS		= $(SRC:.cpp=.d)

CXXFLAGS	= -Wall -Wextra -Werror -MD -std=c++98 $(INC)
CXX			= clang++

DEBUG		= -g3
SANITIZE	= -fsanitize=address

all:		$(NAME)

-include	$(DEPS)

$(NAME):	$(OBJ)
	$(CXX) $^ -o $@

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
