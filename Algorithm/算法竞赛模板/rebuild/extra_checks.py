from pathlib import Path
import json,re,subprocess,concurrent.futures
ROOT=Path(__file__).resolve().parents[1];OUT=ROOT/'tests/revised';OUT.mkdir(exist_ok=True)
book=json.loads((ROOT/'source/handbook.json').read_text(encoding='utf-8'))
base=(ROOT/'code/min25_sieve.hpp').read_text(encoding='utf-8')
variants={
 'phi':('''i64 fpe(i64 p, int e) const {return powerMod(p % mod, e - 1, mod) * ((p - 1) % mod) % mod;}
i64 sumFp(i64 x) const {int k = get(x); return (g1[k] - g0[k] + mod) % mod;}
i64 sumFpPrefix(int j) const {return (sp1[j] - sp0[j] % mod + mod) % mod;}''', 'v=v/p*(p-1);'),
 'tau':('''i64 fpe(i64 p, int e) const {return (e + 1) % mod;}
i64 sumFp(i64 x) const {return 2 * g0[get(x)] % mod;}
i64 sumFpPrefix(int j) const {return 2 * sp0[j] % mod;}''','v*=e+1;'),
 'mu':('''i64 fpe(i64 p, int e) const {return e == 1 ? mod - 1 : 0;}
i64 sumFp(i64 x) const {return (mod - g0[get(x)]) % mod;}
i64 sumFpPrefix(int j) const {return (mod - sp0[j] % mod) % mod;}''','v=e>1?0:-v;')
}
fmt=ROOT/'rebuild/tools/clang_format/data/bin/clang-format.exe'
def replace_fn(c,name,fn):
    p=c.index('    i64 '+name+'(');dep=0
    for q in range(c.index('{',p),len(c)):
        dep+=(c[q]=='{')-(c[q]=='}')
        if dep==0:return c[:p]+fn+c[q+1:]
paths=list((ROOT/'examples').glob('*.cpp'))
for key,(hooks,change) in variants.items():
    c=base
    for fn in hooks.splitlines():c=replace_fn(c,re.search(r'i64 (\w+)\(',fn).group(1),fn)
    # Independent trial factorisation, including prime powers and small moduli.
    c+='''\nint main(){for(int P:{7,101,1000000007}) {long long sum=0;
for(int n=1;n<=800;n++){int x=n;long long v='''+('n' if key=='phi' else '1')+''';
for(int p=2;p<=x;p++)if(x%p==0){int e=0;while(x%p==0)x/=p,e++;'''+change+'''}
sum=(sum+v%P+P)%P;assert(Min25Sieve(n,P).solve()==sum);}}
}\n'''
    p=ROOT/'examples'/f'min25_{key}.cpp';p.write_text(c,encoding='utf-8');paths.append(p)
    subprocess.run([str(fmt),'-i','--style=file',str(p)],check=True)
    temp=ROOT/'tmp'/f'{key}_hooks.cpp';temp.parent.mkdir(exist_ok=True)
    temp.write_text(hooks,encoding='utf-8');subprocess.run([str(fmt),'-i','--style=file',str(temp)],check=True)
    book[92]['examples'].append(dict(title={'phi':'改成 φ','tau':'改成约数个数 τ','mu':'改成 μ'}[key]+'：替换三处函数',
        code=temp.read_text(encoding='utf-8'),file=p.relative_to(ROOT).as_posix(),deps=[],kind='hooks'))
(ROOT/'source/handbook.json').write_text(json.dumps(book,ensure_ascii=False,indent=2),encoding='utf-8')
stress='''#include <bits/stdc++.h>
using namespace std;
'''
for key in ('scc','bridge_articulation','dinic','hopcroft_karp','hld','dsu_on_tree','centroid_decomposition'):
    stress+='namespace '+key+' {\n#include "'+(ROOT/'code'/f'{key}.hpp').as_posix()+'"\n}\n'
stress+='''int main(){int n=200000;vector<vector<int>>g(n+1);
for(int u=2;u<=n;u++)g[u].push_back(u-1),g[u-1].push_back(u);
{vector<vector<int>>a(n+1);for(int u=1;u<n;u++)a[u].push_back(u+1);scc::SCC s(a);assert(s.count==n);}
{bridge_articulation::Lowlink s(n);for(int u=1;u<n;u++)s.addEdge(u,u+1);s.work();assert(s.bridge[1]&&s.cut[n/2]&&!s.cut[1]);}
{dinic::Dinic s(n);for(int u=0;u<n-1;u++)s.addEdge(u,u+1,1);assert(s.maxFlow(0,n-1)==1);}
{hopcroft_karp::HK s(n,n);for(int u=1;u<n;u++){s.addEdge(u,u+1);s.addEdge(u,u);s.left[u]=u+1;s.right[u+1]=u;}s.addEdge(n,n);assert(s.solve()==n);}
{hld::HLD s(n);for(int u=1;u<n;u++)s.addEdge(u,u+1);s.work();assert(s.lca(n,n/2)==n/2&&s.rootedSize(n,1)==1);}
{dsu_on_tree::DSUOnTree s(g);int cur=0;s.run([&](int,int d){cur+=d;},[&](int u){assert(cur==n-u+1);});assert(cur==0);}
{centroid_decomposition::Centroid s(g);int dep=0;for(int u=1;u<=n;u++)dep=max(dep,s.level[u]);assert(dep<=18);}
cout<<"PASS 200000-vertex chains\\n";
}\n'''
p=OUT/'stress.cpp';p.write_text(stress,encoding='utf-8');paths.append(p)
def run(p):
    exe=OUT/(p.stem+'.exe');r=subprocess.run(['D:/msys2/mingw64/bin/g++.exe','-std=gnu++17','-O2',str(p),'-o',str(exe)],capture_output=True,text=True,encoding='utf-8',errors='replace')
    if r.returncode:return dict(file=p.name,ok=False,phase='compile',log=r.stderr)
    try:r=subprocess.run([str(exe)],capture_output=True,text=True,encoding='utf-8',errors='replace',timeout=90)
    except subprocess.TimeoutExpired:return dict(file=p.name,ok=False,phase='timeout',log='>90s')
    return dict(file=p.name,ok=r.returncode==0,phase='run',log=r.stdout+r.stderr)
with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:rs=list(pool.map(run,paths))
(OUT/'examples.json').write_text(json.dumps(rs,ensure_ascii=False,indent=2),encoding='utf-8')
for r in rs:
    if not r['ok']:print(r['file'],r['phase'],r['log'])
print('EXAMPLES AND STRESS',sum(r['ok'] for r in rs),'/',len(rs))
