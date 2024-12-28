"""
Program to track the time it takes to solve all AoC part2, except for day 24 as it was done manually
"""

import os
import subprocess
import time
from functools import reduce

def main():
    days = []
    for dir in os.listdir("."):
        try:
            i = int(dir) # to throw error when needed
            if i == 24:
                raise ValueError("Day 24")

            cpp = [f for f in os.listdir(dir) if f.endswith(".cpp")]
            cpp.sort(key=lambda x: len(x))
            cpp = dir + '/' + cpp[0]

            day = {
                "cpp": cpp,
                "input": cpp.replace('.cpp', '.in'),
                "exe": cpp.replace('.cpp', '')
            }

            days.append(day)
        except:
            pass

    days.sort(key=lambda x: x['input'])    

    """for e in days:
        i = e['exe'].split('/')[0]
        x = subprocess.getoutput(f'g++ -std=c++20 -O3 {e['cpp']} -o {e['exe']}')
        if x != "":
            print("ERROR IN DAY " + i)
        else:
            print(f"DAY {i} COMPILED")"""
    
    t = []
    for e in days:
        i = e['exe'].split('/')[0]
        start = time.time()
        x = subprocess.getoutput(f'./{e['exe']} < {e['input']}')
        dt = time.time() - start
        t.append(dt)
        print(f"DAY {i}: {"{:.2f}".format(1000*dt)}ms")
        print(x)
        print()
        os.remove(e['exe'])

    
    total = reduce(lambda x,y: x+y, t)
    print(f'\n\nTotal: {"{:.2f}".format(1000*total)}ms')
    per = [(x/total, i) for i, x in enumerate(t)]
    per.sort(reverse=True)
    for i, p in enumerate(per):
        print(f'{"{:02}".format(i+1)}º: day {"{:02}".format(p[1]+1)} -> {"{:.2f}".format(100*p[0])}%\t\t{"{:.2f}".format(1000*t[p[1]])}ms')
        

if __name__ == "__main__":
    main()