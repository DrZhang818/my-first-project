from pathlib import Path
import json,re,subprocess,concurrent.futures
import pdfplumber
from pypdf import PdfReader
from PIL import Image,ImageDraw,ImageFont
ROOT=Path(__file__).resolve().parents[1];OUT=ROOT/'tmp/pdfs';OUT.mkdir(parents=True,exist_ok=True)
PDF=ROOT/'output/pdf/算法竞赛模板_GNU17_修订打印版.pdf'
book=json.loads((ROOT/'source/handbook.json').read_text(encoding='utf-8'))
issues=[];pages=[]
norm=lambda s:re.sub(r'\s+','',s)
with pdfplumber.open(PDF) as doc:
    for k,p in enumerate(doc.pages,1):
        text=p.extract_text() or '';pages.append(text)
        if abs(p.width-595.2756)>.1 or abs(p.height-841.8898)>.1:issues.append(['size',k])
        foot=[c for c in p.chars if c['top']>p.height-38]
        if str(k) not in ''.join(c['text'] for c in foot):issues.append(['footer',k])
        for c in p.chars:
            if c['x0']<44 or c['x1']>p.width-44 or c['top']<21 or c['bottom']>p.height-18:
                issues.append(['bounds',k,c['text'],[c['x0'],c['top'],c['x1'],c['bottom']]])
        if not text.strip():issues.append(['empty',k])
        if '\ufffd' in text or '\x00' in text:issues.append(['glyph',k])
    for x in book:
        if x['print'] and norm(x['number']+' '+x['title']) not in norm(pages[x['page']-1]):issues.append(['index',x['id'],x['page']])
reader=PdfReader(PDF)
def outlines(a):return sum(outlines(x) if isinstance(x,list) else 1 for x in a)
ann=sum(len(p.get('/Annots',[])) for p in reader.pages)
report=dict(pages=len(pages),bookmarks=outlines(reader.outline),links=ann,issues=issues,
    checked='Every page: A4, footer, glyph extraction, text bounding boxes; all 151 section start pages; rendering all pages and selected pages at 140 dpi.')
assert not issues,issues[:30]
assert report['bookmarks']==162,report
(ROOT/'tests/revised/pdf_qa.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
# Render every page, then contact sheets for full-document layout inspection.
subprocess.run(['pdftoppm','-r','75','-png',str(PDF),str(OUT/'all')],check=True,capture_output=True)
imgs=sorted((p for p in OUT.glob('all-*.png') if int(p.stem.split('-')[-1])<=len(pages)),key=lambda p:int(p.stem.split('-')[-1]))
assert len(imgs)==len(pages),(len(imgs),len(pages))
font=ImageFont.truetype('C:/Windows/Fonts/consola.ttf',14)
for start in range(0,len(imgs),24):
    sheet=Image.new('RGB',(1080,1120),'#e5e5e5');draw=ImageDraw.Draw(sheet)
    for i,p in enumerate(imgs[start:start+24]):
        im=Image.open(p).convert('RGB');im.thumbnail((172,244));x=(i%6)*180+4;y=(i//6)*280+25
        sheet.paste(im,(x,y));draw.text((x,y-19),str(start+i+1),font=font,fill='black')
    sheet.save(OUT/f'contact_{start//24+1}.png')
selected={1,2,3,len(pages)}
for i in (7,8,32,36,45,53,56,91,92,102,112,125,131):
    selected.add(book[i]['page']);selected.add(min(len(pages),book[i]['page']+1))
def render(k):subprocess.run(['pdftoppm','-f',str(k),'-l',str(k),'-r','140','-png','-singlefile',str(PDF),str(OUT/f'final_{k}')],check=True,capture_output=True)
with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:list(pool.map(render,sorted(selected)))
print('PDF QA',json.dumps(report,ensure_ascii=False));print('Rendered',len(imgs),'pages and',len(selected),'full-size samples')
