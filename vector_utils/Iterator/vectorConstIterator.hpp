#ifndef VECTOR_CONST_ITERATOR_HPP
#define VECTOR_CONST_ITERATOR_HPP

#include "vectorIterator.hpp"

namespace ft {

    template <typename T>
    class vectorConstIterator
    {        

        public :

            typedef const T value_type;
            typedef T * pointer;
            typedef T & reference;
            typedef const T & const_reference;
            typedef T const * const_pointer;
            typedef typename std::ptrdiff_t difference_type;

            vectorConstIterator(void) : m_Ptr(nullptr) {};
            vectorConstIterator(VectorIterator<T> const & cpy) {this->m_Ptr = cpy.operator->();};
            vectorConstIterator(vectorConstIterator const & cpy) {*this = cpy;};
            vectorConstIterator(pointer ptr) : m_Ptr(ptr) {};
            
            
            virtual ~vectorConstIterator(void) {};

            
            vectorConstIterator & operator= (const vectorConstIterator & cpy) {this->m_Ptr = cpy.m_Ptr; return *this;};

            //bool
            bool operator==(const vectorConstIterator & b) const { return (this->m_Ptr == b.m_Ptr); };
            bool operator!=(const vectorConstIterator & b) const { return (this->m_Ptr != b.m_Ptr); };
            bool operator>=(const vectorConstIterator & b) const { return (this->m_Ptr >= b.m_Ptr); };
            bool operator<=(const vectorConstIterator & b) const { return (this->m_Ptr <= b.m_Ptr); };
            bool operator<(const vectorConstIterator & b) const { return (this->m_Ptr < b.m_Ptr); };
            bool operator>(const vectorConstIterator & b) const { return (this->m_Ptr > b.m_Ptr); };


            vectorConstIterator operator++(void) { return (++this->m_Ptr); };
            vectorConstIterator operator--(void) { return (--this->m_Ptr); };
            vectorConstIterator operator++(int) { this->m_Ptr++; return  vectorConstIterator(this->m_Ptr - 1); };
            vectorConstIterator operator--(int) { this->m_Ptr--; return  vectorConstIterator(this->m_Ptr + 1); };

            vectorConstIterator & operator+=(difference_type n) {this->m_Ptr += n; return *this;};
            vectorConstIterator & operator-=(difference_type n) {this->m_Ptr -= n; return *this;};

            difference_type operator+(vectorConstIterator b) { return (this->m_Ptr + b.m_Ptr);};
            difference_type operator-(vectorConstIterator b) { return (this->m_Ptr - b.m_Ptr);};
            vectorConstIterator operator+(difference_type n) { return (vectorConstIterator(this->m_Ptr + n));}
            vectorConstIterator operator-(difference_type n) { return (vectorConstIterator(this->m_Ptr - n));}


            //momory acces
            const_reference operator*() const { return (*this->m_Ptr); };            
            const_reference operator[](difference_type b) const { return (*(this->m_Ptr + b)); };
            const_pointer operator->() const {return (this->m_Ptr); };
            pointer base() const { return (m_Ptr); }
        private:
            pointer m_Ptr;
    };

}

namespace ft {
	template <typename T  >
	bool operator==(const ft::vectorConstIterator<T> &rhs,		const ft::vectorConstIterator<T> &lhs)		{ return (lhs.base() == rhs.base()); }
	template <typename U>
	bool operator==(const ft::VectorIterator<U > &rhs, const ft::vectorConstIterator<U> &lhs)		{ return (lhs.base() == rhs.base()); }

	template <typename T  >
	bool operator!=(const ft::vectorConstIterator<T > &rhs,		const ft::vectorConstIterator<T > &lhs)		{ return (lhs.base() != rhs.base()); }
	template <typename U>
	bool operator!=(const ft::VectorIterator<U > &rhs, const ft::vectorConstIterator<U > &lhs)		{ return (lhs.base() != rhs.base()); }

	template <typename T  >
	bool operator>=(const ft::vectorConstIterator<T > &rhs,		const ft::vectorConstIterator<T > &lhs)		{ return (lhs.base() <= rhs.base()); }
	template <typename U>
	bool operator>=(const ft::VectorIterator<U > &rhs, const ft::vectorConstIterator<U > &lhs)		{ return (lhs.base() <= rhs.base()); }

	template <typename T  >
	bool operator<=(const ft::vectorConstIterator<T > &rhs, 		const ft::vectorConstIterator<T > &lhs)		{ return (lhs.base() >= rhs.base()); }
	template <typename U  >
	bool operator<=(const ft::VectorIterator<U > &rhs,	const ft::vectorConstIterator<U > &lhs)		{ return (lhs.base() >= rhs.base()); }

	template <typename T  >
	bool operator>(const ft::vectorConstIterator<T > &rhs,		const ft::vectorConstIterator<T > &lhs)		{ return (lhs.base() < rhs.base()); }
	template <typename U >
	bool operator>(const ft::VectorIterator<U > &rhs,	const ft::vectorConstIterator<U > &lhs)		{ return (lhs.base() < rhs.base()); }

	template <typename T  >
	bool operator<(const ft::vectorConstIterator<T > &rhs, 		const ft::vectorConstIterator<T > &lhs)		{ return (lhs.base() > rhs.base()); }
	template <typename U  >
	bool operator<(const ft::VectorIterator<U > &rhs,	const ft::vectorConstIterator<U > &lhs)		{ return (lhs.base() > rhs.base()); }

	template <typename T  >
	ft::vectorConstIterator<T > operator+(typename ft::vectorConstIterator<T >::difference_type rhs, const ft::vectorConstIterator<T > &lhs)						{ return (lhs.base() + rhs); }
	
	template <typename T  >
	ft::vectorConstIterator<T > operator+(const ft::vectorConstIterator<T > &rhs, typename ft::vectorConstIterator<T >::difference_type lhs)						{ return (rhs.base() + lhs); }

	template <typename T  >
	ft::vectorConstIterator<T > operator-(const ft::vectorConstIterator<T > &rhs, typename ft::vectorConstIterator<T >::difference_type lhs)						{ return (rhs.base() - lhs); }

	template <typename T  >
	typename ft::vectorConstIterator<T >::difference_type operator-(const ft::vectorConstIterator<T > &rhs, const ft::vectorConstIterator<T > &lhs)				{ return (rhs.base() - lhs.base()); }
	template <typename U, typename V  >
	typename ft::vectorConstIterator<U >::difference_type operator-(const ft::vectorConstIterator<V > &rhs, const ft::vectorConstIterator<U > &lhs)	{ return (rhs.base() - lhs.base()); }
}

#endif