import json
from subprocess import (DEVNULL, PIPE, STDOUT, CalledProcessError,
    TimeoutExpired, call, check_call, check_output, run)
from pathlib import Path
from datetime import datetime

def execute(exe: Path, source: str):
    verify_name = exe.stem
    try: 
        proc = run([exe], stdout=PIPE)
        return {
                    "execute_name": verify_name,
                    "execute_path": str(exe),
                    "source_path": source,
                    "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                    "status": "OK",
                    "detail": json.loads(str(proc.stdout.decode('utf8')))
                }
    except Exception as e:
        # print("verify except: %s" % verify_name)
        print(e)
        return {
                    "execute_name": verify_name,
                    "execute_path": str(exe),
                    "source_path": source,
                    "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                    "status": "RE",
                    "detail": str(e)
                }

if __name__ == '__main__':

    verify_list = open('verify_list', 'r').read().split('\n')
    verify_results = []
    for verify_task in verify_list[0:-1]:
        task_tmp = verify_task.split(':')
        verify_exe = task_tmp[0]
        verify_source = task_tmp[1]

        print("verify: %s" % verify_source)

        result = execute(Path(verify_exe), verify_source)
        verify_results.append(result)
    
    json.dump(verify_results, open("verify_results.json", 'w'), indent=2)

    print("finish")


