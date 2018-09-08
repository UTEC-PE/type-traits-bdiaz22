#ifndef SLIST_H
#define SLIST_H

#include "iterator.h"

template <class T>
class SListIterator : public Iterator<T> {     
    public: 
        SListIterator() : Iterator<T>() {};
        SListIterator(Node<T> *current) : Iterator<T>(current) {};
        SListIterator<T> operator++(){
            this->current = this->current->next;
            return *this;
        }
};

template <typename Tr>
class SList {     
    public:
        typedef typename Tr::T T;
        typedef typename Tr::Operation Operation;
        typedef SListIterator<T> iterator;
      
    private:
        Node<T>* head;
        Operation cmp;
              
    public:
        SList() {
            head = nullptr;
        };

        bool find(T search, Node<T> **&pointer) 
        {
            pointer = &head;
            while((*pointer)->next != NULL)
            {
                if((*pointer)->data == search)
                    return true;

                if(!cmp((*pointer)->data, search))
                    return false;
                
                pointer = &((*pointer)->next);
            }
            return false;
        }
             
        bool insert(T data) {
            Node<T> **temp = &head;  
            if(!head)
            {
                head = new Node<T>(data);
                head->next = NULL;
                return true;
            }
            else if(!find(data,temp))
            {
                Node<T> *created_node = new Node<T>(data);
                if((*temp)->next == NULL)
                {
                    created_node->next = NULL;
                    (*temp)->next = created_node;
                }
                else
                {
                    created_node->next = (*temp)->next;
                    (*temp)->next = created_node;
                }
                return true;
            }          
            return false;
        }
             
        bool remove(T item) {
            Node<T> *current = head;
            Node<T> *temp = head;
            while(!current)
            {
                temp = current->next;
                if(temp->data == item)
                {
                    current->next = temp->next;
                    delete temp;
                    return true;
                }
                current = current->next;    
            }
            return false;
        }  
             
        iterator begin() {
            if(!head)
                throw "Lista Vacia";
            else{                
                SListIterator<T> first(head);
                return first;
            }
        }
             
        iterator end() {
            if(!head)
                throw "Lista Vacia";
            else{
                SListIterator<T> last(NULL);
                return last;
            }
        }
             
        ~SList() {
            if (head) {
                head->killSelf();
            } 
        }         
};

#endif