#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        double result = 0.0;
        nums1.insert(nums1.end(), nums2.begin(),nums2.end());
        return result;
    }
};
int main() {
    vector<int> nums1;
    vector<int> nums2;
    nums1.push_back(1);
    nums1.push_back(2);
    nums2.push_back(3);
    nums2.push_back(4);
    Solution solution;
    cout << solution.findMedianSortedArrays(nums1, nums2) << endl;
}
