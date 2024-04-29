#include "Load.h"
#include <istream>
#include<fstream>
#include <string>
#include<iostream>
using namespace std;

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
				|| instruction == "ADDI" || instruction == "SUB" || instruction == "SUBI" || instruction == "AND" || instruction == "OR" || instruction == "LDD")
				//////////////// THREE OPERANDS/////////////////////
			{
				//////////////Decoding Instrcution///////////////
				if (instruction == "SWAP") {

					opcode = "001001";
				}
				else if (instruction == "ADD") {

					opcode = "001010";
				}
				else if (instruction == "XOR") {

					opcode = "001010";
				}
				else if (instruction == "ADDI") {

					opcode = "101010";
				}
				else if (instruction == "SUB") {

					opcode = "001011";
				}
				else if (instruction == "SUBI") {

					opcode = "101011";
				}
				else if (instruction == "AND") {

					opcode = "001100";

				}
				else if (instruction == "OR") {

					opcode = "001101";

				}
				else if (instruction == "LDD") {

					opcode = "110011";

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
				operand1 = std::string(1, temp1) + std::string(1, temp2);//operand 1 taken

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
				}
				else
				{
					Infile.get(temp1);
					while ((temp1 == ' ' || temp1 == ','))
					{

						Infile.get(temp1);
					}

					Infile.get(temp2);
					operand2 = std::string(1, temp1) + std::string(1, temp2);
					Infile.get(temp1);
					while ((temp1 == ' ' || temp1 == ','))
					{

						Infile.get(temp1);
					}

					Infile.get(temp2);
					operand3 = std::string(1, temp1) + std::string(1, temp2);
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