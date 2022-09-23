
namespace ft
{
    template<bool B, class T = void>
    struct enable_if {};
    
    template<class T>
    struct enable_if<true, T> { typedef T type; };
    
    template<class T, class U>
    struct is_same : std::false_type {};
    
    template<class T>
    struct is_same<T, T> : std::true_type {};
}