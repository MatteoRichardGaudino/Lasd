
namespace lasd {

/* ************************************************************************** */
    template<typename Data>
    StackLst<Data>::~StackLst(){
        Clear();
    }

    template<typename Data>
    StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& sl){
        List<Data>::operator=(sl);
        return *this;
    }

    template<typename Data>
    StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& sl) noexcept{
        List<Data>::operator=(std::move(sl));
        return *this;
    }

    template<typename Data>
    bool StackLst<Data>::operator==(const StackLst& sl) const noexcept{
        return List<Data>::operator==(sl);
    }
    template<typename Data>
    bool StackLst<Data>::operator!=(const StackLst& sl) const noexcept{
        return !(operator==(sl));
    }

    template<typename Data>
    void StackLst<Data>::Push(const Data& data){
        List<Data>::InsertAtFront(data);
    }
    template<typename Data>
    void StackLst<Data>::Push(Data&& data){
        List<Data>::InsertAtFront(std::move(data));
    }

    template<typename Data>
    Data& StackLst<Data>::Top() const{
        return List<Data>::Front();
    }

    template<typename Data>
    void StackLst<Data>::Pop(){
        List<Data>::RemoveFromFront();
    }
    template<typename Data>
    Data StackLst<Data>::TopNPop(){
        return List<Data>::FrontNRemove();
    }

    template<typename Data>
    void StackLst<Data>::Clear(){
        List<Data>::Clear();
    }


/* ************************************************************************** */

}
