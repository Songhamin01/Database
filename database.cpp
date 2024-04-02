#include <string>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

enum Type { INT, DOUBLE, STRING, ARRAY };

struct Array {
  int size;
  Type type;
  void *items;
};

struct Entry {
  Type type;
  std::string key;
  void *value;
};

struct Database {
    int iCount;
    int iMax;
    Entry* dataEntry;
};

void printArray(Array* array);

// 엔트리를 생성한다.
Entry *create(Type type, std::string key, void *value)
{
    Entry* newEntry = new Entry;
    newEntry->type = type;
    newEntry->key = key;
    newEntry->value = value;
    
    // if (type == INT)
    // {
    //     int* intValue = new int(*(int*)value);
    //     newEntry->value = intValue;
    // }
    // else if (type == DOUBLE)
    // {
    //     double* doubleValue = new double(*(double*)value);
    //     newEntry->value = doubleValue;
    // }
    // else if (type == STRING)
    // {
    //     string* stringValue = new string(*(string*)value);
    //     newEntry->value = stringValue;
    // }
    // else if (type == ARRAY)
    // {
    //     Array* arrayValue = new Array(*(Array*)value);
    //     newEntry->value = arrayValue;
    // }

    return newEntry;
}

// 데이터베이스를 초기화한다.
void init(Database &database)
{
    database.iCount = 0;
    database.iMax = 1;
    database.dataEntry = new Entry[database.iMax];
}

// 데이터베이스에 엔트리를 추가한다.
void add(Database &database, Entry *entry)
{
    // 입력받은 key가 중복될 경우 value값만 업데이트
    bool isThere = false;
    for (int i = 0; i < database.iCount; i++)
    {
        if ((database.dataEntry+i)->key == entry->key)
        {
            (database.dataEntry+i)->type = entry->type;
            (database.dataEntry+i)->value = entry->value;
            isThere = true;
            break;
        }
    }

    if (database.iCount >= database.iMax)
    {
        Entry* tempDB = database.dataEntry;
        database.dataEntry = new Entry[database.iMax + 1];
        for (int i = 0; i < database.iCount; i++)
        {   
            *(database.dataEntry + i) = *(tempDB + i);
        }
        delete[] tempDB;
        database.iMax++;
    }

    // 키가 중복되지 않는 경우 메모리에 추가해준다.
    if (!isThere)
    {
        (database.dataEntry+database.iCount)->key = entry->key;
        (database.dataEntry+database.iCount)->type = entry->type;
        (database.dataEntry+database.iCount)->value = entry->value;
        ++database.iCount;
    }

    // 정보 전달을 마친 Entry 제거
    // delete entry;
}

// 데이터베이스에서 키에 해당하는 엔트리를 찾는다.
Entry* get(Database &database, std::string &key)
{
    for (int i = 0; i < database.iCount; i++)
    {
        if ((database.dataEntry + i)->key == key)
        {
            return (database.dataEntry + i);  
        }
    }
    return nullptr;
}

// 데이터베이스에서 키에 해당하는 엔트리를 제거한다.
void remove(Database &database, std::string &key)
{
    Entry* removeDB = database.dataEntry;
    database.dataEntry = new Entry[database.iCount - 1];
    int num = 0;
    for (int i = 0; i < database.iCount; i++)
    {
        if ((removeDB + i)->key == key)
        {
            continue;
        }
        *(database.dataEntry + num) = *(removeDB+i);
        num++;
    }

    if (database.iMax > 1)
        database.iMax--;
    delete[] removeDB;
    database.iCount--;
}

// 데이터베이스를 해제한다.
void destroy(Database &database)
{
    delete[] database.dataEntry;
}

// 데이터베이스의 모든 엔트리를 출력한다.
void showAll(Database &database)
{
    for (int i = 0; i < database.iCount; i++)
    {
        if ((database.dataEntry+i)->type == INT)
            cout << (database.dataEntry+i)->key << ": " << *(int *)(database.dataEntry+i)->value << endl;
        
        else if ((database.dataEntry+i)->type == STRING)
            cout << (database.dataEntry+i)->key << ": \"" << *(string *)(database.dataEntry+i)->value << "\"" <<  endl;

        else if ((database.dataEntry+i)->type == DOUBLE)
            cout << (database.dataEntry+i)->key << ": " << *(double *)(database.dataEntry+i)->value << endl;

        else if ((database.dataEntry+i)->type == ARRAY)
        {
            cout << (database.dataEntry+i)->key << ": " ;
            printArray((Array *)((database.dataEntry+i)->value));
            cout << endl;
        }    
    }
}

// Array를 출력한다.
void printArray(Array* array)
{
    cout << "[";
    if (array->type == INT)
    {
        for (int i = 0; i < (array->size)-1; i++)
        {
            cout << *(int *)((int *)(array->items) + i) << ", ";
        }
        cout << *(int *)((int *)(array->items) + array->size-1);
    }
    if (array->type == DOUBLE)
    {
        for (int i = 0; i < array->size-1; i++)
        {
            cout << *(double *)((double *)(array->items) + i) << ", ";
        }
        cout << *(double *)((double *)(array->items) + array->size-1);
    }
    if (array->type == STRING)
    {
        for (int i = 0; i < array->size-1; i++)
        {
            cout << "\"" << *(string *)((string *)(array->items) + i) << "\"" << ", ";
        }
        cout << "\"" << *(string *)((string *)(array->items) + array->size-1) << "\"";
    }
    if (array->type == ARRAY)
    {
        for (int i = 0; i < array->size-1; i++)
        {
            printArray((Array *)((Array *)(array->items) + i));
            cout << ", ";
        }
        printArray((Array *)((Array *)(array->items) + array->size-1));
    }
    cout << "]";
}