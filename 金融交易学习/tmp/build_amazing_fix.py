from pathlib import Path
import re

root = Path(r'D:\Programme\GitCode\金融交易学习')
source = Path(r'D:\Programme\GitCode\EA策略\amazing\Amazing3.1-去限制去垃圾代码_源码.mq4')
out = root / 'output' / 'Amazing_Exness_Cent'
out.mkdir(parents=True, exist_ok=True)
s = source.read_text(encoding='utf-16')
s = s.replace('#property version    "3.1"', '#property version    "3.11"')
helper = (root / 'tmp/amazing_broker_helpers.mqh').read_text(encoding='utf-8')
s = s.replace(' int init ()', helper + '\n int init ()', 1)
s = s.replace('  总_st_50 = WindowExpertName() ;', '  BrokerPrintSpecs();\n  总_st_50 = WindowExpertName() ;', 1)
s = s.replace(' int start ()\n {', ' int start ()\n {\n if(BrokerLossHalted) { lizong_7(0); Comment("Loss limit reached: EA paused until reinitialization"); return(0); }', 1)
assert 'if(BrokerLossHalted)' in s
# Consistent minimum distances in both initial placement and trailing calculations.
for name in ['FirstStep', 'MinDistance', 'TwoMinDistance']:
    s = re.sub(r'\b' + name + r' \* Point\(\)', f'BrokerDistance({name}) * Point()', s)
old = '子_in_8 + 子_in_9 >= Totals'
s = s.replace(old, '子_in_8 + 子_in_9 + 子_in_10 + 子_in_11 >= Totals')
s = s.replace('临_st_4 = "This EA has stop work ! ";',
              '临_st_4 = "Paused: " + BrokerBlockReason(子_in_8 + 子_in_9 + 子_in_10 + 子_in_11);\n  if(临_st_4=="Paused: ") 临_st_4+="Configured movement filter";\n  BrokerNote(临_st_4);')
# Wrapper checks fresh broker requirements and no longer uses the bypassable division by margin/lot.
for n in ['8', '9']:
    old = f'if ( ( ( 子_do_26 * 2.0<AccountFreeMargin() / MarketInfo(Symbol(),32) && 子_in_{n} > 0 ) || 总_bo_10 ) )'
    assert old in s
    s = s.replace(old, 'if ( 子_do_26 > 0 )')
pattern = r'OrderSend\(Symbol\(\),(OP_BUYSTOP|OP_SELLSTOP),子_do_26,子_do_25,总_in_22,0\.0,0\.0,"(SS|NN)",Magic,0,(Blue|Red)\)'
s, replacements = re.subn(pattern, r'BrokerSendPending(\1,子_do_26,子_do_25,"\2",\3)', s)
assert replacements == 4
# Only the wrapper emits failures, avoiding thousands of undiagnosable duplicate log entries.
s = s.replace('Print(Symbol() + "开单失败");', '// Detailed failure is logged by BrokerSendPending.')
for n in ['13', '14']:
    s = s.replace(f'OrderModify(子_in_{n},子_do_25,0.0,0.0,0,White)', f'BrokerModifyPending(子_in_{n},子_do_25)')
s = re.sub(r'Print\("Error ",GetLastError\(\),"   Order Modify (Buy|Sell)   OOP ",子_do_\d+,"->",子_do_25\);', '// Detailed failure is logged by BrokerModifyPending.', s)
s = s.replace('Print("Buy Loss ",子_do_4);', 'if(StopAfterLoss) BrokerLossHalted=true;\n  Print("Buy Loss ",子_do_4);')
# Initialize pre-existing branch/retry state flagged by the compiler.
for name in ['临_bo_128','临_bo_130','临_bo_145','临_bo_147']:
    s = re.sub(r'(bool\s+'+name+r')\s*;', r'\1=false;', s)
for name in ['临_in_47','子_in_2']:
    s = re.sub(r'(int\s+'+name+r')\s*;', r'\1=0;', s)
# The original label incorrectly calls raw points "pips".
s = s.replace('" pips"', '" points"')
target = out / 'Amazing31_Exness_Cent_Fix.mq4'
target.write_text(s, encoding='utf-16')

settings = dict(re.findall(r'^extern\s+(?:double|int|bool|string|opentime|ENUM_TIMEFRAMES)\s+(\w+)\s*=\s*([^;]+);', s, re.M))
settings = {k:v.strip().strip('"') for k,v in settings.items()}
settings.update({
    'FirstStep':'1000', 'MinDistance':'1500', 'TwoMinDistance':'1500',
    'StepTrallOrders':'200', 'Step':'3000', 'TwoStep':'3000',
    'OpenMode':'2', 'sleep':'60', 'NextTime':'300',
    'lot':'0.01', 'Maxlot':'0.01', 'PlusLot':'0', 'K_Lot':'1.0', 'DigitsLot':'2',
    'Totals':'4', 'MaxTotalLots':'0.04', 'MaxSpread':'400',
    'MaxLoss':'75', 'MaxLossCloseAll':'50', 'StopLoss':'150',
    'CloseAll':'5', 'Profit':'false', 'StopProfit':'5',
    'PendingFloorPoints':'1000', 'BrokerSafetyBufferPoints':'50',
    'TradeRetrySeconds':'10', 'StopAfterLoss':'true',
})
(out / 'XAUUSDc_USC_Diagnostic.set').write_text('\n'.join(f'{k}={v}' for k,v in settings.items())+'\n', encoding='ascii')
# Make a fresh attachment use the same explicitly documented diagnostic defaults.
for key, value in settings.items():
    pattern=r'(extern\s+(?:double|int|bool|opentime|ENUM_TIMEFRAMES)\s+'+re.escape(key)+r'\s*=\s*)[^;]+;'
    s=re.sub(pattern, lambda m:m.group(1)+value+';', s)
target.write_text(s,encoding='utf-16')
print(target)
print('Settings count:', len(settings))
print('Wrapped sends:', replacements)
print('Raw OrderSend calls remaining:', s.count('OrderSend('))
