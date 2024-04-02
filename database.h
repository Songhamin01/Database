#ifndef DATABASE_H
#define DATABASE_H

#include <string>

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

// 엔트리를 생성한다.
Entry *create(Type type, std::string key, void *value);

// 데이터베이스를 초기화한다.
void init(Database &database);

// 데이터베이스에 엔트리를 추가한다.
void add(Database &database, Entry *entry);

// 데이터베이스의 메모리를 추가(동적할당)한다.
void newDB(Database &database);

// 데이터베이스에서 키에 해당하는 엔트리를 찾는다.
Entry* get(Database &database, std::string &key);

// 데이터베이스에서 키에 해당하는 엔트리를 제거한다.
void remove(Database &database, std::string &key);

// 데이터베이스를 해제한다.
void destroy(Database &database);

// 데이터베이스의 모든 엔트리를 출력한다.
void showAll(Database &database);

// Array를 출력한다.
void printArray(Array* array);

#endif