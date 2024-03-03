//до конца пары набрать в текстовом файле алгебраическое выражение из текста лабораторной работы номер 1 таким 
// образом чтобы каждый операнд и каждая операнция отделялась друг от друга хотябы одним пробелом 
// и постороить за тем программу которая считывает из этого текстового файла это алгебраическое выражение и 
// удаляет из него все незначащие пробелы
//после чего определяет сколько операндов сколько операций и сколько скобок использовано
//  в этом алгебраическом выражении ,вывести полученный результат в тот же текстовый файл 
//добавив соответствующему алгебраическому выражание например опреранды 6 штук скобки 11 штук 
//операции 5 штук.
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>


std::string ReadFile(const std::string& filename);

std::string RemoveSpaces(std::string str);

unsigned __int16 CountChars(std::string str, const std::string& chars);

unsigned __int16 CountOperands(std::string str);

std::map<std::string, unsigned __int16> CountAll(std::string str);

void WriteFile(std::string filename, std::string input_str, unsigned __int16 brackets,
    unsigned __int16 operators, unsigned __int16 operands,
    std::map <std::string, unsigned __int16> symbl_counter, std::string str);


int main() {
    try {
        std::string str = ReadFile("input.txt");
        std::string input_str = str;
        str = RemoveSpaces(str);
        unsigned __int16 brackets = CountChars(str, "(){}[]");
        unsigned __int16 operators = CountChars(str, "+-*/");
        unsigned __int16 operands = CountOperands(str);
        std::map <std::string, unsigned __int16> symbl_counter = CountAll(str);
        std::cout << "Input string: " << input_str << std::endl;
        std::cout << std::endl;
        std::cout << "Brackets: " << brackets << std::endl;
        std::cout << "Operators: " << operators << std::endl;
        std::cout << "Operands: " << operands << std::endl;
        std::cout << std::endl;
        std::for_each(symbl_counter.begin(), symbl_counter.end(),
            [](const std::pair<std::string, unsigned __int16>& pair){
                std::cout << std::setw(4) << pair.first << " : " << pair.second << std::endl;
            });
        std::cout << std::endl;
        std::cout << str;
        WriteFile("input.txt", input_str, brackets, operators, operands, symbl_counter, str);
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
    }
}

std::string ReadFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string result;
        std::getline(file, result);
        return result;
    }
    else {
        throw std::runtime_error("File not find!");
    }
}

std::string RemoveSpaces(std::string str) {
    std::string result;
    while (!str.empty()) {
        if (str[0] != ' ') {
            result += str[0];
        }
        str.erase(0, 1);
    }
    return result;
}


unsigned __int16 CountChars(std::string str, const std::string& chars) {
    unsigned __int16 result = 0;
    while (!str.empty()) {
        if (chars.find(str[0]) != std::string::npos) {
            result++;
        }
        str.erase(0, 1);
    }
    return result;
}


unsigned __int16 CountOperands(std::string str) {
    unsigned __int16 result = 0;
    while (!str.empty()) {
        std::string temp;
        std::size_t pos = str.find_first_of("+-*/(){}[]");
        if (pos == std::string::npos) {
            result++;
            break;
        }
        temp = str.substr(0, pos);
        str.erase(0, pos + 1);
        if (!temp.empty()) {
            result++;
        }
    }
    return result;
}


std::map<std::string, unsigned __int16> CountAll(std::string str) {
    std::map<std::string, unsigned __int16> result;
    while (!str.empty()) {
        std::string temp;
        std::size_t pos = str.find_first_of("+-*/(){}[]");
        if (pos == std::string::npos) {
            result[str]++;
            break;
        }
        temp = str.substr(0, pos);
        if (!temp.empty()) {
            result[temp]++;
            str.erase(0, pos);
        }
        else {
            std::string char_str(1, str[0]);
            result[char_str]++;
            str.erase(0, pos + 1);
        }
    }
    return result;
}

void WriteFile(std::string filename, std::string input_str, unsigned __int16 brackets,
    unsigned __int16 operators, unsigned __int16 operands,
    std::map <std::string, unsigned __int16> symbl_counter, std::string str) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << input_str << std::endl;
        file << std::endl;
        file << "Brackets: " << brackets << std::endl;
        file << "Operators: " << operators << std::endl;
        file << "Operands: " << operands << std::endl;
        file << std::endl;
        std::for_each(symbl_counter.begin(), symbl_counter.end(),
            [&file](const std::pair<std::string, unsigned __int16>& pair) {
                file << std::setw(4) << pair.first << " : " << pair.second << std::endl;
            });
        file << std::endl;
        file << str;
    }
    else {
        throw std::runtime_error("Can't open file!");
    }
}

//домашнее задание добавить к решению по определению сколько используется операндов и скобок добавить какие символы и сколько каждого 
//из этих символов используется в этом выражении
//Замечание!правила хорошего тона в разработке програмного обеспечения требуют чтобы любой текст на языке с++был совершенен то есть 
//замкнут и вполне ограничен что предполагает замкнутость которая заключается в том что любая функция зависит только от параметров этой функции 
//и результат передается через заголовок этой функции запрещается использовать любые глобальные переменные запрещается входить в функцию
//не через заголовок и в функции возврат осуществлется через заголовок и через одно место в самом конце функции должно быть написано return 
//ограниченность означает что функционал должен быть четко определен никаких лишних действий причем эти действия должны быть записаны использую 
//здравый смысл 