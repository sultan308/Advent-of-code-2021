
def find_increaseing(sonar_report , window_size):
    """
    Findes number of increasing consective windows ie [w1 , w2] if w1 > w2 counts as one  

    Parameters
    ----------
    sonar_report : list
        a list of integers 
    window_size : int
        the width of each window so 3 would mean [index , index +1 , index+2]

    Returns
    -------
    int
        The number of sums larger than the previous sum

    """
    #Calculates the number of valid windows in the list
    number_of_windows = len(sonar_report) - window_size + 1 
    
    prev_sum = 0
    num_of_increase = 0
    
    
    for i in  range(number_of_windows):
        
        current_sum = 0
        #Gets the window total value
        for j in range(window_size):
            current_sum+=sonar_report[i+j]
        
        #skips first iteration
        if(i!=0): 
            if(current_sum > prev_sum) : num_of_increase+=1
        prev_sum = current_sum
    
    return num_of_increase
        



def main():
    sonar_report = []
    with open('input.txt', encoding='utf8') as f:
        for line in f:
            sonar_report.append(int(line.strip()))
           
    print("Part one answer : " + str(find_increaseing(sonar_report,1)) )
    print("Part two answer : " + str(find_increaseing(sonar_report,3)) )
    
             

if __name__ == "__main__":
    main()
