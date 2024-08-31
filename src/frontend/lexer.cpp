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

#include <string>
#include <cctype>

#include <tis/lexer.hpp>
#include <tis/token.hpp>


static const std::string operators   = "+-"; ///< List of available operators.
static const std::string punctuation = ";";  ///< List of available punctuation symbols.

/**
 * @brief Checks if given character is operator.
 * 
 * @param [in] ch - given character to check.
 * @return true - if given character is operator.
 * @return false - otherwise.
 */
static inline bool is_operator(const char ch)
{
    return (operators.find(ch) != std::string::npos);
}

/**
 * @brief Checks if given character is punctuation symbol.
 * 
 * @param [in] ch - given character to check.
 * @return true - if given character is punctuation symbol.
 * @return false - otherwise.
 */
static inline bool is_punctuation(const char ch)
{
    return (punctuation.find(ch) != std::string::npos);
}


namespace tis {

Lexer::Lexer(const std::string& text) : m_text(text), m_size(text.size()), m_pos(0) {} 

Token Lexer::get_integer(void)
{
    std::string result;
    
    while ((m_pos < m_size) && std::isdigit(m_text[m_pos]))
        result += m_text[m_pos++];

    return Token{TokenType::INTEGER, result};
}

Token Lexer::get_operator(void)
{
    char symbol;

    if (m_pos < m_size) {
        symbol = m_text[m_pos];

        // TODO: use unordered_map for containing operators tokens:
        // [key: "+", Value: TokenType::OPERATOR::PLUS]
        switch (symbol) {
            case '+':
                m_pos++;
                return Token{TokenType::OPERATOR, "+"};

            case '-':
                m_pos++;
                return Token{TokenType::OPERATOR, "-"};
        }
    }
    
    m_pos++;
    return Token{TokenType::UNKNOWN, "[???]"};
}

Token Lexer::get_punctuation(void)
{
    char symbol;

    if (m_pos < m_size) {
        symbol = m_text[m_pos];

        // TODO: use unordered_map for containing operators tokens:
        // [key: "+", Value: TokenType::PUNCTUATION::SEMICOLON]
        switch (symbol) {
            case ';':
                m_pos++;
                return Token{TokenType::PUNCTUATION, ";"};
        }
    }
    
    m_pos++;
    return Token{TokenType::UNKNOWN, "[???]"};
}

Token Lexer::get_next_token(void)
{
    char symbol;

    while (m_pos < m_size) {
        symbol = m_text[m_pos];

        // skip space characters
        if (std::isspace(symbol)) {
            m_pos++;
            continue;
        }
        
        // handle integers
        if (std::isdigit(symbol))
            return get_integer();

        // handle operators
        if (is_operator(symbol))
            return get_operator();

        // handle punctuation
        if (is_punctuation(symbol))
            return get_punctuation();
        
        m_pos++;
    }

    return Token(TokenType::END, "[end]");
}

} // namespace tis