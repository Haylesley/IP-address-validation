#include <iostream>
#include <string>
#include <sstream>

bool is_valid_octet(const std::string& octet) {
    // Проверка длины
    if (octet.length() == 0 || octet.length() > 3) return false;

    // Проверка на наличие ведущих нулей
    if (octet.length() > 1 && octet[0] == '0') return false;

    // Проверка, что все символы - цифры
    for (char c : octet) {
        if (c < '0' || c > '9') return false;
    }

    // Преобразование в число и проверка диапазона
    int num = std::stoi(octet); // stoi (string to integer)
    return num >= 0 && num <= 255;
}

std::string get_address_part(const std::string& ip, int part) {
    std::stringstream ss(ip);
    std::string octet;
    int currentPart = 0;

    while (std::getline(ss, octet, '.')) {
        if (currentPart == part) {
            return octet; // Возвращаем нужный октет
        }
        currentPart++;
    }
    return ""; // Если не найдено, возвращаем пустую строку
}

bool is_valid_ip(const std::string& ip) {
    // Проверяем, что IP-адрес содержит 3 точки
    int dotCount = 0;
    for (char c : ip) {
        if (c == '.') dotCount++;
    }
    if (dotCount != 3) return false;

    // Проверяем каждый октет
    for (int i = 0; i < 4; ++i) {
        std::string octet = get_address_part(ip, i);
        if (!is_valid_octet(octet) || octet.empty()) {
            return false; // Если октет некорректен, возвращаем false
        }
    }
    return true;
}

int main() {
    std::string ip;
    std::cout << "Enter the IP address: ";
    std::cin >> ip;

    if (is_valid_ip(ip)) {
        std::cout << "Valid" << std::endl;
    } else {
        std::cout << "Invalid" << std::endl;
    }
    return 0;
}
