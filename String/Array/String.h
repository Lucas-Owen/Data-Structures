#ifndef STRING_H
#define STRING_H

#include <iostream>
using namespace std;

class String{
    public:
    // Both constructors should construct this String from the parameters
    explicit String(const char * s = "");
    String(char c);
    String(const String & s);
    String operator = ( const String & s);
    char & operator [] (int index);
    int size() const;
    String reverse(); // does not modify this String
    int indexOf( const char c) const;
    int indexOf( const String s) const;
    int indexOf( const char* s) const{ return indexOf(String(s)); };
    bool operator == (const String s) const;
    bool operator != (const String s) const;
    bool operator > (const String s) const;
    bool operator < (const String s) const;
    bool operator <= (const String s) const;
    bool operator >= (const String s) const;
    // concatenates this and s to return result
    String operator + (const String s);
    // concatenates s onto end of this string
    String operator += (const String s);
    void print(ostream & out);
    void read(istream & in);
    ~String();
private:
   static char* str2dup(const char *s, const char *t);

private:
    bool inBounds(int i) const{
        return i >= 0 && i < strlen(buf);
    }// HINT: some C string primitives you should define and use
    static int strlen(const char * s);
    static char * strcpy(char *dest, const char *src);
    static char * strcat(char *dest, const char *src);
    static int strcmp(const char *left, const char *right);
    static int strncmp(const char *left, const char *right, int n);
    /* haystack "The quick brown fox ran up the lazy log"
    needle "ran" */
    static const char * strstr(const char * haystack, const char * needle);
    static char *strstr(char *haystack, const char *needle);
    static void reverse_cpy(char *dest, const char *src);
    static char* strdup(const char *src);

    static char* new_char_array(int n_bytes);
    static void delete_char_array(char* p);

    char* buf; // array for the characters in this string
    // DO NOT store the 'logical' length of this string
    // use the null '\0' terminator to mark the end
    static char terminator;
    public:
    static int num_allocations;
    static int num_deallocations;
};


ostream & operator << (ostream &out, String str);
istream & operator >> (istream &in, String & str);

#endif