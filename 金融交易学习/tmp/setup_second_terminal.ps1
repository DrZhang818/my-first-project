$src = 'C:\Users\31435\AppData\Roaming\MetaQuotes\Terminal\E3B36FCC3E1C00B447F04224409C4ECA'
$dst = 'C:\Users\31435\AppData\Roaming\MetaQuotes\Terminal\50CA3DFB510CC5A8F28B48D1BF2A5702'
$backupRoot = 'D:\Programme\GitCode\金融交易学习\output\mt4_second_backup'
$gbk = [System.Text.Encoding]::GetEncoding(936)
$stamp = Get-Date -Format 'yyyyMMdd-HHmmss'
$backup = Join-Path $backupRoot $stamp

New-Item -ItemType Directory -Force -Path (Join-Path $backup 'config') | Out-Null
New-Item -ItemType Directory -Force -Path (Join-Path $backup 'profiles\default') | Out-Null

foreach ($f in 'terminal.ini','servers.ini') {
  $p = Join-Path $dst "config\$f"
  if (Test-Path $p) { Copy-Item $p (Join-Path $backup "config\$f") -Force }
}
Get-ChildItem (Join-Path $dst 'profiles\default\*') -ErrorAction SilentlyContinue |
  Copy-Item -Destination (Join-Path $backup 'profiles\default') -Force
Write-Output "backup: $backup"

Copy-Item (Join-Path $src 'config\servers.ini') (Join-Path $dst 'config\servers.ini') -Force
Write-Output 'server list copied (Exness-Real8 available)'

New-Item -ItemType Directory -Force -Path (Join-Path $dst 'MQL4\Experts') | Out-Null
New-Item -ItemType Directory -Force -Path (Join-Path $dst 'MQL4\Presets') | Out-Null
foreach ($f in 'TSO.ex4','Amazing31_Exness_Cent_Fix.ex4','Amazing31_Exness_Cent_Fix.mq4','AK47.ex4','Dark Venus.ex4','Joker.ex4') {
  $p = Join-Path $src "MQL4\Experts\$f"
  if (Test-Path $p) {
    Copy-Item $p (Join-Path $dst "MQL4\Experts\$f") -Force
    Write-Output "expert copied: $f"
  }
}
Get-ChildItem (Join-Path $src 'MQL4\Presets\*.set') -ErrorAction SilentlyContinue |
  Copy-Item -Destination (Join-Path $dst 'MQL4\Presets') -Force
Write-Output 'presets copied'

$chart = [System.IO.File]::ReadAllText((Join-Path $src 'profiles\default\chart01.chr'), $gbk)
$chart = [regex]::Replace($chart, '(?m)^flags=279\s*$', 'flags=791')

Get-ChildItem (Join-Path $dst 'profiles\default\chart*.CHR') -ErrorAction SilentlyContinue |
  Move-Item -Destination (Join-Path $backup 'profiles\default') -Force

[System.IO.File]::WriteAllText((Join-Path $dst 'profiles\default\chart01.CHR'), $chart, $gbk)
Write-Output 'chart installed: XAUUSDc M5 + TSO (live trading flag enabled)'
Write-Output 'DONE'
