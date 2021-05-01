
namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept{
        return element;
    }
    template<typename Data>
    const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept{
        return element;
    }

    template<typename Data>
    bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept{
        return (index*2) + 1 < elements.Size();
    }
    template<typename Data>
    bool BinaryTreeVec<Data>::NodeVec::HasRightChild()  const noexcept{
        return (index*2) + 2 < elements.Size();
    }

    template<typename Data>
    typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
        if (HasLeftChild()) return elements[(index*2) + 1];
        else throw std::out_of_range("Left child does not exist");
    }

    template<typename Data>
    typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const {
        if (HasRightChild()) return elements[(index*2) + 2];
        else throw std::out_of_range("Right child does not exist");
    }
    template<typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data>& linearContainer){
        elements.Resize(linearContainer.Size());
        for (unsigned long i = 0;  i < linearContainer.Size(); i++) {
            elements[i].element = linearContainer[i];
            elements.index = i;
        }
    }

    template<typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& bt) {
        elements = bt.elements;
    }

    template<typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& bt) noexcept {
        std::swap(elements, bt.elements);
    }

    template<typename Data>
    BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& bt){
        elements = bt.elements;
        return *this;
    }

    template<typename Data>
    BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& bt) noexcept{
        std::swap(elements, bt.elements);
        return *this;
    }

    template<typename Data>
    bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& bt) const noexcept{
        if (elements.Size() == bt.elements.Size()){
            for (unsigned long i = 0; i < elements.Size(); ++i) {
                if (elements[i].element != bt.elements[i].element) return false;
            }
            return true;
        } else return false;
    }
    template<typename Data>
    bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& bt) const noexcept{
        return !operator==(bt);
    }

    template<typename Data>
    typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const{
        if (elements.Size() != 0){
            return elements[0];
        } else throw std::length_error("BinaryTreeVec is Empty");
    }

    template<typename Data>
    void BinaryTreeVec<Data>::Clear(){
        elements.Clear();
    }
    template<typename Data>
    unsigned long BinaryTreeVec<Data>::Size() const noexcept{
        return elements.Size();
    }

    template<typename Data>
    void BinaryTreeVec<Data>::MapBreadth(const MapFunctor fun, void* v){
        for (unsigned long i = 0; i < elements.Size(); ++i) {
            fun(elements[i].element, v);
        }
    }

    template<typename Data>
    void BinaryTreeVec<Data>::FoldBreadth(const FoldFunctor fun, const void* v1, void* v2) const{
        for (unsigned long i = 0; i < elements.Size(); ++i) {
            fun(elements[i].element, v1, v2);
        }
    }

/* ************************************************************************** */

}
