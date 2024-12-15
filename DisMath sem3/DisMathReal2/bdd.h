#ifndef BDD_H
#define BDD_H

#include <QString>
#include <QChar>

class BDD {
    class Node {
    public:
        bool value;
        Node* zero;
        Node* one;

        bool isEnd();

        Node(const bool& val = 0);
    };

    void destroyTree(Node* node);

public:
    Node* root;

    bool getResult(const QString& num);

    BDD();

    ~BDD();
};

#endif // BDD_H
