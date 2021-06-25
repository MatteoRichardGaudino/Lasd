#include <iostream>
#include <algorithm>

namespace lasd {

/* ************************************************************************** */

/* *****************************Constructors******************************* */

    // With size
    template<typename Data>
    Vector<Data>::Vector(const unsigned long newSize){
        elements = new Data[newSize]{};
        size = newSize;
    }

    // Copy from LinearContainer
    template<typename Data>
    Vector<Data>::Vector(const LinearContainer<Data>& linearContainer){
        elements = new Data[linearContainer.Size()];
        size = linearContainer.Size();
        for (unsigned long i = 0; i < size; i++){
            elements[i] = linearContainer[i];
        }
    }

    // Copy from Vector
    template<typename Data>
    Vector<Data>::Vector(Vector<Data>& vector){
        elements = new Data[vector.size];
        size = vector.size;
        for (unsigned long i = 0; i < size; i++){
            elements[i] = vector.elements[i];
        }
    }

    // Move
    template<typename Data>
    Vector<Data>::Vector(Vector<Data>&& vector) noexcept{
        std::swap(elements, vector.elements);
        std::swap(size, vector.size);
    }

    //Destructor
    template<typename Data>
    Vector<Data>::~Vector(){
        delete[] elements;
    }

/* ***********************Operators**************************************** */
    // = operator
    template<typename Data>
    Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vector){
        delete[] elements;
        elements = new Data[vector.size];
        size = vector.size;
        for (unsigned long i = 0; i < size; i++){
            elements[i] = vector[i];
        }
        return *this;
    }

    // move operator
    template<typename Data>
    Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vector) noexcept{
        std::swap(elements, vector.elements);
        std::swap(size, vector.size);
        return *this;
    }

    // Comparison operators
    template<typename Data>
    bool Vector<Data>::operator==(const Vector<Data>& vector) const noexcept{
        if (size == vector.size){
            bool equal = true;
            unsigned long i = 0;
            while (equal && i < size){
                if ((*this)[i] != vector[i]){
                    equal = false;
                }
                i++;
            }
            return equal;
        } else return false;
        
    }
    template<typename Data>
    bool Vector<Data>::operator!=(const Vector<Data>& vector) const noexcept{
        return !((*this) == vector);
    }
/* ************************************************************************ */

    template<typename Data>
    void Vector<Data>::Resize(unsigned long newSize){
        if (newSize == 0){
            Clear();
        } else if(newSize != size) {
            Data* tmp = new Data[newSize]{};
            unsigned long min = (size<=newSize)? size : newSize;

            for (unsigned long i = 0; i < min; i++){
                std::swap(tmp[i], elements[i]);
            }
            std::swap(tmp, elements);
            size = newSize;
            delete[] tmp;
        }
    }

    template<typename Data>
    void Vector<Data>::Clear(){
        size = 0;
        delete[] elements;
        elements = nullptr;
    }

    template<typename Data>
    Data& Vector<Data>::Front() const{
        if (size != 0){
            return elements[0];
        } else{
            throw std::length_error("Vector is empty");
        }
    }

    template<typename Data>
    Data& Vector<Data>::Back() const{
        if (size != 0){
            return elements[size-1];
        } else{
            throw std::length_error("Vector is empty");
        }
    }

    template<typename Data>
    Data& Vector<Data>::operator[](const unsigned long i) const{
        if (i < size){
            return elements[i];
        } else{
            throw std::out_of_range("Vector size (" + std::to_string(size) + "), Input_index [" + std::to_string(i) + "]");
        }
    }

// Specific member functions (inherited from MappableContainer)

    template<typename Data>
    void Vector<Data>::MapPreOrder(const MapFunctor fun, void* v){
        for (unsigned long i = 0; i < size; i++){
            fun(elements[i], v);
        }
        
    }
    template<typename Data>
    void Vector<Data>::MapPostOrder(const MapFunctor fun, void* v){
        for (unsigned long i = size; i > 0; i--) {
            fun(elements[i-1], v);
        }
    }
// Specific member functions (inherited from FoldableContainer)
    template<typename Data>
    void Vector<Data>::FoldPreOrder(const FoldFunctor fun, const void* v1, void* v2) const {
        for (unsigned long i = 0; i < size; i++){
            fun(elements[i], v1, v2);
        }
        
    }
    template<typename Data>
    void Vector<Data>::FoldPostOrder(const FoldFunctor fun, const void* v1, void* v2) const {
        for (unsigned long i = size; i > 0; i--) {
            fun(elements[i-1], v1, v2);
        }
    }


    template<typename Data>
    void Vector<Data>::Shuffle() {
        std::random_shuffle(elements, elements+size);
    }

    template<typename Data>
    unsigned long Vector<Data>::Partition(unsigned long l, unsigned long r){
        if (l < r){
            Data& x = elements[l];
            unsigned long i = l;
            unsigned long j = r;
            while (i < j){
                while (i < j && elements[i] < x) i++;
                while (i < j && elements[j] >= x) j--;
                if (i < j) std::swap(elements[i], elements[j]);
            }
            return j;
        }
    }
    template<typename Data>
    void Vector<Data>::QuickSort(unsigned long l, unsigned long r){
        if (l < r){
            unsigned long j = Partition(l, r);
            QuickSort(l, j);
            QuickSort(j+1, r);
        }
    }
    template<typename Data>
    void Vector<Data>::QuickSort(){
        if(size != 0)
            QuickSort(0, size-1);
    }

    template<typename Data>
    void Vector<Data>::MergeSort(){
        if(size != 0) {
            aux = new Data[size];
            MergeSort(0, size - 1);
            delete[] aux;
        }
    }
    template<typename Data>
    void Vector<Data>::Merge(unsigned long l, unsigned long m, unsigned long r){
        unsigned long i = l;
        unsigned long j = m+1;

        for (unsigned long k = l; k <= r; ++k) {
            aux[k] = elements[k];
        }

        for(unsigned long k = l; k <= r; ++k){
            if (i > m)               elements[k] = aux[j++];
            else if(j > r)           elements[k] = aux[i++];
            else if(aux[i] < aux[j]) elements[k] = aux[i++];
            else                     elements[k] = aux[j++];
        }
    }

    template<typename Data>
    void Vector<Data>::MergeSort(unsigned long l, unsigned long r){
        if(l < r){
            unsigned long m = (l + r)/2;
            MergeSort(l, m);
            MergeSort(m+1, r);
            Merge(l, m, r);
        }
    }

    template<typename Data>
    void Vector<Data>::HeapSort(){
        if (size != 0) {
            BuildHeap();
            unsigned long s = size;
            for (unsigned long i = size - 1; i > 0; i--) {
                std::swap(elements[0], elements[i]);
                s--;
                Heapify(0, s);
            }
        }
    }

    template<typename Data>
    void Vector<Data>::BuildHeap() {
        for (unsigned long i = size/2; i > 0; --i) {
            Heapify(i, size);
        }
        Heapify(0, size);
    }

    template<typename Data>
    void Vector<Data>::Heapify(unsigned long root, unsigned long siz) {
        unsigned long max = root;
        unsigned long sx = 2*root+1;
        unsigned long dx = 2*root+2;
        if (sx < siz && elements[sx] > elements[max]) max = sx;
        if (dx < siz && elements[dx] > elements[max]) max = dx;

        if (max != root){
            std::swap(elements[max], elements[root]);
            Heapify(max, siz);
        }
    }

    template<typename Data>
    void Vector<Data>::SelectionSort(){
        for (unsigned long i = 0; i < size; ++i) {
            unsigned long min = findMin(i, size);
            if (i != min)
                std::swap(elements[min], elements[i]);
        }
    }
    template<typename Data>
    unsigned long Vector<Data>::findMin(unsigned long l, unsigned long r){
        unsigned long min = l;
        for (unsigned long i = l+1; i < r; ++i) {
            if (elements[min] > elements[i]) min = i;
        }
        return min;
    }

    template<typename Data>
    void Vector<Data>::InsertionSort(){
        for(unsigned long i = 1; i < size; i++){
            unsigned long j = i;
            while (j > 0 && elements[j] < elements[j-1]){
                std::swap(elements[j], elements[j-1]);
                j--;
            }
        }
    }

    template<typename Data>
    bool Vector<Data>::IsSorted(){
        if(size == 0) return true;
        for(unsigned long i = 0; i < size-1; i++){
            if(elements[i] > elements[i+1]) return false;
        }
        return true;
    }



/* ************************************************************************ */


/* ************************************************************************** */

}
