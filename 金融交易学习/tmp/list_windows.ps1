param([string]$ProcessName = 'terminal')

$sig = @'
using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.InteropServices;
public class WinEnum {
  [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
  [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern bool IsIconic(IntPtr h);
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
  public delegate bool EnumProc(IntPtr h, IntPtr l);
  public static List<string> List(uint target) {
    var res = new List<string>();
    EnumWindows((h, l) => {
      uint pid; GetWindowThreadProcessId(h, out pid);
      if (pid != target) return true;
      var t = new StringBuilder(256); GetWindowText(h, t, 256);
      var c = new StringBuilder(256); GetClassName(h, c, 256);
      RECT r; GetWindowRect(h, out r);
      res.Add(string.Format("hwnd={0} visible={1} iconic={2} rect={3},{4},{5},{6} class={7} title={8}",
        h, IsWindowVisible(h), IsIconic(h), r.Left, r.Top, r.Right, r.Bottom, c, t));
      return true;
    }, IntPtr.Zero);
    return res;
  }
}
'@

if (-not ('WinEnum' -as [type])) { Add-Type -TypeDefinition $sig }

foreach ($p in Get-Process $ProcessName -ErrorAction Stop) {
  Write-Output ("--- " + $p.ProcessName + " pid=" + $p.Id)
  [WinEnum]::List([uint32]$p.Id) | ForEach-Object { Write-Output $_ }
}
