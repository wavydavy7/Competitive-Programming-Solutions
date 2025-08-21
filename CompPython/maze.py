from collections import deque

def solution(map):
    rows = len(map)
    cols = len(map[0])
    start_dists = [[float('inf') for _ in range(cols)] for _ in range(rows)]
    end_dists = [[float('inf') for _ in range(cols)] for _ in range(rows)]

    def bfs(i, j, distances):
        queue = deque([(i, j, 1)])
        while queue:
            x, y, dist = queue.popleft()
            if 0 <= x < rows and 0 <= y < cols and map[x][y] == 0 and dist < distances[x][y]:
                distances[x][y] = dist
                for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                    queue.append((x + dx, y + dy, dist + 1))

    bfs(0, 0, start_dists)
    bfs(rows-1, cols-1, end_dists)

    # Without removing any walls
    res = start_dists[rows-1][cols-1]

    # Consider the benefit of removing each wall
    for x in range(rows):
        for y in range(cols):
            if map[x][y] == 1:
                for dx1, dy1 in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                    nx1, ny1 = x + dx1, y + dy1
                    for dx2, dy2 in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                        nx2, ny2 = x + dx2, y + dy2
                        if 0 <= nx1 < rows and 0 <= ny1 < cols and 0 <= nx2 < rows and 0 <= ny2 < cols and map[nx1][ny1] != 1 and map[nx2][ny2] != -1:
                            # If one side of the wall has been visited by start and the other side by the end
                            # We consider the possibility of removing the wall to shorten the path
                                res = min(res, start_dists[nx1][ny1] + end_dists[nx2][ny2] + 1)
                                res = min(res, end_dists[nx1][ny1] + start_dists[nx2][ny2] + 1)

    return res 

print(solution([[0, 1, 1, 0], [0, 0, 0, 1], [1, 1, 0, 0], [1, 1, 1, 0]]))
