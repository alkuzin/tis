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

#include <stdexcept>
#include <string>

#include <tis/token.hpp>

namespace tis {

Token::Token(void) : m_type(TokenType::UNKNOWN), m_value("") {}

Token::Token(TokenType type, const std::string& value) : m_type(type), m_value(value) {}

TokenType Token::get_type(void) const
{
    return m_type;
}

std::string Token::get_value(void) const
{
    return m_value;
}

// Operators overloading

std::ostream& operator<<(std::ostream& os, const TokenType type)
{
    switch (type) {
        case TokenType::INTEGER:
            os << "INTEGER";
            break;
        
        case TokenType::OPERATOR:
            os << "OPERATOR";
            break;
        
        case TokenType::PUNCTUATION:
            os << "PUNCTUATION";
            break;
        
        case TokenType::UNKNOWN:
            os << "UNKNOWN";
            break;
        
        case TokenType::END:
            os << "END";
            break;
        
        default:
            os << "UNKNOWN";
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Token& token)
{
    os << "Token(" << token.get_type() << ", \"" << token.get_value() << "\")";
    return os;
}

}; // namespace tis