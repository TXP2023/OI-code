
template <typename T>
T gcd(T a, T b) {
	if (b == 0) {
		return a;
	} 
	return gcd(b, a % b);
}

template <typename T>
T lcm(T a, T b) {
	return a * b / gcd(b, a % b);
}

