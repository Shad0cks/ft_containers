#include "../utils.hpp"
#include "../Node.hpp"

namespace ft
{
    template <class Key, class T, class Compare = ft::less<Key> > 
    class mapIterator
    {
        public :
            typedef Key key_type;
            typedef T mapped_type;

            typedef Compare key_compare;
            typedef std::size_t size_type;

            typedef Node<key_type, mapped_type>	node;
	        typedef node *					node_ptr;

            typedef ft::pair<const key_type, mapped_type>	value_type;


            typedef value_type *                    pointer;
            typedef const value_type *              const_pointer;
            typedef value_type &                    reference;
            typedef const value_type &              const_reference;

            typedef mapped_type const const_mapped_type;
       
       
        mapIterator (void) { }

        mapIterator(node_ptr ptr) : actualNode(ptr) {  }
        mapIterator(mapIterator const & cpy) : actualNode(cpy.actualNode) {}

       mapIterator & operator++()
       {
           this->nextNode();
           return (*this);
       }

       mapIterator operator++(int)
       {
           mapIterator<key_type, mapped_type> tmp(*this);
           this->nextNode();
           return (tmp);
       }

       bool operator==(mapIterator const & cpm)
       {
           return (this->actualNode == cpm.actualNode);
       }

       bool operator!=(mapIterator const & cpm)
       {
           return (this->actualNode != cpm.actualNode);
       }

       mapIterator & operator--()
       {    
           this->prevNode();
            return (*this);
       }

       mapIterator operator--(int)
       {
            mapIterator<key_type, mapped_type> tmp;
            this->prevNode();
            return (tmp);
       }

       mapIterator & operator=(mapIterator const & other)
       {
           actualNode = other.actualNode;
           return (*this);
       }
        node_ptr	get_ptr(void) const { return (actualNode); };
        mapIterator base(void) const { return ( this->actualNode ) ; };
        reference operator*() { return (*this->actualNode->get_ptr_pair()); };
        const_reference operator*() const { return (*this->actualNode->get_ptr_pair()); };
        pointer operator->() {return ((this->actualNode->get_ptr_pair())); };
        pointer operator->() const {return (this->actualNode->get_ptr_pair()); };
        static bool const input_iter = true;
       private:
            node_ptr actualNode;
            void nextNode(void)
            {
                node_ptr next;
				if (!actualNode->right)
				{
                    
					next = actualNode;
					while (next->parent && next == next->parent->right)
						next = next->parent;
					next = next->parent;
				}
				else
				{
					next = actualNode->right;
					while (next->left)
						next = next->left;
				}
                actualNode = next;
                
				return ;
            }

       void prevNode(void)
       {
           node_ptr next;

            if (!actualNode->left)
            {
                next = actualNode;
                while (next->parent && next == next->parent->left)
                    next = next->parent;
                next = next->parent;
            }
            else
            {
                next = actualNode->left;
                while (next->right)
                    next = next->right;
            }
            actualNode = next;
            return ;
       }
    };


    template <class Key, class T, class Compare = ft::less<Key> > 
    class mapConstIterator
    {
        public :
            typedef Key key_type;
            typedef T mapped_type;

            typedef Compare key_compare;
            typedef std::size_t size_type;

            typedef Node<key_type, mapped_type>	node;
	        typedef node *					node_ptr;

            typedef ft::pair<const key_type, mapped_type>	value_type;


            typedef value_type *                    pointer;
            typedef const value_type *              const_pointer;
            typedef value_type &                    reference;
            typedef const value_type &              const_reference;

            typedef mapped_type const const_mapped_type;
       
       
        mapConstIterator (void) { }

        mapConstIterator(node_ptr ptr) : actualNode(ptr) {  }
        mapConstIterator(mapConstIterator const & cpy) : actualNode(cpy.actualNode) {}
        mapConstIterator(const mapIterator<key_type, mapped_type, Compare> &src) : actualNode(src.get_ptr()) {}

       mapConstIterator & operator++()
       {
           this->nextNode();
           return (*this);
       }

       mapConstIterator operator++(int)
       {
           mapConstIterator<key_type, mapped_type> tmp(*this);
           this->nextNode();
           return (tmp);
       }

       bool operator==(mapConstIterator const & cpm)
       {
           return (this->actualNode == cpm.actualNode);
       }

       bool operator!=(mapConstIterator const & cpm)
       {
           return (this->actualNode != cpm.actualNode);
       }

       mapConstIterator & operator--()
       {    
           this->prevNode();
            return (*this);
       }

       mapConstIterator operator--(int)
       {
            mapConstIterator<key_type, mapped_type> tmp;
            this->prevNode();
            return (tmp);
       }

       mapConstIterator & operator=(mapConstIterator const & other)
       {
           actualNode = other.actualNode;
           return (*this);
       }

        node_ptr	get_ptr(void) const { return (actualNode); };
       
        const_reference operator*() const { return (*this->actualNode->get_ptr_pair()); };
        const_pointer operator->() const {return (this->actualNode->get_ptr_pair()); };
        mapConstIterator base(void) const { return ( this->actualNode ) ; };

       static bool const input_iter = true;
       private:
            node_ptr actualNode;
            void nextNode(void)
            {
                node_ptr next;
				if (!actualNode->right)
				{
					next = actualNode;
					while (next->parent && next == next->parent->right)
						next = next->parent;
					next = next->parent;
				}
				else
				{
					next = actualNode->right;
					while (next->left)
						next = next->left;
				}
                actualNode = next;
				return ;
            }

       void prevNode(void)
       {
           node_ptr next;

            if (!actualNode->left)
            {
                next = actualNode;
                while (next->parent && next == next->parent->left)
                    next = next->parent;
                next = next->parent;
            }
            else
            {
                next = actualNode->left;
                while (next->right)
                    next = next->right;
            }
            actualNode = next;
            return ;
       }
    };

    template <class Key, class T, class Compare = ft::less<Key> > 
    class mapReverseIterator
    {
        public :
            typedef Key key_type;
            typedef T mapped_type;

            typedef Compare key_compare;
            typedef std::size_t size_type;

            typedef Node<key_type, mapped_type>	node;
	        typedef node *					node_ptr;

            typedef ft::pair<const key_type, mapped_type>	value_type;


            typedef value_type *                    pointer;
            typedef const value_type *              const_pointer;
            typedef value_type &                    reference;
            typedef const value_type &              const_reference;

            typedef mapped_type const const_mapped_type;
       
       
        mapReverseIterator (void) { }

        mapReverseIterator(node_ptr ptr) : actualNode(ptr) {  }
        mapReverseIterator(mapReverseIterator const & cpy) : actualNode(cpy.actualNode) {}
        mapReverseIterator(mapIterator<key_type, mapped_type, Compare> const & cpy) : actualNode(cpy.get_ptr()) {}

       mapReverseIterator & operator++()
       {
           this->prevNode();
           return (*this);
       }

       mapReverseIterator operator++(int)
       {
           mapReverseIterator<key_type, mapped_type> tmp(*this);
           this->prevNode();
           return (tmp);
       }

       bool operator==(mapReverseIterator const & cpm)
       {
           return (this->actualNode == cpm.actualNode);
       }

       bool operator!=(mapReverseIterator const & cpm)
       {
           return (this->actualNode != cpm.actualNode);
       }

       mapReverseIterator & operator--()
       {    
           this->nextNode();
            return (*this);
       }

       mapReverseIterator operator--(int)
       {
            mapReverseIterator<key_type, mapped_type> tmp;
            this->nextNode();
            return (tmp);
       }

       mapReverseIterator & operator=(mapReverseIterator const & other)
       {
           actualNode = other.actualNode;
           return (*this);
       }
        node_ptr	get_ptr(void) const { return (actualNode); };
       
        reference operator*() { return (*this->actualNode->get_ptr_pair()); };
        const_reference operator*() const { return (*this->actualNode->get_ptr_pair()); };
        pointer operator->() {return ((this->actualNode->get_ptr_pair())); };
        pointer operator->() const {return (this->actualNode->get_ptr_pair()); };
        mapReverseIterator base(void) const { return ( this->actualNode) ; };

       static bool const input_iter = true;
       private:
            node_ptr actualNode;
                   void nextNode(void)
            {
                node_ptr next;
				if (!actualNode->right)
				{
					next = actualNode;
					while (next->parent && next == next->parent->right)
						next = next->parent;
					next = next->parent;
				}
				else
				{
					next = actualNode->right;
					while (next->left)
						next = next->left;
				}
                actualNode = next;
				return ;
            }

       void prevNode(void)
       {
           node_ptr next;

            if (!actualNode->left)
            {
                next = actualNode;
                while (next->parent && next == next->parent->left)
                    next = next->parent;
                next = next->parent;
            }
            else
            {
                next = actualNode->left;
                while (next->right)
                    next = next->right;
            }
            actualNode = next;
            return ;
       }
    };


        template <class Key, class T, class Compare = ft::less<Key> > 
    class mapConstReverseIterator
    {
        public :
            typedef Key key_type;
            typedef T mapped_type;

            typedef Compare key_compare;
            typedef std::size_t size_type;

            typedef Node<key_type, mapped_type>	node;
	        typedef node *					node_ptr;

            typedef ft::pair<const key_type, mapped_type>	value_type;


            typedef value_type *                    pointer;
            typedef const value_type *              const_pointer;
            typedef value_type &                    reference;
            typedef const value_type &              const_reference;

            typedef mapped_type const const_mapped_type;
       
       
        mapConstReverseIterator (void) { }

        mapConstReverseIterator(node_ptr ptr) : actualNode(ptr) {  }
        mapConstReverseIterator(mapConstReverseIterator const & cpy) : actualNode(cpy.actualNode) {}
        mapConstReverseIterator(mapReverseIterator<key_type, mapped_type, Compare> const & cpy) : actualNode(cpy.get_ptr()) {}
        mapConstReverseIterator(mapIterator<key_type, mapped_type, Compare> const & cpy) : actualNode(cpy.get_ptr()) {}
        mapConstReverseIterator(mapConstIterator<key_type, mapped_type, Compare> const & cpy) : actualNode(cpy.get_ptr()) {}

       mapConstReverseIterator & operator++()
       {
           this->prevNode();
           return (*this);
       }

       mapConstReverseIterator operator++(int)
       {
           mapConstReverseIterator<key_type, mapped_type> tmp(*this);
           this->prevNode();
           return (tmp);
       }

       bool operator==(mapConstReverseIterator const & cpm)
       {
           return (this->actualNode == cpm.actualNode);
       }

       bool operator!=(mapConstReverseIterator const & cpm)
       {
           return (this->actualNode != cpm.actualNode);
       }

       mapConstReverseIterator & operator--()
       {    
           this->nextNode();
            return (*this);
       }

       mapConstReverseIterator operator--(int)
       {
            mapConstReverseIterator<key_type, mapped_type> tmp;
            this->nextNode();
            return (tmp);
       }

       mapConstReverseIterator & operator=(mapConstReverseIterator const & other)
       {
           actualNode = other.actualNode;
           return (*this);
       }
        node_ptr	get_ptr(void) const { return (actualNode); };
       
        const_reference operator*() const { return (*this->actualNode->get_ptr_pair()); };
        const_pointer operator->() const {return (this->actualNode->get_ptr_pair()); };
        mapConstReverseIterator base(void) const { return ( this->actualNode ) ; };

       static bool const input_iter = true;
       private:
            node_ptr actualNode;
                   void nextNode(void)
            {
                node_ptr next;
				if (!actualNode->right)
				{
					next = actualNode;
					while (next->parent && next == next->parent->right)
						next = next->parent;
					next = next->parent;
				}
				else
				{
					next = actualNode->right;
					while (next->left)
						next = next->left;
				}
                actualNode = next;
				return ;
            }

       void prevNode(void)
       {
           node_ptr next;

            if (!actualNode->left)
            {
                next = actualNode;
                while (next->parent && next == next->parent->left)
                    next = next->parent;
                next = next->parent;
            }
            else
            {
                next = actualNode->left;
                while (next->right)
                    next = next->right;
            }
            actualNode = next;
            return ;
       }
    };
}


namespace ft
{
    template <class Key, class T>
    bool operator== (const mapConstIterator<Key, T> &rhs, const mapConstIterator<Key, T> &lhs) {return rhs.base() == lhs.base();}
    template <class Key, class T>
    bool operator== (const mapIterator<Key, T> &rhs, const mapIterator<Key, T> &lhs) {return rhs.base() == lhs.base();}
    template <class Key, class T>
    bool operator== (const mapReverseIterator<Key, T> &rhs, const mapReverseIterator<Key, T> &lhs) {return rhs.base() == lhs.base();}
    template <class Key, class T>
    bool operator== (const mapConstReverseIterator<Key, T> &rhs, const mapConstReverseIterator<Key, T> &lhs) {return rhs.base() == lhs.base();}

    template <class Key, class T>
    bool operator< (const mapConstIterator<Key, T> &rhs, const mapConstIterator<Key, T> &lhs) {return rhs.base() < lhs.base();}
    template <class Key, class T>
    bool operator< (const mapIterator<Key, T> &rhs, const mapIterator<Key, T> &lhs) {return rhs.base() < lhs.base();}
    template <class Key, class T>
    bool operator< (const mapReverseIterator<Key, T> &rhs, const mapReverseIterator<Key, T> &lhs) {return rhs.base() < lhs.base();}
    template <class Key, class T>
    bool operator< (const mapConstReverseIterator<Key, T> &rhs, const mapConstReverseIterator<Key, T> &lhs) {return rhs.base() < lhs.base();}
    

    template <class Key, class T>
    bool operator> (const mapConstIterator<Key, T> &rhs, const mapConstIterator<Key, T> &lhs) {return rhs.base() > lhs.base();}
    template <class Key, class T>
    bool operator> (const mapIterator<Key, T> &rhs, const mapIterator<Key, T> &lhs) {return rhs.base() > lhs.base();}
    template <class Key, class T>
    bool operator> (const mapReverseIterator<Key, T> &rhs, const mapReverseIterator<Key, T> &lhs) {return rhs.base() > lhs.base();}
    template <class Key, class T>
    bool operator> (const mapConstReverseIterator<Key, T> &rhs, const mapConstReverseIterator<Key, T> &lhs) {return rhs.base() > lhs.base();}
    
        template <class Key, class T>
    bool operator== (const mapIterator<Key, T> &rhs, const mapReverseIterator<Key, T> &lhs) {return rhs.get_ptr() == lhs.get_ptr();}
}   