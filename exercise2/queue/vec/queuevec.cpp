
namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    QueueVec<Data>::QueueVec(){
        Vector<Data>::Resize(initSize);
    }

    template<typename Data>
    QueueVec<Data>::QueueVec(const LinearContainer<Data>& lc) : Vector<Data>(lc){
        head = size;
        if (size*resizeFactor < initSize) Vector<Data>::Resize(initSize);
        else Expand();
    }

    template<typename Data>
    QueueVec<Data>::QueueVec(const QueueVec<Data>& qv){
        elements = new Data[qv.size];
        for (unsigned long i = 0; i < qv.size; i++){
            elements[i] = qv.elements[i];
        }
        size = qv.size;
        head = qv.head;
        tail = qv.tail;

    }

    template<typename Data>
    QueueVec<Data>::QueueVec(QueueVec<Data>&& qv) noexcept {
        std::swap(head, qv.head);
        std::swap(tail, qv.tail);
        Vector<Data>::operator=(std::move(qv));
    }

    template<typename Data>
    QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& qv){
        Vector<Data>::operator=(qv);
        head = qv.head;
        tail = qv.tail;
        return *this;
    }

    template<typename Data>
    QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& qv) noexcept{
        std::swap(head, qv.head);
        std::swap(tail, qv.tail);
        Vector<Data>::operator=(std::move(qv));
        return *this;
    }

    template<typename Data>
    bool QueueVec<Data>::operator==(const QueueVec<Data>& qv) const noexcept{
        if (Size() == qv.Size()){
            unsigned long t1 = tail;
            unsigned long t2 = qv.tail;

            while (t1 != head){
                if (elements[t1] != qv.elements[t2]) return false;
                t1 = (t1+1)%size;
                t2 = (t2+1)%qv.size;
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
        elements[head] = data;
        head = (head+1)%size;
        Expand();
    }

    template<typename Data>
    void QueueVec<Data>::Enqueue(Data&& data){
        std::swap(elements[head], data);
        head = (head+1)%size;
        Expand();
    }

    template<typename Data>
    Data& QueueVec<Data>::Head() const{
        if (Size() != 0){
            return elements[tail];
        } else {
            throw std::length_error("Queue is empty");
        }
    }

    template<typename Data>
    void QueueVec<Data>::Dequeue(){
        if (Size() != 0){
            tail = (tail+1)%size;
            Reduce();
        } else {
            throw std::length_error("Queue is empty");
        }
    }

    template<typename Data>
    Data QueueVec<Data>::HeadNDequeue(){
        if (Size() != 0){
            Data data = elements[tail];
            tail = (tail+1)%size;
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
        if (head == tail) return 0;
        else if(tail < head) return head-tail;
        else return size-(tail-head);
    }

    template<typename Data>
    void QueueVec<Data>::Clear(){
        Vector<Data>::Clear();
        head = 0;
        tail = 0;
        Vector<Data>::Resize(initSize);
    }

   //template<typename Data>
   //void QueueVec<Data>::Normalize() {
   //    if (tail != 0) {
   //        Data *tmpElements = new Data[size];
   //        unsigned long t = tail;
   //        unsigned long i = 0;
   //        while (t != head) {
   //            std::swap(tmpElements[i], elements[t]);
   //            t = (t + 1) % size;
   //            i++;
   //        }
   //        std::swap(elements, tmpElements);
   //        head = i;
   //        tail = 0;
   //        delete[] tmpElements;
   //    }
   //}

    template<typename Data>
    void QueueVec<Data>::Expand() {
        if (Size() >= size-1){
            //Normalize();
            Vector<Data>::Resize(size*resizeFactor);
        }
    }

    template<typename Data>
    void QueueVec<Data>::Reduce() {
        unsigned long newSize = size/resizeFactor;
        if (Size() <= size/4 && newSize > Size() && newSize >= initSize){
            //Normalize();
            //Vector<Data>::Resize(newSize);
            Data *tmpElements = new Data[newSize];
            unsigned long t = tail;
            unsigned long i = 0;
            while (t != head) {
                std::swap(tmpElements[i], elements[t]);
                t = (t + 1) % size;
                i++;
            }

            //for (i, t; t != head; t = (t + 1) % size, i++) {
            //    std::swap(tmpElements[i], elements[t]);
            //}
            std::swap(elements, tmpElements);
            head = i;
            tail = 0;
            delete[] tmpElements;
        }
    }

/* ************************************************************************** */

}
