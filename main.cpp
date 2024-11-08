#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using vvl = vector<vl>;
using Pos = pair<ll, ll>;
using vb = vector<bool>;
using vvb = vector<vb>;
using PD = pair<Pos, ll>;

ll N, M, D;
vvl bd;

vl dr{-1, 1, 0, 0};
vl dc{0, 0, -1, 1};

ll ans = 0;
Pos bfs(const vvl& cbd, ll x) {
  queue<PD> Q{};
  Q.push({{N, x}, 0});

  vvb visit(N, vb(M, false));

  ll checkdist = -1;
  Pos target;
  while (!Q.empty()) {
    auto [f, dist] = Q.front();
    auto [fr, fc] = f;
    Q.pop();

    if (fr != N) {
      if (cbd[fr][fc] == 1) {
        if (checkdist == -1) {
          checkdist = dist;
          target = {fr, fc};
        } else {
          if (dist < checkdist) {
            checkdist = dist;
            target = {fr, fc};
          } else if (dist == checkdist && fc < target.second) {
            target = {fr, fc};
          }
        }

        continue;
      }
    }

    if (dist == D) continue;
    if (dist == checkdist) continue;

    for (auto d = 0; d < 4; ++d) {
      const auto& nr = fr + dr[d];
      const auto& nc = fc + dc[d];

      if (nr < 0 || N <= nr || nc < 0 || M <= nc) continue;
      if (visit[nr][nc]) continue;

      Q.push({{nr, nc}, dist + 1});
      visit[nr][nc] = true;
    }
  }

  if (checkdist > 0) {
    return target;
  }

  return {-1, -1};
}
void solve(ll x, ll y, ll z) {
  auto cbd = bd;
  ll ret = 0;
  while (true) {
    const auto& tx = bfs(cbd, x);
    const auto& ty = bfs(cbd, y);
    const auto& tz = bfs(cbd, z);

    if (tx.first != -1) {
      if (cbd[tx.first][tx.second] == 1) {
        ++ret;
        cbd[tx.first][tx.second] = 0;
      }
    }

    if (ty.first != -1) {
      if (cbd[ty.first][ty.second] == 1) {
        ++ret;
        cbd[ty.first][ty.second] = 0;
      }
    }

    if (tz.first != -1) {
      if (cbd[tz.first][tz.second] == 1) {
        ++ret;
        cbd[tz.first][tz.second] = 0;
      }
    }

    for (auto i = N - 1; 0 < i; --i) {
      for (auto j = 0; j < M; ++j) {
        cbd[i][j] = cbd[i - 1][j];
      }
    }
    for (auto j = 0; j < M; ++j) {
      cbd[0][j] = 0;
    }

    auto bk = true;
    for (const auto& row : cbd) {
      if (!bk) break;
      for (const auto& val : row) {
        if (val == 1) {
          bk = false;
          break;
        }
      }
    }

    if (bk) break;
  }

  ans = max(ans, ret);
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> N >> M >> D;
  bd = vvl(N, vl(M));
  for (auto&& row : bd) {
    for (auto&& x : row) cin >> x;
  }

  for (auto i = 0; i < M; ++i) {
    for (auto j = i + 1; j < M; ++j) {
      for (auto k = j + 1; k < M; ++k) {
        solve(i, j, k);
      }
    }
  }

  cout << ans;

  return 0;
}