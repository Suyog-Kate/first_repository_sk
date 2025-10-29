#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// Convert string to lowercase for case-insensitive matching
string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Check if any keyword exists in the input
bool containsAny(const string &input, const vector<string> &keywords) {
    for (const auto &kw : keywords) {
        if (input.find(kw) != string::npos)
            return true;
    }
    return false;
}

void chatbot() {
    cout << "ShopBot: Hi! Welcome to ShopBot customer service.\n";
    cout << "ShopBot: What's your name?\n";
    cout << "You: ";
    string name;
    getline(cin, name);

    cout << "ShopBot: Nice to meet you, " << name << "! How can I assist you today?\n";
    cout << "(Type 'exit' anytime to quit)\n\n";

    while (true) {
        cout << "You: ";
        string input;
        getline(cin, input);

        string query = toLower(input);

        if (query == "exit" || query == "quit" || query == "bye") {
            cout << "ShopBot: Goodbye " << name << "! Thanks for chatting. Have a great day!\n";
            break;
        }

        if (containsAny(query, {"hello", "hi", "hey"})) {
            cout << "ShopBot: Hello " << name << "! How can I help you today?\n";
        }
        else if (containsAny(query, {"how are you", "how's it going", "how are you doing"})) {
            cout << "ShopBot: I'm just a bot, but I'm doing great! How about you?\n";
        }
        else if (containsAny(query, {"good", "fine", "well", "great", "okay"})) {
            cout << "ShopBot: Glad to hear that! How can I assist you further?\n";
        }
        else if (containsAny(query, {"hours", "open", "closing"})) {
            cout << "ShopBot: Our store is open from 9 AM to 9 PM, Monday to Saturday.\n";
        }
        else if (containsAny(query, {"product", "products", "available"})) {
            cout << "ShopBot: We offer electronics, clothing, home goods, and more.\n";
        }
        else if (containsAny(query, {"return", "refund", "exchange"})) {
            cout << "ShopBot: You can return any product within 30 days with your receipt.\n";
        }
        else if (containsAny(query, {"contact", "help", "support"})) {
            cout << "ShopBot: You can reach support at support@shop.com or call 123-456-7890.\n";
        }
        else if (containsAny(query, {"thank", "thanks", "thank you"})) {
            cout << "ShopBot: You're welcome, " << name << "! Happy to help.\n";
        }
        else if (containsAny(query, {"menu", "options"})) {
            cout << "ShopBot: Here are some things I can help you with:\n";
            cout << "1. Store hours\n2. Product information\n3. Return policy\n4. Contact support\n";
            cout << "Just type what you want to know.\n";
        }
        else {
            cout << "ShopBot: Sorry, I didn't get that. You can ask about store hours, products, returns, or support.\n";
            cout << "If you want to see options, just type 'menu'.\n";
        }
    }
}

int main() {
    chatbot();
    return 0;
}
