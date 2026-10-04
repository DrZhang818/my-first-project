from pathlib import Path
import json,re,html,subprocess,concurrent.futures
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.lib import colors
from reportlab.lib.styles import ParagraphStyle
from reportlab.lib.enums import TA_CENTER
from reportlab.lib.pagesizes import A4
from reportlab.lib.units import mm
from reportlab.platypus import TableStyle
from reportlab.platypus import BaseDocTemplate,PageTemplate,Frame,Paragraph,Spacer,PageBreak,Flowable,KeepTogether
from reportlab.platypus.tableofcontents import TableOfContents
ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'output/pdf';OUT.mkdir(parents=True,exist_ok=True)
TMP=ROOT/'tmp/pdfs';TMP.mkdir(parents=True,exist_ok=True)
book=json.loads((ROOT/'source/handbook.json').read_text(encoding='utf-8'))
for name,file in [('CN','msyh.ttc'),('CNB','msyhbd.ttc'),('Code','consola.ttf'),('Math','cambria.ttc')]:
    pdfmetrics.registerFont(TTFont(name,'C:/Windows/Fonts/'+file,subfontIndex=0))
pdfmetrics.registerFontFamily('CN',normal='CN',bold='CNB')
styles={
 'body':ParagraphStyle('body',fontName='CN',fontSize=9.4,leading=14.2,spaceAfter=6,wordWrap='CJK',rightIndent=10),
 'chapter':ParagraphStyle('chapter',fontName='CNB',fontSize=18,leading=25,spaceAfter=15,keepWithNext=True),
 'heading':ParagraphStyle('heading',fontName='CNB',fontSize=12,leading=17,spaceBefore=10,spaceAfter=6,keepWithNext=True),
 'sub':ParagraphStyle('sub',fontName='CNB',fontSize=9.5,leading=14,spaceBefore=7,spaceAfter=5,keepWithNext=True),
 'small':ParagraphStyle('small',fontName='CN',fontSize=8.3,leading=12,spaceAfter=5,wordWrap='CJK',rightIndent=10),
 'cover':ParagraphStyle('cover',fontName='CNB',fontSize=30,leading=43,spaceAfter=20),
 'toc0':ParagraphStyle('toc0',fontName='CNB',fontSize=10.5,leading=17,spaceBefore=5),
 'toc1':ParagraphStyle('toc1',fontName='CN',fontSize=9.3,leading=14.4,leftIndent=12,firstLineIndent=0),
}
def font_for(ch,code=False):
    if code and ord(ch)<128:return 'Code'
    if pdfmetrics.getFont('CN').face.charToGlyph.get(ord(ch)):return 'CN'
    assert pdfmetrics.getFont('Math').face.charToGlyph.get(ord(ch)),('missing glyph',ch)
    return 'Math'
def xml(t):return ''.join(html.escape(c) if font_for(c)=='CN' else '<font name="Math">'+html.escape(c)+'</font>' for c in t)
def para(t,style='body'):return Paragraph(xml(t),styles[style])
def mixed_width(s,size):return sum(pdfmetrics.stringWidth(c,font_for(c,True),size) for c in s)
def draw_mixed(c,s,x,y,size):
    font=None;part=''
    for ch in s+'\0':
        f=font_for(ch,True) if ch!='\0' else None
        if f!=font or ch=='\0':
            if part:c.setFont(font,size);c.drawString(x,y,part);x+=pdfmetrics.stringWidth(part,font,size)
            font=f;part=''
        if ch!='\0':part+=ch

class CodeBlock(Flowable):
    def __init__(self,text,title,cont=False):
        super().__init__();self.lines=text.splitlines() if isinstance(text,str) else text
        self.title=title;self.cont=cont;self.fs=8.7;self.ld=10.65
    def wrap(self,w,h):
        self.width=w;self.height=20+len(self.lines)*self.ld+6
        bad=[s for s in self.lines if mixed_width(s,self.fs)>w-14]
        if bad:raise ValueError(('code exceeds page width',self.title,bad[0],mixed_width(bad[0],self.fs),w))
        return w,self.height
    def split(self,w,h):
        k=int((h-26)/self.ld)
        if k<7:return []
        if len(self.lines)-k<4:k=len(self.lines)-4
        if k<=0:return []
        return [CodeBlock(self.lines[:k],self.title,self.cont),CodeBlock(self.lines[k:],self.title,True)]
    def draw(self):
        c=self.canv;c.setStrokeColor(colors.HexColor('#B7B7B7'));c.setLineWidth(.35)
        c.line(0,self.height,self.width,self.height)
        c.setFont('CN',8);c.setFillColor(colors.HexColor('#555555'))
        c.drawString(5,self.height-12,self.title+(' · 续' if self.cont else ''))
        c.setFillColor(colors.black)
        y=self.height-24
        for s in self.lines:draw_mixed(c,s,5,y,self.fs);y-=self.ld
        c.setStrokeColor(colors.HexColor('#D0D0D0'));c.line(0,0,self.width,0)

deps={29:[28],36:[34],44:[34],52:[50],53:[50],118:[117],119:[117,118],120:[117],121:[117,118,119],123:[117],126:[117]}
markers={29:'struct EdgeBCC',36:'struct BoundFlow',44:'pair<i64, vector<int>> maxClosure',52:'struct TreeDiff',53:'struct VirtualTree',118:'template <class T> struct Line',119:'template <class T> bool onSeg',120:'template <class T> vector<Point<T>> convexHull',121:'template <class T> bool pointInPolygon',123:'template <class T> auto dist2',126:'template <class T>\nvector<Point<T>> minkowskiSum'}
snippets={}
for x in book:
    if not x['code']:continue
    c=(ROOT/'code'/x['code']).read_text(encoding='utf-8')
    c='\n'.join(s for s in c.splitlines() if not s.startswith('#pragma') and s.strip()!='#include <bits/stdc++.h>')
    if x['id'] in markers:c=c[c.index(markers[x['id']]):]
    snippets[x['id']]=c
# The precise printed fragments are compiled after dependency expansion.
def expand(i,seen):
    if i in seen:return ''
    seen.add(i)
    return ''.join(expand(j,seen) for j in deps.get(i,[]))+snippets[i]+'\n'
check_dir=ROOT/'tests/revised/printed';check_dir.mkdir(exist_ok=True)
def compile_print(i):
    p=check_dir/(book[i]['key']+'.cpp')
    p.write_text('#include <bits/stdc++.h>\n#include <ext/pb_ds/assoc_container.hpp>\n#include <ext/pb_ds/tree_policy.hpp>\nusing namespace std;\nusing i64 = long long;\n'+expand(i,set()),encoding='utf-8')
    r=subprocess.run(['D:/msys2/mingw64/bin/g++.exe','-std=gnu++17','-fsyntax-only',str(p)],capture_output=True,text=True,encoding='utf-8',errors='replace')
    return dict(id=i,ok=r.returncode==0,log=r.stderr)
with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:print_checks=list(pool.map(compile_print,deps))
(ROOT/'tests/revised/printed.json').write_text(json.dumps(print_checks,ensure_ascii=False,indent=2),encoding='utf-8')
for r in print_checks:
    if not r['ok']:print(r['id'],r['log'])
assert all(x['ok'] for x in print_checks),'Printed dependencies do not compile'

class Handbook(BaseDocTemplate):
    def __init__(self,p):
        super().__init__(str(p),pagesize=A4,leftMargin=17*mm,rightMargin=17*mm,topMargin=17*mm,bottomMargin=17*mm,
          title='算法竞赛模板 · GNU++17 修订打印版',author='个人竞赛模板修订',pageCompression=1)
        frame=Frame(self.leftMargin,self.bottomMargin,self.width,self.height,id='normal',leftPadding=0,rightPadding=0,topPadding=0,bottomPadding=0)
        self.addPageTemplates(PageTemplate(id='normal',frames=frame,onPageEnd=self.end_page))
        self.current='';self.pages={};self.total=None
    def beforeDocument(self):self.current='';self.pages={}
    def afterFlowable(self,f):
        if hasattr(f,'chapter'):self.current=f.chapter
        if hasattr(f,'bookmark'):
            key=f.bookmark;title=f.getPlainText();self.canv.bookmarkPage(key)
            self.canv.addOutlineEntry(title,key,level=f.level,closed=False)
            self.notify('TOCEntry',(f.level,html.escape(title),self.page,key))
            if key.startswith('id'):self.pages[int(key[2:])]=self.page
    def end_page(self,c,d):
        w,h=A4;c.saveState()
        if d.page>1:
            c.setFont('CN',8.2);c.setFillColor(colors.HexColor('#444444'))
            c.drawString(d.leftMargin,h-11*mm,'算法竞赛模板 · '+d.current)
            c.setStrokeColor(colors.HexColor('#AAAAAA'));c.setLineWidth(.35)
            c.line(d.leftMargin,h-13*mm,w-d.rightMargin,h-13*mm)
        c.setFont('CN',8);c.setFillColor(colors.HexColor('#555555'))
        c.drawString(d.leftMargin,10*mm,'GNU++17  ·  2026-10-02')
        c.setFont('CNB',9);c.drawCentredString(w/2,10*mm,str(d.page))
        c.restoreState()

def heading(title,key,level=1,chapter=None):
    f=para(title,'chapter' if level==0 else 'heading');f.bookmark=key;f.level=level
    if chapter:f.chapter=chapter
    return f

story=[]
story+=[Spacer(1,35*mm),para('算法竞赛模板','cover'),para('GNU++17 修订打印版','chapter'),Spacer(1,5*mm)]
for t in ['完整模板 · 使用说明 · 页码目录','按原资料全部 163 个条目复核，正文包含 104 份代码模板。','代码使用空格、四空格缩进与简短常用命名；无 bit_width / optional。','困难模板配可运行例子，题意相关空框架改为条件与公式速查。']:
    story.append(para(t))
story+=[Spacer(1,16*mm),para('版本日期：2026-10-02','sub'),para('先读下一页的下标、区间和依赖约定。','body'),PageBreak()]
f=para('比赛前与使用时','chapter');f.chapter='使用约定';story.append(f)
guide=[
 '页码：本册全部页面连续编号，包含封面和目录；目录页码就是阅读器/打印纸的实际页码。电子版目录与书签可点击。',
 '编译：GNU++17，#include <bits/stdc++.h>，using namespace std，using i64 = long long。结构化绑定和普通 lambda 可以使用；不依赖 C++20。打印主体省略重复头文件，PBDS 保留专用 include。',
 '下标：数组/普通图多为1-based；Dinic、MCF、BoundFlow 的顶点为0-based；XOR MST、三维偏序、整体二分答案编号为0-based。模板旁说明优先，不能凭习惯混用。',
 '区间：多数接口为闭区间 [l,r]；LCA 的 tin/tout、HLD 的 in/out 是半开子树区间，DSU on Tree 则是闭区间。接线段树时按说明转换。',
 '类型与范围：int 存点/下标，i64 存常见权值，乘法大于64位先转 i128。有限距离和、流量、费用、容量总和按各模板说明控制；INF 是哨兵，不能当普通数直接加减。',
 '复制：code/ 中每份 hpp 是独立完整模板；不同章节可能复用同名类型，按题目挑选并合并必要定义。正文为省纸只打印一次基础依赖，明确写出其编号；调用例子还需该条模板主体。',
 '使用难板：先看前提与接口，再看完整调用例子。先运行例子确认理解，再改 Info/Tag/Policy、函数或题意转移；更改后用小数据暴力对照。',
 '验证范围：104份独立编译，全部有边界/固定种子对照检查；40个示例（含3个 Min_25 改法）及20万点链检查通过。测试不等于形式化证明，浮点精度、随机算法耗时和题目范围仍以注明条件为准。',
 '文件：原157页 PDF 保留；source/算法竞赛模板_完整源稿.md 是可编辑全文；code/ 是模板，examples/ 是调用例子，tests/revised/ 与复核记录保存验证依据。'
]
for t in guide:story.append(para(t))
story.append(PageBreak())
f=para('目录','chapter');f.chapter='目录';story.append(f)
story.append(para('正文编号用于交叉引用；“速查”只保留有用的条件与公式，不提供题意未定义的空代码。','small'))
toc=TableOfContents(tableStyle=TableStyle([('TOPPADDING',(0,0),(-1,-1),1),('BOTTOMPADDING',(0,0),(-1,-1),1),('LEFTPADDING',(0,0),(-1,-1),0),('RIGHTPADDING',(0,0),(-1,-1),0)]));toc.levelStyles=[styles['toc0'],styles['toc1']];toc.dotsMinLevel=1
story+=[toc,PageBreak()]
cur=None;sec=0
for x in book:
    if not x['print']:continue
    ch=x['chapter']
    if ch!=cur:
        if cur is not None:story.append(PageBreak())
        cur=ch;sec=0;story.append(heading(ch,'chapter'+ch.split('.')[0],0,ch))
    sec+=1;x['number']=ch.split('.')[0]+'.'+str(sec)
    title=x['number']+' '+x['title']+(' 〔速查〕' if not x['code'] else '')
    story.append(heading(title,'id'+str(x['id'])))
    for t in x['notes']:story.append(para(t))
    if x['id'] in deps:
        terms=[]
        for i in deps[x['id']]:
            ref=book[i];terms.append(f'<link href="#id{i}" color="#222222">{ref["number"]} {html.escape(ref["title"])}</link>')
        story.append(Paragraph('主体依赖：'+ '；'.join(terms)+'。先复制这些基础定义，再复制下列代码。',styles['small']))
    if x['code']:story.append(CodeBlock(snippets[x['id']],x['number']+' '+x['title']+' · 主体'))
    for ex in x['examples']:
        story.append(para(ex['title'],'sub'))
        if ex.get('deps'):
            ids=[y for y in book if y['code'] in ex['deps']]
            story.append(para('例子还需要：'+'；'.join(y['number']+' '+y['title'] for y in ids)+'。','small'))
        story.append(CodeBlock(ex['code'],x['number']+' · '+ex['title']))
    story.append(Spacer(1,6))
story.append(PageBreak())
f=para('复核与参考','chapter');f.chapter='复核与参考';story.append(f)
for t in [
 '本版逐项重写了说明，使下标、区间、返回值与实际代码一致；通用模板保留完整实现，12个较窄的题意相关条目移出打印正文，但修订后的内容仍在完整源稿和逐项记录中。',
 '修正包括：GNU++17不兼容接口、欧拉路仅框架、朴素匹配、SAM次数与clone约定、深链递归、流的自环反向编号、上下界流的人工边处理、FPS截断混叠、空串Z、Manacher哨兵冲突、凸包重复点、线性基“无答案”值冲突、几何整数乘法宽度。',
 '运行日志与源码：tests/revised/compile.json、verification.json、examples.json、printed.json。固定随机种子712367；暴力参照包括枚举匹配/流/生成树/子集，数组直接维护，朴素字符串匹配与几何枚举。',
 '主要参考的是原资料与下列维护者文档，用于核对算法条件；此册代码与教程已按本地接口重新整理。查阅日期2026-10-02。'
]:story.append(para(t))
refs=[('最小生成树 / Boruvka','https://oi-wiki.org/graph/mst/'),('差分约束','https://oi-wiki.org/graph/diff-constraints/'),('二分图匹配','https://oi-wiki.org/graph/graph-matching/bigraph-match/'),('后缀自动机','https://oi-wiki.org/string/sam/'),('杜教筛','https://oi-wiki.org/math/number-theory/hyperbola/'),('Min_25 筛','https://oi-wiki.org/math/number-theory/min-25/')]
for title,url in refs:story.append(Paragraph(f'OI Wiki · {html.escape(title)}<br/><link href="{url}">{url}</link>',styles['small']))
pdf=OUT/'算法竞赛模板_GNU17_修订打印版.pdf'
doc=Handbook(pdf);doc.multiBuild(story,maxPasses=5)
for x in book:x['page']=doc.pages.get(x['id'])
(ROOT/'source/page_index.json').write_text(json.dumps([{k:x.get(k) for k in ['id','number','title','page','print']} for x in book],ensure_ascii=False,indent=2),encoding='utf-8')
(ROOT/'source/handbook.json').write_text(json.dumps(book,ensure_ascii=False,indent=2),encoding='utf-8')
(ROOT/'source/print_code.json').write_text(json.dumps(snippets,ensure_ascii=False,indent=2),encoding='utf-8')
print('PDF',pdf,'PAGES',doc.page)
