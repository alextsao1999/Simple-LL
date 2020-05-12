

# Simple-LL

A Toy LL Parser Builder

## Usage

```c++
int main() {
    GrammerParser grammer;
    const char *start = "Cpp {"
                        "program: expr*;"
                        "expr: term ( '+' | '-' term ['binary':3] )*;"
                        "term: factor ( '*' | '/' factor ['binary':3] )*;"
                        "factor: primary postfix*;"
                        "primary: identifier | number | ( '(' expr ')' ['compound':3] );"
                        "postfix: '(' arg_lists ')' ['call_postfix':4];"
                        "@arg_lists: expr (',' expr)*;"
                        "}";
    grammer.compile(start);
    auto *parser = grammer["program"];
    if (!parser) {
        return 0;
    }
    GrammerParser::GrammerBuilder::Lexer lexer;
    auto *source = L"add(10, 20) + 30";
    lexer.reset(source, wcslen(source));
    GrammerParser::Builder::Value value;
    parser->init(lexer);
    parser->parse(lexer, value);

    JsonWalker<int> runner;
    runner["binary"] = [&](json &value) -> int {
        if (value[1]["value"] == "+") {
            return runner(value[0]) + runner(value[2]);
        }
        if (value[1]["value"] == "-") {
            return runner(value[0]) - runner(value[2]);
        }
        if (value[1]["value"] == "*") {
            return runner(value[0]) * runner(value[2]);
        }
        if (value[1]["value"] == "/") {
            return runner(value[0]) / runner(value[2]);
        }
        return runner(value[0]);
    };
    runner["call_postfix"] = [&](json &value) -> int {
        if (value[0]["value"] == "add") {
            return runner(value[2]["value"][0]) + runner(value[2]["value"][2]);
        }
        return runner(value[0]);
    };
    runner["number"] = [&](json &value) -> int {
        std::string number = value;
        return std::stol(number);
    };

    std::cout << value << std::endl << "result:" << runner(value[0]);

    return 0;
}

```

Output

```
[{"type":"binary","value":[{"type":"call_postfix","value":[{"type":"identifier","value":"add"},{"type":"match","value":"
("},{"type":"arg_lists","value":[{"type":"number","value":"10"},{"type":"match","value":","},{"type":"number","value":"2
0"}]},{"type":"match","value":")"}]},{"type":"match","value":"+"},{"type":"number","value":"30"}]}]

result:60
```



