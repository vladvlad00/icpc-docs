import os
import re

for ch in os.listdir('content'):
	files = os.listdir(os.path.join('content',ch))
	with open(os.path.join('content',ch,'chapter.tex')) as f:
		content = f.read()
	res = re.findall(r"\\kactlimport\[?.*?\]?\{(.*?)\}", content)
	files = [i for i in files if i.endswith('.h') or i.endswith('.cpp') or i.endswith('.txt') or i.endswith('.py') or i.endswith('.sh')]
	files = set(files)
	res = set(res)
	print(ch)
	print(f'add {files - res}')
	print(f'remove {res - files}')
	print()
