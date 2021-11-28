NAME		= ft_containers

TEST_DIR	= test/
TEST_SRC	= is_integralTest.cpp \
			  enable_ifTest.cpp \
			  pairTest.cpp \
			  equalTest.cpp \
			  lexicographical_compareTest.cpp \
			  reverse_iteratorTest.cpp

ITER_DIR	= iterator/
ITER_INC	= ft_iterators_traits.hpp \
			  ft_reverse_iterator.hpp

TYPES_DIR	= types/
TYPES_INC	= ft_is_integral.hpp \
			  ft_enable_if.hpp

ALG_DIR		= algorithm/
ALG_INC		= ft_equal.hpp \
			  ft_lexicographical_compare.hpp

UTIL_DIR	= utility/
UTIL_INC	= ft_pair.hpp

SRC			= $(addprefix $(TEST_DIR), main.cpp $(TEST_SRC))

INC			= -I$(UTIL_DIR) -I$(ITER_DIR) -I$(TYPES_DIR) -I$(ALG_DIR)
OBJ_DIR		= obj/
OBJ			= $(patsubst $(TEST_DIR)%, $(OBJ_DIR)%, $(SRC:.cpp=.o))
DEPS		= $(OBJ:.o=.d)

CXXFLAGS	= -Wall -Wextra -Werror -MD -std=c++98 $(INC) $(COMMONFLAGS)
CXX			= clang++
COMMONFLAGS	=
LDFLAGS		= $(COMMONFLAGS)

DEBUG		= -g3
SANITIZE	= -fsanitize=address

all:		$(NAME)

-include	$(DEPS)

$(OBJ_DIR)%.o:	$(TEST_DIR)%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	$(RM) $(DEPS)
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME)

sanitize:	COMMONFLAGS += $(SANITIZE) $(DEBUG)
sanitize:	all

run:		all
	./$(NAME)

tag:
	ctags $(SRC)

re:			fclean all

.SILENT: run tag fclean clean
.PHONY: all clean fclean re
