#pragma once

inline  int
ParseInt(const char* p) {
	if (*p != '-') {
		int x = 0;
		while (*p >= '0' && *p <= '9') {
			x = (x * 10) + (*p - '0');
			++p;
		}
		return x;
	}
	else {
		++p;
		int x = 0;
		while (*p >= '0' && *p <= '9') {
			x = (x * 10) + (*p - '0');
			++p;
		}
		return -x;
	}
}