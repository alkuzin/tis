
#include <tis/debug.hpp>
#include <memory>

namespace tis {
namespace debug {

static int16_t coef = 1; // tabulation coefficient

void print_ast(const ASTNodePtr& left, const Token& op)
{
    auto operand       = std::dynamic_pointer_cast<ASTOperand>(left);
    auto operand_value = operand->get_value();
    auto op_type       = op.get_type();

    // TODO: replace PUNCTUATION with SEMICOLON
    if (op_type == TokenType::PUNCTUATION || op_type == TokenType::END)
        std::cout << "\t\t(" << operand_value << ")\n\n";
    else {
        if (coef > 1)
            std::cout << "\t";

        std::cout << "\t[" << op.get_value() << "]\n\n";
        
        for (int16_t i = 0; i < coef - 1; i++)
            std::cout << "\t";
        
        std::cout << "(" << operand_value << ") ";
        coef++;
    }
}

void print_ast(const ASTNodePtr& node, int depth, bool is_left)
{
    std::string indent(depth * 4, ' '); // indentation for visual hierarchy

    if (auto op = std::dynamic_pointer_cast<ASTOperator>(node)) {
        std::cout << indent << (is_left ? "├── " : "└── ") << "[" + op->get_value() + "]\n";

        print_ast(op->get_left(), depth + 1, true);
        print_ast(op->get_right(), depth + 1, false);
    }
    else if (auto operand = std::dynamic_pointer_cast<ASTOperand>(node))
        std::cout << indent << (is_left ? "├── " : "└── ") << "(" + operand->get_value() + ")\n";
}

} // namespace debug
} // namespace tis