#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <map>
#include <set>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <windows.h>
#include "Header.h"

int input() {
    using namespace std;
    int method;
    cout << "Способ ввода данных:" << endl;
    cout << "1. Ввод с консоли" << endl;
    cout << "2. Случайные числа" << endl;
    cout << "3. Из файла" << endl;
    cout << "Выбор: ";
    cin >> method;
    return method;
}

// Вспомогательная функция для вывода вектора
void printVector(const std::vector<int>& v, const std::string& title) {
    using namespace std;
    cout << title << ": ";
    for (int val : v) {
        cout << setw(2) << val << " ";
    }
    cout << endl;
}

// Функция для ввода вектора с консоли
void inputVector(std::vector<int>& v, const std::string& name, int size) {
    using namespace std;
    cout << "Введите " << size << " элементов вектора " << name << ": ";
    v.clear();
    for (int i = 0; i < size; i++) {
        int x;
        cin >> x;
        v.push_back(x);
    }
}

// Функция для генерации случайного вектора заданного размера
void randomVector(std::vector<int>& v, int size) {
    v.clear();
    for (int i = 0; i < size; i++) {
        v.push_back(rand() % 100);
    }
}

// Функция для генерации всех векторов
void generateAllVectors(std::vector<int>& V0, std::vector<std::vector<int>>& vectors, int sizeV0, int sizeOthers, int N) {
    using namespace std;
    randomVector(V0, sizeV0);
    vectors.clear();
    for (int i = 0; i < N; i++) {
        vector<int> v;
        randomVector(v, sizeOthers);
        vectors.push_back(v);
    }
}

// Функция для ввода всех векторов
void inputAllVectors(std::vector<int>& V0, std::vector<std::vector<int>>& vectors, int sizeV0, int sizeOthers, int N) {
    using namespace std;
    inputVector(V0, "V0", sizeV0);    
    vectors.clear();
    for (int i = 1; i <= N; i++) {
        vector<int> v;
        inputVector(v, "V" + to_string(i), sizeOthers);
        vectors.push_back(v);
    }
}

// Функция для чтения векторов из файла
bool readVectorsFromFile(std::vector<int>& V0, std::vector<std::vector<int>>& vectors, int& sizeV0, int& sizeOthers, const std::string& filename) {
    using namespace std;
    ifstream file(filename);
    if (!file) {
        cout << "Ошибка открытия файла!" << endl;
        return false;
    }
    int N;
    file >> sizeV0;
    file >> N;
    file >> sizeOthers;
    
    V0.clear();
    for (int i = 0; i < sizeV0; i++) {
        int x;
        file >> x;
        V0.push_back(x);
    }
    vectors.clear();
    for (int i = 0; i < N; i++) {
        vector<int> v;
        for (int j = 0; j < sizeOthers; j++) {
            int x;
            file >> x;
            v.push_back(x);
        }
        vectors.push_back(v);
    }
    
    file.close();
    return true;
}

void STL5Assoc2() {  
    using namespace std;
    cout << "Найти количество векторов VI, содержащих все элементы V0 (без учета повторений)" << endl;
    
    vector<int> V0;
    vector<vector<int>> vectors;
    int N, sizeV0, sizeOthers;
    int method;
    method = input();
    if (method == 1) {
        cout << "\nВведите размер вектора V0: ";
        cin >> sizeV0;
        cout << "Введите размер всех векторов V1..VN: ";
        cin >> sizeOthers;
        cout << "Введите количество векторов N: ";
        cin >> N;
        
        if (sizeV0 > sizeOthers) {
            cout << "Размер V0 (" << sizeV0 
                 << ") больше размера остальных векторов (" << sizeOthers << ")" << endl;
            cout << "Условие задачи нарушено!" << endl;
        }
        
        inputAllVectors(V0, vectors, sizeV0, sizeOthers, N);
        
        cout << "\nВведенные данные:" << endl;
        printVector(V0, "V0");
        for (int i = 0; i < vectors.size(); i++) {
            printVector(vectors[i], "V" + to_string(i + 1));
        }
    }
    else if (method == 2) {
        cout << "\nВведите размер вектора V0: ";
        cin >> sizeV0;
        cout << "Введите размер всех векторов V1..VN: ";
        cin >> sizeOthers;
        cout << "Введите количество векторов N: ";
        cin >> N;
        
        if (sizeV0 > sizeOthers) {
            cout << "\nРазмер V0 (" << sizeV0 
                 << ") больше размера остальных векторов (" << sizeOthers << ")" << endl;
            cout << "Условие задачи нарушено!" << endl;
        }
        
        generateAllVectors(V0, vectors, sizeV0, sizeOthers, N);
        
        cout << "\nСгенерированные данные:" << endl;
        printVector(V0, "V0");
        for (int i = 0; i < vectors.size(); i++) {
            printVector(vectors[i], "V" + to_string(i + 1));
        }
    }
    else if (method == 3) {
        string filename;
        cout << "Введите имя файла для чтения: ";
        cin >> filename;
        if (!readVectorsFromFile(V0, vectors, sizeV0, sizeOthers, filename)) {
            return;
        }
        cout << "\nДанные из файла:" << endl;
        cout << "Размер V0: " << sizeV0 << endl;
        cout << "Размер векторов V1..V" << vectors.size() << ": " << sizeOthers << endl;
        cout << "Количество векторов: " << vectors.size() << endl;
        printVector(V0, "V0");
        for (int i = 0; i < vectors.size(); i++) {
            printVector(vectors[i], "V" + to_string(i + 1));
        }
        
        if (sizeV0 > sizeOthers) {
            cout << "\nВ файле размер V0 (" << sizeV0 
                 << ") больше размера остальных векторов (" << sizeOthers << ")" << endl;
            cout << "Условие задачи нарушено!" << endl;
        }
    }
    else {
        cout << "Неверный выбор!" << endl;
        return;
    }
    set<int> setV0(V0.begin(), V0.end());
    cout << "\nМножетво V0: ";
    for (int val : setV0) {
        cout << val << " ";
    }
    cout << endl;
    
    int count = 0;
    vector<int> indices;

    for (int i = 0; i < vectors.size(); i++) {
        set<int> setVi(vectors[i].begin(), vectors[i].end());
        
        // Проверяем, содержит ли setVi все элементы setV0
        if (includes(setVi.begin(), setVi.end(), setV0.begin(), setV0.end())) {
            count++;
            indices.push_back(i + 1);
        }
    }
    cout << "РЕЗУЛЬТАТ:" << endl;
    cout << "Найдено " << count << " из " << vectors.size() 
         << " векторов, содержащих все элементы V0" << endl;
    
    if (count > 0) {
        cout << "Номера векторов: ";
        for (int idx : indices) {
            cout << idx << " ";
        }
        cout << endl;
    }
}

// функция для вывода вектора
void printStringVector(const std::vector<std::string>& v, const std::string& title) {
    using namespace std;
    cout << title << ": ";
    for (const string& s : v) {
        cout << s << " ";
    }
    cout << endl;
}

// Функция для чтения из файла
bool readWordsFromFile(std::vector<std::string>& words, const std::string& filename) {
    using namespace std;
    ifstream file(filename);
    if (!file) {
        cout << "Ошибка открытия файла!" << endl;
        return false;
    }
    words.clear();
    string word;
    while (file >> word) {
        for (char& c : word) {
            c = toupper(c);
        }
        words.push_back(word);
    }
    file.close();
    return true;
}

void STL5Assoc17() {
    using namespace std;
    cout << "Определить суммарную длину слов, начинающихся с одной и той же буквы" << endl;
    vector<string> V;
    int method;
    int n;
    method = input();
    if (method == 1) {
        cout << "Введите количество слов: ";
        cin >> n;
        cout << "Введите " << n << " слов (будут преобразованы в ЗАГЛАВНЫЕ): ";
        V.clear();
        for (int i = 0; i < n; i++) {
            string word;
            cin >> word;
            for (char& c : word) {
                c = toupper(c);
            }
            V.push_back(word);
        }
        printStringVector(V, "Введенные слова");
    }
    else if (method == 2) {
        cout << "Введите количество слов: ";
        cin >> n;
        V.clear();
        vector<string> words = { "CAT", "DOG", "SUN", "RUN", "JUMP", "BOOK",
            "TREE", "FISH", "BIRD", "CLOUD", "APPLE", "BANANA",
            "CHAIR", "DOOR", "ELEPHANT", "FOREST", "GARDEN", "HOUSE",
            "ISLAND", "JUNGLE", "KANGAROO", "LION", "MOUNTAIN", "NIGHT",
            "OCEAN", "PARROT", "RAINBOW", "SNOW", "TIGER", "UNIVERSE"
        };
        for (int i = 0; i < n; i++) {
            int random_index = rand() % words.size();
            V.push_back(words[random_index]);
        }
        cout << "\nСгенерированные слова:" << endl;
        printStringVector(V, "Слова");
    }
    else if (method == 3) {
        string filename;
        cout << "Введите имя файла для чтения: ";
        cin >> filename;
        if (!readWordsFromFile(V, filename)) {
            return;
        }
        cout << "\nСлова из файла:" << endl;
        printStringVector(V, "Слова");
    }
    map<char, int> M;

    cout << endl;
    for (vector<string>::iterator it = V.begin(); it != V.end(); ++it) {
        if (!it->empty()) {
            char firstChar = (*it)[0];
            M[firstChar] += it->size();
            cout << "  Слово \"" << *it << "\" (длина=" << it->size()
                << ") -> буква '" << firstChar << "', сумма=" << M[firstChar] << endl;
        }
    }

    cout << "\nРЕЗУЛЬТАТЫ:" << endl;
    int totalLength = 0;
    for (map<char, int>::iterator it = M.begin(); it != M.end(); ++it) {
        cout << "Буква '" << it->first << "' -> суммарная длина: " << it->second << endl;
        totalLength += it->second;
    }
}

// Функция для чтения из файла
bool readNumbersFromFile(std::vector<int>& numbers, const std::string& filename) {
    using namespace std;
    ifstream file(filename);
    if (!file) {
        cout << "Ошибка открытия файла!" << endl;
        return false;
    }
    numbers.clear();
    int x;
    while (file >> x) {
        numbers.push_back(x);
    }
    file.close();
    return true;
}

void STL5Assoc21() {
    using namespace std;
    cout << "Группировка элементов по последней цифре с использованием multimap" << endl;
    vector<int> V;
    int method;
    int n;
    method = input();
    if (method == 1) {
        cout << "Введите количество элементов: ";
        cin >> n;
        cout << "Введите " << n << " целых чисел: ";
        V.clear();
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            V.push_back(x);
        }
        printVector(V, "Введенные числа");
    }
    else if (method == 2) {
        cout << "Введите количество элементов: ";
        cin >> n;
        V.clear();
        for (int i = 0; i < n; i++) {
            V.push_back(rand() % 100);
        }
        cout << "\nСгенерированные числа:" << endl;
        printVector(V, "Числа");
    }
    else if (method == 3) {
        string filename;
        cout << "Введите имя файла для чтения: ";
        cin >> filename;
        if (!readNumbersFromFile(V, filename)) {
            return;
        }
        cout << "\nЧисла из файла:" << endl;
        printVector(V, "Числа");
    }
    else {
        cout << "Неверный выбор!" << endl;
        return;
    }

    multimap<int, int> M;

    for (vector<int>::iterator it = V.begin(); it != V.end(); ++it) {
        int lastDigit = *it % 10;
        M.insert(pair<int, int>(lastDigit, *it));
    }

    cout << "\nВсе элементы (ключ: значение):" << endl;
    for (multimap<int, int>::iterator it = M.begin(); it != M.end(); ++it) {
        cout << "  " << it->first << " : " << it->second << endl;
    }

    cout << "\nГруппировка по ключам:" << endl;

    int Key = -1;
    int groupCount = 0;
    for (multimap<int, int>::iterator it = M.begin(); it != M.end(); ++it) {
        if (it->first != Key) {
            if (Key != -1) {
                cout << "  (всего " << groupCount << " элементов)";
            }
            Key = it->first;
            groupCount = 1;
            cout << "\nЦифра " << Key << ": ";
            cout << it->second;
        }
        else {
            groupCount++;
            cout << ", " << it->second;
        }
    }
    if (Key != -1) {
        cout << "  (всего " << groupCount << " элементов)" << endl;
    }
}