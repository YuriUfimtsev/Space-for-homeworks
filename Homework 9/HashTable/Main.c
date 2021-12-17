#include <stdio.h>

#include "HashTable.h"

int main()
{
    HashTable* table = createHashTable(5);
    insertToHashTable("aaa", table);
    insertToHashTable("bbb", table);
    removeElementFromHashTable("bbb", table);
    insertToHashTable("ccc", table);
    insertToHashTable("kkk", table);
    insertToHashTable("lll", table);
    insertToHashTable("mMM", table);
    insertToHashTable("ccc1", table);
    removeElementFromHashTable("ccck", table);
    deleteHashTable(table);
}
