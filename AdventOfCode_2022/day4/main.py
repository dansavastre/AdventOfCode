class pair:
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def are_fully_overlapping(self, other):
        if self.left <= other.left and other.right <= self.right:
            return True

    def are_partially_overlapping(self, other):
        if self.left <= other.left <= self.right:
            return True
        if self.left <= other.right <= self.right:
            return True

    def __str__(self):
        return f"({self.left}, {self.right})"


def read_lines(lines):
    pairs = []
    for line in lines:
        intervals = line.split(',')
        # print(intervals[0], intervals[1])
        for interval in intervals:
            left, right = interval.split('-')
            pairs.append(pair(int(left), int(right)))
    return pairs


if __name__ == '__main__':
    file = open('day4.in', 'r')
    lines = file.readlines()
    pairs = read_lines(lines)
    part_1 = 0
    part_2 = 0
    for i in range(0, len(pairs), 2):
        print('Pairs: ', pairs[i], pairs[i + 1])
        if pairs[i].are_fully_overlapping(pairs[i + 1]) or pairs[i + 1].are_fully_overlapping(pairs[i]):
            print('Fully overlapping')
            part_1 += 1
        if pairs[i].are_partially_overlapping(pairs[i + 1]) or pairs[i + 1].are_partially_overlapping(pairs[i]):
            print('Partially overlapping')
            part_2 += 1

    print('Part 1: ', part_1)
    print('Part 2: ', part_2)
