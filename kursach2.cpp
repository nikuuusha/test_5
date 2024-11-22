#include <iostream>
#include <chrono>
#include <time.h>
#include <fstream>
#include <string>
#include <queue>
#include <list>

using namespace std;


// узел бинарного дерева 
struct Tree 
{ // указатели на левое и правое поддеревья
    int key;
    Tree* left;
    Tree* right;
};


// визуализация дерева при выводе на экран
struct Trunk 
{
    Trunk* prev = NULL;
    string str;
    Trunk(Trunk* prev, string& str) : prev(prev), str(str) {}
};

// создает новый узел дерева с заданным значением и возвращает указатель на этот узел
Tree* getFreeTree(int value)
{
    Tree* root = new Tree;
    root->left = root->right = NULL;
    root->key = value;
    return root;
}

//рекурсивно вычисляет размер дерева, возвращая количество узлов в нем 
int sizeOfTree(Tree* root) // размер дерева
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        return (sizeOfTree(root->left) + sizeOfTree(root->right));
    }
}

// вставка нового ключа в дерево с корнем рут( если ключ меньше текущего узла - левое поддерево, больше - правое)
void insert(int currKey, Tree* root)
{
    if (currKey < root->key)
    {
        if (root->left != NULL)
        {
            insert(currKey, root->left);
        }
        else
        {
            root->left = new Tree;
            root->left->key = currKey;
            root->left->left = root->left->right = NULL;
        }
    }
    else if (currKey > root->key)
    {
        if (root->right != NULL)
        {
            insert(currKey, root->right);
        }
        else
        {
            root->right = new Tree;
            root->right->key = currKey;
            root->right->left = root->right->right = NULL;
        }
    }
    else
    {
        return;
    }
}

//считывает данные из файла и строит бинарное дерево на основе этих данных
Tree* readFromF(list<int> treeElems)
{
    Tree* root;
    ifstream database("C:\\Users\\nikab\\OneDrive\\Desktop\\лабы прога\\kursach\\курсач1.txt");
    if (!database.is_open())
    {
        cout << "Ошибка при открытии файла!\n";
        return NULL;
    }
    else
    {
        int value;
        string s;
        int startValue;
        if (getline(database, s))
        {
            startValue = stoi(s);
        }
        else
        {
            cout << "В файле нет данных!\n";
            return NULL;
        }
        root = getFreeTree(startValue);
        treeElems.push_back(startValue);
        while (getline(database, s))
        {
            value = stoi(s);
            insert(value, root);
            treeElems.push_back(value);
        }
    }
    return root;
}

// создание бинарного дерева на выбор пользователя
Tree* createTree(int choice, list<int> treeElems)
{
    Tree* root;
    int n;
    auto clockStart = chrono::high_resolution_clock::now();
    auto clockEnd = chrono::high_resolution_clock::now();
    int startValue;
    int end = 99;
    int start = -99;
    string a;
    bool isEnd = false;
    switch (choice)
    {
    case 1:
        cout << "Введите количество элементов в бинарном дереве\n";
        cin >> n;
        while (n <= 0)
        {
            cout << "Бинарное дерево не может быть создано с количеством элементов менее 1, попробуйте использовать другое число\n";
            cin >> n;
        }
        srand(time(NULL));
        clockStart = chrono::high_resolution_clock::now();
        startValue = rand() % (end - start + 1) + start;
        treeElems.push_back(startValue);
        root = getFreeTree(startValue);
        for (int i = 1; i < n; i++)
        {
            int value = rand() % (end - start + 1) + start;
            insert(value, root);
            treeElems.push_back(value);
        }
        clockEnd = chrono::high_resolution_clock::now();
        cout << "Время, затраченное на создание бинарного дерева: ";
        cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";
        return root;
        break;
    case 2:
        cout << "Введите элементы бинарного дерева:\nВведите ""стоп"", чтобы завершить ввод\n";
        clockStart = chrono::high_resolution_clock::now();
        startValue = 0;
        cin >> a;
        if (a == "стоп")
        {
            isEnd = true;
            cout << "Значения не введены, дерево не может быть сформировано, завершение...\n";
            exit(0);
        }
        else
        {
            startValue = stoi(a);
        }
        root = getFreeTree(startValue);
        treeElems.push_back(startValue);
        n = 1;
        int value;
        while (!isEnd)
        {
            cin >> a;
            if (a == "стоп")
            {
                isEnd = true;
                break;
            }
            else
            {
                value = stoi(a);
            }
            insert(value, root);
            treeElems.push_back(value);
            n++;
        }
        clockEnd = chrono::high_resolution_clock::now();
        cout << "Время, затраченное на создание бинарного дерева: ";
        cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";
        return root;
        break;
    case 3:
        cout << "Создание дерева на основе данных из файла\n";
        clockStart = chrono::high_resolution_clock::now();
        root = readFromF(treeElems);
        clockEnd = chrono::high_resolution_clock::now();
        cout << "Время, затраченное на создание бинарного дерева: ";
        cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";
        return root;
        break;
    default:
        cout << "Выход из программы...\n";
        exit(0);
    }
}

// визуализация уровней дерева при выводе на экран
void showTrunk(Trunk* p, int nodeLvl, ofstream& f2)
{
    if (p == NULL)
    {
        return;
    }
    showTrunk(p->prev, nodeLvl, f2);
    nodeLvl++;
    f2 << p->str;
}

// печатает структуру бинарного дерева на экране. рекурсивно вызывает себя для левого и правого поддеревьев, чтобы визуализировать их структуру
void printTree(Tree* tree, Trunk* prev, bool isRight, ofstream& f2)
{
    if (tree == NULL)
    {
        return;
    }
    string prevStr = "    ";
    Trunk* tmp = new Trunk(prev, prevStr);
    printTree(tree->right, tmp, 1, f2);
    if (!prev)
    {
        tmp->str = "-->";
    }
    else if (isRight)
    {
        tmp->str = ".-->";
        prevStr = "   |";
    }
    else
    {
        tmp->str = "-->";
        prev->str = prevStr;
    }
    int nodeLvl = 0;
    showTrunk(tmp, nodeLvl, f2);
    f2 << tree->key << "\n";
    if (prev)
    {
        prev->str = prevStr;
    }
    tmp->str = "   |";
    printTree(tree->left, tmp, 0, f2);
    delete tmp; // освобождаем память, выделенную под tmp
}

// отрытие файла, считывание, вывод на консоль
void printTreeToConsole(const string& fileName)
{
    ifstream file(fileName);
    if (!file.is_open())
    {
        cout << "Ошибка при открытии файла!\n";
        return;
    }
    string data;
    while (getline(file, data))
    {
        cout << data << '\n';
    }
    file.close();
}

// находит узел с максимальным значением ключа в дереве, начиная с корня рут, рекурсивно спускается вправо, пока не достигнет самого правого узла
Tree* findMaxElem(Tree* root)
{
    if (root->right == NULL)
    {
        return root;
    }
    else
    {
        return findMaxElem(root->right);
    }
}

//удаляет узел с ключом куркей начиная с корня рут 
Tree* deleteNode(int currKey, Tree* root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else
    {
        if (currKey == root->key)
        {
            if ((root->left == NULL) && (root->right == NULL))
            {
                return NULL;
            }
            if (root->left == NULL)
            {
                return root->right;
            }
            if (root->right == NULL)
            {
                return root->left;
            }
            Tree* maxElemInLeft = findMaxElem(root->left);
            root->key = maxElemInLeft->key;
            root->left = deleteNode(maxElemInLeft->key, root->left);
        }

        else if (currKey < root->key)
        {
            root->left = deleteNode(currKey, root->left);
        }
        else
        {
            root->right = deleteNode(currKey, root->right);
        }
        return root;
    }
}

// поиск узла, спускается по дереву, сравнивая ключи узлов
Tree* search(int currKey, Tree* root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else
    {
        if (currKey == root->key)
        {
            return root;
        }
        else if (currKey < root->key)
        {
            return search(currKey, root->left);
        }
        else
        {
            return search(currKey, root->right);
        }
    }
}

// обход дерева
void preOrderTravers(Tree* root)
{
    if (root)
    {
        cout << root->key << " ";
        preOrderTravers(root->left);
        preOrderTravers(root->right);
    }
    else
    {
        return;
    }
}

void postOrderTravers(Tree* root)
{
    if (root)
    {
        postOrderTravers(root->left);
        postOrderTravers(root->right);
        cout << root->key << " ";
    }
}

void levelOrderTravers(Tree* root)
{
    queue<Tree*> q;
    q.push(root);
    while (!q.empty())
    {
        Tree* tree = q.front();
        cout << tree->key << " ";
        q.pop();

        if (tree->left != NULL)
        {
            q.push(tree->left);
        }
        if (tree->right != NULL)
        {
            q.push(tree->right);
        }
    }
}

// рекурсивно освобождает память, удаляя все узлы, начиная с корня рут
void destroyTree(Tree* root)
{
    if (root != NULL)
    {
        destroyTree(root->left);
        destroyTree(root->right);
        delete root;
    }
}

void menu()
{
    ofstream file("C:\\Users\\nikab\\OneDrive\\Desktop\\лабы прога\\kursach\\курсач2.txt");
    cout << "Как вы хотите заполнить дерево?\n1. С помощью случайных чисел\n2. Ввести все элементы в консоль\n3. Получение элементов из файла\n0. Выход\n";
    int choice;
    cin >> choice;
    list<int> treeElems;
    Tree* root = createTree(choice, treeElems); // создание дерева 
    int menuPick;
    int consPick;
    printTree(root, NULL, 0, file);
    cout << "Вы хотите увидеть дерево в консоли?\n0. нет\n1. да\n";
    cin >> consPick;
    if (consPick)
    {
        file.close();
        printTreeToConsole("C:\\Users\\nikab\\OneDrive\\Desktop\\лабы прога\\kursach\\курсач2.txt");
    }
    while (true)
    {
        ofstream file("C:\\Users\\nikab\\OneDrive\\Desktop\\лабы прога\\kursach\\курсач2.txt");
        int prevSize = 0;
        int currSize = 0;
        cout << "1. Вставить элемент в дерево\n2. Удалить элемент из дерева\n3. Получить элемент из дерева\n4. Прямой обход\n5. Обратный обход\n6. Обход в ширину\n0. Выход\n";
        cin >> menuPick;
        int currKey;
        auto clockStart = chrono::high_resolution_clock::now();
        auto clockEnd = chrono::high_resolution_clock::now();
        bool isFind = false;
        switch (menuPick)
        {
        case 1:
            cout << "Введите число, которое вы хотите добавить: ";
            cin >> currKey;
            prevSize = sizeOfTree(root);
            clockStart = chrono::high_resolution_clock::now();
            insert(currKey, root);
            clockEnd = chrono::high_resolution_clock::now();
            currSize = sizeOfTree(root);
            cout << "Время, затраченное на вставку элемента в бинарное дерево: ";
            cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";
            clockStart = chrono::high_resolution_clock::now();
            treeElems.push_back(currKey);
            clockEnd = chrono::high_resolution_clock::now();
            cout << "Время, затраченное на вставку элемента в двусвязный список: ";
            cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";
            printTree(root, NULL, false, file);
            cout << "Вы хотите увидеть дерево в консоли?\n0. нет\n1. да\n";
            cin >> consPick;
            if (consPick)
            {
                file.close();
                printTreeToConsole("C:\\Users\\nikab\\OneDrive\\Desktop\\лабы прога\\kursach\\курсач2.txt");
            }

            break;
        case 2:
            cout << "Введите число, которое хотите удалить:  ";
            cin >> currKey;
            clockStart = chrono::high_resolution_clock::now();
            deleteNode(currKey, root);
            clockEnd = chrono::high_resolution_clock::now();
            cout << "Время, затраченное на удаление элемента из бинарного дерева: ";
            cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";

            clockStart = chrono::high_resolution_clock::now();
            for (auto iter = treeElems.begin(); iter != treeElems.end(); iter++)
            {
                if (*iter == currKey)
                {
                    treeElems.erase(iter);
                    break;
                }
            }
            clockEnd = chrono::high_resolution_clock::now();
            cout << "Время, затраченное на удаление элемента из двусвязного списка: ";
            cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";
            printTree(root, NULL, 0, file);
            cout << "Вы хотите увидеть дерево в консоли?\n0. нет\n1. да\n";
            cin >> consPick;
            if (consPick)
            {
                file.close();
                printTreeToConsole("C:\\Users\\nikab\\OneDrive\\Desktop\\лабы прога\\kursach\\курсач2.txt");
            }
            break;
        case 3:
            cout << "Введите число, которое хотите найти: ";
            cin >> currKey;
            clockStart = chrono::high_resolution_clock::now();
            isFind = search(currKey, root);
            clockEnd = chrono::high_resolution_clock::now();
            cout << "Время, затраченное на поиск элемента бинарного дерева: ";
            cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";

            clockStart = chrono::high_resolution_clock::now();
            for (auto iter = treeElems.begin(); iter != treeElems.end(); iter++)
            {
                if (*iter == currKey)
                {
                    break;
                }
            }
            clockEnd = chrono::high_resolution_clock::now();
            cout << "Время, затраченное на поиск элемента двусвязного списка: ";
            cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";
            if (isFind)
            {
                cout << "\nЧисло найдено\n";
            }
            else
            {
                cout << "\nЧисло не найдено в дереве\n";
            }
            break;
        case 4:
            cout << "Прямой обход: ";
            preOrderTravers(root);
            cout << '\n';
            break;
        case 5:
            cout << "Обратный обход: ";
            postOrderTravers(root);
            cout << '\n';
            break;
        case 6:
            cout << "Обход в ширину: ";
            levelOrderTravers(root);
            cout << '\n';
            break;
        default:
            cout << "Выход из программы...\n";
            destroyTree(root);
            treeElems.clear();
            exit(0);
        }
    }
}

int main()
{
    setlocale(0, "");
    menu();
}
