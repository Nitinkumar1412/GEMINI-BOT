// HEADER FILES -----------------------------
#include <iostream>
#include <curl/curl.h>
#include <string>
#include "C:/json/json.hpp"
#include <fstream>
#include <cctype>

#define GREEN   "\033[1;32m"
#define RESET   "\033[0m"

using json = nlohmann::json;
using namespace std;

static const string API_KEY = "AIzaSyCaAVZrQHaEkLrLs09B2cdXNWzYpewtGJE";
static const string CA_BUNDLE = "C:/curl/cacert.pem";

// Callback to capture response
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output)
{
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}
void typingIndicator() 
{
    for (int i = 0; i < 6; i++) 
    {
        cout << "\rSVN Bot is typing";
        cout << string(i % 4, '.') << "   ";
        Sleep(300);
    }
    cout << "\r                           \r";
}

string colorBold(string text, string color = GREEN) 
{
    string result = "";
    bool bold = false;

    for (int i = 0; i < text.size(); i++)  
    {
        if (text[i] == '*' && text[i+1] == '*') 
        {
            bold = !bold;   // toggle
            i++;            // skip second *
            result += (bold ? color : RESET);
            continue;
        }
        result += text[i];
    }

    result += RESET; 
    return result;
}

string wrapText(const string& text, int width = 60) 
{
    string out;
    int count = 0;

    for (char c : text) 
    {
        out += c;
        count++;

        if (count >= width && c == ' ') 
        {
            out += '\n';
            count = 0;
        }
    }
    return out;
}

string doingupper(string text) 
{
    string result = "";
    bool bold = false;

    for (int i = 0; i < text.size(); i++) 
    {
        if (text[i] == '*' && text[i+1] == '*') 
        {                                               // ** hbdvhdvbjdvbjk **
            bold = !bold;   // toggle
            i++;            // skip second * 
        }
        if(bold)
        {
            result+= toupper(text[i]);
        }
        
         else result+= text[i];
    }

    return result;
}


int main()
{
    string filename;
     cout << "-----------------------------------------------\n";
     cout << "            WELCOME TO SVN BOT  \n";
     cout << "-----------------------------------------------\n";
     cout << "     Designed by: Santosh | Nitin | Vaikhan\n";
     cout << "-----------------------------------------------\n";
     cout << "Type 'exit' anytime to quit.\n\n";
     cout<< "Enter the name for the chat to be stored in history : ";
     cin >> filename;
     getchar();
     ofstream myFile("./chat history/"+filename+".md");

    while(true)
    {
        
        cout << "You: ";
        string user;
        getline(cin, user);
        if (user == "exit") 
        {
            break;
        }
        myFile <<"you: "<< user<<"\n";


        // ---------- Build JSON ----------
        json request;
        request["contents"] = 
        {
            {
                {"role", "user"},
                {"parts", { { {"text", user} } }}
            }
        };

        string body = request.dump();

        // ---------- cURL ----------
        CURL* curl = curl_easy_init();
        if (!curl)
        {
            cerr << "Curl failed\n";
            return 1;
        }

        string url =
            "https://generativelanguage.googleapis.com/v1beta/models/"
            "gemini-2.5-flash:generateContent?key=" + API_KEY;

        string response = "";

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
        curl_easy_setopt(curl, CURLOPT_CAINFO, CA_BUNDLE.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {

            cout << "Curl error: " << curl_easy_strerror(res) << endl;
        }
        else

        {
            string reply;
            string history;
            json j = json::parse(response);
            cout << "RAW API RESPONSE: " << response << "\n"<<endl;

            reply=j["candidates"][0]["content"]["parts"][0]["text"];
            typingIndicator();
            history = doingupper(reply);
            reply = colorBold(reply, GREEN);
            reply = wrapText(reply, 60);
            

            myFile <<"SVN bot : " << history<<"\n";
            myFile <<"------------------------------------------------------------------------------------------------------------------\n";
            cout << "SVN Bot : " << reply<< endl << endl;
            cout << "-------------------------------------------------------------------------------------------------------------------\n";
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);


    }
    
    myFile.close();

    return 0;

}
