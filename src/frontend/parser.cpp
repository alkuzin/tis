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

Parser::Parser(const Lexer& lexer) : m_lexer(lexer)
{
    m_current_token = m_lexer.get_next_token();
}

void Parser::set(const Lexer& lexer)
{
    m_lexer         = lexer;
    m_current_token = m_lexer.get_next_token();
}

void Parser::eat(TokenType type)
{
    if (m_current_token.get_type() == type)
        m_current_token = m_lexer.get_next_token();
    else
        // TODO: implement custom exceptions
        throw std::runtime_error("Invalid syntax");
}

ASTNodePtr Parser::factor(void)
{
    auto token      = m_current_token;
    auto token_type = token.get_type();

    if (token_type == TokenType::INTEGER) {
        eat(TokenType::INTEGER);
        return std::make_shared<ASTOperand>(token);
    }
    else if (token_type == TokenType::LPAREN) {
        eat(TokenType::LPAREN);
        auto node = expression();
        eat(TokenType::RPAREN);
        return node;
    }
    
    return nullptr;
}

ASTNodePtr Parser::term(void)
{
    TokenType   type;
    Token       token;

    auto node = factor();

    while ((m_current_token.get_type() == TokenType::MUL) || (m_current_token.get_type() == TokenType::DIV)) {
        token = m_current_token;
        type  = token.get_type();

        if (type == TokenType::MUL)
            eat(TokenType::MUL);
        else if (type == TokenType::DIV)
            eat(TokenType::DIV);
        
        node = std::make_shared<ASTOperator>(ASTOperator(node, token, factor()));
    }
    
    return node;
}

ASTNodePtr Parser::expression(void)
{
    TokenType   type;
    Token       token;

    auto node = term();

    while ((m_current_token.get_type() == TokenType::PLUS) || (m_current_token.get_type() == TokenType::MINUS)) {
        token = m_current_token;
        type  = token.get_type();

        if (type == TokenType::PLUS)
            eat(TokenType::PLUS);
        else if (type == TokenType::MINUS)
            eat(TokenType::MINUS);
        
        node = std::make_shared<ASTOperator>(ASTOperator(node, token, term()));
    }
    
    return node;
}

ASTNodePtr Parser::parse(void)
{
    return expression();
}

ASTNodePtr Parser::get_ast(void) const
{
    return m_root;
}

} // namespace tis