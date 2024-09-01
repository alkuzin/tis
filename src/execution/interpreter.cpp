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

/**
 * @brief Use operator for operands.
 * 
 * @param [in] left - given left operand value.
 * @param [in] right - given right operand value.
 * @param [in] op - given operator type.
 * @return result of using operator for operands.
 */
static inline int32_t evaluate(int32_t left, int32_t right, TokenType op)
{
    int32_t result = 0;

    switch (op) {
        case TokenType::PLUS:
            result = left + right;
            break;
        
        case TokenType::MINUS:
            result = left - right;
            break;
        
        default:
            // TODO
            break;
    }

    return result;
}

// TODO: rename ASTOperator to ASTTerm
// TODO: rename ASTOperatorPtr to ASTTermPtr

/**
 * @brief Traverse AST terms.
 * 
 * @param [in] node - given term.
 * @return expression result.
 */
static int32_t visit_operator(const ASTOperatorPtr& node)
{
    // TODO: create inline function to_operand instead of using std::dynamic_pointer_cast<ASTOperand>(...)
    // TODO: create inline function to_term instead of using std::dynamic_pointer_cast<ASTTerm>(...)
    auto right_operand = std::dynamic_pointer_cast<ASTOperand>(node->get_right());
    auto right_value   = visit_operand(right_operand);
    auto type          = node->get_type();

    int32_t result = 0;
    
    if (auto left_operand = std::dynamic_pointer_cast<ASTOperand>(node->get_left())) {
        // std::cout << "\n(" << visit_operand(left_operand); // for debug
        result = evaluate(visit_operand(left_operand), right_value, type);
    }
    else if(auto left_operator = std::dynamic_pointer_cast<ASTOperator>(node->get_left())) {
        result = evaluate(visit_operator(left_operator), right_value, type);
    }
    // std::cout << " " << node->get_value() << " " << right_value << ")"; // for debug
    
    return result;
}

Interpreter::Interpreter(const Parser& parser) : m_parser(parser) {}

void Interpreter::set(const Parser& parser)
{
    m_parser = parser;
}

int32_t Interpreter::visit(const ASTNodePtr& node)
{
    int32_t result = 0;

    if (auto op = std::dynamic_pointer_cast<ASTOperator>(node)) {
        result = visit_operator(op);
        visit(op->get_left());
        visit(op->get_right());
    }
    else if (auto operand = std::dynamic_pointer_cast<ASTOperand>(node))
        result = visit_operand(operand);

    return result;
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