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
        error_information.push_back("���ʽ���ӷ��Ƿ���");
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
        error_information.push_back("���ʽ�Ƿ���������ʽ��������");
        //
    }

    if (flag && (vec[cur_pos].first == "number" || vec[cur_pos].first == "ident")) cur_pos++;
    else if (flag && vec[cur_pos].first == "lparen") {
        cur_pos++;
        
        flag &= expression();

        if (flag && cur_pos < vec.size() && vec[cur_pos].first == "rparen") cur_pos++;
        else if (flag){
            flag = 0;
            error_information.push_back("ȱʧ������!");
            // 
        }
    }
    else if (flag){
        flag = 0;
        if (cur_pos - 1 >= 0 && vec[cur_pos - 1].second == "(")
            error_information.push_back("�����ź�ȱ�ٱ��ʽ��");
        else
            error_information.push_back("����'" + vec[cur_pos].second + "'ǰȱʧ���ֻ��ʶ����");
        // 
    }

    return flag;
}