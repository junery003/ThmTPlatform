#pragma once

#include "pch.h"
#include <nlohmann/json.hpp>

#include <string>
#include <vector>
#include <fstream>
#include <streambuf>

using namespace std;

struct JT {
    uint32_t a{ 0 };
    string s;

    JT() {}
    JT(int a1, const string& s1) : a(a1), s(s1) {}
};

std::string Serialize() {
    vector<JT> jts{ JT(0, "a"), JT(1, "basdf") };

    auto jarr = nlohmann::json::array();
    for (const auto& it : jts) {
        nlohmann::json tmp;
        tmp["a"] = it.a;
        tmp["s"] = it.s;
        jarr.push_back(tmp);
    }

    //return jarr.dump();
    {
        string fn("1111.json");
        ofstream os(fn);
        os << jarr.dump();
        os.close();

        ifstream is(fn);
        if (is) {
            string data((istreambuf_iterator<char>(is)), istreambuf_iterator<char>());
            return data;
        }
    }

    return "";
}

void from_json(const nlohmann::json& j, JT& jt) {
    j.at("a").get_to(jt.a);
    j.at("s").get_to(jt.s);
}

vector<JT> Deserialize(const std::string& str) {
    auto j = nlohmann::json::parse(str);
    vector<JT> all;
    auto rlt = j.get_to<vector<JT>>(all);

    return all;
}

int main1() {
    string str(Serialize());

    auto rlt(Deserialize(str));

    for (const auto& it : rlt) {

    }
}
