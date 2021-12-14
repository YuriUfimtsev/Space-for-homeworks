#include <stdio.h>

#include "HashTable.h"

int main()
{
    HashTable* table = createHashTable(113);
    insertToHashTable("aaa", table);
    insertToHashTable("bbb", table);
    removeElementFromHashTable("bbb", table);
    deleteHashTable(table);

}
