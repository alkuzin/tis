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

#include <tis/interpreter.hpp>

namespace tis {

/**
 * @brief Get operand value.
 * 
 * @param [in] node - given operand node.
 * @return operand value.
 */
static inline int32_t visit_operand(const ASTOperandPtr& node)
{
    return std::stoi(node->get_value());
}

int32_t Interpreter::visit_operator(const ASTOperatorPtr& node)
{
    auto left  = visit(node->get_left());
    auto right = visit(node->get_right());

    switch (node->get_type()) {
        case TokenType::PLUS:
            return left + right;
        
        case TokenType::MINUS:
            return left - right;
        
        case TokenType::MUL:
            return left * right;

        case TokenType::DIV:
            return left / right;
        
        default:
            break;
    }

    return 0;
}

Interpreter::Interpreter(const Parser& parser) : m_parser(parser) {}

void Interpreter::set(const Parser& parser)
{
    m_parser = parser;
}

int32_t Interpreter::visit(const ASTNodePtr& node)
{
    if (auto operand = std::dynamic_pointer_cast<ASTOperand>(node))
        return visit_operand(operand);
    else if(auto op = std::dynamic_pointer_cast<ASTOperator>(node))
        return visit_operator(op);

    return 0;
}

void Interpreter::interpret(void)
{
    auto tree = m_parser.parse();

    if (!tree) {
        std::cerr << "Interpreter error: empty AST\n";
        std::exit(EXIT_FAILURE);
    }

    auto result = visit(tree);
    std::cout << result << std::endl; // for debug
}

} // namespace tis