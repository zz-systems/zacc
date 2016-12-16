//
// Created by Sergej Zuyev on 12/12/2016.
//
/**
 * @brief https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Hierarchy_Generation
 */

#ifndef ZACC_HIERARCHY_GEN_HPP
#define ZACC_HIERARCHY_GEN_HPP

#include <utility>

namespace zacc {
    template<template<class> class ... policies>
    struct compose;

    template<template<class> class head,
            template<class> class ... tail>
    struct compose<head, tail...> : head<compose<tail...>> {
        template<typename... Args>
        compose(Args &&...args) : head<compose<tail...>>(std::forward<Args>(args)...) {}
    };

    template<>
    struct compose<> {
    };
/*

    template<template<class> class terminator, template<class> class ... policies>
    struct compose_incomplete;

    template<template<class> class terminator, template<class> class head, template<class> class ... tail>
    struct compose_incomplete<terminator, head, tail...> : head<compose_incomplete<terminator, tail...>>
    {
        template<typename... Args>
        compose_incomplete(Args &&...args) : head<compose_incomplete<terminator, tail...>>(std::forward<Args>(args)...)
        {}
    };

    template<>
    template<template<class> class terminator>
    struct compose_incomplete <terminator> :
            terminator {};*/

#define FORWARD2(name, base) \
    template<typename ...Args> \
    name(Args... args) : base(std::forward<Args>(args)...) {}

#define FORWARD(name) FORWARD2(name, base_t)

}

#endif //ZACC_HIERARCHY_GEN_HPP
