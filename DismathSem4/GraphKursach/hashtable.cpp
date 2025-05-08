#include "hashtable.h"

size_t hashQString(QString word) {
    unsigned long long hash = 0;
    int prime = 31;
    for (int i = 0; i < word.length(); ++i) {
        hash = (hash * prime + word[i].unicode());
        hash ^= (hash >> 21);
    }
    return hash;
}

size_t hashQChar(QChar c) {
    unsigned long long hash = static_cast<unsigned long long>(c.unicode());
    unsigned long long prime = 31;

    hash ^= (hash >> 21);
    hash *= prime;
    hash ^= (hash >> 24);

    return static_cast<int>(hash);
}

size_t hashInt(int value) {
    unsigned long long hash = static_cast<unsigned long long>(value);

    hash ^= (hash >> 33);
    hash *= 0xff51afda81b37c29;
    hash ^= (hash >> 33);

    return static_cast<int>(hash);
}
