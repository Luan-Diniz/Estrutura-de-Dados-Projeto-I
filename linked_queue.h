//! Copyright [2022] <Leonardo G de M Brito>
#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>

namespace structures {


template<typename T>
class LinkedQueue {
 public:
    LinkedQueue();

    ~LinkedQueue();

    void clear();  // limpar

    void enqueue(const T& data);  // enfilerar

    T dequeue();  // desenfilerar

    T& front() const;  // primeiro dado

    T& back() const;  // último dado

    bool empty() const;  // fila vazia

    std::size_t size() const;  // tamanho

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* head{nullptr};  // nodo-cabeça
    Node* tail{nullptr};  // nodo-fim
    std::size_t size_{0u};  // tamanho
};

}  // namespace structures

#endif

template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template<typename T>
void structures::LinkedQueue<T>::clear() {
    while (!empty()) {
        dequeue();
    }
}

template<typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
    Node* New_Node = new Node(data, nullptr);

    if (empty()) {
        head = New_Node;
        tail = New_Node;
    } else if (size() == 1) {
        head -> next(New_Node);
        tail = New_Node;
    } else {
        tail -> next(New_Node);
        tail = New_Node;
    }
    size_++;
}

template<typename T>
T structures::LinkedQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("Fila Vazia");
    }

    Node* pointer = head;
    T pointer_val = pointer -> data();
    head = head -> next();

    delete pointer;
    size_--;
    return pointer_val;
}

template<typename T>
T& structures::LinkedQueue<T>::front() const {
    if (empty()) {
        throw std::out_of_range("Fila Vazia");
    }
    return head -> data();
}

template<typename T>
T& structures::LinkedQueue<T>::back() const {
    if (empty()) {
        throw std::out_of_range("Fila Vazia");
    }
    return tail -> data();
}



template<typename T>
bool structures::LinkedQueue<T>::empty() const {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
std::size_t structures::LinkedQueue<T>::size() const {
    return size_;
}
