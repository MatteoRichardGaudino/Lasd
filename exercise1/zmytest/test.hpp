
#ifndef MYTEST_HPP
#define MYTEST_HPP


#include "../list/list.hpp"
#include "../vector/vector.hpp"
#include "../zlasdtest/test.hpp"

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
template<typename Data>
void setupContainerMenu(Menu&, LinearContainer<Data>&);
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

/* *** Container test *** */
template<typename Data>
void testFront(LinearContainer<Data>&);
template<typename Data>
void testBack(LinearContainer<Data>&);
template<typename Data>
void testSubscript(LinearContainer<Data>&);
template<typename Data>
void testExists(TestableContainer<Data>&);
template<typename Data>
void testEmpty(LinearContainer<Data>&);
template<typename Data>
void testSize(LinearContainer<Data>&);
template<typename Data>
void testClear(LinearContainer<Data>&);

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





    /*template<typename Data>
    bool checkExists(LinearContainer<Data>);

    bool checkSumLtN(FoldableContainer<int>, int); // less than
    bool checkProdGtN(FoldableContainer<float>, float); // greater than
    bool checkConcatLeN(FoldableContainer<string>, string); // less or equal than

    bool check2N(MappableContainer<int>);
    bool checkPow(MappableContainer<float>);
    bool checkUppercase(MappableContainer<string>);
/* ************************************************************************** */


#endif
