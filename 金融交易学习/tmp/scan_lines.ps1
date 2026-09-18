param(
  [Parameter(Mandatory=$true)][string]$In,
  [int]$X0 = 600,
  [int]$X1 = 1466,
  [int]$Y0 = 180,
  [int]$Y1 = 860,
  [int]$Threshold = 80
)

Add-Type -AssemblyName System.Drawing
$bmp = New-Object System.Drawing.Bitmap ((Resolve-Path $In).Path)
$rows = @()
for ($y = $Y0; $y -lt [Math]::Min($Y1, $bmp.Height); $y++) {
  $blue = 0; $red = 0; $other = 0
  for ($x = $X0; $x -lt [Math]::Min($X1, $bmp.Width); $x++) {
    $c = $bmp.GetPixel($x, $y)
    $max = [Math]::Max($c.R, [Math]::Max($c.G, $c.B))
    $min = [Math]::Min($c.R, [Math]::Min($c.G, $c.B))
    $sat = $max - $min
    if ($c.B -gt 90 -and $c.B -gt $c.R + 40 -and $c.B -gt $c.G + 40) { $blue++ }
    elseif ($c.R -gt 90 -and $c.R -gt $c.B + 40 -and $c.R -gt $c.G + 40) { $red++ }
    elseif ($sat -gt 60 -and -not ($c.G -ge $c.R -and $c.G -ge $c.B)) { $other++ }
  }
  if ($blue -ge $Threshold -or $red -ge $Threshold -or $other -ge $Threshold) {
    $rows += [pscustomobject]@{ Y = $y; Blue = $blue; Red = $red; Other = $other }
  }
}
$bmp.Dispose()
if ($rows.Count -eq 0) { Write-Output 'no long horizontal blue/red lines found' }
else { $rows | Format-Table -AutoSize | Out-String -Width 80 }
