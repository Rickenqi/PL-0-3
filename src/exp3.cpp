#include "exp3.h"
#include <iostream>

exp3::exp3(const vector<pair<string, string>>& vec)
    :ret(true), cur_pos(0), vec(vec) {
    ret = expression(0);
}

exp3::~exp3() {}

void exp3::print_ret() const {
    cout << "------------------------------" << endl;
    cout << cur_pos << "/" << vec.size() << endl;
    if (ret) {
        cout << "Correct!" << endl;
    }
    else {
        for (auto& it : vec) cout << it.second << " ";
        cout << endl;
        int blank_cnt = 0;
        for (int i = 0; i < cur_pos; i++)
            blank_cnt += 1 + vec[i].second.size();
        for (int i = 0; i < blank_cnt; i++) cout << ' ';
        cout << "^ ";
        //  << "Error!" << endl;
        for (auto& it : error_information) cout << it << endl;
    }
    cout << "------------------------------" << endl;
}

bool exp3::expression(int w = 1) {
    bool flag = 1;
    if (cur_pos < vec.size()
        && (vec[cur_pos].first == "plus" || vec[cur_pos].first == "minus")) cur_pos++;
    
    flag &= term();

    while (flag && cur_pos < vec.size() 
        && (vec[cur_pos].first == "plus" || vec[cur_pos].first == "minus")) {
        cur_pos++;
        flag &= term();
    }

    if (flag && w == 0 && cur_pos != vec.size()) {
        flag = 0;
        error_information.push_back("表达式链接符非法！");
    }

    return flag;
}

bool exp3::term() {
    bool flag = 1;
    flag &= factor();
    while (flag && cur_pos < vec.size() 
        && (vec[cur_pos].first == "times" || vec[cur_pos].first == "slash")) {
        cur_pos++;
        flag &= factor();
    }
    return flag;
}

bool exp3::factor() {
    bool flag = 1;
    if (cur_pos == vec.size()) {
        flag = 0;
        error_information.push_back("表达式非法结束或表达式不完整！");
        //
    }

    if (flag && (vec[cur_pos].first == "number" || vec[cur_pos].first == "ident")) cur_pos++;
    else if (flag && vec[cur_pos].first == "lparen") {
        cur_pos++;
        
        flag &= expression();

        if (flag && cur_pos < vec.size() && vec[cur_pos].first == "rparen") cur_pos++;
        else if (flag){
            flag = 0;
            error_information.push_back("缺失右括号!");
            // 
        }
    }
    else if (flag){
        flag = 0;
        if (cur_pos - 1 >= 0 && vec[cur_pos - 1].second == "(")
            error_information.push_back("左括号后缺少表达式！");
        else
            error_information.push_back("符号'" + vec[cur_pos].second + "'前缺失数字或标识符！");
        // 
    }

    return flag;
}