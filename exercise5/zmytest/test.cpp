#include "test.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../matrix/vec/matrixvec.hpp"
#include "../matrix/csr/matrixcsr.hpp"
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
    Menu structMenu("Chose a data structure");
    Menu typeMenu("Chose a type:");

    MenuItem intType("Int");
    MenuItem floatType("Float");
    MenuItem stringType("String");

    MenuItem fullTest("Start lasd full test", [](){
        lasdtest();
        exit(0);
    });
    MenuItem stressTest("Start my Stress test", [](){
        myStressTest();
        exit(0);
    });

    MenuItem matrVec("MatrixVec", [&](){
        intType.setOnAction([](){
            MatrixVec<int> mx;
            launchMatrixMenu(mx);
        });
        floatType.setOnAction([](){
            MatrixVec<float> mx;
            launchMatrixMenu(mx);
        });
        stringType.setOnAction([](){
            MatrixVec<string> mx;
            launchMatrixMenu(mx);
        });
    });
    MenuItem matrCsr("MatrixCSR", [&](){
        intType.setOnAction([](){
            MatrixCSR<int> mx;
            launchMatrixMenu(mx);
        });
        floatType.setOnAction([](){
            MatrixCSR<float> mx;
            launchMatrixMenu(mx);
        });
        stringType.setOnAction([](){
            MatrixCSR<string> mx;
            launchMatrixMenu(mx);
        });
    });
    structMenu.add(matrVec);
    structMenu.add(matrCsr);
    structMenu.add(fullTest);
    structMenu.add(stressTest);

    if(structMenu.show()){
            typeMenu.add(intType);
            typeMenu.add(floatType);
            typeMenu.add(stringType);
            typeMenu.show();
        }
}

template<typename Data>
void launchMatrixMenu(Matrix<Data>& mx){
    Menu mainMenu("Chose an action:");

    MenuItem insertValues("Insert Values", [&mx](){
        popolaMatrix(mx);
    });
    mainMenu.add(insertValues);

    setupContainerMenu(mainMenu, mx);
    setupTestableContainerMenu(mainMenu, mx);
    setupMappableMenu(mainMenu, mx, false);
    setupFoldableMenu(mainMenu, mx);

    MenuItem rowResize("Row Resize", [&mx](){
        testRowResize(mx);
    });
    MenuItem colResize("Column Resize", [&mx](){
        testColResize(mx);
    });
    MenuItem existsCell("Exists Cell", [&mx](){
        testExistsCell(mx);
    });
    MenuItem accesOperator("Access operator ()", [&mx](){
        testAccesOperator(mx);
    });
    MenuItem constAccesOperator("Access operator () [const]", [&mx](){
        testConstAccessOperator(mx);
    });

    mainMenu.add(rowResize);
    mainMenu.add(colResize);
    mainMenu.add(existsCell);
    mainMenu.add(accesOperator);
    mainMenu.add(constAccesOperator);

    mainMenu.loop();
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

/* *** Random generation *** */
default_random_engine gen(random_device{}());
uniform_int_distribution<unsigned int> distr0_100(0, 100);
uniform_int_distribution<unsigned int> distr0_4(0, 4);

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


/* *** Matrix test *** */

bool eq_matr(const MatrixCSR<int>& mc, const MatrixVec<int>& mv){
    for(int i=0; i<mc.RowNumber(); i++)
        for(int j=0; j<mc.ColumnNumber(); j++){
            if(mc.ExistsCell(i, j))
                if(mc(i, j) != mv(i, j))
                    return false;
        }
    return true;
}


const int& const_acc(const Matrix<int>& mx, unsigned int i, unsigned int j){
    return mx(i, j);
}

void myStressTest(){
    enum Action{
        RowResize,
        ColResize,
        InsertValue,
        TestCopy,
        TestMove
    };

    const long seed = 3499211612;
    MatrixVec<int> mv;
    MatrixCSR<int> mc;
    int valMatr[100][100];
    unsigned long err = 0, test = 0;

    cout<< "Seed: "<< seed << endl;

    for(int i=1; i <= 1000; i++){
        auto action = static_cast<Action>(distr0_4(gen));
        cout<< "["<< i << "] ";
        if(action == RowResize){
            unsigned int r = distr0_100(gen);
            try {
                cout << "Set row to " << r;
                mv.RowResize(r);
                mc.RowResize(r);
                cout << " ok" << endl;
            } catch (...){
                cerr<< "Exception in RowResize" << endl;
                err++;
            }
            test++;
        }
        if(action == ColResize){
            unsigned int c = distr0_100(gen);
            try {
                cout << "Set col to " << c;
                mv.ColumnResize(c);
                mc.ColumnResize(c);
                cout << " ok" << endl;
            } catch (...){
                cerr<< "Exception in ColResize" << endl;
                err++;
            }
            test++;
        }
        if(action == InsertValue && mc.RowNumber() != 0 && mc.ColumnNumber() != 0){
            uniform_int_distribution<unsigned int> N(0, mc.RowNumber()-1);
            uniform_int_distribution<unsigned int> M(0, mc.ColumnNumber()-1);

            unsigned int nElements = distr0_100(gen)/3;
            cout<< "Insert " << nElements << " values" << endl;
            for(int k = 0; k < nElements; k++){
                try {
                    int num = distr0_100(gen);
                    unsigned int n = N(gen);
                    unsigned int m = M(gen);

                    cout << "\tInsert " << num << " in (" << n << ", " << m << ")";
                    mv(n, m) = num;
                    mc(n, m) = num;
                    valMatr[n][m] = num;
                    cout << " ok" << endl;

                    test++;
                    if (mv(n, m) != mc(n, m)) {
                        cerr << "ERRORE! I valori delle matrici sono diversi!! (mv(n, m) != mc(n, m))" << endl;
                        err++;
                    }test++;
                    if (mc(n, m) != valMatr[n][m]) {
                        cerr << "ERRORE! I valori delle matrici sono diversi!! (mc(n, m) != valMatr[n][m])" << endl;
                        err++;
                    }test++;
                    if (mv(n, m) != valMatr[n][m]) {
                        cerr << "ERRORE! I valori delle matrici sono diversi!! (mv(n, m) != valMatr[n][m])" << endl;
                        err++;
                    }test++;
                    if (const_acc(mv, n, m) != const_acc(mc, n, m)) {
                        cerr<< "ERRORE! I valori delle matrici (accesso costante) sono diversi!! const_acc(mv, n, m) != const_acc(mc, n, m)"<< endl;
                        err++;
                    }
                } catch (...){
                    cerr<< "Exception in Insert" << endl;
                    err++;
                }
            }
            cout<< "ok" << endl;
        }
        if(action == TestCopy){
            cout<< "Test Copy";
            try {
                MatrixVec<int> mv_copy(mv);
                MatrixCSR<int> mc_copy(mc);

                if (mc.RowNumber() != 0 && mc.ColumnNumber() != 0) {
                    uniform_int_distribution<unsigned int> N(0, mc.RowNumber() - 1);
                    uniform_int_distribution<unsigned int> M(0, mc.ColumnNumber() - 1);
                    unsigned int nElements = distr0_100(gen)/3;
                    for (int k = 0; k < nElements; k++) {
                        int num = distr0_100(gen);
                        unsigned int n = N(gen);
                        unsigned int m = M(gen);
                        mv(n, m) = num;
                        mc(n, m) = num;

                        mv_copy(n, m) = num;
                        mc_copy(n, m) = num;
                    }
                }


                test++;
                if (!eq_matr(mc_copy, mv_copy)) {
                    err++;
                    cerr << "Le matrici copiate col costruttore sono diverse!!(mc_copy, mv_copy)" << endl;
                } test++;
                if (mv != mv_copy) {
                    err++;
                    cerr << "Le matrici copiate col costruttore sono diverse!!(mv != mv_copy)" << endl;
                } test++;
                if (mc != mc_copy) {
                    err++;
                    cerr << "Le matrici copiate col costruttore sono diverse!!(mc != mc_copy)" << endl;
                }
                mv_copy = mv;
                mc_copy = mc;

                test++;
                if (!eq_matr(mc_copy, mv_copy)) {
                    err++;
                    cerr << "Le matrici copiate per assegnazione sono diverse!!" << endl;
                }
                cout << " ok" << endl;
            } catch (...){
                cerr<< "Exception in Copy" << endl;
                err++;
            }
        }
        if(action == TestMove){
            cout<< "Test Move";
            try {
                MatrixVec<int> mv_copy(mv);
                MatrixCSR<int> mc_copy(mc);

                MatrixVec<int> mv_move(move(mv_copy));
                MatrixCSR<int> mc_move(move(mc_copy));
                test++;
                if (!eq_matr(mc_move, mv_move)) {
                    err++;
                    cout << "Le matrici spostate col costruttore sono diverse!!" << endl;
                }test++;
                if (mv != mv_move) {
                    err++;
                    cout << "Le matrici spostate col costruttore sono diverse!!" << endl;
                }test++;
                if (mc != mc_move) {
                    err++;
                    cout << "Le matrici spostate col costruttore sono diverse!!" << endl;
                }
                mv = move(mv_move);
                mc = move(mc_move);
                test++;
                if (!eq_matr(mc, mv)) {
                    err++;
                    cout << "Le matrici spostate per assegnazione sono diverse!!" << endl;
                }
                cout << " ok" << endl;


                test++;
                if (mv.RowNumber() != mc.RowNumber()) {
                    err++;
                    cerr << "ERRORE! Il numero di righe delle matrici sono diversi!!" << "mc: " << mc.RowNumber() << " mv: "
                         << mv.RowNumber() << endl;
                }test++;
                if (mv.ColumnNumber() != mc.ColumnNumber()) {
                    err++;
                    cerr << "ERRORE! Il numero di colonne delle matrici sono diversi!! " << "mc: " << mc.ColumnNumber()
                         << " mv: " << mv.ColumnNumber() << endl;
                }test++;
                if (!eq_matr(mc, mv)) {
                    err++;
                    cerr << "ERRORE! Le matrici sono diverse!!" << endl;
                }
            }catch (...){
                cerr<< "Exception in Move" << endl;
                err++;
            }
        }
        test++;
    }

    cout << "End. errors/tests: "<< err << "/" << test << endl;
}

template<typename Data>
void popolaMatrix(Matrix<Data>& mx){
    if (mx.RowNumber() != 0 && mx.ColumnNumber() != 0) {
        uniform_int_distribution<unsigned int> N(0, mx.RowNumber() - 1);
        uniform_int_distribution<unsigned int> M(0, mx.ColumnNumber() - 1);
        unsigned int nElements = distr0_100(gen)/3;
        for (int k = 0; k < nElements; k++) {
            mx(N(gen), M(gen)) =  distr0_100(gen);
        }
    }
}
template<typename Data>
void testRowResize(Matrix<Data>& mx){
    unsigned long r;
    cout<< "Insert new row" << endl << ">>> ";
    cin>> r;
    mx.RowResize(r);
    cout<< "Row is set to " << mx.RowNumber() << endl;
}
template<typename Data>
void testColResize(Matrix<Data>& mx){
    unsigned long c;
    cout<< "Insert new column" << endl << ">>> ";
    cin>> c;
    mx.RowResize(c);
    cout<< "Row is set to " << mx.RowNumber() << endl;
}
template<typename Data>
void testExistsCell(const Matrix<Data>& mx){
    unsigned long r, c;
    cout<< "Insert cell row" << endl << ">>> ";
    cin>> r;
    cout<< "Insert cell col" << endl << ">>> ";
    cin>> c;

    try {
        cout<< "Cell("<< r << ", " << c <<") does " << ((mx.ExistsCell(r, c))? "": "not ") << "Exists" << endl;
    } catch (length_error& e){
        cout<< "Error: " << e.what() << endl;
    } catch(out_of_range& e){
        cout<< "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testAccesOperator(Matrix<Data>& mx){
    unsigned long r, c;
    cout<< "Insert cell row" << endl << ">>> ";
    cin>> r;
    cout<< "Insert cell col" << endl << ">>> ";
    cin>> c;

    try {
        Data num;
        cout<< "Cell("<< r << ", " << c <<") is set to" << mx(r, c) << endl;
        cout<< "Insert the new value" << endl << ">>> ";
        cin>> num;
        mx(r, c) = num;
        cout<< "Cell("<< r << ", " << c <<") is set to" << mx(r, c) << endl;
    }catch(out_of_range& e){
        cout<< "Error: " << e.what() << endl;
    }
}
template<typename Data>
void testConstAccessOperator(const Matrix<Data>& mx){
    unsigned long r, c;
    cout<< "Insert cell row" << endl << ">>> ";
    cin>> r;
    cout<< "Insert cell col" << endl << ">>> ";
    cin>> c;

    try {
        Data num;
        cout<< "Cell("<< r << ", " << c <<") is set to" << mx(r, c) << endl;
    } catch (length_error& e){
        cout<< "Error: " << e.what() << endl;
    } catch(out_of_range& e){
        cout<< "Error: " << e.what() << endl;
    }
}
