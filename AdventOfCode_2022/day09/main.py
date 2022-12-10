import numpy as np


def distance(a, b):
    # Calculate the euclidian distance between two points
    return np.sqrt((a[0] - b[0])**2 + (a[1] - b[1])**2)


def move_to_become_neighbor(tail, head):
    if abs(tail[0] - head[0]) == 2 and abs(tail[1] - head[1]) == 2:
        tail[0] = tail[0] + int((head[0] - tail[0]) / 2)
        tail[1] = tail[1] + int((head[1] - tail[1]) / 2)
    elif abs(tail[0] - head[0]) == 2:
        tail[0] = tail[0] + int((head[0] - tail[0]) / 2)
        tail[1] = head[1]
    elif abs(tail[1] - head[1]) == 2:
        tail[0] = head[0]
        tail[1] = tail[1] + int((head[1] - tail[1]) / 2)


def print_grid(head, tail):
    # Create grid
    grid = np.zeros((6, 6), dtype=int)
    # Set head and tail
    grid[5 - head[1], head[0]] = 1
    grid[5 - tail[1], tail[0]] = 2
    # Print grid
    print(grid, '\n')


if __name__ == '__main__':
    # print(np.sqrt(2))
    # file = open('day09.in', 'r')
    file = open('day9_example.in', 'r')
    moves = file.readlines()
    file.close()
    head = (0, 0)
    tail = (0, 0)
    positions_visited = set()
    positions_visited.add(tail)
    for move in moves:
        # print(move[:-1])
        move_direction = move[0]
        move_distance = int(move[2])
        for i in range(move_distance):
            old_head = head
            if move_direction == 'U':
                head = (head[0], head[1] + 1)
            elif move_direction == 'D':
                head = (head[0], head[1] - 1)
            elif move_direction == 'L':
                head = (head[0] - 1, head[1])
            elif move_direction == 'R':
                head = (head[0] + 1, head[1])
            else:
                print('Invalid move')
                exit(1)


            # print(f"dists: {distance(head, tail)}")
            if distance(head, tail) > np.sqrt(2):
                print(f"Distance between head9{old_head} -> {head}) and tail{tail} is too big: {distance(head, tail)}")
                tail = old_head
            if distance(head, tail) > np.sqrt(2):
                print('Error')

            # print(f"Distance: {distance(head, tail)}\n")
            positions_visited.add(tail)
            # print(f"Positions visited: {positions_visited}\n")
            print_grid(head, tail)

    print(f"Positions visited({len(positions_visited)}): {positions_visited}")

    # m = max([x[0] for x in positions_visited]) - min([x[0] for x in positions_visited]) + 1
    # n = max([x[1] for x in positions_visited]) - min([x[1] for x in positions_visited]) + 1
    # print(f"min x: {min([x[0] for x in positions_visited])}")
    # print(f"max x: {max([x[0] for x in positions_visited])}")
    # print(f"min y: {min([x[1] for x in positions_visited])}")
    # print(f"max y: {max([x[1] for x in positions_visited])}")
    # print(f"n: {n}, m: {m}")
    # grid = np.zeros((n, m))
    # for position in positions_visited:
    #     grid[n - position[1] - min([x[1] for x in positions_visited]) - 1, position[0] - min([x[0] for x in positions_visited])] = 1
    #
    # print(grid)

