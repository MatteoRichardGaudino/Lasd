
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


/* ************************************************************************** */

}
