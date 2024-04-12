

template <typename T>
class Node {
private:
    T data;
    Node* left = nullptr;
    Node* right = nullptr;
public:
    Node(Node const& original) : data(original.data), Node()
    {   
        left = new Node(*original.left);
        right = new Node(*original.right);      
    }

    Node(Node&& original)
    {
        this->data = original.data;
        this->left = original.left;
        original.left = nullptr;
        this->right = original.right;
        original.right = nullptr;
    }

    ~Node()
    {
        left->~Node();
        right->~Node();
        data.~T();
    }

    Node& operator=(Node rhs)
    {
        std::swap(left, rhs.left);
        std::swap(right, rhs.right);
        std::swap(data, rhs.data);
        return *this;
    }
};