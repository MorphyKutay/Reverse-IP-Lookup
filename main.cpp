#include<stdio.h>
#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace std;
using json = nlohmann::json;
using namespace std;

void help() {
    cout << "Usage: \n\n ./reverseip -u google.com -a <apikey> -o <output.txt>" << endl;
}



size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t total_size = size * nmemb;
    ((std::string*)userp)->append((char*)contents, total_size);  // Veriyi string'e ekle
    return total_size;
}

vector<string> process_json_response(const string& json_data) {
    vector<string> domain_list;
    try {
        json response = json::parse(json_data);

        // API yanıtında "response" anahtarını kontrol et
        if (response.contains("response") && response["response"].contains("domains")) {
            json domains = response["response"]["domains"];

            cout << "Found domains:" << endl;
            for (const auto& domain : domains) {
                string name = domain.value("name", "N/A");
                cout << name << endl;
                domain_list.push_back(name);  // Listeye ekle
            }
        } else {
            cerr << "Invalid JSON response: missing 'response' or 'domains' key!" << endl;
        }
    } catch (const json::parse_error& e) {
        cerr << "JSON parse error: " << e.what() << endl;
    }

    return domain_list;
}

// Dosyaya kayıt fonksiyonu
void save_file(const vector<string>& domains, const string& filename) {
    ofstream file(filename);

    if (!file) {
        cerr << "Dosya açılamadı: " << filename << endl;
        return;
    }

    for (const auto& domain : domains) {
        file << domain << endl;
    }

    file.close();
    cout << "Data saved to '" << filename << "' successfully." << endl;
}




int main(int argc, char* argv[]){

    if(argc < 6){
        help();
        return 1;
    }
    
    string parameter = argv[1];
    string output_file = argv[6];  // Çıktı dosyası

    string apikey = argv[4];
    if (parameter == "-u" || parameter == "--url"){
        if(argc < 6){
            help();
            return 1;
        }
        CURL* curl;
        CURLcode res;
        std::string read_buffer;
    
        // cURL başlat
        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
    
        if(curl) {
            string url = "https://api.viewdns.info/reverseip/?host=" + std::string(argv[2]) + "&apikey="+std::string(apikey)+"&output=json";
            //cout << url << endl;
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            // Yanıtın bir string'e yazılması için callback fonksiyonunu ayarla
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

            // GET isteği gönder
            res = curl_easy_perform(curl);
            if(res == CURLE_OK) {
                //process_json_response(read_buffer);
                vector<string> domains = process_json_response(read_buffer);
                if (!domains.empty()) {
                    save_file(domains, output_file);  // Kaydet
                } else {
                    cerr << "No domains found, skipping file save." << endl;
                }

            
            } else {
                std::cerr << "cURL hatası: " << curl_easy_strerror(res) << std::endl;
            }
    
            // CURL kaynaklarını serbest bırak
            curl_easy_cleanup(curl);
        
        }else{
            cout << "ERROR" << endl;
        }
        curl_global_cleanup();

    }else{
        help();
    }

    return 0;
}