#include "pruferwidget.h"


bool isValidPruferCodeVector(const QVector<int> &code) {
    int length = code.size();
    if (length < 1)
        return false;

    int n = length + 2;

    for (int val : code) {
        if (val < 1 || val > n)
            return false;
    }
    return true;
}
