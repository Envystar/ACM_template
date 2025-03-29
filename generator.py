import os
import mistune

CONTENT_PATH = 'contents.md'
OUTPUT_PATH = 'contents.tex'

def parse_markdown_file(file_path):
    with open(file_path, 'r', encoding='utf-8') as f:
        md_content = f.read()
    parser = mistune.create_markdown(renderer='ast')
    ast = parser(md_content)
    return ast

content = parse_markdown_file(CONTENT_PATH)

def genertate():
    """
        用于将markdown目录内容构建为tex内容
    """
    level = 0
    output_lines = []
    for node in content:
        if node['type'] == 'heading': #章节
            level = node['attrs']['level'] - 1
            title = node['children'][0]['raw']
            output_lines.append(f"\\{'sub' * level}section{{{title}}}")
        elif node['type'] == 'paragraph': #段
            for son in node['children']:
                if son['type'] == 'strong': #标题
                    title = son['children'][0]['raw']
                    tlevel = level + 1
                    output_lines.append(f"\\{'sub' * tlevel}section{{{title}}}")
                elif son['type'] == 'text': #路径
                    path = son['raw'].replace('\\', '/')
                    ext = os.path.splitext(path)[1]
                    if ext == '.cpp':
                        output_lines.append(f"\\lstinputlisting[style=cppstyle]{{{path}}}")
                    elif ext == '.tex':
                        # output_lines.append(f"\\begin{{small}}")
                        output_lines.append(f"\\input{{{path}}}")
                        # output_lines.append(f"\\end{{small}}")

    with open(OUTPUT_PATH, 'w', encoding='utf-8') as f:
        f.write('\n'.join(output_lines) + '\n')

if __name__ == '__main__':                  
    genertate()
