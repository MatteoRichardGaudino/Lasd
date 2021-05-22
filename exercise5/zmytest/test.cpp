#include "test.hpp"
#include "../stack/vec/stackvec.hpp"
#include <random>

using namespace std;

MenuItem::MenuItem(const MenuItem& m){
    text = m.text;
    action = m.action;
}
MenuItem::MenuItem(MenuItem&& m) noexcept{
    swap(text, m.text);
    swap(action, m.action);
}
MenuItem::MenuItem(const string& label, function<void()> onAction){
    text = label;
    action = onAction;
}
MenuItem::MenuItem(const string & label){
    text = label;
    action = [](){};
}
void MenuItem::run(){
    action();
}

void MenuItem::setOnAction(function<void(void)> fun){
    action = fun;
}
Menu::Menu(const string& t){
    title = t;
}
void Menu::add(const MenuItem& item){
    items.InsertAtBack(item);
}
void Menu::add(MenuItem&& item){
    items.InsertAtBack(move(item));
}

void Menu::add(const string& t, const Menu& subMenu, bool loop){
    if (loop){
        MenuItem item(t, [=]() {
            subMenu.loop();
        });
        add(item);
    } else{
        MenuItem item(t, [=]() {
            subMenu.show();
        });
        add(item);
    }
}

bool Menu::show() const{
    cout << "********************" << endl;
    cout << title << endl;
    unsigned int index = 1;
    items.FoldPreOrder([](const MenuItem& item, const void* _, void* i){
        cout << "[" << (*((unsigned int*) i)) << "] " << item.getText() << endl;
        (*((unsigned int*) i))++;
    }, nullptr, &index);

    cout << "[other] quit" << endl;

    unsigned int input = 0;
    cout << ">>> ";
    cin >> input;

    if (input > 0 && input <= items.Size()){
        items[input-1].run();
    } else {
        cout << "********************" << endl;
        return false;
    }
    cout << "********************" << endl;
    return true;
}

void Menu::loop() const{
    while (show());
}
void Menu::loop(function<void(void)> fun) const{
    while (show())
        fun();
}

void Menu::clear(){
    items.Clear();
}

void launchMenu(){
    Menu exMenu("Chose an exercise:");

    Menu structMenu("Chose a data structure");
    Menu typeMenu("Chose a type:");

    MenuItem intType("Int");
    MenuItem floatType("Float");
    MenuItem stringType("String");

    MenuItem fullTest("Start lasd full test", [](){
        lasdtest();
        exit(0);
    });

    MenuItem ex1("Exercise 1 (Vector, List)", [&](){
        MenuItem vect("Vector", [&](){
            intType.setOnAction([](){ launchVectorMenu<int>(); });
            floatType.setOnAction([](){ launchVectorMenu<float>(); });
            stringType.setOnAction([](){ launchVectorMenu<string>(); });
        });
        MenuItem list("List", [&](){
            intType.setOnAction([](){ launchListMenu<int>(); });
            floatType.setOnAction([](){ launchListMenu<float>(); });
            stringType.setOnAction([](){ launchListMenu<string>(); });
        });
        structMenu.add(vect);
        structMenu.add(list);
    });
    MenuItem ex2("Exercise 2 (Queue, Stack)", [&](){
        MenuItem stackVec("StackVec", [&](){
            intType.setOnAction([](){
                StackVec<int> stk;
                launchStackMenu(stk);
            });
            floatType.setOnAction([](){
                StackVec<float> stk;
                launchStackMenu(stk);
            });
            stringType.setOnAction([](){
                StackVec<string> stk;
                launchStackMenu(stk);
            });
        });
        MenuItem stackLst("StackLst", [&](){
            intType.setOnAction([](){
                StackLst<int> stk;
                launchStackMenu<int>(stk);
            });
            floatType.setOnAction([](){
                StackLst<float> stk;
                launchStackMenu<float>(stk);
            });
            stringType.setOnAction([](){
                StackLst<string> stk;
                launchStackMenu<string>(stk);
            });
        });
        MenuItem queueLst("QueueLst", [&](){
            intType.setOnAction([](){
                QueueLst<int> que;
                launchQueueMenu<int>(que);
            });
            floatType.setOnAction([](){
                QueueLst<float> que;
                launchQueueMenu<float>(que);
            });
            stringType.setOnAction([](){
                QueueLst<string> que;
                launchQueueMenu<string>(que);
            });
        });
        MenuItem queueVec("QueueVec", [&](){
            intType.setOnAction([](){
                QueueVec<int> que;
                launchQueueMenu<int>(que);
            });
            floatType.setOnAction([](){
                QueueVec<float> que;
                launchQueueMenu<float>(que);
            });
            stringType.setOnAction([](){
                QueueVec<string> que;
                launchQueueMenu<string>(que);
            });
        });
        structMenu.add(stackVec);
        structMenu.add(stackLst);
        structMenu.add(queueVec);
        structMenu.add(queueLst);
    });
    MenuItem ex3("Exercise 3 (BinaryTree)", [&](){
        MenuItem btVec("BinaryTreeVec", [&](){
            intType.setOnAction([](){
                BinaryTreeVec<int> bt;
                launchBtMenu(bt);
            });
            floatType.setOnAction([](){
                BinaryTreeVec<float> bt;
                launchBtMenu(bt);
            });
            stringType.setOnAction([](){
                BinaryTreeVec<string> bt;
                launchBtMenu(bt);
            });
        });
        MenuItem btLnk("BinaryTreeLnk", [&](){
            intType.setOnAction([](){
                BinaryTreeLnk<int> bt;
                launchBtMenu(bt);
            });
            floatType.setOnAction([](){
                BinaryTreeLnk<float> bt;
                launchBtMenu(bt);
            });
            stringType.setOnAction([](){
                BinaryTreeLnk<string> bt;
                launchBtMenu(bt);
            });
        });
        structMenu.add(btVec);
        structMenu.add(btLnk);
    });
    MenuItem ex4("Exercise 4 (BST)", [&](){
        MenuItem bst("BST", [&](){
            intType.setOnAction([](){
                BST<int> bt;
                launchBSTMenu(bt);
            });
            floatType.setOnAction([](){
                BST<float> bt;
                launchBSTMenu(bt);
            });
            stringType.setOnAction([](){
                BST<string> bt;
                launchBSTMenu(bt);
            });
        });
        structMenu.add(bst);
    });


    exMenu.add(ex1);
    exMenu.add(ex2);
    exMenu.add(ex3);
    exMenu.add(ex4);
    exMenu.add(fullTest);

    if (exMenu.show())
        if(structMenu.show()){
            typeMenu.add(intType);
            typeMenu.add(floatType);
            typeMenu.add(stringType);
            typeMenu.show();
        }
}

void setupContainerMenu(Menu& menu, Container& cont){
    MenuItem empty("Is Empty", [&cont](){
        testEmpty(cont);
    });
    MenuItem size("Size", [&cont](){
        testSize(cont);
    }) ;

    MenuItem clear("Clear", [&cont](){
        testClear(cont);
    });

    menu.add(empty);
    menu.add(size);
    menu.add(clear);
}
template<typename Data>
void setupLinearContainerMenu(Menu& menu, LinearContainer<Data>& cont){

    MenuItem front("Front", [&cont](){
        testFront(cont);
    });
    MenuItem back("Back", [&cont](){
        testBack(cont);
    });
    MenuItem subscript("Subscript operator []", [&cont](){
        testSubscript(cont);
    });



    menu.add(front);
    menu.add(back);
    menu.add(subscript);

}
template<typename Data>
void setupMappableMenu(Menu& menu, MappableContainer<Data>& cont, const bool addArrow){
    MenuItem printAll("Print all", [&cont, addArrow](){
        printMappable(cont, addArrow);
    });
    MenuItem testMap("Test map function", [&cont](){
        testMappable(cont);
    });
    menu.add(printAll);
    menu.add(testMap);
}
template<typename Data>
void setupFoldableMenu(Menu& menu, FoldableContainer<Data>& cont){
    MenuItem testFold("Test fold function", [&cont](){
        testFoldable(cont);
    });
    menu.add(testFold);
}
template<typename Data>
void setupTestableContainerMenu(Menu& menu, TestableContainer<Data>& cont){
    MenuItem exists("Exists", [&cont](){
        testExists(cont);
    });
    menu.add(exists);
}
template<typename Data, template<typename> class IT>
void setupIteratorMenu(Menu& itMenu, IT<Data>& it, BinaryTree<Data>& bt){
    MenuItem nextIt("Next", [&it]{
        testIteraorNext(it);
    });
    MenuItem acces("operator*", [&it]{
        testIteraorAcces(it);
    });
    MenuItem modify("Modify value", [&it]{
        testModifyBTNode(it);
    });
    MenuItem terminatedIt("Terminated", [&it]{
        testIteraorTerminated(it);
    });
    MenuItem resetIt("Reset", [&it, &bt]{
        resetIterator(it, bt);
    });

    itMenu.add(nextIt);
    itMenu.add(acces);
    itMenu.add(modify);
    itMenu.add(terminatedIt);
    itMenu.add(resetIt);
}

template<typename Data>
void launchVectorMenu(){
    Vector<Data> vec;

    Menu mainMenu("Chose an action:");

    MenuItem insertValues("Insert Values", [&vec](){
        popolaVector(vec);
    });
    mainMenu.add(insertValues);

    setupLinearContainerMenu(mainMenu, vec);
    setupContainerMenu(mainMenu, vec);
    setupTestableContainerMenu(mainMenu, vec);
    setupMappableMenu(mainMenu, vec, false);
    setupFoldableMenu(mainMenu, vec);

    MenuItem resize("Resize", [&vec](){
        testResize(vec);
    });

    mainMenu.add(resize);

    while (mainMenu.show());
}
template<typename Data>
void launchListMenu(){
    List<Data> list;

    Menu mainMenu("Chose an action:");

    MenuItem insertValues("Insert Values", [&list](){
        popolaList(list);
    });
    mainMenu.add(insertValues);

    setupLinearContainerMenu(mainMenu, list);
    setupContainerMenu(mainMenu, list);
    setupTestableContainerMenu(mainMenu, list);
    setupMappableMenu(mainMenu, list, true);
    setupFoldableMenu(mainMenu, list);

    MenuItem insertAtFront("Insert at Front", [&list](){
        testInsertAtFront(list);
    });
    MenuItem removeFromFront("Remove from Front", [&list](){
        testRemoveFromFront(list);
    });
    MenuItem frontNRemove("Front and Remove", [&list](){
        testFrontNRemove(list);
    });
    MenuItem insertAtBack("Insert at Back", [&list](){
        testInsertAtBack(list);
    });

    mainMenu.add(insertAtFront);
    mainMenu.add(removeFromFront);
    mainMenu.add(frontNRemove);
    mainMenu.add(insertAtBack);

    while (mainMenu.show());
}

template<typename Data>
void launchStackMenu(Stack<Data>& stk){
    Menu mainMenu("Chose an action:");

    MenuItem insertValues("Insert Values", [&stk](){
        popolaStack(stk);
    });
    mainMenu.add(insertValues);

    setupContainerMenu(mainMenu, stk);

    MenuItem push("Push", [&stk](){
        testPush(stk);
    });
    MenuItem top("Top", [&stk](){
        testTop(stk);
    });
    MenuItem pop("Pop", [&stk](){
        testPop(stk);
    });
    MenuItem topNPop("Top and Pop", [&stk](){
        testTopNPop(stk);
    });

    mainMenu.add(push);
    mainMenu.add(top);
    mainMenu.add(pop);
    mainMenu.add(topNPop);

    while (mainMenu.show());
}

template<typename Data>
void launchQueueMenu(Queue<Data>& que){
    Menu mainMenu("Chose an action:");

    MenuItem insertValues("Insert Values", [&que](){
        popolaQueue(que);
    });
    mainMenu.add(insertValues);

    setupContainerMenu(mainMenu, que);

    MenuItem enqueue("Enqueue", [&que](){
        testEnqueue(que);
    });
    MenuItem head("Head", [&que](){
        testHead(que);
    });
    MenuItem dequeue("Dequeue", [&que](){
        testDequeue(que);
    });
    MenuItem headNDequeue("Head and Dequeue", [&que](){
        testHeadNDequeue(que);
    });

    mainMenu.add(enqueue);
    mainMenu.add(head);
    mainMenu.add(dequeue);
    mainMenu.add(headNDequeue);

    while (mainMenu.show());
}



template<typename Data, template<typename> class BT>
void launchBtMenu(BT<Data>& bt){
    typename BinaryTree<Data>::Node* node;

    BTInOrderIterator<Data> inIT(bt);
    BTPreOrderIterator<Data> preIT(bt);
    BTPostOrderIterator<Data> postIT(bt);
    BTBreadthIterator<Data> brhIT(bt);


    if (bt.Empty()) node = nullptr;
    else node = &bt.Root();

    Menu mainMenu("Chose an action:");


    MenuItem insertValues("Insert Values", [&](){ // 3 1 1 1 10
        popolaBt(bt);
        if (bt.Empty()) node = nullptr;
        else node = &bt.Root();

        resetIterator(inIT, bt);
        resetIterator(preIT, bt);
        resetIterator(postIT, bt);
        resetIterator(brhIT, bt);
    });
    MenuItem root("Print Root", [&bt](){
        testRoot(bt);
    });

    Menu navigate("Chose an action:");
        MenuItem hasLeft("Has Left Child", [&node](){
            testHasLeftChild<Data>(node);
        });
        MenuItem hasRight("Has Right Child", [&node](){
            testHasRightChild<Data>(node);
        });
        MenuItem isLeaf("Is Leaf", [&node](){
            testIsLeaf<Data>(node);
        });
        MenuItem gotoroot("Goto Root", [&bt, &node](){
            gotoRoot(bt, node);
        });
        MenuItem left("Goto left", [&node](){
            gotoLeft<Data>(node);
        });
        MenuItem right("Goto Right", [&node](){
            gotoRight<Data>(node);
        });
        MenuItem element("Print Element", [&node](){
        testElement<Data>(node);
    });
        MenuItem modElement("Modify Element", [&node]{
            testModifyBTNode<Data>(node);
        });
        navigate.add(hasLeft);
        navigate.add(hasRight);
        navigate.add(isLeaf);
        navigate.add(gotoroot);
        navigate.add(left);
        navigate.add(right);
        navigate.add(element);
        navigate.add(modElement);
    Menu print("Chose an action:");
        MenuItem preOrder("Print PreOrder", [&bt]{
            printPreOrder(bt);
        });
        MenuItem postOrder("Print PostOrder", [&bt]{
            printPostOrder(bt);
        });
        MenuItem inOrder("Print InOrder", [&bt]{
            printInOrder(bt);
        });
        MenuItem breadth("Print Breadth", [&bt]{
            printBreadth(bt);
        });
        print.add(preOrder);
        print.add(postOrder);
        print.add(inOrder);
        print.add(breadth);


    Menu iteratorMenu("Chose an Iterator:");
        Menu preOrderIt("Chose an action");
        Menu postOrderIt("Chose an action");
        Menu inOrderIt("Chose an action");
        Menu breadthIt("Chose an action");
        setupIteratorMenu(preOrderIt, preIT, bt);
        setupIteratorMenu(postOrderIt, postIT, bt);
        setupIteratorMenu(inOrderIt, inIT, bt);
        setupIteratorMenu(breadthIt, brhIT, bt);

        iteratorMenu.add("PreOrder Iterator", preOrderIt, true);
        iteratorMenu.add("PostOrder Iterator", postOrderIt, true);
        iteratorMenu.add("InOrder Iterator", inOrderIt, true);
        iteratorMenu.add("Breadth Iterator", breadthIt, true);


    MenuItem map("Test Map function", [&bt]{
        testMappableBT(bt);
    });
    MenuItem fold("Test Fold function", [&bt]{
        testFoldable(bt);
    });

    mainMenu.add(insertValues);
    setupContainerMenu(mainMenu, bt);
    mainMenu.add(root);

    mainMenu.add("Navigate the Tree", navigate, true);
    mainMenu.add("Print", print, false);
    mainMenu.add("Iterators", iteratorMenu, true);


    mainMenu.add(map);
    mainMenu.add(fold);

    mainMenu.loop([&]{
        if (bt.Empty()) {
            node = nullptr;
            resetIterator(inIT, bt);
            resetIterator(preIT, bt);
            resetIterator(postIT, bt);
            resetIterator(brhIT, bt);
        }
    });

}

template<typename Data>
void launchBSTMenu(BST<Data>& bt){
    typename BinaryTree<Data>::Node* node;

    if (bt.Empty()) node = nullptr;
    else node = &bt.Root();

    Menu mainMenu("Chose an action:");


    MenuItem insertValues("Insert Values", [&](){ // 3 1 1 1 10
        popolaBt(bt);
        if (bt.Empty()) node = nullptr;
        else node = &bt.Root();
    });
    MenuItem root("Print Root", [&bt](){
        testRoot(bt);
    });

    Menu navigate("Chose an action:");
    MenuItem hasLeft("Has Left Child", [&node](){
        testHasLeftChild<Data>(node);
    });
    MenuItem hasRight("Has Right Child", [&node](){
        testHasRightChild<Data>(node);
    });
    MenuItem isLeaf("Is Leaf", [&node](){
        testIsLeaf<Data>(node);
    });
    MenuItem gotoroot("Goto Root", [&bt, &node](){
        gotoRoot(bt, node);
    });
    MenuItem left("Goto left", [&node](){
        gotoLeft<Data>(node);
    });
    MenuItem right("Goto Right", [&node](){
        gotoRight<Data>(node);
    });
    MenuItem element("Print Element", [&node](){
        testElement<Data>(node);
    });
    MenuItem modElement("Modify Element", [&node]{
        testModifyBTNode<Data>(node);
    });
    navigate.add(hasLeft);
    navigate.add(hasRight);
    navigate.add(isLeaf);
    navigate.add(gotoroot);
    navigate.add(left);
    navigate.add(right);
    navigate.add(element);
    navigate.add(modElement);
    Menu print("Chose an action:");
    MenuItem preOrder("Print PreOrder", [&bt]{
        printPreOrder(bt);
    });
    MenuItem postOrder("Print PostOrder", [&bt]{
        printPostOrder(bt);
    });
    MenuItem inOrder("Print InOrder", [&bt]{
        printInOrder(bt);
    });
    MenuItem breadth("Print Breadth", [&bt]{
        printBreadth(bt);
    });
    print.add(preOrder);
    print.add(postOrder);
    print.add(inOrder);
    print.add(breadth);


    MenuItem map("Test Map function", [&bt]{
        testMappableBT(bt);
    });
    MenuItem fold("Test Fold function", [&bt]{
        testFoldable(bt);
    });

    mainMenu.add(insertValues);
    setupContainerMenu(mainMenu, bt);
    mainMenu.add(root);

    mainMenu.add("Navigate the Tree", navigate, true);
    mainMenu.add("Print", print, false);

    mainMenu.add(map);
    mainMenu.add(fold);

    Menu bstMenu("Chose an action");
        MenuItem insert("Insert", [&bt]{ testInsert(bt); });
        MenuItem remove("Remove", [&bt]{ testRemove(bt); });
        MenuItem min("Min", [&bt]{ testMin(bt); });
        MenuItem removeMin("Remove Min", [&bt]{ testRemoveMin(bt); });
        MenuItem max("Max", [&bt]{ testMax(bt); });
        MenuItem removeMax("Remove Max", [&bt]{ testRemoveMax(bt); });
        MenuItem predecessor("Predecessor", [&bt]{ testPredecessor(bt); });
        MenuItem removePredecessor("Remove Predecessor", [&bt]{ testRemovePredecessor(bt); });
        MenuItem successor("Successor", [&bt]{ testSuccessor(bt); });
        MenuItem removeSuccessor("Remove Successor", [&bt]{ testRemoveSuccessor(bt); });
        bstMenu.add(insert);
        bstMenu.add(remove);
        bstMenu.add(min);
        bstMenu.add(removeMin);
        bstMenu.add(max);
        bstMenu.add(removeMax);
        bstMenu.add(predecessor);
        bstMenu.add(removePredecessor);
        bstMenu.add(successor);
        bstMenu.add(removeSuccessor);

    mainMenu.add("BST functions", bstMenu, true);

    mainMenu.loop([&]{
        if (bt.Empty()) {
            node = nullptr;
        }
    });
}

/* *** Random generation *** */
default_random_engine gen(random_device{}());


/* *** Container test *** */

void testEmpty(Container& cont) {
    cout << "Container is" << ((cont.Empty())? "": " not") << " Empty. Size = " << cont.Size() << endl;
}
void testSize(Container& cont) {
    cout << "Size is: " << cont.Size() << endl;
}
void testClear(Container& cont) {
    cont.Clear();
    cout << "Container is clear. Size = " << cont.Size() << ". Is Empty? " << ((cont.Empty())? "True": "False") << endl;
}

/* *** Linear Container test *** */
template<typename Data>
void testFront(LinearContainer<Data>& cont) {
    try {
        cout << "Front value: " << cont.Front() << endl;
    } catch (length_error& e){
        cout << "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testBack(LinearContainer<Data>& cont) {
    try {
    cout << "Back value: " << cont.Back() << endl;
    } catch (length_error& e){
        cout << "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testSubscript(LinearContainer<Data>& cont) {
    unsigned long in = 0;
    cout << "Insert the index (0 <= index < " << cont.Size() << ")" << endl << ">>> ";
    cin >> in;
    try {
        cout << "Container[" << in << "] = " << cont[in] << endl;
    } catch (out_of_range& e){
        cout << "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testExists(TestableContainer<Data>& cont) {
    Data in;
    cout << "Insert the value to search" << endl << ">>> ";
    cin >> in;
    cout << "Value " << in << ((cont.Exists(in))? "": " doesn't") << " belong to container" << endl;
}

/* *** Vector test *** */

void popolaVector(Vector<int>& vec) {
    unsigned long newSize = 0;
    cout << "Insert new Size" << endl << ">>> ";
    cin >> newSize;
    vec.Resize(newSize);
    uniform_int_distribution<int> distr(0, 100);
    for (unsigned long i = 0; i < vec.Size(); i++) {
        vec[i] = distr(gen);
    }
}

void popolaVector(Vector<float>& vec) {
    unsigned long newSize = 0;
    cout << "Insert new Size" << endl << ">>> ";
    cin >> newSize;
    vec.Resize(newSize);
    uniform_int_distribution<int> intDistr(-10000, 10000); // parte intera
    uniform_int_distribution<int> decDistr(0, 99); // parte decimale
    for (unsigned long i = 0; i < vec.Size(); i++) {
        int intVal = intDistr(gen);
        vec[i] = intVal + (decDistr(gen) * ((intVal < 0)? (-0.01): (0.01)));
    }
}

void popolaVector(Vector<string>& vec) {
    unsigned long newSize = 0;
    const string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!:.;-_#*@";
    cout << "Insert new Size" << endl << ">>> ";
    cin >> newSize;
    vec.Resize(newSize);
    uniform_int_distribution<unsigned int> distr(0, charset.size()-1);
    uniform_int_distribution<unsigned int> size(0, 15);

    string str;
    for (unsigned long i = 0; i < vec.Size(); i++) {
        str = "";
        unsigned int s = size(gen);
        for (unsigned int j = 0; j < s; ++j) {
            str += charset[distr(gen)];
        }
        vec[i] = str;
    }
}
template<typename Data>
void testResize(Vector<Data>& vec){
    unsigned long in = 0;
    cout << "Insert new Size" << endl << ">>> ";
    cin >> in;
    vec.Resize(in);
    cout << "New size is " << vec.Size() << endl;
}


/* *** List test *** */
void popolaList(List<int>& list){
    list.Clear();
    unsigned long newSize = 0;
    cout << "Insert new Size" << endl << ">>> ";
    cin >> newSize;
    uniform_int_distribution<int> distr(-10000, 10000);
    for (unsigned long i = 0; i < newSize; ++i) {
        list.InsertAtFront(distr(gen));
    }
}
void popolaList(List<float>& list){
    list.Clear();
    unsigned long newSize = 0;
    cout << "Insert new Size" << endl << ">>> ";
    cin >> newSize;
    uniform_int_distribution<int> intDistr(-10000, 10000); // parte intera
    uniform_int_distribution<int> decDistr(0, 99); // parte decimale
    for (unsigned long i = 0; i < newSize; ++i) {
        int intVal = intDistr(gen);
        list.InsertAtFront(intVal + (decDistr(gen) * ((intVal < 0)? (-0.01): (0.01))));
    }
}
void popolaList(List<string>& list){
    list.Clear();
    unsigned long newSize = 0;
    cout << "Insert new Size" << endl << ">>> ";
    cin >> newSize;
    const string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!:.;-_#*@";
    uniform_int_distribution<unsigned int> distr(0, charset.size()-1);
    uniform_int_distribution<unsigned int> size(0, 15);
    for (unsigned long i = 0; i < newSize; i++) {
        string str = "";
        unsigned int s = size(gen);
        for (unsigned int j = 0; j < s; ++j) {
            str += charset[distr(gen)];
        }
        list.InsertAtFront(str);
    }
}

template<typename Data>
void testInsertAtFront(List<Data>& list){
    Data tmp;
    cout << "Insert the new value" << endl << ">>> ";
    cin >> tmp;
    list.InsertAtFront(tmp);
}
template<typename Data>
void testRemoveFromFront(List<Data>& list){
    try{
        list.RemoveFromFront();
        cout << "Front value removed" << endl;
    } catch (length_error& e){
        cout << "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testFrontNRemove(List<Data>& list){
    try{
        Data data = list.FrontNRemove();
        cout << "Front value removed: " << data << endl;
    } catch (length_error& e){
        cout << "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testInsertAtBack(List<Data>& list){
    Data tmp;
    cout << "Insert the new value" << endl << ">>> ";
    cin >> tmp;
    list.InsertAtBack(tmp);
}

/* *** Mappable test *** */
template<typename Data>
void printMappable(MappableContainer<Data>& cont, bool addArrow){
    cont.MapPreOrder([](Data& i, void* arrow){
        cout << i << ((*((bool*)arrow))? " -> ": " ");
    }, &addArrow);
    if (addArrow) {
        cout << "nullptr";
    }
    cout << endl;
}

void testMappable(MappableContainer<int>& cont){
    cont.MapPreOrder([](int& data, void* _){ data *= 2; }, nullptr);
    cout << "Function n -> 2n applied to all elements" << endl;
}
void testMappable(MappableContainer<float>& cont){
    cont.MapPreOrder([](float & data, void* _){ data *= data; }, nullptr);
    cout << "Function n -> n*n applied to all elements" << endl;
}
void testMappable(MappableContainer<string>& cont){
    cont.MapPreOrder([](string & data, void* _){
        for (char& c : data) {
            c = toupper(c);
        }
        }, nullptr);
    cout << "Function n -> uppercase(n) applied to all elements" << endl;
}

/* *** Foldable test *** */
void testFoldable(FoldableContainer<int>& cont){
    int sum = 0;
    int n;
    cout <<"Insert n(int):" << ">>> ";
    cin >> n;
    cont.FoldPreOrder([](const int& data, const void* n, void* sum){
        if (data < *((int*)n)){
            *((int*)sum) += data;
        }
        }, &n, &sum);
    cout << "Sum of integer (less than " << n << "): " << sum << endl;
}
void testFoldable(FoldableContainer<float>& cont){
    int prod = 1;
    float n;
    cout <<"Insert n(float):" << ">>> ";
    cin >> n;
    cont.FoldPreOrder([](const float& data, const void* n, void* prod){
        if (data > *((float*)n)){
            *((float*)prod) *= data;
        }
    }, &n, &prod);
    cout << "Product of float (greater than " << n << "): " << prod << endl;
}
void testFoldable(FoldableContainer<string>& cont){
    string str = "";
    int n;
    cout <<"Insert n(int):" << ">>> ";
    cin >> n;
    cont.FoldPreOrder([](const string& data, const void* n, void* str){
        if (data.size() <= *((int*)n)){
            *((string*)str) += data;
        }
    }, &n, &str);
    cout << "Concatenation of strings (with size less or equal than " << n << "): " << str << endl;
}

/* *** Stack test *** */
void popolaStack(Stack<int>& stk){
    stk.Clear();
    unsigned long newSize = 0;
    cout << "Insert new Size" << endl << ">>> ";
    cin >> newSize;
    uniform_int_distribution<int> distr(-10000, 10000);
    for (unsigned long i = 0; i < newSize; ++i) {
        stk.Push(distr(gen));
    }
}
void popolaStack(Stack<float>& stk){
    stk.Clear();
    unsigned long newSize = 0;
    cout << "Insert new Size" << endl << ">>> ";
    cin >> newSize;
    uniform_int_distribution<int> intDistr(-10000, 10000); // parte intera
    uniform_int_distribution<int> decDistr(0, 99); // parte decimale
    for (unsigned long i = 0; i < newSize; ++i) {
        int intVal = intDistr(gen);
        stk.Push(intVal + (decDistr(gen) * ((intVal < 0)? (-0.01): (0.01))));
    }
}
void popolaStack(Stack<string>& stk){
    stk.Clear();
    unsigned long newSize = 0;
    cout << "Insert new Size" << endl << ">>> ";
    cin >> newSize;
    const string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!:.;-_#*@";
    uniform_int_distribution<unsigned int> distr(0, charset.size()-1);
    uniform_int_distribution<unsigned int> size(0, 15);
    for (unsigned long i = 0; i < newSize; i++) {
        string str = "";
        unsigned int s = size(gen);
        for (unsigned int j = 0; j < s; ++j) {
            str += charset[distr(gen)];
        }
        stk.Push(str);
    }
}

template<typename Data>
void testPush(Stack<Data>& stk){
    Data value;
    cout<< "Insert value to Push" << endl << ">>> ";
    cin >> value;
    stk.Push(value);
}
template<typename Data>
void testTop(Stack<Data>& stk){
    try {
        cout<< "Top value: " << stk.Top() << endl;
    } catch (length_error& e){
        cout<< "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testPop(Stack<Data>& stk){
    try {
        stk.Pop();
        cout<< "Pop value on top" << endl;
    } catch (length_error& e){
        cout<< "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testTopNPop(Stack<Data>& stk){
    try {
        cout<< "Pop value on top: "<< stk.TopNPop() << endl;
    } catch (length_error& e){
        cout<< "Error: " << e.what() << endl;
    }
}


/* *** Queue test *** */
void popolaQueue(Queue<int>& que){
    que.Clear();
    unsigned long newSize = 0;
    cout << "Insert new Size" << endl << ">>> ";
    cin >> newSize;
    uniform_int_distribution<int> distr(-10000, 10000);
    for (unsigned long i = 0; i < newSize; ++i) {
        que.Enqueue(distr(gen));
    }
}
void popolaQueue(Queue<float>& que){
    que.Clear();
    unsigned long newSize = 0;
    cout << "Insert new Size" << endl << ">>> ";
    cin >> newSize;
    uniform_int_distribution<int> intDistr(-10000, 10000); // parte intera
    uniform_int_distribution<int> decDistr(0, 99); // parte decimale
    for (unsigned long i = 0; i < newSize; ++i) {
        int intVal = intDistr(gen);
        que.Enqueue(intVal + (decDistr(gen) * ((intVal < 0)? (-0.01): (0.01))));
    }
}
void popolaQueue(Queue<string>& que){
    que.Clear();
    unsigned long newSize = 0;
    cout << "Insert new Size" << endl << ">>> ";
    cin >> newSize;
    const string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!:.;-_#*@";
    uniform_int_distribution<unsigned int> distr(0, charset.size()-1);
    uniform_int_distribution<unsigned int> size(0, 15);
    for (unsigned long i = 0; i < newSize; i++) {
        string str = "";
        unsigned int s = size(gen);
        for (unsigned int j = 0; j < s; ++j) {
            str += charset[distr(gen)];
        }
        que.Enqueue(str);
    }
}

template<typename Data>
void testEnqueue(Queue<Data>& que){
    Data value;
    cout<< "Insert value to Enqueue" << endl << ">>> ";
    cin >> value;
    que.Enqueue(value);
}
template<typename Data>
void testHead(Queue<Data>& que){
    try {
        cout<< "Head value: " << que.Head() << endl;
    } catch (length_error& e){
        cout<< "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testDequeue(Queue<Data>& que){
    try {
        que.Dequeue();
        cout<< "Dequeue value on Top" << endl;
    } catch (length_error& e){
        cout<< "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testHeadNDequeue(Queue<Data>& que){
    try {
        cout<< "Dequeue value on top: "<< que.HeadNDequeue() << endl;
    } catch (length_error& e){
        cout<< "Error: " << e.what() << endl;
    }
}

/* *** BinaryTree test *** */

template<typename Data, template<typename> class BT>
void popolaBt(BT<Data>& bt){
    Vector<Data> v;
    popolaVector(v);
    BT<Data> btTemp(v);
    bt = btTemp;
}

template<typename Data>
void printPreOrder(MappableContainer<Data>& mc){
    cout<<"PreOrder: ";
    mc.MapPreOrder([](Data& data, void*){
        cout<< data << " ";
    }, nullptr);
    cout<< endl;
}

template<typename Data>
void printPostOrder(MappableContainer<Data>& mc){
    cout<<"PostOrder: ";
    mc.MapPostOrder([](Data& data, void*){
        cout<< data << " ";
    }, nullptr);
    cout<< endl;
}
template<typename Data>
void printInOrder(InOrderMappableContainer<Data>& mc){
    cout<<"InOrder: ";
    mc.MapInOrder([](Data& data, void*){
        cout<< data << " ";
    }, nullptr);
    cout<< endl;
}
template<typename Data>
void printBreadth(BreadthMappableContainer<Data>& mc){
    cout<<"Breadth: ";
    mc.MapBreadth([](Data& data, void*){
        cout<< data << " ";
    }, nullptr);
    cout<< endl;
}

void testMappableBT(MappableContainer<int>& mc){
    mc.MapPreOrder([](int& data, void*){ data *= 3; }, nullptr);
    cout << "Function n -> 3n applied to all elements" << endl;
}
void testMappableBT(MappableContainer<float>& mc){
    mc.MapPreOrder([](float & data, void*){ data = data*data*data; }, nullptr);
    cout << "Function n -> n*n*n applied to all elements" << endl;
}
void testMappableBT(MappableContainer<string>& mc){
    string str;
    cout<<"Insert string to concat:" << endl << ">>> ";
    cin>>str;
    mc.MapPreOrder([](string& data, void* str){ data = *static_cast<string*>(str)+data; }, &str);
}


template<typename Data>
void gotoRight(typename BinaryTree<Data>::Node*& node){
    try {
        if (node == nullptr) cout<< "Binary Tree is Empty" << endl;
        else {
            node = &node->RightChild();
            cout << "Node is set to Right child. Element: " << node->Element() << endl;
        }
    } catch (out_of_range& e){
        cout<<"Error: " << e.what() << endl;
    }
}
template<typename Data>
void gotoLeft(typename BinaryTree<Data>::Node*& node){
    try {
        if (node == nullptr) cout<< "Binary Tree is Empty" << endl;
        else {
            node = &node->LeftChild();
            cout << "Node is set to Left child. Element: " << node->Element() << endl;
        }
    } catch (out_of_range& e){
        cout<<"Error: " << e.what() << endl;
    }
}
template<typename Data>
void gotoRoot(const BinaryTree<Data>& bt, typename BinaryTree<Data>::Node*& node){
    try {
        node = &bt.Root();
        cout<<"Node is set to Root. Element: " << node->Element() << endl;
    } catch (length_error& e){
        cout<<"Error: " << e.what() << endl;
    }
}

template<typename Data>
void testRoot(BinaryTree<Data>& bt){
    try {
        cout<<"Root: " << bt.Root().Element() << endl;
    } catch (length_error& e){
        cout<<"Error: " << e.what() << endl;
    }
}

template<typename Data>
void testIsLeaf(typename BinaryTree<Data>::Node* node){
    if (node == nullptr) cout<< "Binary Tree is Empty" << endl;
    else
        cout<< "Node is " << ((node->IsLeaf())? "": "not ") << "a leaf" << endl;
}
template<typename Data>
void testHasLeftChild(typename BinaryTree<Data>::Node* node){
    if (node == nullptr) cout<< "Binary Tree is Empty" << endl;
    else
        cout<< "Node has " << ((node->HasLeftChild())? "": "not ") << "Left Child" << endl;
}
template<typename Data>
void testHasRightChild(typename BinaryTree<Data>::Node* node){
    if (node == nullptr) cout<< "Binary Tree is Empty" << endl;
    else
        cout<< "Node has " << ((node->HasRightChild())? "": "not ") << "Right Child" << endl;
}
template<typename Data>
void testElement(typename BinaryTree<Data>::Node* node){
    if (node == nullptr) cout<< "Binary Tree is Empty" << endl;
    else
        cout<< "Element: "<< node->Element() << endl;
}
template<typename Data>
void testModifyBTNode(typename BinaryTree<Data>::Node* node){
    try {
        cout<< "Insert new Value" << endl << ">>> ";
        cin>> node->Element();
    } catch (...){
        cout<< "Error" << endl;
    }
}
template<typename Data>
void testModifyBTNode(ForwardIterator<Data>& it){
    try {
        cout << "Insert new Value" << endl << ">>> ";
        cin >> (*it);
    } catch (out_of_range& e){
        cout<< "Error: " << e.what() << endl;
    }
}

/* *** Iterator test *** */

template<typename Data>
void testIteraorNext(ForwardIterator<Data>& it){
    try {
        ++it;
        cout<< "Next Element: " << *it << endl;
    } catch (out_of_range& e){
        cout<< "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testIteraorAcces(ForwardIterator<Data>& it){
    try {
        cout<< "Element: " << *it << endl;
    } catch (out_of_range& e){
        cout<< "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testIteraorTerminated(ForwardIterator<Data>& it){
    cout<< "Iterator is " << (it.Terminated()? "": "not ") << "Terminated" << endl;
}

template<typename Data, template<typename> class IT>
void resetIterator(IT<Data>& it, BinaryTree<Data>& bt){
    IT<Data> tmp(bt);
    it = tmp;
}

/* *** BST test *** */

template<typename Data>
void testInsert(BST<Data>& bst){
    Data data;
    cout<< "Insert new value" << endl << ">>> ";
    cin>> data;
    bst.Insert(data);
}
template<typename Data>
void testRemove(BST<Data>& bst){
    Data data;
    cout<< "Insert value to remove" << endl << ">>> ";
    cin>> data;
    if (!bst.Exists(data)) cout<< "\"" << data << "\" does not Exists" << endl;
    else {
        bst.Remove(data);
        cout<< "Value: \"" << data << "\" Removed" << endl;
    }
}
template<typename Data>
void testMin(BST<Data>& bst){
    try {
        cout<< "Min: " << bst.Min() << endl;
    } catch (length_error& e){
        cout<< "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testRemoveMin(BST<Data>& bst){
    try {
        cout<< "Min \"" << bst.MinNRemove() << "\" Removed" << endl;
    } catch (length_error& e){
        cout<< "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testMax(BST<Data>& bst){
    try {
        cout<< "Max: " << bst.Max() << endl;
    } catch (length_error& e){
        cout<< "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testRemoveMax(BST<Data>& bst){
    try {
        cout<< "Max \"" << bst.MaxNRemove() << "\" Removed" << endl;
    } catch (length_error& e){
        cout<< "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testPredecessor(BST<Data>& bst){
    Data data;
    cout<< "Insert value: " << endl << ">>> ";
    cin>> data;
    try {
        cout<< "Predecessor of " << data <<": " << bst.Predecessor(data) << endl;
    } catch (length_error& e){
        cout<< "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testRemovePredecessor(BST<Data>& bst){
    Data data;
    cout<< "Insert value: " << endl << ">>> ";
    cin>> data;
    try {
        cout<< "Predecessor of " << data <<": " << bst.PredecessorNRemove(data) << " Removed" << endl;
    } catch (length_error& e){
        cout<< "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testSuccessor(BST<Data>& bst){
    Data data;
    cout<< "Insert value: " << endl << ">>> ";
    cin>> data;
    try {
        cout<< "Successor of " << data <<": " << bst.Successor(data) << endl;
    } catch (length_error& e){
        cout<< "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testRemoveSuccessor(BST<Data>& bst){
    Data data;
    cout<< "Insert value: " << endl << ">>> ";
    cin>> data;
    try {
        cout<< "Successor of " << data <<": " << bst.SuccessorNRemove(data) << " Removed" << endl;
    } catch (length_error& e){
        cout<< "Error: " << e.what() << endl;
    }
}