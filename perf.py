"""
Program to track the time it takes to solve all AoC part 2s

Add --profiled argument to use the -fprofile option, so the programs will be run twice, one time for making a .gcda file for profiling and another compilation using the profiled data

"""

import os
import subprocess
import sys
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

NUMBER_OF_RUNS = 10


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



def compile_run(days, action_msg: str, profiled: bool, gen_prof_data = False):    
    commands = []
    prof = ''
    if gen_prof_data: 
        prof = '-fprofile-generate'
    elif profiled: 
        prof = '-fprofile-use'
    for e in days:
        prefix = str(e['year']) + '/'
        defines = f"-DOUT_FILE -DYEAR={e['year']} -DDAY={e['day']}"

        commands.append((
            f"g++ -std=c++20 {defines} -O2 {prof} {prefix + e['cpp']} -o {prefix + e['exe']}",
            e['day'],
            e['year']
        ))

    with cf.ThreadPoolExecutor() as pool:
        futures = [pool.submit(run_cmd, cmd, day, year) for cmd, day, year in commands]

        for future in cf.as_completed(futures):
            err, day, year = future.result()
            if err:
                print(bcolors.FAIL + f"ERROR IN DAY {day} {year}" + bcolors.ENDC)
                print(bcolors.WARNING + err + bcolors.ENDC)
            else:
                if gen_prof_data:
                    prefix = str(year) + '/' + ("%02d" % day) + '/'
                    e = subprocess.getoutput(f"./{prefix + str(day)} /dev/null < {prefix + str(day)}.in")
                    print(e)
                    os.remove(prefix + str(day))
                print(bcolors.OKGREEN + f"DAY {day} {year} {action_msg}" + bcolors.ENDC)



def remove_files(days, profiled):
    for e in days:
        prefix = str(e['year']) + '/'
        os.remove(prefix + e['exe'])

        if profiled:
            os.remove(prefix + e['exe'] + '.gcda')



def test_run(days, n):    
    times_file = "test" + str(n) + ".txt"
    open(times_file, 'w').close() # clear file contents
    for e in days:
        prefix = str(e['year']) + '/'
        subprocess.run(f"./{prefix + e['exe']} {times_file} < {prefix + e['input']}", shell=True, text=True, capture_output=True)

    t = []
    with open(times_file) as file:
        for entry in file:
            nums = entry.split(';')
            e = {
                'day': nums[0],
                'year': nums[1],
                'time': int(nums[2]),
                'out': nums[3]
            }
            t.append(e)

    return t, times_file, n



def main():    
    days = getPrograms(2023) + getPrograms(2024) + getPrograms(2025)
    days.sort(key=lambda x: (x['year'], x['input']))    

    profiled = sys.argv[1] == '--profiled' if len(sys.argv) > 1 else False

    if profiled:
        print(bcolors.HEADER + "\n\n-----PROFILING-----\n" + bcolors.ENDC) 
        compile_run(days, 'PROFILED', profiled, gen_prof_data=True)

    
    print(bcolors.HEADER + "\n\n-----COMPILATION-----\n" + bcolors.ENDC)
    compile_run(days, 'COMPILED', profiled)


    print(bcolors.HEADER + "\n\n------EXECUTION------\n" + bcolors.ENDC)
    times = []
    with cf.ThreadPoolExecutor(max_workers=2) as pool:
        futures = [pool.submit(test_run, days, n+1) for n in range(NUMBER_OF_RUNS)]
        for future in cf.as_completed(futures):
            t, file, n = future.result()
            times.append(t)
            os.remove(file)
            print(bcolors.OKGREEN + "Run " + str(n) + " done" + bcolors.ENDC)

    
    
    print(bcolors.HEADER + "\n\n------RESULTS------\n" + bcolors.ENDC)
    
    avgs = []
    mins = []
    for i in range(len(times[0])): # i know this is not pythonic
        val = 1e12
        avg = 0
        for j in range(NUMBER_OF_RUNS):
            val = min(val, times[j][i]['time'])
            avg += times[j][i]['time']
        
        e = times[0][i]
        e['time'] = val
        mins.append(e.copy())
        e['time'] = avg / NUMBER_OF_RUNS
        avgs.append(e.copy())
        

    total_avg = 0
    total_min = 0
    for a, m in zip(avgs, mins):
        total_avg += a['time']
        total_min += m['time']
        print(bcolors.BOLD + f"Day {a['day']} {a['year']}: {'{:.2f}'.format(m['time']/1000)}ms (min)\t\t{'{:.2f}'.format(a['time']/1000)}ms (avg)" + bcolors.ENDC)
        print(a['out']) 

    remove_files(days, profiled)    

    print(bcolors.HEADER + f"\n\nTOTAL TIME:\t\t\t\t{'{:.2f}'.format(total_min/1000)}ms (min)\t\t{'{:.2f}'.format(total_avg/1000)}ms (avg)" + bcolors.ENDC)
    ams = list(zip(avgs, mins))
    ams.sort(reverse=True, key=lambda x: x[0]['time'])
    for i, (a, m) in enumerate(ams):
        if(a['time'] > 1000):
            print(bcolors.OKBLUE + f"{'{:01}'.format(i+1)}º: {a['year']} day {a['day']} -> {'{:05.2f}'.format(100*a['time']/total_avg)}%\t\t{'{:.2f}'.format(m['time']/1000)}ms   \t\t{'{:.2f}'.format(a['time']/1000)}ms" + bcolors.ENDC)
        

if __name__ == "__main__":
    main()