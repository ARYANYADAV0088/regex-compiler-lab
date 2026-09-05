#include "dfa.h"
#include <queue>
#include <map>
static std::set<int> epsClosure(const NFA& n,const std::set<int>& seed){std::set<int> c=seed;std::vector<int> st(seed.begin(),seed.end());while(!st.empty()){int s=st.back();st.pop_back();for(auto&t:n.transitions)if(t.from==s&&t.symbol==0&&!c.count(t.to)){c.insert(t.to);st.push_back(t.to);}}return c;}
static std::set<int> moveSet(const NFA& n,const std::set<int>& s,char a){std::set<int> r;for(int q:s)for(auto&t:n.transitions)if(t.from==q&&t.symbol==a)r.insert(t.to);return epsClosure(n,r);}
DFA DFABuilder::build(const NFA& n){DFA d;d.alphabet=n.alphabet;std::set<int> start=epsClosure(n,{n.start});std::map<std::set<int>,int> ids;std::queue<int> q;ids[start]=0;d.subsets.push_back(start);d.states=1;q.push(0);while(!q.empty()){int i=q.front();q.pop();if(d.subsets[i].count(n.accept))d.accept.insert(i);for(char a:d.alphabet){auto s=moveSet(n,d.subsets[i],a);if(s.empty())continue;int j;if(!ids.count(s)){j=d.states++;ids[s]=j;d.subsets.push_back(s);q.push(j);}else j=ids[s];d.transitions.push_back({i,j,a});}}return d;}
