#ifndef __next_combination_h_included__
#define __next_combination_h_included__

bool next_combination(int *a, int n, int k)
{
	if (k <= 0)
		return false;

	int i = k - 1;
	if (a[i] < n - 1) {
		++a[i];
		return true;
	}

	int j = i - 1;
	if (next_combination(a, n - 1, k - 1)) {
		a[i] = a[j] + 1;
		return true;
	}

	return false;
}

#endif
