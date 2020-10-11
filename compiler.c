#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//全局变量
int k ;
int flag; //flag 1表明是数字，2是关键字或标识符
char token[100];

int isBlank(char ch){
    if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n'){
        return 1;
    }else {
        return 0;
    }
}

int isSymbol(char ch){
    if(ch == ':' || ch == '+' || ch == '*' || ch == ',' || ch == '(' || ch == ')')
        return 1;
    else {
        return 0;
    }
}

void digital(void){
    int i;
    for (i = 0; token[i] == '0'; i++)
        ;
    if(token[i] != '\0')
        printf("Int(%s)\n", &token[i]);
    else
        printf("Int(0)\n");
    flag = 0;
    k = 0;
    return ;
}

void keyword(void){
    if (strcmp(token, "BEGIN") == 0)
        printf("Begin\n");
    else if (strcmp(token, "END") == 0)
        printf("End\n");
    else if (strcmp(token, "FOR") == 0)
        printf("For\n");
    else if (strcmp(token, "IF") == 0)
        printf("If\n");
    else if (strcmp(token, "THEN") == 0)
        printf("Then\n");
    else if(strcmp(token, "ELSE") == 0)
        printf("Else\n");
    else
        printf("Ident(%s)\n", token);
    flag = 0;
    k = 0;
    return ;
}

int main(int argc, const char * argv[]){
    char ch;
    int i, j;
    FILE *in;
    in = fopen(argv[1], "r");
    flag = 0;
    k = 0;
    while ((ch=fgetc(in)) != EOF) {
        if (isBlank(ch)) {
            token[k] = '\0';
            if (strlen(token) != 0) {
                if (flag == 1) {
                    digital();
                }
                else if (flag == 2) {
                    keyword();
                }
            }
        }
        else if (isSymbol(ch)) {
            token[k] = '\0';
            if (strlen(token) != 0) {
                if (flag == 1) {
                    digital();
                }
                else if (flag == 2) {
                    keyword();
                }
            }
            if (ch == ':') {
                if ((ch = fgetc(in)) == '=') {
                    printf("Assign\n");
                }
                else{
                    printf("Colon\n");
                    fseek(in,-1L,SEEK_CUR);
                }
            }
            else if (ch == '+')
                printf("Plus\n");
            else if (ch == '*')
                printf("Star\n");
            else if (ch == ',')
                printf("Comma\n");
            else if (ch == '(')
                printf("LParenthesis\n");
            else if (ch == ')')
                printf("RParenthesis\n");
        }
        else if (isdigit(ch)) {
            if (flag == 0)
                flag = 1;
                token[k++] = ch;
        }
        else if (isalpha(ch)) {
            if (flag == 1) {
                token[k] = '\0';
                digital();
            }
            flag = 2;
            token[k++] = ch;
        }
        else {
            printf("Unknown\n");
            return 0;
        }
    }
    token[k] = '\0';
    if (strlen(token) != 0) { //如果最后token还有未输出的内容，那么只能是数字或者是关键字/标识符
        if (flag == 1) {
            digital();
        }
        else if (flag == 2) {
            keyword();
        }
    }
    fclose(in);
    return 0;
}
