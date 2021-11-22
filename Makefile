NAME		= ft_containers

TEST_DIR	= test/
UTILS_TEST	= testIs_integral.cpp \
			  testEnable_if.cpp \
			  testPair.cpp \
			  testEqual.cpp \
			  testLexicographical_compare.cpp \
			  testReverseIterator.cpp

ITER_DIR	= iterators/
ITER_INC	= ft_iterators_traits.hpp \
			  ft_reverse_iterator.hpp

UTILS_DIR	= utils/
UTILS_INC	= ft_is_integral.hpp \
			  ft_enable_if.hpp \
			  ft_pair.hpp \
			  ft_equal.hpp \
			  ft_lexicographical_compare.hpp

SRC			= $(addprefix $(TEST_DIR), main.cpp $(UTILS_TEST))

INC			= -I$(UTILS_DIR) -I$(ITER_DIR)
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
