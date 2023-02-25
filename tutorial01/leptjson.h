#ifndef LEPTJSON_H__
#define LEPTJSON_H__

//JSON 中数据类型
typedef enum { LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT } lept_type;

//最终需要实现一个树的数据结构，每个节点使用 lept_value 结构体表示
typedef struct {
    lept_type type;
}lept_value;

enum {
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR
};

//API: 解析 JSON
int lept_parse(lept_value* v, const char* json);
//API: 获取结果的类型
lept_type lept_get_type(const lept_value* v);

#endif /* LEPTJSON_H__ */
