#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

int fact(int n) {

	int res = 1;
	for (int i = 1; i <= n; i++) {
		res *= i;
	}
	return res;
}
int permutationWithoutRepetiton(int n) {
	int res = 1;

	res = fact(n) / (fact(n - 5));				//5 is the number of possible pieces

	return res;
}

#endif