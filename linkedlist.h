#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <class T>
class LinkedList
{
private:
    class ListNode{
    public:
        ListNode(const T& Data)
        {
            pData = new T();
            memcpy(pData,&Data,sizeof(T));
        }
        ~ListNode()
        {
            delete pData;
        }

        T& data() { return *pData; }
        ListNode* next() { return pNext; }
    private:
        T* pData;
        ListNode* pNext;
    };

    ListNode* pHead,*pTail;
    int nCount;

public:
    LinkedList();
    ~LinkedList();

    void pushback(const T& item);

    class iterator {
        protected:
            ListNode* pCurrent;
        public:
            iterator() {}
            T& operator*(){ return pCurrent; }

            bool operator==(const iterator& X) const
            {
                return pCurrent == X.pCurrent;
            }

            bool operator!=(const iterator& X) const
            {
                return pCurrent != X.pCurrent;
            }

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
};

#endif // LINKEDLIST_H
