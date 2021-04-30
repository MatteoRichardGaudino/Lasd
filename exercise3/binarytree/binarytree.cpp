
#include "../queue/vec/queuevec.hpp"

namespace lasd {

/* ************************************************************************** */

template<typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& node) const noexcept {
        if (Element() != node.Element()) return false;

        else if(HasLeftChild() && node.HasLeftChild() && HasRightChild() && node.HasLeftChild()){
            return LeftChild() == node.LeftChild() && RightChild() == node.RightChild();
        }

        else if(HasLeftChild() && node.HasLeftChild()) {
            return LeftChild() == node.LeftChild();
        } else if(HasLeftChild() || node.HasLeftChild()) return false;

        else if (HasRightChild() && node.HasRightChild()){
            return RightChild() == node.RightChild();
        } else if(HasRightChild() || node.HasRightChild()) return false;
}

template<typename Data>
bool BinaryTree<Data>::Node::operator!=(const Node& node) const noexcept {
    return !operator==(node);
}

template<typename Data>
bool BinaryTree<Data>::Node::IsLeaf() const noexcept{
    return !(HasLeftChild() || HasRightChild());
}

template<typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree<Data>& bt) const noexcept{
    return Root() == bt.Root();
}
template<typename Data>
bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& bt) const noexcept{
    return !operator==(bt);
}
template<typename Data>
void BinaryTree<Data>::MapPreOrder(Node& node, const MapFunctor fun, void* v){
    fun(node.Element(), v);
    if (node.HasLeftChild())
        MapPreOrder(node.LeftChild(), fun, v);
    if (node.HasRightChild())
        MapPreOrder(node.RightChild(), fun, v);
}
template<typename Data>
void BinaryTree<Data>::MapPostOrder(Node& node, const MapFunctor fun, void* v){
    if (node.HasLeftChild())
        MapPreOrder(node.LeftChild(), fun, v);
    if (node.HasRightChild())
        MapPreOrder(node.RightChild(), fun, v);
    fun(node.Element(), v);
}
template<typename Data>
void BinaryTree<Data>::FoldPreOrder(const Node& node, const FoldFunctor fun, const void* v1, void* v2){
    fun(node.Element(), v1, v2);
    if (node.HasLeftChild())
        MapPreOrder(node.LeftChild(), fun, v1, v2);
    if (node.HasRightChild())
        MapPreOrder(node.RightChild(), fun, v1, v2);
}
template<typename Data>
void BinaryTree<Data>::FoldPostOrder(const Node& node, const FoldFunctor fun, const void* v1, void* v2){
    if (node.HasLeftChild())
        MapPreOrder(node.LeftChild(), fun, v1, v2);
    if (node.HasRightChild())
        MapPreOrder(node.RightChild(), fun, v1, v2);
    fun(node.Element(), v1, v2);
}
template<typename Data>
void BinaryTree<Data>::MapInOrder(Node& node, const MapFunctor fun, void* v){
    if (node.HasLeftChild())
        MapPreOrder(node.LeftChild(), fun, v);
    fun(node.Element(), v);
    if (node.HasRightChild())
        MapPreOrder(node.RightChild(), fun, v);
}
template<typename Data>
void BinaryTree<Data>::FoldInOrder(const Node& node, const FoldFunctor fun, const void* v1, void* v2) const{
    if (node.HasLeftChild())
        MapPreOrder(node.LeftChild(), fun, v1, v2);
    fun(node.Element(), v1, v2);
    if (node.HasRightChild())
        MapPreOrder(node.RightChild(), fun, v1, v2);
}
template<typename Data>
void BinaryTree<Data>::MapBreadth(Node& node, const MapFunctor fun, void* v){
    QueueVec<Node*> q;
    q.Enqueue(&node);
    while (!q.Empty()){
        Node* n = q.HeadNDequeue();
        fun(*n, v);
        if(n->HasLeftChild()) q.Enqueue(&(n->LeftChild()));
        if(n->HasRightChild()) q.Enqueue(&(n->RightChild()));
    }
}
template<typename Data>
void BinaryTree<Data>::FoldBreadth(const Node& node, const FoldFunctor fun, const void* v1, void* v2) const{
    QueueVec<Node*> q;
    q.Enqueue(&node);
    while (!q.Empty()){
        Node* n = q.HeadNDequeue();
        fun(*n, v1, v2);
        if(n->HasLeftChild()) q.Enqueue(&(n->LeftChild()));
        if(n->HasRightChild()) q.Enqueue(&(n->RightChild()));
    }
}
/* ************************************************************************** */

}
