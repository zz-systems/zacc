#ifndef ZACC_ZVAL_HPP
#define ZACC_ZVAL_HPP

#include <array>


namespace zacc {

    struct zval_base {
    };

    // TODO: capability
    template<typename _type, typename _shim_type = _type, size_t _dim = 1, size_t alignment = 16, int _capability = 0>
    class zval : zval_base {
    public:
        static const unsigned dim = _dim;
        static const int capability = _capability;

        using type = _type;
        using shim_type = _shim_type;

        using extracted_type = alignas(alignment) std::array<shim_type, dim>;

        template<typename T>
        zval(T value) : _value(value) {}

        _type get_value() const { return _value; }

    protected:
        _type _value;
    };

    template<typename T>
    struct composable {
        template<typename terminator>
        struct type :
                public /*std::conditional_t<
                        std::is_void<_parent>::value,*/
                T,
                /*_parent>,*/
                public terminator {

            template<typename ...Args>
            type(Args... args) : T(std::forward<Args>(args)...) {}
        };
    };

}

#endif //ZACC_ZVAL_HPP