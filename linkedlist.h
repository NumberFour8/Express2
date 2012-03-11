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
            T& Data;
            ListNode* pNext;
        public:
            ListNode(T& Item) : Data(Item)
            { pNext = NULL; }

            T& data() { return Data; }
            ListNode* next() { return pNext; }
    };

    ListNode* pHead,*pTail;
    int nCount;

public:
    LinkedList()
    {
        pHead = pTail = NULL;
        nCount = 0;
    }

    ~LinkedList()
    {
        for (iterator i = begin();i != end();++i)
           delete &(*i);
    }

    void pushback(T& item)
    {
        ListNode *node = new ListNode(item);
        if (pHead == NULL && pTail == NULL)
          pHead = pTail = node;

        if (pHead != NULL && pTail != NULL){
          pTail->pNext = node;
          pTail = node;
        }


        ++nCount;
    }

    class iterator
    {
        friend class LinkedList;
        protected:
            ListNode* pCurrent;
        public:
            iterator() {}
            T& operator*() { return pCurrent->Data; }

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

        iterator begin() const
        {
            iterator ret;
            ret.pCurrent = pHead;
            return ret;
        }
        iterator end() const
        {
            iterator ret;
            ret.pCurrent = pTail;
            return ret;
        }
};

#endif // LINKEDLIST_H
