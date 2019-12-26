import json
from subprocess import (DEVNULL, PIPE, STDOUT, CalledProcessError,
    TimeoutExpired, call, check_call, check_output, run)
from pathlib import Path
from datetime import datetime
import argparse

def execute(exe: Path, source: str):
    verify_name = exe.stem
    try: 
        proc = run([exe], stdout=PIPE)
        return (verify_name, {
                    "execute_path": str(exe),
                    "source_path": source,
                    "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                    "status": "OK",
                    "detail": json.loads(str(proc.stdout.decode('utf8')))
                })
    except Exception as e:
        # print("verify except: %s" % verify_name)
        print(e)
        return (verify_name, {
                    "execute_path": str(exe),
                    "source_path": source,
                    "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                    "status": "RE",
                    "detail": str(e)
                })

def load_old_verify_results(path: Path):
    try:
        return json.load(open(path, 'r'))
    except:
        return {}

def is_verify_skip(old_results, verify_source: Path):
    verify_name = verify_source.stem
    if verify_name in old_results:
        old_timestamp = datetime.strptime(old_results[verify_name]["timestamp"], '%Y-%m-%d %H:%M:%S')
        file_timestamp = datetime.fromtimestamp(verify_source.stat().st_ctime)
        return old_timestamp > file_timestamp
    return False

if __name__ == '__main__':

    parser = argparse.ArgumentParser(description='generate ds_verify result')
    parser.add_argument('cmake_build_path', type=Path, default=None, help='path to cmake build directory')
    parser.add_argument('--all', action='store_true', default=None, help='if all files are not change, dont run verify')

    parsed = parser.parse_args()

    build_path = parsed.cmake_build_path
    all_verify_flag = parsed.all

    verify_list = open(build_path / "verify_list", 'r').read().split('\n')

    verify_results = load_old_verify_results(".ds_verify/verify_results.json")

    if all_verify_flag:
        skip = True
        for verify_task in verify_list[0:-1]:
            task_tmp = verify_task.split(':')
            verify_exe = task_tmp[0]
            verify_source = task_tmp[1]

            if not is_verify_skip(verify_results, Path(verify_source)):
                skip = False

        if skip:
            print("all skip")
            exit()

    for verify_task in verify_list[0:-1]:
        task_tmp = verify_task.split(':')
        verify_exe = task_tmp[0]
        verify_source = task_tmp[1]

        print("verify: %s" % verify_source)

        (verify_name, status) = execute(Path(verify_exe), verify_source)
        verify_results[verify_name] = status
    
    json.dump(verify_results, open(build_path / "verify_results.json", 'w'), indent=2)

    print("finish")


