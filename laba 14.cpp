#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <Windows.h>
#include "Header.h"

int main() {
    using namespace std;
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand(time(0));
    int choice;
    do {
        cout << "\n    ВЫБОР ЗАДАНИЯ \n";
        cout << "1. STL5Assoc2: Найти количество векторов, содержащих все элементы V0\n";
        cout << "2. STL5Assoc17: Группировка слов по первой букве с суммированием длин\n";
        cout << "3. STL5Assoc21: Группировка чисел по последней цифре\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Ошибка ввода! \n";
            continue;
        }

        switch (choice) {
        case 1:
            STL5Assoc2();
            break;
        case 2:
            STL5Assoc17();
            break;
        case 3:
            STL5Assoc21();
            break;
        case 0:
            cout << "Программа завершена." << endl;
            break;
        default:
            cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);

    return 0;
}