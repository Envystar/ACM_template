import sys
import os
from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QTreeWidget, QTreeWidgetItem, QTextEdit,
    QSplitter, QVBoxLayout, QHBoxLayout, QWidget, QPushButton, QFileDialog,
    QCheckBox, QHeaderView, QLabel, QAbstractItemView
)
from PyQt6.QtCore import Qt, QTimer
from PyQt6.QtGui import QDragEnterEvent, QDropEvent, QIcon

# Define common code extensions and their listing styles
CODE_EXTENSIONS = {
    '.c': 'cppstyle',
    '.h': 'cppstyle',
    '.cpp': 'cppstyle',
    '.hpp': 'cppstyle',
    '.py': 'pystyle'
}
TEX_EXT = '.tex'
SECTION_COMMANDS = ["\\section", "\\subsection", "\\subsubsection", "\\subsubsubsection"]

class CustomTreeWidget(QTreeWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.main_window = parent  # Reference to main window for updating preview

    def dropEvent(self, event: QDropEvent):
        drop_item = self.itemAt(event.position().toPoint())
        drop_indicator_position = self.dropIndicatorPosition()
        dragged_items = self.selectedItems()
        if not dragged_items:
            event.ignore()
            return

        dragged_item = dragged_items[0]
        dragged_data = dragged_item.data(0, Qt.ItemDataRole.UserRole)  # None 表示目录
        drop_data = drop_item.data(0, Qt.ItemDataRole.UserRole) if drop_item else None

        # 禁止任何东西拖到文件“里面”
        if drop_item and drop_data and drop_indicator_position == QAbstractItemView.DropIndicatorPosition.OnItem:
            event.ignore()
            return

        # 如果拖动的是目录，禁止放到文件里面
        if dragged_data is None and drop_item:
            if drop_data and drop_indicator_position == QAbstractItemView.DropIndicatorPosition.OnItem:
                event.ignore()
                return

        # 允许文件夹/文件在不同层级间移动（只要不是 OnItem 就行）
        super().dropEvent(event)
        self.main_window.update_preview()

class LatexGeneratorWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("TeX Generator")
        self.setGeometry(100, 100, 1200, 800)
        self.root_dir = ""
        
        # Top bar: Label and buttons with background
        top = QHBoxLayout()
        self.lbl_root = QLabel("根目录：<未选择>")
        self.lbl_root.setTextInteractionFlags(Qt.TextInteractionFlag.TextSelectableByMouse)
        
        btn_choose = QPushButton("选择目录")
        btn_choose.clicked.connect(self.browse_directory)
        
        btn_export = QPushButton("导出为 LaTeX")
        btn_export.clicked.connect(self.export_latex)
        
        top.addWidget(self.lbl_root, stretch=1)
        top.addWidget(btn_choose)
        top.addWidget(btn_export)
        
        top_widget = QWidget()
        top_widget.setLayout(top)
        top_widget.setFixedHeight(40)
        
        # Main splitter
        splitter = QSplitter(Qt.Orientation.Horizontal)
        
        # Left: Custom Tree widget for directory structure
        self.tree = CustomTreeWidget(self)
        self.tree.setHeaderLabels(["目录", "代码文件", "Tex文件"])
        header = self.tree.header()
        header.setStretchLastSection(False)
        header.setSectionResizeMode(0, QHeaderView.ResizeMode.Stretch)
        header.setSectionResizeMode(1, QHeaderView.ResizeMode.Fixed)
        header.setSectionResizeMode(2, QHeaderView.ResizeMode.Fixed)
        header.resizeSection(1, 100)
        header.resizeSection(2, 100)
        self.tree.setColumnCount(3)
        self.tree.setDragEnabled(True)
        self.tree.setDropIndicatorShown(True)
        self.tree.setDragDropMode(QTreeWidget.DragDropMode.InternalMove)
        self.tree.setAcceptDrops(True)
        self.tree.itemChanged.connect(self.update_preview)
        # Set icons and styles
        self.tree.setStyleSheet("""
            QTreeWidget::item { padding: 2px; }
            QTreeWidget::item:selected { background-color: #4a90e2; }
        """)
        
        # Right: LaTeX preview
        self.preview = QTextEdit()
        self.preview.setReadOnly(True)
        
        splitter.addWidget(self.tree)
        splitter.addWidget(self.preview)
        splitter.setSizes([600, 600])
        
        # Central widget
        central_widget = QWidget()
        main_layout = QVBoxLayout()
        main_layout.addWidget(top_widget)
        main_layout.addWidget(splitter)
        central_widget.setLayout(main_layout)
        self.setCentralWidget(central_widget)
        
        # Enable drag and drop for the whole window
        self.setAcceptDrops(True)

    def browse_directory(self):
        directory = QFileDialog.getExistingDirectory(self, "选择目录")
        if directory:
            self.set_root_directory(directory)

    def set_root_directory(self, directory):
        self.root_dir = directory
        self.lbl_root.setText(f"根目录：{directory}")
        self.load_directory_structure()

    def dragEnterEvent(self, event: QDragEnterEvent):
        if event.mimeData().hasUrls():
            event.acceptProposedAction()

    def dropEvent(self, event: QDropEvent):
        urls = event.mimeData().urls()
        if urls and urls[0].isLocalFile():
            path = urls[0].toLocalFile()
            if os.path.isdir(path):
                self.set_root_directory(path)
                event.acceptProposedAction()

    def load_directory_structure(self):
        self.tree.clear()
        if not self.root_dir:
            return
        items = []
        for entry in sorted(os.scandir(self.root_dir), key=lambda e: e.name):
            if entry.is_dir():
                dir_item = QTreeWidgetItem(self.tree, [entry.name])
                dir_item.setIcon(0, QIcon.fromTheme("folder"))
                self._populate_tree(entry.path, dir_item)
                if dir_item.childCount() > 0:
                    items.append(dir_item)
            else:
                base, ext = os.path.splitext(entry.name)
                if ext.lower() in CODE_EXTENSIONS:
                    tex_path = os.path.join(self.root_dir, base + TEX_EXT)
                    has_tex = os.path.exists(tex_path)
                    item = QTreeWidgetItem(self.tree, [entry.name])
                    item.setIcon(0, QIcon.fromTheme("text-x-script"))
                    item.setData(0, Qt.ItemDataRole.UserRole, {'type': 'code', 'path': entry.path, 'base': base, 'ext': ext, 'has_tex': has_tex})
                    item.setCheckState(1, Qt.CheckState.Checked)
                    if has_tex:
                        item.setCheckState(2, Qt.CheckState.Checked)
                    else:
                        item.setText(2, "")
                    items.append(item)
                elif ext.lower() == TEX_EXT:
                    code_found = False
                    for code_ext in CODE_EXTENSIONS:
                        code_path = os.path.join(self.root_dir, base + code_ext)
                        if os.path.exists(code_path):
                            code_found = True
                            break
                    if not code_found:
                        item = QTreeWidgetItem(self.tree, [entry.name])
                        item.setIcon(0, QIcon.fromTheme("text-x-tex"))
                        item.setData(0, Qt.ItemDataRole.UserRole, {'type': 'tex', 'path': entry.path, 'base': base})
                        item.setText(1, "")
                        item.setCheckState(2, Qt.CheckState.Checked)
                        items.append(item)
        
        for item in items:
            self.tree.addTopLevelItem(item)
        self.update_preview()

    def _populate_tree(self, path, parent_item):
        items = []
        for entry in sorted(os.scandir(path), key=lambda e: e.name):
            if entry.is_dir():
                dir_item = QTreeWidgetItem(parent_item, [entry.name])
                dir_item.setIcon(0, QIcon.fromTheme("folder"))
                self._populate_tree(entry.path, dir_item)
                if dir_item.childCount() > 0:
                    items.append(dir_item)
            else:
                base, ext = os.path.splitext(entry.name)
                if ext.lower() in CODE_EXTENSIONS:
                    tex_path = os.path.join(path, base + TEX_EXT)
                    has_tex = os.path.exists(tex_path)
                    item = QTreeWidgetItem(parent_item, [entry.name])
                    item.setIcon(0, QIcon.fromTheme("text-x-script"))
                    item.setData(0, Qt.ItemDataRole.UserRole, {'type': 'code', 'path': entry.path, 'base': base, 'ext': ext, 'has_tex': has_tex})
                    item.setCheckState(1, Qt.CheckState.Checked)
                    if has_tex:
                        item.setCheckState(2, Qt.CheckState.Checked)
                    else:
                        item.setText(2, "")
                    items.append(item)
                elif ext.lower() == TEX_EXT:
                    code_found = False
                    for code_ext in CODE_EXTENSIONS:
                        code_path = os.path.join(path, base + code_ext)
                        if os.path.exists(code_path):
                            code_found = True
                            break
                    if not code_found:
                        item = QTreeWidgetItem(parent_item, [entry.name])
                        item.setIcon(0, QIcon.fromTheme("text-x-tex"))
                        item.setData(0, Qt.ItemDataRole.UserRole, {'type': 'tex', 'path': entry.path, 'base': base})
                        item.setText(1, "")
                        item.setCheckState(2, Qt.CheckState.Checked)
                        items.append(item)
        
        for item in items:
            parent_item.addChild(item)

    def update_preview(self):
        scrollbar = self.preview.verticalScrollBar()
        pos = scrollbar.value()   # 保存当前位置
        latex = self.generate_latex()
        self.preview.setPlainText(latex)
        # 延迟恢复滚动条位置，避免跳到顶部
        QTimer.singleShot(0, lambda: scrollbar.setValue(pos))

    def export_latex(self):
        if not self.root_dir:
            return
        file_path, _ = QFileDialog.getSaveFileName(self, "导出 LaTeX 文件", "", "LaTeX 文件 (*.tex)")
        if file_path:
            with open(file_path, 'w', encoding='utf-8') as f:
                f.write(self.generate_latex())

    def generate_latex(self):
        if self.tree.topLevelItemCount() == 0:
            return ""
        lines = []
        for i in range(self.tree.topLevelItemCount()):
            self._generate_latex_recursive(self.tree.topLevelItem(i), 0, lines, "")
        return "\n".join(lines)

    def _generate_latex_recursive(self, item, depth, lines, current_path):
        data = item.data(0, Qt.ItemDataRole.UserRole)
        if data:
            base = data['base']
            section_name = base.replace('_', ' ')
            section_cmd = SECTION_COMMANDS[min(depth, len(SECTION_COMMANDS) - 1)]
            
            if data['type'] == 'code':
                if (item.checkState(2) == Qt.CheckState.Checked and data['has_tex']) or item.checkState(1) == Qt.CheckState.Checked:
                    lines.append(section_cmd + "{" + section_name + "}")
                if item.checkState(2) == Qt.CheckState.Checked and data['has_tex']:
                    # Use physical path for .tex file
                    tex_path = os.path.relpath(data['path'].replace(data['ext'], TEX_EXT), os.path.dirname(self.root_dir)).replace('\\', '/')
                    lines.append("\\input{" + tex_path + "}")
                if item.checkState(1) == Qt.CheckState.Checked:
                    # Use physical path for code file
                    code_path = os.path.relpath(data['path'], os.path.dirname(self.root_dir)).replace('\\', '/')
                    style = CODE_EXTENSIONS.get(data['ext'].lower(), 'codestyle')
                    lines.append("\\lstinputlisting[style=" + style + "]{" + code_path + "}")
            elif data['type'] == 'tex':
                if item.checkState(2) == Qt.CheckState.Checked:
                    # Use physical path for .tex file
                    lines.append(section_cmd + "{" + section_name + "}")
                    tex_path = os.path.relpath(data['path'], os.path.dirname(self.root_dir)).replace('\\', '/')
                    lines.append("\\input{" + tex_path + "}")
        else:
            section_cmd = SECTION_COMMANDS[min(depth, len(SECTION_COMMANDS) - 1)]
            dir_name = item.text(0).replace('_', ' ')
            lines.append(section_cmd + "{" + dir_name + "}")
            child_path = os.path.join(current_path, item.text(0)).replace('\\', '/')
            for i in range(item.childCount()):
                self._generate_latex_recursive(item.child(i), depth + 1, lines, child_path)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = LatexGeneratorWindow()
    window.show()
    sys.exit(app.exec())