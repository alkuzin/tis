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
 * @file  token.hpp
 * @brief Contains token class description.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   30.08.2024
 */

#ifndef _TIS_TOKEN_HPP_
#define _TIS_TOKEN_HPP_

#include <iostream>
#include <string>

namespace tis {

enum class TokenType : int32_t {
    INTEGER,
    OPERATOR,
    PUNCTUATION,
    END,
    PLUS,
    MINUS,
    UNKNOWN = -1
};

class Token
{
    TokenType   m_type;
    std::string m_value;

    public:
        /** Token default constructor. */
        Token(void);

        /**
         * @brief Construct a new Token object.
         * 
         * @param [in] type - given token type (integer, operator, etc.).
         * @param [in] value - given token value.
         */
        Token(TokenType type, const std::string& value);
        
        /**
         * @brief Get token type.
         * 
         * @return token type.
         */
        TokenType get_type(void) const;

        /**
         * @brief Get token value.
         * 
         * @return token value. 
         */
        std::string get_value(void) const;
};

/**
 * @brief Operator << overloading for printing TokenType.
 * 
 * @param [in] os - given output stream object.
 * @param [in] type - given TokenType object to print.
 * @return output stream object.
 */
std::ostream& operator<<(std::ostream& os, const TokenType type);

/**
 * @brief Operator << overloading for printing Token.
 * 
 * @param [in] os - given output stream object.
 * @param [in] token - given Token object to print.
 * @return output stream object.
 */
std::ostream& operator<<(std::ostream& os, const Token& token);

} // namespace tis

#endif // _TIS_TOKEN_HPP_