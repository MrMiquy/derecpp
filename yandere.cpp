#include "yandere.h"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void Tag::addTag(std::string _name, std::string _type, std::string _amount) {
    short name_size = name.size();
    short amount_size = amount.size();
    short type_size = type.size();

    try {
        if (name.size() < 24) {
            name.push_back(_name);
            amount.push_back(std::stoi(_amount));

            switch (std::stoi(_type)) {
                case 0:
                    type.push_back(General);
                    break;
                case 1:
                    type.push_back(Artist);
                    break;
                case 3:
                    type.push_back(Copyright);
                    break;
                case 4:
                    type.push_back(Character);
                    break;
                case 5:
                    type.push_back(Circle);
                    break;
                case 6:
                    type.push_back(Warning);
                    break;
                default:
                    type.push_back(Other);
                    break;
            }
        }
    } catch (std::exception) {
        if (name_size < (short)name.size()) {
            name.pop_back();
        }
        if (amount_size < (short)amount.size()) {
            amount.pop_back();
        }
        if (type_size < (short)type.size()) {
            type.pop_back();
        }
    }
}

std::string Tag::typeStr(unsigned int index) {
    switch (type[index]) {
        case General:
            return "General";
            break;
        case Artist:
            return "Artist";
            break;
        case Copyright:
            return "Copyright";
            break;
        case Character:
            return "Character";
            break;
        case Circle:
            return "Circle";
            break;
        case Warning:
            return "Warning";
            break;
        default:
            return "Other";
            break;
        }
}

SDL_Color Tag::typeColor(unsigned int index) {
    switch (type[index]) {
        case General:
            return {190, 100, 100, 255};
            break;
        case Artist:
            return {222, 222, 44, 255};
            break;
        case Copyright:
            return {222, 44, 222, 255};
            break;
        case Character:
            return {44, 255, 44, 255};
            break;
        case Circle:
            return {44, 144, 255, 255};
            break;
        case Warning:
            return {255, 44, 44, 255};
            break;
        default:
            return {125, 125, 125, 255};
            break;
        }
}

void Tag::clear() {
    name.clear();
    type.clear();
    amount.clear();
}

bool Parser::request(std::string type, std::string name) {
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    inputMarkup = "";

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, ("https://yande.re/" + type + ".xml?name=" + name + "*").c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &inputMarkup);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res == CURLE_OK) {
            if (type == "tag") {
                tag.clear();
                std::vector<std::string> rt = findAllS("tag");

                for (auto t : rt) {
                    tag.addTag(byAttribute("name", t), byAttribute("type", t), byAttribute("count", t));
                }
                printf("request result: tag.size: %d\t\trt.size(): %d\t\tcount: %d\n", tag.size(), rt.size(), cer);
                rt.clear();
                cer++;
            } else {

            }

            internetConnection = true;
            return true;
        }
    }
    printf("request failed\n");
    internetConnection = false;
    return false;
}

std::string Parser::findP(std::string tag, int match) {
    int _begin, offset, _noding;
    _begin = offset = _noding = 0;

    try {
        for(int i = -1; i < match; i++) {
            for ( ; inputMarkup[offset] != '<'; offset++) {}
            offset++;

            if (inputMarkup.substr(offset, tag.length()) != tag) {
                offset++;
                i--;
                continue;
            }

            _begin = offset - 1;
        }

        while (true) {
            for ( ; inputMarkup[offset] != '<'; offset++) {}
            offset++;

            if (inputMarkup[offset] == '/') {
                if (inputMarkup.substr(offset + 1, tag.length()) == tag) {
                    if (_noding == 0) {
                        break;
                    } else {
                        _noding--;
                    }
                }
            } else if (inputMarkup.substr(offset, tag.length()) == tag) {
                offset++;
                _noding++;
                continue;
            }
            offset++;
        }

        for (; inputMarkup[offset] != '>'; offset++) {}
        offset++;
    }
    catch (std::exception) {
        printf("found error\n");
        return "no data";
    }

    printf("tag was founded: %s\n", inputMarkup.substr(_begin, offset - _begin).c_str());
    if (setToOutput) outputMarkup = inputMarkup.substr(_begin, offset - _begin);

    return inputMarkup.substr(_begin, offset - _begin);
}

std::string Parser::findS(std::string tag, int match) {
    int _begin, _offset;
    _begin = _offset = 0;

    try {
        for (int i = -1; i < match; i++) {
            for (; inputMarkup[_offset] != '<'; _offset++) {}
            _offset++;

            if (inputMarkup.substr(_offset, tag.length()) == tag && inputMarkup[_offset + tag.length()] == ' ') {
                _begin = _offset - 1;
                for (; inputMarkup[_offset] != '>'; _offset++) {}
            }
            else {
                i--;
            }
            _offset++;
        }
    }
    catch (std::exception) {
        return "no data";
    }

    if (setToOutput) outputMarkup = inputMarkup.substr(_begin, _offset - _begin);
    return inputMarkup.substr(_begin, _offset - _begin);
}

std::vector<std::string> Parser::findAllS(std::string tag, int matches) {
    int _begin, _offset;
    _begin = _offset = 0;

    std::vector<std::string> container;

    try {
        for (int i = 0; i < matches || matches == -1; i++) {
            for (; inputMarkup[_offset] != '<'; _offset++) {}
            _offset++;

            if (inputMarkup.substr(_offset, tag.length()) == tag && inputMarkup[_offset + tag.length()] == ' ') {
                _begin = _offset - 1;
                for (; inputMarkup[_offset] != '>'; _offset++) {}
                _offset++;
                container.push_back(inputMarkup.substr(_begin, _offset - _begin));
            }
            else {
                i--;
                _offset++;
            }
        }
    }
    catch (std::exception) {

    }

    return container;
}

std::string Parser::byAttribute(std::string attribute, std::string markup) {
    if (markup == "") markup = inputMarkup;
    unsigned int i = 0; unsigned int begin = 0;

    try {

        search_literal:

        for (; markup[i] != attribute[0]; i++) {}
        if (markup.substr(i, attribute.length()) != attribute) {
            i++;
            goto search_literal;
        }
        for (; markup[i] != '"'; i++) {}

        i++;
        begin = i;

        for (; markup[i] != '"'; i++) {}

    }
    catch (std::exception) {
       return "no data";
    }
    return markup.substr(begin, i - begin);
}
