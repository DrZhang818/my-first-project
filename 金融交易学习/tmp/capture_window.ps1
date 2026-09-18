param(
  [int]$ProcessId = 0,
  [string]$Out = 'output\captures\window.png'
)

Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms

$signature = @'
using System;
using System.Runtime.InteropServices;
public class WinCap {
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hWnd, out RECT r);
  [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr hWnd, IntPtr hdc, uint flags);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr hWnd);
}
'@

if (-not ('WinCap' -as [type])) { Add-Type -TypeDefinition $signature }

$proc = if ($ProcessId -gt 0) { Get-Process -Id $ProcessId } else { Get-Process terminal -ErrorAction Stop | Select-Object -First 1 }
$h = $proc.MainWindowHandle
if ($h -eq 0) { throw "no main window handle for $($proc.ProcessName)" }
if (-not [WinCap]::IsWindowVisible($h)) { throw "window not visible: $($proc.MainWindowTitle)" }

$rect = New-Object WinCap+RECT
[void][WinCap]::GetWindowRect($h, [ref]$rect)
$w = $rect.Right - $rect.Left
$ht = $rect.Bottom - $rect.Top
if ($w -le 0 -or $ht -le 0) { throw "bad window rect $w x $ht" }

$bmp = New-Object System.Drawing.Bitmap $w, $ht
$gfx = [System.Drawing.Graphics]::FromImage($bmp)
$hdc = $gfx.GetHdc()
$ok = [WinCap]::PrintWindow($h, $hdc, 2)
$gfx.ReleaseHdc($hdc)
$gfx.Dispose()

$target = Join-Path (Get-Location) $Out
New-Item -ItemType Directory -Force -Path (Split-Path $target) | Out-Null
$bmp.Save($target, [System.Drawing.Imaging.ImageFormat]::Png)
$bmp.Dispose()
Write-Output ("pid=" + $proc.Id + " title=" + $proc.MainWindowTitle)
Write-Output ("rect=" + $w + "x" + $ht + " printwindow=" + $ok)
Write-Output ("saved=" + $target)
