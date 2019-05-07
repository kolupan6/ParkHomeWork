#include <string>
#include <cstring>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <array>
#define SIZE 16
#define N 4

using namespace std;
const array<int8_t, SIZE> goal = { 1, 2,  3,  4,
                                   5,  6,  7,  8,
                                   9, 10, 11, 12,
                                   13, 14, 15, 0 };

class State {
public:
	State(const array<int8_t, SIZE> &field);

	bool isGoal() const;
	bool isLeft() const;
	bool isRight() const;
	bool isUp() const;
	bool isDown() const;

	State L() const;
	State R() const;
	State U() const;
	State D() const;

	int heuristic() const;
	bool operator==(const State &state) const;

	friend struct stateInstance;

private:
	int X(int pos) const;
	int Y(int pos) const;

	array<int8_t, SIZE> field;
	int8_t nulPos;
};

State::State(const array<int8_t, SIZE> &field) : field(field) {
	nulPos = -1;
	for (int8_t i = 0; i < SIZE; i++)
		if (field[i] == 0) nulPos = i;
}

bool State::isGoal() const { return field == goal; }

bool State::isLeft() const { return nulPos % N != N - 1; }

bool State::isRight() const { return nulPos % N != 0; }

bool State::isUp() const { return nulPos < SIZE - N; }

bool State::isDown() const { return nulPos > N - 1; }

State State::L() const {
	State leftState(*this);
	swap(leftState.field[nulPos], leftState.field[nulPos + 1]);
	leftState.nulPos++;
	return leftState;
}

State State::R() const {
	State rightstate(*this);
	swap(rightstate.field[nulPos], rightstate.field[nulPos - 1]);
	rightstate.nulPos--;
	return rightstate;
}

State State::U() const {
	State upstate(*this);
	swap(upstate.field[nulPos], upstate.field[nulPos + N]);
	upstate.nulPos += N;
	return upstate;
}

State State::D() const {
	State downstate(*this);
	swap(downstate.field[nulPos], downstate.field[nulPos - N]);
	downstate.nulPos -= N;
	return downstate;
}

bool State::operator==(const State &state) const {
	return field == state.field;
}

struct stateInstance {
	int operator()(const State &state) const {
		int instance = 0;
		memcpy(&instance, &(state.field[0]), sizeof(instance));
		return instance;
	}
};

int State::heuristic() const {
	int h = 0;  //манхэтонсике пути
	for (int8_t i = 1; i < SIZE; ++i) {
		for (int8_t j = 0; j < SIZE; ++j) {
			if (field[j] == i) {
				h += abs(X(i - 1) - X(j)) + abs(Y(i - 1) - Y(j));
			}
		}
	}

	h += abs(X(nulPos) - X(SIZE - 1)) + abs(Y(nulPos) - Y(SIZE - 1));

	return h;
}

int State::X(int pos) const { return pos % N; }

int State::Y(int pos) const { return pos / N; }

bool isSolvable(const array<int8_t, SIZE> &field) {
	int inversion = 0;  // кол-во не на своих местах+ строка с нулем
	int posEmpty = 0;
	for (int i = 0; i < SIZE - 1; ++i) {
		for (int j = i + 1; j < SIZE; ++j) {
			if (!field[i]) {
				posEmpty = i;
				continue;
			}

			if (!field[j]) {
				posEmpty = j;
				continue;
			}

			if (field[i] > field[j]) inversion++;
		}
	}

	inversion += 1 + posEmpty / N;

	return !(inversion % 2);
}

struct compareH {
	bool operator()(const State &a, const State &b) {
		return a.heuristic() > b.heuristic();
	}
};

string GetSolution(const array<int8_t, SIZE> &field) {
	unordered_map<State, int8_t, stateInstance> visited;
	State startstate(field);
	priority_queue<State, vector<State>, compareH> queue;

	queue.push(startstate);
	visited[startstate] = 'S';
	while (true) {
		if (queue.size() > 300) {
			priority_queue<State, vector<State>, compareH> newqueue;
			for (int i = 0; i < 2; ++i) {
				newqueue.push(queue.top());
				queue.pop();
			}
			queue = newqueue;
		}

		State state = queue.top();
		queue.pop();
		if (state.isGoal()) break;

		if (state.isLeft()) {
			State leftState = state.L();
			if (visited.find(leftState) == visited.end()) {
				queue.push(leftState);
				visited[leftState] = 'L';
			}
		}
		if (state.isRight()) {
			State rightState = state.R();
			if (visited.find(rightState) == visited.end()) {
				queue.push(rightState);
				visited[rightState] = 'R';
			}
		}
		if (state.isUp()) {
			State upState = state.U();
			if (visited.find(upState) == visited.end()) {
				queue.push(upState);
				visited[upState] = 'U';
			}
		}
		if (state.isDown()) {
			State downState = state.D();
			if (visited.find(downState) == visited.end()) {
				queue.push(downState);
				visited[downState] = 'D';
			}
		}
	}

	string result;
	State state(goal);
	while (visited[state] != 'S') {
		switch (visited[state]) {
		case 'L':
			state = state.R();
			result += 'L';
			break;
		case 'R':
			state = state.L();
			result += 'R';
			break;
		case 'U':
			state = state.D();
			result += 'U';
			break;
		case 'D':
			state = state.U();
			result += 'D';
			break;
		default:
			break;
		}
	}

	reverse(result.begin(), result.end());
	return result;
}

int main() {
	array<int8_t, SIZE> field;
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for (int i = 0; i < SIZE; ++i) {
		int n;
		cin >> n;
		field[i] = n;
	}

	if (isSolvable(field)) {
		string solution = GetSolution(field);
		cout << solution.size() << endl;
		cout << solution << endl;
	}
	else
		cout << -1;

	return 0;
}
