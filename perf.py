"""
Program to track the time it takes to solve all AoC part 2s
"""

import os
import subprocess
import time
import concurrent.futures as cf


class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


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
                "exe": cpp.replace('.cpp', ''),
                "day": i,
            }

            days.append(day)
        except:
            print(f"ERROR: {dir} {i} not compiled")
    
    return days


def run_cmd(cmd, day, year):
    result = subprocess.run(
        cmd,
        shell=True,
        capture_output=True,
        text=True,
    )
    return result.stderr, day, year


def main():    
    days = getPrograms(2023) + getPrograms(2024) + getPrograms(2025)

    days.sort(key=lambda x: (x['year'], x['input']))    


    print(bcolors.HEADER + "\n\n-----COMPILATION-----\n" + bcolors.ENDC)
    times_file = "times.txt"
    open(times_file, 'w').close()
    commands = []
    for e in days:
        prefix = str(e['year']) + '/'
        commands.append((
            f'g++ -std=c++20 -DOUT_FILE=\'"{times_file}"\' -DYEAR={e['year']} -DDAY={e['day']} -O2 {prefix + e['cpp']} -o {prefix + e['exe']}',
            e['day'],
            e['year']
        ))
        
        
    with cf.ThreadPoolExecutor() as pool:
        futures = [pool.submit(run_cmd, cmd, day, year) for cmd, day, year in commands]

        for future in cf.as_completed(futures):
            err, day, year = future.result()
            if err:
                print(bcolors.FAIL + f'ERROR IN DAY {day} {year}' + bcolors.ENDC)
                print(bcolors.WARNING + err + bcolors.ENDC)
            else:
                print(bcolors.OKGREEN + f'DAY {day} {year} COMPILED' + bcolors.ENDC)


    print(bcolors.HEADER + "\n\n------EXECUTION------\n" + bcolors.ENDC)
    for e in days:
        prefix = str(e['year']) + '/'
        subprocess.run(f'./{prefix + e['exe']} < {prefix + e['input']}', shell=True, text=True, capture_output=True)
        os.remove(prefix + e['exe'])


    total = 0
    t = []
    with open(times_file) as file:
        for i, entry in enumerate(file):
            nums = entry.split(';')
            e = {
                'day': nums[0],
                'year': nums[1],
                'time': int(nums[2]),
                'out': nums[3]
            }

            total += e['time']
            t.append(e)

            print(bcolors.BOLD + f'Day {e['day']} {e['year']}: {"{:.2f}".format(e['time']/1000)}ms' + bcolors.ENDC)
            print(e['out'])
            print()
    
    os.remove(times_file)


    print(bcolors.HEADER + f'\n\nTOTAL TIME: {"{:.2f}".format(total/1000)}ms' + bcolors.ENDC)
    t.sort(reverse=True, key=lambda x: x['time'])
    for i, e in enumerate(t):
        if(e['time'] > 1000):
            print(bcolors.OKBLUE + f'{"{:01}".format(i+1)}º: {e['year']} day {e['day']} -> {"{:05.2f}".format(100*e['time']/total)}%\t\t{"{:.2f}".format(e['time']/1000)}ms' + bcolors.ENDC)
        

if __name__ == "__main__":
    main()