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
#include <tis/interpreter.hpp>


int main(void)
{
    tis::Interpreter interpreter;
    tis::Parser      parser;
    tis::Lexer       lexer;

    std::string line;

    // TODO: fork this process like in shell
    while (true) {
        std::cout << ">>> ";
        std::getline(std::cin, line);
        
        if (line.empty())
            continue;
        
        lexer.set(line);
        parser.set(lexer);
        interpreter.set(parser);

        interpreter.interpret();    
    }

    return 0;
}