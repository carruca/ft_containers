NAME			= ft_containers

TEST_DIR		= test/

STACK_DIR		= stack/
STACK_TEST		= top.cpp

MAP_DIR			= map/
MAP_TEST		= lower_bound.cpp					\
				  upper_bound.cpp					\
				  create_empty.cpp

VECTOR_DIR		= vector/
TEST_VECTOR		= test.cpp							\
				  constructor.cpp					\
				  erase.cpp

TEST_UTILS		= pairTest.cpp						\
				  equalTest.cpp						\
				  lexicographical_compareTest.cpp 	\
				  reverse_iteratorTest.cpp
				  #enable_ifTest.cpp				\
				  is_integralTest.cpp


CONTAINER_DIR	= containers/
VECTOR_INC		= vector.hpp						\
				  map.hpp							\
				  stack.hpp

ITER_DIR		= iterator/
ITER_INC		= ft_iterators_traits.hpp			\
				  ft_reverse_iterator.hpp			\
				  ft_normal_iterator.hpp			\
				  ft_tree_iterator.hpp

TYPES_DIR		= types/
TYPES_INC		= ft_is_integral.hpp				\
				  ft_enable_if.hpp

ALG_DIR			= algorithm/
ALG_INC			= ft_equal.hpp						\
				  ft_lexicographical_compare.hpp

UTIL_DIR		= utility/
UTIL_INC		= ft_pair.hpp						\
				  ft_tree.hpp

SRC				= $(addprefix $(TEST_DIR),						\
				  main.cpp										\
				  $(TEST_UTILS)									\
				  $(addprefix $(VECTOR_DIR), $(TEST_VECTOR))	\
				  $(addprefix $(MAP_DIR), $(MAP_TEST))			\
				  $(addprefix $(STACK_DIR), $(STACK_TEST)))

INC				= -I$(CONTAINER_DIR) -I$(ITER_DIR) -I$(TYPES_DIR) -I$(ALG_DIR) -I$(UTIL_DIR)

OBJ_DIR			= obj/
OBJ				= $(patsubst $(TEST_DIR)%, $(OBJ_DIR)%, $(SRC:.cpp=.o))
DEPS			= $(OBJ:.o=.d)

CXXFLAGS		= -Wall -Wextra -Werror -pedantic -O0 -MD $(INC) $(COMMONFLAGS) -std=c++98
CXX				= clang++
COMMONFLAGS		=
LDFLAGS			= $(COMMONFLAGS)

DEBUG			= -g3
SANITIZE		= -fsanitize=address

all:		$(NAME)
#all:		sanitize

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
sanitize:	$(NAME)

run:		all
	./$(NAME)

tag:
	ctags $(SRC)

re:			fclean all

.SILENT: run tag fclean clean
.PHONY: all clean fclean re
