#ifndef VECTOR_REVERSE_CONST_ITERATOR_HPP
#define VECTOR_REVERSE_CONST_ITERATOR_HPP

namespace ft {

    template <typename Iter>
    class vectorConstReverseIterator
    {   
            
        public :

            typedef typename Iter::difference_type difference_type;	
            typedef typename Iter::value_type value_type;
            typedef typename Iter::pointer pointer;
            typedef typename Iter::reference reference;	
            typedef typename Iter::const_pointer const_pointer;	
            typedef typename Iter::const_reference const_reference;	

            vectorConstReverseIterator(void) : m_Ptr(nullptr) {};
            vectorConstReverseIterator(vectorConstIterator<value_type> const & cpy) {this->m_Ptr = cpy.base();};
            vectorConstReverseIterator(vectorReverseIterator<Iter> const &src) { this->m_Ptr = src.operator->(); } ;
            vectorConstReverseIterator(vectorConstReverseIterator const & cpy) {*this = cpy;};
            vectorConstReverseIterator(VectorIterator<value_type> const &src) { this->m_Ptr = src.operator->(); } ;

            virtual ~vectorConstReverseIterator(void) {};
            
            vectorConstReverseIterator & operator= (vectorConstReverseIterator const & cpy) {this->m_Ptr = cpy.m_Ptr; return *this;};

            //bool
            bool operator==(const vectorConstReverseIterator & b) const { return (this->m_Ptr == b.m_Ptr); };
            bool operator!=(const vectorConstReverseIterator & b) const { return (this->m_Ptr != b.m_Ptr); };
            bool operator>=(const vectorConstReverseIterator & b) const { return (this->m_Ptr <= b.m_Ptr); };
            bool operator<=(const vectorConstReverseIterator & b) const { return (this->m_Ptr >= b.m_Ptr); };
            bool operator<(const vectorConstReverseIterator & b) const { return (this->m_Ptr > b.m_Ptr); };
            bool operator>(const vectorConstReverseIterator & b) const { return (this->m_Ptr < b.m_Ptr); };


            vectorConstReverseIterator operator++(void) { this->m_Ptr--; return *this;};
            vectorConstReverseIterator operator--(void) { this->m_Ptr++; return *this; };
            vectorConstReverseIterator operator++(int) { this->m_Ptr--; return  vectorConstReverseIterator(this->m_Ptr + 1); };
            vectorConstReverseIterator operator--(int) { this->m_Ptr++; return  vectorConstReverseIterator(this->m_Ptr - 1); };

            vectorConstReverseIterator & operator+=(difference_type n) {this->m_Ptr -= n; return *this;};
            vectorConstReverseIterator & operator-=(difference_type n) {this->m_Ptr += n; return *this;};

            difference_type operator+(vectorConstReverseIterator b) { return (this->m_Ptr - b.m_Ptr);};
            difference_type operator-(vectorConstReverseIterator b) { return (this->m_Ptr + b.m_Ptr);};
            vectorConstReverseIterator operator+(difference_type n) { return (vectorConstReverseIterator(this->m_Ptr - n));}
            vectorConstReverseIterator operator-(difference_type n) { return (vectorConstReverseIterator(this->m_Ptr + n));}


            //momory acces
            const_reference operator*() const { return (*this->m_Ptr); };
            const_reference operator[](difference_type b) const { return (*(this->m_Ptr + b)); };
            pointer operator->() {return (this->m_Ptr); };
            pointer operator->() const {return (this->m_Ptr); };
            pointer base() const { return (m_Ptr); }
        private:
            pointer m_Ptr;
            vectorConstReverseIterator(pointer ptr) { this->m_Ptr = ptr; };
    };

}

namespace ft {
	template <typename T>
	bool operator==(const ft::vectorConstReverseIterator<T> &rhs,		const ft::vectorConstReverseIterator<T> &lhs)			{ return (lhs.base() == rhs.base()); }
	template <typename U, typename V>
	bool operator==(const ft::vectorConstReverseIterator<U> &rhs,		const ft::vectorConstReverseIterator<V> &lhs)			{ return (lhs.base() == rhs.base()); }


	template <typename T>
	bool operator!=(const ft::vectorConstReverseIterator<T> &rhs,		const ft::vectorConstReverseIterator<T> &lhs)			{ return (lhs.base() != rhs.base()); }
	template <typename U, typename V>
	bool operator!=(const ft::vectorConstReverseIterator<U> &rhs,		const ft::vectorConstReverseIterator<V> &lhs)			{ return (lhs.base() != rhs.base()); }
	
	template <typename T>
	bool operator>=(const ft::vectorConstReverseIterator<T> &rhs,		const ft::vectorConstReverseIterator<T> &lhs)			{ return (lhs.base() >= rhs.base()); }
	template <typename U, typename V>
	bool operator>=(const ft::vectorConstReverseIterator<U> &rhs,		const ft::vectorConstReverseIterator<V> &lhs)			{ return (lhs.base() >= rhs.base()); }

	template <typename T>
	bool operator<=(const ft::vectorConstReverseIterator<T> &rhs, 		const ft::vectorConstReverseIterator<T> &lhs)		{ return (lhs.base() <= rhs.base()); }
	template <typename U, typename V>
	bool operator<=(const ft::vectorConstReverseIterator<U> &rhs, 		const ft::vectorConstReverseIterator<V> &lhs)		{ return (lhs.base() <= rhs.base()); }

	template <typename T>
	bool operator>(const ft::vectorConstReverseIterator<T> &rhs,		const ft::vectorConstReverseIterator<T> &lhs)			{ return (lhs.base() > rhs.base()); }
	template <typename U, typename V>
	bool operator>(const ft::vectorConstReverseIterator<U> &rhs,		const ft::vectorConstReverseIterator<V> &lhs)			{ return (lhs.base() > rhs.base()); }

	template <typename T>
	bool operator<(const ft::vectorConstReverseIterator<T> &rhs, 		const ft::vectorConstReverseIterator<T> &lhs)			{ return (lhs.base() < rhs.base()); }
	template <typename U, typename V>
	bool operator<(const ft::vectorConstReverseIterator<U> &rhs, 		const ft::vectorConstReverseIterator<V> &lhs)			{ return (lhs.base() < rhs.base()); }

	template <typename T>
	ft::vectorConstReverseIterator<T> operator+(typename ft::vectorConstReverseIterator<T>::difference_type rhs, const ft::vectorConstReverseIterator<T> &lhs)						{ return (lhs.base() - rhs); }
	template <typename U, typename V>
	ft::vectorConstReverseIterator<U> operator+(typename ft::vectorConstReverseIterator<U>::difference_type rhs, const ft::vectorConstReverseIterator<V> &lhs)						{ return (lhs.base() - rhs); }
	
	template <typename T>
	ft::vectorConstReverseIterator<T> operator+(const ft::vectorConstReverseIterator<T> &rhs, typename ft::vectorConstReverseIterator<T>::difference_type lhs)						{ return (rhs.base() - lhs); }
	template <typename U, typename V>
	ft::vectorConstReverseIterator<U> operator+(const ft::vectorConstReverseIterator<U> &rhs, typename ft::vectorConstReverseIterator<V>::difference_type lhs)						{ return (rhs.base() - lhs); }

	template <typename T>
	ft::vectorConstReverseIterator<T> operator-(const ft::vectorConstReverseIterator<T> &rhs, typename ft::vectorConstReverseIterator<T>::difference_type lhs)						{ return (rhs.base() + lhs); }
	template <typename U, typename V>
	ft::vectorConstReverseIterator<U> operator-(const ft::vectorConstReverseIterator<U> &rhs, typename ft::vectorConstReverseIterator<V>::difference_type lhs)						{ return (rhs.base() + lhs); }

	template <typename T>
	typename ft::vectorConstReverseIterator<T>::difference_type operator-(const ft::vectorConstReverseIterator<T> &rhs, const ft::vectorConstReverseIterator<T> &lhs)					{ return (lhs.base() - rhs.base()); }
	template <typename U, typename V>
	typename ft::vectorConstReverseIterator<U>::difference_type operator-(const ft::vectorConstReverseIterator<V> &rhs, const ft::vectorConstReverseIterator<U> &lhs)					{ return (lhs.base() - rhs.base()); }
}


#endif