#include<iostream>
#include <string>

class CHAR
{
private:
    char Content;
    int length;
public:
    CHAR(char s = '\0');
    ~CHAR(void);
    void setContent(char c);
    int getLength();
    char getContent();
};

CHAR::CHAR(char s)
{
    this->Content = s;
    this->length = 1;
    if (s == '\0')
        this->length = 0;
}


CHAR::~CHAR(void)
{
}
char CHAR::getContent(){
    return this->Content;
}
void CHAR::setContent(char c)
{
    this->Content = c;
    this->length = 1;
    if (c == '\0')
        this->length = 0;
}
int CHAR::getLength()
{
    return this->length;
}

class STRING
{
    CHAR* content;
    int length;
public:
    STRING(char c= '\0');
    STRING(char *s);
    STRING(CHAR a);
    ~STRING(void);
    char* getContent();
    int getLength();
    void setContent(CHAR *s);
    STRING* expand(CHAR c);
    STRING* expand(char c);
    STRING* expand(STRING const &s);
    STRING* expand(char* s);
    STRING* remove(CHAR c);
    STRING* remove(char c);
    void input();
    
};


STRING::STRING(char c)
{
    this->content=new CHAR[2];
    this->content->setContent(c);
    this->content[1].setContent('\0');
    this->length=1;
    if (c == '\0')
        this->length = 0;
}
STRING::STRING(char *s)
{
    this->length=int(strlen(s));
    this->content=new CHAR[this->length+1];
    for(int i=0; i<length; i++)
    {
        this->content[i].setContent(s[i]);
    }
    this->content[length].setContent('\0');
}
STRING::STRING(CHAR a)
{
    this->content=new CHAR[2];
    if (a.getLength() != 0)
    {
        this->content->setContent(a.getContent());
        this->content[1].setContent('\0');
        this->length = 1;
    }
    else
    {
        this->content->setContent('\0');
        this->length = 0;
    }
}

STRING::~STRING(void)
{
    if (this->content != NULL){
        delete[] this->content;
        this->content = NULL;
    }
}

char* STRING::getContent() {
    char*s = new char[this->length];
    for (int i = 0; i < length; i++)
    {
        if (this->content[i].getContent() == '\0')
            break;
        s[i] = this->content[i].getContent();
    }
    s[length] = '\0';
    return s;
}

int STRING::getLength()
{
    return this->length;
}

STRING* STRING::expand(CHAR c)
{
    int LENGTH = this->length + 1;
    CHAR* s = new CHAR[LENGTH + 1];
    for (int i = 0; i < LENGTH + 1; i++){
        if (i == LENGTH)
        {
            s[i].setContent('\0');
        }
        else if (i == LENGTH - 1){
            s[i].setContent(c.getContent());
        }
        
        else
            s[i].setContent(this->content[i].getContent());
    }
    delete[] this->content;
    this->content = s;
    this->length = LENGTH;
    return this;
}

STRING* STRING::expand(char c)
{
    CHAR *s = new CHAR[this->length + 2];
    for (int i = 0; i < this->length + 2; i++){
        if (i == length + 1){
            s[i].setContent('\0');
        }
        else if (i == length){
            s[i].setContent(c);
        }
        else{
            s[i].setContent(this->content[i].getContent());
        }
    }
    delete[] this->content;
    this->content = s;
    this->length = length + 1;
    return this;
}

STRING* STRING::expand(STRING const &s)
{
    int LENGTH = this->length + s.length;
    CHAR *pStr = new CHAR[LENGTH + 1];
    for (int i = 0; i < LENGTH + 1; i++){
        if (i == LENGTH){
            pStr[i].setContent('\0');
        }
        else if (i >= this->length && i < LENGTH){
            pStr[i].setContent(s.content[i - this->length].getContent());
        }
        else{
            pStr[i].setContent(this->content[i].getContent());
        }
    }
    delete[] this->content;
    this->content = pStr;
    this->length = LENGTH;
    return this;
}

STRING* STRING::expand(char* s)
{
    int LENGTH = this->length + int(strlen(s));
    CHAR *pStr = new CHAR[LENGTH + 1];
    for (int i = 0; i < LENGTH + 1; i++){
        if (i == LENGTH){
            pStr[i].setContent('\0');
        }
        else if (i >= this->length && i < LENGTH){
            pStr[i].setContent(s[i - this->length]);
        }
        else{
            pStr[i].setContent(this->content[i].getContent());
        }
    }
    delete[] this->content;
    this->content = pStr;
    this->length = LENGTH;
    return this;
}

STRING* STRING::remove(char c)
{
    for (int i = 0; i < this->length; i++){
        //Move all the characters behind the removed character up to 1
        if (this->content[i].getContent() == c)
        {
            for (int j = i; j < this->length - 1; j++)
            {
                this->content[j] = this->content[j + 1];
            }
            this->length = length - 1;
            this->content[length].setContent('\0');
        }
        //Check the character of current remove position before i+1
        if (this->content[i].getContent() == c)
        {
            i--;
        }
    }
    return this;
}

STRING* STRING::remove(CHAR c)
{
    for (int i = 0; i < this->length; i++){
        if (this->content[i].getContent() == c.getContent())
        {
            //Move all the characters behind the removed character up to 1
            for (int j = i; j < this->length - 1; j++)
            {
                this->content[j] = this->content[j + 1];
            }
            this->length = length - 1;
            this->content[length].setContent('\0');
        }
        //Check the character of current remove position before i+1
        if (this->content[i].getContent() == c.getContent())
        {
            i--;
        }
    }
    return this;
}

void STRING::input()
{
    char temp[1000];
    std::cin.getline(temp, 1000);
    this->length = int(strlen(temp));
    this->content = new CHAR[length + 1];
    for (int i = 0; i < length + 1; i++)
    {
        this->content[i].setContent(temp[i]);
    }
    this->content[length].setContent('\0');
}


int main()
{
    CHAR c1, c2('c');
    STRING s1, s2("s2"), s3('a'), s4(c1);
    s1.expand(c2)->expand('a')->expand(s2)->expand("abc");
    std::cout << s1.getContent() << std::endl;
    std::cout << s2.getContent() << std::endl;
    std::cout << c2.getContent() << std::endl;
    
    return 0;
}
