#include "String.h"

char String :: terminator = '\0';

int String :: num_allocations = 0;

int String :: num_deallocations = 0;

String :: String(const char * s){
    this->buf = strdup(s);
}

String :: String(char c){
    this->buf = new_char_array(2);
    this->buf[0] = c;
    this->buf[1] = '\0';
}

String :: String(const String &s){
    this->buf = strdup(s.buf);
}

String :: ~String(){
    delete_char_array(buf);
}

String String :: operator = (const String & s){
    delete_char_array(this->buf);
    this->buf = strdup(s.buf);
    return *this;
}

char & String :: operator [] (int index){
    terminator = '\0';
    if(!inBounds(index)) return terminator;
    return buf[index];
}

int String :: size() const{
    return strlen(buf);
}

String String :: reverse(){
    String result(*this);
    reverse_cpy(result.buf, this->buf);
    return result;
}

int String :: indexOf(const char c) const{
    int i = 0;
    while(buf[i] != '\0'){
        if(buf[i] == c){
            return i;
        }
        i++;
    }
    return -1;
}

int String :: indexOf(const String s) const{
    int i = 0;
    char c = String(s)[0];
    char ch = buf[0];
    int len = s.size(); 
    while(ch != '\0'){
        ch = buf[i];
        if(ch == c){
            if(strncmp(&buf[i], s.buf, len) == 0){
                return i;
            }
        }
        i++;
    }
    return -1;
}

bool String :: operator == (const String s) const{
    if(this->size() != s.size()) return false;

    return strcmp(this->buf, s.buf) == 0;
}
bool String :: operator != (const String s) const{
    return strcmp(this->buf, s.buf) != 0;
}
bool String :: operator > (const String s) const{
    return strcmp(this->buf, s.buf) > 0;
}
bool String :: operator < (const String s) const{
    return strcmp(this->buf, s.buf) < 0;
}
bool String :: operator <= (const String s) const{
    return strcmp(this->buf, s.buf) <= 0;
}
bool String :: operator >= (const String s) const{
    return strcmp(this->buf, s.buf) >= 0;
}
String String :: operator + (const String s){
      String result;

      try{
         delete [] result.buf;
      }
      catch(...){
         
      }

      result.buf = str2dup(this->buf, s.buf);

      return result;
   }
String String :: operator += (const String s){
    *this = *this + s;
    return *this;
}

int String :: strlen(const char *s){
    int i = 0;
    char c = s[0];
    while(c != '\0'){
        c = s[++i];
    }

    return i;
}
char * String :: strcpy(char *dest, const char *src){
    int i = 0;
    while(src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';

    return dest;
}

char * String :: strcat(char *dest, const char *src){
    strcpy(&dest[strlen(dest)], src);

    return dest;
}
int String :: strcmp(const char *left, const char *right){

    int len = strlen(left);
    int i;
    for(i = 0; i < len; i++){
        if(left[i] == '\0') return '\0' - right[i];
        if(right[i] == '\0') return left[i] - '\0';
        if(left[i] != right[i]) return left[i] - right[i];
    }
    return 0;
}
int String :: strncmp(const char *left, const char *right, int n){
    int i = 0;
    for(i = 0; i < n; i++){
        if(left[i] == '\0') return '\0' - right[i];
        if(right[i] == '\0') return left[i] - '\0';
        if(left[i] != right[i]) return left[i] - right[i];
    }
    return 0;
}

const char * String :: strstr(const char * haystack, const char * needle){
    int len = strlen(needle);
    int i = 0;
    char c = needle[0];
    while(haystack[i] != '\0'){
        if(haystack[i] == c){
            if(strncmp(&haystack[i], needle, len) == 0){
                return &haystack[i];
            }
        }
        i++;
    }
    return NULL;
}

char * String :: strstr(char * haystack, const char *needle){
    int len = strlen(needle);
    int i = 0;
    char c = needle[0];
    while(haystack[i] != '\0'){
        if(haystack[i] == c){
            if(strncmp(&haystack[i], needle, len) == 0){
                return &haystack[i];
            }
        }
        i++;
    }
    return NULL;
}

void String :: reverse_cpy(char *dest, const char *src){
    int len = strlen(src);
    for(int i = len - 1, j = 0; i >= 0; i--, j++){
        dest[j] = src[i];
    }
    dest[len] = '\0';
}

char* String :: strdup(const char *src){
    char *ptr = new_char_array(strlen(src) + 1);
    strcpy(ptr, src);
    return ptr;
}
void String :: print(ostream & out){
    out << buf ;
}

void String :: read(istream & in){
    char c;
    *this = String();
    while(in.get(c)){
        if(c == ' ' || c == '\n')
            break;
        *this += String(c);
    }
}

char* String :: new_char_array(int n_bytes){
    num_allocations++;
    return new char[n_bytes];
}

void String :: delete_char_array(char *p){
    try{
        delete [] p;
        num_deallocations++;
    }
    catch(...){

    }
}
ostream & operator << (ostream & out, String str){
    str.print(out);
    return out;
}

istream & operator >> (istream & in, String & str){
    str.read(in);
    return in;
}

char* String :: str2dup(const char *s, const char *t){
      char *ptr = new char[strlen(s) + strlen(t) + 1];
      strcpy(ptr, s);
      strcat(ptr, t);

      return ptr;
   }