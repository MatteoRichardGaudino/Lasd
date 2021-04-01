#include "test.hpp"

using namespace std;

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
void Menu::add(MenuItem&& item) noexcept{
    items.InsertAtBack(move(item));
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
/*
void launchMenu(){
    Menu structMenu("Chose a data structure:");

    Menu mainMenu("Chose an action:");

    MenuItem insertValues("Insert Values");
    MenuItem front("Front");
    MenuItem back("Back");
    MenuItem subscript("Subscript operator []");
    MenuItem exists("Exists");
    MenuItem empty("Is Empty");
    MenuItem size("Size") ;
    MenuItem printAll("Print all");
    MenuItem clear("Clear");
    MenuItem testFold("Test fold function");
    MenuItem testMap("Test map function");
    MenuItem fullTest("Start lasd full tes", [](Vector<int>&){
        lasdtest();
    });

    Vector<int> vec;
    MenuItem vect("Vector", [&](Vector<int>&){
        Menu typeMenu("Chose a type:");
        MenuItem resize("Resize");
        mainMenu.add(resize);


        MenuItem intType("Int", [&](Vector<int> vec){
            cout<< "Test size: " << vec.Size();
            insertValues.setOnAction([](Vector<int>& vec){ popolaVector<int>(vec); });
            front.setOnAction([](Vector<int>& vec){ cout << vec.Front() << endl; });
            back.setOnAction([](Vector<int>& vec){ cout << vec.Back() << endl; });

            subscript.setOnAction([](Vector<int>& vec){
                unsigned long in = 0;
                cout << "Insert the index (0 <= index < " << vec.Size() << ")" << endl << ">>> ";
                cin >> in;
                try {
                    cout << "vec[" << in << "] = " << vec[in];
                } catch (out_of_range& e){
                    cout << "Error, Out of range" << endl;
                }
            });
            exists.setOnAction([](Vector<int>& vec){
                int in = 0;
                cout << "Insert the value to search" << endl << ">>> ";
                cin >> in;
                cout << "Value " << in << ((vec.Exists(in))? "": " doesn't") << " Exist in vec" << endl;
            });
            empty.setOnAction([](Vector<int>& vec){ cout << ((vec.Empty())? "True": "False") << endl; });
            size.setOnAction([](Vector<int>& vec){ cout << "Size is: " << vec.Size() << endl; });
            printAll.setOnAction([](Vector<int>& vec){ printMappable<int>(vec, false); });
            clear.setOnAction([](Vector<int>& vec){
                vec.Clear();
                cout << "Cleaning the vector" << endl;
            });
            testFold.setOnAction([](Vector<int>& vec){
                // todo
            });
            testMap.setOnAction([](Vector<int>& vec){
                // todo
            });
            resize.setOnAction([](Vector<int>& vec){
                unsigned long in = 0;
                cout << "Insert new Size" << endl << ">>> ";
                cin >> in;
                vec.Resize(in);
                cout << "New size is " << vec.Size() << endl;
            });
        });
        MenuItem floatType("Float", [](Vector<int>& vec){cout << "hai scelto float...";});
        MenuItem stringType("String", [](Vector<int>& vec){cout << "hai scelto string...";});

        typeMenu.add(intType);
        typeMenu.add(floatType);
        typeMenu.add(stringType);
        typeMenu.show(vec);


        mainMenu.add(insertValues);
        mainMenu.add(front);
        mainMenu.add(back);
        mainMenu.add(subscript);
        mainMenu.add(move(exists));
        mainMenu.add(empty);
        mainMenu.add(size);
        mainMenu.add(printAll);
        mainMenu.add(clear);
        mainMenu.add(testFold);
        mainMenu.add(testMap);
        mainMenu.add(fullTest);
        mainMenu.show(vec);
    });

    MenuItem list("List", [](Vector<int>& vec){
        cout<< "hai scelto list"<< endl;
    });

    structMenu.add(vect);
    structMenu.add(list);
    structMenu.show(vec);
}
 */

void launchMenu(){
    Menu structMenu("Chose a data structure:");
    Menu typeMenu("Chose a type:");

    MenuItem intType("Int");
    MenuItem floatType("Float");
    MenuItem stringType("String");

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
    structMenu.show();

    typeMenu.add(intType);
    typeMenu.add(floatType);
    typeMenu.add(stringType);
    typeMenu.show();
}

template<typename Data>
void launchVectorMenu(){
    Vector<Data> vec;

    Menu mainMenu("Chose an action:");

    MenuItem insertValues("Insert Values", [&vec](){
        popolaVector<Data>(vec);
    });
    MenuItem front("Front", [&vec](){
        testFront(vec);
    });
    MenuItem back("Back", [&vec](){
        testBack(vec);
    });
    MenuItem subscript("Subscript operator []", [&vec](){
        testSubscript(vec);
    });
    MenuItem exists("Exists", [&vec](){
        testExists(vec);
    });
    MenuItem empty("Is Empty", [&vec](){
        testEmpty(vec);
    });
    MenuItem size("Size", [&vec](){
        testSize(vec);
    }) ;
    MenuItem printAll("Print all", [&vec](){
        printMappable(vec, false);
    });
    MenuItem clear("Clear", [&vec](){
        testClear(vec);
    });
    MenuItem testFold("Test fold function", [&vec](){
        // TODO
    });
    MenuItem testMap("Test map function", [&vec](){
        // TODO
    });
    MenuItem fullTest("Start lasd full tes", [](){
        lasdtest();
    });

    MenuItem resize("Resize", [&vec](){
        testResize(vec);
    });

    mainMenu.add(insertValues);
    mainMenu.add(front);
    mainMenu.add(back);
    mainMenu.add(subscript);
    mainMenu.add(move(exists));
    mainMenu.add(empty);
    mainMenu.add(size);
    mainMenu.add(printAll);
    mainMenu.add(clear);
    mainMenu.add(testFold);
    mainMenu.add(testMap);
    mainMenu.add(fullTest);
    mainMenu.add(resize);

    while (mainMenu.show());
}

template<typename Data>
void launchListMenu(){
    List<Data> list;

    Menu mainMenu("Chose an action:");

    MenuItem insertValues("Insert Values", [&list](){
        popolaList<Data>(list);
    });
    MenuItem front("Front", [&list](){
        testFront(list);
    });
    MenuItem back("Back", [&list](){
        testBack(list);
    });
    MenuItem subscript("Subscript operator []", [&list](){
        testSubscript(list);
    });
    MenuItem exists("Exists", [&list](){
        testExists(list);
    });
    MenuItem empty("Is Empty", [&list](){
        testEmpty(list);
    });
    MenuItem size("Size", [&list](){
        testSize(list);
    }) ;
    MenuItem printAll("Print all", [&list](){
        printMappable(list, true);
    });
    MenuItem clear("Clear", [&list](){
        testClear(list);
    });
    MenuItem testFold("Test fold function", [&list](){
        // TODO
    });
    MenuItem testMap("Test map function", [&list](){
        // TODO
    });
    MenuItem fullTest("Start lasd full tes", [](){
        lasdtest();
    });

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

    mainMenu.add(insertValues);
    mainMenu.add(front);
    mainMenu.add(back);
    mainMenu.add(subscript);
    mainMenu.add(move(exists));
    mainMenu.add(empty);
    mainMenu.add(size);
    mainMenu.add(printAll);
    mainMenu.add(clear);
    mainMenu.add(testFold);
    mainMenu.add(testMap);
    mainMenu.add(fullTest);

    mainMenu.add(insertAtFront);
    mainMenu.add(removeFromFront);
    mainMenu.add(frontNRemove);
    mainMenu.add(insertAtBack);

    while (mainMenu.show());
}


template<typename Data>
void popolaVector(Vector<Data> & vec){
    unsigned long newSize = 0;
    cout << "Insert new Size" << endl << ">>> ";
    cin >> newSize;
    vec.Resize(newSize);
    for (unsigned long i = 0; i < newSize; ++i) {
        cout << "[" << i << "] = ";
        cin >> vec[i];
    }
}

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
template<typename Data>
void testEmpty(LinearContainer<Data>& cont) {
    cout << "Container is" << ((cont.Empty())? "": " not") << " Empty. Size = " << cont.Size() << endl;
}
template<typename Data>
void testSize(LinearContainer<Data>& cont) {
    cout << "Size is: " << cont.Size() << endl;
}
template<typename Data>
void testClear(LinearContainer<Data>& cont) {
    cont.Clear();
    cout << "Container is clear. Size = " << cont.Size() << ". Is Empty? " << ((cont.Empty())? "True": "False") << endl;
}
template<typename Data>
void testResize(Vector<Data>& vec){
    unsigned long in = 0;
    cout << "Insert new Size" << endl << ">>> ";
    cin >> in;
    vec.Resize(in);
    cout << "New size is " << vec.Size() << endl;
}



template<typename Data>
void popolaList(List<Data>& list){
    list.Clear();
    unsigned long newSize = 0;
    Data tmp;
    cout << "Insert new Size" << endl << ">>> ";
    cin >> newSize;
    for (unsigned long i = 0; i < newSize; ++i) {
        cout << "[" << i << "] = ";
        cin >> tmp;
        list.InsertAtBack(tmp);
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




