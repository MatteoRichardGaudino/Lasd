
namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    MatrixVec<Data>::MatrixVec(unsigned long r, unsigned long c){
        row = r;
        column = c;
        Resize(row*column);
    }

    template<typename Data>
    MatrixVec<Data>::MatrixVec(const Matrix<Data>& matrix) : Vector<Data>(matrix){
        row = matrix.row;
        column = matrix.column;
    }

    template<typename Data>
    MatrixVec<Data>::MatrixVec(Matrix<Data>&& matrix) noexcept{
        std::swap(row, matrix.row);
        std::swap(column, matrix.column);
        Vector<Data>(std::move(matrix));
    }

    template<typename Data>
    MatrixVec<Data>& MatrixVec<Data>::operator=(const MatrixVec<Data>& matrix){
        row = matrix.row;
        column = matrix.column;
        Vector<Data>::operator=(matrix);
        return *this;
    }

    template<typename Data>
    MatrixVec<Data>& MatrixVec<Data>::operator=(MatrixVec<Data>&& matrix) noexcept{
        std::swap(row, matrix.row);
        std::swap(column, matrix.column);
        Vector<Data>::operator=(std::move(matrix));
        return *this;
    }

    template<typename Data>
    bool MatrixVec<Data>::operator==(const MatrixVec<Data>& matrix) const noexcept{
        if (row != matrix.row || column != matrix.column) return false;
        else return Vector<Data>::operator==(matrix);
    }
    template<typename Data>
    bool MatrixVec<Data>::operator!=(const MatrixVec<Data>& matrix) const noexcept{
        return !operator==(matrix);
    }

    template<typename Data>
    void MatrixVec<Data>::RowResize(unsigned long newRow){
        Vector<Data> tmp(newRow*column);
        unsigned long rowMin = (row < newRow)? row: newRow;

        for (unsigned long i = 0; i < rowMin; ++i) {
            for (unsigned long j = 0; j < column; ++j) {
                std::swap(tmp[(i*newRow) + j], operator()(i, j));
            }
        }

        row = newRow;
        Vector<Data>::operator=(tmp);
    }
    template<typename Data>
    void MatrixVec<Data>::ColumnResize(unsigned long newCol){
        Vector<Data> tmp(row*column);
        unsigned long colMin = (column < newCol)? column: newCol;

        for (unsigned long i = 0; i < row; ++i) {
            for (unsigned long j = 0; j < colMin; ++j) {
                std::swap(tmp[(i*row) + j], operator()(i, j));
            }
        }

        column = newCol;
        Vector<Data>::operator=(tmp);
    }

    template<typename Data>
    bool MatrixVec<Data>::ExistsCell(unsigned long r, unsigned long c) const noexcept{
        return r < row && c < column;
    }

    template<typename Data>
    Data& MatrixVec<Data>::operator()(unsigned long r, unsigned long c){
        if (ExistsCell(r, c))
            return Vector<Data>::operator[]((row*r) + c);
        else throw std::out_of_range("[operator()] Cell does not exists");
    }

    template<typename Data>
    const Data& MatrixVec<Data>::operator()(unsigned long r, unsigned long c) const{
        if (ExistsCell(r, c))
            return Vector<Data>::operator[]((row*r) + c);
        else throw std::out_of_range("[operator() const] Cell does not exists");
    }

    template<typename Data>
    void MatrixVec<Data>::Clear(){
        row = 0;
        column = 0;
        Vector<Data>::Clear();
    }

/* ************************************************************************** */

}
