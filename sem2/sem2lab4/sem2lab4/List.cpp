#include "List.hpp"
#include <iostream>



Node& List::nodeByIndex(size_t const index){
    auto temp = begin();
    return *(temp+=index);
}

List::List(){
    m_size = 0;
    Head.pNext = &Tail;
    Tail.pPrev = &Head;
}

List::~List(){
    makeEmpty();
}

void List::push_front(Circle const& circle){
    new Node(Head, circle);
    m_size++;
}

void List::push_back(Circle const& circle){
    new Node(Tail, circle);
    m_size++;
}

bool List::pop_front(){
    if(Head.pNext!=&Tail){
        delete Head.pNext;
        return true;
    }
    return false;
}

bool List::pop_back(){
    if(Tail.pPrev!=&Head){
        delete Tail.pPrev;
        return true;
    }
    
    return false;
}

iterator_list List::begin(){
    return iterator_list{Head.pNext};
}

iterator_list List::end(){
    return iterator_list{&Tail};
}

iterator_list List::operator[](size_t const & index){
        return begin()+index;
}

void List::insert(iterator_list it, Circle const& ins){
    new Node(*it, ins);
}

bool List::remove(Circle const& equal){
    auto it = begin();
    auto itend = end();
    while(it!=itend){
        if(it->m_Data == equal){
            delete it.getPointer();
            return true;
        }
        ++it;
    }
    m_size--;
    return false;
}

// TODO: сделать O(N), а не O(N*M), где M - кол-во элементов для удаления DONE
unsigned int List::removeAll(Circle const& equal){
    unsigned int i = 0;
    auto it = begin();
    auto itend = end();
    while(it!=itend){
        if(it->m_Data == equal){
            delete it.getPointer();
            m_size--;
            i++;
        }
        ++it;
    }
    return i;
}

void List::makeEmpty(){
    while(pop_back()){}
}

void List::sortByInc(){
    for (auto i = begin(); i != end(); ++i) {
        for (auto j = begin(); j != end() - 1; ++j) {
            if (((*j).getData()).getSquare() > ((*(j + 1)).getData()).getSquare()) {
                swapData(*j, *(j + 1));
            }
        }
    }
}

void List::sortByDec(){
    for (auto i = end(); i != begin()-1; --i) {
        for (auto j = end(); j != begin(); --j) {
            if (((*j).getData()).GetRadius() > ((*(j - 1)).getData()).GetRadius()) {
                swapData(*j, *(j - 1));
            }
        }
    }
}

std::ostream& operator<<(std::ostream& stream, List& list){
    auto it = list.begin();
    auto end = list.end();
    
    while(it!=end){
        stream<<(*it).getData() << '\n';
        ++it;
    }
    return stream;
}


std::istream& operator>>(std::istream& stream, List& list){
    Circle getter;
    
    while(stream >> getter){
        list.push_back(getter);
    }
    
    return stream;
}


iterator_list::iterator_list(Node* ToIt){
    it = ToIt;
}

iterator_list::iterator_list(iterator_list const & other){
    it = other.it;
    
}

const Node* iterator_list::getPointer() const{
    return it;
}

Node& iterator_list::operator*(){
    return *it;
}

Node* iterator_list::operator->(){
    return it;
}

iterator_list& iterator_list::operator++(){
    it=it->pNext;
    return *this;
}

iterator_list iterator_list::operator++(int){
    iterator_list old(it);
    it = it->pNext;
    return  old;
}

iterator_list& iterator_list::operator--(){
    it = it->pPrev;
    return *this;
}

iterator_list iterator_list::operator--(int){
    iterator_list old(it);
    it = it->pPrev;
    return old;
}

iterator_list iterator_list::operator+(size_t n){
    iterator_list result(it);
    for(size_t i = 0; i < n; i++){
        ++result;
    }
    return result;
}

iterator_list iterator_list::operator-(size_t n){
    iterator_list result(it);
    for(size_t i = 0; i < n; i++){
        --result;
    }
    return result;
}

iterator_list& iterator_list::operator+=(size_t n){
    *this = *this+n;
    return *this;
}

iterator_list& iterator_list::operator-=(size_t n){
    *this = *this - n;
    return *this;
}

bool iterator_list::operator==(iterator_list const&other) const{
    return it==other.it;
}

bool iterator_list::operator!=(iterator_list const&other) const{
    return it!=other.it;
}

iterator_list& iterator_list::operator=(Circle const&a){
    it->m_Data = a;
    return *this;
}
