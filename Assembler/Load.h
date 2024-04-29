#pragma once
#include <istream>
#include<fstream>
#include <string>
#include<iostream>
using namespace std;

class Load
{
public:

	string BinaryOperands(int RegNumber);
	string ImmediateValueBinary(int Imm);
	void Execute(bool read);
};

