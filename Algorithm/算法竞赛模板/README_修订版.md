# 修订算法竞赛打印模板

最终打印文件：**output/pdf/算法竞赛模板_GNU17_修订打印版.pdf**。

* 104份GNU++17完整模板；有空格、4空格缩进与简短竞赛命名。
* 40份使用示例（含Min_25的φ/τ/μ改法），可独立编译运行。
* 原资料163条逐项复核，12个窄题意条目移出正文，仍保存在完整源稿。
* 连续页码、可点击目录/书签、跨页代码续标；实际打印时用A4、100%原尺寸。

## 从哪里开始

`source/算法竞赛模板_完整源稿.md`：全部说明、完整代码与示例，可直接编辑。

`code/`：独立模板；`examples/`：调用程序，包含必要头文件依赖。

`source/逐项复核与验证记录.md`：逐条处理和实测依据。

`Algorithm_Handbook_Print.pdf`：原157页文件，保留原样。

## 当前验证

104/104独立编译；6/6暴力/边界对照组（1,553,411次CHECK）；41/41示例与链检查；11/11正文依赖展开编译。

适用环境GNU++17。算法的字符集、范围、单调性、浮点精度等前提写在各条旁；测试不是形式化证明。

## 更新与重建

日常直接编辑 `code/*.hpp`、`source/handbook.json`、`examples/*.cpp`，再构建PDF。格式配置在本目录 `.clang-format`。

```powershell
python rebuild/format_code.py
python rebuild/check_compile.py
python rebuild/verify.py
python rebuild/build_pdf.py
python rebuild/publish_sources.py
python rebuild/qa_pdf.py
```

PDF需要reportlab；QA还用pdfplumber/pypdf/Pillow与Poppler。测试脚本使用当前机器 `D:/msys2/mingw64/bin/g++.exe`，换机器改该路径。clang-format当前在rebuild/tools/。

`recover.py`、`prepare.py`、`enrich.py`、`tutorials.py`、`extra_checks.py`是从原PDF重建本次修订的脚本；**不要在日常手改后随意运行prepare/enrich/tutorials，它们会重新生成对应内容并覆盖编辑。** 若要从恢复材料重新生成，应按这个顺序运行，再进行格式、验证、PDF与QA。

复核记录、恢复JSON与全部可编辑源文件均保留，后续无需再从PDF抽取。
