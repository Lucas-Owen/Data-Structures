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
        String reverse() const; // does not modify this String
        int indexOf( const char c) const;
        int indexOf( const String s) const;
        int indexOf( const char* s) const{ return indexOf(String(s)); };
        bool operator == (const String& s) const;
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
        struct ListNode{
            char info;
            ListNode *next;
            ListNode(char newInfo, ListNode *newNext)
            : info(newInfo), next(newNext){}

            static ListNode * stringToList(const char *s);
            static ListNode * copy(ListNode * L);
            static ListNode * reverse(ListNode * L);
            static ListNode * append(ListNode * L1, ListNode * L2);
            static ListNode * find(char c, ListNode * L);
            static char &charAt(int i, ListNode * L);
            static int length(ListNode * L);
            static int compare(ListNode * L1, ListNode * L2);
            static bool equal(ListNode * L1, ListNode * L2);
            static int ncompare(ListNode * L1, ListNode * L2, int len);
            static void deleteList(ListNode *L);
            
        };
    private:
        bool inBounds(int i) const{
            return i >= 0 && i < size();
        }
        
        ListNode *head{NULL}; 
};


ostream & operator << (ostream &out, String str);
istream & operator >> (istream &in, String & str);

#endif