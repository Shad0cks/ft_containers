#ifndef NODE_HPP
#define NODE_HPP

namespace ft
{
    template <class key, class mapped_type>
    struct Node
    {
        public :
            typedef ft::pair<key, mapped_type>  value_type;
            typedef ft::pair<const key, mapped_type>  pair;
            typedef const key const_key;
            typedef const mapped_type const_mapped_type;

            Node *parent;
            Node *left;
            Node *right;
            int deep;
            
            Node (Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr) : parent(parent), left(left), right(right), deep(1), value()
            {
            }

            Node (value_type const & val, Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr) : parent(parent), left(left), right(right), deep(1), value(val)
            {
            }

            int check_val(Node * n)
            {
                if (n)
                    return n->deep;
                return 0;
            }

            void updateDeep(void)
            {
                this->deep = std::max(check_val(this->left), check_val(this->right)) + 1;
            }

            value_type get_pair(void) const
            {
                return this->value;
            }

            
            pair * get_ptr_pair(void)
            {
                
                return ((reinterpret_cast<pair *>((&this->value))));
            }

            pair const * get_ptr_pair(void) const
            {
                return ((reinterpret_cast<pair const *>((&this->value))));
            }

            void set_key(key const & newKey)
            {
                this->value.first = newKey;
            }

            void set_value(value_type const & val)
            {
                this->value = val;
            }

            void set_mapped_type(mapped_type const & type)
            {
                this->value.second = type;
            }

            const_key & get_key(void) const
            {
                return (this->value.first);
            }
            const_mapped_type & get_mapped_type(void) const
            {
                return (this->value.second);
            }

            mapped_type & get_mapped_type(void)
            {
                return (this->value.second);
            }

            Node (Node const & cpy) 
            {
                *this = cpy;
            }

            Node & operator=(Node const & cpy)
            {
                if (this == &cpy)
                    return (*this);
                this->left = cpy.left;
                this->parent = cpy.parent;
                this->right = cpy.right;
                this->value = cpy.value;
                this->deep = cpy.deep;
                return(*this);
            }

            bool operator==(Node const & toCmp)
            {
                return (this->value == toCmp.value);
            }
        
            virtual ~Node(void) { };
            value_type value;
        
            
    };
    
    template <class key, class mapped_type>
    std::ostream & operator << (std::ostream & o, Node<key, mapped_type> const & node)
    {
        o << "Key : " << node.get_key() << " / deep : " << node.deep  << std::endl;
        return o;
    }
}



#endif