#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;


struct State {
	int n, m;
	vector<string> tubes;

	State() {}

	State(int _n, int _m, vector<string> _tubes) {
		this->n = _n;
		this->m = _m;
		this->tubes = _tubes;
	}

	State(State* _state) {
		this->n = _state->n;
		this->m = _state->m;
		this->tubes = _state->tubes;
	}

	bool pour(string &from, string &to) {
		int fid = 0;
		while (fid < m && from[fid] == 'x') {
			fid++;
		}

		int tid = 0;
		while (tid < m && to[tid] == 'x') {
			tid++;
		}

		if ((fid >= m) || (tid == 0) || (tid < m && to[tid] != from[fid])) {
			return false;
		}

		char col = from[fid];
		from[fid] = 'x';
		tid = tid >= m ? m - 1 : tid - 1;
		to[tid] = col;

		pour(from, to);

		return true;
	}

	bool is_final() {
		for (string tube : tubes) {
			char col = tube[0];
			for (int i = 1; i < m; ++i) {
				if (tube[i] != col && tube[i] != 'x')
					return false;
			}
		}
		return true;
	}

	string get_state() {
		vector<string> stubes(tubes);
        sort(stubes.begin(), stubes.end());
        string s = "";
		for (string tube : stubes) {
			s += tube;
		}
		return s;
	}

	void print() {
		for (string s : tubes) {
			cout << s << " - ";
		}
		cout << endl;
	}
};

int main() {
#ifdef MY_LOCAL_BUILD
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<string> tubes(n);
    for (int i = 0; i < n; ++i) {
    	cin >> tubes[i];
    }

    State init(n, m, tubes);
    map<string, string> par;
    map<string, ii> move;
    queue<State> q;

    q.push(init);

    while (!q.empty()) {
    	State cur = q.front();
    	q.pop();
    	
        string cur_state = cur.get_state();
    	for (int f = 0; f < n; ++f) {
    		for (int t = 0; t < n; ++t) {
    			if (f == t) continue;
    			State next(cur);
                if (!next.pour(next.tubes[f], next.tubes[t]))
                    continue;

                string next_state = next.get_state();
    			if (par.find(next_state) == par.end()) {
    				q.push(next);
    				par[next_state] = cur_state; 
                    move[next_state] = {f + 1, t + 1};

    				if (next.is_final()) {
			    		vector<ii> steps;
			    		string it = next_state;
			    		while (it != "") {
			    			steps.push_back(move[it]);
			    			it = par[it];
			    		}

			    		for (auto it = steps.rbegin() + 1; it != steps.rend(); ++it) {
			    		   cout << it->first << " " << it->second << endl;
			    		}
			    		return 0;
			    	}
    			}
    		}
    	}
    }
}