//
//  List.hpp
//  sem2lab4
//
//  Created by Тимофей Овчинников on 01.03.2024.
//

#ifndef List_hpp
#define List_hpp

#include <iostream>
#include "Node.hpp"

class iterator_list;

class List{
private:
    Node Head;
    Node Tail;
    size_t m_size;
    
    Node& nodeByIndex(size_t const index);
    
public:
    List();
    ~List();
    // TODO: убрать Node из публичного интерфейса DONE
    // TODO: по ссылке DONE
    void push_front(Circle const& circle);
    void push_back(Circle const& circle);
    bool pop_front();
    bool pop_back();
    iterator_list begin();
    iterator_list end();
    // TODO: вставка по итератору (до переданного итератора) DONE
    void insert(iterator_list it, Circle const& ins);
    iterator_list operator[](size_t const& index);
    bool remove(Circle const& equal);
    unsigned int removeAll(Circle const& equal);
    void makeEmpty();
    void sortByInc();
    void sortByDec();
    
    friend std::ostream& operator<<(std::ostream& stream, List& list);
    friend std::istream& operator>>(std::istream& stream, List& list);
    friend class iterator_list;
};

class iterator_list {
private:
    Node* it;
public:
    iterator_list(Node* ToIt);
    iterator_list(iterator_list const & other);
    const Node* getPointer()const;
    Node& operator*();
    Node* operator->();
    iterator_list& operator++();
    iterator_list operator++(int);
    iterator_list& operator--();
    iterator_list operator--(int);
    iterator_list operator+(size_t n);
    iterator_list operator-(size_t n);
    iterator_list& operator+=(size_t n);
    iterator_list& operator-=(size_t n);
    bool operator==(iterator_list const&other) const;
    bool operator!=(iterator_list const&other) const;
    iterator_list& operator=(Circle const&a);
};

#endif /* List_hpp */
