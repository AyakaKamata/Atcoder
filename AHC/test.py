# 想定フォルダ構成
# AHC
#   ├── test.py                     # このファイル
#   └── <contest num>
#           ├── <solve.exe>
#           └── tools or tools_x86_64-pc-windows-gnu
#                   ├── in/                  # テスト入力
#                   ├── out/                 # テスト出力
#                   └── vis.exe              # ローカルテスタ実行ファイル ※windows用のコンパイル済みバイナリの場合

import os
import subprocess
import time
import sys
from concurrent import futures
from math import log10
from typing import List

if len(sys.argv) < 2:
    print("Usage: python test.py <contest_num>")
    sys.exit(1)

CONTEST_NUM = sys.argv[1]
PROGRAM_CMD = os.path.join(CONTEST_NUM, "solve.exe")

START_SEED = 0
SIZE = 100
STEP = 1
MAX_WORKERS = 6
TESTER_OUTPUT_SCORE_TXT = "Score ="
TESTER_DIR = os.path.join(CONTEST_NUM, "tools_x86_64-pc-windows-gnu")
TESTER_CMD = os.path.join(TESTER_DIR, "vis.exe")
TEST_IN_DIR = "in"
TEST_OUT_DIR = "out"

script_dir = os.path.dirname(os.path.abspath(__file__))
TEST_IDS = list(range(START_SEED, START_SEED + SIZE * STEP, STEP))


class TaskInfo:
    def __init__(self, score: int, time: float, seed: int = 0):
        self.score = score
        self.time = time
        self.seed = seed


class Task:
    @classmethod
    def execute(cls, input_file: str, output_file: str, seed: int) -> TaskInfo:
        t_start = time.perf_counter()

        cmd = [PROGRAM_CMD]
        with open(input_file, "r") as fin, open(output_file, "w") as fout:
            result = subprocess.run(cmd, stdin=fin, stdout=fout, stderr=subprocess.PIPE)

        t_end = time.perf_counter()
        t_lapse = t_end - t_start
        ret = TaskInfo(score=0, time=t_lapse, seed=seed)

        execute_tester_command = [TESTER_CMD, input_file, output_file]
        result = subprocess.run(
            execute_tester_command,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            cwd=os.path.join(script_dir, TESTER_DIR),
        )
        std_out = result.stdout.decode("utf-8", "ignore")

        for out in std_out.split("\n"):
            if TESTER_OUTPUT_SCORE_TXT in out:
                try:
                    ret.score = int(out.split(TESTER_OUTPUT_SCORE_TXT)[1].strip())
                except ValueError:
                    pass
                break
        return ret


def task(seed: int, in_path: str, out_path: str) -> TaskInfo:
    os.makedirs(os.path.dirname(out_path), exist_ok=True)
    return Task.execute(input_file=in_path, output_file=out_path, seed=seed)


if __name__ == "__main__":
    executor = futures.ThreadPoolExecutor(max_workers=MAX_WORKERS)
    t_test_start = time.perf_counter()

    tasks = []
    for seed in TEST_IDS:
        in_path = os.path.join(script_dir, TESTER_DIR, TEST_IN_DIR, f"{seed:04}.txt")
        out_path = os.path.join(script_dir, TESTER_DIR, TEST_OUT_DIR, f"{seed:04}.txt")
        if os.path.exists(in_path):
            tasks.append((executor.submit(task, seed, in_path, out_path), seed))

    task_results: List[TaskInfo] = []
    t_sum = 0

    for tsk, i_test in tasks:
        info: TaskInfo = tsk.result()
        task_results.append(info)
        t_ms = round(info.time * 1000)
        t_sum += t_ms
        print(f"{i_test:3d}  score:{info.score:12,d} {t_ms:5d} ms")

    scores = [r.score for r in task_results]
    total_score = sum(scores)
    average_log_score = sum(log10(s) for s in scores) / len(scores)

    print(f"\ntotal   time: {(time.perf_counter() - t_test_start):.1f} s")
    print(f"average time: {t_sum / len(tasks):.0f} ms")
    print(f"sum score   : {total_score:,} pt")
    print(f"average(log): {average_log_score:.5f}")

    RESULT_FILE = "result.csv"
    result_file_path = os.path.join(script_dir, CONTEST_NUM, RESULT_FILE)

    with open(result_file_path, "w") as fp:
        fp.write(f"total  ,{total_score:10d}\n")
        fp.write(f"average log,{average_log_score:8.5f}\n")
        for r in task_results:
            fp.write(f"test{r.seed:03d},{r.score:d}\n")
