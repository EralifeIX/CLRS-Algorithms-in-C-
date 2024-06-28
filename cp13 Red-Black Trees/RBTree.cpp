#include "RBTree.h"
#include<memory>
#include<iostream>


void RBTree::InsertValue(int val) {
    shared_ptr<Node> NewNode = make_shared<Node>();
    NewNode->Data = val;
    NewNode->colour = Colour::Red;
    InsertNode(NewNode);
    FixInsertRBTree(NewNode);
}

void RBTree::InsertNode(shared_ptr<Node> &node) {
    if (this->Root == nullptr) {
        // If the tree is empty, set the new node as the root
        this->Root = node;
        return;
    }

    shared_ptr<Node> current = this->Root;
    shared_ptr<Node> parent = nullptr;

    // Traverse the tree to find the correct position for insertion
    while (current != nullptr) {
        parent = current;
        if (node->Data < current->Data) {
            current = current->Left;
        } else if (node->Data > current->Data) {
            current = current->Right;
        } else {
            // Handle case where node with same value exists (if needed)
            // You might want to decide what to do if a duplicate is found
            // For this example, let's not allow duplicates
            return;
        }
    }

    // Insert node based on comparison with parent
    if (node->Data < parent->Data) {
        parent->Left = node;
    } else {
        parent->Right = node;
    }

    // Set parent of the newly inserted node
    node->Parent = parent;
}


Colour RBTree::GetColour(const shared_ptr<Node>& node) {
    if(node == nullptr)
        return Colour::Black;
    return node->colour;
}

void RBTree::SetColour(shared_ptr<Node>& node, Colour colour) {
    if (node != nullptr) {
        node->colour = colour;
    }
}

void RBTree::RotateLeft(shared_ptr<Node> &node) {
    shared_ptr<Node> RightChild = node->Right;
    node->Right = RightChild->Left;

    if(node->Right != nullptr)
        node->Right->Parent = node;

    RightChild->Parent = node->Parent;

    if(node->Parent.lock() == nullptr)
        this->Root = RightChild;
    else if(node == node->Parent.lock()->Left)
        node->Parent.lock()->Left = RightChild;
    else
        node->Parent.lock()->Right = RightChild;

    RightChild->Left = node;
    node->Parent = RightChild;
}


void RBTree::RotateRight(shared_ptr<Node> &node) {
    shared_ptr<Node> LeftChild = node->Left;
    node->Left = LeftChild->Right;

    if(node->Left != nullptr)
        node->Left->Parent = node;

    LeftChild->Parent = node->Parent;

    if(node->Parent.lock() == nullptr)
        this->Root = LeftChild;
    else if(node == node->Parent.lock()->Left)
        node->Parent.lock()->Left = LeftChild;
    else
        node->Parent.lock()->Right = LeftChild;

    LeftChild->Right = node;
    node->Parent = LeftChild;

}


void RBTree::FixInsertRBTree(shared_ptr<Node> &node) {
    while (node != this->Root && GetColour(node->Parent.lock()) == Colour::Red) {
        auto parent = node->Parent.lock();
        auto grandparent = parent->Parent.lock();

        if (parent == grandparent->Left) {
            auto uncle = grandparent->Right;

            if (GetColour(uncle) == Colour::Red) {
                // Case 1: Uncle is red
                SetColour(parent, Colour::Black);
                SetColour(uncle, Colour::Black);
                SetColour(grandparent, Colour::Red);
                node = grandparent; // Move up to grandparent
            } else {
                // Case 2: Uncle is black and node is a right child
                if (node == parent->Right) {
                    node = parent;
                    RotateLeft(node);
                    // Update parent and grandparent after rotation
                    parent = node->Parent.lock();
                    grandparent = parent->Parent.lock();
                }

                // Case 3: Uncle is black and node is a left child
                SetColour(parent, Colour::Black);
                SetColour(grandparent, Colour::Red);
                RotateRight(grandparent);
            }
        } else {
            // Symmetric cases for right subtree (mirrored)
            auto uncle = grandparent->Left;

            if (GetColour(uncle) == Colour::Red) {
                SetColour(parent, Colour::Black);
                SetColour(uncle, Colour::Black);
                SetColour(grandparent, Colour::Red);
                node = grandparent;
            } else {
                if (node == parent->Left) {
                    node = parent;
                    RotateRight(node);
                    parent = node->Parent.lock();
                    grandparent = parent->Parent.lock();
                }
                SetColour(parent, Colour::Black);
                SetColour(grandparent, Colour::Red);
                RotateLeft(grandparent);
            }
        }
    }

    // Ensure root is black
    SetColour(this->Root, Colour::Black);
}

void RBTree::FixDeleteRBTree(shared_ptr<Node> &node) {
    while (node != this->Root && GetColour(node) == Colour::Black) {
        auto parent = node->Parent.lock();

        if (node == parent->Left) {
            shared_ptr<Node> sibling = parent->Right;

            if (GetColour(sibling) == Colour::Red) {
                // Case 1: Sibling is red
                SetColour(sibling, Colour::Black);
                SetColour(parent, Colour::Red);
                RotateLeft(parent);
                sibling = parent->Right;
            }

            if (GetColour(sibling->Left) == Colour::Black &&
                GetColour(sibling->Right) == Colour::Black) {
                // Case 2: Sibling and its children are black
                SetColour(sibling, Colour::Red);
                node = parent;
            } else {
                if (GetColour(sibling->Right) == Colour::Black) {
                    // Case 3: Sibling's right child is black
                    SetColour(sibling->Left, Colour::Black);
                    SetColour(sibling, Colour::Red);
                    RotateRight(sibling);
                    sibling = parent->Right;
                }

                // Case 4: Sibling's right child is red
                SetColour(sibling, GetColour(parent));
                SetColour(parent, Colour::Black);
                SetColour(sibling->Right, Colour::Black);
                RotateLeft(parent);
                node = this->Root; // Exit loop
            }
        } else {
            // Symmetric cases for right child
            shared_ptr<Node> sibling = parent->Left;

            if (GetColour(sibling) == Colour::Red) {
                // Case 1: Sibling is red
                SetColour(sibling, Colour::Black);
                SetColour(parent, Colour::Red);
                RotateRight(parent);
                sibling = parent->Left;
            }

            if (GetColour(sibling->Right) == Colour::Black &&
                GetColour(sibling->Left) == Colour::Black) {
                // Case 2: Sibling and its children are black
                SetColour(sibling, Colour::Red);
                node = parent;
            } else {
                if (GetColour(sibling->Left) == Colour::Black) {
                    // Case 3: Sibling's left child is black
                    SetColour(sibling->Right, Colour::Black);
                    SetColour(sibling, Colour::Red);
                    RotateLeft(sibling);
                    sibling = parent->Left;
                }

                // Case 4: Sibling's left child is red
                SetColour(sibling, GetColour(parent));
                SetColour(parent, Colour::Black);
                SetColour(sibling->Left, Colour::Black);
                RotateRight(parent);
                node = this->Root; // Exit loop
            }
        }
    }

    SetColour(node, Colour::Black);
}


void RBTree::DeleteNode(int data)
{
    shared_ptr<Node> node = Find(data);
    if(node == nullptr) return;

    shared_ptr<Node> replacement;
    if (node->Left != nullptr && node->Right != nullptr){
        replacement = MinValueNode(node->Right);
       if (node == this->Root) {
            this->Root = replacement;
            this->Root->Parent.lock() = nullptr;
        }
        node.reset();
        node = replacement;
        return;
    }


    replacement = (node->Left != nullptr) ? node->Left : node->Right;
    if(replacement != nullptr)
        replacement->Parent = node->Parent.lock();

    if(node != this->Root){

    shared_ptr<Node> parent = node->Parent.lock();
    if(node == parent->Left)
        parent->Left = replacement;
    else
        parent->Right = replacement;
    if(GetColour(node) == Colour::Black)
        FixDeleteRBTree(replacement);
    }
    else{
        this->Root = replacement;
    }

    node.reset();
}



shared_ptr<Node> RBTree::MinValueNode(shared_ptr<Node> node) {
    while (node->Left != nullptr)
    {
        node = node->Left;
    }
    return node;
}

shared_ptr<Node> RBTree::MaxValueNode(shared_ptr<Node> node)
{
    shared_ptr<Node> current = node;
    while (current && current->Right != nullptr)
    {
        current = current->Right;
    }
    return current;
}

shared_ptr<Node> RBTree::Find(const int data){
    shared_ptr<Node> current = Root;

    while (current != nullptr){
        if (data < current->Data)
            current = current->Left;
        else if (data > current->Data)
            current = current->Right;
        else
            return current;
    }
    return nullptr;
}
