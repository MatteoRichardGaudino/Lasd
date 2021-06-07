
#ifndef MYTEST_HPP
#define MYTEST_HPP



#include "../zlasdtest/test.hpp"
#include "../matrix/matrix.hpp"
#include "../list/list.hpp"

#include <string>
#include <iostream>

using namespace lasd;
using namespace std;

/* ************************************************************************** */

class MenuItem{
public:
    typedef function<void(void)> ActionFunctor;

    MenuItem() = default;
    MenuItem(const MenuItem&);
    MenuItem(MenuItem&&) noexcept;
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
    MenuItem& operator=(MenuItem&& m) noexcept{
        swap(text, m.text);
        swap(action, m.action);
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
    void add(MenuItem&&);
    void add(const string&, const Menu&, bool);
    bool show() const;
    void loop() const;
    void loop(function<void(void)>) const;
    void clear();
private:
    List<MenuItem> items;
    string title;
};

void launchMenu();
template<typename Data>
void launchMatrixMenu(Matrix<Data>&);

void setupContainerMenu(Menu& menu, Container& cont);
template<typename Data>
void setupLinearContainerMenu(Menu&, LinearContainer<Data>&);
template<typename Data>
void setupMappableMenu(Menu&, MappableContainer<Data>&, const bool);
template<typename Data>
void setupFoldableMenu(Menu&, FoldableContainer<Data>&);
template<typename Data>
void setupTestableContainerMenu(Menu&, TestableContainer<Data>&);

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


/* *** Matrix test *** */

void myStressTest();

void popolaMatrix(Matrix<int>&);
void popolaMatrix(Matrix<float>&);
void popolaMatrix(Matrix<string>&);

template<typename Data>
void testRowResize(Matrix<Data>&);
template<typename Data>
void testColResize(Matrix<Data>&);
template<typename Data>
void testExistsCell(const Matrix<Data>&);
template<typename Data>
void testAccesOperator(Matrix<Data>&);
template<typename Data>
void testConstAccessOperator(const Matrix<Data>&);





/* ************************************************************************** */


#endif
