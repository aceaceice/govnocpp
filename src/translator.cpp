#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <iostream>
#include <string>

std::string translate(std::string sentence) {
    std::string translatedText;

    web::http::client::http_client client(U("https://microsoft-translator-text.p.rapidapi.com/translate?api-version=3.0&to%5B0%5D=ru&textType=plain&profanityAction=NoAction"));

    web::http::http_request request(web::http::methods::POST);
    request.headers().add(U("content-type"), U("application/json"));
    request.headers().add(U("X-RapidAPI-Key"), U("e6c9c80ebbmshfc7a48b821e6fe1p1138d5jsn5dc4bb9d7167"));
    request.headers().add(U("X-RapidAPI-Host"), U("microsoft-translator-text.p.rapidapi.com"));

    web::json::value body;
    body[0][U("Text")] = web::json::value::string(sentence);
    request.set_body(body);
    // std::cout << body;
    client.request(request)
        .then([](web::http::http_response response) {
            
            return response.extract_json();
        })
        .then([&translatedText](web::json::value jsonValue) {
            if (jsonValue.is_array() && jsonValue.size() > 0) {
                const auto& text = jsonValue[0][U("translations")][0][U("text")];
                if (text.is_string()) {
                    translatedText = utility::conversions::to_utf8string(text.as_string());
                }
            }
        })
        .wait();
    translatedText = sentence + " -> " + translatedText;
    return translatedText;
}
