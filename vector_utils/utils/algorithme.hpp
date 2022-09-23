#include <cstddef>
namespace ft
{
    template <class InputIterator1, class InputIterator2>
    bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
    {
        while(first1 != last1 && *first1 == *first2)
        {
            first2++;
            first1++;
        }
        return (first1 == last1 && first2 == last2);
    }
    

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
    {
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			first1++;
			first2++;
		}
		return (first2 != last2);
    }

    template <class Iterator, class Iterator2>
    ptrdiff_t  distance (Iterator first, Iterator2 last)
    {
        ptrdiff_t dist = 0;
        while (first != last)
        {
            dist++;
            first++;
        }
        return (dist);
    }

}