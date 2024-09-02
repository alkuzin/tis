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
 * @file  interpretor.hpp
 * @brief Implementation of interpreter class.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   01.09.2024
 */

#ifndef _TIS_INTERPRETER_HPP_
#define _TIS_INTERPRETER_HPP_

#include <tis/parser.hpp>

namespace tis {

class Interpreter
{
    Parser m_parser;

    private:
        /**
         * @brief Traverse throw AST.
         * 
         * @param [in] node - given AST node.
         * @return eveluation result.
         */
        int32_t visit(const ASTNodePtr& node);
        
        /**
         * @brief Traverse AST terms.
         * 
         * @param [in] node - given term.
         * @return expression result.
         */
        int32_t visit_operator(const ASTOperatorPtr& node);

    public:
        /** @brief Interpreter default constructor.*/
        Interpreter(void) = default;
    
        /**
         * @brief Construct a new Interpreter object.
         * 
         * @param [in] parser - given parser object.
         */
        Interpreter(const Parser& parser);

        /**
         * @brief Set interpreter.
         * 
         * @param [in] parser - given parser object.
         */
        void set(const Parser& parser);

        /** @brief Execute AST.*/
        void interpret(void);
};

} // namespace tis

#endif // _TIS_INTERPRETER_HPP_