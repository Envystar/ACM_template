# 算法竞赛模板生成

## 如何使用：

1. 创建代码文件夹，如本仓库中的 `src` 文件夹。

2. 运行 `TeXGenerator.exe` ，选中代码文件夹，调整文件结构，导出 `Tex` 到根目录，命名为 `contents.tex` 。

3. 编译 `template.tex`，在此之前可以对其修改来自定义封面。

   编译命令如下，需要用 `Tex` 环境：

   ```bash
   latexmk -xelatex -synctex=1 -interaction=nonstopmode template.tex
   ```

   清空缓存文件，可以用以下命令：

   ```bash
   latexmk -c
   ```



说明：

本项目中 `TeXGenerator.py` 由 `grok` 编写，仅供参考。
