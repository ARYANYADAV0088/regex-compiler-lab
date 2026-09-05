#include "serializer.h"
#include <sstream>
std::string jsonEscape(const std::string&s){std::string r;for(char c:s){if(c=='"')r+="\\\"";else if(c=='\\')r+="\\\\";else if(c=='\n')r+="\\n";else r+=c;}return r;}
static std::string q(char c){if(c==0)return "epsilon";std::string s(1,c);return s;}
std::string tokensToJson(const std::vector<Token>&v){std::ostringstream o;o<<"[";bool f=true;for(auto&t:v){if(!f)o<<",";f=false;o<<"{\"type\":\""<<tokenTypeName(t.type)<<"\",\"value\":\""<<jsonEscape(q(t.value))<<"\",\"position\":"<<t.pos<<"}";}return o<<"]",o.str();}
static void ast(const std::shared_ptr<ASTNode>&n,std::ostringstream&o,int&id){if(!n){o<<"null";return;}int me=id++;o<<"{\"id\":"<<me<<",\"type\":\""<<astTypeName(n->type)<<"\"";if(n->type==ASTType::SYMBOL)o<<",\"value\":\""<<jsonEscape(q(n->value))<<"\"";if(n->left){o<<",\"left\":";ast(n->left,o,id);}if(n->right){o<<",\"right\":";ast(n->right,o,id);}o<<"}";}
std::string astToJson(const std::shared_ptr<ASTNode>&r){std::ostringstream o;int id=0;ast(r,o,id);return o.str();}
std::string nfaToJson(const NFA&n){std::ostringstream o;o<<"{\"start\":"<<n.start<<",\"accept\":"<<n.accept<<",\"states\":"<<n.states<<",\"alphabet\":[";bool f=true;for(char a:n.alphabet){if(!f)o<<",";f=false;o<<"\""<<jsonEscape(q(a))<<"\"";}o<<"],\"transitions\":[";f=true;for(auto&t:n.transitions){if(!f)o<<",";f=false;o<<"{\"from\":"<<t.from<<",\"to\":"<<t.to<<",\"symbol\":\""<<jsonEscape(q(t.symbol))<<"\"}";}return o<<"]}",o.str();}
static std::string setJson(const std::set<int>&s){std::ostringstream o;o<<"[";bool f=true;for(int x:s){if(!f)o<<",";f=false;o<<x;}return o<<"]",o.str();}
std::string dfaToJson(const DFA&d){std::ostringstream o;o<<"{\"start\":"<<d.start<<",\"states\":"<<d.states<<",\"accept\":"<<setJson(d.accept)<<",\"alphabet\":[";bool f=true;for(char a:d.alphabet){if(!f)o<<",";f=false;o<<"\""<<jsonEscape(q(a))<<"\"";}o<<"],\"subsets\":[";f=true;for(auto&s:d.subsets){if(!f)o<<",";f=false;o<<setJson(s);}o<<"],\"transitions\":[";f=true;for(auto&t:d.transitions){if(!f)o<<",";f=false;o<<"{\"from\":"<<t.from<<",\"to\":"<<t.to<<",\"symbol\":\""<<jsonEscape(q(t.symbol))<<"\"}";}return o<<"]}",o.str();}

std::string minimizationTraceToJson(const std::vector<std::vector<std::set<int>>>& trace) {
    std::ostringstream o;
    o << "[";
    for (size_t round = 0; round < trace.size(); ++round) {
        if (round) o << ",";
        o << "{";
        o << "\"round\":" << round << ",\"partitions\":[";
        for (size_t i = 0; i < trace[round].size(); ++i) {
            if (i) o << ",";
            o << "[";
            size_t j = 0;
            for (int state : trace[round][i]) {
                if (j++) o << ",";
                o << state;
            }
            o << "]";
        }
        o << "]}";
    }
    o << "]";
    return o.str();
}
