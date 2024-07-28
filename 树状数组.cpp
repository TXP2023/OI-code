#include <vector>

template< typename T >
inline T lowbit(T x)
{
	return ((x) & -(x));
}

template< typename T1, typename T2, typename T3 >
inline void TreeAdd(T1 change/*����*/, T2 x/*�±�*/, std::vector< T3 >& _tree/*����*/)
{
	for (size_t i = x; i <= _tree.size() - 1; i += lowbit(x))
	{
		_tree[i] += change;
	}
	return;
}
 