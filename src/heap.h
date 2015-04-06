// -*- mode: c++ -*-
#ifndef __heap_h_included__
#define __heap_h_included__

// Copyright (c) 2015 Olaf Dietsche

#include <algorithm>
#include <functional>

template<typename I, typename C = std::less<typename std::iterator_traits<I>::value_type> > I is_heap_until(I first, I last, C cmp = C())
{
	for (auto i = first; i < last; ++i) {
		I left = first + 2 * (i - first) + 1;
		I right = first + 2 * (i - first) + 2;
		if (left < last && cmp(*i, *left))
			return i;

		if (right < last && cmp(*i, *right))
			return i;
	}

	return last;
}

template<typename I, typename C = std::less<typename std::iterator_traits<I>::value_type> > bool is_heap(I first, I last, C cmp = C())
{
	return ::is_heap_until(first, last, cmp) == last;
}

template<typename I, typename C = std::less<typename std::iterator_traits<I>::value_type> > void push_heap(I first, I last, C cmp = C())
{
	I child = last - 1;
	I parent = first + (child - first - 1) / 2;
	while (child > first && cmp(*parent, *child)) {
		std::iter_swap(parent, child);
		child = parent;
		parent = first + (child - first - 1) / 2;
	}
}

template<typename I, typename C = std::less<typename std::iterator_traits<I>::value_type> > void make_heap(I first, I last, C cmp = C())
{
	for (auto i = first + 2; i <= last; ++i)
		::push_heap(first, i, cmp);
}

template<typename I, typename C = std::less<typename std::iterator_traits<I>::value_type> > void pop_heap(I first, I last, C cmp = C())
{
	if (last - first <= 1)
		return;

	--last;
	std::iter_swap(first, last);
	auto parent = first;
	while (parent < last) {
		I left = first + 2 * (parent - first) + 1;
		I right = first + 2 * (parent - first) + 2;
		if (left < last && cmp(*parent, *left)) {
			if (right < last && cmp(*left, *right)) {
				std::iter_swap(parent, right);
				parent = right;
			} else {
				std::iter_swap(parent, left);
				parent = left;
			}
		} else if (right < last && cmp(*parent, *right)) {
			std::iter_swap(parent, right);
			parent = right;
		} else {
			break;
		}
	}
}

template<typename I, typename C = std::less<typename std::iterator_traits<I>::value_type> > void sort_heap(I first, I last, C cmp = C())
{
	for (auto i = last; i > first + 1; --i)
		::pop_heap(first, i, cmp);
}

#endif
