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

#include <tis/ast.hpp>

namespace tis {

ASTOperator::ASTOperator(void) : m_left(nullptr), m_token(Token(TokenType::UNKNOWN, "[???]")), m_right(nullptr) {}

ASTOperator::ASTOperator(const ASTNodePtr& left, const Token& token, const ASTNodePtr& right)
{
    m_left  = left;
    m_token = token;
    m_right = right;
}

ASTNodePtr ASTOperator::get_left(void) const
{
    return m_left;
}

ASTNodePtr ASTOperator::get_right(void) const
{
    return m_right;
}

TokenType ASTOperator::get_type(void) const
{
    return m_token.get_type();
}

std::string ASTOperator::get_value(void) const
{
    return m_token.get_value();
}

ASTOperand::ASTOperand(void) : m_token(Token(TokenType::UNKNOWN, "[???]")) {}

ASTOperand::ASTOperand(const Token& token) : m_token(token) {}

TokenType ASTOperand::get_type(void) const
{
    return m_token.get_type();
}

std::string ASTOperand::get_value(void) const
{
    return m_token.get_value();
}

} // namespace tis