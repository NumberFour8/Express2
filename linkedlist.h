#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

template <class T>
class LinkedList
{
private:
    class ListNode
    {
        friend class LinkedList;
        private:
            T Data;
            ListNode* pNext;
        public:
            ListNode(const T& Item) { Data = Item; }


            T& data() { return Data; }
            ListNode* next() { return pNext; }
    };

    ListNode* pHead,*pTail;
    int nCount;

public:
    LinkedList();
    ~LinkedList();

    void pushback(const T& item);

    class iterator
    {
        friend class LinkedList;
        protected:
            ListNode* pCurrent;
        public:
            iterator() {}
            T& operator*() { return pCurrent; }

            bool operator==(const iterator& X) const { return pCurrent == X.pCurrent;  }

            bool operator!=(const iterator& X) const { return pCurrent != X.pCurrent;  }

            iterator& operator++()
            {
                pCurrent = pCurrent->next();
                return *this;
            }

            iterator operator++(int)
            {
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }
        };

        iterator begin() const;
        iterator end() const;
};

#endif // LINKEDLIST_H
