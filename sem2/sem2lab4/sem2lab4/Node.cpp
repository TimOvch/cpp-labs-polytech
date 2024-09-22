//
//  Node.cpp
//  sem2lab4
//
//  Created by Тимофей Овчинников on 29.02.2024.
//

#include "Node.hpp"

Node::Node()
:m_Data()
{
    pNext = pPrev = nullptr;
}

Node::Node(Node& HT,const Circle& nCir){
    m_Data = nCir;
    if(HT.pPrev==nullptr){
        pPrev = &HT;
        pNext = HT.pNext;
        HT.pNext->pPrev = this;
        HT.pNext = this;
    } else if(HT.pNext == nullptr){
        pNext = &HT;
        pPrev = HT.pPrev;
        HT.pPrev->pNext = this;
        HT.pPrev = this;
    } else{
        pPrev = HT.pPrev;
        pNext = &HT;
        HT.pPrev = this;
        pPrev->pNext = this;
    }
}

Node::Node(Node&& move){
    pPrev = move.pPrev;
    pNext = move.pNext;
    m_Data = move.m_Data;
}

Node& Node::operator =(Node && move){
    pPrev = move.pPrev;
    pNext = move.pNext;
    m_Data = move.m_Data;
    return *this;
}

Node& Node::operator =(Circle const& cir){
    m_Data = cir;
    return *this;
}

Circle Node::getData(){
    return m_Data;
}

Node::operator Circle&(){
    return m_Data;
}

Node::~Node(){
    if(pPrev==nullptr || pNext == nullptr){
        return;
    }
    pPrev->pNext = pNext;
    pNext->pPrev = pPrev;
}

void swapPtr(Node& somenode, Node& other){
    Node *tmpnxt = somenode.pNext, *tmpprev = somenode.pPrev;
    
    somenode.pNext = other.pNext;
    somenode.pPrev = other.pPrev;
    other.pNext = tmpnxt;
    other.pPrev = tmpprev;
}

void swapData(Node& somenode, Node& other){
    Circle tmp = somenode.m_Data;
    somenode.m_Data = other.m_Data;
    other.m_Data = tmp;
}
