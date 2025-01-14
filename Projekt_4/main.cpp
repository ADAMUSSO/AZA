#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;
//////////conflict!!!!!
struct Item {
    string letter;
    int freq;
    int depth;
    string code;
};
//compare item frequencies
bool compare_items_freq(Item a, Item b) {
    if (a.freq == b.freq) {
        return a.letter < b.letter;
    }
    return a.freq < b.freq;
}
//compare the depth for sort
bool compare_items_depth(Item a, Item b) {
    if (a.depth == b.depth) {
        return a.letter < b.letter;
    }
    return a.depth < b.depth;
}
// calculate cannonical huffman code lengths
void cal_height_Can_Huf(vector<Item>& Items) {
    vector<Item> Items_temp = Items;
    //until everything is merged
    while (Items_temp.size() > 1){
        sort(Items_temp.begin(), Items_temp.end(), compare_items_freq);
        for(auto& Item: Items_temp){
            cout<< Item.letter <<": "<<Item.freq<<", ";
        }
        //merge first 2 items in the list and return them to the list combined
        Item temp;
        temp.letter = Items_temp[0].letter + Items_temp[1].letter;
        temp.freq = Items_temp[0].freq + Items_temp[1].freq;
        temp.depth = 0;
        cout << "Combine: " << temp.letter << " with frequency: "<< temp.freq<<"\n";


        for (char c : temp.letter) {
            for (auto& Item : Items) {
                if (Item.letter == string(1, c)) {
                    //increase letters depth
                    Item.depth++;
                }
            }
        }

        Items_temp.erase(Items_temp.begin());
        Items_temp.erase(Items_temp.begin());
        Items_temp.push_back(temp);
    }
}

void generate_Huff_codes(vector<Item>& Items) {
    sort(Items.begin(), Items.end(), compare_items_depth);

    int current_code = 0;
    int current_length = Items[0].depth;//starting with first and shortest code

    for (auto& Item : Items) {
        // If the depth of the current item is bigger than the depth of the previous one code
        // shifts the current code left by the difference of depths to adjust for the new dpth,
        //this ensures that the codes are different
        // (conflict shouldnt happen so this can be considered where i am dealing with it)
        if (Item.depth > current_length) {
            current_code <<= (Item.depth - current_length);
            current_length = Item.depth; // update the current depth
        }

        Item.code = "";
        int temp_code = current_code;
        //converting the code to binary string
        for (int i = 0; i < current_length; ++i) {
            Item.code = (char)('0' + (temp_code % 2)) + Item.code;
            temp_code /= 2;
        }

        current_code++;//increment for next item
    }
}
//calculate Kraft-McMillan inequality to check validity of  lengths
bool checkup(vector<Item>& Items){
    double sum = 0;
    for(auto& Item :Items){
        sum += pow(2,(-Item.depth));
        cout<<sum<<"\n";
    }
    if(sum <= 1){
        cout<<"Checkup good: "<<sum<<"\n";
        return true;
    }
    return false;
}



//function to approximately determine the depths and code lengths based on calculation of
// log with base 2(freq/total_freq of all items)
void cal_height_freq_aprox(vector<Item>& Items){
    int total = 0;
    double value;
    for(auto& Item : Items){
        total += Item.freq;
    }
    //this is done for each item
    for(auto& Item: Items){
        value = -log2((double)Item.freq / total);
        cout << "Approx. value for letter: " << Item.letter << " is: " << value<<"\n";
        Item.depth = ceil(value);

    }
}

int main() {
    int n = 0;
    int vyber;
    cout << "Enter the number of characters: ";
    cin >> n;

    vector<string> letters_predefined = {"A", "B", "C", "D", "E", "F"};
    vector<int> freq_predefined = {45, 13, 12, 16, 9, 5};
    vector<Item> Items(n);

    for (int i = 0; i < n; i++) {
        Items[i].letter = letters_predefined[i];
        Items[i].freq = freq_predefined[i];
        Items[i].depth = 0;
    }
    cout << "choose option Canonical Huff(1) Frequency based aprox(2):";
    cin >> vyber;
    if(vyber == 1){
        cal_height_Can_Huf(Items);
        cout << "\nHeights of the letters:\n";
        //just to print sorted Items with frequencies(not count to final time complexity
        // because it has just presentation purpose)
        for (const auto& Item : Items) {
            cout << Item.letter << ": height = " << Item.depth << endl;
        }
        if(!checkup(Items)){
            cout<<"Bad checkup";
            return 0;

        }
        //create codes based on code lengths
        generate_Huff_codes(Items);

        cout << "\nHuffman Codes:\n";
        for (const auto& Item : Items) {
            cout << Item.letter << ": code = " << Item.code << ", height = " << Item.depth << endl;
        }
    }
    else if(vyber == 2){
        cal_height_freq_aprox(Items);
        cout << "\nHeights of the letters:\n";
        for (const auto& Item : Items) {
            cout << Item.letter << ": height = " << Item.depth << endl;
        }
        if(!checkup(Items)){
            cout<<"Bad checkup";
            return 0;

        }
        generate_Huff_codes(Items);
        cout << "\nHuffman Codes:\n";
        for (const auto& Item : Items) {
            cout << Item.letter << ": code = " << Item.code << ", height = " << Item.depth << endl;
        }
    }
    //Encoding sequence of letters
    cout << "\nEnter text to encode (letters A-F): ";
    string text_to_encode;
    cin >> text_to_encode;

    string encoded_text = "";

    for (char c : text_to_encode) {
        string letter(1, c); // Convert char to string
        bool found = false;
        for (const auto& Item : Items) {
            if (Item.letter == letter) {//finding code for letter in items
                encoded_text += Item.code;//append the code
                found = true;
                break;
            }
        }
        if (!found) {
            //if code is not found
            cout << "Error: Letter '" << letter << "' not found in codebook.\n";
            return 1;
        }
    }

    cout << "Encoded text: " << encoded_text << endl;
    //decode the encoded text
    string decoded_text;
    string buffer;

    for (char c : encoded_text) {
        buffer += c;//buffer to store code bits and add one by one
        for (const auto& Item : Items) {
            if (Item.code == buffer) {//if match is found add letter to decoded text
                decoded_text += Item.letter;
                buffer = "";//clear buffer
                break;
            }
        }

    }

    if (!buffer.empty()) {
        cout << "Error: Encoded text contains invalid code sequences.\n";
        return 1;
    }

    cout << "Decoded text: " << decoded_text << endl;

    return 0;
}