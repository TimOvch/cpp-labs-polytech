#include "bdd.h"

bool BDD::Node::isEnd(){
    return zero==nullptr && one==nullptr;
}

BDD::Node::Node(const bool &val) : value(val), zero(nullptr), one(nullptr) {}

void BDD::destroyTree(Node *node) {
    if (node) {
        destroyTree(node->zero);
        destroyTree(node->one);
        delete node;
    }
}

bool BDD::getResult(const QString &num){
    Node* searchRes = root;
    QString reNum = num;
    reNum.append(num[0]);
    reNum.removeFirst();
    int numInd = 0;

    while(!searchRes->isEnd()){
        if(reNum[numInd] == QChar('1')){
            searchRes = searchRes->one;
        } else{
            searchRes = searchRes->zero;
        }
        numInd++;
    }

    return searchRes->value;
}

BDD::BDD(){
    root = new Node;

    root->zero = new Node;

    root->zero->zero = new Node(1);
    root->zero->one = new Node;

    root->zero->one->zero = root->zero->zero;
    root->zero->one->one = new Node;

    root->zero->one->one->zero = root->zero->zero;
    root->zero->one->one->one = new Node(0);

    root->one = new Node;

    root->one->zero = root->zero->one;
    root->one->one = new Node;

    root->one->one->one = root->zero->zero;
    root->one->one->zero = root->zero->one->one->one;

}

BDD::~BDD() {
    destroyTree(root);
}
