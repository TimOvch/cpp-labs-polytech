 #ifndef ABSTRACTGRAPH_H
#define ABSTRACTGRAPH_H

#include "matrix.h"

class AbstractGraph
{
protected:
    int p,q;
    Matrix adjacency;

public:
    AbstractGraph(const int& vershini);
    virtual ~AbstractGraph() {}

    void saveToFile(const QString& fileName) const;
    void loadFromFile(const QString& fileName);

    class AbstractGraphExeption : public std::exception {
    private:
        std::string text;

    public:

        AbstractGraphExeption(const std::string& error);

        const char* what() const noexcept override;

        virtual ~AbstractGraphExeption() override {}
    };

};

#endif // ABSTRACTGRAPH_H
