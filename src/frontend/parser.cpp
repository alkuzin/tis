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

#include <tis/parser.hpp>
#include <tis/lexer.hpp>
#include <tis/debug.hpp>

#include <memory>

namespace tis {

Parser::Parser(const Lexer& lexer) : m_lexer(lexer) {}

ASTNodePtr Parser::get_next_node(void)
{
    auto left       = m_lexer.get_next_token();
    auto left_value = left.get_value();
    auto left_type  = left.get_type();

    // TODO: print error with line number and line itself.
    // TODO: implement separate functions for printing errors.
    if (left_type != TokenType::INTEGER) {
        std::cerr << "\nInvalid syntax: \"" << left_value << "\"\n";
        std::exit(EXIT_FAILURE);
    }

    ASTNodePtr left_node = std::make_shared<ASTOperand>(left);

    auto op      = m_lexer.get_next_token();
    auto op_type = op.get_type();

    debug::print_ast(left_node, op);

    // TODO: replace PUNCTUATION with SEMICOLON
    if (op_type == TokenType::PUNCTUATION || op_type == TokenType::END)
        return std::dynamic_pointer_cast<ASTOperand>(left_node);

    ASTNodePtr right_node = get_next_node();

    return std::make_shared<ASTOperator>(left_node, op, right_node);
}

void Parser::parse(void)
{
    m_root = get_next_node();
    debug::print_ast(m_root);
}

} // namespace tis