// FastLib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "step.h"


int main()
{
	step::DeserializeFile("tests\\20150101.out", [](std::string& s, int i) {
		printf("%d: %d\n", s.size(), i);
	});

	int a = 0;
	std::cin >> a;
    return 0;
}

