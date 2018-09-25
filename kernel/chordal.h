#include <limits>
#include <set>

extern int ARRAY_SIZE;
extern int max_inp, min_inp;
extern std::set<std::vector<int> > pool;
extern std::vector<std::vector<int> > ans_subs_union;

bool is_simplicial(std::set<std::vector<int> >::iterator itr, int tab);
std::vector<int> find_lseq(const std::vector<int>& input, int max);
std::vector<int> find_hvector(const std::vector<int>& input, int max);
std::vector<int> find_BettiNums(int max, const std::vector<int>& h);
