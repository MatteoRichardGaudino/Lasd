
namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    MatrixCSR<Data>::MatrixCSR(){
        R.Resize(1);
        R[0] = &head;
    }

    template<typename Data>
    MatrixCSR<Data>::MatrixCSR(unsigned long r, unsigned long c) : Matrix<Data>(){
        row = r;
        column = c;
    }

    template<typename Data>
    MatrixCSR<Data>::MatrixCSR(const MatrixCSR<Data>& mx){
        // TODO
    }

    template<typename Data>
    MatrixCSR<Data>::MatrixCSR(MatrixCSR<Data>&& mx) noexcept{
        std::swap(R, mx.R);
        std::swap(row, mx.row);
        std::swap(column, mx.column);
        List<pair>::operator=(std::move(mx));
    }

    template<typename Data>
    MatrixCSR<Data>& MatrixCSR<Data>::operator=(const MatrixCSR<Data>&){
        // TODO
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
        else{
            for (unsigned long i = 0; i < R.Size() - 1; ++i) {
                unsigned long j = i;
                // TODO
            }
        }
    }

    template<typename Data>
    bool MatrixCSR<Data>::operator!=(const MatrixCSR<Data>& mx) const noexcept{
        return !operator==(mx);
    }

    template<typename Data>
    void MatrixCSR<Data>::RowResize(unsigned long) {
        // TODO
    }
    template<typename Data>
    void MatrixCSR<Data>::ColumnResize(unsigned long){
        // TODO
    }
    template<typename Data>
    bool MatrixCSR<Data>::ExistsCell() const noexcept{
        // TODO
    }
    template<typename Data>
    Data& MatrixCSR<Data>::operator()(unsigned long, unsigned long){
        // TODO
    }
    template<typename Data>
    const Data& MatrixCSR<Data>::operator()(unsigned long, unsigned long) const{
        // TODO
    }

    template<typename Data>
    void MatrixCSR<Data>::Clear(){
        List<pair>::Clear();
        R.Clear();
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
