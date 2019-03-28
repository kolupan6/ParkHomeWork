#include<iostream>	
#include<algorithm>
#include<vector>
using namespace std;
typedef int ll;
bool cmp(pair<ll, ll> i, pair<ll, ll> j)
{
	if (i.first != j.first)
		return i.first < j.first;
	else
		return i.second < j.second;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	ll n;
	cin >> n;

	vector<pair<ll, ll>> A(n);

	for (ll i = 0; i < n; i++)
	{
		cin >> A[i].first >> A[i].second;
	}

	ll sum = 0;
	sort(A.begin(), A.end(), cmp);
	ll pr = A[0].first;
	for (ll i = 0; i<n; i++)
	{
		if (A[i].first < pr)
		{
			sum += max((ll)0, A[i].second - pr);
			pr = max(pr, A[i].second);
		}
		else
		{
			sum += A[i].second - A[i].first;
			pr = A[i].second;
		}
	}
	cout << sum;
	return 0;
}
