#include <iostream>
#include "string.h"
using namespace std;

struct Node //Звено дерева
{
    char* word;
    char* translation; //слово и перевод
    int pos[2];
    Node *l, *r; //Это указатели на новые звенья
};


class Dict
{
private:

    Node *root;
    int compare(char* word, char* element)
    {
        int min,i=0,result=100;
        if (strlen(word)>strlen(element)) min = strlen(element);
        else min = strlen(word);
        while(result==100)
        {
            if(word[i]>element[i]) result = 1;
            if(word[i]<element[i]) result = -1;
            if(i<min) i++;
            else
            {
                if(min == strlen(word) && min == strlen(element)) result = 0;
                else {
                    if (min == strlen(word)) result = -1;
                    if (min == strlen(element)) result = 1;
                }
            }
        }
        return result;
    }
    int counter = 0;
    int f = 0,p = 0;
public:
    Dict()
    {
        root = NULL;
    };
    Node *& getRoot()
    {
        return root;
    }



    void show(Node *&Tree) //Функция обхода
    {
        if (Tree != NULL) //Пока не встретится пустое звено
        {
            show(Tree->l); //Рекурсивная функция для вывода левого поддерева
            cout << Tree->word << '\t' << Tree->translation<<"\n"; //Отображаем корень дерева
            show(Tree->r); //Рекурсивная функци для вывода правого поддерева
        }
    }

/*Добавили очистку памяти*/
    void del(Node *&Tree)
    {

        if (Tree != NULL) //Пока не встретится пустое звено
        {
            del(Tree->l); //Рекурсивная функция прохода по левому поддереву
            del(Tree->r); //Рекурсивная функци для прохода по правому поддереву
            delete Tree; //Убиваем конечный элемент дерева
            Tree = NULL; //Может и не обязательно, но плохого не будет
        }

    }

    void add_node(char* x, char* translation, Node *&Tree) //Фукция добавления звена в дерево
    {
        if (NULL == Tree)  //То, о чем я в самом начале писал. Если дерева нет, то ложим семечко
        {
            Tree = new Node; //Выделяем память под звено дерева
            Tree->word = x; //Записываем данные в звено
            Tree->translation = translation;
            Tree->l = Tree->r = NULL; //Подзвенья инициализируем пустотой во избежание ошибок
        } else {
            if (compare(x, Tree->word) == -1)   //Если нововведенный элемент x меньше чем элемент x из семечка дерева, уходим влево
            {
                if (Tree->l != NULL)
                    add_node(x, translation, Tree->l); //При помощи рекурсии заталкиваем элемент на свободный участок
                else //Если элемент получил свой участок, то
                {
                    Tree->l = new Node;  //Выделяем память левому подзвену. Именно подзвену, а не просто звену
                    Tree->l->l = Tree->l->r = NULL; //У левого подзвена будут свои левое и правое подзвенья, инициализируем их пустотой
                    Tree->l->word = x; //Записываем в левое подзвено записываемый элемент
                    Tree->l->translation = translation;
                }
            }

            if (compare(x, Tree->word) == 1)   //Если нововведенный элемент x больше чем элемент x из семечка дерева, уходим вправо
            {
                if (Tree->r != NULL)
                    add_node(x, translation, Tree->r); //При помощи рекурсии заталкиваем элемент на свободный участок
                else //Если элемент получил свой участок, то
                {
                    Tree->r = new Node;  //Выделяем память правому подзвену. Именно подзвену, а не просто звену
                    Tree->r->l = Tree->r->r = NULL; //У правого подзвена будут свои левое и правое подзвенья, инициализируем их пустотой
                    Tree->r->word = x; //Записываем в правое подзвено записываемый элемент
                    Tree->r->translation = translation;
                }
            }
            if (compare(x, Tree->word) == 0) cout << "Такой элемент уже есть\n";
        }
    }

    void search(char* word, Node *&Tree)
    {
        if(NULL == Tree) cout << "Словарь пуст!";
        else if(compare(word,Tree->word)==0) cout << Tree->translation;
        else if (compare(word, Tree->word) == -1)
            if (Tree->l != NULL) search(word, Tree->l);
            else cout << "Слово не найдено!";
        else if (compare(word, Tree->word) == 1)
            if (Tree->r != NULL) search(word, Tree->r);
            else cout << "Слово не найдено!";
    }
    int floorCount(Node *&Tree) {


        if (NULL != Tree)
            if (Tree->l != NULL || Tree->r != NULL)
                counter++;
            if (Tree->l != NULL) {
                floorCount(Tree->l);
            }
            if (Tree->r != NULL) {
                floorCount(Tree->r);
            }
        return counter;
    }
    Node *& getFirstLeft(Node *&Tree) {
        if (Tree != NULL)
            if (Tree->l != NULL)
                return getFirstLeft(Tree->l);
            else if (Tree->r != NULL)
                return getFirstLeft(Tree->r);
                else Tree = NULL;
    }
};
class Menu
{
private:
    void title()
    {
        cout << "\n---------------------------\n";
        cout << "Англо-Русский словарь.\n\n";
    }
    void ending()
    {
        cout << "\n\n";
        cout << "9. Вернуться в меню.\n";
        cout << "0. Выход.\n";
        cout << "Введите цифру действия: ";
    }
public:
    char* word;
    char* translation;
    int choosing;
    Menu(){};
    void mainPage()
    {
        title();
        cout << "1. Посмотреть содержимое словаря.\n";
        cout << "2. Добавить новое слово.\n";
        cout << "3. Найти перевод слова.\n";
        cout << "4. Удалить словарь.\n\n";
        cout << "0. Выход.\n";
        cout << "Введите цифру действия: ";
    }
    void page1()
    {
        title();
    }
    void page1_end()
    {
        ending();
    }
    void page2_1()
    {
        title();
        cout << "Введите слово на английском: ";
    }
    void page2_2()
    {
        cout << "\nВведите его перевод на русском: ";
    }
    void page2_end()
    {
        cout << "\nСлово успешно добавлено!";
        ending();
    }
    void page3_1()
    {
        title();
        cout << "Введите слово на английском которое хотите найти: ";
    }
    void page3_2()
    {
        cout << "\nПеревод вашего слова: ";
    }
    void page3_end()
    {
        ending();
    }
    void page4()
    {
        title();
        cout << "Словарь успешно удалён!";
        ending();
    }
    void error()
    {
        cout << "Ошибка!\nВведите один из вариантов: ";
    }
};
int main()
{
    Dict dict;
    Menu menu;

    int choosing = -1;

    const int n = 5;
    char* memory[n][2] = {{"hello","привет"},{"apple","яблоко"},{"chair","стул"},{"car","окно"},{"bread","хлеб"}};


    for(int i=0;i<n;i++) dict.add_node(memory[i][0],memory[i][1],dict.getRoot());

    cout << "Element count: "<< dict.floorCount(dict.getRoot()) <<"\n\n";
    cout << "First :" <<dict.getFirstLeft(dict.getRoot())->word<<"\n\n";
    do
    {
        char* word;
        char* translation;
        menu.mainPage();
        cin >> choosing;
        switch(choosing)
        {
            case 1:
            {
                menu.page1();
                dict.show(dict.getRoot());
                menu.page1_end();
                cin >> choosing;
                while (choosing != 9 && choosing != 0) {
                    menu.error();
                    cin >> choosing;
                }
                break;
            }
            case 2:
            {
                menu.page2_1();
                cin >> word;
                menu.page2_2();
                cin >> translation;
                dict.add_node(word,translation,dict.getRoot());
                menu.page2_end();
                cin >> choosing;
                while (choosing != 9 && choosing != 0) {
                    menu.error();
                    cin >> choosing;
                }
                break;
            }
            case 3:
            {
                menu.page3_1();
                cin >> word;
                menu.page3_2();
                dict.search(word,dict.getRoot());
                menu.page3_end();
                cin >> choosing;
                while (choosing != 9 && choosing != 0) {
                    menu.error();
                    cin >> choosing;
                }
                break;
            }
            case 4:
            {
                menu.page4();
                dict.del(dict.getRoot());
                cin >> choosing;
                while (choosing != 9 && choosing != 0) {
                    menu.error();
                    cin >> choosing;
                }
                break;
            }
            default:
                break;
        }

    }while(choosing!=0);
}