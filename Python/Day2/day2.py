import os

def part1(instructions):

    depth = 0
    height = 0
    
    for instruction in instructions:

        direction , value = instruction
        
        if direction == "down":
        
            depth += value
        
        elif direction == "up":
        
            depth -= value
        
        elif direction == "forward":
            
            height += value
    
    return depth*height

def part2(instructions):

    depth = 0
    height = 0
    aim = 0
    
    for instruction in instructions:

        direction , value = instruction
        
        if direction == "down":
        
            aim += value
        
        elif direction == "up":
        
            aim -= value
        
        elif direction == "forward":
            
            height += value
            depth += value*aim
    
    return depth*height




def main():
    instructions = []
    
    dirname = os.path.dirname(__file__)
    filename = os.path.join(dirname, 'input.txt')

    with open(filename, encoding='utf8') as f:
        
        for line in f:
            l = line.split(" ")

            instruction = (l[0], int(l[1]))
            instructions.append(instruction)
      
    print("Part one answer : "  + str(part1(instructions)))
    print("Part two answer : "  + str(part2(instructions)))
    
             

if __name__ == "__main__":
    main()
