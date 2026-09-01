class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int n = classroom.size();
        int m = classroom[0].size();

        int sx, sy;
        int k = 0;

        vector<vector<int>> id(n, vector<int>(m, -1));

        // Find start and give every trash cell an ID
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (classroom[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }

                if (classroom[i][j] == 'L') {
                    id[i][j] = k++;
                }
            }
        }

        int allMask = (1 << k) - 1;

        // visited[x][y][energy][mask]
        vector<vector<vector<vector<bool>>>> visited(
            n,
            vector<vector<vector<bool>>>(
                m,
                vector<vector<bool>>(
                    energy + 1,
                    vector<bool>(1 << k, false)
                )
            )
        );

        queue<array<int, 4>> q;

        // x, y, energy, mask
        q.push({sx, sy, energy, 0});
        visited[sx][sy][energy][0] = true;

        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        int moves = 0;

        while (!q.empty()) {

            int sz = q.size();

            while (sz--) {

                auto cur = q.front();
                q.pop();

                int x = cur[0];
                int y = cur[1];
                int e = cur[2];
                int mask = cur[3];

                // All trash collected
                if (mask == allMask)
                    return moves;

                // If no energy, cannot move
                if (e == 0)
                    continue;

                for (int d = 0; d < 4; d++) {

                    int nx = x + dx[d];
                    int ny = y + dy[d];

                    // Outside grid
                    if (nx < 0 || nx >= n ||
                        ny < 0 || ny >= m)
                        continue;

                    // Wall
                    if (classroom[nx][ny] == 'X')
                        continue;

                    int ne = e - 1;
                    int nmask = mask;

                    // Trash
                    if (classroom[nx][ny] == 'L') {
                        nmask |= (1 << id[nx][ny]);
                    }

                    // Recharge
                    if (classroom[nx][ny] == 'R') {
                        ne = energy;
                    }

                    if (!visited[nx][ny][ne][nmask]) {

                        visited[nx][ny][ne][nmask] = true;

                        q.push({
                            nx,
                            ny,
                            ne,
                            nmask
                        });
                    }
                }
            }

            moves++;
        }

        return -1;
    }
};