/*  Justin Meman
    CPSC 323

    Assignment 3
    Write a syntax analyzer using any bottom-up approach.
*/

using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <istream>
#include <locale>
#include <array>
#include <stack>
#include <vector>

struct tokens {
	string lexeme;
	string token;
	string actualInput;
	int mem_add;
};

struct actions {
	string action;
	string state;
};

actions object;

tokens number;
tokens dollar;
string types[6] = {"bool", "char", "int", "float", "double" , "void"};

vector <tokens> lexered;

// Converts strings to table values
int To_Table(string input)
{
	if (input == "id" || input == "Identifier" || input == "0")
		return 0;
	else if (input == "num" || input == "number" || input == "1")
		return 1;
	else if (input == "=" || input == "2")
		return 2;
	else if (input == "+" || input == "3")
		return 3;
	else if (input == "-" || input == "4")
		return 4;
	else if (input == "*" || input == "5")
		return 5;
	else if (input == "/" || input == "6")
		return 6;
	else if (input == "(" || input == "7")
		return 7;
	else if (input == ")" || input == "8")
		return 8;
	else if (input == "key" || input == "9")
		return 9;
	else if (input == "$" || input == "10")
		return 10;
	else if (input == "S" || input == "11")
		return 11;
	else if (input == "E" || input == "12")
		return 12;
	else if (input == "T" || input == "13")
		return 13;
	else if (input == "F" || input == "14")
		return 14;
	else if (input == "A" || input == "15")
		return 15;
	else if (input == "D" || input == "16")
		return 16;
	else if (input == "17")
		return 17;
	else if (input == "18")
		return 18;
	else if (input == "19")
		return 19;
	else if (input == "20")
		return 20;
	else if (input == "21")
		return 21;
	else if (input == "22")
		return 22;
	else if (input == "23")
		return 23;
	else if (input == "24")
		return 24;
	else if (input == "25")
		return 25;
	else if (input == "26")
		return 26;
	else if (input == "27")
		return 27;
	else if (input == "28")
		return 28;
	else if (input == "29")
		return 29;
	else if (input == "30")
		return 30;
	else if (input == "31")
		return 31;
	else if (input == "32")
		return 32;
	else if (input == "33")
		return 33;
	else if (input == "34")
		return 34;
	else if (input == "35")
		return 35;
	else if (input == "36")
		return 36;
	else if (input == "37")
		return 37;
	else if (input == "38")
		return 38;
	else if (input == "39")
		return 39;
}

// Original syntax analyzer using a top-down approach [No longer used]
void Syntax_Analyzer(vector <tokens> lexered)
{
	string table[8][11];

	table[0][0] = "Rule 1";
	table[0][1] = "Rule 1";
	table[0][7] = "Rule 1";
	table[0][9] = "Rule 3";
	table[1][0] = "Rule 15";
	table[2][9] = "Rule 16";
	table[3][0] = "Rule 4";
	table[3][1] = "Rule 4";
	table[3][7] = "Rule 4";
	table[4][3] = "Rule 5";
	table[4][4] = "Rule 6";
	table[4][8] = "Rule 7";
	table[4][10] = "Rule 7";
	table[5][0] = "Rule 8";
	table[5][1] = "Rule 8";
	table[5][7] = "Rule 8";
	table[6][3] = "Rule 11";
	table[6][4] = "Rule 11";
	table[6][5] = "Rule 9";
	table[6][6] = "Rule 10";
	table[6][8] = "Rule 11";
	table[6][10] = "Rule 11";
	table[7][0] = "Rule 13";
	table[7][1] = "Rule 14";
	table[7][7] = "Rule 12";

	int position = 0;
	int flag = 0;
	stack <string> mystack;
	lexered.push_back(dollar);
	mystack.push(dollar.lexeme);
	mystack.push("S");

	ofstream out;
	out.open("output.txt");
	out << "\tTOKENS\t\t\t     LEXEMES\n\n";

	while (mystack.top() != "$") {
		string t = mystack.top();
		tokens i = lexered.at(position);

		if(i.actualInput == "$")
			break;
		
		if (flag == 0) {
			cout << "Token: " << i.token << " " << "\t\t    Lexeme: " << i.actualInput << endl;
			out << "Token: " << i.token << " " << "\t\t    Lexeme: " << i.actualInput << endl;
			flag = 1;
		}

		// Validity checks to see if top of stack is a terminal
		if (t == "id" || t == "num" || t == "type" || t == "=" || t == "+" || t == "-" || t == "/" || t == "*" || t == "(" || t == ")") {
			// if the top of stack is a terminal, checks if it matches the current position of the input and increments position variable
			if (t == i.lexeme || (t == "id" && i.token == "Identifier") || (t == "num" && i.token == "Integer") || (t == "type" && i.token == "Keyword")) {
				mystack.pop();
				position++;
				flag = 0;
			}
			else {
				cout << "Error Found" << endl;
				out << "Error Found" << endl;
				return;
			}
		}
		
		// Implementation for each rule corresponding to the table
		// Rule 1 is a special case because it can either be sent to Rule 1, 2, or 3
		else if (table[To_Table(t)][To_Table(i.lexeme)] == "Rule 1") {
			if (lexered.at(position + 1).actualInput != "=") {
				cout << "     <Statement> -> <Expression>";
				out << "     <Statement> -> <Expression>";
				mystack.pop();
				mystack.push("E");
			}

			else if(lexered.at(position + 1).actualInput == "=") {
				cout << "     <Statement> -> <Assign>";
				out << "     <Statement> -> <Assign>";
				mystack.pop();
				mystack.push("A");
			}
		}

		else if (table[To_Table(t)][To_Table(i.lexeme)] == "Rule 2") {
			cout << "     <Statement> -> <Assign>";
			out << "     <Statement> -> <Assign>";
			mystack.pop();
			mystack.push("A");
		}

		else if (table[To_Table(t)][To_Table(i.lexeme)] == "Rule 3") {
			cout << "     <Statement> -> <Declaration>";
			out << "     <Statement> -> <Declaration>";
			mystack.pop();
			mystack.push("D");
		}

		else if (table[To_Table(t)][To_Table(i.lexeme)] == "Rule 4") {
			cout << "     <Expression> -> <Term><E'>";
			out << "     <Expression> -> <Term><E'>";
			mystack.pop();
			mystack.push("E'");
			mystack.push("T");
		}

		else if (table[To_Table(t)][To_Table(i.lexeme)] == "Rule 5") {
			cout << "     <E'> -> +<Term><E'>";
			out << "     <E'> -> +<Term><E'>";
			mystack.pop();
			mystack.push("E'");
			mystack.push("T");
			mystack.push("+");
		}
		
		else if ((table[To_Table(t)][To_Table(i.lexeme)] == "Rule 6")) {
			cout << "     <E'> -> -<Term><E'>";
			out << "     <E'> -> -<Term><E'>";
			mystack.pop();
			mystack.push("E'");
			mystack.push("T");
			mystack.push("-");
		}

		else if ((table[To_Table(t)][To_Table(i.lexeme)] == "Rule 7")) {
			cout << "     <E'> -> epsilon";
			out << "     <E'> -> epsilon";
			mystack.pop();
		}

		else if (table[To_Table(t)][To_Table(i.lexeme)] == "Rule 8") {
			cout << "     <Term> -> <Factor><T'>";
			out << "     <Term> -> <Factor><T'>";
			mystack.pop();
			mystack.push("T'");
			mystack.push("F");
		}

		else if (table[To_Table(t)][To_Table(i.lexeme)] == "Rule 9") {
			cout << "     <T'> -> *<Factor><T'>";
			out << "     <T'> -> *<Factor><T'>";
			mystack.pop();
			mystack.push("T'");
			mystack.push("F");
			mystack.push("*");
		}

		else if (table[To_Table(t)][To_Table(i.lexeme)] == "Rule 10") {
			cout << "     <T'> -> /<Factor><T'>";
			out << "     <T'> -> /<Factor><T'>";
			mystack.pop();
			mystack.push("T'");
			mystack.push("F");
			mystack.push("/");
		}

		else if (table[To_Table(t)][To_Table(i.lexeme)] == "Rule 11") {
			cout << "     <T'> -> epsilon";
			out << "     <T'> -> epsilon";
			mystack.pop();
		}

		else if (table[To_Table(t)][To_Table(i.lexeme)] == "Rule 12") {
			cout << "     <Factor> -> ( <Expression> )";
			out << "     <Factor> -> ( <Expression> )";
			mystack.pop();
			mystack.push(")");
			mystack.push("E");
			mystack.push("(");
		}

		else if (table[To_Table(t)][To_Table(i.lexeme)] == "Rule 13") {
			cout << "     <Factor> -> id";
			out << "     <Factor> -> id";
			mystack.pop();
			mystack.push("id");
		}

		else if (table[To_Table(t)][To_Table(i.lexeme)] == "Rule 14") {
			cout << "     <Factor> -> num";
			out << "     <Factor> -> num";
			mystack.pop();
			mystack.push("num");
		}

		else if (table[To_Table(t)][To_Table(i.lexeme)] == "Rule 15") {
			cout << "     <Assign> -> id = <Expression>";
			out << "     <Assign> -> id = <Expression>";
			mystack.pop();
			mystack.push("E");
			mystack.push("=");
			mystack.push("id");
		}

		else if (table[To_Table(t)][To_Table(i.lexeme)] == "Rule 16") {
			cout << "     <Declaration> -> type id";
			out << "     <Declaration> -> type id";
			mystack.pop();
			mystack.push("id");
			mystack.push("type");
		}

		// Special case rule to fix stack in order to syntactically analyze a new line
		else if(i.lexeme == ";") {
			cout << "     --New Line--" << endl;
			out << "     --New Line--" << endl;
			int j = mystack.size() - 1;
			for(int i = 0; i < j; i++){
				mystack.pop();
			}
			mystack.push("S");
			position++;
			flag = 0;
		}

		else {
			cout << "Error Found" << endl;
			out << "Error Found" << endl;
			return;
		}

		cout << endl;
		out << endl;
	}

	cout << "Syntactically Correct" << endl;
	out << "Syntactically Correct" << endl;

	out.close();
}

// Populates LR table
void PopulateTable(actions (&table)[40][17])
{
	table[0][0].action = "S";
	table[0][0].state = "6";

	table[0][1].action = "S";
	table[0][1].state = "10";

	table[0][7].action = "S";
	table[0][7].state = "9";

	table[0][9].action = "S";
	table[0][9].state = "7";

	table[0][11].action = "goto";
	table[0][11].state = "1";

	table[0][12].action = "goto";
	table[0][12].state = "2";

	table[0][13].action = "goto";
	table[0][13].state = "5";

	table[0][14].action = "goto";
	table[0][14].state = "8";

	table[0][15].action = "goto";
	table[0][15].state = "3";

	table[0][16].action = "goto";
	table[0][16].state = "4";

	table[1][10].action = "ACCT";
	table[1][10].state = "";

	table[2][3].action = "S";
	table[2][3].state = "11";

	table[2][4].action = "S";
	table[2][4].state = "12";

	table[2][10].action = "R";
	table[2][10].state = "1";

	table[3][10].action = "R";
	table[3][10].state = "2";

	table[4][10].action = "R";
	table[4][10].state = "3";

	table[5][3].action = "R";
	table[5][3].state = "6";

	table[5][4].action = "R";
	table[5][4].state = "6";

	table[5][5].action = "S";
	table[5][5].state = "13";

	table[5][6].action = "S";
	table[5][6].state = "14";

	table[5][10].action = "R";
	table[5][10].state = "6";

	table[6][2].action = "S";
	table[6][2].state = "15";

	table[6][3].action = "R";
	table[6][3].state = "11";

	table[6][4].action = "R";
	table[6][4].state = "11";

	table[6][5].action = "R";
	table[6][5].state = "11";

	table[6][6].action = "R";
	table[6][6].state = "11";

	table[6][10].action = "R";
	table[6][10].state = "11";

	table[7][0].action = "S";
	table[7][0].state = "16";

	table[8][3].action = "R";
	table[8][3].state = "9";

	table[8][4].action = "R";
	table[8][4].state = "9";

	table[8][5].action = "R";
	table[8][5].state = "9";

	table[8][6].action = "R";
	table[8][6].state = "9";

	table[8][10].action = "R";
	table[8][10].state = "9";

	table[9][0].action = "S";
	table[9][0].state = "21";

	table[9][1].action = "S";
	table[9][1].state = "22";

	table[9][7].action = "S";
	table[9][7].state = "20";

	table[9][12].action = "goto";
	table[9][12].state = "17";

	table[9][13].action = "goto";
	table[9][13].state = "18";

	table[9][14].action = "goto";
	table[9][14].state = "19";

	table[10][3].action = "R";
	table[10][3].state = "12";

	table[10][4].action = "R";
	table[10][4].state = "12";

	table[10][5].action = "R";
	table[10][5].state = "12";

	table[10][6].action = "R";
	table[10][6].state = "12";

	table[10][10].action = "R";
	table[10][10].state = "12";

	table[11][0].action = "S";
	table[11][0].state = "24";

	table[11][1].action = "S";
	table[11][1].state = "10";

	table[11][7].action = "S";
	table[11][7].state = "9";

	table[11][13].action = "goto";
	table[11][13].state = "23";

	table[11][14].action = "goto";
	table[11][14].state = "8";

	table[12][0].action = "S";
	table[12][0].state = "24";

	table[12][1].action = "S";
	table[12][1].state = "10";

	table[12][7].action = "S";
	table[12][7].state = "9";

	table[12][13].action = "goto";
	table[12][13].state = "25";

	table[12][14].action = "goto";
	table[12][14].state = "8";

	table[13][0].action = "S";
	table[13][0].state = "24";

	table[13][1].action = "S";
	table[13][1].state = "10";

	table[13][7].action = "S";
	table[13][7].state = "9";

	table[13][14].action = "goto";
	table[13][14].state = "26";

	table[14][0].action = "S";
	table[14][0].state = "24";

	table[14][1].action = "S";
	table[14][1].state = "10";

	table[14][7].action = "S";
	table[14][7].state = "9";

	table[14][14].action = "goto";
	table[14][14].state = "27";

	table[15][0].action = "S";
	table[15][0].state = "24";

	table[15][1].action = "S";
	table[15][1].state = "10";

	table[15][7].action = "S";
	table[15][7].state = "9";

	table[15][12].action = "goto";
	table[15][12].state = "28";

	table[15][13].action = "goto";
	table[15][13].state = "5";

	table[15][14].action = "goto";
	table[15][14].state = "8";

	table[16][10].action = "R";
	table[16][10].state = "14";

	table[17][3].action = "S";
	table[17][3].state = "30";

	table[17][4].action = "S";
	table[17][4].state = "31";

	table[17][8].action = "S";
	table[17][8].state = "29";

	table[18][3].action = "R";
	table[18][3].state = "6";

	table[18][4].action = "R";
	table[18][4].state = "6";

	table[18][5].action = "S";
	table[18][5].state = "32";

	table[18][6].action = "S";
	table[18][6].state = "33";

	table[18][8].action = "R";
	table[18][8].state = "6";

	table[19][3].action = "R";
	table[19][3].state = "9";

	table[19][4].action = "R";
	table[19][4].state = "9";

	table[19][5].action = "R";
	table[19][5].state = "9";

	table[19][6].action = "R";
	table[19][6].state = "9";

	table[19][8].action = "R";
	table[19][8].state = "9";

	table[20][0].action = "S";
	table[20][0].state = "21";

	table[20][1].action = "S";
	table[20][1].state = "22";

	table[20][7].action = "S";
	table[20][7].state = "20";

	table[20][12].action = "goto";
	table[20][12].state = "34";

	table[20][13].action = "goto";
	table[20][13].state = "18";

	table[20][14].action = "goto";
	table[20][14].state = "19";

	table[21][3].action = "R";
	table[21][3].state = "11";

	table[21][4].action = "R";
	table[21][4].state = "11";

	table[21][5].action = "R";
	table[21][5].state = "11";

	table[21][6].action = "R";
	table[21][6].state = "11";

	table[21][8].action = "R";
	table[21][8].state = "11";

	table[22][3].action = "R";
	table[22][3].state = "12";

	table[22][4].action = "R";
	table[22][4].state = "12";

	table[22][5].action = "R";
	table[22][5].state = "12";

	table[22][6].action = "R";
	table[22][6].state = "12";

	table[22][8].action = "R";
	table[22][8].state = "12";

	table[23][3].action = "R";
	table[23][3].state = "4";

	table[23][4].action = "R";
	table[23][4].state = "4";

	table[23][5].action = "S";
	table[23][5].state = "13";

	table[23][6].action = "S";
	table[23][6].state = "14";

	table[23][10].action = "R";
	table[23][10].state = "4";

	table[24][3].action = "R";
	table[24][3].state = "11";

	table[24][4].action = "R";
	table[24][4].state = "11";

	table[24][5].action = "R";
	table[24][5].state = "11";

	table[24][6].action = "R";
	table[24][6].state = "11";

	table[24][10].action = "R";
	table[24][10].state = "11";

	table[25][3].action = "R";
	table[25][3].state = "5";

	table[25][4].action = "R";
	table[25][4].state = "5";

	table[25][5].action = "S";
	table[25][5].state = "13";

	table[25][6].action = "S";
	table[25][6].state = "14";

	table[25][10].action = "R";
	table[25][10].state = "5";

	table[26][3].action = "R";
	table[26][3].state = "7";

	table[26][4].action = "R";
	table[26][4].state = "7";

	table[26][5].action = "R";
	table[26][5].state = "7";

	table[26][6].action = "R";
	table[26][6].state = "7";

	table[26][10].action = "R";
	table[26][10].state = "7";

	table[27][3].action = "R";
	table[27][3].state = "8";

	table[27][4].action = "R";
	table[27][4].state = "8";

	table[27][5].action = "R";
	table[27][5].state = "8";

	table[27][6].action = "R";
	table[27][6].state = "8";

	table[27][10].action = "R";
	table[27][10].state = "8";

	table[28][3].action = "S";
	table[28][3].state = "11";

	table[28][4].action = "S";
	table[28][4].state = "12";

	table[28][10].action = "R";
	table[28][10].state = "13";

	table[29][3].action = "R";
	table[29][3].state = "10";

	table[29][4].action = "R";
	table[29][4].state = "10";

	table[29][5].action = "R";
	table[29][5].state = "10";

	table[29][6].action = "R";
	table[29][6].state = "10";

	table[29][10].action = "R";
	table[29][10].state = "10";

	table[30][0].action = "S";
	table[30][0].state = "21";

	table[30][1].action = "S";
	table[30][1].state = "22";

	table[30][7].action = "S";
	table[30][7].state = "20";

	table[30][13].action = "goto";
	table[30][13].state = "35";

	table[30][14].action = "goto";
	table[30][14].state = "19";

	table[31][0].action = "S";
	table[31][0].state = "21";

	table[31][1].action = "S";
	table[31][1].state = "22";

	table[31][7].action = "S";
	table[31][7].state = "20";

	table[31][13].action = "goto";
	table[31][13].state = "36";

	table[31][14].action = "goto";
	table[31][14].state = "19";

	table[32][0].action = "S";
	table[32][0].state = "21";

	table[32][1].action = "S";
	table[32][1].state = "22";

	table[32][7].action = "S";
	table[32][7].state = "20";

	table[32][14].action = "goto";
	table[32][14].state = "37";

	table[33][0].action = "S";
	table[33][0].state = "21";

	table[33][1].action = "S";
	table[33][1].state = "22";

	table[33][7].action = "S";
	table[33][7].state = "20";

	table[33][14].action = "goto";
	table[33][14].state = "38";

	table[34][3].action = "S";
	table[34][3].state = "30";

	table[34][4].action = "S";
	table[34][4].state = "31";

	table[34][8].action = "S";
	table[34][8].state = "39";

	table[35][3].action = "R";
	table[35][3].state = "4";

	table[35][4].action = "R";
	table[35][4].state = "4";

	table[35][5].action = "S";
	table[35][5].state = "32";

	table[35][6].action = "S";
	table[35][6].state = "33";

	table[35][8].action = "R";
	table[35][8].state = "4";

	table[36][3].action = "R";
	table[36][3].state = "5";

	table[36][4].action = "R";
	table[36][4].state = "5";

	table[36][5].action = "S";
	table[36][5].state = "32";

	table[36][6].action = "S";
	table[36][6].state = "33";

	table[36][8].action = "R";
	table[36][8].state = "5";

	table[37][3].action = "R";
	table[37][3].state = "7";

	table[37][4].action = "R";
	table[37][4].state = "7";

	table[37][5].action = "R";
	table[37][5].state = "7";

	table[37][6].action = "R";
	table[37][6].state = "7";

	table[37][8].action = "R";
	table[37][8].state = "7";

	table[38][3].action = "R";
	table[38][3].state = "8";

	table[38][4].action = "R";
	table[38][4].state = "8";

	table[38][5].action = "R";
	table[38][5].state = "8";

	table[38][6].action = "R";
	table[38][6].state = "8";

	table[38][8].action = "R";
	table[38][8].state = "8";

	table[39][3].action = "R";
	table[39][3].state = "10";

	table[39][4].action = "R";
	table[39][4].state = "10";

	table[39][5].action = "R";
	table[39][5].state = "10";

	table[39][6].action = "R";
	table[39][6].state = "10";

	table[39][8].action = "R";
	table[39][8].state = "10";
}

// Bottum up syntax analyzer 
void BottomUpSyntax(vector <tokens> lexered)
{
	// Define the LR table
	actions table[40][17];
	PopulateTable(table);

	// Set up for parser
	int position = 0;
	stack <string> mystack;
	lexered.push_back(dollar);
	mystack.push("$");
	mystack.push("0");

	// File to create output.txt file
	ofstream out;
	out.open("output.txt");

	string t = mystack.top();
	tokens i = lexered.at(position);

	// Symbol table output
	cout << "          SYMBOL TABLE          " << endl;
	cout << "IDENTIFIER          MEM LOCATION" << endl;
	out << "          SYMBOL TABLE          " << endl;
	out << "IDENTIFIER          MEM LOCATION" << endl;

	int counter = 0;
	while (lexered.at(counter).lexeme != "$") {
		if (lexered.at(counter).mem_add != NULL)
		{
			cout << lexered.at(counter).actualInput + "                   ";
			cout << lexered.at(counter).mem_add << endl;
			out << lexered.at(counter).actualInput + "                   ";
			out << lexered.at(counter).mem_add << endl;
		}
		counter++;
	}

	cout << endl << "ASSEMBLY INSTRUCTIONS" << endl;
	out << endl << "ASSEMBLY INSTRUCTIONS" << endl;
	// LR Parser
	while (table[To_Table(t)][To_Table(i.token)].action != "ACCT" || table[To_Table(t)][To_Table(i.token)].state == "") {
		if (lexered.at(position).token == ";") {
			position++;
		}

		string t = mystack.top();
		tokens i = lexered.at(position);

		// Outputs assembly instructions
		if (i.token == "id")
		{
			cout << "PUSHM     ";
			cout << i.mem_add << endl;
			out << "PUSHM     ";
			out << i.mem_add << endl;
		}
		else if (i.token == "*")
		{
			cout << "MUL       ";
			cout << "nil" << endl;
			out << "MUL       ";
			out << "nil" << endl;
		}
		else if (i.token == "-")
		{
			cout << "SUB       ";
			cout << "nil" << endl;
			out << "SUB       ";
			out << "nil" << endl;
		}
		else if (i.token == "+")
		{
			cout << "ADD       ";
			cout << "nil" << endl;
			out << "ADD       ";
			out << "nil" << endl;
		}
		else if (i.token == "/")
		{
			cout << "DIV       ";
			cout << "nil" << endl;
			out << "DIV       ";
			out << "nil" << endl;
		}
		
		// Shift cases
		if (table[To_Table(t)][To_Table(i.token)].action == "S") {
			if(i.token != "$") {
				mystack.push(i.token);
				mystack.push(table[To_Table(t)][To_Table(i.token)].state);
			}
			position++;
		}

		// Reduce sases
		else if (table[To_Table(t)][To_Table(i.token)].action == "R") {
			if (table[To_Table(t)][To_Table(i.token)].state == "1" || table[To_Table(t)][To_Table(i.token)].state == "2" || table[To_Table(t)][To_Table(i.token)].state == "3") {
				// S -> E || S -> A || S -> D [Pop 2 times]
				mystack.pop();
				mystack.pop();

				string temp = table[To_Table(mystack.top())][To_Table("S")].state;
				mystack.push("S");
				mystack.push(temp);
				temp = "";
			}

			else if (table[To_Table(t)][To_Table(i.token)].state == "4" || table[To_Table(t)][To_Table(i.token)].state == "5") {
				// E -> E + T || E - T [Pop 6 times]
				mystack.pop();
				mystack.pop();
				mystack.pop();
				mystack.pop();
				mystack.pop();
				mystack.pop();

				string temp = table[To_Table(mystack.top())][To_Table("E")].state;
				mystack.push("E");
				mystack.push(temp);
				temp = "";
			}

			else if (table[To_Table(t)][To_Table(i.token)].state == "6") {
				// E -> T [Pop 2 times]
				mystack.pop();
				mystack.pop();

				string temp = table[To_Table(mystack.top())][To_Table("E")].state;
				mystack.push("E");
				mystack.push(temp);
				temp = "";
			}

			else if (table[To_Table(t)][To_Table(i.token)].state == "7" || table[To_Table(t)][To_Table(i.token)].state == "8") {
				// T -> T * F || T / F [Pop 6 times]
				mystack.pop();
				mystack.pop();
				mystack.pop();
				mystack.pop();
				mystack.pop();
				mystack.pop();

				string temp = table[To_Table(mystack.top())][To_Table("T")].state;
				mystack.push("T");
				mystack.push(temp);
				temp = "";
			}

			else if (table[To_Table(t)][To_Table(i.token)].state == "9") {
				// T -> F [Pop 2 times]
				mystack.pop();
				mystack.pop();

				string temp = table[To_Table(mystack.top())][To_Table("T")].state;
				mystack.push("T");
				mystack.push(temp);
				temp = "";
			}

			else if (table[To_Table(t)][To_Table(i.token)].state == "10") {
				// F -> ( E ) [Pop 6 times]
				mystack.pop();
				mystack.pop();
				mystack.pop();
				mystack.pop();
				mystack.pop();
				mystack.pop();

				string temp = table[To_Table(mystack.top())][To_Table("F")].state;
				mystack.push("F");
				mystack.push(temp);
				temp = "";
			}

			else if (table[To_Table(t)][To_Table(i.token)].state == "11") {
				// F -> id [Pop 2 times]
				mystack.pop();
				mystack.pop();
			
				string temp = table[To_Table(mystack.top())][To_Table("F")].state;
				mystack.push("F");
				mystack.push(temp);
				temp = "";
			}

			else if (table[To_Table(t)][To_Table(i.token)].state == "12") {
				// F -> num [Pop 2 times]
				mystack.pop();
				mystack.pop();

				string temp = table[To_Table(mystack.top())][To_Table("F")].state;
				mystack.push("F");
				mystack.push(temp);
				temp = "";
			}

			else if (table[To_Table(t)][To_Table(i.token)].state == "13") {
				// A -> id = E [Pop 6 times]
				mystack.pop();
				mystack.pop();
				mystack.pop();
				mystack.pop();
				mystack.pop();
				mystack.pop();

				string temp = table[To_Table(mystack.top())][To_Table("A")].state;
				mystack.push("A");
				mystack.push(temp);
				temp = "";
			}

			else if (table[To_Table(t)][To_Table(i.token)].state == "14") {
				// D -> type id [Pop 4 times]
				mystack.pop();
				mystack.pop();
				mystack.pop();
				mystack.pop();

				string temp = table[To_Table(mystack.top())][To_Table("D")].state;
				mystack.push("D");
				mystack.push(temp);
				temp = "";
			}
		}

		// If input is syntactically correct
		else if (table[To_Table(t)][To_Table(i.token)].action == "ACCT") {
			cout << "ACCEPTED" << endl;
			out << "ACCEPTED" << endl;
			return;
		}
	}

	out.close();
}

int MEMORY = 5000;

// Pushes text input data into a symbol table
// Has a counter for mem addresses 
void LexerOutput(string token, string lexeme, string actual) {
	tokens temp {token, lexeme, actual};

	if (token == "Identifier") {
		temp.mem_add = MEMORY;
		lexered.push_back(temp);
		MEMORY++;
	}

	else if (token == "Real" || token == "Integer") {
		lexered.push_back(temp);
	}

	else if (token == "Keyword") {
		lexered.push_back(temp);
	}

	else if (token == "Operator" && lexeme == "=") {
		lexered.push_back(temp);
	}

	else if (token == "Operator" && lexeme == "+") {
		lexered.push_back(temp);
	}

	else if (token == "Operator" && lexeme == "-") {
		lexered.push_back(temp);
	}

	else if (token == "Operator" && lexeme == "/") {
		lexered.push_back(temp);
	}

	else if (token == "Operator" && lexeme == "*") {
		lexered.push_back(temp);
	}

	else if (token == "Separator" && lexeme == "(") {
		lexered.push_back(temp);
	}

	else if (token == "Separator" && lexeme == ")") {
		lexered.push_back(temp);
	}
	
	else if (token == "Separator" && lexeme == ";") {
		lexered.push_back(temp);
	}

	else if (token == "EndSymbol" && lexeme == "$") {
		lexered.push_back(temp);
	}
}

// Lexer function
void Lexer()
{
	ifstream in;

    string s, w, num;
    int state = 0;
    int column;
    bool flag = true;

    // Defining FSM - mimics the FSM defined in the documentation
    int fsm[10][8] = {  {1, 3, 7, 8, 0, 0, 8, 9}, 
                        {1, 1, 2, 2, 1, 2, 2, 2}, 
                        {0, 0, 0, 0, 0, 0, 0, 0}, 
                        {5, 3, 5, 5, 5, 5, 4, 5}, 
                        {6, 4, 6, 6, 6, 6, 6, 6}, 
                        {0, 0, 0, 0, 0, 0, 0, 0}, 
                        {0, 0, 0, 0, 0, 0, 0, 0}, 
                        {0, 0, 0, 0, 0, 0, 0, 0}, 
                        {0, 0, 0, 0, 0, 0, 0, 0}, 
                        {9, 9, 9, 9, 9, 9, 9, 0} };
    
    // Array of operators
    char op[8] = {'+', '-', '*', '/', '=', '%', '<', '>'};

    // Array of separators
    char sep[10] = {'[', ']', '(', ')', '{', '}', ',', '.', ';', ':'};

    // Array of keywords
    string keywords[21] = {"int", "float", "bool", "True", "False", "if", "else", "then", "endif", "endelse", "while", "whileend", 
        "do", "enddo", "for", "endfor", "STDinput", "STDoutput", "and", "or", "not"};

    in.open("input.txt");

    if(!in.is_open()) {
        cout << "ERROR: File cannot be opened/found\n";
        system("pause");
        exit(1);
    }

    // cout << endl;
    // cout << "\tTOKENS\t\t\t     LEXEMES\n\n";

    while(getline(in, s)) {
        for(char c : s) {
            // Operator check
            if(state == 0) {
                for(int i = 0; i < 8; i++) {
                    // Operator column
                    column = 2;
                    if(c == op[i]) {
                        // Changing states
                        state = fsm[state][column];
                        // cout << "OPERATOR\t\t=\t\t" << c << endl;
						string s(1, c);
						LexerOutput("Operator", s, s);
						s = "";
                    }
                    // Revert back to state 0 after output
                    state = 0;          
                }
            }

            // Separator check
            if(state == 0){
                for(int i = 0; i < 10; i++) {
                    // Separator column
                    column = 3;
                    if(c == sep[i]) {
                        // Changing states
                        state = fsm[state][column];
                        // cout << "SEPARATOR\t\t=\t\t" << c << endl;
						string s(1, c);
						LexerOutput("Separator", s, s);
						s = "";
                    }
                    // Revert back to state 0 after output
                    state = 0;
                }
            }

            // Checks for comment blocks in txt file
            if(c == '!' && state == 0) {
                // Changing states
                state = 9;
            }
            else if(c == '!' && state == 9) {
                // Revert back to state 0 after end of comment block
                state = 0;
            }

            // Character check
            column = 0;
            if(isalpha(c) && state == 0) {
                state = fsm[state][column];
                // Concatonate char to w string
                w += c;
            }

            else if((isalpha(c) || isdigit(c) || c == '$' || c == '_') && state == 1) {
                // Concatonate char to w string
                w += c;
            }

            else if(!isalpha(c) && !isdigit(c) && c != '$' && c != '_' && state == 1) {
                // Keyword check
                for(int i = 0; i < 21; i++) {
                    if(w == keywords[i]) {
                        // cout << "KEYWORD\t\t\t=\t\t" << w << endl;
						LexerOutput("Keyword", "key", w);
                        flag = false;
                    }
                }

                // If not keyword, w is an identifier
                if(flag != false) {
                    // cout << "IDENTIFIER\t\t=\t\t" << w << endl;
					LexerOutput("Identifier", "id", w);
                }

                // Next 2 for loops checks to see if !isalpha(c) && !isdigit(c) && c != '$' && c != '_' 
                // is an operator or separator
                for(int i = 0; i < 8; i++) {
                    // Operator column
                    column = 2;
                    if(c == op[i]) {
                        // Changing states
                        state = fsm[state][column];
                        // cout << "OPERATOR\t\t=\t\t" << c << endl;
						string s(1, c);
						LexerOutput("Operator", s, s);
						s = "";
                    }
                    // Revert back to state 0 after output
                    state = 0;          
                }

                for(int i = 0; i < 10; i++) {
                    // Separator column
                    column = 3;
                    if(c == sep[i]) {
                        // Changing states
                        state = fsm[state][column];
                        // cout << "SEPARATOR\t\t=\t\t" << c << endl;
						string s(1, c);
						LexerOutput("Separator", s, s);
						s = "";
                    }
                    // Revert back to state 0 after output
                    state = 0;
                }

                state = 0;
                w = "";
                flag = true;
            }

            // Integer check
            column = 1;
            if(isdigit(c) && state == 0) {
                state = fsm[state][column];
                // Concatonate char to num string
                num += c;
            }

            else if(isdigit(c) && state == 3) {
                // Concatonate char to string
                num += c;
            }

            else if(!isdigit(c) && c != '.' && state == 3) {
                // cout << "INTEGER\t\t\t=\t\t" << num << endl;
				LexerOutput("Integer", "num", num);

                // Next 2 for loops checks to see if !isdigit(c) && c != '.' is an operator or separator
                for(int i = 0; i < 8; i++) {
                    // Operator column
                    column = 2;
                    if(c == op[i]) {
                        // Changing states
                        state = fsm[state][column];
                        // cout << "OPERATOR\t\t=\t\t" << c << endl;
						string s(1, c);
						LexerOutput("Operator", s, s);
						s = "";
                    }
                    // Revert back to state 0 after output
                    state = 0;          
                }

                for(int i = 0; i < 10; i++) {
                    // Separator column
                    column = 3;
                    if(c == sep[i]) {
                        // Changing states
                        state = fsm[state][column];
                        // cout << "SEPARATOR\t\t=\t\t" << c << endl;
						string s(1, c);
						LexerOutput("Separator", s, s);
						s = "";
                    }
                    // Revert back to state 0 after output
                    state = 0;
                }

                state = 0;
                num = "";
            }

            // Real number check
            else if(c == '.' && state == 3) {
                column = 6;
                state = fsm[state][column];
                num += c;
            }

            else if(isdigit(c) && state == 4) {
                num += c;
            }

            else if(!isdigit(c) && state == 4) {
                // cout << "REAL NUMBER\t\t=\t\t" << num << endl;
				LexerOutput("Real", "num", num);

                // Next 2 for loops checks to see if !isdigit(c) is an operator or separator
                for(int i = 0; i < 8; i++) {
                    // Operator column
                    column = 2;
                    if(c == op[i]) {
                        // Changing states
                        state = fsm[state][column];
                        // cout << "OPERATOR\t\t=\t\t" << c << endl;
						string s(1, c);
						LexerOutput("Operator", s, s);
						s = "";
                    }
                    // Revert back to state 0 after output
                    state = 0;          
                }

                for(int i = 0; i < 10; i++) {
                    // Separator column
                    column = 3;
                    if(c == sep[i]) {
                        // Changing states
                        state = fsm[state][column];
                        // cout << "SEPARATOR\t\t=\t\t" << c << endl;
						string s(1, c);
						LexerOutput("Separator", s, s);
						s = "";
                    }
                    // Revert back to state 0 after output
                    state = 0;
                }

                state = 0;
                num = "";
            }
        }
    }

	LexerOutput("EndSymbol", "$", "$");
    in.close();
}

int main()
{
	// Initialized dollar token
	dollar.token = "EndSymbol";
	dollar.lexeme = "$";
	dollar.actualInput = "$";

	Lexer();
	BottomUpSyntax(lexered);
}