#ifndef __selection_sort_h_included__
#define __selection_sort_h_included__

#include <algorithm>
#include <functional>
#include <iterator>
#include <utility>

template<typename I, typename T = typename std::iterator_traits<I>::value_type, typename C = std::less<T> > void selection_sort(I first, I last, C cmp = C())
{
	for (; first != last; ++first) {
		auto min = std::min_element(first, last, cmp);
		std::swap(*first, *min);
	}
}

#endif
