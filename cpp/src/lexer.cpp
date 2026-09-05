#include "lexer.h"
#include <cctype>
#include <sstream>

std::string tokenTypeName(TokenType t){switch(t){case TokenType::CHAR:return "CHAR";case TokenType::UNION:return "UNION";case TokenType::STAR:return "STAR";case TokenType::PLUS:return "PLUS";case TokenType::QUESTION:return "QUESTION";case TokenType::LPAREN:return "LPAREN";case TokenType::RPAREN:return "RPAREN";case TokenType::CONCAT:return "CONCAT";default:return "END";}}
std::vector<Token> Lexer::tokenize() const {
 std::vector<Token> out; if(input.empty()) throw LexerError("Regular expression cannot be empty.");
 for(size_t i=0;i<input.size();++i){ unsigned char c=input[i]; if(std::isspace(c)) throw LexerError("Whitespace is not supported at position "+std::to_string(i)+"."); Token t{TokenType::CHAR,(char)c,(int)i};
  switch(c){case '|':t={TokenType::UNION,0,(int)i};break;case '*':t={TokenType::STAR,0,(int)i};break;case '+':t={TokenType::PLUS,0,(int)i};break;case '?':t={TokenType::QUESTION,0,(int)i};break;case '(':t={TokenType::LPAREN,0,(int)i};break;case ')':t={TokenType::RPAREN,0,(int)i};break;case '\\': if(i+1>=input.size()) throw LexerError("Dangling escape at position "+std::to_string(i)+"."); t={TokenType::CHAR,input[++i],(int)i};break; default: break;} out.push_back(t);
 } out.push_back({TokenType::END,0,(int)input.size()}); return out;
}
static bool leftCanEnd(TokenType t){return t==TokenType::CHAR||t==TokenType::RPAREN||t==TokenType::STAR||t==TokenType::PLUS||t==TokenType::QUESTION;}
static bool rightCanStart(TokenType t){return t==TokenType::CHAR||t==TokenType::LPAREN;}
std::vector<Token> insertConcat(const std::vector<Token>& in){std::vector<Token> out; for(size_t i=0;i+1<in.size();++i){out.push_back(in[i]); if(leftCanEnd(in[i].type)&&rightCanStart(in[i+1].type)) out.push_back({TokenType::CONCAT,0,in[i+1].pos});} if(!in.empty()) out.push_back(in.back()); return out;}
