#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <vector>
#include <string>
#include "../vector_utils/Iterator/vectorIterator.hpp"
#include "../vector_utils/Iterator/vectorConstIterator.hpp"
#include "../vector_utils/Iterator/vectorReverseIterator.hpp"
#include "../vector_utils/Iterator/vectorConstReverseIterator.hpp"
#include "../vector_utils/utils/algorithme.hpp"
#include "../vector_utils/utils/type_traits.hpp"

namespace ft 
{
    template <class T, class Alloc = std::allocator<T> >

    class vector
    {   
        public:
            typedef T value_type;
            typedef T * pointer;
            typedef const T * const_pointer;
            typedef T & reference;
            typedef const T & const_reference;
            typedef std::size_t size_type;
            typedef  Alloc allocator_type;

            typedef typename ft::VectorIterator<T> iterator; 
            typedef typename ft::vectorConstIterator<T> const_iterator; 
            typedef typename ft::vectorConstReverseIterator<iterator> const_reverse_iterator; 
            typedef typename ft::vectorReverseIterator<iterator> reverse_iterator; 

            explicit vector (const allocator_type& alloc = allocator_type()) : m_Size(0),  m_Capacity(0), m_Data(nullptr), m_Alloc(alloc) { }
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : m_Alloc(alloc) 
            {
                if (n < 0)
                    throw std::length_error("vector");
                if (n == 0)
                    return ;
                this->m_Data = this->m_Alloc.allocate(n);
                for (size_type i = 0; i < n; i++)
                    this->m_Alloc.construct(this->m_Data + i, val);
                this->m_Capacity = n;
                this->m_Size = n;
            }   
            vector (const vector & x) : m_Size(0), m_Capacity(0),  m_Data(nullptr), m_Alloc(x.m_Alloc)
            {
                *this = x;
            }

           template <class InputIterator>
           vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0) : m_Alloc(alloc)
           {
		        size_type		n = 0;
                InputIterator cpy = first;

                while (cpy != last)
                {
                    cpy++;
                    n++;
                }

                this->m_Data = this->m_Alloc.allocate(n);
                
                for (size_t i = 0; i < n; i++)
                    this->m_Alloc.construct(this->m_Data + i, *first++);
                
                this->m_Capacity = n;
                this->m_Size = n;
           }

            ~vector(void)
            {
                this->clear();
                this->m_Alloc.deallocate(this->m_Data, this->m_Capacity);
            }

            void clear()
            {
                for (size_t i = 0; i < this->m_Size; i++)
                    this->m_Alloc.destroy(m_Data + i); 
                this->m_Size = 0;
            }

            void reserve(size_type n)
            {
                if (n > this->max_size())
                    throw std::length_error("Capacity overflow");
                if (n <= this->m_Capacity)
                    return ;
                T * t_Data = this->m_Alloc.allocate(n);
                
                if (n < this->m_Size)
                    this->m_Size = n;

                for (size_type i = 0; i < this->m_Size; i++)
                    this->m_Alloc.construct(t_Data + i, this->m_Data[i]);
                this->m_Alloc.deallocate(this->m_Data, this->m_Capacity);
                this->m_Data = t_Data;
                this->m_Capacity = n;
            }

            void push_back (const value_type& val)
            {
                if (this->m_Capacity == 0)
                {
                    this->m_Data = this->m_Alloc.allocate(1);
                    this->m_Capacity = 1;
                }
                else if (this->m_Size >= this->m_Capacity)
                    this->reserve(this->m_Capacity * 2);
                
                this->m_Alloc.construct(m_Data + m_Size, val);
                this->m_Size++;
            }

            void pop_back()
            {
                if (this->m_Size > 0)
                {
                    this->m_Size--;
                    this->m_Alloc.destroy(this->m_Data + this->m_Size); 
                }
            }

            void resize (size_type n, value_type val = value_type())
            {
                if (n < this->m_Size)
                    for (size_type i = n; i < this->m_Size; i++)
                        this->m_Alloc.destroy(this->m_Data + i); 
                else
                {
                    if (this->m_Capacity < n && this->m_Capacity * 2 >= n)
                        this->reserve(this->m_Capacity * 2);
                    else if (this->m_Capacity < n)
                        this->reserve(n);
                        
                    for (size_type i = this->m_Size; i < n; i++)
                        this->m_Alloc.construct(this->m_Data + i, val);
                }
                this->m_Size = n;
            }

            template <class InputIterator>
            void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
            {
                this->clear();
                size_type n = 0;

                for (InputIterator cpy = first; cpy != last; cpy++)
                    n++;
                
                if (this->m_Capacity < n)
                    this->reserve(n);

                for (size_type i = 0; i < n; i++)
                    this->m_Alloc.construct(this->m_Data + i, *first++);
                this->m_Size = n;
            }

            void assign (size_type n, const value_type& val)
            {
                this->clear();
                if (this->m_Capacity < n)
                    this->reserve(n);

                for (size_type i = 0; i < n; i++)
                    this->m_Alloc.construct(this->m_Data + i, val);
                this->m_Size = n;
            }

            iterator insert (iterator position, const value_type& val)
            {

                size_type n = ft::distance(this->begin(), position);

                insert(position, 1, val);
                return (iterator(&(this->m_Data[n])));
            }

            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
            {
                vector temp(position, this->end());

                this->m_Size -= ft::distance(position, this->end());

                while (first != last)
                {
                    this->push_back(*first);
                    first++;
                }

                for (iterator i = temp.begin(); i != temp.end(); i++)
                    this->push_back(*i);
            }

            void insert (iterator position, size_type n, const value_type& val)
            {
                vector temp(position, this->end());

                this->m_Size -= ft::distance(position, this->end());

                for (size_t i = 0; i < n; i++)
                    this->push_back(val);
                
                for (iterator i = temp.begin(); i != temp.end(); i++)
                    this->push_back(*i);
            }

            iterator erase (iterator position)
            {
                iterator tmp = iterator(position);
                this->m_Alloc.destroy(m_Data + ft::distance(this->begin(), position));

                for (iterator i = position; i < this->end() - 1; i++)
                {
                    *position = *(position + 1);
                    position++;
                }
                this->m_Size--;
                return (tmp);
                    
            }
            iterator erase (iterator first, iterator last)
            {
                iterator tmp = iterator(first);
                iterator tmp2 = iterator(first);
                while(tmp != last)
                {
                   this->m_Alloc.destroy(m_Data + ft::distance(this->begin(), tmp));
                   tmp++;
                }
                
                vector temp(last, this->end());
                
                for (iterator i = temp.begin(); i != temp.end(); i++)
                {
                    *first = *i;
                    first++;
                }
                this->m_Size -=  ft::distance(tmp2, last);
                return (tmp2);
            }

            void swap (vector & x)
            {
                std::swap(this->m_Alloc, x.m_Alloc);
                std::swap(this->m_Size, x.m_Size);
                std::swap(this->m_Capacity, x.m_Capacity);
                std::swap(this->m_Data, x.m_Data);
            }

            reference at (size_type n)
            {
                if (n >= this->m_Size || n < 0)
                    throw std::out_of_range("index out of range");
                return (this->m_Data[n]);
            }

            const_reference at (size_type n) const
            {
                if (n >= this->m_Size || n < 0)
                    throw std::out_of_range("index out of range");
                return (this->m_Data[n]);
            }

            reference front()
            {
                return (this->m_Data[0]);
            }

            const_reference front() const
            {
                return (this->m_Data[0]);
            }

            reference back()
            {
                return (this->m_Data[this->m_Size - 1]);
            }

            const_reference back() const
            {
                return (this->m_Data[this->m_Size - 1]);
            }

            bool empty() const
            {
                return (this->m_Size == 0);
            }

            size_type max_size() const
            {
                return this->m_Alloc.max_size();
            }

            size_type capacity() const
            {
                return this->m_Capacity;
            }

            size_type size() const
            {
                return this->m_Size;
            }


            vector & operator= (const vector & x)
            {
                for (size_t i = 0; i < this->m_Size; i++)
                    this->m_Alloc.destroy(m_Data + i); 
                    
                if (this->m_Capacity < x.m_Capacity)
                {
                    if (this->m_Capacity > 0)
                        this->m_Alloc.deallocate(this->m_Data, this->m_Capacity);
                    this->m_Data = this->m_Alloc.allocate(x.m_Size);
                    this->m_Capacity = x.m_Size;
                }
                for (size_type i = 0; i < x.m_Size; i++)
                    this->m_Alloc.construct(m_Data + i, x[i]);
                
                this->m_Size = x.m_Size;
                return (*this);
            }

            reference operator[] (size_type n)
            {
                return this->m_Data[n];
            }

            const_reference operator[] (size_type n) const
            {
                return this->m_Data[n];
            }

            allocator_type get_allocator() const
            {
                return (allocator_type());
            }

            iterator begin()
            {
                return (iterator(this->m_Data));
            }

            iterator end()
            {
                return (iterator(this->m_Data + this->m_Size));
            }

            
            const_iterator begin() const
            {
                return (const_iterator(this->m_Data));
            }

            const_iterator end() const
            {
                return (const_iterator(this->m_Data + this->m_Size));
            }
            
            reverse_iterator rbegin()
            {
                return (reverse_iterator((this->end()) - 1));
            }

            reverse_iterator rend()
            {
                return (reverse_iterator((this->begin() - 1)));
            }

            const_reverse_iterator rbegin() const
            {
                return (this->rbegin());
            }

            const_reverse_iterator rend() const
            {
                return (this->rend());
            }
        
        private:
            size_type m_Size;
            size_type m_Capacity;
            T * m_Data;
            Alloc m_Alloc;
    };
    
    template<class T, class Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return(ft::equal(lhs.begin(), lhs.end() ,rhs.begin(), rhs.end()));}
    template<class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return(!(lhs == rhs));}
    template<class T, class Alloc>
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}
    template<class T, class Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (!(lhs > rhs));}
    template<class T, class Alloc>
    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (rhs < lhs);}
    template<class T, class Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (!(lhs < rhs));}

    template <class T, class Alloc>
    void swap (vector<T, Alloc> & x, vector<T, Alloc> & y)
    {
        y.swap(x);
    }
}

#endif