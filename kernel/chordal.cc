#define _CRT_SECURE_NO_DEPRECATE
/*
* First Version:
* Author: Iman Kiarazm
* e-mail: i.kiarazm@iasbs.ac.ir
* 10 Aug 2015
*
* Second Version:
* Author: AmirAshkan Safiallah
* e-mail: amirsafiallah@iasbs.ac.ir
* 20 Apr 2016
* */

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <time.h>
#include <limits>

using namespace std;

#define STR_SIZE 100
#define ARRAY_COUNT 2000

int ARRAY_SIZE; //Contains the total number of array;
int bt;
int tab;
int max_inp, min_inp;
int line_number;

set<vector<int>> pool;

vector<vector<int>> ans_subs_union;
vector<vector<int>> ans_selected_subset;

void print_tab(const char &ch, int &tab) {
	if (ch == ' ') cout << endl;
	stringstream ss("");
	for (int i = 0; i < tab; ++i)
		ss << " ";

	if (ch != ' ')
		ss << " `--> ";

	string output;
	getline(ss, output);

	tab = (int)output.size();

	cout << output;
}

void subset(const vector<int> &inp, int left, int pos, vector<int> &select, vector<vector<int> > &sub) {
	
	if (left == 0) {
		vector<int> tmp;
		for (int i = 0; i < (int)inp.size(); ++i)	if (select[i]) {
			tmp.push_back(inp[i]);
		}
		sub.push_back(tmp);
		return;
	}
	for (int i = pos; i < (int)inp.size(); ++i) {
		select[i] = 1;
		subset(inp, left - 1, i + 1, select, sub);
		select[i] = 0;
	}
}

int init() {
	max_inp = numeric_limits<int>::min();
	min_inp = numeric_limits<int>::max();

	string line;
	int l = 0;
	while (cin >> line) {

		int num, i;
		char x, a, b;
		vector<int> arr;

		ARRAY_SIZE = 0;
		for (i = 0; line.find("*") != string::npos; ++i) {
			int pos = line.find("*");
			string s = line.substr(0, pos);
			line = line.substr(pos + 1);

			++ARRAY_SIZE;
			stringstream ss(s);
			ss >> x >> a >> num >> b;
			arr.push_back(num);
		}

		++ARRAY_SIZE;
		stringstream ss(line);
		ss >> x >> a >> num >> b;
		arr.push_back(num);
		sort(arr.begin(), arr.end());

		min_inp = min(min_inp, arr.front());
		max_inp = max(max_inp, arr.back());

		++l;
		//if (cnt != ARRAY_SIZE) {
		//	cout << "An error occured at line " << l << endl;
		//	cout << "ARRAY_SIZE = " << ARRAY_SIZE << endl;
		//	cout << "File array size = " << cnt << endl;
		//	exit(0);
		//}

		pool.insert(move(arr));

	}
	return l;
}

bool is_simplicial(set<vector<int> >::iterator itr, int tab) {

	int prv = tab;

	vector<vector<int> > subs;
	vector<int> select((int)itr->size(), 0);

	subset(*itr, ARRAY_SIZE - 1, 0, select, subs);

	for (int k = 0; k < (int)subs.size(); ++k) {

		vector<int> rem;
		vector<vector<int> > erase;

		for (set<vector<int> >::iterator i = pool.begin(); i != pool.end(); ++i) {

			int j = 0;
			int r = (*i)[ARRAY_SIZE - 1];

			int count = 0;
			for (int pos = 0; pos < ARRAY_SIZE && j < ARRAY_SIZE - 1; ++pos) {
				if ((*i)[pos] != subs[k][j]) {
					r = (*i)[pos];
					if ((*i)[pos] > subs[k][j])	--pos, ++j;
					continue;
				}
				++count, ++j;
			}
			if (count == ARRAY_SIZE - 1) {
				rem.push_back(r);
				erase.push_back(*i);
			}
		}

		set<int> tmp(subs[k].begin(), subs[k].end());
		for (int i = 0; i < (int)rem.size(); ++i)
			tmp.insert(rem[i]);
		vector<int> sets_union(tmp.begin(), tmp.end());

		vector<vector<int> > subsets;
		vector<int> select((int)sets_union.size(), 0);

		subset(sets_union, ARRAY_SIZE, 0, select, subsets);

		bool sw = true;
		for (int i = 0; i < (int)subsets.size(); ++i) {
			if (pool.find(subsets[i]) == pool.end()) {
				sw = false;
				break;
			}
		}

		if (sw) {
			for (int i = 0; i < (int)erase.size(); ++i) {
				pool.erase(pool.find(erase[i]));
			}

			int prv = tab;

			ans_subs_union.push_back(sets_union);
			ans_selected_subset.push_back(subs[k]);

			sw = true;
			for (set<vector<int> >::iterator pos = pool.begin(); pos != pool.end(); ++pos) {
				sw = false;
				int prv_ = tab;
				bool done = is_simplicial(pos, tab);
				tab = prv_;
				if (done) return true;
			}
			if (sw == false) {
				++bt;
				cout << "Here back track occured!!!" << endl;
				cout << "# " << bt << endl;
			}
			if (sw) return true;

			ans_subs_union.pop_back();
			ans_selected_subset.pop_back();

			tab = prv;

			for (int i = 0; i < (int)erase.size(); ++i) {
				pool.insert(erase[i]);
			}

		}
	}

	tab = prv;
	return false;
}

int combination(int N, int M)
{
	if (N < M) return 0;
	if (N == M) return 1;
	double res = 1;
	for (int i = 0; i < M; i++)
	{
		res *= double(N - i);
		res /= double(i + 1);
	}
	return res;
}

vector<int> find_lseq(const vector<int>& input, int max)
{
	std::vector<int> l(max, 0);
	for (const int&i : input)
	{
		++l[i-1];
	}
	return l;
}

int computeM(const vector<int>& input, int i)
{
	int res = 0;
	for (const int& N : input)
	{
		res += combination(N, i);
	}
	return res;
}

vector<int> find_hvector(const vector<int>& input, int max)
{
	int size = max + ARRAY_SIZE - 1;
	int n = max_inp - min_inp + 1;

	vector<int> h(size + 1);
	for (int k = 0; k <= ARRAY_SIZE - 1; k++)
	{
		h[k] = 0;
		int p = (k) % 2 == 0 ? 1 : -1;
		for (int i = 0; i <= k; i++)
		{
			int res = p;
			res *= combination(max + ARRAY_SIZE - 1 - i, k - i);
			res *= combination(n, i);
			h[k] += res;
			p *= -1;
		}
	}
	for (int k = ARRAY_SIZE; k <= size; k++)
	{
		h[k] = 0;
		int p = (k) % 2 == 0 ? 1 : -1;

		for (int i = 0; i <= ARRAY_SIZE - 1; i++)
		{
			int res = p; // (-1)^(k-i)
			res *= combination(max + ARRAY_SIZE - 1 - i, k - i);
			res *= combination(n, i);
			h[k] += res;
			p *= -1;
		}
		p = (k - ARRAY_SIZE) % 2 == 0 ? 1 : -1;
		for (int i = ARRAY_SIZE; i <= k; i++)
		{
			int res = p; // (-1)^(k-i)
			res *= combination(max + ARRAY_SIZE - 1 - i, k - i);
			res *= computeM(input, i - ARRAY_SIZE + 1);
			h[k] += res;
			p *= -1;
		}
	}
	return h;
}

vector<int> find_BettiNums(int max, const vector<int>& h)
{
	int n = max_inp - min_inp + 1;
	vector<int> B(n - ARRAY_SIZE + 1);
	auto sizeHVector = h.size();
	for (int i = 1; i <= n+1 - ARRAY_SIZE; i++)
	{
		B[i-1] = 0;
		int total = ARRAY_SIZE + i - 1;
		int p = (i) % 2 == 0 ? 1 : -1;
		for (int l = 0; l <= total; l++)
		{
			if (total - l >= sizeHVector)
			{
				p *= -1;
				continue;
			}
			int res = p;

			res *= h[total - l];
			res *= combination(n - (max + ARRAY_SIZE - 1), l);
			B[i-1] += res;
			p *= -1;
		}
	}
	return B;
}

vector<int> find_BettiNums(const vector<int>& input, int max)
{
	auto h = find_hvector(input, max);
	return find_BettiNums(max, h);
}

void print_vector(const char* name, const vector<int>&input)
{
	cout << name << ": { ";
	bool first = true;
	for (const int&num : input)
	{
		if (first) first = false;
		else cout << ",";
		cout << num << " ";
	}
	cout << " }" << endl;
}

int main() {

	freopen("Duval.txt", "r", stdin);

	freopen("out Duval.txt", "w", stdout);

	cout << "Read " << (line_number = init()) << " numbers of lines from input file." << endl;

	clock_t start = clock();

	for (set<vector<int> >::iterator itr = pool.begin(); itr != pool.end(); ++itr) {

		if (is_simplicial(itr, 0)) {
			cout << "Input is chordal." << endl;
			vector<int> result;//a vector storing N(i) sequence.
			result.reserve(line_number);

			int max_N = numeric_limits<int>::min();//declare max_N as minimum int value.
			for (int i = 0; i < (int)ans_subs_union.size(); ++i) {
				int N = ans_subs_union[i].size() - ARRAY_SIZE + 1;
				max_N = max(max_N, N);
				result.push_back(N);
			}
			print_vector("lambda seq: ", find_lseq(result, max_N));
			print_vector("The multiset", result);
			vector<int> h = find_hvector(result, max_N);
			print_vector("The H_vector", h);
			print_vector("The Betti", find_BettiNums(max_N, h));

			cout << "\nRunning time : " << (clock() - start) / CLOCKS_PER_SEC << " Seconds" << endl;
			return 0;
		}
	}
	cout << "Running time : " << (clock() - start) / CLOCKS_PER_SEC << " Seconds" << endl;
	cout << "Input is not chordal.\n" << endl;

	return 0;
}
