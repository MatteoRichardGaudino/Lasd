#include "test.hpp"
#include <random>

using namespace std;

MenuItem::MenuItem(const string& label, function<void()> onAction){
    text = label;
    action = std::move(onAction);
}
MenuItem::MenuItem(const string & label){
    text = label;
    action = [](){};
}
void MenuItem::run(){
    action();
}

void MenuItem::setOnAction(function<void(void)> fun){
    action = std::move(fun);
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

void launchMenu(){
    Menu structMenu("Chose a data structure or Launch lasd full test:");
    Menu typeMenu("Chose a type:");

    MenuItem intType("Int");
    MenuItem floatType("Float");
    MenuItem stringType("String");

    MenuItem fullTest("Start lasd full test", [](){
        lasdtest();
        exit(0);
    });

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
    structMenu.add(fullTest);

    if(structMenu.show()){
        typeMenu.add(intType);
        typeMenu.add(floatType);
        typeMenu.add(stringType);
        typeMenu.show();
    }
}

template<typename Data>
void setupContainerMenu(Menu& menu, LinearContainer<Data>& cont){

    MenuItem front("Front", [&cont](){
        testFront(cont);
    });
    MenuItem back("Back", [&cont](){
        testBack(cont);
    });
    MenuItem subscript("Subscript operator []", [&cont](){
        testSubscript(cont);
    });

    MenuItem empty("Is Empty", [&cont](){
        testEmpty(cont);
    });
    MenuItem size("Size", [&cont](){
        testSize(cont);
    }) ;

    MenuItem clear("Clear", [&cont](){
        testClear(cont);
    });

    menu.add(front);
    menu.add(back);
    menu.add(subscript);
    menu.add(empty);
    menu.add(size);
    menu.add(clear);
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

template<typename Data>
void launchVectorMenu(){
    Vector<Data> vec;

    Menu mainMenu("Chose an action:");

    MenuItem insertValues("Insert Values", [&vec](){
        popolaVector(vec);
    });
    mainMenu.add(insertValues);

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

default_random_engine gen(random_device{}());

/* *** Container test *** */
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


/* *** Vector test *** */

void popolaVector(Vector<int> & vec) {
    unsigned long newSize = 0;
    cout << "Insert new Size" << endl << ">>> ";
    cin >> newSize;
    vec.Resize(newSize);
    uniform_int_distribution<int> distr(-10000, 10000);
    for (unsigned long i = 0; i < vec.Size(); i++) {
        vec[i] = distr(gen);
    }
}

void popolaVector(Vector<float> & vec) {
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

void popolaVector(Vector<string> & vec) {
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
        list.InsertAtFront(move(str));
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







