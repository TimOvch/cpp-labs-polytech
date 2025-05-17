#include "redblacktree.h"

void RedBlackTree::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left != nullptr) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;

    if (x->right != nullptr) {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == nullptr) {
        root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}

void RedBlackTree::fixViolation(Node* z) {
    while (z->parent != nullptr && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;

            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;

            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RedBlackTree::insert(QString key) {
    key = key.toLower();

    Node* node = new Node(key);
    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (node->key < x->key) {
            x = x->left;
        } else if (node->key > x->key) {
            x = x->right;
        } else {
            x->count++;
            delete node;
            return;
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node;
    } else if (node->key < y->key) {
        y->left = node;
    } else {
        y->right = node;
    }

    fixViolation(node);
}


void RedBlackTree::loadFromFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл:" << filename;
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QRegularExpression re("[А-Яа-яЁё]+");
        QRegularExpressionMatchIterator it = re.globalMatch(line);

        while (it.hasNext()) {
            QString word = it.next().captured(0);
            if (!word.isEmpty()) {
                insert(word);
            }
        }
    }
    qDebug() << "Слова загружены из файла:" << filename;
}


Node* RedBlackTree::search(QString key) {
    Node* current = root;
    while (current != nullptr) {
        if (key == current->key) {
            return current;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return nullptr;
}

void RedBlackTree::inorder(Node* node, QString& result) {
    if (node == nullptr) return;
    inorder(node->left,result);
    result.append(node->key);
    result += " (" + QString::number(node->count) + ") \n";
    inorder(node->right, result);
}

QString RedBlackTree::getAllWords() {
    QString result;

    inorder(root,result);

    return result;
}

int RedBlackTree::height(Node *node) {
    if (node == nullptr) return 0;
    return std::max(height(node->left), height(node->right)) + 1;
}

int RedBlackTree::countNodes(Node *node) {
    if (node == nullptr) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int RedBlackTree::countUniqueWords() {
    return countNodes(root);
}

bool RedBlackTree::isValidRBTree(Node *node, int &blackCount, int currentBlackCount) {
    if (node == nullptr) {
        if (blackCount == -1) {
            blackCount = currentBlackCount;
        } else if (blackCount != currentBlackCount) {
            return false;
        }
        return true;
    }

    if (node->color == RED) {
        if ((node->parent != nullptr && node->parent->color == RED) || node->parent == nullptr) {
            return false;
        }
    }

    if (node->color == BLACK) {
        currentBlackCount++;
    }

    return isValidRBTree(node->left, blackCount, currentBlackCount) &&
           isValidRBTree(node->right, blackCount, currentBlackCount);
}

QString RedBlackTree::getFirstThreeLevels() {
    QString result;
    if (root == nullptr) {
        result = "<p><b>Уровень 0</b>: [NIL, &lt;none&gt;, <span style='color:black;font-weight:bold;'>B</span>, root]</p>";
        return result;
    }

    QQueue<std::tuple<Node*, QString, QString>> queue;
    queue.enqueue({root, "&lt;none&gt;", "root"});
    int currentLevel = 0;
    int nodesAtCurrentLevel = 1;

    while (!queue.isEmpty() && currentLevel < 4) {
        QString levelOutput;
        int nodesAtNextLevel = 0;

        for (int i = 0; i < nodesAtCurrentLevel; ++i) {
            auto [currentNode, parentKey, position] = queue.dequeue();

            if (currentNode == nullptr) {
                levelOutput += QString("[NIL, %1, <span style='color:black;font-weight:bold;'>B</span>, %2] ")
                                   .arg(parentKey)
                                   .arg(position);
                continue;
            }

            QString colorText = (currentNode->color == BLACK)
                                    ? "<span style='color:black;font-weight:bold;'>B</span>"
                                    : "<span style='color:red;font-weight:bold;'>R</span>";

            levelOutput += QString("[%1, %2, %3, %4] ")
                               .arg(currentNode->key.toHtmlEscaped())
                               .arg(parentKey)
                               .arg(colorText)
                               .arg(position);

            if (currentNode->left != nullptr) {
                queue.enqueue({currentNode->left, currentNode->key.toHtmlEscaped(), "L"});
                nodesAtNextLevel++;
            } else {
                queue.enqueue({nullptr, currentNode->key.toHtmlEscaped(), "L"});
                nodesAtNextLevel++;
            }

            if (currentNode->right != nullptr) {
                queue.enqueue({currentNode->right, currentNode->key.toHtmlEscaped(), "R"});
                nodesAtNextLevel++;
            } else {
                queue.enqueue({nullptr, currentNode->key.toHtmlEscaped(), "R"});
                nodesAtNextLevel++;
            }
        }

        result += QString("<p><b>Уровень %1</b>: %2</p>")
                      .arg(currentLevel)
                      .arg(levelOutput.trimmed());
        nodesAtCurrentLevel = nodesAtNextLevel;
        currentLevel++;
    }

    return result;
}



// УДАЛЕНИЕ

Node* RedBlackTree::successor(Node* x) {
    Node* current = x->right;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

void RedBlackTree::fixDeletion(Node* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if ((w->left == nullptr || w->left->color == BLACK) &&
                (w->right == nullptr || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right == nullptr || w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right) w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if ((w->right == nullptr || w->right->color == BLACK) &&
                (w->left == nullptr || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left == nullptr || w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left) w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

Node* RedBlackTree::deleteNode(Node* root, QString key) {
    if (root == nullptr) return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = successor(root);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == nullptr) return root;

    fixDeletion(root);
    return root;
}

void RedBlackTree::clearHelper(Node *node) {
    if (node == nullptr) {
        return;
    }

    clearHelper(node->left);
    clearHelper(node->right);

    delete node;
}

void RedBlackTree::remove(QString key) {
    root = deleteNode(root, key);
}

void RedBlackTree::clear() {
    clearHelper(root);
    root = nullptr;
}
