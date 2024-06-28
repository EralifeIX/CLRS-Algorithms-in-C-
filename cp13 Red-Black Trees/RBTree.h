#pragma once
#include<memory>

using namespace std;

#ifndef CLRSC___RBTREE_H
#define CLRSC___RBTREE_H

enum class Colour{
    Red,
    Black,
    DoubleBlack
};

struct Node{
    int Data;
    Colour colour;
    shared_ptr<Node> Left = nullptr;
    shared_ptr<Node> Right = nullptr;
    weak_ptr<Node> Parent;
};


class RBTree {
public:
    shared_ptr<Node> Root = nullptr;

    void RotateLeft(shared_ptr<Node>& node);
    void RotateRight(shared_ptr<Node>& node);
    void FixInsertRBTree(shared_ptr<Node>& node);
    void FixDeleteRBTree(shared_ptr<Node>& node);
    void InsertValue(int val);
    void InsertNode(shared_ptr<Node>& node);
    void DeleteNode(const int data);
    void Transplant(shared_ptr<Node> u, shared_ptr<Node> v);
    shared_ptr<Node> MinValueNode(shared_ptr<Node> node);
    shared_ptr<Node> MaxValueNode(shared_ptr<Node> node);
    shared_ptr<Node> Find(const int data);

    void SetColour(shared_ptr<Node>& node, Colour colour);
    Colour GetColour(const shared_ptr<Node>& node);

    bool DelCase1(shared_ptr<Node>& node);
    void DelCase2(shared_ptr<Node>& node);
    bool DelCase3(shared_ptr<Node>& parent,shared_ptr<Node>& pointer );
    bool DelCase4(shared_ptr<Node>& parent,shared_ptr<Node>& pointer );

};


#endif //CLRSC___RBTREE_H
