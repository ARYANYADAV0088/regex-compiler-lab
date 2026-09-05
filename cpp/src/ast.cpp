#include "ast.h"
std::string astTypeName(ASTType t){switch(t){case ASTType::SYMBOL:return "SYMBOL";case ASTType::CONCAT:return "CONCAT";case ASTType::UNION:return "UNION";case ASTType::STAR:return "STAR";case ASTType::PLUS:return "PLUS";default:return "OPTIONAL";}}
