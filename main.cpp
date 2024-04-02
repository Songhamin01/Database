#include <iostream>
#include "database.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;

Array* makeArray(Array* array)
{
    string array_type;
    int size;
    cout << "value: type (int, double, string, array): ";
    cin >> array_type;
    cout << "size: ";
    cin >> size;


    if (array_type == "int")
    {
        int* arr = new int[size];
        for(int i = 0; i < size; i++)
        {
            int item;
            cout << "item[" << i << "]: ";
            cin >> item;
            *(arr + i) = item;
        }
        cout << endl;
        array->size = size;
        array->type = Type::INT;
        array->items = arr;
    }
    else if (array_type == "double")
    {
        double* arr = new double[size];
        for(int i = 0; i < size; i++)
        {
            double item;
            cout << "item[" << i << "]: ";
            cin >> item;
            *(arr + i) = item;
        }
        cout << endl;
        array->size = size;
        array->type = Type::DOUBLE;
        array->items = arr;
    }
    else if (array_type == "string")
    {
        cin.ignore();
        string* arr = new string[size];
        for(int i = 0; i < size; i++)
        {
            string item;
            cout << "item[" << i << "]: ";
            getline(cin, item);
            *(arr + i) = item;
        }
        cout << endl;
        array->size = size;
        array->type = Type::STRING;
        array->items = arr;
    }
    else if (array_type == "array")
    {
        Array* arr = new Array[size];
        array->size = size;
        array->type = Type::ARRAY;
        for(int i = 0; i < size; i++)
        {
            Array* item = new Array;
            cout << "item[" << i << "]: ";
            item = makeArray(item);
            *(arr + i) = *item;
        }
        array->items = arr;
    }
    return array;
}

// ** 중요 ** 수정해야할 부분
// 이중배열 출력할 때 첫번째 배열의 값이 마지막 배열의 값으로 출력된다
// 첫번째 배열의 값이 제대로 출력되게끔 수정해야함

int main()
{
    Database db;
    init(db);
    int i = 0;

    while(true)
    {
        string answer;
        cout << "command (list, add, get, del, exit): ";
        cin >> answer;

        if (answer == "exit")
        {
            destroy(db);
            break;
        }

        else if (answer == "add")
        {
            Entry* en = new Entry;
            string key, type;
            cout << "key: ";
            cin >> key;

            cout << "type (int, double, string, array): ";
            cin >> type;

            while (true)
            {   
                if (type == "int")
                {
                    int* i_value = new int;
                    cout << "value: ";
                    cin >> *i_value;
                    cout << endl;
                    en = create(Type::INT, key, i_value);
                    break;
                }
                else if (type == "double")
                {
                    double* d_value = new double;
                    cout << "value: ";
                    cin >> *d_value;
                    cout << endl;
                    en = create(Type::DOUBLE, key, d_value);
                    break;
                }
                else if (type == "string")
                {
                    string* s_value = new string;
                    cout << "value: ";
                    cin.ignore();
                    getline(cin, *s_value);
                    cout << endl;
                    en = create(Type::STRING, key, s_value);
                    break;
                }
                else if (type == "array")
                {
                    Array* reArray = new Array;
                    reArray = makeArray(reArray);
                    en = create(Type::ARRAY, key, reArray);
                    break;
                }
                else
                {
                    cout << endl;
                    cout << "Error: no such your command :(" << endl;
                    cout << endl;
                }
            }

            add(db, en);
        }

        else if (answer == "list")
        {
            showAll(db);
            cout << endl;
        }

        else if (answer == "get")
        {
            Entry* getting;
            string whatGet;
            cout << "key: ";
            cin >> whatGet;
            getting = get(db, whatGet);

            while (true)
            {
                if (getting->type == INT)
                {
                    cout << getting->key << ": " << *(int *)getting->value << endl;
                    break;
                }

                else if (getting->type == STRING)
                {
                    cout << getting->key << ": \"" << *(string *)getting->value << "\"" <<  endl;
                    break;
                }
                
                else if (getting->type == DOUBLE)
                {
                    cout << getting->key << ": " << *(double *)getting->value << endl;
                    break;
                }
                
                else if (getting->type == ARRAY)
                {
                    cout << getting->key << ": ";
                    printArray((Array *)getting->value);
                    cout << endl;
                    break;
                }
                else
                {
                    cout << endl;
                    cout << "Error: no such your command :(" << endl;
                    cout << endl;
                }
                cout << endl;
            }
            cout << endl;
        }

        else if (answer == "del")
        {
            string whatDel;
            cout << "key: ";
            cin >> whatDel;
            remove(db, whatDel);
            cout << endl;
        }
        // if (answer != "exit" && answer != "add" && answer != "list" && answer != "get" && answer != "del")
        else
        {
            cout << endl;
            cout << "Error: no such your command :(" << endl;
            cout << endl;
        }
    }
}