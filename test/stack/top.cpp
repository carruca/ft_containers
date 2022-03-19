#include "stack.hpp"
#include "vector.hpp"

#include <stack>
#include <vector>

# define NAMESPACE	ft

void	pop_stack_test( void )
{
	typedef NAMESPACE::vector<int>	int_vct_type;
	typedef NAMESPACE::stack<int>	int_stck_type;

	int_vct_type	vct;
	int_stck_type	stck(vct);
}
