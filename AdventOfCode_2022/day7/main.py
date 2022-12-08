import re


class Directory:
    def __init__(self, name, children, parent, size):
        self.name = name
        self.children = children
        self.parent = parent
        self.size = size
        if name != "/":
            parent.addChild(self)

    def __repr__(self):
        return f"dir {self.name} -> {self.children} ({self.size})"

    def __str__(self):
        return self.__repr__()

    def addChild(self, child):
        self.children.append(child)

    def changeDirectory(self, newDirectory):
        if newDirectory == "..":
            return self.parent
        elif newDirectory == "/":
            return root
        else:
            for child in self.children:
                # Check if child is directory type
                if isinstance(child, Directory) and child.name == newDirectory:
                    return child
            return self


class File:
    """
    File class
    Attributes:
        name: Name of file
        size: Size of file
        parent: Parent directory
    """
    def __init__(self, name, size, parent):
        self.name = name
        self.size = size
        self.parent = parent
        parent.addChild(self)

    def __repr__(self):
        return f"file {self.name} ({self.size} bytes)"

    def __str__(self):
        return self.__repr__()


root = Directory("/", [], None, 0)


def PrintFileSystem(currentDirectory, depth):
    if isinstance(currentDirectory, Directory):
        print(f"{'  '*depth}{currentDirectory.name} -> {currentDirectory.size}")
        for child in currentDirectory.children:
            PrintFileSystem(child, depth+1)
    else:
        print(f"{'  '*depth}{currentDirectory.name} ({currentDirectory.size} bytes)")


def update_sizes(directory, size):
    """
    Updates the size of a directory and all of its parents
    """
    if directory.parent is not None:
        directory.parent.size += size
        update_sizes(directory.parent, size)


if __name__ == '__main__':
    # dir = Directory("a", [], root)
    # print(root)
    # Directory("b", [], dir)
    # dir = root.changeDirectory("a")
    # print(root)

    file = open('day7.in', 'r')
    # file = open('day7_example.in', 'r')
    lines = file.readlines()
    file.close()
    current = root
    for i in range(len(lines)):
        line = lines[i]
        if line[0] == '$':
            # Line is a command
            # cd - change directory
            # ls - list directory
            # Check command type
            if line[2:4] == 'cd':
                # Change directory
                # .. goes up one directory
                # / goes to root
                # else goes to child directory
                newDirectory = line[5:-1]
                # print(f"cd {newDirectory}")
                # print(f"Current: {current}")
                current = current.changeDirectory(newDirectory)
            elif line[2:4] == 'ls':
                # List directory
                # print(f"ls {current.name}")
                # Go until next command and add each line as a child of the current directory
                for j in range(i + 1, len(lines)):
                    if lines[j][0] == '$':
                        break
                    else:
                        # Add child
                        # If line starts with dir then it is a directory
                        # Otherwise add as file
                        if lines[j][0:3] == 'dir':
                            # print(f" - dir {lines[j][4:-1]}")
                            Directory(lines[j][4:-1], [], current, 0)
                        else:
                            # print(f" - file {lines[j][:-1]}")
                            size = int(re.search(r'\d+', lines[j])[0])
                            name = lines[j].split(' ')[1].strip()
                            f = File(name, size, current)
                            current.size += size
                            # print(f"New File: {f}")
                            update_sizes(current, size)
    # print(root)
    PrintFileSystem(root, 0)

    # Part 1
    total = 0
    q = [root]
    while len(q) > 0:
        directory = q.pop(0)
        # If directory size is less than 100000
        if isinstance(directory, Directory) and directory.size <= 100000:
            # Add to total
            total += directory.size
        if isinstance(directory, Directory):
            # Add children to queue
            q += directory.children
    print(f"Part 1: {total}")

    # Part 2
    free_space = 70000000 - root.size
    # Find the smallest directory that, if deleted, would free up
    # enough space on the filesystem to run the update
    # Free space required = 30000000
    answer = 1e9
    q = [root]
    while len(q) > 0:
        directory = q.pop(0)
        # If directory size is less than 100000
        if isinstance(directory, Directory) and free_space + directory.size >= 30000000 and directory.size < answer:
            # Add to total
            answer = directory.size
        if isinstance(directory, Directory):
            # Add children to queue
            q += directory.children
    print(f"Part 2: {answer}")