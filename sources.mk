TEST_DIR		= test/

STACK_DIR		= stack/
STACK_TEST		= top.cpp

MAP_DIR			= map/
MAP_TEST		= lower_bound.cpp					\
				  upper_bound.cpp					\
				  create_empty.cpp					\
				  equal_range.cpp					\
				  size.cpp							\
				  find.cpp							\
				  value_comp.cpp					\
				  relationals.cpp					\
				  swap.cpp							\
				  insert.cpp

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

SRC				= $(addprefix $(TEST_DIR),						\
				  main.cpp										\
				  $(TEST_UTILS)									\
				  $(addprefix $(VECTOR_DIR), $(TEST_VECTOR))	\
				  $(addprefix $(MAP_DIR), $(MAP_TEST))			\
				  $(addprefix $(STACK_DIR), $(STACK_TEST)))

