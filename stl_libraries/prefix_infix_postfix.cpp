#include <iostream>
#include <stack>
#include <cmath>

int prefixEvaluation(std::string s){
    std::stack<int> st;
    for(int i = s.size()-1; i>=0;i--){
        if(s[i] >= '0' && s[i] <= '9'){
            st.push(s[i]-'0');
        }
        else{
            int op1 = st.top();
            st.pop();
            int op2 = st.top();
            st.pop();

            switch (s[i])
            {
            case '+':
                st.push(op1+op2);
                break;
            case '-':
                st.push(op1-op2);
                break;
            case '*':
                st.push(op1*op2);
                break;
            case '/':
                st.push(op1/op2);
                break;
            case '^':
                st.push(std::pow(op1,op2));
                break;
            
            default:
                break;
            }
        }
    }
    return st.top();
}

int postfixEvaluation(std::string s){
    std::stack<int> st;

    for(int i = 0; i < s.size(); i++){
        if(s[i] >= '0' && s[i] <= '9'){
            st.push(s[i]-'0');
        }
        else{
            int op2 = st.top();
            st.pop();
            
            int op1 = st.top();
            st.pop();

            switch (s[i])
            {
            case '+':
                st.push(op1+op2);
                break;
            case '-':
                st.push(op1-op2);
                break;
            case '*':
                st.push(op1*op2);
                break;
            case '/':
                st.push(op1/op2);
                break;
            case '^':
                st.push(op1^op2);
                break;
            }
        }
    }
    return st.top();
}

int main(){
    std::cout << "Prefix Evaluation:\n";
    std::cout << prefixEvaluation("-+7*45+20") << "\n\n";

    std::cout << "Postfix Evaluation:\n";
    std::cout << postfixEvaluation("46+2/5*7+") << "\n\n";

    return 0;
}