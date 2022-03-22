#include "String.h"
#include <stdexcept>

String :: String(const char * s){
    this->head = String :: ListNode :: stringToList(s);
}

String :: String(char c){
    const char str[2] = {c, '\0'};
    *this = String(str);
}

String :: String(const String &s){
    this->head = String :: ListNode :: copy(s.head);
}

String :: ~String(){
    ListNode :: deleteList(this->head);
}

String String :: operator = (const String & s){
    ListNode :: deleteList(this->head);
    this->head = String :: ListNode :: copy(s.head);
    return *this;
}

char & String :: operator [] (int index){
    static char term = '\0';
    if(!inBounds(index)){
        term = '\0';
        return term;
    }
    // throw out_of_range("String index out of range");
    return String :: ListNode :: charAt(index, this->head);
}

int String :: size() const{
    return String :: ListNode :: length(this->head);
}

String String :: reverse() const{
    String result(*this);
    result.head = ListNode :: reverse(result.head);
    return result;
}

int String :: indexOf(const char c) const{
    ListNode *temp = this->head;
    int i = 0;
    while(temp != NULL){
        if(temp->info == c){
            return i;
        }
        temp = temp->next;
        i++;
    }
    return -1;
}

int String :: indexOf(const String s) const{
    int i = 0;
    if(s.head == NULL) return -1;
    char c = String(s)[0];
    ListNode *node = this->head;
    int len = s.size(); 
    while(node != NULL){
        if(ListNode :: ncompare(node, s.head, len) == 0){
            return i;
        }
        node = node->next;
        i++;
    }
    return -1;
}

bool String :: operator == (const String& s) const{

    return ListNode :: equal(this->head, s.head);
}
bool String :: operator != (const String s) const{
    return String :: ListNode :: compare(this->head, s.head) != 0;
}
bool String :: operator > (const String s) const{
    return String :: ListNode :: compare(this->head, s.head) > 0;
}
bool String :: operator < (const String s) const{
    return String :: ListNode :: compare(this->head, s.head) < 0;
}
bool String :: operator <= (const String s) const{
    return String :: ListNode :: compare(this->head, s.head) <= 0;
}
bool String :: operator >= (const String s) const{
    return String :: ListNode :: compare(this->head, s.head) >= 0;
}
String String :: operator + (const String s){
      String result;

      result.head = String :: ListNode :: append(this->head, s.head);

      return result;
   }
String String :: operator += (const String s){
    *this = *this + s;
    return *this;
}

String :: ListNode * String :: ListNode :: stringToList(const char *s){
    if(s[0] == '\0') return NULL;

    ListNode *node = new ListNode(s[0], NULL), *temp = node;
    int i = 1;
    while(s[i] != '\0'){
        temp->next = new ListNode(s[i], NULL);
        temp = temp->next;
        i++;
    }

    return node;
}
int String :: ListNode :: length(ListNode* L){
    int i = 0;
    
    while(L != NULL){
        L = L->next;
        i++;
    }

    return i;
}
String :: ListNode * String :: ListNode :: copy(ListNode *L){
    if(L == NULL) return NULL;

    ListNode *node = new ListNode(L->info, NULL), *temp = node;
    L = L->next;
    while(L != NULL){
        temp->next = new ListNode(L->info, NULL);
        temp = temp->next;
        L = L->next;
    }

    return node;
}

String :: ListNode * String :: ListNode :: reverse(ListNode* L){
    ListNode *prev = NULL, *temp;
    while(L != NULL){
        temp = L->next;
        L->next = prev;
        prev = L;
        L = temp;
    }
    return prev;
}

String :: ListNode * String :: ListNode :: append(ListNode *L1, ListNode *L2){
    ListNode *L1copy = copy(L1), *temp = L1copy;
    ListNode *L2copy = copy(L2);
    if(temp == NULL){
        return L2copy;
    }
    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = L2copy;

    return L1copy;
}
int String :: ListNode :: compare(ListNode *left, ListNode *right){

    while(left != NULL || right != NULL){
        if(left == NULL) return '\0' - right->info;
        if(right == NULL) return left->info - '\0';
        if(left->info != right->info) return left->info - right->info;

        left = left->next;
        right = right->next;
    }
    return 0;
}
bool String :: ListNode :: equal(ListNode *left, ListNode *right){

    while(left != NULL || right != NULL){
        if(left == NULL) return false;
        if(right == NULL) return false;
        if(left->info != right->info) return false;

        left = left->next;
        right = right->next;
    }
    return true;
}
int String :: ListNode :: ncompare(ListNode *left, ListNode *right, int n){

    for(int i = 0; i < n; i++){
        if(left == NULL && right != NULL) return '\0' - right->info;
        if(right == NULL && left != NULL) return left->info - '\0';
        if(left->info != right->info) return left->info - right->info;

        left = left->next;
        right = right->next;
    }
    return 0;
}

String :: ListNode * String :: ListNode :: find(char c, ListNode *L){
    while(L != NULL){
        if(L->info == c){
            return L;
        }
        L = L->next;
    }
    return NULL;
}

char & String :: ListNode :: charAt(int i, ListNode * L){
    while(i > 0){
        L = L->next;
        i--;
    }
    return L->info;
}

void String :: ListNode :: deleteList(ListNode *L){
    if(L == NULL) return;
    ListNode* temp = L;
    L = L->next;
    delete temp;
    deleteList(L);
}


void String :: print(ostream & out){
    String :: ListNode *temp = this->head;
    while(temp != NULL){
        out << temp->info ;
        temp = temp->next;
    }
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

ostream & operator << (ostream & out, String str){
    str.print(out);
    return out;
}

istream & operator >> (istream & in, String & str){
    str.read(in);
    return in;
}


int main(){
    String input;
    while(cin >> input){
        if(input == String("yes") )
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
    return 0;
}