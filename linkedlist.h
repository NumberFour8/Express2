#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <assert.h>

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
        ListNode* i = pHead,*t = NULL;
        while (i){
            t = i->pNext;
            delete i;
            i = t;
        }
    }

    void pushback(T& item)
    {
        ListNode *node = new ListNode(item);
        if (pHead == NULL)
          pHead = pTail = node;
        else if (pTail != NULL){
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
                assert(pCurrent != NULL);
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
            ret.pCurrent = /*pTail->pNext*/NULL;
            return ret;
        }

        void swap(iterator a,iterator b)
        {
            if (a == b) return;

            ListNode* prevA = NULL,*prevB = NULL,*t = NULL;
            for (iterator i = begin();i != end();++i){
                if (i == a) prevA = t;
                else if (i == b) prevB = t;
                t = i.pCurrent;
            }

            if (prevA != NULL)
              prevA->pNext = b.pCurrent;
            if (prevB != NULL)
              prevB->pNext = a.pCurrent;

            if (a == begin()) pHead = b.pCurrent;
            else if (b == begin()) pHead = a.pCurrent;

            if (a == end()) pTail = b.pCurrent;
            else if (b == end()) pTail = a.pCurrent;

            t = a.pCurrent->pNext;
            a.pCurrent->pNext = b.pCurrent->pNext;
            b.pCurrent->pNext = t;
        }

        int count() const { return nCount; }
};

#endif // LINKEDLIST_H
