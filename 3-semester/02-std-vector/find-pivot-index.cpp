#include <iostream>
#include <vector>

class Solution {
public:
    int pivotIndex(const std::vector<int>& nums) {
        int left = 0, right = 0;
        for(int i = 1; i < nums.size(); i++)
            right += nums[i];
        
        for(int i = 0; i < nums.size(); i++){
            if( left == right )
                return i;
            if( i != nums.size()-1 ){
                left += nums[i];
                right -= nums[i+1];
            }
            else
                if( left == 0 )
                    return i;
        }
        
        return -1;
    }
};

std::vector<int> gen_array(const int& array_len) {
    std::vector<int> myret;
    for(int i = 0; i < array_len; i++) {
        myret.push_back(rand() % 10);
    }
    return myret;
}

int main() {
    int array_len;
    std::cout << "Hi, i'm finding pivot of array" << std::endl;

    std::cout << "if you want to use manual, enter 1" << std::endl;
    int manual_choice = 0;
    std::cin >> manual_choice;
    std::vector<int> generated_array;

    if(manual_choice) {
        int tmp_manual_element;
        

        while(std::cin >> tmp_manual_element) {
            generated_array.push_back(tmp_manual_element);
        }
    }
    else {
        std::cout << "Enter length to generate random array and to find it's pivot" << std::endl;
        std::cin >> array_len;
        generated_array = gen_array(array_len);
    }

    array_len = generated_array.size();
    
    Solution is;
    
    for(int i = 0; i < array_len; i++) { // kak zaconstantit' array_len ?
        std::cout << generated_array[i] << " ";
    }

    std::cout << std::endl;
    std::cout << "pivot is " << is.pivotIndex(generated_array) << std::endl;

    return 0;
}