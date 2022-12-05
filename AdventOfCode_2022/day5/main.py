import re


class move:
    """
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
    """
    Class stack contains the following attributes:
        - stack: list of items in the stack
        - index: index of the stack
    Class stack contains the following methods:
        - push: push an item to the stack
        - pop: pop an item from the stack
        - pop_index: pop an item from the stack at a specific index
        - peek: peek at the top of the stack
        - isEmpty: check if the stack is empty
        - getStackIndex: get the index of the stack
    """
    def __init__(self, index):
        self.stack = []
        self.index = index

    def push(self, val):
        self.stack.append(val)

    def pop(self):
        return self.stack.pop()

    def pop_index(self, index):
        return self.stack.pop(index)

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
            # Bottom of stacks
            n_stacks = int(line[-2])
            # Depth is the index of the line
            depth = lines.index(line) - 1
        # Add crates to stacks
        if lines.index(line) <= depth:
            for i in range(1, len(line), 4):
                if line[i].isupper():
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
            moves.append(move(re.findall(r'\d+', line)))

    # Flip the stacks
    for st in stacks:
        st.stack.reverse()

    # Sort stacks by index
    stacks.sort(key=lambda x: x.getStackIndex())

    # Create new stacks for the moves
    stacks_part_1 = []
    stacks_part_2 = []
    for st in stacks:
        stacks_part_1.append(stack(st.getStackIndex()))
        stacks_part_2.append(stack(st.getStackIndex()))
        for crate in st.stack:
            stacks_part_1[-1].push(crate)
            stacks_part_2[-1].push(crate)

    # Start moving the crates
    for move in moves:
        for i in range(move.number, 0, -1):
            stacks_part_1[move.to_stack - 1].push(stacks_part_1[move.from_stack - 1].pop())
            stacks_part_2[move.to_stack - 1].push(stacks_part_2[move.from_stack - 1].pop_index(-i))

    # Print the final result for part 1
    result_part_1 = ''
    result_part_2 = ''
    for i in range(n_stacks):
        result_part_1 += stacks_part_1[i].peek()
        result_part_2 += stacks_part_2[i].peek()

    print('Part 1:', result_part_1)
    print('Part 2:', result_part_2)
