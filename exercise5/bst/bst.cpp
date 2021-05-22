#include "bst.hpp"

namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    BST<Data>::BST(const LinearContainer<Data>& lc){
        for (unsigned int i = 0; i < lc.Size(); ++i) {
            Insert(lc[i]);
        }
    }

    template<typename Data>
    BST<Data>::BST(const BST<Data>& bst) : BinaryTreeLnk<Data>(bst){}

    template<typename Data>
    BST<Data>::BST(BST<Data>&& bst) noexcept : BinaryTreeLnk<Data>(std::move(bst)){}

    template<typename Data>
    BST<Data>& BST<Data>::operator=(const BST<Data>& bst){
        BinaryTreeLnk<Data>::operator=(bst);
        return *this;
    }

    template<typename Data>
    BST<Data>& BST<Data>::operator=(BST<Data>&& bst) noexcept{
        BinaryTreeLnk<Data>::operator=(std::move(bst));
        return *this;
    }

    template<typename Data>
    bool  BST<Data>::operator==(const BST<Data>& bst) const noexcept{
        if (size == bst.size) {
            BTInOrderIterator<Data> i1(*this);
            BTInOrderIterator<Data> i2(bst);
            while (!i1.Terminated()){
                if (*i1 != *i2) return false;
                ++i1;
                ++i2;
            }
            return true;
        }else return false;
    }
    template<typename Data>
    bool  BST<Data>::operator!=(const BST<Data>& bst) const noexcept{
        return !operator==(bst);
    }

    template<typename Data>
    void BST<Data>::Insert(const Data& data){
        if (Empty()){
            root = new NodeLnk(data);
            size++;
        } else{
            NodeLnk** node = FindPointerTo(&root, data);
            if (*node == nullptr){
                *node = new NodeLnk(data);
                size++;
            }
        }
    }
    template<typename Data>
    void BST<Data>::Insert(Data&& data){
        if (Empty()){
            root = new NodeLnk(std::move(data));
            size++;
        } else{
            NodeLnk** node = FindPointerTo(&root, data);
            if (*node == nullptr){
                *node = new NodeLnk(std::move(data));
                size++;
            }
        }
    }
    template<typename Data>
    void BST<Data>::Remove(const Data& data){
        if (!Empty()){
            delete Detach(FindPointerTo(&root, data));
        }
    }

    template<typename Data>
    const Data& BST<Data>::Min() const {
        if (!Empty()){
            return (*FindPointerToMin(const_cast<NodeLnk**>(&root)))->element;
        } else throw std::length_error("[Min()] BTS is Empty");
    }
    template<typename Data>
    Data BST<Data>::MinNRemove() {
        if (!Empty()){
            NodeLnk* minPtr = DetachMin(&root);
            Data min = minPtr->element;
            delete minPtr;
            return min;
        } else throw std::length_error("[MinNRemove()] BTS is Empty");
    }
    template<typename Data>
    void BST<Data>::RemoveMin() {
        if (!Empty()){
            delete DetachMin(&root);
        } else throw std::length_error("[RemoveMin()] BTS is Empty");
    }



    template<typename Data>
    const Data& BST<Data>::Max() const {
        if (!Empty()){
            return (*FindPointerToMax(const_cast<NodeLnk**>(&root)))->element;
        } else throw std::length_error("[Max()] BTS is Empty");
    }
    template<typename Data>
    Data BST<Data>::MaxNRemove() {
        if (!Empty()){
            NodeLnk* maxPtr = DetachMax(&root);
            Data max = maxPtr->element;
            delete maxPtr;
            return max;
        } else throw std::length_error("[MaxNRemove()] BTS is Empty");
    }
    template<typename Data>
    void BST<Data>::RemoveMax() {
        if (!Empty()){
            delete DetachMax(&root);
        } else throw std::length_error("[RemoveMax()] BTS is Empty");
    }

    template<typename Data>
    const Data& BST<Data>::Predecessor(const Data& data) const{
        NodeLnk** pred = FindPointerToPredecessor(const_cast<NodeLnk**>(&root), data);
        if (pred != nullptr){
            return (*pred)->element;
        } else throw std::length_error("[Predecessor()] Predecessor doesn't exists");
    }
    template<typename Data>
    Data BST<Data>::PredecessorNRemove(const Data& data){
        NodeLnk** predPtr = FindPointerToPredecessor(&root, data);
        if (predPtr != nullptr){
            Data pred = (*predPtr)->element;
            delete Detach(predPtr);
            return pred;
        } else throw std::length_error("[PredecessorNRemove()] Predecessor doesn't exists");
    }
    template<typename Data>
    void BST<Data>::RemovePredecessor(const Data& data){
        NodeLnk** predPtr = FindPointerToPredecessor(&root, data);
        if (predPtr != nullptr){
            delete Detach(predPtr);
        } else throw std::length_error("[RemovePredecessor()] Predecessor doesn't exists");
    }

    template<typename Data>
    const Data& BST<Data>::Successor(const Data& data) const{
        NodeLnk** succ = FindPointerToSuccessor(const_cast<NodeLnk**>(&root), data);
        if (succ != nullptr){
            return (*succ)->element;
        } else throw std::length_error("[Successor()] Successor doesn't exists");
    }
    template<typename Data>
    Data BST<Data>::SuccessorNRemove(const Data& data){
        NodeLnk** succPtr = FindPointerToSuccessor(&root, data);
        if (succPtr != nullptr){
            Data succ = (*succPtr)->element;
            delete Detach(succPtr);
            return succ;
        } else throw std::length_error("[SuccessorNRemove()] Successor doesn't exists");
    }
    template<typename Data>
    void BST<Data>::RemoveSuccessor(const Data& data){
        NodeLnk** succPtr = FindPointerToSuccessor(&root, data);
        if (succPtr != nullptr){
            delete Detach(succPtr);
        } else throw std::length_error("[RemoveSuccessor()] Successor doesn't exists");
    }

    template<typename Data>
    bool BST<Data>::Exists(const Data& data) const noexcept{
        if (!Empty()) {
            return *FindPointerTo(const_cast<NodeLnk**>(&root), data) != nullptr;
        } else return false;
    }

    template<typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk** node){
        if (node != nullptr && *node != nullptr){
            NodeLnk* nod = *node;
            if (!((*node)->HasRightChild())) {
                *node = (*node)->left;
                nod->left = nullptr;
                size--;
            } else if (!((*node)->HasLeftChild())) {
                *node = (*node)->right;
                nod->right = nullptr;
                size--;
            } else{
                NodeLnk* min = DetachMin(&((*node)->right));
                std::swap((*node)->element, min->element);
                return min;
            }
            return nod;
        } else return nullptr;
    }

    template<typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk** node){
        if (node == nullptr || *node == nullptr) return nullptr;
        NodeLnk** minPtr = FindPointerToMin(node);
        NodeLnk* min = *minPtr;
        *minPtr = (*minPtr)->right;
        min->right = nullptr;
        size--;
        return min;
    }

    template<typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk** node){
        if (node == nullptr || *node == nullptr) return nullptr;
        NodeLnk** maxPtr = FindPointerToMax(node);
        NodeLnk* max = *maxPtr;
        *maxPtr = (*maxPtr)->left;
        max->left = nullptr;
        size--;
        return max;
    }

    template<typename Data>
    typename BST<Data>::NodeLnk** BST<Data>::FindPointerToMin(NodeLnk** node) const{
        if (node == nullptr || *node == nullptr) return nullptr;
        while ((*node)->HasLeftChild()){
            node = &((*node)->left);
        }
        return node;
    }
    template<typename Data>
    typename BST<Data>::NodeLnk** BST<Data>::FindPointerToMax(NodeLnk** node) const{
        if (node == nullptr || *node == nullptr) return nullptr;
        while ((*node)->HasRightChild()){
            node = &((*node)->right);
        }
        return node;
    }

    template<typename Data>
    typename BST<Data>::NodeLnk** BST<Data>::FindPointerTo(NodeLnk** node, const Data& data) const{
        if (node == nullptr || *node == nullptr) return nullptr;
        do{
            if (data == (*node)->element) return node;
            if (data < (*node)->element){
                if ((*node)->HasLeftChild()){
                    node = &((*node)->left);
                } else return &((*node)->left);
            }
            if (data > (*node)->element){
                if ((*node)->HasRightChild()){
                    node = &((*node)->right);
                } else return &((*node)->right);
            }
        } while (true);
    }

    template<typename Data>
    typename BST<Data>::NodeLnk** BST<Data>::FindPointerToPredecessor(NodeLnk** node, const Data& data) const{
        if (node == nullptr) return nullptr;
        NodeLnk** pred = nullptr;
        while ((*node) != nullptr && (*node)->element != data) {
            if (data < (*node)->element) {
                node = &((*node)->left);
            } else{
                pred = node;
                node = &((*node)->right);
            }
        }
        if (*node != nullptr && (*node)->HasLeftChild()) return FindPointerToMax(&((*node)->left));
        return pred;
    }
    template<typename Data>
    typename BST<Data>::NodeLnk** BST<Data>::FindPointerToSuccessor(NodeLnk** node, const Data& data) const{
        if (node == nullptr) return nullptr;
        NodeLnk** succ = nullptr;
        while (*node != nullptr && (*node)->element != data) {
            if (data < (*node)->element) {
                succ = node;
                node = &((*node)->left);
            } else{
                node = &((*node)->right);
            }
        }
        if (*node != nullptr && (*node)->HasRightChild()) return FindPointerToMin(&((*node)->right));
        return succ;
    }

/* ************************************************************************** */

}
