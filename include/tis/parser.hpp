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

#include <tis/lexer.hpp>
#include <tis/ast.hpp>

namespace tis {

class Parser
{
    Lexer      m_lexer;
    ASTNodePtr m_root;  ///< AST root node.

    private:
        /**
         * @brief Parse next node.
         * 
         * @return pointer to the right node.
         */
        ASTNodePtr get_next_node(void);

    public:
        /**
         * @brief Construct a new Parser object.
         * 
         * @param [in] lexer - given lexer object.
         */
        Parser(const Lexer& lexer);

        /** @brief Parse tokens into AST. */
        void parse(void);
};

} // namespace tis

#endif // _TIS_PARSER_HPP_