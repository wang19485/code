
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<char>v;
        vector<int>com;
        vector<int>com2;
        int result = 0;
        if(s == ""){
            return 0;
        }else if(s.size() == 1){
            return 1;
        }
        for(int i = 0; i < s.size();++i){
            if((find(v.begin(),v.end(),s[i]) == v.end()) || v.empty()){
                v.push_back(s[i]);
                com2.push_back(0);
                for (int j = 0; j < com2.size(); ++j) {
                    com2[j] = com2[j]+1;
                }
                com.push_back(com2.front());
            }else{
                while (v.front() != s[i]) {
                    v.erase(v.begin());
                    com2.erase(com2.begin());
                }
                v.erase(v.begin());
                v.push_back(s[i]);
                com2.erase(com2.begin());
                com2.push_back(0);
                for (int j = 0; j < com2.size(); ++j) {
                    com2[j] = com2[j]+1;
                }
            }
        }
        if(!com.empty()){
            int max = com[0];
            for(int j = 0; j < com.size();++j){
                if(com[j] > max){
                    max = com[j];
                }
            }
            result = max;
        }
        return result;
    }
};
int main() {
    Solution s;
    cout << s.lengthOfLongestSubstring("pwwkew") << endl;
    cout << s.lengthOfLongestSubstring("aab") << endl;
    cout << s.lengthOfLongestSubstring("dvdf") << endl;
    cout << s.lengthOfLongestSubstring("abcabcbb") << endl;
    cout << s.lengthOfLongestSubstring("ckilbkd") << endl;
}
