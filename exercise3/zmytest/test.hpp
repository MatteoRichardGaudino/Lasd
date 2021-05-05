
#ifndef MYTEST_HPP
#define MYTEST_HPP


#include "../list/list.hpp"
#include "../vector/vector.hpp"
#include "../stack/stack.hpp"
#include "../queue/queue.hpp"
#include "../zlasdtest/test.hpp"
#include "../binarytree/binarytree.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"

#include <string>
#include <iostream>

using namespace lasd;
using namespace std;

/* ************************************************************************** */

class MenuItem{
public:
    typedef function<void(void)> ActionFunctor;

    MenuItem() = default;
    MenuItem(const string &);
    MenuItem(const string&, ActionFunctor);
    virtual ~MenuItem() = default;
    string getText() const{
        return text;
    }
    void run();
    void setOnAction(ActionFunctor);

    MenuItem& operator=(const MenuItem& m){
        text = m.text;
        action = m.action;
        return *this;
    }
    bool operator==(const MenuItem& m) const noexcept{
        return this == &m;
    }
private:
    string text;
    ActionFunctor action;
};

class Menu{
public:
    Menu(const string&);
    virtual ~Menu() = default;
    void add(const MenuItem&);
    void add(MenuItem&&) noexcept;
    bool show() const;
private:
    List<MenuItem> items;
    string title;
};

void launchMenu();
void setupContainerMenu(Menu& menu, Container& cont);
template<typename Data>
void setupLinearContainerMenu(Menu&, LinearContainer<Data>&);
template<typename Data>
void setupMappableMenu(Menu&, MappableContainer<Data>&, const bool);
template<typename Data>
void setupFoldableMenu(Menu&, FoldableContainer<Data>&);
template<typename Data>
void setupTestableContainerMenu(Menu&, TestableContainer<Data>&);

template<typename Data>
void launchVectorMenu();
template<typename Data>
void launchListMenu();

template<typename Data>
void launchStackMenu(Stack<Data>&);

template<typename Data>
void launchQueueMenu(Queue<Data>&);

template<typename Data>
void launchBtMenu(BinaryTree<Data>&);

/* *** Container test *** */

void testEmpty(Container&);
void testSize(Container&);
void testClear(Container&);

/* *** Linear Container test *** */
template<typename Data>
void testFront(LinearContainer<Data>&);
template<typename Data>
void testBack(LinearContainer<Data>&);
template<typename Data>
void testSubscript(LinearContainer<Data>&);
template<typename Data>
void testExists(TestableContainer<Data>&);


/* *** Vector test *** */
template<typename Data>
void testResize(Vector<Data>&);
void popolaVector(Vector<int> &);
void popolaVector(Vector<float> &);
void popolaVector(Vector<string> &);


/* *** List test *** */
void popolaList(List<int>&);
void popolaList(List<float>&);
void popolaList(List<string>&);

template<typename Data>
void testInsertAtFront(List<Data>&);
template<typename Data>
void testRemoveFromFront(List<Data>&);
template<typename Data>
void testFrontNRemove(List<Data>&);
template<typename Data>
void testInsertAtBack(List<Data>&);

/* *** Mappable test *** */
template<typename Data>
void printMappable(MappableContainer<Data>&, bool);
void testMappable(MappableContainer<int>&);
void testMappable(MappableContainer<float>&);
void testMappable(MappableContainer<string>&);

/* *** Foldable test *** */
void testFoldable(FoldableContainer<int>&);
void testFoldable(FoldableContainer<float>&);
void testFoldable(FoldableContainer<string>&);


/* *** Stack test *** */
void popolaStack(Stack<int>&);
void popolaStack(Stack<float>&);
void popolaStack(Stack<string>&);

template<typename Data>
void testPush(Stack<Data>&);
template<typename Data>
void testTop(Stack<Data>&);
template<typename Data>
void testPop(Stack<Data>&);
template<typename Data>
void testTopNPop(Stack<Data>&);

/* *** Queue test *** */
void popolaQueue(Queue<int>&);
void popolaQueue(Queue<float>&);
void popolaQueue(Queue<string>&);

template<typename Data>
void testEnqueue(Queue<Data>&);
template<typename Data>
void testHead(Queue<Data>&);
template<typename Data>
void testDequeue(Queue<Data>&);
template<typename Data>
void testHeadNDequeue(Queue<Data>&);

/* *** BinaryTree test *** */
template<typename Data>
void popolaBt(BinaryTree<Data>&);
void popolaBtVec(BinaryTreeVec<int>&);
void popolaBtVec(BinaryTreeVec<float>&);
void popolaBtVec(BinaryTreeVec<string>&);

void popolaBtLnk(BinaryTreeLnk<int>&);
void popolaBtLnk(BinaryTreeLnk<float>&);
void popolaBtLnk(BinaryTreeLnk<string>&);

template<typename Data>
void printPreOrder(const MappableContainer<Data>&);
template<typename Data>
void printPostOrder(const MappableContainer<Data>&);
template<typename Data>
void printInOrder(const InOrderMappableContainer<Data>&);
template<typename Data>
void printBreadth(const BreadthMappableContainer<Data>&);

void testMappableBT(MappableContainer<int>&);
void testMappableBT(MappableContainer<float>&);
void testMappableBT(MappableContainer<string>&);

template<typename Data>
void gotoRight(typename BinaryTree<Data>::Node*&);
template<typename Data>
void gotoLeft(typename BinaryTree<Data>::Node*&);
template<typename Data>
void gotoRoot(typename BinaryTree<Data>::Node*&);

template<typename Data>
void testRoot(BinaryTree<Data>&);

template<typename Data>
void testIsLeaf(typename BinaryTree<Data>::Node*);
template<typename Data>
void testHasLeftChild(typename BinaryTree<Data>::Node*);
template<typename Data>
void testHasRightChild(typename BinaryTree<Data>::Node*);
template<typename Data>
void testElement(typename BinaryTree<Data>::Node*);


/* ************************************************************************** */


#endif
