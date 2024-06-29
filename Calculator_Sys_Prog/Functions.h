#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>


HDC hdc;
HWND hWnd;
HINSTANCE hInst;

namespace myMath {
	double log(double a, double b) { // b по основанию a
		return std::log(b) / std::log(a);
	}

	double abs(double x) { // функция нахождения модуля
		if (x < 0) {
			return -x;
		}
		else {
			return x;
		}
	}

	std::string sin(double value, char ch) {
		std::string temp = "";
		if (ch == 'R') {
			while (value > 6.28319) {
				value -= 6.28319;
			}
			if (value >= 0 && value <= 3.141591) {
				temp = std::to_string(std::sin(value));
				return temp;
			}
			else if (value > 3.141591 && value <= 6.28319) {
				temp += "-";
				temp += std::to_string(std::sin(3.141591 - (value - 3.141591)));
				return temp;
			}
		}
		else if (ch == 'D') {
			return std::to_string(std::sin(value * 3.14159 / 180));
		}
	}

	std::string cos(double value, char ch) {
		std::string temp = "";
		if (ch == 'R') {
			while (value > 6.28319) {
				value -= 6.28319;
			}
			if ((value >= 4.71239 && value <= 6.28319) || (value >= 0 && value <= 1.5708)) {
				return std::to_string(std::cos(value));
			}
			else if ((value > 1.5708 && value <= 3.14159)) {
				temp += "-";
				temp += std::to_string(std::cos(1.5708 - (value - 1.5708)));
				return temp;
			}
			else if ((value > 3.14159 && value < 4.71239)) {
				temp += "-";
				temp += std::to_string(std::cos(4.71239 + (4.71239 - value)));
				return temp;
			}
		}
		else if (ch == 'D') {
			return std::to_string(std::cos(value * 3.14159 / 180));
		}
	}

	double tg(double value, char ch) {
		if (ch == 'R') {
			return stod(sin(value, 'R')) / stod(cos(value, 'R'));
		}
		else if (ch == 'D') {
			return stod(sin(value, 'D')) / stod(cos(value, 'D'));
		}
	}

	double ctg(double value, char ch) {
		if (ch == 'R') {
			return stod(cos(value, 'R')) / stod(sin(value, 'R'));
		}
		else if (ch == 'D') {
			return stod(cos(value, 'D')) / stod(sin(value, 'D'));
		}
	}

}

bool isDigit(std::string);
bool Checking(std::string, int);
std::string Calculate(std::string);
std::string SymbolicAnalysis(std::string, int&, int&);
std::string Operating(std::string, std::string, char);
std::string SublineIncut(std::string, std::string, int, int, int, std::vector < std::vector<char>>&, std::vector < std::vector<int>>&, int);
std::string PartCalc(int, std::vector < std::vector<char>>&, std::vector < std::vector<int>>&, std::string, char, char);

bool Checking(std::string str, int i) {
	if (i == 0) {
		return false;
	}
	if (str[i] == '+' || str[i] == '/' || str[i] == '*') {
		return true;
	}
	else if (str[i] == '-') {
		for (int a = i - 1;; a--) {
			if (str[a] == ' ') {
				continue;
			}
			else if ((str[a] != '(') && (str[a] != '+') && (str[a] != '-') && (str[a] != '/') && (str[a] != '*')) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}

std::string SublineIncut(std::string str, std::string substr, int x, int y, int xSize, std::vector < std::vector<char>>& operators, std::vector < std::vector<int>>& oper_pos, int a) {
	str.replace(x, y - x + 1, substr);
	for (int i = 0; i < operators[xSize - 1].size(); i++) {
		if (oper_pos[xSize - 1][i] > oper_pos[xSize - 1][a]) {
			oper_pos[xSize - 1][i] -= ((y - x + 1) - substr.size());
		}
	}
	operators[xSize - 1].erase(operators[xSize - 1].begin() + a);
	oper_pos[xSize - 1].erase(oper_pos[xSize - 1].begin() + a);
	operators[xSize - 1].shrink_to_fit();
	oper_pos[xSize - 1].shrink_to_fit();
	if (oper_pos[xSize - 1].empty() /*&& xSize > 1*/) {
		oper_pos[xSize - 1].resize(0);
		operators[xSize - 1].resize(0);
		oper_pos.erase(oper_pos.begin() + (xSize - 1));
		operators.erase(operators.begin() + (xSize - 1));
	}
	operators.shrink_to_fit();
	oper_pos.shrink_to_fit();
	return str;
}

std::string Operating(std::string leftPart, std::string rightPart, char symb) {
	if (symb == '*') {
		return std::to_string(stod(leftPart) * stod(rightPart));
	}
	else if (symb == '/') {
		return std::to_string(stod(leftPart) / stod(rightPart));
	}
	else if (symb == '+') {
		return std::to_string(stod(leftPart) + stod(rightPart));
	}
	else if (symb == '-') {
		return std::to_string(stod(leftPart) - stod(rightPart));
	}
}

std::string SymbolicAnalysis(std::string str, int& left_par, int& right_par) {
	int iterator_pos = 0;
	std::string left = "", right_n = "";
	char right = 'R';
	std::string str2 = "";
	for (int i = 0; i < str.size(); i++) {
		if ((i <= str.size() - 2) & (str[i] == 'P' && str[i + 1] == 'i')) {
			str2 += "3.14159";
			i++;
		}
		else if (str[i] == 'e') {
			str2 += "2.71828";
		}
		else if (str[i] == '|') {
			std::string number = "", subline = "";
			if (i + 2 > str.size() - 1) {
				left_par += 1000;
				return str2;
			}
			for (int a = i + 1; str[a] != '|' && a != str.size(); a++) {
				if (!isdigit(str[a]) && str[a] != '.' && str[a] != '-') {
					left_par += 1000;
					return str2;
				}
				number += str[a];
				iterator_pos = a;
				if (a == str.size() - 1) {
					left_par += 1000;
					return str2;
				}
			}
			subline = std::to_string(abs(stod(number)));
			str.replace(i, iterator_pos - i + 2, subline);
			i += subline.size() - 1;
			if (i + 1 == str.size()) {
				str2 += subline;
			}
			else {
				for (int j = i + 1; j < str.size(); j++) {
					if (str[j] == ' ') {
						continue;
					}
					else if (str[j] != '^') {
						str2 += subline;
					}
					else {
						break;
					}
				}
			}

		}
		else if (str[i] == '^') {
			left = "", right_n = "";
			std::string number = "";
			int iterator = 0;
			if (i - 1 < 0) {
				left_par += 1000;
				return str2;
			}
			for (int j = i - 1; !isdigit(str[j]); j--) {
				if (str[j] != ' ' || j == 0) {
					left_par += 1000;
					return str2;
				}
			}
			for (int l = i - 1; l >= 0; l--) {
				if (str2.size() > 0) {
					if (isdigit(str[l]) && str[l] == str2[str2.size() - 1]) {
						str2.pop_back();
					}
				}
				if (!isdigit(str[l]) && str[l] != '-' && str[l] != ' ' && str[l] != '.') {
					iterator = l + 1;
					break;
				}
			}
			for (int a = iterator; a != i; a++) {
				if (str[a] != ' ') {
					if (str[a] == ',') {
						left += '.';
					}
					else {
						left += str[a];
					}
				}
			}
			if (i + 3 > str.size() - 1 | (str[i + 1] != '(')) {
				left_par += 1000;
				return str2;
			}
			for (int a = i + 2; str[a] != ')'; a++) {
				if (str[a] != ' ') {
					if (str[a] == ',') {
						right_n += '.';
					}
					else {
						if (!isdigit(str[a]) && str[a] != '.' && str[a] != '-') {
							left_par += 1000;
							return str2;
						}
						right_n += str[a];
					}
				}
				iterator_pos = a;
				if (a == str.size() - 1) {
					left_par += 1000;
					return str2;
				}
			}
			i -= iterator;

			str2 += std::to_string(std::pow(stod(left), stod(right_n)));
			i += (iterator_pos + 1) - i;
		}
		else if ((i <= str.size() - 4) & (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' && str[i + 3] == 't')) {
			std::string number = "";
			if (i + 6 > str.size() - 1 | (str[i + 4] != '(')) {
				left_par += 1000;
				return str2;
			}
			for (int a = i + 5; str[a] != ')' && a != str.size(); a++) {
				if (str[a] != ' ') {
					if (str[a] == ',') {
						number += '.';
					}
					else {
						if (!isdigit(str[a]) && str[a] != '.') {
							left_par += 1000;
							return str2;
						}
						number += str[a];
					}
				}
				iterator_pos = a;
				if (a == str.size() - 1) {
					left_par += 1000;
					return str2;
				}
			}
			i += (iterator_pos + 1) - i;
			if (stod(number) <= 0) {
				left_par += 1000;
				return str2;
			}
			str2 += std::to_string(sqrt(stod(number)));
		}
		else if ((i <= str.size() - 3) & (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n')) {
			left = "";
			if (i + 8 > str.size() - 1 | (str[i + 3] != '(')) {
				left_par += 1000;
				return str2;
			}
			for (int a = i + 4; str[a] != ')'; a++) {
				if (str[a] != ' ') {
					if (str[a] == ',') {
						left += '.';
					}
					else {
						if (!isdigit(str[a]) && str[a] != '.' && str[a] != '-') {
							left_par += 1000;
							return str2;
						}
						left += str[a];
					}
				}
				iterator_pos = a;
				if (a == str.size() - 1) {
					left_par += 1000;
					return str2;
				}
			}
			if (iterator_pos + 4 > str.size() - 1 | (str[iterator_pos + 2] != '(')) {
				left_par += 1000;
				return str2;
			}
			for (int a = iterator_pos + 3; str[a] != ')'; a++) {
				if (str[a] != ' ') {
					if (str[a] == ',') {
						right += '.';
					}
					else {
						if (str[a] != 'R' && str[a] != 'D') {
							left_par += 1000;
							return str2;
						}
						right = str[a];
					}
				}
				iterator_pos = a;
				if (a == str.size() - 1) {
					left_par += 1000;
					return str2;
				}
			}
			i += (iterator_pos + 1) - i;
			str2 += myMath::sin(stod(left), right);
		}
		else if ((i <= str.size() - 3) & (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's')) {
			left = "";
			if (i + 8 > str.size() - 1 | (str[i + 3] != '(')) {
				left_par += 1000;
				return str2;
			}
			for (int a = i + 4; str[a] != ')'; a++) {
				if (str[a] != ' ') {
					if (str[a] == ',') {
						left += '.';
					}
					else {
						if (!isdigit(str[a]) && str[a] != '.' && str[a] != '-') {
							left_par += 1000;
							return str2;
						}
						left += str[a];
					}
				}
				iterator_pos = a;
				if (a == str.size() - 1) {
					left_par += 1000;
					return str2;
				}
			}
			if (iterator_pos + 4 > str.size() - 1 | (str[iterator_pos + 2] != '(')) {
				left_par += 1000;
				return str2;
			}
			for (int a = iterator_pos + 3; str[a] != ')'; a++) {
				if (str[a] != ' ') {
					if (str[a] == ',') {
						right += '.';
					}
					else {
						if (str[a] != 'R' && str[a] != 'D') {
							left_par += 1000;
							return str2;
						}
						right = str[a];
					}
				}
				iterator_pos = a;
				if (a == str.size() - 1) {
					left_par += 1000;
					return str2;
				}
			}
			i += (iterator_pos + 1) - i;
			str2 += myMath::cos(stod(left), right);
		}
		else if ((i <= str.size() - 3) & (str[i] == 't' && str[i + 1] == 'g')) {
			left = "";
			if (i + 7 > str.size() - 1 | (str[i + 2] != '(')) {
				left_par += 1000;
				return str2;
			}
			for (int a = i + 3; str[a] != ')'; a++) {
				if (str[a] != ' ') {
					if (str[a] == ',') {
						left += '.';
					}
					else {
						if (!isdigit(str[a]) && str[a] != '.' && str[a] != '-') {
							left_par += 1000;
							return str2;
						}
						left += str[a];
					}
				}
				iterator_pos = a;
				if (a == str.size() - 1) {
					left_par += 1000;
					return str2;
				}
			}
			if (iterator_pos + 4 > str.size() - 1 | (str[iterator_pos + 2] != '(')) {
				left_par += 1000;
				return str2;
			}
			for (int a = iterator_pos + 3; str[a] != ')'; a++) {
				if (str[a] != ' ') {
					if (str[a] == ',') {
						right += '.';
					}
					else {
						if (str[a] != 'R' && str[a] != 'D') {
							left_par += 1000;
							return str2;
						}
						right = str[a];
					}
				}
				iterator_pos = a;
				if (a == str.size() - 1) {
					left_par += 1000;
					return str2;
				}
			}
			i += (iterator_pos + 1) - i;
			str2 += std::to_string(myMath::tg(stod(left), right));
		}
		else if ((i <= str.size() - 3) & (str[i] == 'c' && str[i + 1] == 't' && str[i + 2] == 'g')) {
			left = "";
			if (i + 8 > str.size() - 1 | (str[i + 3] != '(')) {
				left_par += 1000;
				return str2;
			}
			for (int a = i + 4; str[a] != ')'; a++) {
				if (str[a] != ' ') {
					if (str[a] == ',') {
						left += '.';
					}
					else {
						if (!isdigit(str[a]) && str[a] != '.' && str[a] != '-') {
							left_par += 1000;
							return str2;
						}
						left += str[a];
					}
				}
				iterator_pos = a;
				if (a == str.size() - 1) {
					left_par += 1000;
					return str2;
				}
			}
			if (iterator_pos + 4 > str.size() - 1 | (str[iterator_pos + 2] != '(')) {
				left_par += 1000;
				return str2;
			}
			for (int a = iterator_pos + 3; str[a] != ')'; a++) {
				if (str[a] != ' ') {
					if (str[a] == ',') {
						right += '.';
					}
					else {
						if (str[a] != 'R' && str[a] != 'D') {
							left_par += 1000;
							return str2;
						}
						right = str[a];
					}
				}
				iterator_pos = a;
				if (a == str.size() - 1) {
					left_par += 1000;
					return str2;
				}
			}
			i += (iterator_pos + 1) - i;
			str2 += std::to_string(myMath::ctg(stod(left), right));
		}
		else if ((i <= str.size() - 3) & (str[i] == 'l' && str[i + 1] == 'o' && str[i + 2] == 'g')) {
			left = "";
			if (i + 8 > str.size() - 1 | (str[i + 3] != '(')) {
				left_par += 1000;
				return str2;
			}
			for (int a = i + 4; str[a] != ')'; a++) {
				if (str[a] != ' ') {
					if (str[a] == ',') {
						left += '.';
					}
					else {
						if (!isdigit(str[a]) && str[a] != '.' && str[a] != '-') {
							left_par += 1000;
							return str2;
						}
						left += str[a];
					}
				}
				iterator_pos = a;
				if (a == str.size() - 1) {
					left_par += 1000;
					return str2;
				}
			}
			if (iterator_pos + 4 > str.size() - 1 | (str[iterator_pos + 2] != '(')) {
				left_par += 1000;
				return str2;
			}
			for (int a = iterator_pos + 3; str[a] != ')'; a++) {
				if (str[a] != ' ') {
					if (str[a] == ',') {
						right_n += '.';
					}
					else {
						if (!isdigit(str[a]) && str[a] != '.' && str[a] != '-') {
							left_par += 1000;
							return str2;
						}
						right_n += str[a];
					}
				}
				iterator_pos = a;
				if (a == str.size() - 1) {
					left_par += 1000;
					return str2;
				}
			}
			i += (iterator_pos + 1) - i;
			if (stod(left) <= 0 || stod(right_n) <= 0 || stod(left) == 1) {
				left_par += 1000;
				return str2;
			}
			str2 += std::to_string(myMath::log(stod(left), stod(right_n)));
		}
		else if ((i <= str.size() - 2) & (str[i] == 'l' && str[i + 1] == 'n')) {
			left = "";
			if (i + 4 > str.size() - 1 | (str[i + 2] != '(')) {
				left_par += 1000;
				return str2;
			}
			for (int a = i + 3; str[a] != ')'; a++) {
				if (str[a] != ' ') {
					if (str[a] == ',') {
						left += '.';
					}
					else {
						if (!isdigit(str[a]) && str[a] != '.' && str[a] != '-') {
							left_par += 1000;
							return str2;
						}
						left += str[a];
					}
				}
				iterator_pos = a;
				if (a == str.size() - 1) {
					left_par += 1000;
					return str2;
				}
			}

			i += (iterator_pos + 1) - i;
			if (stod(left) <= 0) {
				left_par += 1000;
				return str2;
			}
			str2 += std::to_string(std::log(stod(left)));
		}
		else if (str[i] == ',') {
			str2 += '.';
		}
		else if (str[i] == ' ') {
			continue;
		}
		else if (str[i] == '(') {
			left_par++;
			str2 += str[i];
		}
		else if (str[i] == ')') {
			right_par++;
			str2 += str[i];
		}
		else if (isdigit(str[i]) || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
			str2 += str[i];
		}
		else {
			left_par += 1000;
			break;
		}

	}
	return str2;
}

bool isDigit(std::string str) {
	for (int i = 0; i < str.size(); i++) {
		if (!isdigit(str[i]) && str[i] != '-' && str[i] != '.') {
			return false;
		}
	}
	return true;
}

std::string Calculate(std::string str)
{
	int left_par = 0, right_par = 0;
	static std::vector <std::vector <char>>operators; //Масив операторов в уравнении
	static std::vector < std::vector <int>> oper_pos; //Масив позиций операторов
	static int xSize = 0; // Для размера двумерного вектора
	int equels = 0; //Для понимания оператор в скобках или нет
	xSize++;

	if (xSize == 1) {
		str = SymbolicAnalysis(str, left_par, right_par);
		if (left_par != right_par) {
			xSize--;
			return "ERROR";
		}
	}

	if (str[0] == '(' && str[str.size() - 1] == ')' && xSize != 1) {
		str.erase(str.begin());
		str.erase(str.begin() + (str.size() - 1));
	}

	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '(') {
			equels++;
		}
		if (str[i] == ')') {
			equels--;
		}
		if ((equels == 0) && Checking(str, i)) { //Заполнение operators из str
			operators.resize(xSize);
			oper_pos.resize(xSize);
			operators[xSize - 1].push_back(str[i]); // Записываем оператор
			oper_pos[xSize - 1].push_back(i); //Записываем его позицию в str
		}
	}
	if (!operators.empty()) {
		str = PartCalc(xSize, operators, oper_pos, str, '*', '/');
		if (operators.size() == xSize) {
			str = PartCalc(xSize, operators, oper_pos, str, '+', '-');
		}
	}

	xSize--;
	return str;
}

std::string PartCalc(int xSize, std::vector < std::vector<char>>& operators, std::vector < std::vector<int>>& oper_pos, std::string str, char v1, char v2) {
	std::string leftPart = "", rightPart = ""; // Часть до оператора и после
	int x = 0, y = 0;
	for (int a = 0; a < operators[xSize - 1].size(); a++) {
		if (operators[xSize - 1][a] == v1 || operators[xSize - 1][a] == v2) {
			if (a == 0) {
				leftPart = str.substr(0, oper_pos[xSize - 1][a]);

				x = 0;
			}
			else {
				leftPart = str.substr(oper_pos[xSize - 1][a - 1] + 1, oper_pos[xSize - 1][a] - oper_pos[xSize - 1][a - 1] - 1);
				x = oper_pos[xSize - 1][a - 1] + 1;
			}

			if (a == (operators[xSize - 1].size() - 1)) {
				rightPart = str.substr(oper_pos[xSize - 1][a] + 1, str.size());
				y = str.size() - 1;
			}
			else {
				rightPart = str.substr(oper_pos[xSize - 1][a] + 1, oper_pos[xSize - 1][a + 1] - oper_pos[xSize - 1][a] - 1);
				y = oper_pos[xSize - 1][a + 1] - 1;
			}

			if (!isDigit(leftPart)) {
				int left_old = x;
				int lenght = leftPart.size();
				leftPart = Calculate(leftPart);
				operators.resize(xSize);
				oper_pos.resize(xSize);
				operators.shrink_to_fit();
				oper_pos.shrink_to_fit();
				str.replace(left_old, lenght, leftPart);
				x = left_old;
				for (int i = 0; i < operators[xSize - 1].size(); i++) {
					if (oper_pos[xSize - 1][i] >= x + lenght) {
						oper_pos[xSize - 1][i] -= (lenght - rightPart.size() - 1);
					}
				}
				y -= lenght - leftPart.size();
			}
			if (!isDigit(rightPart)) {
				int right_old = oper_pos[xSize - 1][a] + 1;
				int lenght = rightPart.size();
				rightPart = Calculate(rightPart);
				operators.resize(xSize);
				oper_pos.resize(xSize);
				operators.shrink_to_fit();
				oper_pos.shrink_to_fit();
				str.replace(right_old, lenght, rightPart);
				for (int i = 0; i < operators[xSize - 1].size(); i++) {
					if (oper_pos[xSize - 1][i] >= right_old + lenght) {
						oper_pos[xSize - 1][i] -= (lenght - rightPart.size());
					}
				}
				y -= lenght - rightPart.size();
			}
			str = SublineIncut(str, Operating(leftPart, rightPart, operators[xSize - 1][a]), x, y, xSize, operators, oper_pos, a);
			if (operators.size() != xSize) {
				return str;
			}
			a--;
		}
	}
	return str;
}