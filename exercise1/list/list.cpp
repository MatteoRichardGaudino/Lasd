
namespace lasd {

/* ************************************************************************** */

// ...


    // Specific constructor
    template<typename Data>
    List<Data>::List(const LinearContainer<Data>& l) {
        if (l.Size() > 0){
            head = new Node(l[0]);
            Node* tmp = head;
            for (unsigned long i = 1; i < l.Size(); i++) {
                tmp->next = new Node(l[i]);
                tmp = tmp->next;
            }
            size = l.Size();
        }
    } // A list obtained from a LinearContainer

    /* ************************************************************************ */

    // Copy constructor
    template<typename Data>
    List<Data>::List(const List<Data>& list){
        if (list.Size() > 0){
            head = new Node(list.head->data);
            Node* tmp = head;
            Node* tmp2 = list.head->next;
            while (tmp2 != nullptr){
                tmp->next = new Node(tmp2->data);
                tmp = tmp->next;
                tmp2 = tmp2->next;
            }
            size = list.size;
        }
    }

    // Move constructor
    template<typename Data>
    List<Data>::List(List<Data>&& list) noexcept{
        std::swap(head, list.head);
        std::swap(size, list.size);
    }

    /* ************************************************************************ */

    // Destructor
    template<typename Data>
    List<Data>::~List(){
        Clear();
    }

    /* ************************************************************************ */

    // Copy assignment
    template<typename Data>
    List<Data>& List<Data>::operator=(const List<Data>& list){
        Clear();
        if (list.Size() > 0){
            head = new Node(list.head->data);
            Node* tmp = head;
            Node* tmp2 = list.head->next;
            while (tmp2 != nullptr){
                tmp->next = new Node(tmp2->data);
                tmp = tmp->next;
                tmp2 = tmp2->next;
            }
            size = list.size;
        }
        return *this;
    }

    // Move assignment
    template<typename Data>
    List<Data>& List<Data>::operator=(List<Data>&& list) noexcept{
        std::swap(head, list.head);
        std::swap(size, list.size);
        return *this;
    }

    /* ************************************************************************ */

    // Comparison operators
    template<typename Data>
    bool List<Data>::operator==(const List<Data>& list) const noexcept{
        if (size == list.size){
            Node* tmp = head;
            Node* tmp2 = list.head;
            while (tmp != nullptr){
                if (tmp->data != tmp2->data){
                    return false;
                }
                tmp = tmp->next;
                tmp2 = tmp2->next;
            }
            return true;
        } else return false;
    }
    template<typename Data>
    bool List<Data>::operator!=(const List<Data>& list) const noexcept{
        return !((*this) == list);
    }

    /* ************************************************************************ */

    // Specific member functions

    template<typename Data>
    void List<Data>::InsertAtFront(const Data& dat){
        Node* newNode = new Node(dat);
        newNode->next = head;
        head = newNode;
        size++;
    }
    template<typename Data>
    void List<Data>::InsertAtFront(Data&& dat){
        Node* newNode = new Node(std::move(dat));
        newNode->next = head;
        head = newNode;
        size++;
    }

    template<typename Data>
    void List<Data>::RemoveFromFront(){
        if (size != 0) {
            Node *tmp = head;
            head = head->next;
            size--;
            delete tmp;
        } else{
            throw std::length_error("List is empty");
        }
    }
    template<typename Data>
    Data List<Data>::FrontNRemove(){
        if (size != 0) {
            Data data = std::move(head->data);
            Node *tmp = head;
            head = head->next;
            size--;
            delete tmp;
            return data;
        } else{
            throw std::length_error("List is empty");
        }
    }

    template<typename Data>
    void List<Data>::InsertAtBack(const Data& dat){
        if (size == 0){
            InsertAtFront(dat);
        } else{
            Node* newNode = new Node(dat);
            Node* tmp = head;
            while (tmp->next != nullptr){
                tmp = tmp->next;
            }
            tmp->next = newNode;
            size++;
        }
    }

    template<typename Data>
    void List<Data>::InsertAtBack(Data&& dat){
        if (size == 0){
            InsertAtFront(dat);
        } else{
            Node* newNode = new Node(dat);
            Node* tmp = head;
            while (tmp->next != nullptr){
                tmp = tmp->next;
            }
            tmp->next = newNode;
            size++;
        }
    } // Move of the value

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    template<typename Data>
    void List<Data>::Clear(){
        while (size != 0){
            RemoveFromFront();
        }
    } // Override Container member

    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)

    template<typename Data>
    Data& List<Data>::Front() const {
        if (size != 0){
            return head->data;
        } else {
            throw std::length_error("List is empty");
        }
    }
    template<typename Data>
    Data& List<Data>::Back() const {
        if(size != 0){
            return (*this)[size-1];
        } else {
            throw std::length_error("List is empty");
        }
    }

    template<typename Data>
    Data& List<Data>::operator[](const unsigned long i) const noexcept {
        if (i < size){
            Node* tmp = head;
            unsigned long j = 0;
            while (j < i){
                j++;
                tmp = tmp->next;
            }
            return tmp->data;
        } else {
            throw std::out_of_range("List size (" + std::to_string(size) + "), Input_index [" + std::to_string(i) + "]");
        }
    }

    /* ************************************************************************ */

    // Specific member functions (inherited from MappableContainer)

    template<typename Data>
    void List<Data>::MapPreOrder(const MapFunctor fun, void * v){
        Node* tmp = head;
        while (tmp != nullptr){
            fun(tmp->data, v);
            tmp = tmp->next;
        }
    }
    template<typename Data>
    void List<Data>::MapPostOrder(const MapFunctor fun, void * v) {
        for (unsigned long i = size; i > 0; i--) {
            fun((*this)[i-1], v);
        }
    }

    /* ************************************************************************ */

    // Specific member functions (inherited from FoldableContainer)

    template<typename Data>
    void List<Data>::FoldPreOrder(const FoldFunctor fun, const void* v1, void* v2) const {
        Node* tmp = head;
        while (tmp != nullptr){
            fun(tmp->data, v1, v2);
            tmp = tmp->next;
        }
    }
    template<typename Data>
    void List<Data>::FoldPostOrder(const FoldFunctor fun, const void* v1, void* v2) const {
        for (unsigned long i = size ; i > 0; i--) {
            fun((*this)[i-1], v1, v2);
        }
    } // Override FoldableContainer member


/* ************************************************************************** */

}
