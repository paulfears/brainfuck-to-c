#include <iostream>
#include <string>
#include <fstream>

std::string generate_code(std::string bf_code, int memory, bool debug = false){
  std::string c_code;
  c_code.append("#include <stdio.h>\n");
  c_code.append("int main(){\n");
  c_code.append("int memory[").append(std::to_string(memory)).append("];\n");
  c_code.append("int* current_pos = &memory[0];\n");
  c_code.append("int* now_position = current_pos;\n");
  for(int i = 0; i<bf_code.length(); i++){
    if(bf_code.at(i) == '+'){
      c_code.append("*current_pos +=1;\n");
    }
    if(bf_code.at(i) == '-'){
      c_code.append("*current_pos -=1;\n");
    }
    if(bf_code.at(i) == '>'){
      c_code.append("current_pos+=1;\n");
    }
    if(bf_code.at(i) == '<'){
      c_code.append("current_pos-=1;\n");
    }
    if(bf_code.at(i) == '.'){
      c_code.append("printf(\"%c\",(char)*current_pos);\n");
    }
    if(bf_code.at(i)==','){
      c_code.append("*current_pos = (int)getchar();\n");

    }
    if(bf_code.at(i) == '['){
      c_code.append("now_position = current_pos;\n");
      c_code.append("while(*now_position>0){\n");
    }
    if(bf_code.at(i) == ']'){
      c_code.append("now_position=current_pos;};\n");
    }
  }
  if(debug){
    c_code.append("for(int i = 0; i<").append(std::to_string(memory)).append("; i++){\n");
    c_code.append("printf(\"%i\", memory[i]);\n");
    c_code.append("}\n");
  }
  c_code.append("return 0;\n");
  c_code.append("}\n");
  return c_code;
}

std::string readfile(const char* filename){
  std::string data;
  char x[200];
  std::ifstream infile;
  infile.open(filename);
  while(infile>>x){
    data.append(x);
  }
  infile.close();
  return (std::string)data;
}
void write_string_to_file(std::string data, std::string filename){
  std::ofstream newfile;
  newfile.open(filename.c_str());
  newfile<<data;
}


int main(){
  std::cout<<"filename with bf code: ";
  std::string filename;
  std::cin>>filename;
  std::string code = readfile(filename.c_str()); 
  write_string_to_file(generate_code(code, 10000), "code.c");
  std::system("gcc -S code.c");
  std::cout<<"generating raw assembly"<<std::endl;
  std::system("gcc -o executeable_bf code.c");
  std::cout<<"running code"<<std::endl;
  std::system("./executeable_bf");

  return 0;
}
