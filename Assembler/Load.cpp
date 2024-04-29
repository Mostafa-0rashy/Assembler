#include "Load.h"
#include <istream>
#include<fstream>
#include <string>
#include<iostream>
#include <algorithm>
using namespace std;

string Load::BinaryOperands(int RegNumber) {
	string binary = "";
	if (RegNumber == 0) {
		binary = "000";
	}
	else {
		while (RegNumber > 0) {
			binary = std::to_string(RegNumber % 2) + binary;
			RegNumber /= 2;
		}
	}
	return binary;
}
std::string toUpperCase(const std::string& str)
{
	std::string result = str;

	transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
		return std::toupper(c);
		});

	return result;
}
string Load ::ImmediateValueBinary(int Imm) {
	if (Imm == 0) {
		return "0";
	}

	std::string binary = "";
	bool negative = false;

	// Handle negative numbers
	if (Imm < 0) {
		negative = true;
		Imm = -Imm; // Make the number positive
	}

	// Convert to binary using two's complement
	while (Imm > 0) {
		binary = (Imm % 2 == 0 ? "0" : "1") + binary;
		Imm /= 2;
	}

	// Add leading zeros to make it 8 bits (assuming 8-bit signed binary)
	while (binary.length() < 8) {
		binary = "0" + binary;
	}

	// Invert bits if negative
	if (negative) {
		// Invert bits
		for (char& bit : binary) {
			bit = (bit == '0' ? '1' : '0');
		}
		// Add 1 to the binary number
		for (int i = binary.length() - 1; i >= 0; --i) {
			if (binary[i] == '0') {
				binary[i] = '1';
				break;
			}
			else {
				binary[i] = '0';
			}
		}
	}

	return binary;
}





void Load ::Execute(bool read)
{

	string line;
	int cnt; // count of figures
	string opcode;
	string operand1;
	string operand2;
	string operand3;
	string immValue;
	ifstream Infile;
	Infile.open("Instructions.txt", ios::in);
	ofstream outFile("Out.txt", ios::out);
	if (Infile.fail()) //if file name is invaild
	{
		cout << "File didn't successfully open";
		return;
	}
	else
	{
		cout << "File Opened";

		while (!Infile.eof())
		{
			string instruction; //instruction
			Infile >> instruction;
			instruction = toUpperCase(instruction);
			if (instruction == "SWAP" || instruction == "ADD" || instruction == "XOR"
				|| instruction == "ADDI" || instruction == "SUB" || instruction == "SUBI" || instruction == "AND" || instruction == "OR" || instruction == "LDD")
				//////////////// THREE OPERANDS/////////////////////
			{
				//////////////Decoding Instrcution///////////////
				if (instruction == "SWAP") {

					opcode = "001001";
					outFile << opcode;
				}
				else if (instruction == "ADD") {

					opcode = "001010";
					outFile << opcode;
				}
				else if (instruction == "XOR") {

					opcode = "001010";
					outFile << opcode;
				}
				else if (instruction == "ADDI") {

					opcode = "101010";
					outFile << opcode;
				}
				else if (instruction == "SUB") {

					opcode = "001011";
					outFile << opcode;
				}
				else if (instruction == "SUBI") {

					opcode = "101011";
					outFile << opcode;
				}
				else if (instruction == "AND") {

					opcode = "001100";
					outFile << opcode;

				}
				else if (instruction == "OR") {

					opcode = "001101";
					outFile << opcode;

				}
				else if (instruction == "LDD") {

					opcode = "110011";
					outFile << opcode;

				};


				//////////////Reading Operand1///////////////

				char temp1;
				char temp2;
				Infile.get(temp1);
				while (temp1 == ' ')
				{

					Infile.get(temp1);
				};
				Infile.get(temp2);
				operand1 = BinaryOperands(temp2 - '0');
				outFile << operand1;


				if (instruction == "ADDI" || instruction == "SUBI")
				{				

					//////////////Reading Immediate value///////////////


					char immValueint;
					Infile.get(immValueint);
					while (immValueint == ' ' || immValueint == ',')
					{

						Infile.get(immValueint);
					};
					immValue = std::string(1, immValueint);
					string immvaluerest;
					Infile >> immvaluerest;
					immValue = immValue + immvaluerest;
					immValue = ImmediateValueBinary(std::stoi(immValue));

				}
				else if (instruction == "LDD")
				{
					char immValueint;
					Infile.get(immValueint);
					while (immValueint == ' ' || immValueint == ',')
					{

						Infile.get(immValueint);
					};
					immValue = std::string(1, immValueint);
					string immvaluerest;
					Infile >> immvaluerest;
					immValue = immValue + immvaluerest;
					immValue = ImmediateValueBinary(std::stoi(immValue));
					outFile << immValue;
				}
				else
				{
					Infile.get(temp1);
					while ((temp1 == ' ' || temp1 == ','))
					{

						Infile.get(temp1);
					}

					Infile.get(temp2);
					operand2 = BinaryOperands(temp2 - '0');
					outFile << operand2;
					Infile.get(temp1);
					while ((temp1 == ' ' || temp1 == ','))
					{

						Infile.get(temp1);
					}

					Infile.get(temp2);
					operand3 = BinaryOperands(temp2 - '0');
					outFile << operand3;
				}
			}
			////////////////////////TWO OPERAND////////////////////////////////
			else if (instruction == "MOV" || instruction == "SWAP" || instruction == "CMP" || instruction == "LDM" || instruction == "STD")
			{
				if (instruction == "MOV")

				{
					opcode = "001000";
					outFile << opcode;
				}
				else if (instruction == "SWAP")
				{
					opcode = "001001";
					outFile << opcode;
				}
				else if (instruction == "LDM")
				{
					opcode = "110010";
					outFile << opcode;

				}
				else if (instruction == "CMP")
				{
					opcode = "001111";
					outFile << opcode;
					outFile << "0000";
				}


				char temp1;
				char temp2;
				Infile.get(temp1);
				while (temp1 == ' ')
				{

					Infile.get(temp1);
				}
				Infile.get(temp2);
				///////////Taking Operand 1//////////////////
				operand1 = BinaryOperands(temp2 - '0');
				outFile << operand1;

				Infile.get(temp1);
				while ((temp1 == ' ' || temp1 == ','))
				{

					Infile.get(temp1);
				}

				Infile.get(temp2);

				///////////////Taking Operand 2//////////////

				operand2 = BinaryOperands(temp2 - '0');
				outFile << operand2;

			}
			//////////////////////ONE OPERAND//////////////////////////////
			else if (instruction == "JZ" || instruction == "JMP" || instruction == "CALL" || instruction == "INT" || instruction == "NEG" || instruction == "NOT"

				|| instruction == "INC" || instruction == "DEC" || instruction == "OUT" || instruction == "IN")

			{


			}

			////////////////////ZERO OPERAND//////////////////////////////

			else if (instruction == "NOP" || instruction == "RET" || instruction == "RTI" || instruction == "RESET")
			{



			}
			outFile<<"\n";

		}
	}	//reads fill clr
	   ////////////Set draw color

	   ////////////Set fill color

	   //// Read fig count
		Infile >> cnt;
		//identify figures
		/*for (int i = 0; i < cnt; i++)
		{
			Infile >> type;
			if (type == "Rectangle")
				myfig = new CRectangle;
			if (type == "Circle")
				myfig = new CCircle;
			if (type == "Triangle")
				myfig = new CTriangle;
			if (type == "Square")
				myfig = new CSquare;
			if (type == "Hexagon")
				myfig = new CHex;
			myfig->Load(Infile);
			pManager->AddF(myfig);
		}*/
	}