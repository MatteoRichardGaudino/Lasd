
namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& ql){
        List<Data>::operator=(ql);
        return *this;
    }
    template<typename Data>
    QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& ql) noexcept{
        List<Data>::operator=(std::move(ql));
        return *this;
    }

    template<typename Data>
    bool QueueLst<Data>::operator==(const QueueLst<Data>& ql) const noexcept{
        return List<Data>::operator==(ql);
    }
    template<typename Data>
    bool QueueLst<Data>::operator!=(const QueueLst<Data>& ql) const noexcept{
        return !operator==(ql);
    }

    template<typename Data>
    void QueueLst<Data>::Enqueue(const Data& data) {
        List<Data>::InsertAtBack(data);
    }
    template<typename Data>
    void QueueLst<Data>::Enqueue(Data&& data) {
        List<Data>::InsertAtBack(std::move(data));
    }
    template<typename Data>
    Data& QueueLst<Data>::Head() const {
        return List<Data>::Front();
    }
    template<typename Data>
    void QueueLst<Data>::Dequeue() {
        List<Data>::RemoveFromFront();
    }
    template<typename Data>
    Data QueueLst<Data>::HeadNDequeue() {
        return List<Data>::FrontNRemove();
    }
    template<typename Data>
    void QueueLst<Data>::Clear() {
        List<Data>::Clear();
    }


/* ************************************************************************** */

}
