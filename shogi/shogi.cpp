#include<iostream>
#include<conio.h>
#include<fstream>
#include<math.h>
#include<windows.h>
using namespace std;
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int colour)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
}
enum PLAYER { WHITE, BLACK, };
struct LOCATION { int rloc, cloc; };
void LEFTTORIGHT(int row, int startcol, int endcol, char symbol, int colour) {
	for (int col = startcol; col <= endcol; col++) {
		SetClr(colour);
		gotoRowCol(row, col);
		cout << symbol;
	}
}
void BOX(int row, int col, int boxrows, int boxcols, int colour) {
	for (int r = 0; r < boxrows; r++) {
		for (int c = 0; c < boxcols; c++) {
			SetClr(colour);
			gotoRowCol(row + r, c + col);
			cout << char(-37);
		}
	}
}
void BOARD(int Dimention, int rows, int cols) {
	for (int r = 0; r < Dimention; r++) {
		for (int c = 0; c < Dimention; c++) {
			if ((r + c) % 2 == 0) {
				BOX(r * rows, c * cols, rows, cols, 15);
			}
			else {
				BOX(r * rows, c * cols, rows, cols, 8);
			}
		}
	}
}
void INITIALIZATION(char**& Matrix, int& Dimention, int TURN, string nameAray[], char**& TEMP_MATRIX, char**& TEMP_MATRIX2) {
	ifstream reader("INPUT.txt");
	if (!reader)
		cout << "Loading fail....", exit(1);
	reader >> Dimention;
	Matrix = new char* [Dimention];
	TEMP_MATRIX = new char* [Dimention];
	TEMP_MATRIX2 = new char* [Dimention];
	for (int r = 0; r < Dimention; r++) {
		Matrix[r] = new char[Dimention] {};
		TEMP_MATRIX[r] = new char[Dimention] {};
		TEMP_MATRIX2[r] = new char[Dimention] {};
	}
	for (int r = 0; r < Dimention; r++) {
		for (int c = 0; c < Dimention; c++)
			reader >> Matrix[r][c];
	}
	for (int r = 0; r < Dimention; r++) {
		for (int c = 0; c < Dimention; c++) {
			TEMP_MATRIX[r][c] = Matrix[r][c];
			TEMP_MATRIX2[r][c] = Matrix[r][c];
		}
	}
	for (int r = 0; r < 2; r++) {
		cout << "PLAYER " << r + 1 << ":";
		cin >> nameAray[r];
	}
	TURN = 0;
}
void INITIALIZATION1(char**& Matrix, int& Dimention, int TURN, string nameAray[], char**& TEMP_MATRIX, char**& TEMP_MATRIX2) {
	ifstream reader("Text.txt");
	if (!reader)
		cout << "Loading fail....", exit(1);
	reader >> Dimention;
	Matrix = new char* [Dimention];
	TEMP_MATRIX = new char* [Dimention];
	TEMP_MATRIX2 = new char* [Dimention];
	for (int r = 0; r < Dimention; r++) {
		Matrix[r] = new char[Dimention] {};
		TEMP_MATRIX[r] = new char[Dimention] {};
		TEMP_MATRIX2[r] = new char[Dimention] {};
	}
	for (int r = 0; r < Dimention; r++) {
		for (int c = 0; c < Dimention; c++)
			reader >> Matrix[r][c];
	}
	for (int r = 0; r < Dimention; r++) {
		for (int c = 0; c < Dimention; c++) {
			TEMP_MATRIX[r][c] = Matrix[r][c];
			TEMP_MATRIX2[r][c] = Matrix[r][c];
		}
	}
	for (int r = 0; r < 2; r++) {
		cout << "PLAYER " << r + 1 << ":";
		cin >> nameAray[r];
	}
	TURN = 0;
}
void TURN_DISPLAY(string nameAray[], int TURN) {
	cout << "\n\n\n\n\n" << endl;
	cout << nameAray[TURN] << "'s TURN" << endl;
}
void selectLOCATION(LOCATION& P, int Dimention, int divide) {
	int y, x; {
		getRowColbyLeftClick(x, y);
		P.rloc = x / divide;
		P.cloc = y / divide;
	}
}
void PRINT_DATA(char** Matrix, int Dimention, int Bdim) {
	int fR = 0;
	int fC = 0;
	for (int i = 0; i < Dimention; i++) {
		for (int j = 0; j < Dimention; j++) {
			gotoRowCol((i + Bdim / 2) + fR, (j + Bdim / 2) + fC);
			if (Matrix[i][j] != '-')
				cout << Matrix[i][j];
			fC += (Bdim - 1);
		}
		fC = 0;
		fR += (Bdim - 1);
	}
}
bool WHITEPIECE(char symbol) { return symbol >= 'a' && symbol <= 'z'; }
bool BLACKPIECEe(char symbol) { return symbol >= 'A' && symbol <= 'Z'; }
bool MY_PIECE(char symbol, int TURN) {
	if (TURN == WHITE)
		return WHITEPIECE(symbol);
	return BLACKPIECEe(symbol);
}
bool IS_IN_RANGE(int Dimention, LOCATION SOURCE) {
	if (SOURCE.rloc<0 || SOURCE.rloc>Dimention - 1 || SOURCE.cloc<0 || SOURCE.cloc>Dimention - 1)
		return false;
	return true;
}
bool SOURCEVALID(char** Matrix, int Dimention, int TURN, LOCATION SOURCE) {
	if (Matrix[SOURCE.rloc][SOURCE.cloc] == '-')
		return false;
	if (IS_IN_RANGE(Dimention, SOURCE) == 0)
		return false;
	return MY_PIECE(Matrix[SOURCE.rloc][SOURCE.cloc], TURN);
}
bool DESTINATIONVALID(char** Matrix, int Dimention, int TURN, LOCATION SOURCE) {
	if (IS_IN_RANGE(Dimention, SOURCE) == 0)
		return false;
	return !(MY_PIECE(Matrix[SOURCE.rloc][SOURCE.cloc], TURN));
}
void UPDATE(char** Matrix, LOCATION SOURCE, LOCATION Dest) {
	char temp = Matrix[SOURCE.rloc][SOURCE.cloc];
	Matrix[Dest.rloc][Dest.cloc] = temp;
	Matrix[SOURCE.rloc][SOURCE.cloc] = '-';
}
void REPLACE(char** Matrix, LOCATION pre, LOCATION Dest, char symbol) {
	Matrix[Dest.rloc][Dest.cloc] = symbol;
	Matrix[pre.rloc][pre.cloc] = '-';
}
void CHANGETURN(int& TURN) { TURN = (TURN + 1) % 2; }
bool HORIZONTOL(LOCATION Take, LOCATION Dest) { return(Take.rloc == Dest.rloc); }
bool VERTICAL(LOCATION Take, LOCATION Dest) { return(Take.cloc == Dest.cloc); }
bool DIGNAL(LOCATION Take, LOCATION Dest) { return (abs(Take.rloc - Dest.rloc) == abs(Take.cloc - Dest.cloc)); }
bool SECOND_DIGNAL(LOCATION Take, LOCATION Dest) { return (abs(Take.rloc - Dest.rloc) == abs(Take.cloc - Dest.cloc) && (Take.rloc - Dest.rloc) != (Take.cloc - Dest.cloc)); }
bool CLEARHORIZOTALPATH(char** Matrix, LOCATION Take, LOCATION Dest) {
	int s, e;
	if (Dest.cloc > Take.cloc) {
		s = Take.cloc + 1;
		e = Dest.cloc;
	}
	else {
		s = Dest.cloc + 1;
		e = Take.cloc;
	}
	for (int r = s; r < e; r++) {
		if (Matrix[Take.rloc][r] != '-')
			return false;
	}
	return true;
}
bool CLEARVERTICALPATH(char** Matrix, LOCATION Take, LOCATION Dest) {
	int s, e;
	if (Dest.rloc > Take.rloc)
	{
		s = Take.rloc + 1;
		e = Dest.rloc;
	}
	else {
		s = Dest.rloc + 1;
		e = Take.rloc;
	}
	for (int r = s; r < e; r++) {
		if (Matrix[r][Take.cloc] != '-')
			return false;

	}
	return true;
}
bool DIGNALPATHClearLEFTTORIGHT(char** Matrix, LOCATION Take, LOCATION Dest) {
	int si, sj, ei, ej;
	if (Dest.rloc - Take.rloc > 0 && Dest.cloc - Take.cloc > 0) {
		si = Take.rloc + 1;
		sj = Take.cloc + 1;
		ei = Dest.rloc;
		ej = Dest.cloc;
	}
	else
	{
		si = Dest.rloc + 1;
		sj = Dest.cloc + 1;
		ei = Take.rloc;
		ej = Take.cloc;
	}
	for (int r = si, c = sj; c < ej; r++, c++)
	{
		if (Matrix[r][c] != '-')
			return false;
	}
	return true;
}
bool DIGNALPATHClearR2L(char** Matrix, LOCATION Take, LOCATION Dest) {
	int si, sj, ei, ej;
	if (Dest.rloc - Take.rloc > 0 && Dest.cloc - Take.cloc < 0) {
		si = Take.rloc + 1;
		sj = Take.cloc - 1;
		ei = Dest.rloc;
		ej = Dest.cloc;
	}
	else {
		si = Dest.rloc + 1;
		sj = Dest.cloc;
		ei = Take.rloc;
		ej = Take.cloc + 1;

	}
	for (int r = si, c = sj;  c > ej; r++, c--)
	{
		if (Matrix[r][c] != '-')
			return false;

	}
	return true;
}
bool LANCELEGALITU(char** Matrix, char symbol, LOCATION SOURCE, LOCATION Dest) {
	if (symbol == toupper(symbol)) {
		if (Dest.rloc > SOURCE.rloc) {
			return (VERTICAL(SOURCE, Dest) && CLEARVERTICALPATH(Matrix, SOURCE, Dest));
		}
	}
	else {
		if (Dest.rloc < SOURCE.rloc)
		{
			return (VERTICAL(SOURCE, Dest) && CLEARVERTICALPATH(Matrix, SOURCE, Dest));
		}
	}
}
bool ROOKLEGALITY(char** Matrix, LOCATION SOURCE, LOCATION Dest) {
	return (VERTICAL(SOURCE, Dest) && CLEARVERTICALPATH(Matrix, SOURCE, Dest)) || (HORIZONTOL(SOURCE, Dest) && CLEARHORIZOTALPATH(Matrix, SOURCE, Dest));
}
bool BISHOPLEGALITY(char** Matrix, LOCATION SOURCE, LOCATION Dest) {
	return (DIGNAL(SOURCE, Dest) && DIGNALPATHClearLEFTTORIGHT(Matrix, SOURCE, Dest)) || (SECOND_DIGNAL(SOURCE, Dest) && DIGNALPATHClearR2L(Matrix, SOURCE, Dest));

}
bool KNIGHTLEGALITY(char** Matrix, LOCATION SOURCE, LOCATION Dest, char symbol) {
	int CHECK = (Dest.rloc - SOURCE.rloc);
	if (symbol == toupper(symbol))
		return CHECK == 2 && (abs(Dest.cloc - SOURCE.cloc) == 1);
	return CHECK == -2 && (abs(Dest.cloc - SOURCE.cloc) == 1);
	return false;
}
bool KINGLEGALITY(char** Matrix, LOCATION SOURCE, LOCATION Dest) {
	int temp = abs(Dest.rloc - SOURCE.rloc);
	int temp1 = abs(Dest.cloc - SOURCE.cloc);
	if (temp == 1 && VERTICAL(SOURCE, Dest))
		return true;
	else if (temp1 == 1 && HORIZONTOL(SOURCE, Dest))
		return true;
	else if ((abs(SOURCE.rloc - Dest.rloc) == 1) && (abs(SOURCE.cloc - Dest.cloc) == 1))
		return true;
	return false;

}
bool SILVERLEGALITY(char** Matrix, char symbol, LOCATION SOURCE, LOCATION Dest)
{
	if (symbol == toupper(symbol)) {
		if (Dest.cloc - SOURCE.cloc > 0 && VERTICAL(SOURCE, Dest))
			return true;
		if ((abs(SOURCE.rloc - Dest.rloc) == 1) && (abs(SOURCE.cloc - Dest.cloc) == 1))
			return true;

	}
	if (Dest.cloc - SOURCE.cloc < 0 && VERTICAL(SOURCE, Dest))
		return true;

	if ((abs(SOURCE.rloc - Dest.rloc) == 1) && (abs(SOURCE.cloc - Dest.cloc) == 1))
		return true;
	return false;
}
bool GOLDENREALITY(char** Matrix, char symbol, LOCATION SOURCE, LOCATION Dest) {
	int temp = abs(Dest.rloc - SOURCE.rloc);
	int temp1 = abs(Dest.cloc - SOURCE.cloc);
	if (temp == 1 && VERTICAL(SOURCE, Dest))
		return true;

	else if (temp1 == 1 && HORIZONTOL(SOURCE, Dest))
		return true;
	if (symbol == toupper(symbol))
	{
		if (((SOURCE.rloc - Dest.rloc == -1) && (SOURCE.cloc - Dest.cloc == 1)) || ((SOURCE.rloc - Dest.rloc == -1) && (SOURCE.cloc - Dest.cloc == -1)))
		{
			return true;
		}
	}

	if (((SOURCE.rloc - Dest.rloc == 1) && (SOURCE.cloc - Dest.cloc == 1)) || ((SOURCE.rloc - Dest.rloc == 1) && (SOURCE.cloc - Dest.cloc == -1)))
		return true;
	return false;
}
bool PAWNLEGALITY(char** Matrix, char symbol, LOCATION SOURCE, LOCATION Dest) {
	int CHECK = (Dest.rloc - SOURCE.rloc);
	int check1 = (Dest.rloc - SOURCE.rloc);
	if (symbol == toupper(symbol))
	{
		if (CHECK == 1 && VERTICAL(SOURCE, Dest))
			return true;
	}
	if (check1 == -1 && VERTICAL(SOURCE, Dest))
		return true;
	return false;
}
bool LEGAL_MOVE(char** Matrix, LOCATION SOURCE, LOCATION Dest)
{
	char temp = Matrix[SOURCE.rloc][SOURCE.cloc];
	switch (temp) {
	case 'l':
	case 'L':
		return LANCELEGALITU(Matrix, temp, SOURCE, Dest);
	case 'R':
	case 'r':
		return ROOKLEGALITY(Matrix, SOURCE, Dest);
	case'B':
	case'b':
		return BISHOPLEGALITY(Matrix, SOURCE, Dest);
	case's':
	case'S':
		return SILVERLEGALITY(Matrix, temp, SOURCE, Dest);
	case 'g':
	case 'G':
		return GOLDENREALITY(Matrix, temp, SOURCE, Dest);
	case'p':
	case'P':
		return PAWNLEGALITY(Matrix, temp, SOURCE, Dest);
	case'n':
	case'N':
		return KNIGHTLEGALITY(Matrix, SOURCE, Dest, temp);
	case'k':
	case'K':
		return KINGLEGALITY(Matrix, SOURCE, Dest);

	}
}
bool** HIGHLIGHT(char** Matrix, int Dimention, LOCATION Take, int TURN) {
	bool** boolB = new bool* [9] {};
	for (int r = 0; r < Dimention; r++) {
		boolB[r] = new bool[9] {};
	}
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			LOCATION dc;
			dc.rloc = r; dc.cloc = c;
			if (!(Take.rloc == dc.rloc && Take.cloc == dc.cloc))
			{

				boolB[r][c] = LEGAL_MOVE(Matrix, Take, dc);
			}

		}
	}
	return boolB;
}
LOCATION KINGLOCFINDER(char** Matrix, int Dimention, int TURN)
{
	LOCATION temp;
	char king;
	if (TURN == 0)
		king = 'k';
	else
		king = 'K';

	for (int r = 0; r < Dimention - 1; r++)
		for (int c = 0; c < Dimention - 1; c++)
		{
			temp.rloc = r, temp.cloc = c;
			if (Matrix[temp.rloc][temp.cloc] == king)
				return temp;

		}

}
bool CHECK(char** Matrix, int Dimention, int TURN) {
	LOCATION Take;
	CHANGETURN(TURN);
	LOCATION Dest = KINGLOCFINDER(Matrix, Dimention, TURN);
	CHANGETURN(TURN);
	for (int r = 0; r < Dimention - 1; r++) {
		for (int c = 0; c < Dimention - 1; c++) {
			Take.rloc = r, Take.cloc = c;
			if (MY_PIECE(Matrix[Take.rloc][Take.cloc], TURN)) {
				if (LEGAL_MOVE(Matrix, Take, Dest)) {
					return true;
				}
			}
		}
	}
	return false;
}
bool SELFCHECK(char** Matrix, int Dimention, int TURN) {
	CHANGETURN(TURN);
	return CHECK(Matrix, Dimention, TURN);
}
void COPY(char** M1, char** M2, char** M3, int Dimention) {
	for (int r = 0; r < Dimention - 1; r++) {
		for (int c = 0; c < Dimention - 1; c++) {
			M2[r][c] = M1[r][c];
			M3[r][c] = M1[r][c];
		}
	}
}


bool CheckMate(char** Matrix, int Dimention, int TURN, char** M2) {
	LOCATION MyPiece, Dest, prev;
	bool CHECKMATE = false;
	CHANGETURN(TURN);
	for (int r = 0; r < Dimention - 1; r++) {
		for (int c = 0; c < Dimention - 1; c++) {
			prev.rloc = r, prev.cloc = c;
			MyPiece.rloc = r, MyPiece.cloc = c;
			if (MY_PIECE(Matrix[r][c], TURN)) {
				for (int k = 0; k < Dimention - 1; k++) {
					for (int l = 0; l < Dimention - 1; l++) {
						Dest.rloc = k, Dest.cloc = l;
						if (LEGAL_MOVE(Matrix, MyPiece, Dest)) {
							REPLACE(M2, prev, Dest, Matrix[r][c]);
							if (SELFCHECK(M2, Dimention, TURN) == 0)
								return false;
							prev.rloc = k, prev.cloc = l;
						}
					}
				}
			}
		}
	}
	return true;
}


void Load(char** matrix, int dim)
{
	ofstream wrt("bscs22110_Input.txt");

	wrt << dim << endl;
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
			wrt << matrix[i][j] << " ";
		wrt << endl;
	}


}
int main() {
	char** Matrix, ** TempB, ** TempM2;
	string nameAray[2] = {};
	LOCATION P, SOURCE, Dest;
	int TURN = 0, Dimention = 0;
	int choice = -1;
	cout << "Please Select:\n";
	cout << "1.New\n";
	cout << "2.Load\n";
	cin >> choice;
	if (choice == 2) {
		INITIALIZATION1(Matrix, Dimention, TURN, nameAray, TempB, TempM2);
	}
	else {
		INITIALIZATION(Matrix, Dimention, TURN, nameAray, TempB, TempM2);
	}
	
	int BoxDim = 7;
	BOARD(Dimention - 1, BoxDim, BoxDim);
	PRINT_DATA(Matrix, Dimention, BoxDim);
	while (true) {
		TURN_DISPLAY(nameAray, TURN);
		do {
			do {
				do {
					do {
						selectLOCATION(SOURCE, Dimention, BoxDim);
					} while (SOURCEVALID(Matrix, Dimention, TURN, SOURCE) == 0);
					selectLOCATION(Dest, Dimention, BoxDim);
				} while (DESTINATIONVALID(Matrix, Dimention, TURN, Dest) == 0);
			} while ((LEGAL_MOVE(Matrix, SOURCE, Dest) == 0));
			UPDATE(TempB, SOURCE, Dest);
		} while (SELFCHECK(TempB, Dimention, TURN));
		UPDATE(Matrix, SOURCE, Dest);
		COPY(Matrix, TempB, TempM2, Dimention);
		if (CHECK(Matrix, Dimention, TURN)) {

			if (CheckMate(Matrix, Dimention, TURN, TempM2)) {
				gotoRowCol(56, 0);
				cout << "CHECKMATE";
				exit(1);
			}
			else {
				gotoRowCol(56, 0);
				cout << "CHECK!!";
			}
		}
		else {
			gotoRowCol(56, 0);
			cout << "                                            ";
		}
		BOARD(Dimention - 1, BoxDim, BoxDim);
		PRINT_DATA(Matrix, Dimention, BoxDim);
		CHANGETURN(TURN);
		Load(Matrix,Dimention);

	}
	return 0;
}
