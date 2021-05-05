namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& e) {
        element = e;
    }
    template<typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data&& e) {
        std::swap(element, e);
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
        AuxCopyNode(this, root);
    }


    template<typename Data>
    void BinaryTreeLnk<Data>::NodeLnk::AuxCopyNode(NodeLnk* nodecpy, const Node& node){
        nodecpy->element = node.Element();
        if (node.HasLeftChild()){
            nodecpy->left = new NodeLnk();
            AuxCopyNode(nodecpy->left, node.LeftChild());
        }
        if (node.HasRightChild()){
            nodecpy->right = new NodeLnk();
            AuxCopyNode(nodecpy->right, node.RightChild());
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
        return left != nullptr;
    }
    template<typename Data>
    bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild()const noexcept{
        return right != nullptr;
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
            FromLinearContainer(linearContainer, root, 0);
            size = linearContainer.Size();
        }
    }
    template<typename Data>
    void BinaryTreeLnk<Data>::FromLinearContainer(const LinearContainer<Data>& lc, NodeLnk* node, unsigned long i) {
        if (i*2 + 1 < lc.Size()){
            node->left = new NodeLnk(lc[i*2 + 1]);
            FromLinearContainer(lc, node->left, i*2 + 1);
        }
        if (i*2 + 2 < lc.Size()){
            node->right = new NodeLnk(lc[i*2 + 2]);
            FromLinearContainer(lc, node->right, i*2 + 2);
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
        if (!Empty() && !bt.Empty())
            return Root() == bt.Root();
        else if (Empty() && bt.Empty()) return true;
        else return false;

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
        PostOrderClear(root);
        root = nullptr;
        size = 0;
    }
    template<typename Data>
    void BinaryTreeLnk<Data>::PostOrderClear(NodeLnk* node){
        if (node != nullptr){
            PostOrderClear(node->left);
            PostOrderClear(node->right);
            delete node;
        }
    }

/* ************************************************************************** */

}
