namespace lasd {

/* ************************************************************************** */
template <typename Data>
MatrixVec<Data>::MatrixVec(unsigned long r, unsigned long c) {
    row = r;
    column = c;
    Vector<Data>::Resize(row*column);
}

template<typename Data>
MatrixVec<Data>::MatrixVec(const MatrixVec<Data>& matrix) : Vector<Data>(matrix){
    row = matrix.row;
    column = matrix.column;
}

template <typename Data>
MatrixVec<Data>::MatrixVec(MatrixVec<Data>&& matrix) noexcept {
    operator=(std::move(matrix));
}

template <typename Data>
MatrixVec<Data> & MatrixVec<Data>::operator=(const MatrixVec<Data>& matrix) {
    row = matrix.row;
    column = matrix.column;
    Vector<Data>::operator=(matrix);
    return *this;
}
template <typename Data>
MatrixVec<Data> & MatrixVec<Data>::operator=(MatrixVec<Data>&& matrix) noexcept {
    std::swap(row, matrix.row);
    std::swap(column, matrix.column);
    Vector<Data>::operator=(std::move(matrix));
    return *this;
}

template <typename Data>
bool MatrixVec<Data>::operator==(const MatrixVec<Data>& matrix) const noexcept {
    if(row == matrix.row && column == matrix.column)
        return Vector<Data>::operator==(matrix);
    else return false;
}

template <typename Data>
bool MatrixVec<Data>::operator!=(const MatrixVec<Data>& matrix) const noexcept {
    return !operator==(matrix);
}
/* *********************** MEMBER FUNCTIONS *************************************************** */

template <typename Data>
void MatrixVec<Data>::Clear() {
    Vector<Data>::Clear();
    row = 0;
    column = 0;
}

template <typename Data>
void MatrixVec<Data>::RowResize(unsigned long newRow) {
//    Vector<Data> tmp(newRow*column);
//    unsigned long rowMin = (row < newRow)? row: newRow;
//
//    for (unsigned long i = 0; i < rowMin; ++i) {
//        for (unsigned long j = 0; j < column; ++j) {
//            std::swap(tmp[(i*column) + j], Vector<Data>::operator[](i*column + j));
//        }
//    }
//
//    row = newRow;
//    Vector<Data>::operator=(std::move(tmp));
    unsigned long col = column;
    Vector<Data>::Resize(newRow*column);
    row = newRow;
    column = col;
}

template <typename Data>
void MatrixVec<Data>::ColumnResize(unsigned long newCol) {
    Vector<Data> tmp(row*newCol);
    unsigned long colMin = (column < newCol)? column: newCol;

    for (unsigned long i = 0; i < row; ++i) {
        for (unsigned long j = 0; j < colMin; ++j) {
            std::swap(tmp[(i*newCol) + j], Vector<Data>::operator[](i*column + j));
        }
    }
    column = newCol;
    Vector<Data>::operator=(std::move(tmp));
}

template <typename Data>
bool MatrixVec<Data>::ExistsCell(unsigned long r, unsigned long c) const noexcept {
    return r < row && c < column;
//    return ((r * column) + c) < (row * column);
}

template <typename Data>
Data & MatrixVec<Data>::operator()(unsigned long r, unsigned long c) {
    if (ExistsCell(r, c))
        return Vector<Data>::operator[]((r*column) + c);
    else throw std::out_of_range("[operator()] Cell (" + std::to_string(r)+ ", "
        + std::to_string(c) + ") does not exists in Matrix("
        + std::to_string(row) +", " + std::to_string(row) + ").");

}
template <typename Data>
const Data & MatrixVec<Data>::operator()(unsigned long r, unsigned long c) const {
    if (ExistsCell(r, c))
        return Vector<Data>::operator[]((r*column) + c);
    else throw std::out_of_range("[const operator()] Cell (" + std::to_string(r)+ ", "
                                 + std::to_string(c) + ") does not exists in Matrix("
                                 + std::to_string(row) +", " + std::to_string(column) + ").");
}

}