#include "../map_utils/binary_tree.hpp"
#include <map>
#include <algorithm>
#include "../map_utils/debug_tree.hpp"

namespace ft
{

    template < class Key,                                     // map::key_type
            class T,                                       // map::mapped_type
            class Compare = ft::less<Key>,                     // map::key_compare
            class Alloc = std::allocator< ft::Node<Key, T>  >    // map::allocator_type
            >
    class map
    {

        public :
            
            typedef Key key_type;
            typedef T mapped_type;
            typedef ft::pair<const Key, T> value_type;
            typedef ft::pair<Key, T> value_nConst;
            typedef Compare key_compare;
            typedef Alloc allocator_type;
            typedef value_type & reference;
            typedef value_type const & const_reference;
            typedef value_type * pointer;
            typedef value_type const * const_pointer;
            typedef ft::mapIterator<key_type, mapped_type> iterator;
            typedef ft::mapConstIterator<key_type, mapped_type> const_iterator;
            typedef ft::mapReverseIterator<key_type, mapped_type> reverse_iterator;
            typedef ft::mapConstReverseIterator<key_type, mapped_type> const_reverse_iterator;
            typedef std::ptrdiff_t difference_type;
            typedef std::size_t size_type;

            class value_compare : public ft::binary_function<value_type, value_type, bool>
            {
                friend class map<Key, T, Compare, Alloc>;

                public:
                    bool operator()(const value_type& left, const value_type& right) const
                    {
                        return (this->_Comp(left.first, right.first));
                    }

                    bool operator()(const value_nConst& left, const value_nConst& right) const
                    {
                        return (this->_Comp(left.first, right.first));
                    }

                    value_compare(Compare pred) : _Comp(pred) {};

                protected:
                    Compare _Comp;
            };


            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :  m_Alloc(alloc), m_Comp(comp), tree()
            {

            }
            
            //copy
            map (const map& x) : m_Alloc(x.m_Alloc), m_Comp(x.m_Comp),  tree(true)
            {
                if (x.size() > 0)
                    this->insert(x.begin(), x.end());
            }
            
            //itrerator
            template <class InputIterator>
            map (InputIterator first, InputIterator last,  const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : m_Alloc(alloc), m_Comp(comp), tree()
            {
                this->insert(first, last);
            }

            map & operator= (const map& x)
            {
                this->tree.clearD();
                if (this->tree.get_ptr_head() != nullptr)
                    this->tree.clear();
                if (x.size() > 0)
                    this->insert(x.begin(), x.end());
                return (*this);
            }

            virtual ~map(void)
            {
                if (this->tree.get_size() > 0)
                    this->tree.clear();
            }

            iterator begin()
            {
                tree.put_fake_node();
                
                if (this->tree.get_ptr_head() == nullptr)
                {
                    iterator p(this->tree.end);
                    return p;
                }
                iterator t(this->tree.start->parent);
                return (t);
            }

            iterator end()
            {
                iterator t(this->tree.end);
                return (t);
            }

            const_iterator begin() const
            {                
                if (this->tree.get_ptr_head() == nullptr)
                {
                    const_iterator p(this->tree.end);
                    return p;
                }
                const_iterator t(this->tree.start->parent);
                return (t);
            }

            const_iterator end() const
            {
                const_iterator t(this->tree.end);
                return (t);
            }

            reverse_iterator rbegin()
            {
                reverse_iterator t(this->tree.end->parent);
                return (t);
            }

            reverse_iterator rend()
            {                
                if (this->tree.get_ptr_head() == nullptr)
                {
                    reverse_iterator p(this->tree.end->parent);
                    return p;
                }
                reverse_iterator t(this->tree.start);
                return (t);
            }

            const_reverse_iterator rbegin() const
            {
                const_reverse_iterator t(this->tree.end->parent);
                return (t);
            }

            const_reverse_iterator rend() const
            {                
                if (this->tree.get_ptr_head() == nullptr)
                {
                    const_reverse_iterator p(this->tree.end->parent);
                    return p;
                }
                const_reverse_iterator t(this->tree.start);
                return (t);
            }

            iterator find (const key_type& k)
            {                
                iterator n(this->tree.start);
                while (n->first != k && n != this->end())
                    n++;
                return (n);
            }   

            const_iterator find (const key_type& k) const
            {
                const_iterator n(this->tree.start);
                while (n->first != k && n != this->end())
                    n++;
                return (n);
            }

            iterator lower_bound (const key_type& k)
            {
                iterator it = this->begin();

                while (m_Comp(it->first, k) == true && it != this->end())
                {
                    it++;
                }
                return (it);
            }

            const_iterator lower_bound (const key_type& k) const
            {
               const_iterator it = this->begin();

                while (m_Comp(it->first, k) == true && it != this->end())
                {
                    it++;
                }
                return (it);
            }

            iterator upper_bound (const key_type& k)
            {
                for (iterator it = begin(); it != end(); it++)
                    if (m_Comp(k, it->first))
                        return it;
                
                return (this->end());
            }

            const_iterator upper_bound (const key_type& k) const
            {
                for (const_iterator it = begin(); it != end(); it++)
                    if (m_Comp(k, it->first))
                        return it;
                
                return (this->end());
            }


            pair<const_iterator,const_iterator> equal_range (const key_type& k) const
            {
                return (pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
            }

            pair<iterator,iterator>             equal_range (const key_type& k)
            {
                return (pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
            }

            bool empty() const
            {
                return (this->tree.get_size() == 0);
            }

            size_type size() const
            {
                return (this->tree.get_size());
            }

            size_type max_size() const
            {
                return std::map<key_type, mapped_type>().max_size() ;;
            }

            mapped_type & operator[] (const key_type& k)
            {
                return this->tree[k];
            }


            // mapped_type& at (const key_type& k)
            // {
            //    return tree.at(k);
            // }

            // const mapped_type& at (const key_type& k) const
            // {
            //     return tree.at(k);
            // }

            iterator insert (iterator position, const value_type& val)
            {
                (void)position;
			    return insert(val).first;
            }

            iterator insert (iterator position, const value_nConst& val)
            {
                (void)position;
			    return insert(val).first;
            }

            pair<iterator,bool> insert (const value_type& val)
            {
                if (this->count(val.first) == 1)
                    return pair<iterator, bool>(find(val.first), false);
                ft::Node<key_type, mapped_type> t(ft::make_pair(val.first, val.second));
                this->tree.insert(t, true);
                return pair<iterator, bool>(iterator(tree.tmpCreatedNode), true);
            }

            pair<iterator,bool> insert (const value_nConst& val)
            {
                if (this->count(val.first) == 1)
                    return pair<iterator, bool>(find(val.first), false);
                ft::Node<key_type, mapped_type> t(ft::make_pair(val.first, val.second));    
                this->tree.insert(t, true);            
                return pair<iterator, bool>(iterator(tree.tmpCreatedNode), true);
            }
        
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last)
            {
                while (first != last)
                {
                    insert(ft::make_pair((*first).first, (*first).second));
                    first++;
                }
            }

            void erase (iterator position)
            {
                
                this->tree.erase(position->first);
            }

            size_type erase (const key_type& k)
            {
                this->tree.erase(k);
                return this->tree.get_size();
            }

            void erase (iterator first, iterator last)
            {    
                size_t i = ft::distance(first, last);
                while (first != last  && i > 0)
                {
                    this->erase(first++);
                    i--;
                }
                
            }

            void swap (map& x)
            {
                binary_tree<key_type, mapped_type, Compare, allocator_type> tmp(false);

                tmp = this->tree;
                this->tree = x.tree;
                x.tree = tmp;
                tmp.start = nullptr;
                tmp.end = nullptr;
            }

            void clear()
            {
                this->tree.clearD();
                this->tree.clear();
            }

            key_compare key_comp() const
            {
                return (key_compare());
            }

            value_compare value_comp() const
            {
                return (value_compare(Compare()));
            }

            size_type count (const key_type& k) const
            {
                try
                {
                    this->tree.at(k);
                }
                catch(const std::exception& e)
                {
                    return 0;
                }
                return 1;
            }

            allocator_type get_allocator() const
            {
                return (Alloc());
            }

            ft::Node<key_type, mapped_type> *  first(void)
            {
                return (this->tree.get_ptr_head());
            }
            

        private :
            Alloc m_Alloc;
            Compare m_Comp;
            binary_tree<Key, mapped_type, Compare, Alloc> tree;
    };


    template <class _Key, class _Tp, class _Compare, class _Allocator>
    bool
    operator==(const ft::map<_Key, _Tp, _Compare, _Allocator>& __x,
            const ft::map<_Key, _Tp, _Compare, _Allocator>& __y)
    {
        return __x.size() == __y.size() && ft::equal(__x.begin(), __x.end(), __y.begin(), __y.end());
    }

    template <class _Key, class _Tp, class _Compare, class _Allocator>
    bool
    operator< (const ft::map<_Key, _Tp, _Compare, _Allocator>& __x,
            const ft::map<_Key, _Tp, _Compare, _Allocator>& __y)
    {
        return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
    }

    template <class _Key, class _Tp, class _Compare, class _Allocator>
    bool
    operator!=(const ft::map<_Key, _Tp, _Compare, _Allocator>& __x,
            const ft::map<_Key, _Tp, _Compare, _Allocator>& __y)
    {
        return !(__x == __y);
    }

    template <class _Key, class _Tp, class _Compare, class _Allocator>
    bool
    operator> (const ft::map<_Key, _Tp, _Compare, _Allocator>& __x,
            const ft::map<_Key, _Tp, _Compare, _Allocator>& __y)
    {
        return __y < __x;
    }

    template <class _Key, class _Tp, class _Compare, class _Allocator>
    bool
    operator>=(const ft::map<_Key, _Tp, _Compare, _Allocator>& __x,
            const ft::map<_Key, _Tp, _Compare, _Allocator>& __y)
    {
        return !(__x < __y);
    }

    template <class _Key, class _Tp, class _Compare, class _Allocator>
    bool
    operator<=(const ft::map<_Key, _Tp, _Compare, _Allocator>& __x,
            const ft::map<_Key, _Tp, _Compare, _Allocator>& __y)
    {
        return !(__y < __x);
    }

    template <class _Key, class _Tp, class _Compare, class _Allocator>
    void
    swap(ft::map<_Key, _Tp, _Compare, _Allocator>& __x,
        ft::map<_Key, _Tp, _Compare, _Allocator>& __y)
        _NOEXCEPT_(_NOEXCEPT_(__x.swap(__y)))
    {
        __x.swap(__y);
    }
    
    
}









