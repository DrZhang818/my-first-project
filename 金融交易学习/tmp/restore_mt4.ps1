param(
  [string]$DataDir = 'C:\Users\31435\AppData\Roaming\MetaQuotes\Terminal\E3B36FCC3E1C00B447F04224409C4ECA',
  [string]$BackupRoot = 'D:\Programme\GitCode\金融交易学习\output\mt4_backup',
  [string]$Report = 'D:\Programme\GitCode\金融交易学习\output\mt4_backup\restore_report.txt',
  [int]$TimeoutMinutes = 20
)

$gbk = [System.Text.Encoding]::GetEncoding(936)
$log = New-Object System.Collections.Generic.List[string]

function Add-Log([string]$m) {
  $line = (Get-Date -Format 'HH:mm:ss') + '  ' + $m
  $log.Add($line)
  Write-Output $line
}

Add-Log "waiting for MetaTrader 4 to close (timeout ${TimeoutMinutes}m) ..."
$deadline = (Get-Date).AddMinutes($TimeoutMinutes)
while ((Get-Process terminal -ErrorAction SilentlyContinue) -and ((Get-Date) -lt $deadline)) {
  Start-Sleep -Seconds 2
}

if (Get-Process terminal -ErrorAction SilentlyContinue) {
  Add-Log 'TIMEOUT: MetaTrader 4 is still running - nothing changed.'
} else {
  Start-Sleep -Seconds 3
  Add-Log 'MetaTrader 4 closed - applying restore.'

  $stamp = Get-Date -Format 'yyyyMMdd-HHmmss'
  $backup = Join-Path $BackupRoot $stamp
  New-Item -ItemType Directory -Force -Path (Join-Path $backup 'config') | Out-Null
  New-Item -ItemType Directory -Force -Path (Join-Path $backup 'profiles\default') | Out-Null
  Copy-Item (Join-Path $DataDir 'config\terminal.ini') (Join-Path $backup 'config\terminal.ini') -Force
  Copy-Item (Join-Path $DataDir 'profiles\default\*.chr') (Join-Path $backup 'profiles\default\') -Force
  Add-Log "backup written to $backup"

  $iniPath = Join-Path $DataDir 'config\terminal.ini'
  $ini = [System.IO.File]::ReadAllText($iniPath, $gbk)
  $before = $ini
  $ini = [regex]::Replace($ini, '(?m)^VirtualMigrationFlag=1\s*$', 'VirtualMigrationFlag=0')
  $ini = [regex]::Replace($ini, '(?m)^(Expert - .+?)=1\s*$', '$1=2')
  if ($ini -ne $before) {
    [System.IO.File]::WriteAllText($iniPath, $ini, $gbk)
    Add-Log 'terminal.ini: VirtualMigrationFlag -> 0, per-EA live trading -> 2'
  } else {
    Add-Log 'terminal.ini: no change needed'
  }

  $patched = 0
  Get-ChildItem (Join-Path $DataDir 'profiles\default\*.chr') | ForEach-Object {
    $text = [System.IO.File]::ReadAllText($_.FullName, $gbk)
    $new = [regex]::Replace($text, '(?m)^flags=279\s*$', 'flags=791')
    if ($new -ne $text) {
      [System.IO.File]::WriteAllText($_.FullName, $new, $gbk)
      $patched++
      Add-Log ("chart patched: " + $_.Name + " (expert flags 279 -> 791)")
    }
  }
  if ($patched -eq 0) { Add-Log 'no chart needed patching (no flags=279 found)' }

  Add-Log 'DONE - start MetaTrader 4 again.'
}

New-Item -ItemType Directory -Force -Path (Split-Path $Report) | Out-Null
$log | Set-Content -Path $Report -Encoding UTF8
Add-Log "report: $Report"
