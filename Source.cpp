#include <iostream>
#include <vector>
#include<Windows.h>
#include <list>
#include <cstring>
#include <chrono>

using namespace std;
int _StateMenu;
int choice;

void Menu() {
    cout << "*****************************************************************************"<<endl
        << "*..... /| .... / .. . ./---.... /---/ . /---/ ...# .----..---.---.............*"<<endl
        << "*.... /.| ... / ... ../    ... /   / . /   / .../ .  / .. /  /  / ............*" << endl
        << "*... /__| .. / .... ./ __   . /   / . /.... .../ .  / .. /     / .............*" << endl
        << "*.. /...| . /___ .  /___/  . /___/ . /.... .../ .  / .. /     /...............*" << endl
        <<"*******************************************************************************" << endl
        <<endl
        << "Choose the action : " << endl
        << "(0) Ending a session." << endl
        << "(1) Array_Sort" << endl
        << "(2) Polindrom chek." << endl
        << "(3) Hash Table." << endl
        << "Your choise : ";
    cin >> _StateMenu;

}
// Інтерфейс стратегії
class SortStrategy {
public:
    virtual void sort(std::vector<int>& data) = 0;
};

//patern Strategy
// 
// Конкретна стратегія - Сортування бульбашкою
class BubbleSortStrategy : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        int n = data.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    swap(data[j], data[j + 1]);
                }
            }
        }
    }
};

// Конкретна стратегія - Сортування вибором
class SelectionSortStrategy : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        int n = data.size();
        for (int i = 0; i < n - 1; i++) {
            int min_idx = i;
            for (int j = i + 1; j < n; j++) {
                if (data[j] < data[min_idx]) {
                    min_idx = j;
                }
            }
            std::swap(data[i], data[min_idx]);
        }
    }
};

// Клас контексту
class SortContext {
private:
    SortStrategy* strategy;

public:
    SortContext(SortStrategy* strategy) : strategy(strategy) {}

    void setStrategy(SortStrategy* strategy) {
        this->strategy = strategy;
    }

    void sort(std::vector<int>& data) {
        strategy->sort(data);
    }
};

// Функція для виводу масиву на екран
void printArray(const std::vector<int>& data) {
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}
//patern Strategy
// 
//Перевірка числа на поліндром
class PalindromeChecker {
public:
    PalindromeChecker(int n) {
        num = n;
    }

    bool isPalindrome() {
        int n = num;
        int rev = 0;

        
        do {
            int digit = n % 10;
            rev = (rev * 10) + digit;
            n = n / 10;
        } while (n != 0);

        
        return num == rev;
    }

private:
    int num;
};

/////////////////////////////////////////////////////////////

class HashTable {
private:
    static HashTable* instance;
    const static int hashGroups = 11;
    list<pair<int, string>> table[hashGroups];

    HashTable() {}

public:
    void under_Menu() {
        cout << "Enter your choice: " << endl;
        cout << "1. Insert item in hash table." << endl;
        cout << "2. Insert item in hash table." << endl;
        cout << "3. Remove item from hash-table." << endl;
        cout << "4. Print all hash-table." << endl;
        cout << "5. Search table." << endl;
        cout << "0. Exit." << endl;
        cin >> choice;
    }

    static HashTable* getInstance() {
        if (!instance) {
            instance = new HashTable();
        }
        return instance;
    }

    bool isEmpty() const {
        int sum = 0;
        for (int i = 0; i < hashGroups; i++) {
            sum += table[i].size();
        }
        return sum == 0;
    }

    int hashFunc(int key) {
        return key % hashGroups;
    }

    void insertItem(int key, string value) {
        int hashValue = hashFunc(key);
        auto& cell = table[hashValue];
        auto bItr = begin(cell);
        bool keyExists = false;
        for (; bItr != end(cell); bItr++) {
            if (bItr->first == key) {
                keyExists = true;
                bItr->second = value;
                cout << "[WARNING] Key exists. Value replaced." << endl;
                break;
            }
        }
        if (!keyExists) {
            cell.emplace_back(key, value);
        }
    }

    void removeItem(int key) {
        int hashValue = hashFunc(key);
        auto& cell = table[hashValue];
        auto bItr = begin(cell);
        bool keyExists = false;
        for (; bItr != end(cell); bItr++) {
            if (bItr->first == key) {
                keyExists = true;
                bItr = cell.erase(bItr);
                cout << "[INFO] Item removed." << endl;
                break;
            }
        }
        if (!keyExists) {
            cout << "[WARNING] Key not found. Pair not removed." << endl;
        }
    }

    void printTable() {
        for (int i = 0; i < hashGroups; i++) {
            if (table[i].size() == 0) continue;
            cout << "Hash Group " << i << ":" << endl;
            for (const auto& pair : table[i]) {
                cout << "Key: " << pair.first << ", Value: " << pair.second << endl;
            }
        }
    }

    string searchTable(int key) {
        for (int i = 0; i < hashGroups; i++) {
            if (table[i].size() == 0) continue;
            auto bItr = table[i].begin();
            for (; bItr != table[i].end(); bItr++) {
                if (bItr->first == key) {
                    return bItr->second;
                }
            }
        }
        return "";
    }
};

HashTable* HashTable::instance = nullptr;


/// //////////////////////////////////////////////////////////

int main() {

    Menu();

    switch (_StateMenu) {
    case 1: {
        system("cls");
        vector<int> data;
        int size;

        cout << "Enter array size: ";
        cin >> size;

        int fillChoice;
        cout << "Choose array filling method:\n";
        cout << "1. Manual input\n";
        cout << "2. Random numbers\n";
        cin >> fillChoice;

        switch (fillChoice) {
        case 1: {
            cout << "Enter arr element:\n";
            for (int i = 0; i < size; ++i) {
                int num;
                cin >> num;
                data.push_back(num);
            }
            break;
        }
        case 2: {
            srand(time(0));
            for (int i = 0; i < size; ++i) {
                int num = rand();
                data.push_back(num);
            }
            break;
        }
        }
        SortContext context(nullptr);

        int choice;
        cout << "Chose sorting algorithm:\n";
        cout << "1. Buble sort\n";
        cout << "2. Selection sort\n";
        cin >> choice;

        auto start = chrono::high_resolution_clock::now();

        switch (choice) {
        case 1: {
            context.setStrategy(new BubbleSortStrategy());
            break;
        }
        case 2: {
            context.setStrategy(new SelectionSortStrategy());
            break;
        }
        default: {
            std::cout << "Incorrect algorithm method.\n";
            return 0;
        }
        }

        context.sort(data);

        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

        cout << "Sorted array: ";
        printArray(data);

        cout << "Execution time: " << duration.count() << " microseconds" << endl;

        system("pause");
        system("cls");
        Menu();
        break;
    }

    case 2: {
        system("cls");

        int num;
        cout << "Enter the number: ";
        cin >> num;

        PalindromeChecker pc(num);

        auto start = chrono::high_resolution_clock::now();

        if (pc.isPalindrome()) {
            cout << num << " is a palindrome.";
        }
        else {
            cout << num << " is not a palindrome.\n";
        }

        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

        cout << "Execution time: " << duration.count() << " microseconds" << endl;

        system("pause");
        system("cls");
        Menu();
        break;
    }
    case 3: {
        system("cls");
        HashTable* ht = HashTable::getInstance();

        ht->under_Menu();

        int key;
        string value;
        switch (choice) {
        case 1: {
            system("cls");
            cout << "Enter key and value to insert: " << endl;
            cin >> key >> value;
            ht->insertItem(key, value);
            system("pause");
            system("cls");
            ht->under_Menu();
            break;
        }
        }
        system("pause");
        system("cls");
        Menu();
        break;
    }
    default:
        cout << "Invalid choice" << endl;
        break;
    }

    return 0;
}
