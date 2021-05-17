
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
            NodeLnk* nod = FindPointerTo(data);
            if (nod->Element() != data){
                auto* newNode = new NodeLnk(data);
                if (data < nod->Element()){
                    nod->left = newNode;
                } else {
                    nod->right = newNode;
                }
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
            NodeLnk* nod = FindPointerTo(data);
            if (nod->Element() != data){
                auto* newNode = new NodeLnk(std::move(data));
                if (data < nod->Element()){
                    nod->left = newNode;
                } else {
                    nod->right = newNode;
                }
                size++;
            }
        }
    }
    template<typename Data>
    void BST<Data>::Remove(const Data& data){
        if (!Empty()){
            Remove(root, data);
        }
    }

    template<typename Data>
    const Data& BST<Data>::Min() const {
        if (!Empty()){
            return FindPointerToMin(root)->Element();
        } else throw std::length_error("[Min()] BTS is Empty");
    }
    template<typename Data>
    Data BST<Data>::MinNRemove() {
        if (!Empty()){
            NodeLnk* node = DetachMin();
            Data min = node->Element();
            delete node;
            return min;
        } else throw std::length_error("[RemoveMin()] BTS is Empty");
    }
    template<typename Data>
    void BST<Data>::RemoveMin() {
        if (!Empty()){
            delete DetachMin();
        } else throw std::length_error("[RemoveMin()] BTS is Empty");
    }



    template<typename Data>
    const Data& BST<Data>::Max() const {
        if (!Empty()){
            return FindPointerToMax(root)->Element();
        } else throw std::length_error("[Max()] BTS is Empty");
    }
    template<typename Data>
    Data BST<Data>::MaxNRemove() {
        if (!Empty()){
            NodeLnk* node = DetachMax();
            Data max = node->Element();
            delete node;
            return max;
        } else throw std::length_error("[RemoveMax()] BTS is Empty");
    }
    template<typename Data>
    void BST<Data>::RemoveMax() {
        if (!Empty()){
            delete DetachMax();
        } else throw std::length_error("[RemoveMax()] BTS is Empty");
    }

    template<typename Data>
    const Data& BST<Data>::Predecessor(const Data& data) const{
        NodeLnk* pred = FindPointerToPredecessor(data);
        if (pred != nullptr) return pred->Element();
        else throw std::length_error("[Predecessor()] Predecessor doesn't exists");
    }
    template<typename Data>
    Data BST<Data>::PredecessorNRemove(const Data& data){
        NodeLnk* pred = FindPointerToPredecessor(data);
        if (pred != nullptr){
            Data d = pred->Element();
            Remove(d);
            return d;
        } else throw std::length_error("[PredecessorNRemove()] Predecessor doesn't exists");
       // TODO
    }
    template<typename Data>
    void BST<Data>::RemovePredecessor(const Data& data){
        NodeLnk* pred = FindPointerToPredecessor(data);
        if (pred != nullptr){
            Remove(pred->Element());
        } else throw std::length_error("[RemovePredecessor()] Predecessor doesn't exists");
        //TODO
    }

    template<typename Data>
    const Data& BST<Data>::Successor(const Data& data) const{
        NodeLnk* pred = FindPointerToSuccessor(data);
        if (pred != nullptr) return pred->Element();
        else throw std::length_error("[Successor()] Successor doesn't exists");
    }
    template<typename Data>
    Data BST<Data>::SuccessorNRemove(const Data& data){
        NodeLnk* succ = FindPointerToSuccessor(data);
        if (succ != nullptr){
            Data d = succ->Element();
            Remove(d);
            return d;
        } else throw std::length_error("[SuccessorNRemove()] Successor doesn't exists");
        // TODO
    }
    template<typename Data>
    void BST<Data>::RemoveSuccessor(const Data& data){
        NodeLnk* succ = FindPointerToSuccessor(data);
        if (succ != nullptr){
            Remove(succ->Element());
        } else throw std::length_error("[RemoveSuccessor()] Successor doesn't exists");
        // TODO
    }

    template<typename Data>
    bool BST<Data>::Exists(const Data& data) const noexcept{
        if (!Empty()) {
            NodeLnk *n = FindPointerTo(data);
            if (n->Element() == data) return true;
            else return false;
        } else return false;
    }


    template<typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::Remove(NodeLnk* node, const Data& data){
        if (node != nullptr) {
            if (data < node->Element())
                node->left = Remove(node->left, data);
            else if (data > node->Element())
                node->right = Remove(node->right, data);
            else {
                if (!node->HasRightChild())
                    node = node->left;
                else if (!node->HasLeftChild())
                    node = node->right;
                else{
                    NodeLnk* min = SkipOnLeft(node->right);
                    if (min == nullptr){
                        min = node->right;
                        node->right = nullptr;
                    }
                    node->Element() = min->Element();
                    delete min;
                }
                size--;
            }
        }
        return node;
    }

    template<typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::DetachMin(){
        if (size > 0){
            NodeLnk* nod = SkipOnLeft(root);
            size--;
            if (nod == nullptr){
                NodeLnk* min = root;
                root = nullptr;
                return min;
            } else {
                NodeLnk* min = nod->left;
                nod->left = nullptr;
                return min;
            }
        } else return nullptr;
    }

    template<typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::DetachMax(){
        if (size > 0){
            NodeLnk* nod = SkipOnRight(root);
            size--;
            if (nod == nullptr) {
                NodeLnk* max = root;
                root = nullptr;
                return max;
            } else{
                NodeLnk *max = nod->right;
                nod->right = nullptr;
                return max;
            }
        } else return nullptr;
    }

    template<typename Data>
    typename BST<Data>::NodeLnk * BST<Data>::SkipOnLeft(NodeLnk* node) const {
        if (node != nullptr && node->HasLeftChild()){
            if (node->left->HasLeftChild())
                return SkipOnLeft(node->left);
            else return node;
        } else return nullptr;
    }
    template<typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::SkipOnRight(NodeLnk* node) const{
        if (node != nullptr && node->HasRightChild()){
            if (node->right->HasRightChild())
                return SkipOnRight(node->right);
            else return node;
        } else return nullptr;
    }

    template<typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::FindPointerToMin(NodeLnk* node) const{
        if (node != nullptr){
            NodeLnk* n = SkipOnLeft(node);
            if (n == nullptr) return node;
            else return n->left;
        } else return nullptr;
    }
    template<typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::FindPointerToMax(NodeLnk* node) const{
        if (node != nullptr){
            NodeLnk* n = SkipOnRight(node);
            if (n == nullptr) return node;
            else return n->right;
        } else return nullptr;
    }

    template<typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::FindPointerTo(const Data& data) const{
        NodeLnk* tmp = root;
        do{
            if (data == tmp->Element()) return tmp;
            if (data < tmp->Element()){
                if (tmp->HasLeftChild()){
                    tmp = tmp->left;
                } else return tmp;
            }
            if (data > tmp->Element()){
                if (tmp->HasRightChild()){
                    tmp = tmp->right;
                } else return tmp;
            }
        } while (true);
    }

    template<typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::FindPointerToPredecessor(const Data& data) const{
        NodeLnk* pred = nullptr;
        NodeLnk* tmp = root;
        if (!Empty()){
            while (tmp != nullptr && tmp->Element() != data) {
                if (data < tmp->Element()) {
                    tmp = tmp->left;
                } else{
                    pred = tmp;
                    tmp = tmp->right;
                }
            }
            if (tmp != nullptr && tmp->HasLeftChild()) return FindPointerToMax(tmp->left);
            return pred;
        } else return nullptr; // TODO
    }
    template<typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::FindPointerToSuccessor(const Data& data) const{
        NodeLnk* succ = nullptr;
        NodeLnk* tmp = root;
        if (!Empty()){
            while (tmp != nullptr && tmp->Element() != data) {
                if (data < tmp->Element()) {
                    succ = tmp;
                    tmp = tmp->left;
                } else{
                    tmp = tmp->right;
                }
            }
            if (tmp != nullptr && tmp->HasRightChild()) return FindPointerToMin(tmp->right);
            return succ;
        } else return nullptr;
    }

/* ************************************************************************** */

}
