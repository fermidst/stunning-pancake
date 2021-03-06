#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>

using vvs = std::vector<std::vector<std::string>>;
using vs = std::vector<std::string>;

auto Symbols = vs {
  "x",
  "y",
  "z",
  "!x",
  "!y",
  "!z"
};

void getTruthTable(int columns, int rows, vvs& array) {
  for (auto i = 0; i < columns; i++) {
    for (auto j = 0; j < rows; j++) {
      if ((j + 1) % (int)std::pow(2, columns - i) <= (int)std::pow(2, columns - i) / 2 &&
        (j + 1) % (int)std::pow(2, columns - i) != 0) {
        array.at(j).at(i) = "0";
      }
      else {
        array.at(j).at(i) = "1";
      }
    }
  }
}

std::string getPDNF(std::string const& funcValues, vvs const& truthTable, int columns) {
  std::string result;
  for (auto i = 0; i < funcValues.size(); i++)
  {
    for (auto j = 0; funcValues.at(i) == '1' && j < columns; j++)
    {
      
      result += truthTable.at(i).at(j) == "0" ? Symbols.at(j + Symbols.size() / 2) : Symbols.at(j);
      if (j == columns - 1) result += " | ";
    }
  }

  return result.empty() ? result : result.substr(0, result.size() - 3);
}

std::string getPCNF(std::string const& funcValues, vvs const& truthTable, int columns) {
  std::string result;
  auto k = 1;
  for (auto i = 0; i < funcValues.size(); i++)
  {
    for (auto j = 0; funcValues.at(i) == '0' && j < columns; j++)
    {
      if (k == 1)
      {
        result += "(";
        k = 0;
      }

      result += truthTable.at(i).at(j) == "1" ? Symbols.at(j + Symbols.size() / 2) : Symbols.at(j);
      if (j == columns - 1)
        result += ") & ";
      else
        result += " | ";
    }
    k = 1;
  }

  return result.empty() ? result : result.substr(0, result.size() - 3);
}

int main() {
  std::string funcVector;
  std::cin >> funcVector;
  
  auto columns = (int)(std::log(funcVector.size()) / std::log(2));
  auto rows = (int)std::pow(2, columns);

  vvs truthTable = vvs(rows, vs(columns));
  getTruthTable(columns, rows, truthTable);

  std::cout << "PDNF: " << getPDNF(funcVector, truthTable, columns) << std::endl;
  std::cout << "PCNF: " << getPCNF(funcVector, truthTable, columns) << std::endl << std::endl;

  // n1 = 17 + 3 = 20; 0d20 = 0b10100;
  std::string n1FuncVector = "00010100";
  std::cout << "n1 (17 + 3) 00010100 PDNF: " << getPDNF(n1FuncVector, truthTable, columns) << std::endl;
  std::cout << "n1 (17 + 3) 00010100 PCNF: " << getPCNF(n1FuncVector, truthTable, columns) << std::endl;

  // n2 = 256 - 20 = 236; 0d236 = 0b11101100;
  std::string n2FuncVector = "11101100";
  std::cout << "n2 (256 - (17 + 3)) 11101100 PDNF: " << getPDNF(n2FuncVector, truthTable, columns) << std::endl;
  std::cout << "n2 (256 - (17 + 3)) 11101100 PCNF: " << getPCNF(n2FuncVector, truthTable, columns) << std::endl;

  std::fstream output("output.txt", std::fstream::out);
  output << "PDNF: " << getPDNF(funcVector, truthTable, columns) << std::endl;
  output << "PCNF: " << getPCNF(funcVector, truthTable, columns) << std::endl << std::endl;

  output << "n1 (17 + 3) 00010100 PDNF: " << getPDNF(n1FuncVector, truthTable, columns) << std::endl;
  output << "n1 (17 + 3) 00010100 PCNF: " << getPCNF(n1FuncVector, truthTable, columns) << std::endl;

  output << "n2 (256 - (17 + 3)) 11101100 PDNF: " << getPDNF(n2FuncVector, truthTable, columns) << std::endl;
  output << "n2 (256 - (17 + 3)) 11101100 PCNF: " << getPCNF(n2FuncVector, truthTable, columns) << std::endl;
}