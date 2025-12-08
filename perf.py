"""
Program to track the time it takes to solve all AoC part 2 of 2023 and 2024
"""

import os
import subprocess
import time
from functools import reduce

def getPrograms(year):
    prefix = str(year) + '/'
    days = []
    for dir in os.listdir(prefix):
        try:
            i = int(dir) # to throw error when needed

            cpp = [f for f in os.listdir(prefix + dir) if f.endswith(".cpp")]
            cpp.sort(key=lambda x: len(x))
            cpp = dir + '/' + cpp[0]

            day = {
                "year": year,
                "cpp": cpp,
                "input": cpp.replace('.cpp', '.in'),
                "exe": cpp.replace('.cpp', '')
            }

            days.append(day)
        except:
            print(f"ERROR: {dir} {i} not compiled")
    
    return days



def main():
    days = getPrograms(2023) + getPrograms(2024) + getPrograms(2025)

    days.sort(key=lambda x: (x['year'], x['input']))    

    for e in days:
        i = e['exe'].split('/')[0]
        prefix = str(e['year']) + '/'
        x = subprocess.getoutput(f'g++ -std=c++20 -O2 {prefix + e['cpp']} -o {prefix + e['exe']}')
        if x != "":
            print("ERROR IN DAY " + i)
            print(x)
        else:
            print(f"DAY {i} {e['year']} COMPILED")

    t = []
    for e in days:
        i = e['exe'].split('/')[0]
        prefix = str(e['year']) + '/'
        start = time.time()
        x = subprocess.getoutput(f'./{prefix + e['exe']} < {prefix + e['input']}')
        dt = time.time() - start
        t.append(dt)
        print(f"DAY {i}: {"{:.2f}".format(1000*dt)}ms")
        print(x)
        print()
        os.remove(prefix + e['exe'])

    
    total = reduce(lambda x,y: x+y, t)
    print(f'\n\nTotal: {"{:.2f}".format(1000*total)}ms')
    per = [(x/total, i) for i, x in enumerate(t)]
    per.sort(reverse=True)
    for i, p in enumerate(per):
        if(t[p[1]] > 1/100):
            print(f'{"{:01}".format(i+1)}º: {2023 if p[1]//25==0 else 2024} day {"{:02}".format((p[1]%25)+1)} -> {"{:.2f}".format(100*p[0])}%\t\t{"{:.2f}".format(1000*t[p[1]])}ms')
        

if __name__ == "__main__":
    main()