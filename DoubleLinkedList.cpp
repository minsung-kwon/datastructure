#pragma once

#include <iostream>

template <typename T>
struct DllNode
{
    T* Data;
    DllNode* Next;
    DllNode* Prev;

    ~DllNode()
    {
        delete Data;
    }
};

template <typename T>
class Dll
{
public:
    using Node = DllNode<T>;
    using NodePtr = Node*;

private:
    NodePtr Head;
    size_t n;

public:
    Dll()
        : Head(new Node{ nullptr, nullptr, nullptr }), n(0)
    {
        Head->Next = Head;
        Head->Prev = Head;
    }

    size_t size() const
    {
        return n;
    }

    void insert(const T& Value)
    {
        NodePtr NewNode = new Node{ new T(Value), nullptr, nullptr };
        NodePtr Tail = Head->Prev;

        NewNode->Next = Head;
        NewNode->Prev = Tail;

        Tail->Next = NewNode;
        Head->Prev = NewNode;

        Head = NewNode;
        n++;
    }

    void erase(const T& Value)
    {
        if (n == 0) return;

        NodePtr Current = Head;

        do {
            if (*(Current->Data) == Value)
            {
                Current->Prev->Next = Current->Next;
                Current->Next->Prev = Current->Prev;

                if (Current == Head)
                {
                    Head = Current->Next;
                }

                delete Current;
                n--;
                return;
            }
            Current = Current->Next;
        } while (Current != Head);
    }

    class DllIter
    {
    private:
        NodePtr Ptr;
        NodePtr Head;

    public:
        DllIter(NodePtr p, NodePtr head)
            : Ptr(p), Head(head) {}

        T& operator* ()
        {
            return *(Ptr->Data);
        }

        NodePtr get()
        {
            return Ptr;
        }

        DllIter& operator++()
        {
            Ptr = Ptr->Next;
            if (Ptr == Head)
                Ptr = nullptr;
            return *this;
        }

        DllIter operator++(int)
        {
            DllIter It = *this;
            ++(*this);
            return It;
        }

        friend bool operator==(const DllIter& It1, const DllIter& It2)
        {
            return It1.Ptr == It2.Ptr;
        }

        friend bool operator!=(const DllIter& It1, const DllIter& It2)
        {
            return It1.Ptr != It2.Ptr;
        }
    };

    DllIter begin()
    {
        return DllIter{ Head , Head };
    }

    DllIter end()
    {
        return DllIter{ nullptr, Head };
    }

    Dll(const Dll<T>& Other)
        : Dll()
    {
        for (auto It = Other.begin(); It != Other.end(); ++It)
        {
            insert(*It);
        }
    }

    Dll(const std::initializer_list<T>& Il)
        : Dll()
    {
        for (const T& i : Il)
        {
            insert(i);
        }
    }

    ~Dll()
    {
        while (size())
        {
            erase(*(Head->Data));
        }
        delete Head;
    }
};

int main()
{
    Dll<int> DoubleLinkedList;
    for (int i = 0; i < 10; i++)
    {
        DoubleLinkedList.insert(i);
    }

    for (auto& li : DoubleLinkedList)
    {
        std::cout << li << ' ';
    }
    std::cout << "\n";

    DoubleLinkedList.erase(0);
    std::cout << "Size: " << DoubleLinkedList.size() << '\n';
    std::cout << "First Element: " << *(DoubleLinkedList.begin()) << '\n';

    return 0;
}
