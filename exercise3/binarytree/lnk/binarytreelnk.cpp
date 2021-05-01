
namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data e) {
        element = e;
    }

    template<typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk& root){
        //element = root.element;
        //if (root.HasLeftChild()){
        //    left = new NodeLnk();
        //    AuxCopyNode(left, root.left);
        //}
        //if (root.HasRightChild()){
        //    right = new NodeLnk();
        //    AuxCopyNode(right, root.right);
        //}
        AuxCopyNode(this, &root);
    }

    template<typename Data>
    void BinaryTreeLnk<Data>::NodeLnk::AuxCopyNode(NodeLnk* nodecpy, const NodeLnk* node){
        nodecpy->element = node->element;
        if (node->HasLeftChild()){
            nodecpy->left = new NodeLnk();
            AuxCopyNode(nodecpy->left, node->left);
        }
        if (node->HasRightChild()){
            nodecpy->right = new NodeLnk();
            AuxCopyNode(nodecpy->right, node->right);
        }
    }

    template<typename Data>
    Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept{
        return element;
    }

    template<typename Data>
    const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept {
        return element;
    }

    template<typename Data>
    bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept{
        return left == nullptr;
    }
    template<typename Data>
    bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild()const noexcept{
        return right == nullptr;
    }

    template<typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const{
        if (HasLeftChild()) return *left;
        else throw std::out_of_range("Left child does not exist");
    }

    template<typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
        if (HasRightChild()) return *right;
        else throw std::out_of_range("Right child does not exist");
    }

    template<typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data>& linearContainer){
        if (linearContainer.Size() != 0){
            root = new NodeLnk(linearContainer[0]);
            AuxCopyLinearContainer(linearContainer, 0, root);
            size = linearContainer.Size();
        }
    }

    template<typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& bt){
        if (bt.size != 0){
            root = new NodeLnk(bt.Root());
            size = bt.size;
        }
    }

    template<typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& bt) noexcept{
        std::swap(root, bt.root);
        std::swap(size, bt.size);
    }
    template<typename Data>
    BinaryTreeLnk<Data>::~BinaryTreeLnk(){
        Clear();
    }

    template<typename Data>
    BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& bt){
        Clear();
        if (bt.size != 0){
            root = new NodeLnk(bt.Root());
            size = bt.size;
        }
        return *this;
    }
    template<typename Data>
    BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& bt) noexcept{
        std::swap(root, bt.root);
        std::swap(size, bt.size);
        return *this;
    }

    template<typename Data>
    bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data>& bt) const noexcept{
        return *root == *(bt.root);
    }

    template<typename Data>
    bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data>& bt) const noexcept{
        return !operator==(bt);
    }

    template<typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const{
        if (size != 0) return *root;
        else throw std::length_error("BinaryTreeLnk is empty");
    }

    template<typename Data>
    void BinaryTreeLnk<Data>::Clear(){
        size = 0;
        // TODO
    }

    template<typename Data>
    void BinaryTreeLnk<Data>::AuxCopyLinearContainer(const LinearContainer<Data>& lc, unsigned long i, NodeLnk* node){
        if ((i*2)+1 < lc.Size()){
            NodeLnk* newNode = new NodeLnk(lc[(i*2)+1]);
            node->left = newNode;
            AuxCreateNode(lc, i, (i*2)+1, newNode);
        }
        if ((i*2)+2 < lc.Size()){
            NodeLnk* newNode = new NodeLnk(lc[(i*2)+2]);
            node->right = newNode;
            AuxCreateNode(lc, i, (i*2)+2, newNode);
        }
    }


/* ************************************************************************** */

}
