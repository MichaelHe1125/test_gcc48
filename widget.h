#ifndef WIDGET_H
#define WIDGET_H
#include <utility>
#include <string>
#include <ostream>
#include <type_traits>


inline namespace FifthEd {
    class Widget
    {
    public:
        template <typename T> using twin = std::pair<T,T>;
        void recoup(int) noexcept;
        Widget();
    };

    template <typename It>
    auto fcn(It beg, It end) -> decltype(*beg)
    {
        // process the range
        return *beg;
    }
    template <typename It>
    auto fcn2(It beg, It end) -> typename std::remove_reference<decltype(*beg)>::type
    {
        // process the range
        return *beg;
    }

    template <typename T>
    std::ostream& print(std::ostream &os, const T &t)
    {
        return os<<t;
    }
    template <typename T, typename... Args>
    std::ostream& print(std::ostream &os, const T &t, const Args&... rest)
    {
        os<<t<<" ";
        return print(os, rest...);
    }

    void g() noexcept(false);

    void f() noexcept(noexcept(g()));  // f has same exception specifier as g
}

namespace FourthEd {
    class Widget
    {
    public:
        Widget();
    };
}
#endif // WIDGET_H
