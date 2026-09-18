param(
  [Parameter(Mandatory=$true)][string]$Path,
  [int]$Tail = 40,
  [string]$Filter = ''
)

$stream = [System.IO.FileStream]::new($Path, [System.IO.FileMode]::Open, [System.IO.FileAccess]::Read, [System.IO.FileShare]::ReadWrite)
try {
  $bytes = New-Object byte[] $stream.Length
  $read = 0
  while ($read -lt $bytes.Length) {
    $n = $stream.Read($bytes, $read, $bytes.Length - $read)
    if ($n -le 0) { break }
    $read += $n
  }
} finally { $stream.Dispose() }

$encoding = [System.Text.Encoding]::GetEncoding(936)
if ($bytes.Length -ge 2 -and $bytes[0] -eq 0xFF -and $bytes[1] -eq 0xFE) {
  $encoding = [System.Text.Encoding]::Unicode
} elseif ($bytes.Length -ge 2 -and $bytes[0] -eq 0xFE -and $bytes[1] -eq 0xFF) {
  $encoding = [System.Text.Encoding]::BigEndianUnicode
} elseif ($bytes.Length -ge 2 -and $bytes[1] -eq 0 -and $bytes[0] -ne 0) {
  $encoding = [System.Text.Encoding]::Unicode
} elseif ($bytes.Length -ge 2 -and $bytes[0] -eq 0 -and $bytes[1] -ne 0) {
  $encoding = [System.Text.Encoding]::BigEndianUnicode
}

$text = $encoding.GetString($bytes)
$lines = $text -split "`r?`n"
Write-Output ("# encoding=" + $encoding.WebName + " lines=" + $lines.Count)

if ($Filter -ne '') {
  $matches = $lines | Where-Object { $_ -match $Filter }
  Write-Output ("# matched=" + $matches.Count)
  $matches | Select-Object -Last $Tail
} else {
  $lines | Select-Object -Last $Tail
}
