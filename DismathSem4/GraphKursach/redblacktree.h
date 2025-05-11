#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QRegularExpression>
#include <QTextStream>
#include <QQueue>

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

    QString getFirstThreeLevels() {
        QString result;
        if (root == nullptr) {
            return result;
        }

        QQueue<std::tuple<Node*, QString>> queue;
        queue.enqueue({root, "<none>"});
        int currentLevel = 0;
        int nodesAtCurrentLevel = 1;

        while (!queue.isEmpty() && currentLevel < 4) {
            QString levelOutput;
            int nodesAtNextLevel = 0;

            for (int i = 0; i < nodesAtCurrentLevel; ++i) {
                auto [currentNode, parentKey] = queue.dequeue();
                QString color = currentNode->color ? "B" : "R";

                levelOutput += QString("[%1, %2, %3] ")
                                   .arg(currentNode->key)
                                   .arg(parentKey)
                                   .arg(color);

                if (currentNode->left != nullptr) {
                    queue.enqueue({currentNode->left, currentNode->key});
                    nodesAtNextLevel++;
                }
                if (currentNode->right != nullptr) {
                    queue.enqueue({currentNode->right, currentNode->key});
                    nodesAtNextLevel++;
                }
            }

            // Добавляем вывод текущего уровня в общий результат и увеличиваем счетчик уровня
            result += QString("Уровень %1: %2\n").arg(currentLevel).arg(levelOutput.trimmed());
            nodesAtCurrentLevel = nodesAtNextLevel; // Переходим к следующему уровню
            currentLevel++;
        }

        return result.trimmed();
    }

};

#endif // REDBLACKTREE_H
