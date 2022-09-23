
namespace ft
{
    template <class Key, class mapped_value>
    void debug_tree(const ft::Node<Key, mapped_value> * p, int indent)
    {
        if(p != NULL) 
        {
            if(p->right)
                debug_tree(p->right, indent+4);
            if (indent) 
                std::cout << std::setw(indent) << ' ';
            if (p->right)
                std::cout<<" /\n" << std::setw(indent) << ' ';
            std::cout<< p->get_key() << "\n ";
            if(p->left)
            {
                std::cout << std::setw(indent) << ' ' <<" \\\n";
                debug_tree(p->left, indent+4);
            }
        }
    }
}
