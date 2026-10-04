from pathlib import Path
import json,re,hashlib
ROOT=Path(__file__).resolve().parents[1]
book=json.loads((ROOT/'source/handbook.json').read_text(encoding='utf-8'))
rs={name:json.loads((ROOT/'tests/revised'/f'{name}.json').read_text(encoding='utf-8')) for name in ['compile','verification','examples','printed']}
for name,a in rs.items():
    assert all(x.get('ok') for x in a),name
count=sum(int(re.findall(r'PASS \w+ (\d+)',x['log'])[-1]) for x in rs['verification'])
lines=['# 算法竞赛模板 · GNU++17 修订版','','日期：2026-10-02。原资料的全部163个条目均有复核结论；正文104份代码，40份使用示例（3份为Min_25完整改法）。',
       '', '打印版在 output/pdf/算法竞赛模板_GNU17_修订打印版.pdf。所有页码以实际页面为准。此源稿还包含12个移出打印正文的条目。',
       '', '各 hpp 为独立完整模板，按题目选用。不同模块的同名类型应手动合并；不要一次 include 所有文件。GNU++17、4空格缩进、运算符空格，不使用 optional / bit_width。']
audit=['# 逐项复核与验证记录','','原件：Algorithm_Handbook_Print.pdf（157页，保留未改动）。日期：2026-10-02。',
       '',f'104/104 独立编译通过；6/6 对照测试组通过，累计 {count:,} 次 CHECK；40/40 调用/改法示例与1份20万点链检查通过；11/11 打印代码依赖展开编译通过。',
       '', '这记录实测结果，不代表形式化正确性证明。浮点误差、随机分解耗时与实际题目约束按各条说明处理。',
       '', '|编号|原页|条目|处理|新打印页|验证|','|---|---:|---|---|---:|---|']
cur=''
for x in book:
    if x['chapter']!=cur:cur=x['chapter'];lines+=['','## '+cur]
    title=x.get('number') or f'原条目{x["id"]+1}'
    lines+=['','### '+title+' '+x['title']+('（移出打印正文）' if not x['print'] else ''),'']
    lines+=x['notes']
    if x['code']:
        lines+=['',f'完整独立代码：`code/{x["code"]}`。','','```cpp',(ROOT/'code'/x['code']).read_text(encoding='utf-8'),'```']
    for ex in x['examples']:
        lines+=['','#### '+ex['title'],'',f'可编译文件：`{ex["file"]}`。']
        if ex.get('deps'):lines+=['额外依赖：'+', '.join(ex['deps'])+'。']
        lines+=['','```cpp',ex['code'],'```']
    audit+=[f'|{x["id"]+1}|{x["old_page"]}|{x["title"]}|{x["action"]}|{x.get("page") or "—"}|{"；".join(x["checks"])}|']
audit+=['','## 本次实质修正','',
 '* 逐项重写接口说明：下标、闭/半开区间、返回 bool 的输出参数、非法/不可达约定、运算范围、适用条件。',
 '* 格式：所有模板和示例统一空格、缩进、换行，for 循环采用用户要求的后置增量；缩短结构与常用字段名。',
 '* 兼容：移除 bit_width/bit_floor/optional/nullopt；虚树与倍增在 GNU++17 下独立编译。',
 '* 图论：完整重写欧拉路、Hopcroft-Karp、Boruvka、XOR MST、差分约束、区间优化建图、函数图、严格次小MST、最大权闭合图。',
 '* 流：修正自环反向边编号；上下界流补可行环流、非负最大/最小流、原边流量恢复与人工边双向删除；示例使用普通 bool + 输出结构。',
 '* 深链：SCC、2-SAT、桥割点、点双、LCA、HLD、树差分、虚树、DSU on Tree、直径、重心、点分大小遍历使用显式栈；Dinic与HK增广同样改为显式栈。',
 '* 数据结构：后继DSU查找不用递归；线段树空输入构造边界；Beats叶子极小上界与128位差值；可持久化修改语义说明；TopK的-1类别约定。',
 '* 筛法：杜教筛φ前缀用i128；Min_25商值、质数前缀、最小质因子递归含义与三处修改契约；φ/τ/μ改法均对照试除求和。',
 '* 多项式：FPS补齐到真实线性卷积长度，避免截断混叠；NTT大数组对照验证实际快速路径；对数常数项约定明确。',
 '* 数论与代数：CRT非互素与溢出状态；扩展BSGS最小解；模加法接近INT_MAX；矩形方程不再猜变量数；线性基无答案不与ULLONG_MAX冲突。',
 '* 字符串：SAM完整clone/计数教程；AC fail累加；Z空串；Manacher独立整数哨兵；PAM重复计数幂等；字节符号与子序列字符基准。',
 '* 几何：整型乘法先提升i128；凸包去重；最近点对O(nlogn)归并；点段/重合圆/退化Minkowski；半平面交有界正面积前提；矩形真实坐标长度。',
 '* 离线：莫队内部压缩；三维偏序重复点；整体二分稳定时间顺序与回滚；时间线段树的边生命周期。',
 '* 技巧：删除依赖未知函数的空框架；修正中位数奇偶约定、Knuth充分条件、WQS计数跳跃条件、SOS与子集卷积区别、树上背包不可达状态。',
 '', '## 验证文件', '',
 '`tests/revised/compile.json`：独立头文件语法检查；`verification.json`：固定种子712367的各组结果；`suite_*.cpp`：全部参照测试；`examples.json`：调用例子、Min_25改法与链检查；`printed.json`：正文省略重复基础后的依赖编译。',
 '', '运行编译器：MinGW g++ 14.2.0，-std=gnu++17；运行测试使用 -O2。没有实际比赛OJ提交记录，因此不写“已在所有题目上验证”。',
 '', '## 参考', '',
 '[OI Wiki 最小生成树](https://oi-wiki.org/graph/mst/)；[差分约束](https://oi-wiki.org/graph/diff-constraints/)；[二分图匹配](https://oi-wiki.org/graph/graph-matching/bigraph-match/)；[SAM](https://oi-wiki.org/string/sam/)；[杜教筛](https://oi-wiki.org/math/number-theory/hyperbola/)；[Min_25](https://oi-wiki.org/math/number-theory/min-25/)。主要用于核对算法前提，查阅日期2026-10-02。'
]
(ROOT/'source/算法竞赛模板_完整源稿.md').write_text('\n'.join(lines)+'\n',encoding='utf-8')
(ROOT/'source/逐项复核与验证记录.md').write_text('\n'.join(audit)+'\n',encoding='utf-8')
readme=f'''# 修订算法竞赛打印模板

最终打印文件：**output/pdf/算法竞赛模板_GNU17_修订打印版.pdf**。

* 104份GNU++17完整模板；有空格、4空格缩进与简短竞赛命名。
* 40份使用示例（含Min_25的φ/τ/μ改法），可独立编译运行。
* 原资料163条逐项复核，12个窄题意条目移出正文，仍保存在完整源稿。
* 连续页码、可点击目录/书签、跨页代码续标；实际打印时用A4、100%原尺寸。

## 从哪里开始

`source/算法竞赛模板_完整源稿.md`：全部说明、完整代码与示例，可直接编辑。

`code/`：独立模板；`examples/`：调用程序，包含必要头文件依赖。

`source/逐项复核与验证记录.md`：逐条处理和实测依据。

`Algorithm_Handbook_Print.pdf`：原157页文件，保留原样。

## 当前验证

104/104独立编译；6/6暴力/边界对照组（{count:,}次CHECK）；41/41示例与链检查；11/11正文依赖展开编译。

适用环境GNU++17。算法的字符集、范围、单调性、浮点精度等前提写在各条旁；测试不是形式化证明。

## 更新与重建

日常直接编辑 `code/*.hpp`、`source/handbook.json`、`examples/*.cpp`，再构建PDF。格式配置在本目录 `.clang-format`。

```powershell
python rebuild/format_code.py
python rebuild/check_compile.py
python rebuild/verify.py
python rebuild/build_pdf.py
python rebuild/publish_sources.py
python rebuild/qa_pdf.py
```

PDF需要reportlab；QA还用pdfplumber/pypdf/Pillow与Poppler。测试脚本使用当前机器 `D:/msys2/mingw64/bin/g++.exe`，换机器改该路径。clang-format当前在rebuild/tools/。

`recover.py`、`prepare.py`、`enrich.py`、`tutorials.py`、`extra_checks.py`是从原PDF重建本次修订的脚本；**不要在日常手改后随意运行prepare/enrich/tutorials，它们会重新生成对应内容并覆盖编辑。** 若要从恢复材料重新生成，应按这个顺序运行，再进行格式、验证、PDF与QA。

复核记录、恢复JSON与全部可编辑源文件均保留，后续无需再从PDF抽取。
'''
(ROOT/'README_修订版.md').write_text(readme,encoding='utf-8')
manifest={p.relative_to(ROOT).as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in [ROOT/'Algorithm_Handbook_Print.pdf']+list((ROOT/'code').glob('*.hpp'))+list((ROOT/'output/pdf').glob('*.pdf'))}
(ROOT/'source/sha256.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding='utf-8')
print('Saved complete source and 163-entry audit; CHECKS',count)
