#include "nfa.h"
#include <stdexcept>
int ThompsonBuilder::newState(){return nfa.states++;}
std::pair<int,int> ThompsonBuilder::buildNode(const std::shared_ptr<ASTNode>& x){
 if(!x) throw std::runtime_error("Invalid AST");
 if(x->type==ASTType::SYMBOL){int s=newState(),e=newState();nfa.transitions.push_back({s,e,x->value});nfa.alphabet.insert(x->value);return{s,e};}
 if(x->type==ASTType::CONCAT){auto a=buildNode(x->left),b=buildNode(x->right);nfa.transitions.push_back({a.second,b.first,0});return{a.first,b.second};}
 if(x->type==ASTType::UNION){auto a=buildNode(x->left),b=buildNode(x->right);int s=newState(),e=newState();nfa.transitions.push_back({s,a.first,0});nfa.transitions.push_back({s,b.first,0});nfa.transitions.push_back({a.second,e,0});nfa.transitions.push_back({b.second,e,0});return{s,e};}
 auto a=buildNode(x->left);int s=newState(),e=newState();
 if(x->type==ASTType::STAR){nfa.transitions.push_back({s,e,0});nfa.transitions.push_back({s,a.first,0});nfa.transitions.push_back({a.second,a.first,0});nfa.transitions.push_back({a.second,e,0});}
 else if(x->type==ASTType::PLUS){nfa.transitions.push_back({s,a.first,0});nfa.transitions.push_back({a.second,a.first,0});nfa.transitions.push_back({a.second,e,0});}
 else {nfa.transitions.push_back({s,e,0});nfa.transitions.push_back({s,a.first,0});nfa.transitions.push_back({a.second,e,0});}
 return{s,e};
}
NFA ThompsonBuilder::build(const std::shared_ptr<ASTNode>& root){nfa=NFA{};auto p=buildNode(root);nfa.start=p.first;nfa.accept=p.second;return nfa;}
