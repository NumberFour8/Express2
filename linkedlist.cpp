#include "linkedlist.h"

template<class T>
LinkedList<T>::LinkedList()
{
    pHead = pTail = NULL;
    nCount = 0;
}

template<class T>
LinkedList<T>::~LinkedList()
{
    for (iterator i = begin();i != end();++i)
       delete &(*i);
}

template<class T>
typename LinkedList<T>::iterator LinkedList<T>::begin() const
{
    iterator ret();
    ret.pCurrent = pHead;
    return ret;
}

template<class T>
typename LinkedList<T>::iterator LinkedList<T>::end() const
{
    iterator ret();
    ret.pCurrent = pTail;
    return ret;
}

template<class T>
void LinkedList<T>::pushback(const T& item)
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
