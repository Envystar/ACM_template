#include <bits/stdc++.h>

const std::string header_path = ".\\header.txt"; 
const std::string bottom_path = ".\\bottom.txt";
const std::string source_path = ".\\src";
const std::string output_path = ".\\templete.tex";
const std::string addtion_name = "7 Addition.tex";
const std::string fontsize = "small"; //注记文本大小

std::string readFileContent(const std::string& filePath) {  
    std::ifstream file(filePath);  
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());  
    return content;  
}  

int main() {
    
    freopen(output_path.c_str(), "w", stdout);
    
    auto find = [](auto self, const std::filesystem::path &path, int level) ->void {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {  
            
            std::string file_name = entry.path().stem().string(); //文件名/文件夹名，去后缀
            if(std::isdigit(file_name.front())) {
                file_name = file_name.substr(2);
            }
            std::string file_path = (entry.path().parent_path() / entry.path().stem()).string(); //文件/文件夹路径, 去后缀
            std::replace(file_path.begin(), file_path.end(), '\\', '/');
            if (std::filesystem::is_regular_file(entry)) {
                if(entry.path().extension() == ".tex") continue; 
                std::cout << "\\";
                for(int i = 1; i <= level; ++i) {
                    std::cout << "sub";
                }
                std::cout << "section{" << file_name << "}" << std::endl; //章节

                if(std::filesystem::exists(file_path + ".tex")) {
                    std::cout << "\\begin{" << fontsize << "}" << std::endl;  
                    std::cout << "\\input{" << file_path << ".tex" << "}" << std::endl; //注记
                    std::cout << "\\end{" << fontsize << "}" << std::endl;  
                }

                std::cout << "\\lstinputlisting[style=" << entry.path().extension().string().substr(1) 
                        << "style]{" << file_path << entry.path().extension().string() << "}" << std::endl;//文件 
            } else if (std::filesystem::is_directory(entry)) {  
                std::cout << "\\";
                for(int i = 1; i <= level; ++i) {
                    std::cout << "sub";
                }
                std::cout << "section{" << file_name << "}" << std::endl;  
                self(self, entry.path(), level + 1);
            }  
        } 
    };
    std::cout << readFileContent(header_path) << std::endl;
    find(find, source_path, 0);
    if(addtion_name != "") {
        std::string addtion_path = source_path + "\\" + addtion_name;
        std::cout << "\\begin{" << fontsize << "}" << std::endl;  
        std::replace(addtion_path.begin(), addtion_path.end(), '\\', '/');
        std::cout << "\\input{" << addtion_path << "}" << std::endl; //注记
        std::cout << "\\end{" << fontsize << "}" << std::endl; 
    }
    std::cout << readFileContent(bottom_path) << std::endl;
    return 0;
}