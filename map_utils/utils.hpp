# include <iostream>

namespace ft {

    template <class _T1, class _T2>
    struct pair
    {
        typedef _T1 first_type;
        typedef _T2 second_type;

        _T1 first;
        _T2 second;

    	pair() : first(_T1()), second(_T2()) { }

		pair(const _T1& __a, const _T2& __b)
		: first(__a), second(__b) { }

		pair(const pair<_T1, _T2>& __p)
			: first(__p.first), second(__p.second) { }

        virtual ~pair(){}

        pair & operator=(const pair& __p)
        {
			//std::cout << "first : {" << first << "} / p_first : {" << __p.first << "}\n"; 
			first = __p.first;
			second = __p.second;
            return *this;
        }
    };

    template <class _T1, class _T2>
    bool
    operator==(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
    {
        return __x.first == __y.first && __x.second == __y.second;
    }

    template <class _T1, class _T2>
    bool
    operator!=(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
    {
        return !(__x == __y);
    }

    template <class _T1, class _T2>
    bool
    operator< (const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
    {
        return __x.first < __y.first || (!(__y.first < __x.first) && __x.second < __y.second);
    }

    template <class _T1, class _T2>
    bool
    operator> (const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
    {
        return __y < __x;
    }

    template <class _T1, class _T2>
    bool
    operator>=(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
    {
        return !(__x < __y);
    }

    template <class _T1, class _T2>
    bool
    operator<=(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
    {
        return !(__y < __x);
    }

    template <typename _T1, typename _T2>
    ft::pair<_T1, _T2> make_pair(_T1 __t1, _T2 __t2)
    {
        return (ft::pair <_T1, _T2>(__t1, __t2));
    };

    template<class Arg1, class Arg2, class Result>
    struct binary_function
    {
        typedef Arg1    first_argument_type;
        typedef Arg2    second_argument_type;
        typedef Result  result_type;
    };

    template <class T>
    struct less : ft::binary_function<T, T, bool> 
    {
       bool  operator ()(const T &lhs, const T &rhs) const  { return lhs < rhs;}
    };


}