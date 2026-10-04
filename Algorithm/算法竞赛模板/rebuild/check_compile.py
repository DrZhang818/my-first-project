from pathlib import Path
import subprocess,concurrent.futures,json
ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'tests/revised';OUT.mkdir(parents=True,exist_ok=True)
def run(p):
    tmp=OUT/(p.stem+'_compile.cpp')
    tmp.write_text('#include "'+p.as_posix()+'"\nint main() {}\n',encoding='utf-8')
    r=subprocess.run(['D:/msys2/mingw64/bin/g++.exe','-std=gnu++17','-O0','-fsyntax-only',str(tmp)],capture_output=True,text=True,encoding='utf-8',errors='replace')
    return dict(file=p.name,ok=r.returncode==0,log=r.stderr)
with concurrent.futures.ThreadPoolExecutor(max_workers=4) as ex:
    rs=list(ex.map(run,sorted((ROOT/'code').glob('*.hpp'))))
(OUT/'compile.json').write_text(json.dumps(rs,ensure_ascii=False,indent=2),encoding='utf-8')
for r in rs:
    if not r['ok']:print(r['file'],r['log'][:1800])
print('COMPILE',sum(r['ok'] for r in rs),'/',len(rs))
