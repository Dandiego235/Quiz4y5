#include "Node.h"
#include "event.h"
#include <iostream>

#ifndef LIST

#define LIST 1

using namespace std;

// 2. ajustar a que esta lista sea doblemente enlazada, cambia el add, find, insert y el remove
template <class T>
class List
{
private:
    Node<T> *first;
    Node<T> *last;
    int quantity;
    bool empty;
    Node<T> *searchPosition;

public:
    List()
    {
        first = NULL;
        last = NULL;
        searchPosition = NULL;
        quantity = 0;
        empty = true;
    }

    void add(T *pData) // Función que inserta un nodo al final.
    {
        Node<T> *newNode = new Node<T>(pData); // crea el nuevo nodo

        if (quantity > 0) // si la lista no está vacía
        {
            this->last->setNext(newNode); // pone el nuevo nodo al final
            newNode->setPrev(last); // pone el apuntador al anterior, que es el final
        }
        else
        {
            this->first = newNode; // Si está vacía, first es newNode. Ambos punteros apuntan a NULL.
        }
        this->last = newNode; // last es newNode.

        empty = false;
        quantity++;
    }

    Node<T> *getFirst()
    {
        return this->first;
    }

    int getSize()
    {
        return quantity;
    }

    bool isEmpty()
    {
        return !quantity;
    }

    T* find(int pPosition)
    {
        T *result = NULL; // puntero al contenido del nodo
        searchPosition = this->first; // Se pone el puntero buscador en el inicio

        if (pPosition < getSize()) // si la posición es menor que el tamaño.
        {
            while (pPosition > 0) // mientras la posición no sea 0
            {
                searchPosition = searchPosition->getNext(); // Corre el puntero al siguiente
                pPosition--; // decrementa la posición
            }
            result = searchPosition->getData();
            // Cuando está en la posición dada, retorna la estructura que contiene el nodo.
        }
        return result;
        // Si la posición no existe, queda nulo.
    }

    
    void insert(int pPosition, T *pData)
    {
        // Si el position es mayor a la cantidad, entonces inserto al final
        if (pPosition < getSize() && first != NULL)
        {
            Node<T> *newNodo = new Node<T>(pData); // Nuevo nodo con el valor dado.

            find(pPosition); // Se coloca el buscador en la posición deseada, no nos interesa lo que retorna.

            newNodo->setNext(searchPosition);
            // Se pone el siguiente del nuevo nodo como el nodo en la posición
            newNodo->setPrev(searchPosition->getPrev());
            // Se pone el anterior del nuevo nodo como el nodo anterior del nodo en la posición
            if (searchPosition->getPrev() != NULL) // Si el anterior del nodo en la posición no es nulo, o sea, si no es el primer nodo.
            {
                searchPosition->getPrev()->setNext(newNodo);
                // Se pone el siguiente del nodo anterior al nodo de la posición, como el nodo nuevo.
            }
            else
            {
                this->first = newNodo; // si es el primer nodo, se establece que el primer nodo es el nuevo nodo.
                // el puntero al anterior queda apuntando a nulo.
            }
            searchPosition->setPrev(newNodo); // Se pone que el nodo anterior del nodo en la posición es el nuevo nodo.
            quantity++;
        }
        else
        {
            add(pData);
            // Si la posición dada es mayor o igual que la cantidad de nodos, se agrega al final.
        }
    }

    bool remove(int pPosition)
    {
        bool result = false; // resultado de si se eliminó o no
        if (first != NULL && pPosition < getSize())
        {
            find(pPosition); // Se posiciona el puntero searchPosition en la posición dada.
            if (pPosition != 0) // Si no es el primer elemento
            {
                searchPosition->getPrev()->setNext(searchPosition->getNext());
                // Se pone que el nodo siguiente del nodo anterior a la posición es el siguiente del nodo en la posición
                // Nos "saltamos" al nodo original

                if (searchPosition != last) // Si la posición no es el último nodo.
                {
                    searchPosition->getNext()->setPrev(searchPosition->getPrev());
                    // si no es el último, se pone que el anterior del nodo siguiente a la posición, es el anterior del nodo en la posición a borrar.
                    // Desconectamos el nodo de sus vecinos.
                }
                else
                {
                    last = searchPosition->getPrev(); // Si es el último, el nuevo last es el anterior del nodo en la posicíon.

                }
            }
            else
            {
                first = first->getNext();
                // si es el primer elemento, se pone que el nuevo primer elemento es el siguiente del nodo en la posición.
                searchPosition->setNext(NULL);
                // se desconecta el nodo del siguiente elemento.
            }
            delete searchPosition; // se borra el nodo en la posición.
            quantity--;
            result = true;
        }
        return result;
    }
};

#endif