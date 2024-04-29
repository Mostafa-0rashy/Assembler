#include "Load.h"
#include <istream>
#include<fstream>
#include <string>
#include<iostream>
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
		if (binary.size()==2)
		{
			binary = "0" + binary;
		}
		else if (binary.size() == 1)
		{
			binary = "00" + binary;
		}
	}
	return binary;
}

string Load ::ImmediateValueBinary(int Imm) {
	std::string binary = "";

	// If the number is negative, convert it to its 2's complement representation
	if (Imm < 0) {
		Imm = (1 << 15) + Imm; // Convert to positive and set the MSB to 1
	}

	// Handle the case when the number is 0
	if (Imm == 0) {
		binary = "0";
	}
	else {
		while (Imm > 0) {
			binary = std::to_string(Imm % 2) + binary;
			Imm /= 2;
		}
	}

	// Pad with zeros to ensure the binary string is 16 bits long
	while (binary.length() < 16) {
		binary = "0" + binary;
	}

	return binary;
}




void Load ::Execute(bool read)
{
	
	string instruction; //instruction
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
		cout <<"File didn't successfully open";
		return;
	}
	else
	{
		cout << "File Opened";

		while (!Infile.eof())
		{	
			Infile >> instruction;
			std::string toUpperCase(instruction);
			if (instruction == "SWAP" || instruction == "ADD" || instruction == "XOR"
				|| instruction == "ADDI" || instruction == "SUB" || instruction == "SUBI" || instruction == "AND" || instruction == "OR" || instruction == "LDD" || instruction == "STD")
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
					outFile << endl;


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
					string immvaluerest;
					Infile >> immvaluerest;
					immValue = immValue + immvaluerest;


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
					outFile << endl;
					break;
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
					outFile << endl;
				}
			}
			////////////////////////TWO OPERAND////////////////////////////////
			else if (instruction == "MOV" || instruction == "SWAP" || instruction == "CMP" || instruction == "LDM" || instruction == "STD")
			{
				char temp1;
				char temp2;
				Infile.get(temp1);
				while (temp1 == ' ')
				{

					Infile.get(temp1);
				}
				Infile.get(temp2);
				operand1 = std::string(1, temp1) + std::string(1, temp2);//operand 1 taken
				Infile.get(temp1);
				while ((temp1 == ' ' || temp1 == ','))
				{

					Infile.get(temp1);
				}

				Infile.get(temp2);
				operand2 = std::string(1, temp1) + std::string(1, temp2);
				if (instruction == "MOV")

				{
					opcode = "001000";
					outFile<<opcode;
				}
				else if(instruction=="SWAP")
				{
					opcode = "001001";
					outFile << opcode;
				}
				else if (instruction == "ADDI")
				{
					opcode = "101010";
				}
				else if (instruction == "SUBI")

				{
					opcode = "101011";
				}


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

		}
	}	//reads fill clr
	   ////////////Set draw color

	   ////////////Set fill color

	   //// Read fig count
		Infile >> cnt;
		outFile.close();
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