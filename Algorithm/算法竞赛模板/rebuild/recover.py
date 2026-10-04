"""Recover editable text/code from the surviving print PDF. Original is untouched."""
from pathlib import Path
import json, re, logging
import pdfplumber
from pypdf import PdfReader

logging.getLogger('pdfminer').setLevel(logging.ERROR)
ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'rebuild'
src = ROOT / 'Algorithm_Handbook_Print.pdf'
reader = PdfReader(src)
bookmarks = []
def visit(items, level=0):
    for it in items:
        if isinstance(it, list): visit(it, level+1)
        else:
            bookmarks.append(dict(title=it['/Title'], page=reader.get_destination_page_number(it)+1,
                                  top=float(it.get('/Top',0)), level=level))
visit(reader.outline)
sections=[]
chapter=''
current=None
full=[]
with pdfplumber.open(src) as doc:
    for page_num, pg in enumerate(doc.pages,1):
        lines=pg.extract_text_lines(strip=False,return_chars=True)
        for line in lines:
            cs=sorted(line['chars'],key=lambda c:c['x0'])
            size=max(c['size'] for c in cs)
            text=line['text'].replace('\xa0',' ').rstrip()
            # Source's first three pages contain a prose-only table of contents.
            if page_num<3: continue
            if size>14:
                title=text.strip()
                if re.match(r'^\d+\.',title):
                    chapter=title
                    current=None
                elif chapter:
                    current=dict(title=title,chapter=chapter,old_page=page_num,blocks=[])
                    sections.append(current)
                continue
            if not current: continue
            iscode=size<9.2 and any('LucidaConsole' in c['fontname'] for c in cs)
            kind='code' if iscode else 'text'
            # Keep actual leading whitespace encoded in the PDF for source code.
            if iscode:
                unit=5.2875
                text=' ' * max(0,round((cs[0]['x0']-56.25)/unit))
                end=cs[0]['x0']
                for c in cs:
                    text+=' ' * max(0,round((c['x0']-end)/unit))+c['text']
                    end=c['x1']
                text=text.replace('\xa0',' ').rstrip()
            else: text=text.strip()
            if not current['blocks'] or current['blocks'][-1]['kind']!=kind:
                current['blocks'].append(dict(kind=kind,lines=[]))
            current['blocks'][-1]['lines'].append(text)
            full.append(text)
OUT.mkdir(parents=True,exist_ok=True)
(OUT/'recovered.json').write_text(json.dumps(sections,ensure_ascii=False,indent=2),encoding='utf-8')
(OUT/'original_outline.json').write_text(json.dumps(bookmarks,ensure_ascii=False,indent=2),encoding='utf-8')
(OUT/'recovered.txt').write_text('\n'.join(full),encoding='utf-8')
print('Recovered',len(sections),'sections;',sum(any(b['kind']=='code' for b in s['blocks']) for s in sections),'with code')
for i,s in enumerate(sections):
    print(i,s['title'],'p'+str(s['old_page']),sum(len(b['lines']) for b in s['blocks']))
