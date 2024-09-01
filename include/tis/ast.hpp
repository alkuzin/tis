/**
 * The Tis programming language.
 * Copyright (C) 2024  Alexander (@alkuzin).
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file  ast.hpp
 * @brief Abstract Syntax Tree (AST) class implementation.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   31.08.2024
 */

#ifndef _TIS_AST_HPP_
#define _TIS_AST_HPP_

#include <string>
#include <memory>

#include <tis/token.hpp>

namespace tis {

class ASTNode
{
    public:
        virtual ~ASTNode(void) = default;
};

using ASTNodePtr = std::shared_ptr<ASTNode>;

class ASTOperator : public ASTNode
{
    ASTNodePtr m_left;
    Token      m_token;
    ASTNodePtr m_right;

    public:
        /** @brief ASTOperator default constructor.*/
        ASTOperator(void);

        /**
         * @brief Construct a new ASTOperator object.
         * 
         * @param [in] left - given left node pointer.
         * @param [in] token - given operator token.
         * @param [in] right - given right node pointer.
         */
        ASTOperator(const ASTNodePtr& left, const Token& token, const ASTNodePtr& right);

        /**
         * @brief Get the left node.
         * 
         * @return left node pointer.
         */
        ASTNodePtr get_left(void) const;
        /**
         * @brief Get the right node.
         * 
         * @return right node pointer.
         */
        ASTNodePtr get_right(void) const;

        /**
         * @brief Get operator token type.
         * 
         * @return operator type.
         */
        TokenType get_type(void) const;

        /**
         * @brief Get operator token value.
         * 
         * @return operator value. 
         */
        std::string get_value(void) const;
};

class ASTOperand : public ASTNode
{
    Token m_token;

    public:
        /** @brief ASTOperand default constructor.*/
        explicit ASTOperand(void);

        /**
         * @brief Construct a new ASTOperand object.
         * 
         * @param [in] token - given operand token.
         */
        explicit ASTOperand(const Token& token);

        /**
         * @brief Get operand token type.
         * 
         * @return operand type.
         */
        TokenType get_type(void) const;

        /**
         * @brief Get operand token value.
         * 
         * @return operand value. 
         */
        std::string get_value(void) const;
};

} // namespace tis

#endif // _TIS_AST_HPP_