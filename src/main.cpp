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

#include <iostream>
#include <string>

#include <tis/token.hpp>
#include <tis/lexer.hpp>

int main(void)
{
    // Example
    std::string text = "12 + 10 - 32 * 4;";
    tis::Lexer lexer(text);
    tis::Token token;

    do {
        token = lexer.get_next_token();
        std::cout << token << std::endl;
    } while (token.get_type() != tis::TokenType::END);

    return 0;
}