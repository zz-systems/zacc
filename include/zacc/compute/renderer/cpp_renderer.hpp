//---------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015-2019 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//---------------------------------------------------------------------------------

#pragma once

namespace zacc { namespace compute {

    // =================================================================================================================

    template<typename>
    struct variable;

    template<typename, size_t>
    struct batch;

    template<typename, size_t, size_t>
    struct mat;

    template<typename>
    struct complex;

    template<typename>
    struct is_matrix;

    template<typename, typename>
    struct expression_type;

    template<std::size_t, typename>
    struct operand_type;

    template<typename>
    struct unpack;

    class __renderer;

    template<typename Expression>
    class renderer;

    // =================================================================================================================

    template<typename T>
    class renderer<type<literal<T>>> : public __renderer
    {
        using __renderer::__renderer;
    public:
        void visit(type<literal<bool>>)
        {
            _program << "bool";
        }

        void visit(type<literal<int8_t>>)
        {
            _program << "int8_t";
        }

        void visit(type<literal<int16_t>>)
        {
            _program << "int16_t";
        }

        void visit(type<literal<int32_t>>)
        {
            _program << "int32_t";
        }

        void visit(type<literal<int64_t>>)
        {
            _program << "int64_t";
        }

        void visit(type<literal<float>>)
        {
            _program << "float";
        }

        void visit(type<literal<double>>)
        {
            _program << "double";
        }
    };

    
    // =================================================================================================================

    template<typename T>
    class renderer<literal<T>> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression const& expression)
        {
            _program << expression.value;
        }
    };

//    template<>
//    class renderer<literal<bool>> : public __renderer
//    {
//        using __renderer::__renderer;
//    public:
//        void visit(literal<bool>)
//        {
//            _program << "bool";
//        }
//    };
//
//    template<>
//    class renderer<literal<int8_t>> : public __renderer
//    {
//        using __renderer::__renderer;
//    public:
//        void visit(literal<int8_t>)
//        {
//            _program << "int8_t";
//        }
//    };
//
//    template<>
//    class renderer<literal<int16_t>> : public __renderer
//    {
//        using __renderer::__renderer;
//    public:
//        void visit(literal<int16_t>)
//        {
//            _program << "int16_t";
//        }
//    };
//
//    template<>
//    class renderer<literal<int32_t>> : public __renderer
//    {
//        using __renderer::__renderer;
//    public:
//        void visit(literal<int32_t>)
//        {
//            _program << "int32_t";
//        }
//    };
//
//    template<>
//    class renderer<literal<int64_t>> : public __renderer
//    {
//        using __renderer::__renderer;
//    public:
//        void visit(literal<int64_t>)
//        {
//            _program << "int64_t";
//        }
//    };
//
//    template<>
//    class renderer<literal<float>> : public __renderer
//    {
//        using __renderer::__renderer;
//    public:
//        void visit(literal<float>)
//        {
//            _program << "float";
//        }
//    };
//
//    template<>
//    class renderer<literal<double>> : public __renderer
//    {
//        using __renderer::__renderer;
//    public:
//        void visit(literal<double>)
//        {
//            _program << "double";
//        }
//    };
    // =================================================================================================================


    template<typename T>
    class renderer<variable<T>> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            return _program << "var_" << std::hex << expression.id();
        }
    };

    template<>
    class renderer<variable<>> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            _program << "var_" << std::hex << expression.id();
        }
    };

    // =================================================================================================================

    template<>
    class renderer<select_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << "? ";
            next<1>(std::forward<Expression>(expression));
            _program << ": " ;
            next<2>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer<call_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&&)
        {
            //"todo()";
        }
    };

    template<>
    class renderer<init_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << " ";
            next<1>(std::forward<Expression>(expression));
            _program << " = ";
            next<2>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer<assign_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << " = ";
            next<1>(std::forward<Expression>(expression));
        }
    };

    // =================================================================================================================
    // ARITHMETIC
    // =================================================================================================================

    template<>
    class renderer<identity_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer<add_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            _program << "(";
            next<0>(std::forward<Expression>(expression));
            _program << " + ";
            next<1>(std::forward<Expression>(expression));
            _program << ")";
        }
    };

    template<>
    class renderer<sub_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << " - ";
            next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer<mul_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << " * ";
            next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer<div_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << " / ";
            next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer<mod_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << " % ";
            next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer<neg_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            _program << " -";
            next<0>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer<promote_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            _program << " +";
            next<0>(std::forward<Expression>(expression));
        }
    };

    // =================================================================================================================
    // COMPARISON
    // =================================================================================================================

    template<>
    class renderer<equal_to_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << " == ";
            next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer<not_equal_to_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << " != ";
            next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer<greater_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << " > ";
            next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer<less_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << " < ";
            next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer<greater_equal_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << " >= ";
            next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer<less_equal_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << " <= ";
            next<1>(std::forward<Expression>(expression));
        }
    };

    // =================================================================================================================
    // BOOLEAN
    // =================================================================================================================

    template<>
    class renderer<bool_and_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << " && ";
            next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer<bool_or_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << " || ";
            next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer<bool_not_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            _program <<"!";
            next<0>(std::forward<Expression>(expression));
        }
    };

    // =================================================================================================================
    // BITWISE
    // =================================================================================================================

    template<>
    class renderer<bit_and_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << " & ";
            next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer<bit_or_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << " | ";
            next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer<bit_xor_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << " ^ ";
            next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer<bit_shl_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << " << ";
            next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer<bit_shr_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            next<0>(std::forward<Expression>(expression));
            _program << " >> ";
            next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class renderer< bit_not_op> : public __renderer
    {
        using __renderer::__renderer;
    public:
        template<typename Expression>
        void visit(Expression&& expression)
        {
            _program << " ~";
            next<0>(std::forward<Expression>(expression));
        }
    };

    // =================================================================================================================
}}