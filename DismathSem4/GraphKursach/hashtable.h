#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <QList>
#include <QDebug>

size_t hashQString(QString word);
size_t hashQChar(QChar c);
size_t hashInt(int value);

template <typename K, typename V>
class HashTable {
    using HashFunc = size_t(*)(const K);

private:
    struct HashNode {
        K key;
        V value;
        HashNode(const K& k, const V& v) : key(k), value(v) {}
    };

    QList<HashNode>* table;
    size_t capacity;
    size_t size;
    HashFunc hash;

public:
    HashTable(HashFunc hashF,size_t cap = 20) : capacity(cap), size(0) {
        table = new QList<HashNode>[capacity];
        hash = hashF;
    }

    ~HashTable() {
        delete[] table;
    }

    void insert(const K& key, const V& value) {
        size_t index = hash(key) % capacity;
        for (auto& node : table[index]) {
            if (node.key == key) {
                node.value = value;
                return;
            }
        }
        table[index].append(HashNode(key, value));
        size++;
    }


    bool get(const K& key, V& value) const {
        size_t index = hash(key)%capacity;
        for (const auto& node : table[index]) {
            if (node.key == key) {
                value = node.value;
                return true;
            }
        }
        return false;
    }

    void remove(const K& key) {
        size_t index = hash(key)%capacity;
        auto& bucket = table[index];
        for (int i = 0; i < bucket.size(); ++i) {
            if (bucket[i].key == key) {
                bucket.removeAt(i);
                size--;
                return;
            }
        }
    }

    bool contains(const K& key) const {
        V value;
        return get(key, value);
    }

    size_t currentSize() const {
        return size;
    }

    void clear() {
        for (size_t i = 0; i < capacity; ++i) {
            table[i].clear();
        }
        size = 0;
    }

    bool isEmpty() const {
        return size == 0;
    }

    V& operator[](const K& key) {
        size_t index = hash(key) % capacity;
        for (auto& node : table[index]) {
            if (node.key == key) {
                return node.value;
            }
        }
        insert(key, V{});
        return table[index].last().value;
    }

    friend QDebug operator<<(QDebug dbg, const HashTable<K, V>& ht) {
        dbg << "HashTable {";
        for (size_t i = 0; i < ht.capacity; ++i) {
            if (!ht.table[i].isEmpty()) {
                for (const auto& node : ht.table[i]) {
                    dbg << QString("  [%1]: %2").arg(node.key).arg(node.value);
                }
            }
        }
        dbg << "}";
        return dbg;
    }

    class Iterator {
    private:
        HashTable<K,V>& hashTable;
        size_t currentBucket;
        typename QList<HashNode>::iterator currentNode;

        void moveToNext() {
            while (currentBucket < hashTable.capacity) {
                if (currentNode != hashTable.table[currentBucket].end()) {
                    return;
                }
                currentBucket++;
                if (currentBucket < hashTable.capacity) {
                    currentNode = hashTable.table[currentBucket].begin();
                } else {
                    currentNode = {};
                }
            }
        }

    public:
        Iterator(HashTable<K, V>& ht, size_t bucketIndex = 0)
            : hashTable(ht), currentBucket(bucketIndex) {
            if (currentBucket < hashTable.capacity) {
                currentNode = hashTable.table[currentBucket].begin();
                if (currentNode == hashTable.table[currentBucket].end()) {
                    moveToNext();
                }
            } else {
                currentNode = {};
            }
        }

        HashNode& operator*() {
            return *currentNode;
        }

        Iterator& operator++() {
            ++currentNode;
            moveToNext();
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return (currentBucket != other.currentBucket || currentNode != other.currentNode);
        }

        K key(){
            return currentNode->key;
        }

        V value(){
            return currentNode->value;
        }
    };

    Iterator begin() {
        return Iterator(*this);
    }

    Iterator end() {
        return Iterator(*this, capacity);
    }
};
#endif
