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

#include <memory>

#include <tis/parser.hpp>
#include <tis/debug.hpp>


namespace tis {

Parser::Parser(const Lexer& lexer) : m_lexer(lexer) {}

void Parser::set(const Lexer& lexer)
{
    m_lexer = lexer;
}

ASTNodePtr Parser::get_next_node(void)
{
    auto right = m_stack.top();
    m_stack.pop();

    auto op = m_stack.top();
    m_stack.pop();

    ASTNodePtr right_node = std::make_shared<ASTOperand>(right);

    if (m_stack.empty())
        return right_node;
    
    if (m_stack.size() == 1) {
        auto left = m_stack.top();
        m_stack.pop();

        ASTNodePtr left_node = std::make_shared<ASTOperand>(left);
        
        return std::make_shared<ASTOperator>(left_node, op, right_node);
    }
    
    ASTNodePtr left_node = get_next_node();

    return std::make_shared<ASTOperator>(left_node, op, right_node);
}

ASTNodePtr Parser::parse(void)
{
    Token token;
    
    // fill stack with tokens
    while (token.get_type() != TokenType::END) {
        token = m_lexer.get_next_token();
        m_stack.push(token);
    } 
    
    // pop END token
    token = m_stack.top();
    m_stack.pop(); 

    // handle single correct token
    if (m_stack.size() == 1) {
        // get last token
        token = m_stack.top();
        m_stack.pop();

        m_root = std::make_shared<ASTOperand>(token);
        return m_root;
    }

    // handle incorrect token
    else if (m_stack.empty() && (token.get_type() != TokenType::INTEGER)) {
        std::cerr << "\nInvalid syntax: \"" << token.get_value() << "\"\n";
        std::exit(EXIT_FAILURE);
    }
    
    m_root = get_next_node();
    return m_root;
}

ASTNodePtr Parser::get_ast(void) const
{
    return m_root;
}

} // namespace tis