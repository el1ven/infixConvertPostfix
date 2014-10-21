//
//  main.cpp
//  pro1
//
//  Created by el1ven on 14-6-6.
//  Copyright (c) 2014年 el1ven. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <stack>

using namespace std;

//中缀表达式转化为后缀表达式, RSP代表逆波兰表达式

bool isOptMark(char op){//判断是否为运算符
    switch(op){
        case '+':
            return 1;
            break;
        case '-':
            return 1;
            break;
        case '*':
            return 1;
            break;
        case '/':
            return 1;
            break;
        case '(':
            return 1;
            break;
        default:
            return 0;
    }
}

int prior(char op){//求运算符优先级
    switch (op) {
        case '#':
            return -1;
            break;
        case '(':
            return 0;
            break;
        case '+':
        case '-':
            return 1;
            break;
        case '*':
        case '/':
            return 2;
            break;
        default:
            return -1;
    }
}

string convert(string infixExp,string &RSP){//中缀表达式转后缀表达式
    
        stack<char> stk;//存储操作符栈
    
        stk.push('#');//必须要有这个末尾识别符号，否则栈为空的话，会报错！！！
    
        int length = (int)infixExp.length();//获取表达式的长度
        for(int i = 0; i < length; i++){
            if(infixExp[i] >= '0' && infixExp[i] <= '9'){
                //读入数字的话，直接输出
                RSP += infixExp[i];
            }else if(infixExp[i] == '('){
                //遇到左括号直接入栈
                stk.push(infixExp[i]);
            }else if(infixExp[i] == ')'){
                //如果遇到右括号的话，就把一直到最近的左括号之间的都弹出来加入RPN中
                while(stk.top() != '('){
                    RSP += stk.top();
                    stk.pop();
                }
                stk.pop();//把左括号弹出栈
            }else if(isOptMark(infixExp[i])){
                //用空格把数字和运算符分开，这样就可以计算多位数字了
                RSP += ' ';
                //如果是运算符的话，比较他们的优先级再决定是否入栈
                while( prior(infixExp[i]) <= prior(stk.top()) ){
                    //如果当前的优先级小于等于栈顶操作符的话，栈顶操作符弹出，加入RSP
                    RSP += stk.top();
                    stk.pop();
                }
                //如果当前的优先级大于栈顶操作符的话，入栈

                stk.push(infixExp[i]);
  
               
            }
        }
        //如果已经扫描到中缀表达式的末尾，就把栈中的操作符都弹出来加入到RSP中
        while(!stk.empty()){
            RSP += stk.top();
            stk.pop();
        }
    
    return RSP;
}

int readNum(string exp, int &i){
    int result = 0;
    while(exp[i] >= '0' && exp[i] <= '9'){
        result = result * 10 + (exp[i] - '0');
        i++;
    }
    return result;
}

int calulate(string RSP){//计算后缀表达式(逆波兰表达式)的最终数值
    
    int i = 0;
    stack<int> optNum;//操作数栈
    int x1,x2 = 0;
    
    while(RSP[i] != '#'){//没有遇到结束标志#，即进行表达式的计算
        if(RSP[i] >= '0' && RSP[i] <= '9'){
            optNum.push(readNum(RSP, i));//字符串转整数
        }else if(RSP[i] == ' '){
            i++;
        }else if(RSP[i] == '+'){
            x1 = optNum.top();
            optNum.pop();
            x2 = optNum.top();
            optNum.pop();
            optNum.push(x1+x2);
            i++;
        }else if(RSP[i] == '-'){
            x1 = optNum.top();
            optNum.pop();
            x2 = optNum.top();
            optNum.pop();
            optNum.push(x2-x1);
            i++;
        }else if(RSP[i] == '*'){
            x1 = optNum.top();
            optNum.pop();
            x2 = optNum.top();
            optNum.pop();
            optNum.push(x1*x2);
            i++;
        }else if(RSP[i] == '/'){
            x1 = optNum.top();
            optNum.pop();
            x2 = optNum.top();
            optNum.pop();
            optNum.push(x2/x1);
            i++;
        }
    }
    return optNum.top();//返回最终的计算结果
}


int main(){
    string infixExp = "";
    while(cin>>infixExp){
        string RSP = "";
        string postFix = convert(infixExp, RSP);//后缀表达式
        cout<<"RSP为: "<<postFix<<endl;
        int result = calulate(postFix);
        cout<<"Result: "<<result<<endl;
    }
    return 0;
}



