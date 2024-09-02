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


static const std::string operators   = "+-*/"; ///< List of available operators.
static const std::string punctuation = ";";    ///< List of available punctuation symbols.
static const std::string parens      = "()";   ///< List of available parens symbols.

/**
 * @brief Checks if given character is in symbols list.
 * 
 * @param [in] ch - given character to check.
 * @return true - if given character is in list.
 * @return false - otherwise.
 */
static inline bool in_list(const std::string& src, const char ch)
{
    return (src.find(ch) != std::string::npos);
}


namespace tis {

Lexer::Lexer(const std::string& text) : m_text(text), m_size(text.size()), m_pos(0)
{
    m_current_char = m_text[m_pos];
}

void Lexer::set(const std::string& text)
{
    m_size = text.size();
    m_text = text;
    m_pos  = 0;
    m_current_char = m_text[m_pos];
}

void Lexer::advance(void)
{
    m_pos++;

    if (m_pos > (m_size - 1))
        m_current_char = '\0';
    else
        m_current_char = m_text[m_pos];
}

void Lexer::skip_whitespace(void)
{
    while ((m_current_char != '\0') && std::isspace(m_current_char))
        advance();
}

Token Lexer::get_integer(void)
{
    std::string result;
    
    while ((m_current_char != '\0') && std::isdigit(m_current_char)) {
        result += m_current_char;
        advance();
    }

    return Token{TokenType::INTEGER, result};
}

Token Lexer::get_operator(void)
{
    // TODO: use unordered_map for containing operators tokens:
    // [key: "+", Value: TokenType::OPERATOR::PLUS]
    switch (m_current_char) {
        case '+':
            advance();
            return Token{TokenType::PLUS, "+"};

        case '-':
            advance();
            return Token{TokenType::MINUS, "-"};
        
        case '*':
            advance();
            return Token{TokenType::MUL, "*"};
        
        case '/':
            advance();
            return Token{TokenType::DIV, "/"};
    }
    
    advance();
    return Token{TokenType::UNKNOWN, "[?]"};
}

Token Lexer::get_punctuation(void)
{
    switch (m_current_char) {
        case ';':
            advance();
            return Token{TokenType::PUNCTUATION, ";"};
    }
    
    advance();
    return Token{TokenType::UNKNOWN, "[?]"};
}

Token Lexer::get_paren(void)
{
    // TODO: use unordered_map for containing operators tokens:
    // [key: "(", Value: TokenType::LPAREN]
    switch (m_current_char) {
        case '(':
            advance();
            return Token{TokenType::LPAREN, "("};
        
        case ')':
            advance();
            return Token{TokenType::RPAREN, ")"};
    }
    
    advance();
    return Token{TokenType::UNKNOWN, "[?]"};
}

Token Lexer::get_next_token(void)
{
    while (m_current_char != '\0') {
        // skip space characters
        if (std::isspace(m_current_char)) {
            skip_whitespace();
            continue;
        }
        
        // handle integers
        if (std::isdigit(m_current_char))
            return get_integer();

        // handle operators
        if (in_list(operators, m_current_char))
            return get_operator();
        
        // handle parens
        if (in_list(parens, m_current_char))
            return get_paren();

        // handle punctuation
        if (in_list(punctuation, m_current_char))
            return get_punctuation();
    }

    return Token(TokenType::END, "\0");
}

} // namespace tis