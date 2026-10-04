from pathlib import Path
import subprocess,re
ROOT=Path(__file__).resolve().parents[1]
fmt=ROOT/'rebuild/tools/clang_format/data/bin/clang-format.exe'
assert fmt.exists(),fmt
files=list((ROOT/'code').glob('*.hpp'))+list((ROOT/'rebuild/additions').glob('*.hpp'))
for p in files:
    s=p.read_text(encoding='utf-8')
    # Match the user's increment style when the result is unused in a for clause.
    s=re.sub(r'(for\s*\([^;\n]*;[^;\n]*;\s*)\+\+(\w+)(\s*\))',r'\1\2++\3',s)
    s=re.sub(r'(for\s*\([^;\n]*;[^;\n]*;\s*)--(\w+)(\s*\))',r'\1\2--\3',s)
    p.write_text(s,encoding='utf-8')
    subprocess.run([str(fmt),'-i','--style=file',str(p)],check=True)
print('Formatted',len(files),'files')
