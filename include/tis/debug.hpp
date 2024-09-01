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
 * @file  debug.hpp
 * @brief Auxilar functions for debugging.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   01.09.2024
 */

#ifndef _TIS_DEBUG_HPP_
#define _TIS_DEBUG_HPP_

#include <tis/ast.hpp>

namespace tis {
namespace debug {

/**
 * @brief Print Abstract Syntax Tree. (used inside of parser)
 * 
 * @param [in] left - given operand.
 * @param [in] op - given operator token.
 */
void print_ast(const ASTNodePtr& left, const Token& op);

/**
 * @brief Print Abstract Syntax Tree.
 * 
 * @param [in] node - given AST root node.
 * @param [in] depth - given current depth relative to the @a node.
 * @param [in] is_left - given flag for left node.
 */
void print_ast(const ASTNodePtr& node, int depth = 0, bool is_left = true);

} // namespace debug
} // namespace tis

#endif // _TIS_DEBUG_HPP_