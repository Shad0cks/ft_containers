#ifndef VECTOR_REVERSE_ITERATOR_HPP
#define VECTOR_REVERSE_ITERATOR_HPP


namespace ft {

    template <class Iter>
    class vectorReverseIterator
    {   
        public :

            typedef typename Iter::difference_type difference_type;	
            typedef typename Iter::value_type value_type;
            typedef typename Iter::pointer pointer;
            typedef typename Iter::reference reference;	
            typedef typename Iter::const_pointer const_pointer;	
            typedef typename Iter::const_reference const_reference;	

            vectorReverseIterator(void) : m_Ptr(nullptr) {};
            vectorReverseIterator(pointer ptr) : m_Ptr(ptr) {};
            vectorReverseIterator(VectorIterator<value_type> const & cpy) {this->m_Ptr = cpy.operator->();};
            vectorReverseIterator(const vectorReverseIterator & cpy) {*this = cpy;};
            virtual ~vectorReverseIterator(void) {};
            
            vectorReverseIterator & operator= (const vectorReverseIterator & cpy) {this->m_Ptr = cpy.m_Ptr; return *this;};

            //bool
            bool operator==(const vectorReverseIterator & b) const { return (this->m_Ptr == b.m_Ptr); };
            bool operator!=(const vectorReverseIterator & b) const { return (this->m_Ptr != b.m_Ptr); };
            bool operator>=(const vectorReverseIterator & b) const { return (this->m_Ptr <= b.m_Ptr); };
            bool operator<=(const vectorReverseIterator & b) const { return (this->m_Ptr >= b.m_Ptr); };
            bool operator<(const vectorReverseIterator & b) const { return (this->m_Ptr > b.m_Ptr); };
            bool operator>(const vectorReverseIterator & b) const { return (this->m_Ptr < b.m_Ptr); };


            vectorReverseIterator operator++(void) { this->m_Ptr--; return *this; };
            vectorReverseIterator operator--(void) { this->m_Ptr++; return *this; };
            vectorReverseIterator operator++(int) { this->m_Ptr--; return  vectorReverseIterator(this->m_Ptr + 1); };
            vectorReverseIterator operator--(int) { this->m_Ptr++; return  vectorReverseIterator(this->m_Ptr - 1); };

            vectorReverseIterator & operator+=(difference_type n) {this->m_Ptr -= n; return *this;};
            vectorReverseIterator & operator-=(difference_type n) {this->m_Ptr += n; return *this;};

            difference_type operator+(vectorReverseIterator b) { return (this->m_Ptr - b.m_Ptr);};
            difference_type operator-(vectorReverseIterator b) { return (this->m_Ptr + b.m_Ptr);};
            vectorReverseIterator operator+(difference_type n) { return (vectorReverseIterator(this->m_Ptr - n));}
            vectorReverseIterator operator-(difference_type n) { return (vectorReverseIterator(this->m_Ptr + n));}


            //momory acces
            reference operator*() { return (*this->m_Ptr); };
            const_reference operator*() const { return (*this->m_Ptr); };
            reference operator[](difference_type b) { return (*(this->m_Ptr + b)); };
            const_reference operator[](difference_type b) const { return (*(this->m_Ptr + b)); };
            pointer operator->() {return (this->m_Ptr); };
            pointer operator->() const {return (this->m_Ptr); };
            pointer base() const { return (m_Ptr); }
        private:
            pointer m_Ptr;
    };


	template <typename T>
	bool operator==(const vectorReverseIterator<T> &rhs,		const vectorReverseIterator<T> &lhs)			{ return (lhs.base() == rhs.base()); }
	template <typename U, typename V>
	bool operator==(const ft::vectorReverseIterator<U> &rhs,		const ft::vectorReverseIterator<V> &lhs)			{ return (lhs.base() == rhs.base()); }


	template <typename T>
	bool operator!=(const ft::vectorReverseIterator<T> &rhs,		const ft::vectorReverseIterator<T> &lhs)			{ return (lhs.base() != rhs.base()); }
	template <typename U, typename V>
	bool operator!=(const ft::vectorReverseIterator<U> &rhs,		const ft::vectorReverseIterator<V> &lhs)			{ return (lhs.base() != rhs.base()); }
	
	template <typename T>
	bool operator>=(const ft::vectorReverseIterator<T> &rhs,		const ft::vectorReverseIterator<T> &lhs)			{ return (lhs.base() >= rhs.base()); }
	template <typename U, typename V>
	bool operator>=(const ft::vectorReverseIterator<U> &rhs,		const ft::vectorReverseIterator<V> &lhs)			{ return (lhs.base() >= rhs.base()); }

	template <typename T>
	bool operator<=(const ft::vectorReverseIterator<T> &rhs, 		const ft::vectorReverseIterator<T> &lhs)		{ return (lhs.base() <= rhs.base()); }
	template <typename U, typename V>
	bool operator<=(const ft::vectorReverseIterator<U> &rhs, 		const ft::vectorReverseIterator<V> &lhs)		{ return (lhs.base() <= rhs.base()); }

	template <typename T>
	bool operator>(const ft::vectorReverseIterator<T> &rhs,		const ft::vectorReverseIterator<T> &lhs)			{ return (lhs.base() > rhs.base()); }
	template <typename U, typename V>
	bool operator>(const ft::vectorReverseIterator<U> &rhs,		const ft::vectorReverseIterator<V> &lhs)			{ return (lhs.base() > rhs.base()); }

	template <typename T>
	bool operator<(const ft::vectorReverseIterator<T> &rhs, 		const ft::vectorReverseIterator<T> &lhs)			{ return (lhs.base() < rhs.base()); }
	template <typename U, typename V>
	bool operator<(const ft::vectorReverseIterator<U> &rhs, 		const ft::vectorReverseIterator<V> &lhs)			{ return (lhs.base() < rhs.base()); }

	template <typename T>
	ft::vectorReverseIterator<T> operator+(typename ft::vectorReverseIterator<T>::difference_type rhs, const ft::vectorReverseIterator<T> &lhs)						{ return (lhs.base() - rhs); }
	template <typename U, typename V>
	ft::vectorReverseIterator<U> operator+(typename ft::vectorReverseIterator<U>::difference_type rhs, const ft::vectorReverseIterator<V> &lhs)						{ return (lhs.base() - rhs); }
	
	template <typename T>
	ft::vectorReverseIterator<T> operator+(const ft::vectorReverseIterator<T> &rhs, typename ft::vectorReverseIterator<T>::difference_type lhs)						{ return (rhs.base() - lhs); }
	template <typename U, typename V>
	ft::vectorReverseIterator<U> operator+(const ft::vectorReverseIterator<U> &rhs, typename ft::vectorReverseIterator<V>::difference_type lhs)						{ return (rhs.base() - lhs); }

	template <typename T>
	ft::vectorReverseIterator<T> operator-(const ft::vectorReverseIterator<T> &rhs, typename ft::vectorReverseIterator<T>::difference_type lhs)						{ return (rhs.base() + lhs); }
	template <typename U, typename V>
	ft::vectorReverseIterator<U> operator-(const ft::vectorReverseIterator<U> &rhs, typename ft::vectorReverseIterator<V>::difference_type lhs)						{ return (rhs.base() + lhs); }

	template <typename T>
	typename ft::vectorReverseIterator<T>::difference_type operator-(const ft::vectorReverseIterator<T> &rhs, const ft::vectorReverseIterator<T> &lhs)					{ return (lhs.base() - rhs.base()); }
	template <typename U, typename V>
	typename ft::vectorReverseIterator<U>::difference_type operator-(const ft::vectorReverseIterator<V> &rhs, const ft::vectorReverseIterator<U> &lhs)					{ return (lhs.base() - rhs.base()); }


}

#endif