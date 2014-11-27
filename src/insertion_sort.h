#ifndef __insertion_sort_h_included__
#define __insertion_sort_h_included__

#include <functional>
#include <iterator>
#include <utility>

template<typename I, typename T = typename std::iterator_traits<I>::value_type, typename C = std::less<T> > void insertion_sort(I first, I last, C cmp = C())
{
	T t;
	for (auto i = first + 1; i != last; ++i) {
		t = std::move(*i);
		auto j = i;
		for (; j != first && cmp(t, *(j - 1)); --j)
			*j = std::move(*(j - 1));

		*j = std::move(t);
	}
}

#endif
