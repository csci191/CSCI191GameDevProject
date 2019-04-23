#include "loadShader.h"
using namespace std;
#include<iostream>

loadShader::loadShader()
{
    //ctor
}

loadShader::~loadShader()
{
    //dtor
    cleanUp();
}

void loadShader::loadFile(char* FileName, string& str)
{
    char tmp[1024];
    ifstream in(FileName);
    if(!in.eof())
    {
        cout << "File cannot be opened" << endl;
        return;
    }

    while(!in.eof())
    {
        in.getline(tmp,1024);
        str += tmp;
        str +='\n';
    }
    cout << str << endl;
}

unsigned int loadShader::LoadShader(string& source, unsigned int mode)
{
    unsigned int id;
    const char* csource;
    char error[1024];

    id =glCreateShader(mode);
    csource = source.c_str();
    glShaderSource(id,1,&csource, NULL);
    glGetShaderInfoLog(id,1024,NULL, error);
    cout << "Compile Status \n" << error << endl;

    return id;
}

void loadShader::initShader(char*VfileName, char* FfileName)
{
    string source;
    loadFile(VfileName, source);
    vs = LoadShader(source, GL_VERTEX_SHADER);
    source = "";

    loadFile(FfileName,source);
    fs = LoadShader(source, GL_FRAGMENT_SHADER);
    program = glCreateProgram();

    glAttachShader(program,vs);
    glAttachShader(program,fs);

    glLinkProgram(program);

}

void loadShader::cleanUp()
{
    glDetachShader(program,vs);
    glDetachShader(program,fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
    glDeleteProgram(program);
}
