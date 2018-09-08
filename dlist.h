#ifndef DLIST_H
#define DLIST_H

#include "iterator.h"
#include <stdexcept>

template <typename T>
class DListIterator : public Iterator<T> {     
    public: 
        DListIterator() : Iterator<T>() {};
        DListIterator(Node<T> *current) : Iterator<T>(current) {};
        DListIterator<T> operator++()
        {
            this->current = this->current->next;
            return *this;
        }
        DListIterator<T> operator--()
        {
            this->current = this->current->prev;
            return *this;
        }
};

template <typename Tr>
class DList {     
    public:
        typedef typename Tr::T T;
        typedef DListIterator<T> iterator;
      
    private:
        Node<T>* head;
        Node<T>* tail;
              
    public:
        DList() {
            head = tail = nullptr;
        };

        void push_front(T data) {            
            if(!head)
            {
                head = new Node<T>(data);
                head->data = data;
                head->next = NULL;
                head->prev = NULL;
                tail = head;
            }
            else
            {
                Node<T> *temp= new Node<T>(data);
                temp->next = head;
                temp->prev = NULL;
                head->prev = temp;
                head = temp;
            }
        }

        void push_back(T data) {
            if(!head)
            {
                tail = new Node<T>;
                tail->data = data;
                tail->next = NULL;
                tail->prev = NULL;
                head = tail;
            }
            else
            {
                Node<T> *temp= new Node<T>(data);
                temp->next = NULL;
                temp->prev = tail;
                tail->next = temp;
                tail = temp;
            }

        }
             
        void pop_front() {
            if(!head)
                throw "Lista vacia"; 
            else if(head == tail)
                tail = NULL;

            Node<T> *temp = head;
            head = head->next;
        
            if(head != NULL)
                head->prev = NULL;
        
            delete temp;

        }
             
        void pop_back() {
            Node<T> *temp = tail;
            if(!head)
                throw "Lista vacia"; 
            else if(head == tail)
                head = NULL;
                       
            tail = tail->prev;
            
            if(tail != NULL)
                tail->next = NULL;
            
            delete temp;
        }
             
        iterator begin() {
            if(!head)
                throw "Lista Vacia";
            else{
                DListIterator<T> first(head);
                return first;  
            }  
        }
             
        iterator end() {
            if(!head)
                throw "Lista Vacia";
            else{            
                DListIterator<T> last(tail);
                return last;
            }
        }
             
        ~DList() {
            if (head) {
                head->killSelf();
            } 
        }         
};

#endif