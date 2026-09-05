#include "matcher.h"
MatchResult match(const DFA& d,const std::string& input){
    MatchResult r;
    r.path.push_back(d.start);
    int s=d.start;
    for(char c:input){
        int nxt=-1;
        for(const auto&t:d.transitions)
            if(t.from==s&&t.symbol==c){nxt=t.to;break;}
        MatchStep step{c,s,nxt,nxt>=0};
        r.steps.push_back(step);
        if(nxt<0){
            r.error="No transition for symbol '"+std::string(1,c)+"' from state q"+std::to_string(s)+".";
            return r;
        }
        s=nxt;
        r.path.push_back(s);
    }
    r.accepted=d.accept.count(s)>0;
    if(!r.accepted) r.error="Input ended in non-accepting state q"+std::to_string(s)+".";
    return r;
}
