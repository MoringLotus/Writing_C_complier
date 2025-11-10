#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <unordered_map>
enum  {
    token_identifier = -1,
    token_num = -2,
    token_left_paren = -3,
    token_right_paren = -4,
    token_semicolon = -5,
    token_left_brace = -6,
    token_right_brace = -7
};

class TokenValidator {
private:
    std::unordered_map<std::string, std::regex> tokenPatterns = {
        {"IDENTIFIER",    std::regex(R"(^[a-zA-Z_]\w*$)")},
        {"CONSTANT",      std::regex(R"(^[0-9]+\.?[0-9]*$)")},
        {"INT_KEYWORD",   std::regex(R"(^int$)")},
        {"VOID_KEYWORD",  std::regex(R"(^void$)")},
        {"RETURN_KEYWORD",std::regex(R"(^return$)")},
        {"OPEN_PAREN",    std::regex(R"(^\($)")},      // ✅ 修复：匹配左括号
        {"CLOSE_PAREN",   std::regex(R"(^\)$)")},      // ✅ 修复：匹配右括号
        {"OPEN_BRACE",    std::regex(R"(^\{$)")},
        {"CLOSE_BRACE",   std::regex(R"(^\}$)")},
        {"SEMICOLON",     std::regex(R"(^;$)")}
    };

public:
    // 检查单个token是否合法
    bool isValidToken(const std::string& token) {
        for (const auto& [tokenType, pattern] : tokenPatterns) {
            if (std::regex_match(token, pattern)) {
                return true;
            }
        }
        return false;
    }

    // 获取token的类型
    std::string getTokenType(const std::string& token) {
        for (const auto& [tokenType, pattern] : tokenPatterns) {
            if (std::regex_match(token, pattern)) {
                return tokenType;
            }
        }
        return "UNKNOWN";
    }

    // 验证token列表
    bool validateTokens(const std::vector<std::string>& tokens) {
        for (const auto& token : tokens) {
            if (!isValidToken(token)) {
                std::cout << "非法token: " << token << std::endl;
                return false;
            }
        }
        return true;
    }
};

static std::string identifierStr = " ";
static double NumVal;

/// gettok - Return the next token from standard input.
int gettok() {
  static int LastChar = ' ';
  LastChar = getchar();
  // Skip any whitespace.
  while (isspace(LastChar))
    LastChar = getchar();

  if (isalpha(LastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
    identifierStr = LastChar;
    while (isalnum((LastChar = getchar())))
      identifierStr += LastChar;
    return token_identifier;
  }

  if (isdigit(LastChar) || LastChar == '.') { // Number: [0-9.]+
    std::string NumStr;
    do {
      NumStr += LastChar;
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');

    NumVal = strtod(NumStr.c_str(), nullptr);
    return token_num;
  }

  if(LastChar == '(')
    return token_left_paren;

  if(LastChar == ')')
    return  token_right_paren;

  if(LastChar == '{')
    return token_left_brace;

  if(LastChar == '}')
    return token_right_brace;


  if (LastChar == ';') {
    return token_semicolon;
  }

  int ThisChar = LastChar;
  LastChar = getchar();
  return ThisChar;
}
int main () {
    TokenValidator tv;

    while(true){
        int target = gettok();
        if(target == -1){
            std::cout << identifierStr << std::endl;
            std::cout << tv.getTokenType(identifierStr) << std::endl;
            identifierStr = " ";
        }else if (target == -2){
            std::cout << NumVal << std::endl;
        }else if (target == -3){
            std::cout << '(' << std::endl;
            std::cout << tv.getTokenType("(") << std::endl;
        }else if (target == -4){
             std::cout << ')' << std::endl;
            std::cout << tv.getTokenType(")") << std::endl;
        }else if (target == -5){
             std::cout << ';' << std::endl;
            std::cout << tv.getTokenType(";") << std::endl;
        }else if (target == -6){
            std::cout << '{' << std::endl;
            std::cout << tv.getTokenType("{") << std::endl;
        }else {
             std::cout << '}' << std::endl;
            std::cout << tv.getTokenType("}") << std::endl;
        }
    }
}