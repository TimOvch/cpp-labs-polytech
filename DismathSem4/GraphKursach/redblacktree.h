#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QRegularExpression>
#include <QTextStream>

enum Color { RED, BLACK };

class Node {
public:
    QString key;
    int count;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(QString key) : key(key), count(1), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    void leftRotate(Node* x);
    void rightRotate(Node* y);
    void fixViolation(Node* z);
    void fixDeletion(Node* x);
    Node* successor(Node* x);
    Node* deleteNode(Node* root, QString key);
    void clearHelper(Node* node);
    void inorder(Node* node, QString &result);

public:
    RedBlackTree() : root(nullptr) {}
    ~RedBlackTree() {clear();}

    void insert(QString key);
    void loadFromFile(const QString& filename);

    Node* search(QString key);

    void remove(QString key);
    void clear();

    QString getAllWords();

    Node* getRoot() { return root; }

    int height(Node* node);
    int countNodes(Node* node);
    int countUniqueWords();

    bool isValidRBTree(Node* node, int& blackCount, int currentBlackCount);

};

#endif // REDBLACKTREE_H
