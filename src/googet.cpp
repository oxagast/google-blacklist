#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(int argc, char *argv[])
{
  std::string sub_query = argv[1];
  // maybe needed this &tok=qrPq0XiGY77JP-GaK0ngBQ ?
  std::string url = "https://www.google.com/complete/search?client=hp&hl=en&gs_rn=64&gs_ri=hp&gs_mss=" + sub_query + "&cp=6&gs_id=y&q=" + sub_query + "&xhr=t";
  boost::replace_all(url, " ", "\%20");
  CURL *curl;
  std::string read_buffer;
  CURLcode res;
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    #ifdef SKIP_PEER_VERIFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    #endif
    #ifdef SKIP_HOSTNAME_VERIFICATION 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    #endif
  //  curl_easy_setopt(curl, CURLOPT_READDATA, &from_goog);
    /* Perform request, res will return code */
   // curl_easy_perform(curl);
    /* errors */ 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    /* cleanup */ 
    }

    else {
        /*
         * make a bunch of formatting corrections
         */
        boost::replace_all(read_buffer, "\\u003cb\\u003e", "");
        boost::replace_all(read_buffer, "\\u003c\\/b\\u003e\",0", "\n");
        boost::replace_all(read_buffer, "[\"" + sub_query + "\",[[\"", "");
        boost::replace_all(read_buffer, "],[\"", "");
        boost::replace_all(read_buffer, "\",0", "\n");
        boost::replace_all(read_buffer, "\\u003c\\/b\\u003e", "");
        /* 
         * create a vector for each one to sit in 
         */
        std::vector<std::string> suggestions;
        /*
         * split the string up by newlines
         */
        boost::split(suggestions, read_buffer, boost::is_any_of("\n"), boost::token_compress_on);
        /*
         * get rid of that nasty last line
         */
        suggestions.erase(suggestions.end());        
        /*
         * loop around the vector for each suggestion out of google
         */
        for (int cur_sugg = 0; cur_sugg < suggestions.size(); cur_sugg++) {
          if (suggestions[cur_sugg].find(",[") == std::string::npos) {
            std::cout << suggestions[cur_sugg] << std::endl;
          }
      }  
    }
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return 0;
}

