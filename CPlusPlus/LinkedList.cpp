#include <iostream>
using namespace std;

class Node
{
private:
    int value;
    Node *next;

public:
    Node(int value = 0)
    {
        this->value = value;
        this->next = nullptr;
    }

    int getValue()
    {
        return this->value;
    }

    Node *getNext()
    {
        return this->next;
    }

    void setNext(Node *next)
    {
        this->next = next;
    }
};

class LinkedList
{
private:
    Node *head;

public:
    LinkedList()
    {
        head = nullptr;
    }

    LinkedList(int value)
    {
        head = new Node(value);
    }

    void display()
    {
        Node *i = this->head;
        while (i != nullptr)
        {
            cout << i->getValue() << " ";
            i = i->getNext();
        }
        cout << endl;
    }

    bool push(int value = 0)
    {
        Node *n = new Node(value);
        if (head == nullptr)
        {
            head = n;
        }
        else
        {
            Node *current = head;
            while (current->getNext() != nullptr)
            {
                current = current->getNext();
            }
            current->setNext(n);
        }
        return true;
    }

    Node *headNode()
    {
        return this->head;
    }

    Node *nextNode()
    {
        return (head != nullptr) ? head->getNext() : nullptr;
    }

    Node *pop()
    {
        if (head == nullptr)
            return nullptr;

        Node *temp = head;
        head = head->getNext();
        return temp;
    }

    void addAtHead(int v = 0)
    {
        Node *tmp = new Node(v);
        tmp->setNext(head);
        head = tmp;
    }

    void addAfterValue(int value, int v = 0)
    {
        if (head == nullptr)
        {
            head = new Node(v);
            return;
        }

        Node *i = head;
        while (i != nullptr)
        {
            if (i->getValue() == value)
            {
                Node *newNode = new Node(v);
                newNode->setNext(i->getNext());
                i->setNext(newNode);
                return;
            }
            i = i->getNext();
        }

        // If value not found, add at end
        push(v);
    }
};

int main()
{
    LinkedList list;
    list.addAtHead(5);
    list.push(10);
    list.push(15);
    list.addAfterValue(10, 12);
    list.display();

    return 0;
}