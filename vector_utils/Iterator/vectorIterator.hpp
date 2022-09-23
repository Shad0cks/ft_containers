#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP


namespace ft {

    template <typename T>
    class VectorIterator
    {   

        public :
            
            typedef T value_type;
            typedef T * pointer;
            typedef const T * const_pointer;
            typedef T & reference;
            typedef const T & const_reference;
            typedef typename std::ptrdiff_t difference_type;

            VectorIterator(void) : m_Ptr(nullptr) {};
            VectorIterator(pointer ptr) : m_Ptr(ptr) {};
            VectorIterator(const VectorIterator & cpy) {*this = cpy;};
            virtual ~VectorIterator(void) {};
            
            VectorIterator & operator= (const VectorIterator & cpy) {this->m_Ptr = cpy.operator->(); return *this;};

            //bool
            bool operator==(const VectorIterator & b) const { return (this->m_Ptr == b.m_Ptr); };
            bool operator!=(const VectorIterator & b) const { return (this->m_Ptr != b.m_Ptr); };
            bool operator>=(const VectorIterator & b) const { return (this->m_Ptr >= b.m_Ptr); };
            bool operator<=(const VectorIterator & b) const { return (this->m_Ptr <= b.m_Ptr); };
            bool operator<(const VectorIterator & b) const { return (this->m_Ptr < b.m_Ptr); };
            bool operator>(const VectorIterator & b) const { return (this->m_Ptr > b.m_Ptr); };


            VectorIterator operator++(void) { return (++this->m_Ptr); };
            VectorIterator operator--(void) { return (--this->m_Ptr); };
            VectorIterator operator++(int) { this->m_Ptr++; return  VectorIterator(this->m_Ptr - 1); };
            VectorIterator operator--(int) { this->m_Ptr--; return  VectorIterator(this->m_Ptr + 1); };

            VectorIterator & operator+=(difference_type n) {this->m_Ptr += n; return *this;};
            VectorIterator & operator-=(difference_type n) {this->m_Ptr -= n; return *this;};

            difference_type operator+(VectorIterator b) { return (this->m_Ptr + b.m_Ptr);};
            difference_type operator-(VectorIterator b) { return (this->m_Ptr - b.m_Ptr);};
            VectorIterator operator+(difference_type n) { return (VectorIterator(this->m_Ptr + n));}
            VectorIterator operator-(difference_type n) { return (VectorIterator(this->m_Ptr - n));}


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

}

namespace ft {
	template <typename T  >
	bool operator==(const ft::VectorIterator<T> &rhs,		const ft::VectorIterator<T> &lhs)		{ return (lhs.base() == rhs.base()); }
	template <typename U, typename V  >
	bool operator==(const ft::VectorIterator<U > &rhs, const ft::VectorIterator<V > &lhs)		{ return (lhs.base() == rhs.base()); }

	template <typename T  >
	bool operator!=(const ft::VectorIterator<T > &rhs,		const ft::VectorIterator<T > &lhs)		{ return (lhs.base() != rhs.base()); }
	template <typename U, typename V  >
	bool operator!=(const ft::VectorIterator<U > &rhs, const ft::VectorIterator<V > &lhs)		{ return (lhs.base() != rhs.base()); }

	template <typename T  >
	bool operator>=(const ft::VectorIterator<T > &rhs,		const ft::VectorIterator<T > &lhs)		{ return (lhs.base() <= rhs.base()); }
	template <typename U, typename V  >
	bool operator>=(const ft::VectorIterator<U > &rhs, const ft::VectorIterator<V > &lhs)		{ return (lhs.base() <= rhs.base()); }

	template <typename T  >
	bool operator<=(const ft::VectorIterator<T > &rhs, 		const ft::VectorIterator<T > &lhs)		{ return (lhs.base() >= rhs.base()); }
	template <typename U, typename V  >
	bool operator<=(const ft::VectorIterator<U > &rhs,	const ft::VectorIterator<V > &lhs)		{ return (lhs.base() >= rhs.base()); }

	template <typename T  >
	bool operator>(const ft::VectorIterator<T > &rhs,		const ft::VectorIterator<T > &lhs)		{ return (lhs.base() < rhs.base()); }
	template <typename U, typename V  >
	bool operator>(const ft::VectorIterator<U > &rhs,	const ft::VectorIterator<V > &lhs)		{ return (lhs.base() < rhs.base()); }

	template <typename T  >
	bool operator<(const ft::VectorIterator<T > &rhs, 		const ft::VectorIterator<T > &lhs)		{ return (lhs.base() > rhs.base()); }
	template <typename U, typename V  >
	bool operator<(const ft::VectorIterator<U > &rhs,	const ft::VectorIterator<V > &lhs)		{ return (lhs.base() > rhs.base()); }

	template <typename T  >
	ft::VectorIterator<T > operator+(typename ft::VectorIterator<T >::difference_type rhs, const ft::VectorIterator<T > &lhs)						{ return (lhs.base() + rhs); }
	
	template <typename T  >
	ft::VectorIterator<T > operator+(const ft::VectorIterator<T > &rhs, typename ft::VectorIterator<T >::difference_type lhs)						{ return (rhs.base() + lhs); }

	template <typename T  >
	ft::VectorIterator<T > operator-(const ft::VectorIterator<T > &rhs, typename ft::VectorIterator<T >::difference_type lhs)						{ return (rhs.base() - lhs); }

	template <typename T  >
	typename ft::VectorIterator<T >::difference_type operator-(const ft::VectorIterator<T > &rhs, const ft::VectorIterator<T > &lhs)				{ return (rhs.base() - lhs.base()); }
	template <typename U, typename V  >
	typename ft::VectorIterator<U >::difference_type operator-(const ft::VectorIterator<V > &rhs, const ft::VectorIterator<U > &lhs)	{ return (rhs.base() - lhs.base()); }
}

#endif