//! Copyright [2022] <Leonardo G de M Brito>
#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>

namespace structures {

template<typename T>
class LinkedStack {
 public:
    LinkedStack();

    ~LinkedStack();

    void clear();  // limpa pilha

    void push(const T& data);  // empilha

    T pop();  // desempilha

    T& top() const;  // dado no topo

    bool empty() const;  // pilha vazia

    std::size_t size() const;  // tamanho da pilha

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: info
            return data_;
        }

        const T& data() const {  // getter-constante: info
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter-constante: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* top_{nullptr};  // nodo-topo
    std::size_t size_{0u};  // tamanho
};

}  // namespace structures

template<typename T>
structures::LinkedStack<T>::LinkedStack() {
    top_ = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}

template<typename T>
void structures::LinkedStack<T>::clear() {
    while (!empty()) {
        pop();
    }
}

template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node* New_Node = new Node(data, nullptr);

    if (empty()) {
        top_ = New_Node;
    } else {
        New_Node -> next(top_);
        top_ = New_Node;
    }
    size_++;
}

template<typename T>
T structures::LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Pilha Vazia");
    }

    Node* pointer = top_;
    T pointer_val = top_ -> data();
    top_ = top_ -> next();
    delete pointer;
    size_--;
    return pointer_val;
}

template<typename T>
T& structures::LinkedStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Pilha Vazia");
    }
    return top_ -> data();
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}

#endif
