
#include "../../../exercise1/container/container.hpp"

namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    StackVec<Data>::StackVec(){
        Vector<Data>::Resize(initSize);
    }

    template<typename Data>
    StackVec<Data>::StackVec(const LinearContainer<Data>& lc) : Vector<Data>(lc){
        cursor = size;
        if (size*resizeFactor < initSize) Vector<Data>::Resize(initSize);
        else Expand();
    }

    template<typename Data>
    StackVec<Data>::StackVec(const StackVec<Data>& sv) : Vector<Data>(sv){
        cursor = sv.cursor;
    }
    template<typename Data>
    StackVec<Data>::StackVec(StackVec<Data>&& sv) noexcept {
        std::swap(elements, sv.elements);
        std::swap(size, sv.size);
        std::swap(cursor, sv.cursor);
    }


    template<typename Data>
    StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& sv){
        Vector<Data>::operator=(sv);
        cursor = sv.cursor;
        return *this;
    }
    template<typename Data>
    StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& sv) noexcept{
        std::swap(cursor, sv.cursor);
        Vector<Data>::operator=(std::move(sv));
        return *this;
    }

    template<typename Data>
    bool StackVec<Data>::operator==(const StackVec<Data>& sv) const noexcept{
        if (sv.cursor == cursor){
            for (unsigned long i = 0; i < cursor; ++i) {
                if (elements[i] != sv.elements[i]) return false;
            }
            return true;
        } else return false;
    }

    template<typename Data>
    bool StackVec<Data>::operator!=(const StackVec<Data>& sv) const noexcept{
        return !operator==(sv);
    }


    template<typename Data>
    void StackVec<Data>::Push(const Data& data){
        elements[cursor++] = data;
        Expand();
    }
    template<typename Data>
    void StackVec<Data>::Push(Data&& data){
        elements[cursor++] = std::move(data);
        Expand();
    }

    template<typename Data>
    Data& StackVec<Data>::Top() const{
        if (cursor != 0){
            return elements[cursor-1];
        } else {
            throw std::length_error("Stack is empty");
        }
    }
    template<typename Data>
    void StackVec<Data>::Pop(){
        if (cursor != 0){
            cursor--;
            Reduce();
        } else{
            throw std::length_error("Stack is empty");
        }
    }

    template<typename Data>
    Data StackVec<Data>::TopNPop(){
        if (cursor != 0){
            Data val = std::move(elements[--cursor]);
            Reduce();
            return val;
        } else{
            throw std::length_error("Stack is empty");
        }
    }

    template<typename Data>
    bool StackVec<Data>::Empty() const noexcept{
        return cursor == 0;
    }

    template<typename Data>
    unsigned long StackVec<Data>::Size() const noexcept{
        return cursor;
    }

    template<typename Data>
    void StackVec<Data>::Clear() {
        Vector<Data>::Clear();
        Vector<Data>::Resize(initSize);
        cursor = 0;
    }

    template<typename Data>
    void StackVec<Data>::Expand() {
        if (cursor >= size - 1){
            Vector<Data>::Resize(size*resizeFactor);
            std::cout<< "Stack expanded cursor: " << cursor << " newSize: " << size << " oldSize: " << size/resizeFactor << std::endl;
        }
    }
    template<typename Data>
    void StackVec<Data>::Reduce() {
        unsigned long newSize = size/resizeFactor;
        if (cursor <= size/4 && newSize > cursor && newSize >= initSize){ //cursor <= 25% of size
            Vector<Data>::Resize(newSize);
            std::cout<< "Stack reduced cursor: " << cursor << " newSize: " << size << " oldSize: " << size*resizeFactor << std::endl;
        }
    }
/* ************************************************************************** */

}






