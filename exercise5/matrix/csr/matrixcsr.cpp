
namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    MatrixCSR<Data>::MatrixCSR(){
        R.Resize(1);
        R[0] = &head;
    }

    template<typename Data>
    MatrixCSR<Data>::MatrixCSR(unsigned long r, unsigned long c) {
        R.Resize(r + 1);
        row = r;
        column = c;
        for (unsigned long i = 0; i <= row; ++i) {
            R[i] = &head;
        }
    }


    template<typename Data>
    MatrixCSR<Data>::MatrixCSR(const MatrixCSR<Data>& mx){
        operator=(mx);
    }

    template<typename Data>
    MatrixCSR<Data>::MatrixCSR(MatrixCSR<Data>&& mx) noexcept{
        std::swap(R, mx.R);
        std::swap(row, mx.row);
        std::swap(column, mx.column);
        List<pair>::operator=(std::move(mx));
    }

    template<typename Data>
    MatrixCSR<Data>& MatrixCSR<Data>::operator=(const MatrixCSR<Data>& mx){
        List<pair>::operator=(mx);
        R.Resize(mx.R.Size());
        row = mx.row;
        column = mx.column;
        Node** ptr1 = &head;
        for (unsigned long i = 0; i < row; ++i) {
            R[i] = ptr1;
            mx.forEachElementInRow(i, [&ptr1]{
                ptr1 = &((*ptr1)->next);
            });
        }
        R.Back() = ptr1;
        return *this;
    }

    template<typename Data>
    MatrixCSR<Data>& MatrixCSR<Data>::operator=(MatrixCSR<Data>&& mx) noexcept{
        std::swap(R, mx.R);
        std::swap(row, mx.row);
        std::swap(column, mx.column);
        List<pair>::operator=(std::move(mx));
        return *this;
    }

    template<typename Data>
    bool MatrixCSR<Data>::operator==(const MatrixCSR<Data>& mx) const noexcept{
        if (row != mx.row || column != mx.column) return false;
        else if (row == 0 && mx.row == 0 &&
                column == 0 && mx.column == 0) return true;
        else{
            for (unsigned long i = 0; i < row; ++i) {
                Node* ptr1 = *R[i];
                Node* ptr2 = *mx.R[i];

                while (ptr1 != *R[i+1] && ptr2 != *mx.R[i+1]){
                    if (ptr1->data != ptr2->data) return false;
                    ptr1 = ptr1->next;
                    ptr2 = ptr2->next;
                }
                if ((ptr1 == *R[i+1] && ptr2 != *mx.R[i+1]) ||
                    (ptr1 != *R[i+1] && ptr2 == *mx.R[i+1])) return false;
                else return true;
            }
        }
    }

    template<typename Data>
    bool MatrixCSR<Data>::operator!=(const MatrixCSR<Data>& mx) const noexcept{
        return !operator==(mx);
    }

    template <typename Data>
    void MatrixCSR<Data>::RowResize(unsigned long newRow){
        if(newRow < row){
            Node* curr = *R[newRow];
            while(curr != nullptr){
                Node* del = curr;
                curr = curr->next;
                delete del;
                size--;
            }
            row = newRow;
            R.Resize(row + 1);
            *R.Back() = nullptr;
        } else if(newRow > row){
                R.Resize(newRow + 1);
                for(unsigned long i = row; i < newRow; i++) R[i+1] = R[i];
                row = newRow;
        }
    }
    template<typename Data>
    void MatrixCSR<Data>::ColumnResize(unsigned long newCol){
        if(newCol == 0){
            List<pair>::Clear();
            for (unsigned long i = 0; i < R.Size(); ++i) {
                R[i] = &head;
            }
            size = 0;
        } else if(newCol < column){
            for (unsigned long i = 0; i < row; ++i) {
                Node** tmp = R[i];
                while (tmp != R[i+1]){
                    if ((*tmp)->data.second >= newCol){
                        Node* del = *tmp;
                        *tmp = del->next;
                        if (&(del->next) == R[i+1]){
                            R[i+1] = tmp;
                        }
                        del->next = nullptr;
                        delete del;
                        size--;
                    }else tmp = &((*tmp)->next);
                }
            }
        }
        column = newCol;
    }

    template<typename Data>
    bool MatrixCSR<Data>::ExistsCell(unsigned long r, unsigned long c) const noexcept{
        if (r < row && c < column){
            Node** ptr = R[r];
            while (ptr != R[r+1] && (*ptr)->data.second <= c) {
                if((*ptr)->data.second == c) return true;
                ptr = &((*ptr)->next);
            }
        }
        return false;
    }
    template<typename Data>
    Data& MatrixCSR<Data>::operator()(unsigned long r, unsigned long c){
        if (r < row && c < column){
            Node** ptr = R[r];
            Node** ext = R[r+1];
            while (ptr != ext && (*ptr)->data.second <= c) {
                Node& node = **ptr;
                if(node.data.second == c) return node.data.first;
                ptr = &(node.next);
            }

            Node* newNode = new Node();
            newNode->next = *ptr;
            *ptr = newNode;
            newNode->data.second = c;
            size++;
            unsigned long i = r+1;
            if(ptr == ext){
                for(; i < row && R[i] == R[i+1]; ++i){
                    R[i] = &((*ptr)->next);
                }
                R[i] = &((*ptr)->next);
            }
            return newNode->data.first;

        } else throw std::out_of_range("[operator()] Out of Range");

    }
    template<typename Data>
    const Data& MatrixCSR<Data>::operator()(unsigned long r, unsigned long c) const{
        if (r < row && c < column){
            Node** ptr = R[r];
            while ((*ptr) != *R[r+1] && (*ptr)->data.second <= c) {
                if((*ptr)->data.second == c) return (*ptr)->data.first;
                ptr = &((*ptr)->next);
            }
            throw std::length_error("[operator() const] Element is not present");
        } else throw std::out_of_range("[operator() const] Out of Range");
    }

    template<typename Data>
    void MatrixCSR<Data>::Clear(){
        List<pair>::Clear();
        R.Resize(1);
        row = 0;
        column = 0;
    }

    template<typename Data>
    void MatrixCSR<Data>::MapPreOrder(const MapFunctor fun, void* v){
        List<pair>::MapPreOrder([&fun](pair& p, void* v){
            fun(p.first, v);
        }, v);
    }
    template<typename Data>
    void MatrixCSR<Data>::MapPostOrder(const MapFunctor fun, void* v){
        List<pair>::MapPostOrder([&fun](pair& p, void* v){
            fun(p.first, v);
        }, v);
    }
    template<typename Data>
    void MatrixCSR<Data>::FoldPreOrder(const FoldFunctor fun, const void* v1, void* v2) const{
        List<pair>::FoldPreOrder([&fun](const pair& p, const void* v1, void* v2){
            fun(p.first, v1, v2);
        }, v1, v2);
    }
    template<typename Data>
    void MatrixCSR<Data>::FoldPostOrder(const FoldFunctor fun, const void* v1, void* v2) const {
        List<pair>::FoldPostOrder([&fun](const pair& p, const void* v1, void* v2){
            fun(p.first, v1, v2);
        }, v1, v2);
    }


/* ************************************************************************** */

}
