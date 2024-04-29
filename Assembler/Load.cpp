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
	else if (RegNumber>0) {
		for (int i = 2; i >= 0; i--) {
			binary = std::to_string(RegNumber & 1) + binary;
			RegNumber >>= 1;
		}
	}
	
	return binary;
}
std::string toUpperCase(const std::string& str)
{
	std::string result = str;

	transform(result.begin(), result.end(), result.begin(), [](unsigned char c) 
	{
		return std::toupper(c);
	});
	return result;
}
string Load ::ImmediateValueBinary(int Imm) {
	std::string binary = "";
	int Immabs = std::abs(Imm);
	// Handle the case when the number is 0
	if (Immabs == 0) {
		binary = "0";
	}
	else {
		while (Immabs > 0) {
			binary = std::to_string(Immabs % 2) + binary;
			Immabs /= 2;
		}
	}

	// Pad with zeros to ensure the binary string is 16 bits long
	while (binary.length() < 15) {
		binary = "0" + binary;
	}
	if (binary.length() == 15)
	{
		if (Imm> 0)
		{
			binary = "0" + binary;
		}
		else if (Imm < 0)
		{
			binary = "1" + binary;
		}

	}

	return binary;
}

void Load::Execute(bool read)
{
	string line;
	string opcode;
	string operand1;
	string operand2;
	string operand3;
	string immValue;
	string Outinstruction;
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
			if (instruction == "ADD" || instruction == "XOR"
				|| instruction == "ADDI" || instruction == "SUB" || instruction == "SUBI" || instruction == "AND" || instruction == "OR" || instruction == "LDD" || instruction == "STD")
				//////////////// THREE OPERANDS/////////////////////
			{
				//////////////Decoding Instrcution///////////////
				if (instruction == "ADD") {

					opcode = "001010";
					outFile << opcode;
				}
				else if (instruction == "XOR") {

					opcode = "001110";
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

				}
				else if (instruction == "STD") {

					opcode = "110100";
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

					outFile << "0000000";
					outFile << endl;
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
				else if (instruction == "LDD" || instruction == "STD")
				{



					//////////////Reading Immediate value///////////////

					char immValueint;
					Infile.get(immValueint);
					while (immValueint == ' ' || immValueint == ',')
					{

						Infile.get(immValueint);
					};
					immValue = std::string(1, immValueint);
					char immvaluerest;
					Infile.get(immvaluerest);
					while (immvaluerest != '(')
					{

						immValue = immValue + std::string(1, immvaluerest);
						Infile.get(immvaluerest);
					}


					//////////////Reading Operand2///////////////
					Infile.get(temp1);
					while ((temp1 == ' ' || temp1 == '(' || temp1 == ','))
					{

						Infile.get(temp1);
					}

					Infile.get(temp2);
					operand2 = BinaryOperands(temp2 - '0');
					outFile << operand2 <<"0000";
					outFile << endl;



					immValue = ImmediateValueBinary(std::stoi(immValue));
					outFile << immValue;

					Infile.get(temp1);
					while ((temp1 == ' ' || temp1 == ')'))
					{

						Infile.get(temp1);
						if (Infile.eof()) {
							break;
						}
					}
				}
				else 
				{
					//////////////Reading Operand2///////////////
					Infile.get(temp1);
					while ((temp1 == ' ' || temp1 == ','))
					{

						Infile.get(temp1);
					}

					Infile.get(temp2);
					operand2 = BinaryOperands(temp2 - '0');
					outFile << operand2;

					//////////////Reading Operand3///////////////

					Infile.get(temp1);
					while ((temp1 == ' ' || temp1 == ','))
					{

						Infile.get(temp1);
					}

					Infile.get(temp2);
					operand3 = BinaryOperands(temp2 - '0');
					outFile << operand3 <<"0";
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
					outFile << "000";
				}

				if (instruction == "LDM")
				{
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
					outFile << "0000000";
					outFile << "\n";

					string imm1;
					Infile.get(temp1);
					Infile >> imm1;
					imm1 = ImmediateValueBinary(std::stoi(imm1));
					outFile << imm1;
				}
				else
				{
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
				 
				   if (instruction != "LDM")
				   {
					
				    if (instruction != "CMP")
					{
						outFile << "0000";
					}
					else
					{
					
					outFile << "0";
					}
				   //do nothing
				   }

				

			}
			//////////////////////ONE OPERAND//////////////////////////////
			else if (instruction == "JZ" || instruction == "JMP" || instruction == "CALL" || instruction == "NEG" || instruction == "NOT" || instruction == "INC" 
					|| instruction == "DEC" || instruction == "OUT" || instruction == "IN" || instruction == "POP" || instruction == "PUSH" 
					|| instruction == "PROTECT" || instruction == "FREE")
			{
				//////////////Decoding Instrcution///////////////
				if (instruction == "JZ")
				{
					opcode = "011000";
				}
				else if (instruction == "JMP")
				{
					opcode = "011001";
				}
				else if (instruction == "CALL")
				{
					opcode = "011010";
				}
				else if (instruction == "NEG")
				{
					opcode = "000001";
				}
				else if (instruction == "NOT")
				{
					opcode = "000011";
				}
				else if (instruction == "INC")
				{
					opcode = "000100";
				}
				else if (instruction == "DEC")
				{
					opcode = "000101";
				}
				else if (instruction == "OUT")
				{
					opcode = "000110";
				}
				else if (instruction == "IN")
				{
					opcode = "000111";
				}
				else if (instruction == "POP")
				{
					opcode = "010001";
				}
				else if (instruction == "PUSH")
				{
					opcode = "010000";
				}
				else if (instruction == "PROTECT")
				{
					opcode = "010101";
				}
				else if (instruction == "FREE")
				{
					opcode = "010110";
				}
				char temp1;
				char temp2;
				Infile.get(temp1);
				while (temp1 == ' ')
				{
					Infile.get(temp1);
				}
				Infile.get(temp2);
				operand1 = std::string(1, temp1) + std::string(1, temp2);//operand 1 taken

				if (operand1 == "R0" || operand1 == "r0")
				{
					Outinstruction = opcode + "0000000000";
					outFile << Outinstruction;
				}
				else if (operand1 == "R1" || operand1 == "r1")
				{
					Outinstruction = opcode + "0010000000";
					outFile << Outinstruction;
				}
				else if (operand1 == "R2" || operand1 == "r2")
				{
					Outinstruction = opcode + "0100000000";
					outFile << Outinstruction;
				}
				else if (operand1 == "R3" || operand1 == "r3")
				{
					Outinstruction = opcode + "0110000000";
					outFile << Outinstruction;
				}
				else if (operand1 == "R4" || operand1 == "r4")
				{
					Outinstruction = opcode + "1000000000";
					outFile << Outinstruction;
				}
				else if (operand1 == "R5" || operand1 == "r5")
				{
					Outinstruction = opcode + "1010000000";
					outFile << Outinstruction;
				}
				else if (operand1 == "R6" || operand1 == "r6")
				{
					Outinstruction = opcode + "1100000000";
					outFile << Outinstruction;
				}
				else if (operand1 == "R7" || operand1 == "r7")
				{
					Outinstruction = opcode + "1110000000";
					outFile << Outinstruction;
				}
			}
			////////////////////ZERO OPERAND//////////////////////////////
			else if (instruction == "NOP" || instruction == "RET" || instruction == "RTI" || instruction == "RESET" || instruction == "INT")
			{
				if (instruction == "NOP")
				{
					opcode = "000000";
				}
				else if (instruction == "RET")
				{
					opcode = "011011";
				}
				else if (instruction == "RTI")
				{
					opcode = "011100";
				}
				else if (instruction == "RESET")
				{
					opcode = "111111";
				}
				else if (instruction == "INT")
				{
					opcode = "111000";
				}
				Outinstruction = opcode + "0000000000";
				outFile << Outinstruction;
			}

			outFile << '\n';
		}
	}
};