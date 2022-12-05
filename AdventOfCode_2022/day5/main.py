import re


class move:
    """
    docstring for move
    Class move contains the following attributes:
        - number of items to move
        - stack index to move from
        - stack index to move to
    """
    def __init__(self, info):
        self.number = int(info[0])
        self.from_stack = int(info[1])
        self.to_stack = int(info[2])

    def __str__(self):
        return f"Move {self.number} from stack {self.from_stack} to stack {self.to_stack}"

    def __repr__(self):
        return f"Move {self.number} from stack {self.from_stack} to stack {self.to_stack}"


class stack:
    def __init__(self, index):
        self.stack = []
        self.index = index

    def push(self, val):
        self.stack.append(val)

    def pop(self):
        return self.stack.pop()

    def peek(self):
        return self.stack[-1]

    def isEmpty(self):
        return len(self.stack) == 0

    def getStackIndex(self):
        return self.index

    def __str__(self):
        return f"Stack {self.index}: {self.stack}"

    def __repr__(self):
        return f"Stack {self.index}: {self.stack}"


if __name__ == '__main__':
    # file = open('day5_example.in', 'r')
    file = open('day5.in', 'r')
    lines = file.readlines()
    stacks = []
    moves = []
    n_stacks = 0
    depth = len(lines)
    for line in lines:
        # Find the number of stacks
        if len(line) > 1 and line[1].isnumeric():
            # Bottom of stack
            # print('Number of stacks:', line[-2])
            n_stacks = int(line[-2])
            # Depth is the index of the line
            depth = lines.index(line) - 1
        # Add crates to stacks
        if lines.index(line) <= depth:
            for i in range(1, len(line), 4):
                if line[i].isupper():
                    print('Stack {}: {}'.format((i + 3) // 4, line[i]))
                    flag = False
                    for st in stacks:
                        if st.getStackIndex() == (i + 3) // 4:
                            st.push(line[i])
                            flag = True
                            break
                    if not flag:
                        stacks.append(stack((i + 3) // 4))
                        stacks[-1].push(line[i])

        # Once stacks are filled, read the moves
        if lines.index(line) > depth + 2:
            print('Move: ', line)
            moves.append(move(re.findall(r'\d+', line)))

    # Flip the stacks
    for st in stacks:
        st.stack.reverse()

    #Sort stacks by index
    stacks.sort(key=lambda x: x.getStackIndex())
    print('Stacks: ', stacks)
    print('Moves: ', moves)

    # Start moving
    for move in moves:
        print(move)
        for i in range(move.number):
            stacks[move.to_stack - 1].push(stacks[move.from_stack - 1].pop())
        print(stacks)

    # Print the final result
    # is the string of the top of each stack
    result = ''
    for st in stacks:
        result += st.peek()
    print('Result: ', result)

