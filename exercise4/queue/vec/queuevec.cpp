namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    QueueVec<Data>::QueueVec(){
        Vector<Data>::Resize(initSize);
    }

    template<typename Data>
    QueueVec<Data>::QueueVec(const LinearContainer<Data>& lc){
        if (lc.Size() == 0) Vector<Data>::Resize(initSize);
        else {
            if (lc.Size() * resizeFactor < initSize) Vector<Data>::Resize(initSize);
            else Vector<Data>::Resize(lc.Size() * resizeFactor);
            for (unsigned long i = 0; i < lc.Size(); ++i) {
                elements[i] = lc[i];
            }
            tail = lc.Size();
        }
    }

    template<typename Data>
    QueueVec<Data>::QueueVec(const QueueVec<Data>& qv){
        elements = new Data[qv.size];
        for (unsigned long i = 0; i < qv.size; i++){
            elements[i] = qv.elements[i];
        }
        size = qv.size;
        tail = qv.tail;
        head = qv.head;

    }

    template<typename Data>
    QueueVec<Data>::QueueVec(QueueVec<Data>&& qv) noexcept {
        std::swap(tail, qv.tail);
        std::swap(head, qv.head);
        Vector<Data>::operator=(std::move(qv));
    }

    template<typename Data>
    QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& qv){
        Vector<Data>::operator=(qv);
        tail = qv.tail;
        head = qv.head;
        return *this;
    }

    template<typename Data>
    QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& qv) noexcept{
        std::swap(tail, qv.tail);
        std::swap(head, qv.head);
        Vector<Data>::operator=(std::move(qv));
        return *this;
    }

    template<typename Data>
    bool QueueVec<Data>::operator==(const QueueVec<Data>& qv) const noexcept{
        if (Size() == qv.Size()){
            unsigned long h1 = head;
            unsigned long h2 = qv.head;

            while (h1 != tail){
                if (elements[h1] != qv.elements[h2]) return false;
                h1 = (h1+1)%size;
                h2 = (h2+1)%qv.size;
            }
            return true;
        } else return false;
    }

    template<typename Data>
    bool QueueVec<Data>::operator!=(const QueueVec<Data>& qv) const noexcept{
        return !operator==(qv);
    }

    template<typename Data>
    void QueueVec<Data>::Enqueue(const Data& data) {
        elements[tail] = data;
        tail = (tail+1)%size;
        Expand();
    }

    template<typename Data>
    void QueueVec<Data>::Enqueue(Data&& data){
        std::swap(elements[tail], data);
        tail = (tail+1)%size;
        Expand();
    }

    template<typename Data>
    Data& QueueVec<Data>::Head() const{
        if (Size() != 0){
            return elements[head];
        } else {
            throw std::length_error("Queue is empty");
        }
    }

    template<typename Data>
    void QueueVec<Data>::Dequeue(){
        if (Size() != 0){
            head = (head+1)%size;
            Reduce();
        } else {
            throw std::length_error("Queue is empty");
        }
    }

    template<typename Data>
    Data QueueVec<Data>::HeadNDequeue(){
        if (Size() != 0){
            Data data = elements[head];
            head = (head+1)%size;
            Reduce();
            return data;
        } else {
            throw std::length_error("Queue is empty");
        }
    }

    template<typename Data>
    bool QueueVec<Data>::Empty() const noexcept{
        return Size() == 0;
    }

    template<typename Data>
    unsigned long QueueVec<Data>::Size() const noexcept{
        if (tail == head) return 0;
        else if(head < tail) return tail-head;
        else return size-(head-tail);
    }

    template<typename Data>
    void QueueVec<Data>::Clear(){
        Vector<Data>::Resize(initSize);
        tail = 0;
        head = 0;
    }

    template<typename Data>
    void QueueVec<Data>::Normalize(unsigned long newSize) {
        Data *tmpElements = new Data[newSize];
        unsigned long h = head;
        unsigned long i = 0;
        while (h != tail) {
            std::swap(tmpElements[i], elements[h]);
            h = (h + 1) % size;
            i++;
        }
        std::swap(elements, tmpElements);
        tail = i;
        head = 0;
        size = newSize;
        delete[] tmpElements;
    }

    template<typename Data>
    void QueueVec<Data>::Expand() {
        if (Size() >= size-1){
            Normalize(size*resizeFactor);
        }
    }

    template<typename Data>
    void QueueVec<Data>::Reduce() {
        unsigned long newSize = size/resizeFactor;
        if (Size() <= size/4 && newSize > Size() && newSize >= initSize){
            Normalize(newSize);
        }
    }

/* ************************************************************************** */

}
