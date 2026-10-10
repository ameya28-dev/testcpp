#ifndef FORWARD_LIST_IO_H
#define FORWARD_LIST_IO_H

// Optional printing support for Forward::ForwardList.
// Include this only where you need it; forward_list.h itself has no string or stream dependencies.
//
// Element types are printed with their operator<<. Declare that operator in the element type's
// own namespace (always found), or in the global namespace before including this header.

#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

#include "forward_list.hpp"

// __cpp_concepts is predefined by the compiler (no header needed) when C++20 concepts are available.
#if defined(__cpp_concepts) && __cpp_concepts >= 201907L
#define FORWARD_LIST_IO_HAS_CONCEPTS 1
#else
#define FORWARD_LIST_IO_HAS_CONCEPTS 0
#endif

namespace Forward {
    namespace Detail {
        // The constraint and write_element must look operator<< up from the same place,
        // so both live here, before Forward::operator<< is declared. Otherwise the constraint
        // could accept a type that the function body then fails to print.

#if FORWARD_LIST_IO_HAS_CONCEPTS
        // True if a const T can be written with stream << value.
        template <typename T>
        concept Streamable = requires(std::ostream& stream, const T& value) { stream << value; };
#else
        // True if a const T can be written with stream << value.
        template <typename T, typename = void>
        struct IsStreamable : std::false_type {};

        template <typename T>
        struct IsStreamable<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<const T&>())>>
            : std::true_type {};
#endif

        template <typename T>
        void write_element(std::ostream& stream, const T& value) {
            stream << value;
        }
    } // namespace Detail

    // Both functions below exist only when the element type is printable.
    // For other element types they are removed from overload resolution instead of failing
    // inside their bodies, so:
    //   - the error points at your call site, not at this header, and
    //   - "can I print this?" checks (test frameworks, loggers, nested lists) give the right answer.

#if FORWARD_LIST_IO_HAS_CONCEPTS
    template <typename T>
        requires Detail::Streamable<T>
#else
    template <typename T, std::enable_if_t<Detail::IsStreamable<T>::value, int> = 0>
#endif
    std::ostream& operator<<(std::ostream& stream, const ForwardList<T>& list) {
        stream << "forward list: ";
        for (const T& value : list) {
            Detail::write_element(stream, value);
            stream << "->";
        }
        return stream << "nullptr";
    }

#if FORWARD_LIST_IO_HAS_CONCEPTS
    template <typename T>
        requires Detail::Streamable<T>
#else
    template <typename T, std::enable_if_t<Detail::IsStreamable<T>::value, int> = 0>
#endif
    std::string to_string(const ForwardList<T>& list) {
        std::ostringstream stream;
        stream << list;
        return stream.str();
    }
} // namespace Forward

#undef FORWARD_LIST_IO_HAS_CONCEPTS

#endif // FORWARD_LIST_IO_H
