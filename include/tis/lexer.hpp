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
 * @file  lexer.hpp
 * @brief Lexer convert the input source code into tokens.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   31.08.2024
 */

#ifndef _TIS_LEXER_HPP_
#define _TIS_LEXER_HPP_

#include <string>

#include <tis/token.hpp>

namespace tis {

class Lexer
{
    std::string m_text; ///< Source code.
    std::size_t m_size; ///< Length of source code.
    std::size_t m_pos;  ///< Current position.

private:
    /**
     * @brief Get integer from current position.
     * 
     * @return integer token.
     */
    Token get_integer(void);

    /**
     * @brief Get operator from current position.
     * 
     * @return operator token.
     */
    Token get_operator(void);
    
    /**
     * @brief Get punctuation from current position.
     * 
     * @return punctuation token.
     */
    Token get_punctuation(void);
    
public:
    /** @brief Lexer default constructor.*/
    Lexer(void) = default;

    /**
     * @brief Construct a new Lexer object.
     * 
     * @param [in] text - given source code.
     */
    Lexer(const std::string& text);
    
    /**
     * @brief Set lexer.
     * 
     * @param [in] text - given source code.
     */
    void set(const std::string& text);

    /**
     * @brief Get the next Token.
     * 
     * @return next token. 
     */
    Token get_next_token(void);
};

} // namespace tis

#endif // _TIS_LEXER_HPP_