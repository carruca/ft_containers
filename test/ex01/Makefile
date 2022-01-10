NAME			= ex01

SRC				= main.cpp \
			  	Span.cpp

OBJ				= $(SRC:.cpp=.o)
VECTOR_INC		= ../../containers/
ITERATOR_INC	= ../../iterator/
ALGORITHM_INC	= ../../algorithm/
TYPES_INC		= ../../types/

INC				= -I.					\
				  -I$(VECTOR_INC)		\
				  -I$(ITERATOR_INC)		\
				  -I$(ALGORITHM_INC)	\
				  -I$(TYPES_INC)

CXXFLAGS		= -Wall -Wextra -Werror -Wshadow $(INC)
CXX				= clang++

DEBUG			= -g3
SANITIZE		= -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

sanitize: CXXFLAGS += $(SANITIZE) $(DEBUG)
sanitize: all

tag:
	ctags $(SRC)

re: fclean all

.PHONY: all clean fclean re
