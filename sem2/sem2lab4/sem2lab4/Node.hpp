//
//  Node.hpp
//  sem2lab4
//
//  Created by Тимофей Овчинников on 29.02.2024.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include "Circle.hpp"

class Node{
private:
    Node* pPrev;
    Node* pNext;
    Circle m_Data;
public:
    Node();
    Node(Node& HT,const Circle& nCir);
    Node(Node const &nd);
    Node(Node&& move);
    Node& operator =(Node && move);
    Node& operator =(Circle const& cir);
    operator Circle&();
    ~Node();
    
    Circle getData();
    
    friend void swapPtr(Node& somenode, Node& other);
    friend void swapData(Node& somenode, Node& other);
    friend class List;
    friend class iterator_list;
};

#endif /* Node_hpp */
