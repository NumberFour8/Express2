#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <assert.h>

// Třída spojového seznamu
template <class T>
class LinkedList
{
private:
    // Prvek v seznamu
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

    // Přidání prvku na konec seznamu
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

    // Vlastní dopředný iterátor
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
            ret.pCurrent = NULL; // Zarážka, poslední prvek musí mít pNext rovno NULL
            return ret;
        }

        // Metoda pro výměnu dvou prvků na daných pozicích
        void swap(const int a,const int b)
        {
            assert(a >= 0 && b >= 0 && max(a,b) < nCount);
            if (a == b) return;

            ListNode* prevA = NULL,*A = NULL,*prevB = NULL,*B = NULL,*t = NULL;
            iterator it = begin();
            for (int i = 0; i <= max(a,b);++i,++it){
               if (i+1 == a)
                 prevA = it.pCurrent;
               if (i == a)
                 A = it.pCurrent;
               if (i+1 == b)
                 prevB = it.pCurrent;
               if (i == b)
                 B = it.pCurrent;
            }

            t = prevA->pNext;
            prevA->pNext = B;
            prevB->pNext = t;

            t = A->pNext;
            A->pNext = B->pNext;
            B->pNext = t;

            if (a == 0) pHead = B;
            else if (b == 0) pHead = A;

        }

        // Počet prvků v seznamu
        int count() const { return nCount; }
};

#endif // LINKEDLIST_H
