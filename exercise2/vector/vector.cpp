
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
            elements[i] = vector[i];
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



/* ************************************************************************ */


/* ************************************************************************** */

}
