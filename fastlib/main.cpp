// FastLib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "step.h"

void Callback(char* s, int size)
{
	std::cout << size << std::endl;
}

int main()
{
	step::DeserializeFile("tests\\20150101.out", Callback);

	int a = 0;
	std::cin >> a;
    return 0;
}

