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
 * @file  parser.hpp
 * @brief Syntax analyser.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   31.08.2024
 */

#ifndef _TIS_PARSER_HPP_
#define _TIS_PARSER_HPP_

#include <stack>

#include <tis/lexer.hpp>
#include <tis/ast.hpp>

namespace tis {

class Parser
{
    std::stack<Token> m_stack;
    ASTNodePtr        m_root;  ///< AST root node.
    Lexer             m_lexer;

    private:
        /**
         * @brief Parse next node.
         * 
         * @return pointer to the right node.
         */
        ASTNodePtr get_next_node(void);

    public:
        /** @brief Parser default constructor.*/
        Parser(void) = default;
        
        /**
         * @brief Construct a new Parser object.
         * 
         * @param [in] lexer - given lexer object.
         */
        Parser(const Lexer& lexer);
        
        /**
         * @brief Set parser.
         * 
         * @param [in] lexer - given lexer object.
         */
        void set(const Lexer& lexer);

        /**
         * @brief Get AST root node.
         * 
         * @return root node. 
         */
        ASTNodePtr get_ast(void) const;

        /**
         * @brief Parse tokens into AST.
         * 
         * @return root node.
         */
        ASTNodePtr parse(void);
};

} // namespace tis

#endif // _TIS_PARSER_HPP_