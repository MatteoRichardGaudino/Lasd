
namespace lasd {

/* ************************************************************************** */

    template <typename Data>
    bool FoldableContainer<Data>::Exists(const Data& data) const noexcept{
        bool exists = false;
        FoldPreOrder([](const Data& dat, const void* val, void* ex){
            if (dat == *((Data*) val)) *((bool*) ex) = true;
        }, data, &exists);
        return exists;
    }

/* ************************************************************************** */

}
