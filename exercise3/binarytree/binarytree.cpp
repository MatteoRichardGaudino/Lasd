
#include "../queue/vec/queuevec.hpp"

namespace lasd {

/* ************************************************************************** */

template<typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& node) const noexcept {
        if (Element() == node.Element()) {
            if (HasLeftChild() && node.HasLeftChild() &&
            HasRightChild() && node.HasRightChild()) { // se hanno entrambi i figli
                return LeftChild() == node.LeftChild() && RightChild() == node.RightChild(); // i nodi sono uguali se sono uguali ramo sx e dx
            } else if (IsLeaf() && node.IsLeaf()) return true; // se sono foglie sono uguali

            // se arriva qua allora uno dei 2 alberi ha un figlio mancante
            if ((HasLeftChild() && !node.HasLeftChild()) || // se uno ha figlio sinistro e l'altro no
                (!HasLeftChild() && node.HasLeftChild()) ||
                (HasRightChild() && !node.HasRightChild()) || // se uno ha figlio destro e l'altro no
                (!HasRightChild() && node.HasRightChild())) return false; // allora sono diversi

            // se arriva qua allora
            // il primo ha figlio destro <=> il secondo lo ha
            // il primo ha figlio sinistro <=> il secondo lo ha
            // il primo ha figlio sinistro <=> non ha figlio destro
            if (HasLeftChild()) { // se ha figlio sinistro (allora anche il secondo lo ha)
                return LeftChild() == node.LeftChild();
            } else if (HasRightChild()) { // se non ha figlio sinistro allora ha figlio destro
                return RightChild() == node.RightChild();
            }
        }
        return false;
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
    if (!Empty() && !bt.Empty())
        return Root() == bt.Root();
    else if (Empty() && bt.Empty()) return true;
    else return false;
}
template<typename Data>
bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& bt) const noexcept{
    return !operator==(bt);
}

/* ************************************************************************ */
template<typename Data>
void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void* v) {
    if (!Empty())
        MapPreOrder(Root(), fun, v);
}
template<typename Data>
void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void* v) {
    if (!Empty())
        MapPostOrder(Root(), fun, v);
}

/* ************************************************************************ */

template<typename Data>
void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void* v1, void* v2) const {
    if (!Empty())
        FoldPreOrder(Root(), fun, v1, v2);
}
template<typename Data>
void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void* v1, void* v2) const {
    if (!Empty())
        FoldPostOrder(Root(), fun, v1, v2);
}

template<typename Data>
void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void* v) {
    if (!Empty())
        MapInOrder(Root(), fun, v);
}

template<typename Data>
void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void* v1, void* v2) const {
    if (!Empty())
        FoldInOrder(Root(), fun, v1, v2);
}

template<typename Data>
void BinaryTree<Data>::MapBreadth(const MapFunctor fun, void* v) {
    if (!Empty())
        MapBreadth(Root(), fun, v);
}

template<typename Data>
void BinaryTree<Data>::FoldBreadth(const FoldFunctor fun, const void* v1, void* v2) const {
    if (!Empty())
        FoldBreadth(Root(), fun, v1, v2);
}

/* ************************************************************************ */


template<typename Data>
void BinaryTree<Data>::MapPreOrder(Node& node, const MapFunctor fun, void* v){
    fun(node.Element(), v);
    if (node.HasLeftChild())
        MapPreOrder(node.LeftChild(), fun, v);
    if (node.HasRightChild())
        MapPreOrder(node.RightChild(), fun, v);
    return;
}
template<typename Data>
void BinaryTree<Data>::MapPostOrder(Node& node, const MapFunctor fun, void* v){
    if (node.HasLeftChild())
        MapPostOrder(node.LeftChild(), fun, v);
    if (node.HasRightChild())
        MapPostOrder(node.RightChild(), fun, v);
    fun(node.Element(), v);
}
template<typename Data>
void BinaryTree<Data>::FoldPreOrder(Node& node, const FoldFunctor fun, const void* v1, void* v2) const{
    fun(node.Element(), v1, v2);
    if (node.HasLeftChild())
        FoldPreOrder(node.LeftChild(), fun, v1, v2);
    if (node.HasRightChild())
        FoldPreOrder(node.RightChild(), fun, v1, v2);
}
template<typename Data>
void BinaryTree<Data>::FoldPostOrder(Node& node, const FoldFunctor fun, const void* v1, void* v2) const{
    if (node.HasLeftChild())
        FoldPostOrder(node.LeftChild(), fun, v1, v2);
    if (node.HasRightChild())
        FoldPostOrder(node.RightChild(), fun, v1, v2);
    fun(node.Element(), v1, v2);
}
template<typename Data>
void BinaryTree<Data>::MapInOrder(Node& node, const MapFunctor fun, void* v){
    if (node.HasLeftChild())
        MapInOrder(node.LeftChild(), fun, v);
    fun(node.Element(), v);
    if (node.HasRightChild())
        MapInOrder(node.RightChild(), fun, v);
}
template<typename Data>
void BinaryTree<Data>::FoldInOrder(Node& node, const FoldFunctor fun, const void* v1, void* v2) const{
    if (node.HasLeftChild())
        FoldInOrder(node.LeftChild(), fun, v1, v2);
    fun(node.Element(), v1, v2);
    if (node.HasRightChild())
        FoldInOrder(node.RightChild(), fun, v1, v2);
}
template<typename Data>
void BinaryTree<Data>::MapBreadth(Node& node, const MapFunctor fun, void* v){
    QueueVec<Node*> q;
    q.Enqueue(&node);
    while (!q.Empty()){
        Node* n = q.HeadNDequeue();
        fun(n->Element(), v);
        if(n->HasLeftChild()) q.Enqueue(&(n->LeftChild()));
        if(n->HasRightChild()) q.Enqueue(&(n->RightChild()));
    }
}
template<typename Data>
void BinaryTree<Data>::FoldBreadth(Node& node, const FoldFunctor fun, const void* v1, void* v2) const{
    QueueVec<Node*> q;
    q.Enqueue(&node);
    while (!q.Empty()){
        Node* n = q.HeadNDequeue();
        fun(n->Element(), v1, v2);
        if(n->HasLeftChild()) q.Enqueue(&(n->LeftChild()));
        if(n->HasRightChild()) q.Enqueue(&(n->RightChild()));
    }
}
/* ************************************************************************** */

/* *** PreOrder Iterator  *** */
    template<typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& bt){
        binaryTree = &bt;
        if (!bt.Empty()) {
            node = &bt.Root();
        }
    }

    template<typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& i){
        stk = i.stk;
        node = i.node;
        binaryTree = i.binaryTree;
    }

    template<typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& i) noexcept{
        std::swap(stk, i.stk);
        std::swap(node, i.node);
        std::swap(binaryTree, i.binaryTree);
    }

    template<typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& i){
        stk = i.stk;
        node = i.node;
        binaryTree = i.binaryTree;
        return *this;
    }

    template<typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& i) noexcept{
        std::swap(stk, i.stk);
        std::swap(node, i.node);
        std::swap(binaryTree, i.binaryTree);
        return *this;
    }
    template<typename Data>
    bool BTPreOrderIterator<Data>:: operator==(const BTPreOrderIterator<Data>& i) const noexcept{
        return (node == i.node) && (stk == i.stk) && (binaryTree == i.binaryTree);
    }
    template<typename Data>
    bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data>& i) const noexcept{
        return !operator==(i);
    }

    template<typename Data>
    Data& BTPreOrderIterator<Data>::operator*() const{
        if (!Terminated()) return node->Element();
        else throw std::out_of_range("Iterator is Terminated");
    }

    template<typename Data>
    bool BTPreOrderIterator<Data>::Terminated() const noexcept{
        return node == nullptr;
    }

    template<typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++(){
        if (!Terminated()){
            if (node->HasRightChild()) stk.Push(&(node->RightChild()));

            if (node->HasLeftChild()) node = &(node->LeftChild());
            else {
                if (!stk.Empty()){
                    node = stk.TopNPop();
                } else node = nullptr;
            }
        } else throw std::out_of_range("Iterator is Terminated");
        return *this;
    }

/* *** PostOrder Iterator  *** */
    template<typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt){
        binaryTree = &bt;
        if (!bt.Empty()) {
            node = &bt.Root();
            gotoNext();
        }
    }

    template<typename Data>
    void BTPostOrderIterator<Data>::gotoNext(){
        if (node->HasLeftChild()){
            stk.Push(node);
            node = &(node->LeftChild());
            gotoNext();
        } else {
            if (node->HasRightChild()){
                stk.Push(node);
                node = &(node->RightChild());
                gotoNext();
            }
        }

    }

    template<typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data>& i){
        stk = i.stk;
        node = i.node;
        binaryTree = i.binaryTree;
        prevNode = i.prevNode;
    }

    template<typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data>&& i) noexcept{
        std::swap(stk, i.stk);
        std::swap(node, i.node);
        std::swap(binaryTree, i.binaryTree);
        std::swap(prevNode, i.prevNode);
    }

    template<typename Data>
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& i){
        stk = i.stk;
        node = i.node;
        binaryTree = i.binaryTree;
        prevNode = i.prevNode;
        return *this;
    }

    template<typename Data>
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data>&& i) noexcept{
        std::swap(stk, i.stk);
        std::swap(node, i.node);
        std::swap(prevNode, i.prevNode);
        std::swap(binaryTree, i.binaryTree);
        return *this;
    }
    template<typename Data>
    bool BTPostOrderIterator<Data>:: operator==(const BTPostOrderIterator<Data>& i) const noexcept{
        return (node == i.node) && (prevNode == i.prevNode) && (stk == i.stk) && (binaryTree == i.binaryTree);
    }
    template<typename Data>
    bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data>& i) const noexcept{
        return !operator==(i);
    }

    template<typename Data>
    Data& BTPostOrderIterator<Data>::operator*() const{
        if (!Terminated()) return node->Element();
        else throw std::out_of_range("Iterator is Terminated");
    }

    template<typename Data>
    bool BTPostOrderIterator<Data>::Terminated() const noexcept{
        return node == nullptr;
    }

    template<typename Data>
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++(){
        if (!Terminated()){
            if (stk.Empty()) node = nullptr;
            else {
                prevNode = node;
                node = stk.Top();
                if (node->HasRightChild() && prevNode != &(node->RightChild())){
                    node = &(node->RightChild());
                    gotoNext();
                } else node = stk.TopNPop();
            }
        } else throw std::out_of_range("Iterator is Terminated");
        return *this;
    }

/* *** InOrder Iterator  *** */
    template<typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt){
        binaryTree = &bt;
        if (!bt.Empty()) {
            node = &bt.Root();
            gotoMostLeftNode();
        }
    }
    template<typename Data>
    void BTInOrderIterator<Data>::gotoMostLeftNode() {
        while (node->HasLeftChild()){
            stk.Push(node);
            node = &(node->LeftChild());
        }
    }

    template<typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data>& i){
        stk = i.stk;
        node = i.node;
        binaryTree = i.binaryTree;
    }

    template<typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data>&& i) noexcept{
        std::swap(stk, i.stk);
        std::swap(node, i.node);
        std::swap(binaryTree, i.binaryTree);
    }

    template<typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data>& i){
        stk = i.stk;
        node = i.node;
        binaryTree = i.binaryTree;
        return *this;
    }

    template<typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data>&& i) noexcept{
        std::swap(stk, i.stk);
        std::swap(node, i.node);
        std::swap(binaryTree, i.binaryTree);
        return *this;
    }
    template<typename Data>
    bool BTInOrderIterator<Data>:: operator==(const BTInOrderIterator<Data>& i) const noexcept{
        return (node == i.node) && (stk == i.stk) && (binaryTree == i.binaryTree);
    }
    template<typename Data>
    bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& i) const noexcept{
        return !operator==(i);
    }

    template<typename Data>
    Data& BTInOrderIterator<Data>::operator*() const{
        if (!Terminated()) return node->Element();
        else throw std::out_of_range("Iterator is Terminated");
    }

    template<typename Data>
    bool BTInOrderIterator<Data>::Terminated() const noexcept{
        return node == nullptr;
    }

    template<typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++(){
        if (!Terminated()){
            if (node->HasRightChild()) {
                node = &(node->RightChild());
                gotoMostLeftNode();
            } else {
                if(stk.Empty()) node = nullptr;
                else node = stk.TopNPop();
            }
        } else throw std::out_of_range("Iterator is Terminated");
        return *this;
    }

/* *** Breadth Iterator  *** */
    template<typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bt){
        binaryTree = &bt;
        if (!bt.Empty()) {
            node = &bt.Root();
            if (node->HasLeftChild()) que.Enqueue(&(node->LeftChild()));
            if (node->HasRightChild()) que.Enqueue(&(node->RightChild()));
        }
    }


    template<typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& i){
        que = i.que;
        node = i.node;
        binaryTree = i.binaryTree;
    }

    template<typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& i) noexcept{
        std::swap(que, i.que);
        std::swap(node, i.node);
        std::swap(binaryTree, i.binaryTree);
    }

    template<typename Data>
    BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data>& i){
        que = i.que;
        node = i.node;
        binaryTree = i.binaryTree;
        return *this;
    }

    template<typename Data>
    BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data>&& i) noexcept{
        std::swap(que, i.que);
        std::swap(node, i.node);
        std::swap(binaryTree, i.binaryTree);
        return *this;
    }
    template<typename Data>
    bool BTBreadthIterator<Data>:: operator==(const BTBreadthIterator<Data>& i) const noexcept{
        return (node == i.node) && (que == i.que) && (binaryTree == i.binaryTree);
    }
    template<typename Data>
    bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& i) const noexcept{
        return !operator==(i);
    }

    template<typename Data>
    Data& BTBreadthIterator<Data>::operator*() const{
        if (!Terminated()) return node->Element();
        else throw std::out_of_range("Iterator is Terminated");
    }

    template<typename Data>
    bool BTBreadthIterator<Data>::Terminated() const noexcept{
        return node == nullptr;
    }

    template<typename Data>
    BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++(){
        if (!Terminated()){
            if (!que.Empty()){
                node = que.HeadNDequeue();
                if (node->HasLeftChild()) que.Enqueue(&(node->LeftChild()));
                if (node->HasRightChild()) que.Enqueue(&(node->RightChild()));
            } else node = nullptr;
        } else throw std::out_of_range("Iterator is Terminated");
        return *this;
    }
}