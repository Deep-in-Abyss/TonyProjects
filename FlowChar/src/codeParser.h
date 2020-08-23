#ifndef __CODEPARSER_H
#define __CODEPARSER_H

#include "token.h"
#include "tree.h"

#include <fstream>
#include <memory>
#include <string>
#include <vector>

namespace FC {
namespace FE {

class CodeParser
{
private:
    std::fstream fs;
    std::vector<Token *> tokenList;

    struct parsingTableEntry {
        enum class Action : int {
            SHIFT,
            GOTO,
            REDUCE,
            ACCEPT
        } action;
        int num;

        parsingTableEntry(Action action) : action(action) {}
        parsingTableEntry(Action action, int num) : action(action), num(num) {}
    };

    struct reductionInfo {
        Token::Kind newTokenKind;
        int popNum;

        reductionInfo(Token::Kind newTokenKind, int popNum) : newTokenKind(newTokenKind), popNum(popNum) {}
    };

public:
    CodeParser(const std::string &path);
    ~CodeParser();
    void scan();
    void printTokenList();
    std::shared_ptr<IR::Stm> parse();
    parsingTableEntry lookupParsingTable(int cntState, Token::Kind tokenKind, std::pair<int, int> pos);
    reductionInfo getReductionInfo(int productionNum);
};

} // namespace FE
} // namespace FC

#endif