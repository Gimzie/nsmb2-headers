#pragma once

#include "sead.h"

template <typename T>
class LineNodeMgr
{
public:
    struct Node
    {
        Node(T* obj_)
            : obj(obj_)
            , next(nullptr)
            , prev(nullptr)
        {}

        T* obj;
        Node* next;
        Node* prev;
    };

    size_assert(Node, 0xC);

public:
    LineNodeMgr()
        : mpHead(nullptr)
        , mpTail(nullptr)
    {}

    Node* front() const
    {
        return mpHead;
    }

    Node* back() const
    {
        return mpTail;
    }

    bool contains(const Node* node) const
    {
        if (node == nullptr)
            return false;

        return node->next != nullptr || node->prev != nullptr || node == mpHead;
    }

    void insertAfter(Node* node, Node* basis)
    {
        if (basis == nullptr)
        {
            pushFront(node);
            return;
        }

        if (node == nullptr)
            return;

        node->next = basis->next;
        node->prev = basis;
        basis->next = node;

        if (node->next != nullptr)
            node->next->prev = node;

        if (node->next == nullptr)
            mpTail = node;
    }

    void erase(Node* node)
    {
        if (node == nullptr)
            return;

        if (node->prev != nullptr)
            node->prev->next = node->next;

        else if (node == mpHead)
            mpHead = node->next;

        if (node->next != nullptr)
            node->next->prev = node->prev;

        else if (node == mpTail)
            mpTail = node->prev;

        node->next = nullptr;
        node->prev = nullptr;
    }

    void pushBack(Node* node)
    {
        if (node == nullptr)
            return;

        if (mpTail != nullptr)
        {
            mpTail->next = node;
            node->prev = mpTail;
        }
        else
        {
            mpHead = node;
        }

        mpTail = node;
    }

    void pushFront(Node* node)
    {
        if (node == nullptr)
            return;

        if (mpHead != nullptr)
        {
            mpHead->prev = node;
            node->next = mpHead;
        }
        else
        {
            mpTail = node;
        }

        mpHead = node;
    }

    void clear()
    {
        while (mpHead != nullptr)
            erase(mpHead);
    }

protected:
    Node* mpHead;
    Node* mpTail;
};

size_assert(LineNodeMgr<void>, 0x8);
